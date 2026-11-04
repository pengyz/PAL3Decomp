"""proof_matrix — 矩阵语料扫描器 + disposition 分类账（spec v2 §2·R5）。

scan_corpus_keys(ann_dir): 机械键扫描（机器触发——禁手维护清单）：
  struct.<key>/member.<key>/methods.<key>/functions.<key>/globals.<key>/skip.<key>
  → {key_path: 出现计数}。复核实测键域：struct 45/member 14/methods 33/
  functions 17/globals 15 种（真语料 data/annotations 为准）。
build_matrix(ann_dir, dispositions): 每个扫描键必须有 disposition 条目——
  missing 非空=不完备（schema 演进未入矩阵=红）。
disposition schema: {key_path: {transfer: 'op'|'dropped', reason: str,
  verify: 'direct'|'indirect:<效果>'|'comment'|'none'}}
"""
import glob
import json
import os


def _entries(raw):
    """json 载入体 → (key, value) 迭代（dict 形键=value；list 形用 address/name 键）。"""
    if isinstance(raw, dict):
        return list(raw.items())
    if isinstance(raw, list):
        out = []
        for i in raw:
            if isinstance(i, dict):
                out.append((i.get('address') or i.get('addr') or i.get('name') or '?', i))
        return out
    return []


def scan_corpus_keys(ann_dir):
    """机械键扫描 → {key_path: count}。"""
    counts = {}

    def bump(p):
        counts[p] = counts.get(p, 0) + 1

    def walk_obj(prefix, obj):
        if isinstance(obj, dict):
            for k in obj:
                bump('%s.%s' % (prefix, k))
        elif isinstance(obj, list):
            for item in obj:
                if isinstance(item, dict):
                    for k in item:
                        bump('%s.%s' % (prefix, k))

    fp = os.path.join(ann_dir, 'functions.json')
    if os.path.exists(fp):
        for _k, info in _entries(json.load(open(fp))):
            walk_obj('functions', info)
    for f in sorted(glob.glob(os.path.join(ann_dir, 'structs', '*.json'))):
        d = json.load(open(f))
        for k in (d if isinstance(d, dict) else {}):
            if k in ('known_members', 'methods'):
                continue
            bump('struct.%s' % k)
        km = (d or {}).get('known_members')
        items = km.values() if isinstance(km, dict) else (km or [])
        for m in items:
            walk_obj('member', m)
        for _addr, m in ((d or {}).get('methods') or {}).items():
            walk_obj('methods', m)
    gp = os.path.join(ann_dir, 'globals.json')
    if os.path.exists(gp):
        for _k, info in _entries(json.load(open(gp))):
            walk_obj('globals', info)
    for sf in ('skip_functions.json',):
        sp = os.path.join(ann_dir, sf)
        if os.path.exists(sp):
            raw = json.load(open(sp))
            if isinstance(raw, dict):
                for _k, info in raw.items():
                    walk_obj('skip', info if isinstance(info, dict) else {})
                    bump('skip.entry')
            elif isinstance(raw, list):
                for item in raw:
                    walk_obj('skip', item if isinstance(item, dict) else {})
                    bump('skip.entry')
    return counts


def build_matrix(ann_dir, dispositions):
    """矩阵构建：每扫描键须有 disposition——missing 非空=不完备（禁静默全过）。"""
    keys = scan_corpus_keys(ann_dir)
    dispositions = dispositions or {}
    missing = sorted(k for k in keys if k not in dispositions)
    matrix = {k: dispositions[k] for k in keys if k in dispositions}
    return {'matrix': matrix, 'missing': missing, 'scanned': len(keys)}
