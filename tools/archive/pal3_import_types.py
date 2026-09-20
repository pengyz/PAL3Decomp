"""
IDAPython: 导入 PAL3A.PDB 类型系统到 PAL3.exe IDB

将 1057 个 class + 351 个 enum 导入到 PAL3.exe IDB。
类型系统在 PAL3A 和 PAL3 之间高度一致（同一源代码）。

运行环境: PAL3.exe.i64
输入: asm/pal3a/pdb_export.json

用法:
  idat.exe -A -S"pal3_import_types.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_typeinf
import idc
import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
GLOBALS_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3a", "globals_export.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_import_types_log.txt")

# PAL3.exe data sections (for global variable naming)
RDATA_START = 0x0056A000
RDATA_END = 0x0057F178
DATA_START = 0x00580000
DATA_END = 0x0060C000

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def phase1_enums(til, enums):
    """Import enums. Format: {name, values: {NAME: "value_str"}}"""
    log("[Phase 1] 导入枚举 (%d)" % len(enums))
    ok = 0
    for enum_info in enums:
        name = enum_info.get('name', '')
        values = enum_info.get('values', {})
        if not name or not values:
            continue
        if '__unnamed' in name or '::__unnamed' in name:
            continue
        # Clean name for IDA
        if '<' in name or '>' in name or '::' in name:
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
            ok += 1

    log("  成功: %d" % ok)
    return ok


def phase2_classes(til, classes):
    """Import classes. Format: {name, size, data_members: [{name, type, offset}]}"""
    log("[Phase 2] 导入类/结构体 (%d)" % len(classes))

    # Step 1: Forward declarations
    for cls in classes:
        name = cls.get('name', '')
        if name and '<' not in name and '>' not in name:
            decl = 'struct %s;' % name
            tinfo = ida_typeinf.tinfo_t()
            if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
                tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)

    # Step 2: Full definitions
    ok = 0
    for cls in classes:
        name = cls.get('name', '')
        size = cls.get('size', 0)
        data_members = cls.get('data_members', [])
        if not name:
            continue
        if '<' in name or '>' in name:
            continue

        # Try building struct from data_members
        if data_members and size > 0:
            member_strs = []
            for dm in data_members:
                mtype = dm.get('type', 'int')
                mname = dm.get('name', '_field')
                mtype = mtype.replace('class ', '').replace('struct ', '')
                if not mname or mname.startswith('__'):
                    mname = '_field_%X' % dm.get('offset', 0)
                member_strs.append('    %s %s;' % (mtype, mname))
            if member_strs:
                decl = 'struct %s {\n%s\n};' % (name, '\n'.join(member_strs))
                tinfo = ida_typeinf.tinfo_t()
                if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
                    tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
                    ok += 1
                    continue

        # Fallback: opaque struct
        if size > 0:
            decl = 'struct %s { char _data[%d]; };' % (name, size)
            tinfo = ida_typeinf.tinfo_t()
            if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
                tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
                ok += 1

    log("  成功: %d" % ok)
    return ok


def phase3_globals(til):
    """Apply global variable names from PAL3A globals export."""
    log("[Phase 3] 应用全局变量名")

    if not os.path.exists(GLOBALS_FILE):
        log("  跳过: 文件不存在 %s" % GLOBALS_FILE)
        return 0

    with open(GLOBALS_FILE, 'r', encoding='utf-8') as f:
        globals_data = json.load(f)

    import ida_bytes
    import ida_name

    globals_list = globals_data.get('globals', [])
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

        # Only .rdata and .data ranges that are shared between PAL3A and PAL3
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

    log("  应用: %d, 跳过: %d" % (applied, skipped))
    return applied


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 类型导入 + 全局变量")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        if not os.path.exists(PDB_EXPORT):
            log("[!] PDB 文件不存在: %s" % PDB_EXPORT)
            return

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        classes = pdb_data.get('classes', [])
        enums = pdb_data.get('enums', [])
        log("[*] PDB 数据: %d classes, %d enums" % (len(classes), len(enums)))

        til = ida_typeinf.get_idati()

        phase1_enums(til, enums)
        phase2_classes(til, classes)
        phase3_globals(til)

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")
        log("[*] 完成!")

    except Exception as e:
        log("[!] 错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
