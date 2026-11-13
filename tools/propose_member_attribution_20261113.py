#!/usr/bin/env python3
"""[归属族批量提案器 2026-11-13] free_functions 错归属成员函数全量取证。

判据(TOP5/ProcessScriptEvent 双实证的机制):
  (1)ecx-this: `int vN; // ecx` 未初始化即用 = thiscall this 被 cdecl 渲染吞掉
  (2)虚表派发 >=2: (**vN)(...) 形态 = 全局函数不可能访问 vtable
  (3)名字前缀 -> 类名先验(与 structs 目录实名单匹配)
  (4)泄漏栈参: `Type aX; // [esp+N] [ebp+M]` M>0 = thiscall 第2+参

产出: /tmp/member_attribution_proposal.json
用法: python3 tools/propose_member_attribution_20261113.py
"""
import json
import os
import re
import collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, 'pal3', 'src', 'free_functions.cpp')
STRUCTS_DIR = os.path.join(ROOT, 'data', 'annotations', 'structs')

known_classes = set()
for f in os.listdir(STRUCTS_DIR):
    if f.endswith('.json'):
        known_classes.add(f[:-5])

functions_ann = json.load(open(os.path.join(ROOT, 'data', 'annotations',
                                            'functions.json'), encoding='utf-8'))

addr_by_name = {}
for f in os.listdir(os.path.join(ROOT, 'asm', 'pal3', 'decomp')):
    if not f.endswith('.json'):
        continue
    base = f[:-5]
    m = re.match(r'^(.+)_([0-9a-f]{8})$', base)
    if m:
        addr_by_name.setdefault(m.group(1), m.group(2))


def class_candidates(fname):
    cands = []
    parts = fname.split('_')
    for i in range(1, len(parts)):
        c = '_'.join(parts[:i])
        if c in known_classes and c not in cands:
            cands.append(c)
    m = re.match(r'^([A-Z][a-z0-9]+(?:(?=[A-Z][a-z0-9])[A-Z][a-z0-9]+)*?)(?=[A-Z][a-z])', fname)
    if m and m.group(1) in known_classes and m.group(1) not in cands:
        cands.append(m.group(1))
    return cands


def main():
    ls = open(SRC, encoding='utf-8', errors='ignore').read().split('\n')
    funcs = []
    for i, l in enumerate(ls, 1):
        if re.match(r'^\s*(?:static\s+)?[\w: ]+\**\s*[\w:~]+\([^;]*\)\s*$', l) \
                and not l.strip().startswith('//'):
            m = re.search(r'([\w:~]+)\(', l)
            if m:
                funcs.append((i, m.group(1)))

    proposal = {}
    stats = collections.Counter()
    for idx, (i, fname) in enumerate(funcs):
        end = funcs[idx + 1][0] if idx + 1 < len(funcs) else len(ls)
        body = ls[i - 1:end]
        ecx = False
        for j, l in enumerate(body):
            m = re.search(r'^\s*(?:int|unsigned int) (\w+); // ecx', l)
            if m:
                var = m.group(1)
                for l2 in body[j + 1:]:
                    if re.search(r'\b%s\b' % var, l2) and '=' in l2 and '// ecx' not in l2:
                        ecx = True
                        break
                break
        vt = sum(1 for l in body if re.search(r'\(\*\*\w+\)\(', l))
        if not (ecx or vt >= 2):
            stats['skip_no_evidence'] += 1
            continue
        cands = class_candidates(fname)
        leaked = []
        for l in body:
            m = re.search(r'^\s*([\w ]+\**)\s*(\w+); // \[esp\+0x[0-9a-f]+\] \[ebp\+0x([0-9a-f]+)\]', l)
            if m and int(m.group(3), 16) > 0:
                leaked.append((m.group(1).strip(), m.group(2)))
        status = 'auto' if (ecx and len(cands) == 1) else 'review'
        in_ann = fname in functions_ann or \
                 any(isinstance(e, dict) and e.get('name') == fname
                     for e in functions_ann.values())
        proposal[fname] = {
            'line': i,
            'cls_candidates': cands,
            'vt_calls': vt,
            'ecx_this': ecx,
            'leaked_params': leaked,
            'status': status,
            'in_functions_json': in_ann,
            'addr': addr_by_name.get(fname),
        }
        stats[status] += 1

    json.dump(proposal, open('/tmp/member_attribution_proposal.json', 'w',
                             encoding='utf-8'), ensure_ascii=False, indent=1)
    print('函数总数:', len(funcs))
    print('提案分布:', dict(stats))
    print('产出: /tmp/member_attribution_proposal.json (%d 条)' % len(proposal))
    byc = collections.Counter()
    for p in proposal.values():
        c = p['cls_candidates'][0] if p['cls_candidates'] else '(no_class)'
        byc[c] += 1
    print('\n按类聚类:')
    for c, n in byc.most_common(18):
        print('  %-20s %d' % (c, n))


if __name__ == '__main__':
    main()
