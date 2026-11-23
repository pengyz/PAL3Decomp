#!/usr/bin/env python3
"""[探针 2026-11-24 #7] CEffMgr 成员普查——43312B 真锚的语义成员填充。

方法集 = CEffMgr.json methods(34, 含新迁入 Create/RenderAll/RenderUpdate/SceneMgrUpdate)
+ g_pSceneManager 接收点直呼目标。
寄存器追踪: this 集合={ecx}起步; mov eX,eY(this集)传播; call 清易失寄存器;
[reg+disp] 且 reg∈this集 → 成员访问记录。
输出: 每 max disp + 全类 disp 分布 → known_members 填充判据。
用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_ceffmgr_members_20261124.py
"""
import sys
import re
import json
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

ceff = json.load(open('/home/peng/workspace/PAL3Decomp/data/annotations/structs/CEffMgr.json'))
methods = {}
for k, v in ceff['methods'].items():
    methods[int(k, 16)] = v.get('name', '?')
say('CEffMgr methods: %d' % len(methods))

VOLATILE = {'eax', 'ecx', 'edx'}
REG8 = {'al': 'eax', 'bl': 'ebx', 'cl': 'ecx', 'dl': 'edx',
        'ah': 'eax', 'bh': 'ebx', 'ch': 'ecx', 'dh': 'edx'}

per_method = {}
all_disps = collections.Counter()

for maddr, mname in sorted(methods.items()):
    fs, fe = func_range(maddr)
    this_regs = {'ecx'}
    got = []
    cur = fs
    n = 0
    while cur < fe and n < 8000:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        text = idc.generate_disasm_line(cur, 0) or ''
        parts = text.split(None, 1)
        mnem = parts[0].lower() if parts else ''
        rest = parts[1] if len(parts) > 1 else ''

        if mnem in ('call',):
            this_regs -= VOLATILE
        elif mnem == 'mov':
            mm = re.match(r'\s*([a-z]{2,3})\s*,\s*(.+)$', rest)
            if mm:
                dst, src = mm.group(1), mm.group(2).strip()
                dst_n = REG8.get(dst, dst)
                src_n = REG8.get(src, src.split(',')[0].strip())
                if src_n in this_regs or ('this' in text and dst_n == 'ecx'):
                    this_regs.add(dst_n)
                elif dst_n in this_regs:
                    # mov eX, imm 或非 this 源 → this 副本被覆盖
                    if not re.match(r'[a-z]{2,3}$', src_n) or src_n not in this_regs:
                        this_regs.discard(dst_n)
        elif mnem in ('lea',):
            mm = re.match(r'\s*([a-z]{2,3})\s*,\s*(.+)$', rest)
            if mm:
                dst = REG8.get(mm.group(1), mm.group(1))
                src = mm.group(2)
                # lea eX, [eY+disp] 且 eY∈this → eX = this+disp 派生指针(不再算 this 本体)
                m = re.match(r'\[([a-z]{2,3})', src)
                if m and REG8.get(m.group(1), m.group(1)) in this_regs:
                    this_regs.discard(dst)
                elif 'this' in text:
                    pass
        elif mnem in ('jmp', 'ret', 'retn'):
            break

        # 成员访问: [reg+disp] / [reg]
        for m in re.finditer(r'\[([a-z]{2,3})\+([0-9A-Fa-f]+)h?\]', rest):
            r = REG8.get(m.group(1), m.group(1))
            if r in this_regs:
                d = int(m.group(2).rstrip('h'), 16)
                got.append((d, cur - fs, text.strip()))
        m0 = re.match(r'.*\[([a-z]{2,3})\]', rest)
        if m0:
            r = REG8.get(m0.group(1), m0.group(1))
            if r in this_regs:
                got.append((0, cur - fs, text.strip()))

        cur = idc.next_head(cur, fe)
        n += 1

    if got:
        per_method[maddr] = (mname, got)
        for d, off, tx in got:
            all_disps[d] += 1

say('有成员访问的方法: %d / %d' % (len(per_method), len(methods)))
say('\nTOP-15 max disp:')
rows = sorted(((max(g[0] for g in got), a) for a, (nm, got) in per_method.items()))
for mx, a in rows[-15:]:
    say('  %-30s 0x%X (%d 站)' % (per_method[a][0], mx, len(per_method[a][1])))
say('\n全类 disp >= 0x1000 清单:')
big = [d for d in sorted(all_disps) if d >= 0x1000]
for d in big:
    # 找 2 个样本
    samples = []
    for a, (nm, got) in per_method.items():
        for dd, off, tx in got:
            if dd == d and len(samples) < 2:
                samples.append('%s+%#x: %s' % (nm, off, tx[:60]))
    say('  0x%05X x%d  %s' % (d, all_disps[d], ' | '.join(samples)))
say('\ndisp 直方(4K 桶):')
import itertools
buckets = collections.Counter(d >> 12 for d in all_disps)
say('  ' + ', '.join('0x%Xk:%d' % (b << 12, c) for b, c in sorted(buckets.items())))
say('全类 max disp = 0x%X (binary_size=0xA930)' % (max(all_disps) if all_disps else 0))

with open('/home/peng/workspace/PAL3Decomp/pipeline/ida/probe_ceffmgr_members_out.txt',
          'w', encoding='utf-8') as f:
    f.write('\n'.join(OUT))
print('\n[probe7] saved')
idapro.close_database(False)
