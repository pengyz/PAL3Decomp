#!/usr/bin/env python3
"""[探针 2026-11-18] graph 布局定谳——LoadFromFile(0x4bb260) 的原始 Read disp 链。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_graph_loadfromfile_20261118.py
"""
import sys

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)

import idc
import ida_ua
import ida_bytes

for name, ea, cap in (
        ('graph LoadFromFile', 0x004bb260, 200),
        ('sg_emitter Render',  0x004bae60, 500),
):
    print('\n=== %s @ 0x%08x ===' % (name, ea))
    cur = ea
    n = 0
    while cur < ea + cap and n < 80:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        insn = ida_ua.insn_t()
        length = ida_ua.decode_insn(insn, cur)
        if length == 0:
            break
        print('  0x%08x  %s' % (cur, idc.generate_disasm_line(cur, 0)))
        if idc.print_insn_mnem(cur) == 'ret':
            break
        cur += length
        n += 1

idapro.close_database(False)
print('\n[probe] done')
