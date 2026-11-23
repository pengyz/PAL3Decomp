#!/usr/bin/env python3
"""[探针 2026-11-24 #6] g_pSceneManager ↔ CEffMgr 链接封口。

五轮已证: InitGame push 0xA930 + operator new = CEffMgr.binary_size。
本轮: D1 InitGame +0x276..+0x2D6 严格线性流(定 ctor 调用地址)
      D2 g_pSceneManager 11 调用目标地址 → 对照 CEffMgr 方法表/重名考古
用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_scenemgr_ceffmgr_link_20261124.py
"""
import sys
import re
import struct
import json

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

G_P_SCENEMGR = 0x00BFDA78
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


# CEffMgr 方法表
ceff = json.load(open('/home/peng/workspace/PAL3Decomp/data/annotations/structs/CEffMgr.json'))
ceff_methods = {}
for k, v in ceff.get('methods', {}).items():
    if isinstance(v, dict):
        ceff_methods[int(k, 16)] = (v.get('name'), ','.join(v.get('flags') or []))
    else:
        ceff_methods[int(k, 16)] = (str(v), '')
known = {v[0]: k for k, v in ceff_methods.items()}
say('CEffMgr 方法: %d (ctor=0x%X)' % (len(ceff_methods), known.get('CEffMgr', 0)))

# ---------------------------------------------------------------- D1
say('\n=== D1: InitGame +0x270..+0x2E0 线性流 ===')
for ea in idautils.Functions():
    if ida_name.get_name(ea) == 'InitGame':
        fs = ea
        break
fe = func_range(fs)[1]
cur = fs + 0x270
while cur < fs + 0x2E0:
    if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
        cur += 1
        continue
    text = (idc.generate_disasm_line(cur, 0) or '').strip()
    mark = ''
    m = re.match(r'call\s+([0-9A-Fa-f]+)', text)
    if m:
        tgt = int(m.group(1), 16)
        info = ceff_methods.get(tgt)
        mark = '   <<< CEffMgr.%s %s' % (info[0], info[1]) if info else \
               '   <<< %s' % func_name(tgt)
    if 'g_pSceneManager' in text:
        mark += '   <<< 工厂赋值'
    say('  +%#05x %s%s' % (cur - fs, text, mark))
    cur = idc.next_head(cur, fs + 0x2E0)

# ---------------------------------------------------------------- D2
say('\n=== D2: g_pSceneManager 调用目标对照 ===')
ts = None
for seg_ea in idautils.Segments():
    s = ida_segment.getseg(seg_ea)
    if ida_segment.get_segm_name(s) == '.text':
        ts = s
blob = ida_bytes.get_bytes(ts.start_ea, ts.end_ea - ts.start_ea) or b''
base = ts.start_ea
pat = b'\x8b\x0d' + struct.pack('<I', G_P_SCENEMGR)
i = blob.find(pat)
hits = []
while i >= 0:
    hits.append(base + i)
    i = blob.find(pat, i + 1)
for ea in hits:
    cur = idc.next_head(ea, ea + 32)
    text = (idc.generate_disasm_line(cur, 0) or '').strip()
    m = re.match(r'call\s+([0-9A-Fa-f]+)', text)
    f = ida_funcs.get_func(ea)
    fs2 = f.start_ea if f else ea
    if m:
        tgt = int(m.group(1), 16)
        info = ceff_methods.get(tgt)
        tag = ('CEffMgr.%s[%s]' % info) if info else 'NOT-IN-CEffMgr(%s)' % func_name(tgt)
        say('  %s+0x%X -> 0x%X %s' % (func_name(fs2), ea - fs2, tgt, tag))
    else:
        say('  %s+0x%X -> [%s]  (非直呼)' % (func_name(fs2), ea - fs2, text))

with open('/home/peng/workspace/PAL3Decomp/pipeline/ida/probe_scenemgr_ceffmgr_link_out.txt',
          'w', encoding='utf-8') as f:
    f.write('\n'.join(OUT))
print('\n[probe6] saved')
idapro.close_database(False)
