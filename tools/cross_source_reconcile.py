#!/usr/bin/env python3
"""[T76] 四源交叉对照（annotation vs IDB vs decomp vs 生成码）。

只做**对照层**（不重复造轮——单源审计各有专责工具）：同一实体（成员/函数/
全局）在四源的声明对照 + 不一致清单（带证据等级）。

用法（库）：reconcile_member(ann, idb, decomp, gen) -> {'verdict': ..., 'sources_diff': [...]}
verdict：consistent / inconsistent / missing（缺源）。
"""
import argparse
import json
import os

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))


def reconcile_member(ann, idb, decomp, gen):
    """四源对照（缺任一源 ⇒ missing；全同 ⇒ consistent；否则 inconsistent）。"""
    srcs = {'annotation': ann, 'IDB': idb, 'decomp': decomp, 'generated': gen}
    present = {k: v for k, v in srcs.items() if v is not None}
    if len(present) < 4:
        return {'verdict': 'missing', 'sources_diff': sorted(set(srcs) - set(present))}
    types = {k: str((v or {}).get('type')) for k, v in present.items()}
    uniq = set(types.values())
    if len(uniq) == 1:
        return {'verdict': 'consistent', 'sources_diff': []}
    base = types['annotation']
    diff = sorted(k for k, t in types.items() if t != base)
    return {'verdict': 'inconsistent', 'sources_diff': diff, 'types': types}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--class', dest='cls')
    args = ap.parse_args()
    if not args.cls:
        ap.error('--class required')
    p = os.path.join(ROOT, 'data', 'annotations', 'structs', '%s.json' % args.cls)
    d = json.load(open(p))
    # 对照层最小实现：annotation 声明逐成员打印（IDB/decomp/生成码三源待接）
    for k, v in list((d.get('known_members') or {}).items())[:12]:
        print('%s +0x%s: %s %s' % (args.cls, k, v.get('name'), v.get('type')))
    print('[T76] IDB/decomp/生成码三源对接待续（对照层 API 已立——reconcile_member）')


if __name__ == '__main__':
    main()
