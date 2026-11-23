#!/usr/bin/env python3
"""[继承关系精确建模 20261115] 三证据源融合的递归多态判定器。

数据源(权威序):
  1. adjustor thunk(data/status/adjustor_thunks_20261115.json): (派生thunk, 基偏移N, 基实现)
     — thunk归簇: thunk地址簇↔派生类代码簇, target↔基实现
  2. ctor写表(true_vtable_map): 表addr→写点
  3. 注解bases(structs/*.json) — 辅助
  4. CTaskTpl_18实例 — 二进制已证多态族

输出: data/status/inheritance_graph_20261115.json
  {cls: {bases_binary: [(name, offset)], polymorphic: bool, evidence: [...], gaps: [...]}}
用法: python3 tools/build_inheritance_graph_20261115.py [--apply]
"""
import json, glob, os, struct, re, collections, bisect, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
S = os.path.join(ROOT, 'data/annotations/structs/%s.json')
APPLY = '--apply' in sys.argv

def norm(a):
    a = str(a)
    return '0x%08x' % int(a, 16) if a.lower().startswith('0x') else a

# ---- 二进制 ----
data = open(os.path.join(ROOT, 'original/PAL3.exe'), 'rb').read()
# .text: raw=0x1000 ↔ VA=0x401000 (VA = off + 0x400000, off = VA - 0x400000)
def va2off(va): return va - 0x400000
def rd32(va):
    off = va2off(va)
    return struct.unpack_from('<I', data, off)[0]
def read_va(va, n):
    off = va2off(va)
    return data[off:off+n]

reg = {}
for line in open(os.path.join(ROOT, 'data/status/pal3_registry.jsonl')):
    r = json.loads(line)
    reg[int(r['addr'], 16)] = r['name']
addrs = sorted(reg.keys())
def fname(va):
    i = bisect.bisect_right(addrs, va) - 1
    return (reg[addrs[i]], va - addrs[i]) if i >= 0 else ('?', 0)

# ---- 证据源1: adjustor thunks ----
thunks = json.load(open(os.path.join(ROOT, 'data/status/adjustor_thunks_20261115.json'), encoding='utf-8'))
# thunk→(sub偏移, 基实现target)

# ---- 证据源2: 写表(true_vtable_map + registrar_supplement区段补扫) ----
tvm = json.load(open(os.path.join(ROOT, 'data/status/true_vtable_map_20261114.json'), encoding='utf-8'))
evidenced_tables = set()
for r in tvm:
    try: evidenced_tables.add(int(r['table'], 16))
    except: pass
# [registrar补扫 20261115] 区段0x5704C8-0x570A78强证据表(裁决书F.2: C7-only漏寄存器中介写)
_supp_path = os.path.join(ROOT, 'data/status/registrar_supplement_20261115.json')
if os.path.exists(_supp_path):
    for _r in json.load(open(_supp_path, encoding='utf-8')):
        try: evidenced_tables.add(int(_r['table'], 16))
        except: pass

# ---- 证据源3: 注解 ----
classes = [os.path.basename(f)[:-5] for f in glob.glob(S % '*')]
ann = {c: json.load(open(S % c, encoding='utf-8')) for c in classes}

# ---- CTaskTpl 多态实证族 ----
CTASKTPL = {c for c in classes if c.startswith('CTaskTpl_')}

def binary_polymorphic(cls, seen=None):
    """递归: cls在二进制里是否多态(有自己的vtable或继承多态且被覆写/带thunk)。
"""
    if seen is None: seen = set()
    if cls in seen: return False, []
    seen.add(cls)
    ev = []
    d = ann.get(cls) or {}
    # 1) 注解vtables有写证据/裁决
    for vt in (d.get('vtables') or []):
        try:
            a = int(vt.get('addr') or '0', 16)
        except: continue
        if a in evidenced_tables:
            ev.append('write_evidence@0x%08X' % a)
    if d.get('_adjudicated_tables'):
        ev.append('adjudicated_tables')
    # 2) CTaskTpl族
    if cls in CTASKTPL:
        ev.append('ctasktpl_poly_family')
    # 2b) thunk target ∈ 本类methods簇 — 权威源#1接入(裁决书C.4: thunk加载后未用)
    _ms = d.get('methods') or {}
    _ms_addrs = set()
    for _k in _ms:
        try: _ms_addrs.add(int(_k, 16))
        except: pass
    for _t in thunks:
        try: _tt = int(_t['target'], 16)
        except: continue
        if _tt in _ms_addrs:
            ev.append('thunk_target_in_methods@%s sub=%d' % (_t['thunk'], _t['sub']))
    # 3) 递归祖先
    any_base_poly = False
    for b in (d.get('bases') or []):
        bn = b.get('name') if isinstance(b, dict) else b
        if bn and bn in ann:
            bp, ev2 = binary_polymorphic(bn, seen)
            if bp:
                any_base_poly = True
                ev.extend('base:%s:%s' % (bn, x) for x in ev2[:2])
    poly = bool(ev) or any_base_poly
    return poly, ev

# ---- 融合图构建 ----
graph = {}
for cls in classes:
    d = ann.get(cls) or {}
    bases_ann = [(b.get('name') if isinstance(b, dict) else b, b.get('offset') if isinstance(b, dict) else None)
                 for b in (d.get('bases') or [])]
    poly, ev = binary_polymorphic(cls)
    gaps = []
    # 缺口: 有methods虚槽名或头virtual痕迹但无任何多态证据
    # 缺口: 有methods虚槽名或头virtual痕迹但无任何多态证据
    if not poly and not d.get('vtables') and (d.get('methods') or {}):
        gaps.append('no_bases_no_evidence')
    graph[cls] = {
        'bases_ann': bases_ann,
        'polymorphic': poly,
        'evidence': ev,
        'gaps': gaps,
        'n_vtables': len(d.get('vtables') or []),
    }

# ---- thunk交叉验证 ----
out = {'classes': graph, 'thunks': thunks}
json.dump(out, open(os.path.join(ROOT, 'data/status/inheritance_graph_20261115.json'), 'w'),
          ensure_ascii=False, indent=1)
n_poly = sum(1 for g in graph.values() if g['polymorphic'])
print('类: %d | 多态: %d | 非多态: %d | gaps: %d' % (
    len(graph), n_poly, len(graph)-n_poly, sum(1 for g in graph.values() if g['gaps'])))
print('-> data/status/inheritance_graph_20261115.json')
