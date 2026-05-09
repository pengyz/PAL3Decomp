"""
IDAPython: 导入 PAL3A.PDB 类型系统到 PAL3.exe IDB

运行环境: PAL3.exe IDB (新建数据库)
输入: asm/pal3a/pdb_export.json (classes + enums)

将 PAL3A.PDB 中的 1057 个 class 和 351 个 enum 定义导入到
PAL3.exe 的 IDA 数据库中，使 Hex-Rays 反编译能产生高质量输出。

用法:
  idat.exe -A -S"pal3_import_types.py" PAL3.exe.i64
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
LOG_FILE = os.path.join(LOG_DIR, "pal3_import_types_log.txt")


def import_enum(til, enum_info):
    """Import a single enum definition"""
    name = enum_info.get('name', '')
    members = enum_info.get('members', [])
    if not name or not members:
        return False

    # Create C enum declaration
    member_strs = []
    for m in members:
        mname = m.get('name', '')
        mval = m.get('value', 0)
        if mname:
            member_strs.append('    %s = %d' % (mname, mval))

    if not member_strs:
        return False

    decl = 'enum %s {\n%s\n};' % (name, ',\n'.join(member_strs))

    # Parse and add to TIL
    tinfo = ida_typeinf.tinfo_t()
    result = ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
    if result is not None:
        tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
        return True
    return False


def import_class(til, class_info):
    """
    Import a single class/struct definition.
    Uses the C declaration from PDB if available.
    """
    name = class_info.get('name', '')
    c_decl = class_info.get('c_declaration', '')
    size = class_info.get('size', 0)

    if not name:
        return False

    # If we have a C declaration from PDB export, use it directly
    if c_decl:
        tinfo = ida_typeinf.tinfo_t()
        result = ida_typeinf.parse_decl(tinfo, til, c_decl + ';', ida_typeinf.PT_TYP)
        if result is not None:
            tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
            return True

    # Fallback: create opaque struct with known size
    if size > 0:
        decl = 'struct %s { char _data[%d]; };' % (name, size)
        tinfo = ida_typeinf.tinfo_t()
        result = ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
        if result is not None:
            tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
            return True

    # Minimal forward declaration
    decl = 'struct %s;' % name
    tinfo = ida_typeinf.tinfo_t()
    result = ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
    if result is not None:
        tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
        return True

    return False


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 类型导入 (from PAL3A.PDB)")

        if not os.path.exists(PDB_EXPORT):
            log("[!] 找不到 PDB 导出文件: %s" % PDB_EXPORT)
            return

        log("[*] 加载 PDB 数据: %s" % PDB_EXPORT)
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        classes = pdb_data.get('classes', [])
        enums = pdb_data.get('enums', [])
        log("[*] 类型: %d classes, %d enums" % (len(classes), len(enums)))

        til = ida_typeinf.get_idati()

        # Phase 1: Import enums first (no dependencies)
        log("[*] Phase 1: 导入枚举...")
        enum_ok = 0
        enum_fail = 0
        for enum_info in enums:
            if import_enum(til, enum_info):
                enum_ok += 1
            else:
                enum_fail += 1
        log("    成功: %d, 失败: %d" % (enum_ok, enum_fail))

        # Phase 2: Forward-declare all classes (resolve circular deps)
        log("[*] Phase 2: 前向声明所有类...")
        for cls in classes:
            name = cls.get('name', '')
            if name:
                decl = 'struct %s;' % name
                tinfo = ida_typeinf.tinfo_t()
                ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
                tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)

        # Phase 3: Import full class definitions
        log("[*] Phase 3: 导入完整类定义...")
        cls_ok = 0
        cls_fail = 0
        cls_fail_names = []

        for cls in classes:
            if import_class(til, cls):
                cls_ok += 1
            else:
                cls_fail += 1
                name = cls.get('name', '')
                if name and len(cls_fail_names) < 20:
                    cls_fail_names.append(name)

        log("    成功: %d, 失败: %d" % (cls_ok, cls_fail))
        if cls_fail_names:
            log("    失败样本: %s" % ', '.join(cls_fail_names[:10]))

        # Phase 4: Retry failed classes (dependencies may now be resolved)
        if cls_fail > 0:
            log("[*] Phase 4: 重试失败的类...")
            retry_ok = 0
            for cls in classes:
                name = cls.get('name', '')
                if not name:
                    continue
                # Check if already imported successfully
                tinfo = ida_typeinf.tinfo_t()
                if tinfo.get_named_type(til, name):
                    # Check if it's just a forward declaration (size 0 or opaque)
                    if tinfo.get_size() > 0:
                        continue
                # Retry
                if import_class(til, cls):
                    retry_ok += 1
            log("    额外成功: %d" % retry_ok)
            cls_ok += retry_ok

        log("")
        log("[*] 导入完成!")
        log("    枚举: %d / %d" % (enum_ok, len(enums)))
        log("    类: %d / %d" % (cls_ok, len(classes)))

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log("[!] 错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))


if __name__ == '__main__':
    main()
