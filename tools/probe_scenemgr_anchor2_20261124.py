#!/usr/bin/env python3
"""[探针 2026-11-24 #2] SceneMgr 锚边界二轮: 指针寄存器来源追踪。

一轮结论:
  - 无 CRT init / 无绝对引用 0xC12470 → +0xE0E0 全部经指针寄存器访问
  - 本轮: A) 22 个 mov ecx,0xC04390 接收点后 16 条指令窗口(内联成员访问 disp)
          B) 32 个 +0xE0E0 宿主函数: 函数头 40 条指令(指针寄存器来源) +
             体/调用者中 0xC04390 引用判定
用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_scenemgr_anchor2_20261124.py
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

G_SCENEMGR = 0x00C04390

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


ts = None
for seg_ea in idautils.Segments():
    s = ida_segment.getseg(seg_ea)
    if ida_segment.get_segm_name(s) == '.text':
        ts = s
blob = ida_bytes.get_bytes(ts.start_ea, ts.end_ea - ts.start_ea) or b''
base = ts.start_ea

# ---------------------------------------------------------------- A
say('========== A: 接收点后内联访问窗口 ==========')
recv_sites = []
pat = struct.pack('<I', G_SCENEMGR)
i = blob.find(b'\xb9' + pat)
while i >= 0:
    recv_sites.append(base + i)
    i = blob.find(b'\xb9' + pat, i + 1)

inline_disps = collections.Counter()
for ea in recv_sites:
    f = ida_funcs.get_func(ea)
    fs = f.start_ea if f else ea
    fe = f.end_ea if f else ea + 0x400
    say('\n-- %s+0x%X --' % (func_name(fs), ea - fs))
    cur = ea
    for k in range(16):
        cur = idc.next_head(cur, fe)
        if cur == idc.BADADDR:
            break
        text = (idc.generate_disasm_line(cur, 0) or '').strip()
        say('   +%#04x %s' % (cur - fs, text))
        m = re.search(r'\[ecx\+([0-9A-Fa-f]+)h?\]', text)
        if m:
            inline_disps[int(m.group(1).rstrip('h'), 16)] += 1
        if text.startswith('call') or text.startswith('jmp'):
            break

say('\n接收点后 [ecx+disp] 汇总: %s' % [
    '0x%X(x%d)' % (d, c) for d, c in sorted(inline_disps.items())])

# ---------------------------------------------------------------- B
say('\n========== B: +0xE0E0 宿主函数指针来源追踪 ==========')
pat_e0 = struct.pack('<I', 0xE0E0)
hosts = []
seen = set()
i = blob.find(pat_e0)
while i >= 0:
    ea = base + i
    head = ida_bytes.get_item_head(ea)
    if head and ida_bytes.is_code(ida_bytes.get_flags(head)) and head not in seen:
        seen.add(head)
        f = ida_funcs.get_func(head)
        if f:
            hosts.append(f.start_ea)
    i = blob.find(pat_e0, i + 1)

say('宿主函数: %d 个' % len(set(hosts)))
for fs in sorted(set(hosts)):
    fsr, fe = func_range(fs)
    # 1) 函数体内是否引用 0xC04390 / 0xC11758(UIManager) / 0xC0A360(stru_C0A360)
    #    / 0xC043A0(g_RoleSlotBuf) / 0xC12B48(g_RoleSystemInstance)
    anchors = collections.Counter()
    cur = fsr
    n = 0
    while cur < fe and n < 4000:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        text = idc.generate_disasm_line(cur, 0) or ''
        for a, nm in [(0xC04390, 'SceneMgr'), (0xC11758, 'UIManager'),
                      (0xC0A360, 'stru_C0A360'), (0xC043A0, 'RoleSlotBuf'),
                      (0xC12B48, 'RoleSysInst'), (0xC059A0, 'C059A0')]:
            if ('%X' % a) in text.upper():
                anchors[nm] += 1
        cur = idc.next_head(cur, fe)
        n += 1
    # 2) 函数头 24 条指令(指针寄存器如何来)
    head_lines = []
    cur = fsr
    for k in range(24):
        if cur >= fe or not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        text = (idc.generate_disasm_line(cur, 0) or '').strip()
        head_lines.append('+%#04x %s' % (cur - fsr, text))
        cur = idc.next_head(cur, fe)
    # 3) 调用者中 0xC04390 引用
    callers = []
    for xr in idautils.XrefsTo(fs, 0):
        callers.append(xr.frm)
    caller_hit = 0
    for c in callers[:24]:
        cf = ida_funcs.get_func(c)
        if not cf:
            continue
        cfs, cfe = func_range(cf.start_ea)
        cur = cfs
        while cur < cfe:
            if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
                break
            text = idc.generate_disasm_line(cur, 0) or ''
            if 'C04390' in text:
                caller_hit += 1
                break
            cur = idc.next_head(cur, cfe)
    say('\n== %s (0x%X) e0e0命中 +0xE0E0锚:%s 调用者%d个(含C04390:%d)' % (
        func_name(fs), fs, dict(anchors), len(callers), caller_hit))
    for hl in head_lines:
        say('   ' + hl)

with open('/home/peng/workspace/PAL3Decomp/pipeline/ida/probe_scenemgr_anchor2_out.txt',
          'w', encoding='utf-8') as f:
    f.write('\n'.join(OUT))
print('\n[probe2] saved -> probe_scenemgr_anchor2_out.txt')
idapro.close_database(False)
