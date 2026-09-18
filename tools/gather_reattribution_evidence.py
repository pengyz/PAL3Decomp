#!/usr/bin/env python3
"""为"归属无据"的函数批量收集**成员访问证据**，产出可入批次的**重归属候选**。

# 判据（项目规则）

> 不能仅凭 signature 的 `this` 修正函数归属 —— 必须有 decomp 成员访问证据
> （函数内 `this->member` 引用的成员**在目标类中存在、且不在原类中存在**）。

本工具把这条判据自动化：对每个注解方法，取它 decomp 里出现的**成员样式标识符**
（`this->X`、`p_m_X`、以及 Hex-Rays 用成员名命名的局部变量），
查出这些标识符**各自属于哪个注解类**，然后：

* 若某个类 `T` 独占了这些成员的**大多数**，且 `T != 当前注解类` ⇒ **重归属候选** `(当前类 → T)`；
* 若证据分散/无 ⇒ **不定案**（宁可不做）。

# 名字（用户要求：重归属时同时复核函数名）

自动流程**不敢造名**。产出条目的 `new_name` 一律是**诚实占位名** `_todo_<addr>`
（`name_evidence` 写成"含义未定，归属证据充分、名字待人工复核"）。
真正有语义的名字要在**人工复核**后由 `--apply-names` 或手改批次给出 ——
依据 `docs/knowledge/pattern_annotation_batch_rename_no_evidence.md`
（一次无证据造名批量被整体撤销）。

用法：
    python3 tools/gather_reattribution_evidence.py                 # 报告
    python3 tools/gather_reattribution_evidence.py --write-batch   # 写 data/status/annotation_fix_batch.json
    python3 tools/gather_reattribution_evidence.py --min-votes 3   # 收紧独占票数阈值
"""
import argparse
import collections
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN = os.path.join(ROOT, 'data', 'annotations', 'structs')
DECOMP = os.path.join(ROOT, 'asm', 'pal3', 'decomp')
BATCH = os.path.join(ROOT, 'data', 'status', 'annotation_fix_batch.json')

_MEMNAME = re.compile(r'\b(m_[A-Za-z]\w*|p?m_p[A-Za-z]\w*)\b')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write-batch', action='store_true')
    ap.add_argument('--min-votes', type=int, default=3,
                    help='目标类至少要独占这么多成员才算定案（默认 3）')
    ap.add_argument('--max-batch', type=int, default=40, help='一次最多产出多少条')
    args = ap.parse_args()

    # 成员名 -> 拥有它的注解类集合
    owner = collections.defaultdict(set)
    anns = {}
    for f in sorted(glob.glob(os.path.join(ANN, '*.json'))):
        d = json.load(open(f, encoding='utf-8'))
        cls = d.get('name') or os.path.basename(f)[:-5]
        anns[cls] = d
        for _o, v in (d.get('known_members') or {}).items():
            if v.get('name'):
                owner[v['name']].add(cls)

    byaddr = {}
    for f in glob.glob(os.path.join(DECOMP, '*.json')):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except Exception:
            continue
        a = str(d.get('address') or '').lower()
        if a:
            byaddr[a] = (d.get('decompiled_c') or '', d.get('signature') or '',
                         d.get('local_vars') or [])

    cands = []
    for cls, d in anns.items():
        for a, v in (d.get('methods') or {}).items():
            try:
                va = int(a, 16)
            except ValueError:
                continue
            e = byaddr.get('0x%x' % va) or byaddr.get('0x%08x' % va)
            if not e:
                continue
            txt, sig, lvars = e
            # **只认"从 this 派生的证据"**：
            #   ① 局部变量表里以 m_/p_m_ 开头的名字（Hex-Rays 的局部名来自它被赋值的表达式，
            #      若来自 `this->m_X` 就长这样）；
            #   ② `p_m_*`（"指向成员 m_X 的指针"命名，通常出自 `&this->m_X`）。
            # **排除**文本里 `->m_X` / `.m_X` 形态 —— 那可能是**另一个对象**的成员
            #   （`this->m_pRoleObj->m_Actor` 的 m_Actor 属于 Actor，但函数仍是 Role 的方法），
            #   全量文本匹配会把它误当成本函数的成员证据（本工具初版就踩了这个坑）。
            ids = set()
            for lv in lvars:
                nm = lv.get('name') if isinstance(lv, dict) else lv
                if isinstance(nm, str) and (nm.startswith('p_m_') or nm.startswith('m_')):
                    ids.add(nm)
            for n in _MEMNAME.findall(txt):
                if n.startswith('p_m_'):
                    ids.add(n)
            # 逐标识符投票
            votes = collections.Counter()
            detail = collections.defaultdict(list)
            for n in ids:
                bases = [n]
                if n.startswith('p_m_'):
                    bases.append(n[2:])
                who = set()
                for b in bases:
                    who |= owner.get(b, set())
                # 只在"该名字确实属于某个注解类"时计票
                for w in who:
                    votes[w] += 1
                    if len(detail[w]) < 6:
                        detail[w].append(n)
            if not votes:
                continue
            top, n = votes.most_common(1)[0]
            # 排除当前类；要求独占票数达阈值且明显高于次席
            second = votes.most_common(2)[1][1] if len(votes) > 1 else 0
            if top == cls or n < args.min_votes or n <= second:
                continue
            cands.append({
                'kind': 'reattribute',
                'addr': a,
                'from': cls,
                'to': top,
                'new_name': '_todo_%s' % a.lower().replace('0x', ''),
                'evidence': ('成员访问证据：decomp 里出现的成员 %s … 共 %d 个属于 %s，'
                             '且不在原注解类 %s 的成员表里（次席票数 %d）。'
                             '签名=%s' % (', '.join(detail[top]), n, top, cls, second, sig[:60])),
                'name_evidence': '含义未定：归属证据充分，但名字需人工复核后给出语义名；'
                                 '此处按规则用诚实占位名，禁止造名。',
            })
    cands.sort(key=lambda x: x['to'])
    print('重归属候选: %d 个（阈值 min-votes=%d）' % (len(cands), args.min_votes))
    by = collections.Counter((c['from'], c['to']) for c in cands)
    print()
    print('按 (原类 -> 目标类) 聚合 top 20:')
    for (fr, to), n in by.most_common(20):
        print('   %-24s -> %-24s %d' % (fr[:24], to[:24], n))
    print()
    print('样本（前 10）:')
    for c in cands[:10]:
        print('   %-12s %s -> %-16s  %s' % (c['from'][:12], c['addr'], c['to'][:16],
                                            c['evidence'][:96]))

    if args.write_batch:
        batch = cands[:args.max_batch]
        json.dump(batch, open(BATCH, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
        print('\n已写入批次（%d 条）-> %s' % (len(batch), BATCH))
        print('注意：new_name 是诚实占位名；跑管线前建议人工复核几条例子的名字与证据。')
    return 0


if __name__ == '__main__':
    sys.exit(main())