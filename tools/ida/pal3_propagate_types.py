"""
IDAPython: PAL3.exe 类型传播第二轮

策略:
1. 从 .rdata 中的 RTTI 信息提取所有类名及其 vtable 地址
2. 对每个 vtable，在 .data 中搜索引用它的地址 → 这就是该类的全局实例
3. 为找到的实例设置类型并命名
4. 对所有 PDB 中的大类，在已有反编译中搜索 this+offset 模式验证
5. 命名更多函数：通过 vtable slot 匹配 PDB 虚函数名

用法:
  idat.exe -A -S"pal3_propagate_types.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_funcs
import ida_hexrays
import ida_name
import ida_typeinf
import ida_segment
import ida_xref
import idautils
import idc
import json
import os
import re
import struct
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
CALLGRAPH = os.path.join(PROJECT_ROOT, "asm", "pal3", "call_graph.json")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
LOG_FILE = os.path.join(LOG_DIR, "pal3_propagate_types_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0
RDATA_START = 0x0056A000
RDATA_END = 0x00580000
DATA_START = 0x00580000
DATA_END = 0x01897000

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def scan_rtti_vtables():
    """扫描 .rdata 中的 RTTI 信息，提取所有 vtable → class 映射"""
    vtables = {}  # vtable_addr -> class_name

    seg = ida_segment.get_segm_by_name(".rdata")
    if not seg:
        return vtables

    ea = seg.start_ea
    end = seg.end_ea

    while ea < end - 4:
        # Look for TypeDescriptor references
        # Pattern: ".?AVClassName@@" at td+8
        raw = ida_bytes.get_strlit_contents(ea, -1, 0)
        if raw:
            s = raw.decode('utf-8', errors='replace')
            class_name = None
            if s.startswith('.?AV') and s.endswith('@@'):
                class_name = s[4:-2]
            elif s.startswith('.?AU') and s.endswith('@@'):
                class_name = s[4:-2]

            if class_name and len(class_name) > 1 and not class_name.startswith('?'):
                # This is a TypeDescriptor at (ea - 8)
                # Find Complete Object Locator that references this TD
                td_addr = ea - 8

                # Search for COL: at COL+12 = td_addr
                # COL is referenced at vtable[-1]
                # Brute-force: scan .rdata for dwords == td_addr at offset +12
                for col_ea in range(seg.start_ea, seg.end_ea - 20, 4):
                    if ida_bytes.get_dword(col_ea + 12) == td_addr:
                        # Found COL at col_ea
                        # vtable is at the address that has [vtable-4] = col_ea
                        for vt_ea in range(seg.start_ea + 4, seg.end_ea - 4, 4):
                            if ida_bytes.get_dword(vt_ea - 4) == col_ea:
                                # Verify: vt_ea should point to code
                                first_vf = ida_bytes.get_dword(vt_ea)
                                if TEXT_START <= first_vf < TEXT_END:
                                    vtables[vt_ea] = class_name
                                break
                        break
        ea += 1

    return vtables


def scan_rtti_fast():
    """更快的 RTTI 扫描：直接找 Complete Object Locator 模式"""
    vtables = {}

    seg = ida_segment.get_segm_by_name(".rdata")
    if not seg:
        return vtables

    # 策略：扫描所有 xrefs 到 .rdata 中有 .?AV 字符串的位置
    # 更快的方式：直接枚举所有已知的 off_ 数据引用
    ea = seg.start_ea
    end = seg.end_ea

    while ea < end - 16:
        # Check if ea looks like start of a vtable:
        # [ea-4] points to .rdata (COL)
        # [ea], [ea+4], ... point to .text (virtual functions)
        ptr0 = ida_bytes.get_dword(ea)
        if not (TEXT_START <= ptr0 < TEXT_END):
            ea += 4
            continue

        # Check [ea-4] for COL pointer
        col_ptr = ida_bytes.get_dword(ea - 4)
        if not (seg.start_ea <= col_ptr < seg.end_ea):
            ea += 4
            continue

        # Count consecutive function pointers
        count = 0
        for i in range(200):
            ptr = ida_bytes.get_dword(ea + i * 4)
            if TEXT_START <= ptr < TEXT_END:
                f = ida_funcs.get_func(ptr)
                if f and f.start_ea == ptr:
                    count += 1
                else:
                    break
            else:
                break

        if count < 2:
            ea += 4
            continue

        # Try to get class name from COL -> TD
        class_name = None
        td_ptr = ida_bytes.get_dword(col_ptr + 12)
        if td_ptr and ida_bytes.is_loaded(td_ptr + 8):
            raw = ida_bytes.get_strlit_contents(td_ptr + 8, -1, 0)
            if raw:
                s = raw.decode('utf-8', errors='replace')
                if s.startswith('.?AV') and s.endswith('@@'):
                    class_name = s[4:-2]
                elif s.startswith('.?AU') and s.endswith('@@'):
                    class_name = s[4:-2]

        if class_name:
            vtables[ea] = (class_name, count)

        ea += max(count * 4, 4)

    return vtables


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 类型传播 第二轮")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        t0 = time.time()

        # === Phase 1: RTTI vtable 扫描 ===
        log("")
        log("=" * 60)
        log("[Phase 1] RTTI 虚函数表扫描")
        log("=" * 60)

        vtables = scan_rtti_fast()
        log("[*] 发现 vtable: %d" % len(vtables))

        # Load PDB for virtual function matching
        pdb_data = None
        pdb_vfuncs = {}  # class_name -> [vfunc_names]
        if os.path.exists(PDB_EXPORT):
            with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
                pdb_data = json.load(f)
            # Build virtual function list per class
            for func in pdb_data.get('functions', []):
                if func.get('is_virtual'):
                    cls = func.get('class', '')
                    if cls:
                        pdb_vfuncs.setdefault(cls, []).append(func)

        # Name vtables and virtual functions
        vtable_named = 0
        vfunc_named = 0

        for vt_ea, (class_name, vf_count) in sorted(vtables.items()):
            # Name vtable
            cur = ida_name.get_name(vt_ea) or ""
            vt_label = "vtbl_%s" % class_name
            if cur.startswith("off_") or not cur or cur.startswith("unk_"):
                ida_name.set_name(vt_ea, vt_label, ida_name.SN_NOWARN | ida_name.SN_FORCE)
                vtable_named += 1

            # Name virtual function slots
            for i in range(vf_count):
                vf_ea = ida_bytes.get_dword(vt_ea + i * 4)
                cur_vf = ida_name.get_name(vf_ea) or ""
                if not cur_vf.startswith("sub_"):
                    continue

                # Try PDB match
                new_name = None
                if class_name in pdb_vfuncs:
                    vf_list = pdb_vfuncs[class_name]
                    if i < len(vf_list):
                        pdb_name = vf_list[i].get('name', '')
                        if pdb_name:
                            new_name = "%s_%s" % (class_name, pdb_name)

                if not new_name:
                    # Generic naming
                    new_name = "%s_vf%d" % (class_name, i)

                clean = new_name.replace('::', '_').replace(' ', '_')
                clean = clean.replace('<', '_').replace('>', '_').replace('~', 'dtor_')
                if len(clean) > 80:
                    clean = clean[:80]

                if ida_name.set_name(vf_ea, clean, ida_name.SN_NOWARN):
                    vfunc_named += 1

        log("[*] vtable 命名: %d, 虚函数命名: %d" % (vtable_named, vfunc_named))

        # Show discovered classes
        if vtables:
            log("[*] 发现的类:")
            for vt_ea, (cls, cnt) in sorted(vtables.items(), key=lambda x: -x[1][1])[:30]:
                log("  0x%08X %-30s (%d vfuncs)" % (vt_ea, cls, cnt))

        # === Phase 2: 全局实例查找 ===
        log("")
        log("=" * 60)
        log("[Phase 2] 全局对象实例定位")
        log("=" * 60)

        # For each vtable, find data references to it
        # If .data has a dword that equals vtable_addr, that's the object's vtable pointer
        instances_found = 0
        instance_map = {}  # data_addr -> class_name

        for vt_ea, (class_name, vf_count) in vtables.items():
            # Find data xrefs pointing TO this vtable address
            # (object construction: mov [obj], offset vtable)
            for xref in idautils.DataRefsTo(vt_ea):
                if DATA_START <= xref < DATA_END:
                    # This is likely a global instance of this class
                    instance_map[xref] = class_name
                    instances_found += 1

                    cur = ida_name.get_name(xref) or ""
                    if cur.startswith("dword_") or cur.startswith("off_") or not cur:
                        inst_name = "g_%s" % class_name
                        ida_name.set_name(xref, inst_name, ida_name.SN_NOWARN | ida_name.SN_FORCE)
                        log("  [+] 0x%08X: %s (instance of %s)" % (xref, inst_name, class_name))

        log("[*] 全局实例: %d" % instances_found)

        # === Phase 3: __thiscall 签名从 vtable 推断 ===
        log("")
        log("=" * 60)
        log("[Phase 3] __thiscall 签名推断")
        log("=" * 60)

        til = ida_typeinf.get_idati()
        thiscall_applied = 0

        for vt_ea, (class_name, vf_count) in vtables.items():
            # Check if class type exists in IDA
            tinfo = ida_typeinf.tinfo_t()
            if not tinfo.get_named_type(til, class_name):
                continue

            # Apply __thiscall to all virtual functions
            for i in range(vf_count):
                vf_ea = ida_bytes.get_dword(vt_ea + i * 4)
                cur_type = idc.get_type(vf_ea) or ""
                if "__thiscall" in cur_type:
                    continue

                name = ida_name.get_name(vf_ea) or ("sub_%X" % vf_ea)
                sig = "int __thiscall %s(%s *this)" % (name, class_name)
                if idc.SetType(vf_ea, sig):
                    thiscall_applied += 1

        log("[*] __thiscall 签名应用: %d" % thiscall_applied)

        # === Save and re-export ===
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] IDB 已保存")

        # Re-export
        log("")
        log("=" * 60)
        log("[Phase 4] 重新导出")
        log("=" * 60)

        os.makedirs(OUTPUT_DIR, exist_ok=True)
        import glob
        for f in glob.glob(os.path.join(OUTPUT_DIR, "*.json")):
            if not os.path.basename(f).startswith('_'):
                os.remove(f)

        targets = []
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if not name or name.startswith("nullsub_") or name.startswith("j_"):
                continue
            func = ida_funcs.get_func(ea)
            if not func or func.size() <= 1:
                continue
            targets.append((ea, name, func.size()))

        targets.sort()
        named = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] 导出目标: %d (命名: %d, +%d)" % (len(targets), named, named - 1453))

        exported = 0
        errors = 0
        t1 = time.time()

        for i, (ea, name, size) in enumerate(targets):
            if (i + 1) % 1000 == 0:
                elapsed = time.time() - t1
                log("  [%d/%d] exported=%d (%.0f f/s)" % (
                    i+1, len(targets), exported, (i+1)/elapsed))
            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    errors += 1
                    continue
                code = str(cfunc)
                sig = cfunc.type.dstr()
                demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else name

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
        log("[*] 导出: %d 成功, %d 错误" % (exported, errors))
        log("")
        log("=" * 60)
        log("[*] 第二轮完成!")
        log("  vtable: %d, 虚函数命名: %d" % (vtable_named, vfunc_named))
        log("  全局实例: %d" % instances_found)
        log("  __thiscall: %d" % thiscall_applied)
        log("  命名函数: %d (+%d)" % (named, named - 1453))
        log("  总耗时: %.1fs" % elapsed)
        log("=" * 60)

        summary = {
            'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S"),
            'vtables_found': len(vtables),
            'vtables_named': vtable_named,
            'vfuncs_named': vfunc_named,
            'instances_found': instances_found,
            'thiscall_applied': thiscall_applied,
            'named_functions': named,
            'exported': exported,
        }
        with open(os.path.join(OUTPUT_DIR, "_export_summary.json"), 'w', encoding='utf-8') as f:
            json.dump(summary, f, indent=2)

        idc.save_database(idc.get_idb_path(), 0)

    except Exception as e:
        log("[!] 致命错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
