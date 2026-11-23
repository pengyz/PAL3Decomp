#!/usr/bin/env python3
"""[探针 2026-11-24 #4] SceneMgr 类存在性终审。

三~轮已证:
  - 22 个 thiscall 全是 Array 方法; 0xC0439C=Array 尾指针(独立命名 g_pSceneArrayEnd2)
  - m_nRoleCount@+0xE0E0 指针来自 UISceneUpdate 返回值 = 0xC21FE8+idx*BIG (场景池!)
  - 无 ctor / 无绝对寻址访问
本轮: D1 g_pSceneManager 符号真身 / D2 0xC21FE8 身份与数组拓扑 /
      D3 二进制 SceneMgr 字符串线索 / D4 0xC04390 16 字节原始内容(Array 布局验证)
用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_scenemgr_anchor4_20261124.py
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


# ---------------------------------------------------------------- D1
say('=== D1: g_pSceneManager 等符号真身 ===')
for want in ('g_pSceneManager', 'g_SceneMgr', 'g_pSceneArrayEnd2',
             'g_SceneArray', 'g_RoleSlotBuf'):
    found = []
    for seg_ea in idautils.Segments():
        s = ida_segment.getseg(seg_ea)
        ea = s.start_ea
        while ea < s.end_ea:
            nm = ida_name.get_name(ea)
            if nm == want:
                found.append((ea, nm))
                ea += max(4, ida_bytes.get_item_size(ea))
                continue
            ea += 4
    for ea, nm in found:
        v = ida_bytes.get_dword(ea)
        tgt_fn = ida_funcs.get_func(v)
        say('  %-22s @ 0x%08X = 0x%08X %s' % (
            nm, ea, v,
            ('-> func %s' % func_name(v)) if tgt_fn else '(data/ptr?)'))
    if not found:
        say('  %-22s : NOT FOUND' % want)

# g_pSceneManager 的 xrefs
say('\n--- g_pSceneManager xrefs ---')
for seg_ea in idautils.Segments():
    s = ida_segment.getseg(seg_ea)
    ea = s.start_ea
    while ea < s.end_ea:
        if ida_name.get_name(ea) == 'g_pSceneManager':
            for xr in idautils.XrefsTo(ea, 0):
                f = ida_funcs.get_func(xr.frm)
                fs = f.start_ea if f else xr.frm
                say('  %s+0x%X: %s' % (
                    func_name(fs), xr.frm - fs,
                    (idc.generate_disasm_line(xr.frm, 0) or '').strip()))
            ea = ea
            break
        ea += 4

# ---------------------------------------------------------------- D2
say('\n=== D2: 0xC21FE8 身份 ===')
nm = ida_name.get_name(0xC21FE8)
say('IDA name(0xC21FE8) = %s' % nm)
# 其后 0x78664 内的命名条目(数组元素拓扑)
ea = 0xC21FE8
cnt = 0
end = 0xC21FE8 + 0x78664
while ea < end and cnt < 25:
    n2 = ida_name.get_name(ea)
    if n2:
        say('  0x%08X %s (+%#x)' % (ea, n2[:50], ea - 0xC21FE8))
        cnt += 1
        sz = ida_bytes.get_item_size(ea)
        if sz > 4:
            ea += sz
            continue
    ea += 4
say('0xC21FE8..+0x78664 命名条目: %d' % cnt)

# stride 复核: idx*0x78664? 反汇编 lea 链复核(直接打印 UISceneUpdate 的除法变换)
# 123289*4 = 493156 = 0x78664
say('stride = 123289*4 = %d = 0x%X' % (123289 * 4, 123289 * 4))

# ---------------------------------------------------------------- D3
say('\n=== D3: 二进制 SceneMgr/SceneManager 字符串 ===')
ts = None
for seg_ea in idautils.Segments():
    s = ida_segment.getseg(seg_ea)
    if ida_segment.get_segm_name(s) == '.text':
        ts = s
for seg_ea in idautils.Segments():
    s = ida_segment.getseg(seg_ea)
    blob = ida_bytes.get_bytes(s.start_ea, s.end_ea - s.start_ea) or b''
    for kw in (b'SceneMgr', b'SceneManager', b'CSceneMgr', b'CSceneManager'):
        i = blob.find(kw)
        while i >= 0:
            ctx = blob[max(0, i - 24):i + 32]
            printable = ''.join(chr(c) if 32 <= c < 127 else '.'
                                for c in ctx)
            say('  [%s] 0x%08X: %s' % (
                ida_segment.get_segm_name(s), s.start_ea + i, printable))
            i = blob.find(kw, i + 1)

# ---------------------------------------------------------------- D4
say('\n=== D4: 0xC04390 16B 原始内容(Array 布局验证) ===')
raw = ida_bytes.get_bytes(0xC04390, 16) or b''
say('raw: %s' % raw.hex(' '))
say('dwords: %s' % ['0x%08X' % d for d in struct.unpack('<4I', raw)])
# Array 已知布局: 对照 g_RoleTeamArray@0xC04360
raw2 = ida_bytes.get_bytes(0xC04360, 16) or b''
say('g_RoleTeamArray@0xC04360 raw: %s' % ['0x%08X' % d for d in struct.unpack('<4I', raw2)])
raw3 = ida_bytes.get_bytes(0xC04380, 16) or b''
say('g_SceneArray@0xC04380   raw: %s' % ['0x%08X' % d for d in struct.unpack('<4I', raw3)])

with open('/home/peng/workspace/PAL3Decomp/pipeline/ida/probe_scenemgr_anchor4_out.txt',
          'w', encoding='utf-8') as f:
    f.write('\n'.join(OUT))
print('\n[probe4] saved')
idapro.close_database(False)
