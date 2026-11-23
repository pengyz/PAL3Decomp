#!/usr/bin/env python3
"""[探针 2026-11-18] Actor 四同体 dtor 的归属裁决——搜 .rdata 引用四地址的
vtable 位置 + 各 vtable 的类名(ctor 写表链/命名)。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_actor_sdtor_vtables_20261118.py
"""
import sys

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)

import idc
import ida_bytes
import ida_name
import idautils
import ida_segment

TARGETS = [0x004c9470, 0x004cb280, 0x004d37a0, 0x004d4ca0]

# 对每个目标地址, 找所有数据 xref (vtable 槽引用)
for t in TARGETS:
    print('\n=== 0x%08x (%s) ===' % (t, ida_name.get_name(t)))
    refs = []
    for xr in idautils.DataRefsTo(t):
        # xref 处往前回溯找 vtable 头: 连续函数指针区的起点
        refs.append(xr)
    for xr in refs:
        # 读 vtable 上下文: xref 前后各 8 槽
        start = xr - 4 * 8
        names = []
        for i in range(-8, 12):
            p = ida_bytes.get_dword(start + i * 4)
            if 0x00401000 <= p < 0x00570000 and ida_bytes.is_code(ida_bytes.get_flags(p)):
                names.append((i, ida_name.get_name(p)[:36]))
            else:
                names.append((i, None))
        # 打印 xref 位置 + 前后槽名
        seg = ida_segment.getseg(xr)
        print('  ref@0x%08x seg=%s' % (xr, ida_segment.get_segm_name(seg) if seg else '?'))
        for i, nm in names:
            mark = ' <<<' if (start + i * 4) == xr else ''
            if nm or mark:
                print('      %+3d  %s%s' % (i, nm or '.', mark))

idapro.close_database(False)
print('\n[probe] done')
