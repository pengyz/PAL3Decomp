"""
IDAPython: 导出 PAL3.exe IDB 中所有已命名函数到 JSON

输出: asm/pal3/pal3_names.json

运行环境: PAL3.exe.i64
"""

import ida_auto
import ida_funcs
import ida_name
import idautils
import idc
import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))

OUTPUT_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "pal3_names.json")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0


def main():
    ida_auto.auto_wait()

    functions = []
    named_count = 0
    total_count = 0

    for ea in idautils.Functions(TEXT_START, TEXT_END):
        total_count += 1
        name = ida_name.get_name(ea) or ""

        func = ida_funcs.get_func(ea)
        size = func.end_ea - func.start_ea if func else 0

        demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN)) or ""
        comment = idc.get_func_cmt(ea, 0) or ""
        is_named = not (name.startswith("sub_") or name.startswith("nullsub_"))

        if is_named:
            named_count += 1

        functions.append({
            'address': '0x%08X' % ea,
            'mangled': name,
            'demangled': demangled,
            'size': size,
            'named': is_named,
            'comment': comment,
        })


    output = {
        'meta': {
            'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S"),
            'binary': 'PAL3.exe',
            'text_range': ['0x%08X' % TEXT_START, '0x%08X' % TEXT_END],
            'total_functions': total_count,
            'named_functions': named_count,
            'coverage': '%.1f%%' % (100.0 * named_count / total_count),
        },
        'functions': functions,
    }

    os.makedirs(os.path.dirname(OUTPUT_FILE), exist_ok=True)
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
        json.dump(output, f, indent=2, ensure_ascii=False)

    print("[*] Exported %d/%d named functions to %s" % (named_count, total_count, OUTPUT_FILE))
    idc.qexit(0)


if __name__ == '__main__':
    main()
