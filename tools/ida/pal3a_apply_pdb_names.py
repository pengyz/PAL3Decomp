"""
IDAPython: 将 PDB 函数名批量应用到 PAL3A.exe.i64

问题: PAL3A.exe.i64 中 8782/9625 个函数仍为 sub_XXXXX，
PDB 符号在 pdb_export.json 中但未应用到 IDB 函数名。

本脚本直接读取 pdb_export.json，将函数名应用到对应地址。
这是运行 pal3a_create_sig.py 的前置步骤。

运行环境: PAL3A.exe.i64
用法:
  idat.exe -A -S"pal3a_apply_pdb_names.py" PAL3A.exe.i64
"""

import ida_auto
import ida_funcs
import ida_name
import idautils
import idc
import json
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3a_apply_pdb_names_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x00558000


def main():
    lines = []

    def log(msg):
        lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] 应用 PDB 函数名到 PAL3A.exe.i64")

        if not os.path.exists(PDB_EXPORT):
            log("[!] 找不到: %s" % PDB_EXPORT)
            return

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        functions = pdb_data['functions']
        log("[*] PDB 函数总数: %d" % len(functions))

        # Build address → name mapping for .text functions
        addr_to_name = {}
        for func in functions:
            addr = int(func['address'], 16)
            mangled = func.get('mangled_name', '')
            if mangled and TEXT_START <= addr < TEXT_END:
                addr_to_name[addr] = mangled

        log("[*] .text 内 PDB 函数: %d" % len(addr_to_name))

        # Apply names
        applied = 0
        already_named = 0
        no_func = 0
        failed = 0

        for addr, name in sorted(addr_to_name.items()):
            # Check if function exists at this address
            func = ida_funcs.get_func(addr)
            if not func:
                # Try to create function if code exists here
                if not ida_funcs.add_func(addr):
                    no_func += 1
                    continue

            # Check existing name
            existing = ida_name.get_name(addr) or ""
            if existing == name:
                already_named += 1
                continue

            # Don't overwrite non-sub names (might be manually corrected)
            if existing and not existing.startswith("sub_"):
                already_named += 1
                continue

            # Apply mangled name
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN):
                applied += 1
            else:
                # Try with SN_FORCE for duplicates
                if ida_name.set_name(addr, name, ida_name.SN_FORCE):
                    applied += 1
                else:
                    failed += 1

        log("")
        log("[*] 完成!")
        log("    应用: %d" % applied)
        log("    已有名称: %d" % already_named)
        log("    无函数: %d" % no_func)
        log("    失败: %d" % failed)

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log("[!] 错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
