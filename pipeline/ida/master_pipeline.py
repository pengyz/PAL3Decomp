"""
IDAPython: PAL3.exe 完整分析管线

在新建的 PAL3.exe IDB 上一次性执行:
1. 导入 PAL3A.PDB 类型 (structs, enums)
2. 应用 FLIRT 签名 (pal3a_text.sig)
3. 应用全局变量名
4. 导出 Hex-Rays 反编译

用法 (新建 IDB 并执行管线):
  idat.exe -A -S"pal3_master_pipeline.py" original/PAL3.exe

或在已有 IDB 上执行:
  idat.exe -A -S"pal3_master_pipeline.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_funcs
import ida_name
import ida_bytes
import ida_hexrays
import ida_typeinf
import ida_fixup
import idautils
import idc
import json
import os
import time
import builtins

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "pipeline", "data", "pdb", "pdb_export.json")
GLOBALS_FILE = os.path.join(PROJECT_ROOT, "pipeline", "data", "pdb", "globals_export.json")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3")
SIG_NAME = "pal3a_text"

LOG_FILE = os.path.join(LOG_DIR, "pal3_master_pipeline_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0
RDATA_START = 0x0056A000
RDATA_END = 0x0057F178
DATA_START = 0x00580000
DATA_END = 0x0060C000

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


# ========================================================================
# Phase 1: Import Types
# ========================================================================
def phase1_import_types():
    log("")
    log("=" * 60)
    log("[Phase 1] 导入 PAL3A.PDB 类型")
    log("=" * 60)

    # Load SDK TIL for D3D/Windows types (ID3DXEffect, IDirect3DDevice9, etc.)
    # This makes D3D types available for gbRenderEffect and other gbengine types.
    til = ida_typeinf.get_idati()
    for til_name in ('mssdk_win7', 'mssdk_win10'):
        rc = ida_typeinf.add_til(til_name, ida_typeinf.ADDTIL_SILENT)
        if rc:
            log("[*] Loaded TIL: %s" % til_name)
            break
    else:
        log("[!] No mssdk TIL found (D3D types may be unavailable)")

    if not os.path.exists(PDB_EXPORT):
        log("[!] PDB 文件不存在: %s" % PDB_EXPORT)
        return

    with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
        pdb_data = json.load(f)

    classes = pdb_data.get('classes', [])
    enums = pdb_data.get('enums', [])
    log("[*] 类: %d, 枚举: %d" % (len(classes), len(enums)))

    til = ida_typeinf.get_idati()

    # Enums - format: {name, values: {NAME: "value_str"}}
    enum_ok = 0
    for enum_info in enums:
        name = enum_info.get('name', '')
        values = enum_info.get('values', {})
        if not name or not values:
            continue
        # Skip anonymous enums (contain "::" with __unnamed)
        if '__unnamed' in name or '::' in name:
            continue
        member_strs = []
        for mname, mval_str in values.items():
            try:
                mval = int(mval_str)
            except (ValueError, TypeError):
                mval = 0
            member_strs.append('    %s = %d' % (mname, mval))
        if not member_strs:
            continue
        decl = 'enum %s {\n%s\n};' % (name, ',\n'.join(member_strs))
        tinfo = ida_typeinf.tinfo_t()
        if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
            tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
            enum_ok += 1

    log("[*] 枚举导入: %d / %d" % (enum_ok, len(enums)))

    # System types provided by SDK headers — do NOT import from PDB (creates blobs)
    _SKIP_SYSTEM_TYPES = {
        '_DIMOUSESTATE', '_DIMOUSESTATE2', '_DIJOYSTATE', '_DIJOYSTATE2',
        '_DIDEVCAPS', '_DIDEVICEINSTANCEA', '_DIDEVICEOBJECTINSTANCEA',
        'DIMOUSESTATE', 'DIMOUSESTATE2', 'DIJOYSTATE', 'DIJOYSTATE2',
        'tagRECT', 'tagPOINT', 'tagSIZE', 'tagMSG', 'RECT', 'POINT', 'SIZE',
        'WNDCLASSA', 'tagWNDCLASSA', '_WIN32_FIND_DATAA',
        '_FILETIME', '_SYSTEMTIME', '_MEMORYSTATUS', '_SECURITY_ATTRIBUTES',
        '_OSVERSIONINFOA', '_STARTUPINFOA', '_GUID', 'GUID', 'IID',
        'D3DMATRIX', '_D3DMATRIX', 'D3DVECTOR', '_D3DVECTOR',
        '_iobuf', 'FILE',
    }

    # Forward declarations
    for cls in classes:
        name = cls.get('name', '')
        if name and name not in _SKIP_SYSTEM_TYPES:
            decl = 'struct %s;' % name
            tinfo = ida_typeinf.tinfo_t()
            if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
                tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)

    # Full definitions - format: {name, size, data_members: [{name, type, offset}]}
    cls_ok = 0
    for cls in classes:
        name = cls.get('name', '')
        size = cls.get('size', 0)
        data_members = cls.get('data_members', [])
        if not name:
            continue
        # Skip system types (SDK headers provide complete definitions)
        if name in _SKIP_SYSTEM_TYPES:
            continue
        # Skip names with template chars that IDA can't handle
        if '<' in name or '>' in name:
            continue

        # Try to build struct with members
        if data_members and size > 0:
            member_strs = []
            last_offset = 0
            for dm in data_members:
                mtype = dm.get('type', 'int')
                mname = dm.get('name', '_field')
                # Clean type for IDA
                mtype = mtype.replace('class ', '').replace('struct ', '')
                if not mname or mname.startswith('__'):
                    mname = '_field_%X' % dm.get('offset', 0)
                member_strs.append('    %s %s;' % (mtype, mname))
            if member_strs:
                decl = 'struct %s {\n%s\n};' % (name, '\n'.join(member_strs))
                tinfo = ida_typeinf.tinfo_t()
                if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
                    tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
                    cls_ok += 1
                    continue

        # Fallback: opaque struct with known size
        if size > 0:
            decl = 'struct %s { char _data[%d]; };' % (name, size)
            tinfo = ida_typeinf.tinfo_t()
            if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
                tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
                cls_ok += 1

    log("[*] 类导入: %d / %d" % (cls_ok, len(classes)))


# ========================================================================
# Phase 2: Apply FLIRT Signatures
# ========================================================================
def phase2_apply_flirt():
    log("")
    log("=" * 60)
    log("[Phase 2] 应用 FLIRT 签名")
    log("=" * 60)

    # Count functions before
    before_named = 0
    before_total = 0
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        if ea < TEXT_START or ea >= TEXT_END:
            continue
        before_total += 1
        name = ida_name.get_name(ea) or ""
        if name and not name.startswith("sub_"):
            before_named += 1

    log("[*] 签名应用前: %d 命名 / %d 总函数" % (before_named, before_total))

    # Apply FLIRT signature file using ida_funcs API
    import ida_funcs as _ida_funcs
    result = _ida_funcs.apply_idasgn_to(SIG_NAME, TEXT_START, False)
    log("[*] apply_idasgn_to('%s', 0x%X) 返回: %d" % (SIG_NAME, TEXT_START, result))
    if result >= 0:
        log("[*] FLIRT 签名应用成功")
    else:
        log("[!] FLIRT 签名应用失败 (返回 %d)" % result)
        log("    请确认 %s.sig 在 IDA sig/pc/ 目录中" % SIG_NAME)

    # Wait for auto-analysis
    ida_auto.auto_wait()

    # Count after
    after_named = 0
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        if ea < TEXT_START or ea >= TEXT_END:
            continue
        name = ida_name.get_name(ea) or ""
        if name and not name.startswith("sub_"):
            after_named += 1

    log("[*] 签名应用后: %d 命名 (+%d)" % (after_named, after_named - before_named))


# ========================================================================
# Phase 3: Apply Global Variable Names
# ========================================================================
def phase3_apply_globals():
    log("")
    log("=" * 60)
    log("[Phase 3] 应用全局变量名")
    log("=" * 60)

    if not os.path.exists(GLOBALS_FILE):
        log("[!] Globals 文件不存在: %s" % GLOBALS_FILE)
        return

    with open(GLOBALS_FILE, 'r', encoding='utf-8') as f:
        globals_data = json.load(f)

    globals_list = globals_data.get('globals', [])
    log("[*] 全局变量: %d" % len(globals_list))

    applied = 0
    skipped = 0
    for g in globals_list:
        name = g.get('name', '')
        addr_str = g.get('address', '')
        if not name or not addr_str:
            continue
        try:
            addr = int(addr_str, 16)
        except (ValueError, TypeError):
            continue

        # Only shared address range
        if not (RDATA_START <= addr < RDATA_END or DATA_START <= addr < DATA_END):
            skipped += 1
            continue
        if not ida_bytes.is_loaded(addr):
            skipped += 1
            continue

        existing = ida_name.get_name(addr) or ""
        if existing and not existing.startswith("dword_") and \
           not existing.startswith("byte_") and \
           not existing.startswith("unk_") and \
           not existing.startswith("off_"):
            continue

        clean = name.replace('::', '_').replace('<', '_').replace('>', '_')
        clean = clean.replace(' ', '_').replace('*', 'p')
        if ida_name.set_name(addr, clean, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            applied += 1

    log("[*] 应用: %d, 跳过: %d" % (applied, skipped))


# ========================================================================
# Phase 4: Export Hex-Rays Decompilation
# ========================================================================
def phase4_export():
    log("")
    log("=" * 60)
    log("[Phase 4] 导出 Hex-Rays 反编译")
    log("=" * 60)

    os.makedirs(OUTPUT_DIR, exist_ok=True)

    # Clean old decomp files (preserve annotations.json and _prefixed files)
    import glob
    old_files = glob.glob(os.path.join(OUTPUT_DIR, "*.json"))
    removed = 0
    for f in old_files:
        basename = os.path.basename(f)
        if basename.startswith('_') or basename == 'annotations.json':
            continue
        os.remove(f)
        removed += 1
    if removed:
        log("[*] 清理旧文件: %d" % removed)

    # Collect targets
    targets = []
    named = 0
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        if ea < TEXT_START or ea >= TEXT_END:
            continue
        name = ida_name.get_name(ea) or ""
        if not name or name.startswith("nullsub_") or name.startswith("j_"):
            continue
        func = ida_funcs.get_func(ea)
        if not func or func.size() == 0:
            continue
        is_named = not name.startswith("sub_")
        if is_named:
            named += 1
        targets.append((ea, name, func.size(), is_named))

    log("[*] 目标: %d (命名: %d, sub_: %d)" % (len(targets), named, len(targets) - named))

    # Export
    exported = 0
    errors = 0
    t0 = time.time()

    for i, (ea, name, size, is_named) in enumerate(targets):
        if (i + 1) % 500 == 0:
            elapsed = time.time() - t0
            rate = (i + 1) / elapsed if elapsed > 0 else 0
            log("  [%d/%d] exported=%d (%.0f f/s)" % (i + 1, len(targets), exported, rate))

        try:
            cfunc = ida_hexrays.decompile(ea)
            if not cfunc:
                errors += 1
                continue

            code = str(cfunc)
            sig = cfunc.type.dstr()

            demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
            display_name = demangled if demangled else name

            # Filename
            safe = display_name.replace('::', '_').replace('<', '_').replace('>', '_')
            safe = safe.replace('*', '_').replace(' ', '_').replace('?', '_')
            safe = safe.replace('@', '_').replace('$', '_').replace(',', '_')
            safe = safe.replace('(', '').replace(')', '').replace('/', '_')
            safe = safe.replace('"', '').replace("'", '').replace('\\', '_')
            while '__' in safe:
                safe = safe.replace('__', '_')
            safe = safe.strip('_')
            if len(safe) > 100:
                safe = safe[:100]
            filename = '%s_%08x.json' % (safe, ea)

            result = {
                'name': display_name,
                'mangled_name': name,
                'address': '0x%08X' % ea,
                'size_bytes': size,
                'signature': sig,
                'decompiled_c': code,
            }

            with open(os.path.join(OUTPUT_DIR, filename), 'w', encoding='utf-8') as f:
                json.dump(result, f, indent=2, ensure_ascii=False)

            exported += 1

        except Exception:
            errors += 1

    elapsed = time.time() - t0
    log("[*] 导出完成: %d 成功, %d 错误 (%.1fs)" % (exported, errors, elapsed))

    # Summary
    summary = {
        'total_targets': len(targets),
        'named_functions': named,
        'exported': exported,
        'errors': errors,
        'elapsed_seconds': round(elapsed, 1),
    }
    with open(os.path.join(OUTPUT_DIR, "_export_summary.json"), 'w', encoding='utf-8') as f:
        json.dump(summary, f, indent=2)


# ========================================================================
# Main
# ========================================================================
def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 分析管线启动")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        phase1_import_types()

        # After importing types, reanalyze .text to refresh Hex-Rays type cache.
        # Without this, functions decompiled during auto_wait() retain anonymous
        # struct references (struct #NNN) instead of the newly imported names.
        log("[*] Requesting reanalysis to refresh type cache...")
        ida_auto.auto_mark_range(TEXT_START, TEXT_END, ida_auto.AU_USED)
        ida_auto.auto_wait()
        log("[*] Reanalysis complete")

        idc.save_database(idc.get_idb_path(), 0)

        # phase2_apply_flirt()  # disabled: +0 contribution, TIL causes stdiobuf misattribution
        idc.save_database(idc.get_idb_path(), 0)

        phase3_apply_globals()
        idc.save_database(idc.get_idb_path(), 0)

        phase4_export()
        idc.save_database(idc.get_idb_path(), 0)

        log("")
        log("[*] 全部完成!")

    except Exception as e:
        log("[!] 致命错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
