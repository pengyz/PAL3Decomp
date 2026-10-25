#!/usr/bin/env python3
"""Actor fn-ptr 簇普查（一次性，2026-10-25）：逐站解析槽偏移 → UIPushButton 槽方法。"""
import json
import re
import collections
import os

cur = json.load(open('data/status/probe_census.json', encoding='utf-8'))
cu = {r['unit'].replace('\\', '/'): r for r in cur['s2']['results']}
src = open('pal3/src/Role/Actor.cpp', encoding='utf-8', errors='replace').read().splitlines()

d = json.load(open('data/annotations/structs/UIPushButton.json', encoding='utf-8'))
vt = (d.get('vtables') or [])[0]
slots = {}
for i, s in enumerate(vt.get('slots', [])):
    sa = int(str(s.get('addr', '0')), 16)
    slots[i * 4] = {'idx': i, 'addr': sa, 'from': s.get('from')}

fj = json.load(open('data/annotations/functions.json', encoding='utf-8'))
dd = d
glob_files = {}
for f in os.listdir('asm/pal3/decomp'):
    m = re.match(r'(.+)_([0-9a-f]{8})\.json$', f)
    if m:
        glob_files[int(m.group(2), 16)] = m.group(1)


def method_of(addr):
    e = fj.get('0x%08X' % addr)
    if e and e.get('name'):
        return '%s (%s)' % (e['name'], e.get('class') or '?')
    m = (dd.get('methods') or {}).get('0x%08X' % addr)
    if m:
        return '%s (structs)' % m.get('name')
    return glob_files.get(addr) or ('sub_%X' % addr)


errs = cu['pal3/src/Role/Actor.cpp']['errors']
out = []
for e in errs:
    if e['code'] != 'C2664':
        continue
    ln = e.get('line') or 0
    slot_off = None
    cast_ty = None
    for i in range(ln, max(0, ln - 14), -1):
        t = src[i - 1]
        m = re.search(r'\*\)\(\*\(u?_?DWORD \*\)\(?\*\(u?_?DWORD \*\)this \+ (\d+)\) \+ (\d+)\)', t)
        if m:
            slot_off = int(m.group(2), 0)
            cm = re.search(r'\(\*\(([^)]+)\)\(', t)
            cast_ty = cm.group(1) if cm else None
            break
        m2 = re.search(r'\(u?_?DWORD \*\)this \+ (\d+)\) \+ (\d+)\)', t)
        if m2:
            slot_off = int(m2.group(2), 0)
            cm = re.search(r'\(\*\(([^)]+)\)\(', t)
            cast_ty = cm.group(1) if cm else None
            break
    mi = slots.get(slot_off, {}).get('addr') if slot_off is not None else None
    out.append({'line': ln, 'slot_off': slot_off,
                'method': method_of(mi) if mi else None,
                'cast_ty': (cast_ty or '')[:70],
                'msg': e.get('msg', '')[:70]})

agg = collections.Counter(r['method'] or ('slot%s' % r['slot_off']) for r in out)
print('Actor.cpp C2664 总数:', len(out), '· 解析到槽方法:', sum(1 for r in out if r['method']))
print()
for k, c in agg.most_common(14):
    ex = next(r for r in out if (r['method'] or ('slot%s' % r['slot_off'])) == k)
    print('  %2d %-48s 例 L%s | %s' % (c, str(k)[:48], ex['line'], ex['msg'][:52]))

json.dump(out, open('data/status/_actor_vtbl_census_20261025.json', 'w', encoding='utf-8'),
          ensure_ascii=False, indent=1)
print()
print('saved -> data/status/_actor_vtbl_census_20261025.json')
