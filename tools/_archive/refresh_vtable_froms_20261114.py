#!/usr/bin/env python3
"""[from刷新 2026-11-14 v2安全版] 全类vtable槽 from=当前ownership。

事故教训(数据污染20261114): v1脚本第二循环复用第一循环的stale d变量
⇒ ~100类文件被互相覆盖。v2铁律: 每类独立load/dump, 不跨迭代复用任何类级变量。
用法: python3 tools/refresh_vtable_froms_20261114.py [--apply]
"""
import json, glob, os

S = 'data/annotations/structs/%s.json'
def norm(a):
    a = str(a)
    return '0x%08x' % int(a, 16) if a.lower().startswith('0x') else a

import sys
APPLY = '--apply' in sys.argv

# owner map: 全部类表声明, 声明序首占
owner = {}
classes = [os.path.basename(f)[:-5] for f in glob.glob('data/annotations/structs/*.json')]
# [拓扑序 2026-11-15 复核裁决C节] 首占必须按继承深度(基类先占) —
# 字母序/glob序让派生类抢走基类槽(UIWnd 0x445E70被68张表引用的案例)
_depth = {}
def _dep(c, seen=None):
    if c in _depth: return _depth[c]
    if seen is None: seen = set()
    if c in seen: return 0
    seen.add(c)
    try:
        d = json.load(open(S % c, encoding='utf-8'))
        bs = d.get('bases') or []
    except Exception:
        bs = []
    if not bs:
        _depth[c] = 0
    else:
        _depth[c] = 1 + max((_dep(b.get('name') if isinstance(b, dict) else b, seen) for b in bs), default=0)
    return _depth[c]
for c in classes: _dep(c)
classes.sort(key=lambda c: (_depth.get(c, 0), c))
tables = {}
for cls in classes:
    d = json.load(open(S % cls, encoding='utf-8'))
    vts = d.get('vtables') or []
    if vts:
        tables[cls] = vts
        for vt in vts:
            for s in (vt.get('slots') or []):
                a = s.get('addr')
                if a: owner.setdefault(norm(a), cls)

n = 0
for cls, vts in tables.items():
    d = json.load(open(S % cls, encoding='utf-8'))  # ★每类独立load(v2铁律)
    vts = d.get('vtables') or []  # ★★重绑到新load对象(v2.1)
    # [裁决保护 2026-11-15] _adjudicated_tables 标记的表 = ctor写表二进制裁决过的真表,
    # 其 from 不被 owner 首占覆盖(首占模型的派生表同址引用会推翻基类自有裁决)
    _adj = {(t.get('addr') or '').lower() for t in (d.get('_adjudicated_tables') or [])}
    changed = False
    for vt in vts:
        if (vt.get('addr') or '').lower() in _adj:
            continue  # 裁决表: from已定谳, 不动
        for s in (vt.get('slots') or []):
            a = s.get('addr')
            if not a: continue
            ow = owner.get(norm(a))
            new_from = ow if (ow and ow != cls) else None
            if s.get('from') != new_from:
                s['from'] = new_from
                changed = True
                n += 1
    if changed and APPLY:
        json.dump(d, open(S % cls, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('from刷新 %d 处 (覆盖 %d 类)%s' % (n, len(tables), '' if APPLY else ' [dry-run]'))
