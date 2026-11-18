#!/usr/bin/env python3
"""[探针 2026-11-18] 四个 782B 同体 dtor 的物理字节验证——ICF 折叠(thunk) vs 独立副本。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_sdtor_bytes_20261118.py
"""
import sys

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)

import idc
import ida_bytes
import ida_funcs
import ida_name

for ea in (0x004c9470, 0x004cb280, 0x004d37a0, 0x004d4ca0):
    f = ida_funcs.get_func(ea)
    print('\n=== 0x%08x %s ===' % (ea, ida_name.get_name(ea)))
    print('  func range: 0x%08x..0x%08x size=%s' % (
        f.start_ea if f else 0, f.end_ea if f else 0,
        (f.end_ea - f.start_ea) if f else '?'))
    # 头 32 字节
    raw = ida_bytes.get_bytes(ea, 32) or b''
    print('  head bytes: %s' % raw[:16].hex(' '))
    # 反汇编头 6 条
    cur = ea
    for _ in range(6):
        print('    0x%08x  %s' % (cur, idc.generate_disasm_line(cur, 0)))
        n = idc.next_head(cur)
        if n <= cur: break
        cur = n

# 函数体逐字节比对: 0x4c9470 vs 0x4cb280 (各 0x2C0)
import hashlib
for a, b in ((0x004c9470, 0x004cb280), (0x004c9470, 0x004d37a0)):
    ba = ida_bytes.get_bytes(a, 0x2C0) or b''
    bb = ida_bytes.get_bytes(b, 0x2C0) or b''
    print('\n0x%08x vs 0x%08x: identical=%s' % (a, b, ba == bb))
    if ba != bb:
        for i in range(min(len(ba), len(bb))):
            if ba[i] != bb[i]:
                print('  first diff @+%#x: %02x vs %02x' % (i, ba[i], bb[i]))
                break

idapro.close_database(False)
print('\n[probe] done')
