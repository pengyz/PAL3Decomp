#!/usr/bin/env python3
"""**结构性**归属检测：函数访问的最大偏移 vs 该类注解尺寸 —— 唯一可靠的重归属判据。

# 为什么用结构而不是启发式

本会话已把三条启发式口径全部证伪（见 `tools/gather_reattribution_evidence.py` 头部）：

| 口径 | 结局 |
|---|---|
| 文本成员名投票 | 273 候选全假阳性（传递访问污染） |
| `// ecx` 首局部 = this | 360 候选，假阳性（中途占用 ecx 的临时值） |
| 无显式 this ＋ 首个**指针** `// ecx` | 32 候选，假阳性（正则跳过非指针首个，抓到中途值） |

**可靠的是不等式**：一个函数若在某个基指针上访问了偏移 `max_off`，
而它被注解成的类尺寸只有 `size`，则 **`max_off >= size` ⇒ 它必然不属于该类**
（对象里不存在那个字节）。这与访问方式、命名、寄存器分配**全都无关**，是**可证伪的**。

这正是注解里历史条目所用过的证据形式，例如
`_misattrib_evidence: "max_offset=140>class_size=4"`（`0x00411CA0`）与
`"max this-offset 0x19DA8 fits SaleUI 0x19DB8"`（**放得下 ⇒ 不构成误归属证据**）。

# 判据

* 取 decomp 里形如 `*((_TYPE *)BASE + N)` / `*(_TYPE *)(BASE + N)` / `BASE[N]` 的**最大 N**；
* `BASE` 取：`this`，否则「签名无显式 this 时首个 `// ecx` 局部」（**只用来读偏移，
  不用来判断归属** —— 这里它是"被访问的基指针"的候选，不是归属结论）；
* `max_off >= class_size` ⇒ **CONTRADICTS**（有据"移出"）；
* 否则若 `max_off` 落在**另一个类**的成员区间内 ⇒ 提示候选目标类（仅提示，需人工确认）；
* 否则 ⇒ `FITS`（不构成证据）。

用法：
    python3 tools/audit_structural_attribution.py                # 报告
    python3 tools/audit_structural_attribution.py --addr 0x00411CA0  # 单条（验证用）
"""
import argparse
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN = os.path.join(ROOT, 'data', 'annotations', 'structs')
DECOMP = os.path.join(ROOT, 'asm', 'pal3', 'decomp')

_PAT = [
    re.compile(r'\*\(\s*\(\s*[A-Za-z_][\w:]*\s*\*+\s*\)\s*(\w+)\s*\+\s*(\d+)\s*\)'),
    re.compile(r'\*\s*\(\s*[A-Za-z_][\w:]*\s*\*+\s*\)\s*\(\s*(\w+)\s*\+\s*(\d+)\s*\)'),
    re.compile(r'\b(\w+)\s*\[\s*(\d+)\s*\]'),
]


def max_off_for(txt, base):
    """基指针 `base` 上出现的最大字面偏移。"""
    best = 0
    for pat in _PAT:
        for m in pat.finditer(txt):
            if m.group(1) == base:
                best = max(best, int(m.group(2)))
    return best


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--addr', help='只查这一条（验证用）')
    ap.add_argument('--limit', type=int, default=25)
    args = ap.parse_args()

    anns, sizes = {}, {}
    for f in sorted(glob.glob(os.path.join(ANN, '*.json'))):
        d = json.load(open(f, encoding='utf-8'))
        cls = d.get('name') or os.path.basename(f)[:-5]
        anns[cls] = d
        try:
            sizes[cls] = int(d.get('binary_size') or 0)
        except (TypeError, ValueError):
            sizes[cls] = 0

    byaddr = {}
    for f in glob.glob(os.path.join(DECOMP, '*.json')):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except Exception:
            continue
        a = str(d.get('address') or '').lower()
        if a:
            byaddr[a] = d

    contradictions, fits, unknown = [], 0, 0
    for cls, d in anns.items():
        size = sizes.get(cls) or 0
        if not size:
            continue
        for a in (d.get('methods') or {}):
            try:
                va = int(a, 16)
            except ValueError:
                continue
            if args.addr and a.lower() != args.addr.lower() and \
                    ('0x%x' % va) != args.addr.lower():
                continue
            e = byaddr.get('0x%x' % va) or byaddr.get('0x%08x' % va)
            if not e:
                unknown += 1
                continue
            txt = e.get('decompiled_c') or ''
            sig = e.get('signature') or ''
            # **只认基指针 == `this`**。
            # 其它局部（含 ecx 来的）都可能指向**别的对象**，其偏移相对那个对象而非本对象
            # （实测假阳性：`*((_DWORD *)m_pRoleState + 932)` 的 932 相对 m_pRoleState；
            #   `v4 + 24600` 同理）⇒ 那样得到的"超出类尺寸"不成立。
            off, base = max_off_for(txt, 'this'), 'this'
            if not off:
                unknown += 1
                continue
            if off >= size:
                tgt = [c for c, s in sizes.items()
                       if c != cls and s > off and (anns[c].get('known_members') or {})]
                contradictions.append({
                    'kind': 'reattribute', 'addr': a, 'from': cls,
                    'to': (tgt[0] if len(tgt) == 1 else ''),
                    'new_name': '_todo_%s' % a.lower().replace('0x', ''),
                    'evidence': ('结构性证据：decomp 在基指针 `%s` 上访问到最大偏移 %d（0x%X），'
                                 '而注解类 %s 的 binary_size=%d ⇒ **%d >= %d，必然不属于该类**'
                                 '（对象里不存在那个字节）。签名=%s'
                                 % (base, off, off, cls, size, off, size, sig[:54])),
                    'name_evidence': '含义未定：归属有结构性证据，名字需按函数逻辑人工复核；'
                                     '此处按规则用诚实占位名，禁止造名。',
                })
            else:
                fits += 1

    print('结构性检测：偏移**超出**注解尺寸（有据的误归属）= %d 条；'
          '放得下（不构成证据）= %d；无法判定 = %d' % (len(contradictions), fits, unknown))
    print()
    for c in contradictions[:args.limit]:
        print('   %s  %s(size=%d) -> %s' % (c['addr'], c['from'][:22],
                                            sizes.get(c['from'], 0), c['to'] or '(目标类待定)'))
        print('        %s' % c['evidence'][:150])
    if args.addr and contradictions:
        json.dump(contradictions, open('/tmp/structural_one.json', 'w', encoding='utf-8'),
                  ensure_ascii=False, indent=1)
        print('\n单条结果 -> /tmp/structural_one.json')
    return 0


if __name__ == '__main__':
    sys.exit(main())