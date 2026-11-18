#!/usr/bin/env python3
"""[探针 2026-11-18] CCBStage 任务数组布局定谳——取 GetTask/GetTaskID/ForceDelTask/
StartSubTask/EndTask 原始汇编, 钉死 2632-stride 数组真实基址 disp。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_ccbstage_layout_20261118.py
"""
import sys

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)
print('[probe] db opened:', db)

import idc
import ida_ua
import ida_bytes

TARGETS = [
    ('GetProperCurAction', 0x0050ad30),
    ('StartSubTask',       0x004fce00),
    ('ForceDelTask',       0x004fca00),
    ('EndTask',            0x004fc9a0),
    ('DelTask',            0x004fc9c0),
    ('IsSubTaskFinished',  0x004fce70),
    ('GetTaskState',       0x004fcc10),
]

for name, ea in TARGETS:
    print('\n=== %s @ 0x%08x ===' % (name, ea))
    cur = ea
    end = ea + 0x400  # cap; functions are short except GetTask
    n = 0
    while cur < end and n < 120:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        insn = ida_ua.insn_t()
        length = ida_ua.decode_insn(insn, cur)
        if length == 0:
            break
        text = idc.generate_disasm_line(cur, 0)
        print('  0x%08x  %s' % (cur, text))
        if idc.print_insn_mnem(cur) == 'ret':
            break
        cur += length
        n += 1

idapro.close_database(False)
print('\n[probe] done')
