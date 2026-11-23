#!/usr/bin/env python3
"""[探针 2026-11-24 #8] ScriptSystemData 真实尾界仲裁。

矛盾: g_ScriptSystemData@0xD8B318 binary_size=0x3150(尾 0xD8E468);
     但 CRT 对象 Iostream_init@0xD8C338(=struct+0xF20) 落在声称域内
     —— 链接器不可能把独立对象放进真类内部 ⇒ 真尾界 ≤ 0xD8C338 或结构非真。
判据:
  D1 CRT init 表引用 0xD8B318(动态初始化=真类证据)与 0xD8C338(独立对象证据)
  D2 mov ecx,0xD8B318 接收点 → this-form 成员访问 disp 全集(真成员域上界)
  D3 XrefsTo(0xD8C338) 全景(Iostream_init 的 CRT 管理证据)
  D4 mov ecx,0xD8E468(g_pLoadBuffer)/邻接锚接收点(下一对象起点)
用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_scriptsystemdata_20261124.py
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
import ida_name
import idautils

BASE = 0x00D8B318
OUT = []


def say(s):
    print(s)
    OUT.append(s)


def func_range(ea):
    f = ida_funcs.get_func(ea)
    return (f.start_ea, f.end_ea) if f else (ea, ea + 0x400)


def func_name(ea):
    n = ida_name.get_name(ea)
    return (n if n else 'sub_%X' % ea)[:50]


ts = None
for seg_ea in idautils.Segments():
    s = ida_segment.getseg(seg_ea) if False else None
import ida_segment
for seg_ea in idautils.Segments():
    sg = ida_segment.getseg(seg_ea)
    if ida_segment.get_segm_name(sg) == '.text':
        ts = sg
blob = ida_bytes.get_bytes(ts.start_ea, ts.end_ea - ts.start_ea) or b''
base = ts.start_ea

# ---------------- D1: 立即数引用普查(接收点/取址/初始化) ----------------
say('=== D1: .text 内 0xD8B318/0xD8C338 立即数引用全景 ===')


def imm_refs(addr):
    pat = struct.pack('<I', addr)
    hits = []
    i = blob.find(pat)
    while i >= 0:
        head = ida_bytes.get_item_head(base + i)
        if head and ida_bytes.is_code(ida_bytes.get_flags(head)):
            hits.append(head)
        i = blob.find(pat, i + 1)
    return hits

for probe_addr, label in ((BASE, 'g_ScriptSystemData'), (0xD8C338, 'Iostream_init')):
    refs = imm_refs(probe_addr)
    forms = collections.Counter()
    rows = []
    for h in refs[:40]:
        f = ida_funcs.get_func(h)
        fs = f.start_ea if f else h
        t = (idc.generate_disasm_line(h, 0) or '').strip()
        key = re.sub(r'0x?[0-9A-Fa-f]+h?\b', '#', t)
        forms[key] += 1
        rows.append((func_name(fs), h - fs, t))
    say('%s(0x%X): %d 处, 形态:' % (label, probe_addr, len(refs)))
    for k, c in forms.most_common(8):
        say('   x%d %s' % (c, k))
    for fn, off, t in rows[:12]:
        say('     %s+0x%X: %s' % (fn, off, t))
    say('')

# ---------------- D2: mov ecx, BASE 接收点的 this-form disp ----------------
say('=== D2: mov ecx,0xD8B318 接收点 → this-form 成员 disp ===')
recv = imm_refs(BASE)
recv = [h for h in recv if re.search(r'mov\s+ecx,.*', (idc.generate_disasm_line(h, 0) or ''))]
say('mov ecx 接收点: %d' % len(recv))
disps = collections.Counter()
for h in recv:
    f = ida_funcs.get_func(h)
    fs = f.start_ea if f else h
    fe = f.end_ea if f else h + 0x300
    cur = h
    for i in range(25):
        cur = idc.next_head(cur, fe)
        if cur == idc.BADADDR:
            break
        t = (idc.generate_disasm_line(cur, 0) or '').strip()
        if t.startswith('call') or t.startswith('jmp'):
            break
        for m in re.finditer(r'\[ecx\+([0-9A-Fa-f]+)h?\]', t):
            disps[int(m.group(1).rstrip('h'), 16)] += 1
        if re.match(r'mov\s+ecx\s*,', t) and 'D8B318' not in t:
            break
say('this-form disp: %s' % ['0x%X(x%d)' % (d, c) for d, c in sorted(disps.items())])

# ---------------- D3: XrefsTo Iostream_init ----------------
say('\n=== D3: XrefsTo(0xD8C338) ===')
n = 0
for xr in idautils.XrefsTo(0xD8C338, 0):
    f = ida_funcs.get_func(xr.frm)
    fs = f.start_ea if f else xr.frm
    say('  %s+0x%X: %s' % (func_name(fs), xr.frm - fs,
                           (idc.generate_disasm_line(xr.frm, 0) or '').strip()))
    n += 1
say('xrefs: %d' % n)

# ---------------- D4: CRT init 表归属 ----------------
say('\n=== D4: CRT init 表条目归属 ===')
rdata = None
for seg_ea in idautils.Segments():
    sg = ida_segment.getseg(seg_ea)
    if ida_segment.get_segm_name(sg) == '.rdata':
        rdata = sg
if rdata:
    rblob = ida_bytes.get_bytes(rdata.start_ea, rdata.end_ea - rdata.start_ea) or b''
    rbase = rdata.start_ea
    run = []
    found = []
    for off in range(0, len(rblob) - 4, 4):
        v = struct.unpack('<I', rblob[off:off + 4])[0]
        f = ida_funcs.get_func(v) if v else None
        if f and f.start_ea == v and 0x401000 <= v < 0x5C0000:
            run.append((rbase + off, v))
        else:
            if len(run) >= 5:
                for tea, tv in run:
                    fs, fe = func_range(tv)
                    cur = fs
                    hit_a = hit_i = 0
                    while cur < fe:
                        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
                            break
                        t = (idc.generate_disasm_line(cur, 0) or '')
                        if 'D8B318' in t: hit_a += 1
                        if 'D8C338' in t: hit_i += 1
                        cur = idc.next_head(cur, fe)
                    if hit_a or hit_i:
                        found.append((tea, tv, hit_a, hit_i))
            run = []
    for tea, tv, ha, hi in found:
        say('  init[0x%X] -> %s (0x%X): D8B318x%d D8C338x%d' % (
            tea, func_name(tv), tv, ha, hi))
        if ha:
            fs, fe = func_range(tv)
            cur = fs
            while cur < fe:
                if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
                    break
                t = (idc.generate_disasm_line(cur, 0) or '').strip()
                if 'D8B318' in t or 'stosd' in t:
                    say('    +%#x %s' % (cur - fs, t))
                cur = idc.next_head(cur, fe)
say('\n[probe8] done')
with open('/home/peng/workspace/PAL3Decomp/pipeline/ida/probe_scriptsystemdata_out.txt',
          'w', encoding='utf-8') as f:
    f.write('\n'.join(OUT))
idapro.close_database(False)
