#!/usr/bin/env python3
"""[方法归属收敛 2026-11-14 v2安全版] 按表归属(owner)收敛 methods 条目。

owner map: addr → 表归属类(各leaf走表槽值首占, 基表先占)。
- 叶methods条目 addr==基表值 → 删(继承实现=基所有)
- 叶methods条目 addr归属≠本类 → 迁移至owner(目标已有则删重)
v2铁律(数据污染20261114教训): 每类独立load/dump, 不跨迭代复用类级变量。
用法: python3 tools/converge_method_ownership_20261114.py [--apply]
"""
import json, glob, os, sys

S = 'data/annotations/structs/%s.json'
def norm(a):
    a = str(a)
    return '0x%08x' % int(a, 16) if a.lower().startswith('0x') else a

APPLY = '--apply' in sys.argv
classes = [os.path.basename(f)[:-5] for f in glob.glob(S % '*')]
ALL = sorted(classes)

# owner map: 基表(CEffObj)先占, 其余按字母序表声明首占
owner = {}
base = json.load(open(S % 'CEffObj', encoding='utf-8'))
for vt in (base.get('vtables') or []):
    for s in (vt.get('slots') or []):
        if s.get('addr'): owner.setdefault(norm(s['addr']), 'CEffObj')
for cls in ALL:
    if cls == 'CEffObj': continue
    d = json.load(open(S % cls, encoding='utf-8'))
    for vt in (d.get('vtables') or []):
        for s in (vt.get('slots') or []):
            if s.get('addr'): owner.setdefault(norm(s['addr']), cls)

moves, deletes = [], []
for cls in ALL:
    if cls == 'CEffObj': continue
    d = json.load(open(S % cls, encoding='utf-8'))  # ★每类独立load
    ms = d.get('methods', {})
    for a in list(ms.keys()):
        au = norm(a)
        ow = owner.get(au)
        if ow == 'CEffObj':
            deletes.append('%s %s' % (cls, ms[a].get('name')))
            ms.pop(a, None)
        elif ow and ow != cls:
            td = json.load(open(S % ow, encoding='utf-8'))
            tm = td.setdefault('methods', {})
            if au not in tm:
                tm[au] = ms.pop(a)
                moves.append('%s %s(%s) → %s' % (cls, tm[au].get('name'), au, ow))
            else:
                deletes.append('%s %s(重复)' % (cls, ms[a].get('name')))
                ms.pop(a, None)
            if APPLY: json.dump(td, open(S % ow, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    if APPLY: json.dump(d, open(S % cls, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

print('迁移 %d, 删除 %d' % (len(moves), len(deletes)))
for x in moves[:20]: print('  ', x)
