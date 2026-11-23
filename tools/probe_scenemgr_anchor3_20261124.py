#!/usr/bin/env python3
"""[探针 2026-11-24 #3] UISceneUpdate 返回值溯源 + 0xE0E0 数组宿主定谳。

二轮结论:
  - 22 个 mov ecx,0xC04390 全是 Array 方法(Insert/Erase/Size/AddRoleEntry)
  - g_pSceneArrayEnd2@0xC0439C = 0xC04390+0xC → 0xC04390 运行时真身 = Array 头
  - +0xE0E0 访问指针全部来自 call UISceneUpdate 的返回值
本轮: D1 UISceneUpdate 体+返回值溯源 / D2 ret 指令处 eax 来源回溯 /
      D3 UISceneUpdate 调用者全景(全部把返回值当什么类型用)
用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_scenemgr_anchor3_20261124.py
"""
import sys
import re
import struct
import collections

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)

import idc
import ida_bytes
import ida_funcs
import ida_segment
import ida_name
import idautils

OUT = []


def say(s):
    print(s)
    OUT.append(s)


def func_range(ea):
    f = ida_funcs.get_func(ea)
    return (f.start_ea, f.end_ea) if f else (ea, ea + 0x800)


def func_name(ea):
    n = ida_name.get_name(ea)
    return (n if n else 'sub_%X' % ea)[:60]


# 找 UISceneUpdate
tgt = None
for ea in idautils.Functions():
    if 'UISceneUpdate' in (ida_name.get_name(ea) or ''):
        tgt = ea
        break
say('UISceneUpdate @ 0x%X' % tgt if tgt else 'UISceneUpdate NOT FOUND')

if tgt:
    fs, fe = func_range(tgt)
    say('=== D1: UISceneUpdate 体 (%d B) ===' % (fe - fs))
    cur = fs
    n = 0
    while cur < fe and n < 600:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        text = (idc.generate_disasm_line(cur, 0) or '').strip()
        mark = ''
        if text.startswith('retn') or 'g_' in text or 'mov     eax' in text:
            mark = '   <<<'
        say('  +%#05x %s%s' % (cur - fs, text, mark))
        cur = idc.next_head(cur, fe)
        n += 1

    # D3 调用者全景: 每个调用点后 4 条指令
    say('\n=== D3: UISceneUpdate 调用者返回值用法 ===')
    for xr in idautils.XrefsTo(tgt, 0):
        cf = ida_funcs.get_func(xr.frm)
        cfs = cf.start_ea if cf else xr.frm
        say('\n-- %s+0x%X --' % (func_name(cfs), xr.frm - cfs))
        cur = xr.frm
        for k in range(5):
            cur = idc.next_head(cur, func_range(cfs)[1])
            if cur == idc.BADADDR:
                break
            text = (idc.generate_disasm_line(cur, 0) or '').strip()
            say('   %s' % text)

# D2: 全局锚点候选 —— 哪些地址 X 有 X+0xE0E0 数组语义
# (count@X+0xE0E0, elem@X+0xE0E4, stride 0x2200)
say('\n=== D2: stride-0x2200 数组模式归属扫描 ===')
ts = None
for seg_ea in idautils.Segments():
    s = ida_segment.getseg(seg_ea)
    if ida_segment.get_segm_name(s) == '.text':
        ts = s
blob = ida_bytes.get_bytes(ts.start_ea, ts.start_ea and ts.end_ea - ts.start_ea) or b''
base = ts.start_ea
# mov reg, [X+0E0E0h] 形态里 X 是寄存器, 但 0x2200 步距 add 的宿主函数已知
# → 直接对每个 +0xE0E0 宿主, 找 [eax+0E35Ch]-0x278 = 0xE0E4 首元素 + 反推 X
# 改为: 扫 UISceneUpdate 返回值形态 (若上面 D1 已见 return X 即可)
for seg_ea in idautils.Segments():
    s = ida_segment.getseg(seg_ea)
    nm = ida_segment.get_segm_name(s)
    if nm in ('.data', '.data1', '.bss'):
        say('[seg] %s 0x%X-0x%X' % (nm, s.start_ea, s.end_ea))

with open('/home/peng/workspace/PAL3Decomp/pipeline/ida/probe_scenemgr_anchor3_out.txt',
          'w', encoding='utf-8') as f:
    f.write('\n'.join(OUT))
print('\n[probe3] saved')
idapro.close_database(False)
