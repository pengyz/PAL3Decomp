#!/usr/bin/env python3
"""[N20b 修复 2026-11-22] 17 类 dtor 载体恢复——解除 deleting 条目压制。

N20b 警告: 类级载体全空(所有 dtor 条目 type=skip/declaration_only 压制)
→ ??1/??_G 符号双丢。
修复: 解除恰一条压制(deleted-form ABI 下删除式可当定义源, del 形优先;
多删除式按 VA 判据选 L1 ??_G 对应条目——Role 案先例)。
防护: 解除后跑 probe+match 验证(防 L1 复丢)。
"""
import glob
import json
import os
import re

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STRUCTS = os.path.join(REPO, 'data', 'annotations', 'structs')

# L1 ??_G 符号 va 索引(多删除式 VA 判据用)
s4 = json.load(open(os.path.join(REPO, 'data', 'status', 's4_baseline.json'), encoding='utf-8'))
l1_g = {}  # cls -> va
for r in s4.get('rows', []):
    if r.get('status') == 'match_L1':
        m = re.match(r'^\?\?_G([A-Za-z_]\w*)@@', r['symbol'])
        if m:
            l1_g[m.group(1)] = r.get('va')

txt = open('/tmp/check_full.txt', encoding='utf-8').read()
n20b = re.findall(r'N20b\[(\w+)\]: 类级载体全空\((\d+)条dtor全压制\)', txt)
changed, skipped = [], []


def unsuppress(m):
    """解除单条压制: 删 type=skip 键 + 删 declaration_only; reason 留档。"""
    m.pop('type', None)
    m.pop('declaration_only', None)
    m['reason'] = ((m.get('reason') or '') +
                   ' | [N20b 修复 20261122] 解除压制: deleted-form ABI 删除式可当'
                   '定义源——??1/??_G 载体恢复(类级载体全空债务清偿)').strip(' |')


for cls, _n in n20b:
    fp = os.path.join(STRUCTS, '%s.json' % cls)
    d = json.load(open(fp, encoding='utf-8'))
    _dirty = False
    dels = []
    for a, m in (d.get('methods') or {}).items():
        fl = m.get('flags') or []
        nm = str(m.get('name') or '')
        if ('dtor' in fl or nm.startswith('~')) and 'deleting' in fl:
            dels.append((a, m))
    if not dels:
        # 无 del 条目 → 解除 comp 唯一形态(CCBMagicWindow 案)
        for a, m in (d.get('methods') or {}).items():
            fl = m.get('flags') or []
            nm = str(m.get('name') or '')
            if ('dtor' in fl or nm.startswith('~')) and 'deleting' not in fl:
                if m.get('type') == 'skip' or m.get('declaration_only'):
                    unsuppress(m)
                    _dirty = True
                    changed.append((cls, a, 'comp唯一形态'))
                    break
        if _dirty:
            json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
        continue
    # VA 判据: 优先解除 L1 ??_G va 对应条目
    target = None
    l1va = l1_g.get(cls)
    if l1va:
        for a, m in dels:
            try:
                if int(a, 16) == int(l1va, 16):
                    target = (a, m)
                    break
            except (ValueError, TypeError):
                pass
    if target is None:
        target = dels[0]
    a, m = target
    if m.get('type') == 'skip' or m.get('declaration_only'):
        unsuppress(m)
        _dirty = True
        changed.append((cls, a, 'del%s' % ('(VA=L1)' if l1va else '')))
    else:
        skipped.append((cls, a))
    if _dirty:
        json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('解除 %d 类: %s' % (len(changed), [(c, a, h) for c, a, h in changed]))
if skipped:
    print('跳过(已非压制):', skipped)
