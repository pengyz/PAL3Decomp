#!/usr/bin/env python3
"""[探针 2026-11-18] .rdata vtable 区全貌——0x56f8f0..0x56fb60 逐槽读出函数名。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_vtable_region_56f9_20261118.py
"""
import sys

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)

import ida_bytes
import ida_name

BASE = 0x0056f8f0
for i in range(0, 0x270 // 4):
    addr = BASE + i * 4
    p = ida_bytes.get_dword(addr)
    if 0x00401000 <= p < 0x00570000:
        nm = ida_name.get_name(p)
        mark = ''
        if addr in (0x56f908, 0x56f95c, 0x56fac4, 0x56fb18):
            mark = '   <<< dtor写表目标'
        print('0x%08x  0x%08x  %-44s%s' % (addr, p, nm[:44], mark))
    else:
        print('0x%08x  0x%08x  (非函数指针)' % (addr, p))

idapro.close_database(False)
print('\n[probe] done')
