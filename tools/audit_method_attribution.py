#!/usr/bin/env python3
"""筛出**归属无据**的函数：注解为类方法，但 decomp 里既不用 `this->`、签名也不是 `__thiscall`。

# 判据来源（项目规则）

> 不能仅凭 signature 的 `this` 修正函数归属 —— 必须有 decomp 成员访问证据
> （函数内 `this->member` 引用的成员在目标类中存在、且不在原类中存在）。

本工具是该判据的**第一道筛子**：`this->` 次数为 0 **且**签名非 `__thiscall`
⇒ 既没有"属于该类"的正面证据，也不像实例方法。**它只筛不定案。**

起因（2026-09-18）：`ScriptObj::ScriptObj` @0x00411CA0 的 decomp 是
`int __cdecl ScriptObj__ScriptObj(int nVal)`、`this->` 0 次，却被当成 `ScriptObj` 的 ctor；
顺着它追基偏移时才发现整条归属链不可信。全库筛出 **339 个**同类候选。

# 注意（不要误读）

候选里包含大量 **`__cdecl` 辅助/编译器生成函数**（`CopyConstruct_1C(void*, const void*)`、
`CompareModelName(char*, char*)`、`ParseLocaleData(char*, char*)` 等）。
把它们挂在某个类下**可能是有意分组**（静态成员/就近归类），也**可能是误归属** ——
**每个都要人看**，不能按本工具的输出批量改。

用法：
    python3 tools/audit_method_attribution.py            # 报告（默认按类聚合）
    python3 tools/audit_method_attribution.py --json o.json
"""
import argparse
import collections
import glob
import json
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN = os.path.join(ROOT, 'data', 'annotations', 'structs')
DECOMP = os.path.join(ROOT, 'asm', 'pal3', 'decomp')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--json')
    args = ap.parse_args()

    byaddr = {}
    for f in glob.glob(os.path.join(DECOMP, '*.json')):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except Exception:
            continue
        a = str(d.get('address') or '').lower()
        if a:
            byaddr[a] = (d.get('decompiled_c') or '', d.get('signature') or '',
                         os.path.basename(f))

    susp, tot, notfound = [], 0, 0
    for f in sorted(glob.glob(os.path.join(ANN, '*.json'))):
        d = json.load(open(f, encoding='utf-8'))
        cls = d.get('name') or os.path.basename(f)[:-5]
        for a, v in (d.get('methods') or {}).items():
            tot += 1
            try:
                va = int(a, 16)
            except ValueError:
                continue
            e = byaddr.get('0x%x' % va) or byaddr.get('0x%08x' % va)
            if not e:
                notfound += 1
                continue
            txt, sig, fn = e
            nthis = len(re.findall(r'\bthis->', txt))
            if nthis == 0 and '__thiscall' not in sig:
                susp.append({'class': cls, 'addr': a, 'name': v.get('name'),
                             'sig': sig, 'file': fn})

    print('注解方法 %d；匹配到 decomp %d；未匹配 %d' % (tot, tot - notfound, notfound))
    print()
    print('**归属无据候选**: %d 个（this-> 为 0 且非 __thiscall）' % len(susp))
    byc = collections.Counter(x['class'] for x in susp)
    print()
    print('按类聚合 top 20:')
    for c, n in byc.most_common(20):
        print('   %-28s %d' % (c[:28], n))
    print()
    print('样本（前 12）:')
    for x in susp[:12]:
        print('   %-22s %-12s %-24s %s' % (x['class'][:22], x['addr'],
                                           str(x['name'])[:24], x['sig'][:52]))
    if args.json:
        json.dump(susp, open(args.json, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
        print('\n结果 -> %s' % args.json)


if __name__ == '__main__':
    main()
