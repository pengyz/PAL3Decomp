#!/usr/bin/env python3
"""[MoveWindow ABI 探针 2026-11-21] 0x445f20 RET弹栈真值 + UICaption 0x43a810 调用站 push 形。

病象: UICaption.cpp L28 / UIMap.cpp L45 `->MoveWindow()` 0参调用 C2660
(单元体渲染 j_UIWnd::MoveWindow(this+116), j_thunk 型=0参 → codegen 成员调用形丢显式参)。
ABI-RET 判据: RET 弹栈字节 = 显式栈参真相; thiscall 下 retn N → N/4 个显式栈参。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_movewindow_abi_20261121.py
"""
import sys

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)
print('[probe] db opened:', db)

import idc
import ida_funcs
import ida_name
import ida_xref


def disasm(ea, n):
    out = []
    for i in range(n):
        d = idc.GetDisasm(ea)
        if not d or ea == idc.BADADDR:
            break
        out.append('0x%X: %s' % (ea, d))
        nxt = idc.next_head(ea)
        if nxt <= ea:
            break
        ea = nxt
    return out


# 1) 0x445f20 本体全反汇编 (找 retn N / retn)
f = ida_funcs.get_func(0x445f20)
if f:
    print('func 0x445f20 range: 0x%X-0x%X name=%s' %
          (f.start_ea, f.end_ea, ida_name.get_name(f.start_ea)))
    end = f.end_ea
    print('== 0x445f20 头 8 条 ==')
    for l in disasm(0x445f20, 8):
        print(' ', l)
    print('== 尾 8 条 (retn 形) ==')
    import ida_ua
    tail = []
    ea = f.start_ea
    prev = []
    while ea < end and ea != idc.BADADDR:
        d = idc.GetDisasm(ea)
        prev.append('0x%X: %s' % (ea, d))
        if len(prev) > 10:
            prev.pop(0)
        nxt = idc.next_head(ea)
        if nxt <= ea:
            break
        ea = nxt
    for l in prev:
        print(' ', l)
else:
    print('0x445f20 无函数!')

# 2) UICaption Destroy2 0x43a810 调用站: 全函数找 call j_ 前 push/lea 形
print('== 0x43a810 (UICaption::Destroy2) 全函数 ==')
f2 = ida_funcs.get_func(0x43a810)
if f2:
    ea = f2.start_ea
    while ea < f2.end_ea and ea != idc.BADADDR:
        d = idc.GetDisasm(ea)
        print(' ', '0x%X: %s' % (ea, d))
        nxt = idc.next_head(ea)
        if nxt <= ea:
            break
        ea = nxt

# 3) j_ thunk 地址: xrefs 到 0x445f20
print('== xrefs to 0x445f20 ==')
for x in ida_xref.XrefsTo(0x445f20, 0):
    nm = ida_name.get_name(x.frm)
    print('  frm 0x%X (%s)' % (x.frm, nm))
