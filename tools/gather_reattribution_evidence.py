#!/usr/bin/env python3
"""【**已停用 —— 两条口径都被证伪，保留作反例记录，不要再据此批改注解**】

* 口径 v1（文本**成员名投票**）→ 273 个候选**全假阳性**：Hex-Rays 用成员名命名局部变量，
  而函数**合法访问别的对象的成员**（`this->m_pRoleObj->m_Actor` 的 `m_Actor` 属于 `Actor`，
  但函数是 `Role` 的方法）⇒ 传递访问污染。
  见 docs/knowledge/gotcha_member_name_voting_is_confounded_by_transitive_access.md。
* 口径 v3（签名无显式 `this` ＋ 首个**指针型** `// ecx` 局部 = `this`）→ 32 个候选，
  抽样即现反例 `0x005155D0`：正则**跳过**了真正的首个 `// ecx`（`int v2; // ecx`），
  抓到**中途临时值** `C2DSpark *v9; // ecx`，于是把 `CCBSystem::PassCmdToTask` 误判为
  `CCBSystem → C2DSpark`。⇒ 局部类型由 Hex-Rays 从赋值表达式（常含强转）推断，**类型 ≠ 归属**。

**⇒ 寄存器/命名启发式都不可靠。可靠的是【结构性证据】**：成员访问的**最大偏移 vs 类尺寸**
（`max_offset > class_size` ⇒ **必然不属于该类**）—— 即注解里那条
`_misattrib_evidence: "max_offset=140>class_size=4"` 的做法。它一直是对的。

原用途（历史记录）：为"归属无据"的函数批量收集成员访问证据，产出可入批次的重归属候选。

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
    ap.add_argument('--min-votes', type=int, default=0,
                    help='成员投票口径的票数阈值；默认 0 = 关闭（该口径已被证伪，见知识库）')
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
            # ---- 判据（user 指正后采用）：**寄存器来源** ----
            # MSVC __thiscall 把 this 放在 ecx；decomp 里首个局部若形如
            #     `X *v1; // ecx`
            # 那它就是 this ⇒ 函数属于 X（或其派生）。
            # 这比"成员名投票"强得多：后者会被**传递访问**污染
            # （this->m_pRoleObj->m_Actor 的 m_Actor 属于 Actor，但函数是 Role 的）。
            # **必须先排除"签名里已有显式 this"的情形**：
            # Hex-Rays 的 `// ecx` 只是**寄存器分配**注释，中途占用 ecx 的临时值也会带上它
            # （实测 0x004FB9F0：`Actor **p_m_WPXVariance; // ecx` 其实是 `&this->m_WPXVariance`，
            #  而该函数签名里已有 `CCBStage *this`）⇒ 那样会把 CCBStage 的析构误判成 Actor 的方法。
            # 只有当签名**没有**显式 this（Hex-Rays 没物化 this，如 0x00411CA0 的 `__cdecl(int)`）
            # 时，首个 `// ecx` 局部才可能是 this。
            ecx_hit = None
            if not re.search(r'\bthis\b', sig):
                for line in txt.split('\n')[:40]:
                    m = re.match(r'\s*([A-Za-z_]\w*)\s*\*+\s*(\w+)\s*;\s*//\s*ecx\b', line)
                    if m:
                        ecx_hit = m.group(1)
                        break
            # **只认"从 this 派生的证据"**：
            #   ① 局部变量表里以 m_/p_m_ 开头的名字（Hex-Rays 的局部名来自它被赋值的表达式，
            #      若来自 `this->m_X` 就长这样）；
            #   ② `p_m_*`（"指向成员 m_X 的指针"命名，通常出自 `&this->m_X`）。
            # **排除**文本里 `->m_X` / `.m_X` 形态 —— 那可能是**另一个对象**的成员
            #   （`this->m_pRoleObj->m_Actor` 的 m_Actor 属于 Actor，但函数仍是 Role 的方法），
            #   全量文本匹配会把它误当成本函数的成员证据（本工具初版就踩了这个坑）。
            # 有 ecx 证据 ⇒ 直接定案（不再投票）
            if ecx_hit and ecx_hit != cls and ecx_hit in anns:
                cands.append({
                    'kind': 'reattribute', 'addr': a, 'from': cls, 'to': ecx_hit,
                    'new_name': '_todo_%s' % a.lower().replace('0x', ''),
                    'evidence': ('寄存器来源证据：签名无显式 this（Hex-Rays 未物化 this），且 decomp 首个 `// ecx` 局部为 '
                                 '`%s *…` —— MSVC __thiscall 把 this 放在 ecx ⇒ 该函数属于 %s，'
                                 '而非注解里的 %s。签名=%s' % (ecx_hit, ecx_hit, cls, sig[:56])),
                    'name_evidence': '含义未定：归属有寄存器证据，但名字需按函数逻辑（算法语义）'
                                     '人工复核后给出；此处按规则用诚实占位名，禁止造名。',
                })
                continue
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
            if args.min_votes <= 0:
                continue            # 投票口径默认关闭（已被证伪：传递访问会污染）
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