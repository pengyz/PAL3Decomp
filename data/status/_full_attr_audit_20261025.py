#!/usr/bin/env python3
"""全语料归属普查（一次性，2026-10-25·校准后放行）。

校准：6/6 已知真值复现（5 证实 + CreateSceneEntities 误归属）后才放行。
判决（筛子而非法官——零注解变异，SUSPECT=人工裁决优先级队列）：
  CORROBORATED   边界内且命中成员 ≥2
  SUSPECT-HIGH   越界比 >50% 且命中 <2（强疑似）
  SUSPECT-LOW    混合形态（待人工）
  NO-OFFSETS     覆盖但零偏移（工具盲区）
  NO-ASM         dump 未覆盖
输出：data/status/_full_attr_audit_20261025.json
"""
import json
import re
import collections
import os

PROC_RE = re.compile(r'^([A-Za-z_][\w]*)\s+proc\s+near')
lines = open('original/PAL3.exe.asm', encoding='utf-8', errors='replace').read().split('\n')

# 单遍 proc 索引
pidx = {}
cur = None
for i, l in enumerate(lines):
    m = PROC_RE.match(l)
    if m:
        cur = m.group(1).lower()
        if cur not in pidx:
            pidx[cur] = [i + 1, i + 1]
    elif cur and l.rstrip().endswith('endp'):
        pidx[cur][1] = i + 1
        cur = None
print('proc 索引:', len(pidx))

IMM = A_imm = None


def _imm(tok):
    tok = tok.strip()
    if not tok:
        return None
    if tok.lower().endswith('h'):
        try:
            return int(tok[:-1], 16)
        except ValueError:
            return None
    try:
        return int(tok)
    except ValueError:
        return None


def offsets_by_index(addr):
    """索引化 this_offsets（收集逻辑与原工具逐行一致）"""
    name = ('sub_%x' % addr).lower()
    span = pidx.get(name)
    if not span:
        return None
    s, e = span
    is_this = {'ecx': True}
    offs = {}
    for j in range(s, e + 1):
        code = lines[j - 1].split(';')[0].rstrip()
        if not code.strip():
            continue
        for m in re.finditer(r'\[(\w+)([+-])([0-9A-Fa-f]+h|\d+)\]', code):
            r = m.group(1)
            if is_this.get(r):
                v = _imm(m.group(3))
                if v is not None:
                    if m.group(2) == '-':
                        v = -v
                    if v not in offs:
                        offs[v] = j
        m = re.search(r'\bmov\s+(\w+),\s*(\w+)\s*$', code)
        if m:
            dst, src2 = m.group(1), m.group(2)
            is_this[dst] = bool(is_this.get(src2)) if src2 in is_this else False
            continue
        m = re.match(r'\s*mov\s+(\w+)\s*,', code)
        if m:
            is_this[m.group(1)] = False
            continue
        m = re.match(r'\s*lea\s+(\w+)\s*,\s*\[(\w+)(?:\+0)?\]\s*$', code)
        if m:
            is_this[m.group(1)] = bool(is_this.get(m.group(2)))
            continue
        m = re.match(r'\s*(?:lea|xor|sub|add|and|or|pop|imul|shl|shr|neg|not)\s+(\w+)', code)
        if m and m.group(1) != 'ecx':
            is_this[m.group(1)] = False
    regs = {r for r, v in is_this.items() if v}
    return offs, regs, (s, e)


sdir = 'data/annotations/structs'
verdicts = collections.defaultdict(list)
n = 0
for fn in sorted(os.listdir(sdir)):
    if not fn.endswith('.json'):
        continue
    cls = fn[:-5]
    d = json.load(open(os.path.join(sdir, fn), encoding='utf-8'))
    size = d.get('binary_size') or 0
    km = set(int(k) for k in (d.get('known_members') or {}))
    for a, m in (d.get('methods') or {}).items():
        if not isinstance(m, dict):
            continue
        n += 1
        try:
            addr = int(str(a), 16)
        except ValueError:
            continue
        r = offsets_by_index(addr)
        if r is None:
            verdicts['NO-ASM'].append({'cls': cls, 'addr': '0x%08X' % addr, 'name': m.get('name', '')})
            continue
        offs = sorted(r[0])
        if not offs:
            verdicts['NO-OFFSETS'].append({'cls': cls, 'addr': '0x%08X' % addr, 'name': m.get('name', '')})
            continue
        beyond = [o for o in offs if o >= size]
        hits = [o for o in offs if o in km]
        ratio = len(beyond) / len(offs)
        if ratio > 0.5 and len(hits) < 2:
            v = 'SUSPECT-HIGH'
        elif ratio > 0.3 or len(hits) < 2:
            v = 'SUSPECT-LOW'
        else:
            v = 'CORROBORATED'
        verdicts[v].append({'cls': cls, 'addr': '0x%08X' % addr, 'name': m.get('name', ''),
                            'offsets': len(offs), 'beyond': len(beyond), 'hits': len(hits),
                            'max_off': '0x%X' % offs[-1] if offs else '0'})

print('methods:', n)
summary = {k: len(v) for k, v in verdicts.items()}
print('判决分布:', summary)
json.dump({'generated': '2026-10-25', 'calibration': '6/6', 'summary': summary,
           'verdicts': dict(verdicts)},
          open('data/status/_full_attr_audit_20261025.json', 'w', encoding='utf-8'),
          ensure_ascii=False, indent=1)
print('saved -> data/status/_full_attr_audit_20261025.json')
print()
print('SUSPECT-HIGH Top 15:')
for r in verdicts['SUSPECT-HIGH'][:15]:
    print('  %-22s %-30s 越界 %d/%d 命中 %d 最大 %s' % (
        r['cls'], r['name'][:30], r['beyond'], r['offsets'], r['hits'], r['max_off']))
