#!/usr/bin/env python3
"""检测 annotation source 里的「两说并存」（P0-9）。

## 为什么（2026-10-21 R56/R57 教训）

撤位面标时**追加新说**而非**删旧说** ⇒ 同一 source 含新旧两说 ⇒ 账面自相矛盾。
R56 reviewer 抓 9 处残文本 · R57 实扫仍剩 5 处（replace 悬挂片段）。

## 检测规则

同一 source 若同时含**新说标记**和**旧说标记** ⇒ 报 DUAL_CLAIM。

新旧说标记对（可扩展）：
  - 「值位面复用铁证」（旧）vs「撤位面标」（新）
  - 「ptr 对」（旧）vs「int 对」（新）
  - 「数组基=this+0x118」（旧）vs「折叠自洽」（新）

## 用法
    python3 tools/check_dual_claims.py               # 扫全部
    python3 tools/check_dual_claims.py --cls RoleSystem
"""
import argparse
import glob
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# (旧说标记, 新说标记) —— 同 source 同时含两者 ⇒ DUAL_CLAIM
PAIRS = [
    ('值位面复用铁证', '撤位面标'),
    ('值位面复用铁证', '值镜像'),
    ('ptr 对', 'int 对'),
    ('数组基=this+0x118', '折叠自洽'),
    ('数组基=+0x118', '折叠自洽'),
    ('50 元素', '16 元素'),
    ('100 元素', '10 元素'),
    ('SINGLE_FLOAT', 'SINGLE_ASSIGN'),
    ('SINGLE_FLOAT', 'MIXED'),
]


def scan(cls_filter=None):
    hits = []
    for fp in sorted(glob.glob(os.path.join(ROOT, 'data', 'annotations', 'structs', '*.json'))):
        try:
            with open(fp, encoding='utf-8') as fh:
                d = json.load(fh)
        except (OSError, ValueError):
            continue
        cls = str(d.get('name') or os.path.basename(fp)[:-5])
        if cls_filter and cls != cls_filter:
            continue
        for section in ('known_members', 'methods'):
            for key, m in (d.get(section) or {}).items():
                if not isinstance(m, dict):
                    continue
                src = str(m.get('source') or '')
                for old, new in PAIRS:
                    if old in src and new in src:
                        hits.append({'cls': cls, 'section': section, 'key': key,
                                     'name': m.get('name'), 'old_claim': old,
                                     'new_claim': new, 'source_len': len(src)})
    return hits


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--cls')
    ap.add_argument('--json', action='store_true')
    args = ap.parse_args()
    hits = scan(args.cls)
    if args.json:
        print(json.dumps({'dual_claims': hits, 'count': len(hits)}, ensure_ascii=False, indent=2))
    else:
        if not hits:
            print('✅ 无两说并存')
            return 0
        print(f'⚠️ 两说并存 {len(hits)} 处:')
        for h in hits:
            print(f"  {h['cls']}+{h['key']} {h['name']}: 旧「{h['old_claim']}」+ 新「{h['new_claim']}」")
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
