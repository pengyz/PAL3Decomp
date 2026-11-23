#!/usr/bin/env python3
"""[R4 事件修复 2026-11-19] deleting dtor sig_model 虚构参数清除（params清零v2 回滚毒）。

根因链: params清零v2 回滚(04dc77c64)恢复时把 UIMap 式结构参(UIWnd Block 等)错误
带入 deleting dtor sig_model → apply 设毒类型(tinfo 携带虚构参名) → hexrays 渲染
毒参名(Block/消歧名 Blocka) → 4c段名字匹配失配半剥 → C2065 → TU 死 → S4 整类退出
(L1 49→43 事件)。

ABI 律: ??_G = (this, <恰好1个标量 flags>)。结构/指针参皆为虚构。

A 族(本脚本修): 参≠1 或含非标量参 → 删全部指针/结构参, 保留恰好 1 个标量 flags。
B 族(不动, 归属债): 参0≠1 的零参 deleting(幽灵类兄弟 dtor 身份未裁决)。

用法: python3 tools/sem_conv_r4_dtor_sig_poison_20261119.py [--dry]
输出: 逐条修改打印 + 归档 data/annotations/archive/dtor_sig_poison_fix_20261119.json
"""
import json
import glob
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv

SCALAR = {'void', 'int', 'char', 'float', 'double', 'long', 'short', 'unsigned',
          'signed', 'bool', '_BOOL', '_BYTE', '_WORD', '_DWORD', '__int8',
          '__int16', '__int32'}

def base_type(t):
    return str(t).replace('*', '').strip()

def is_scalar_flag(t):
    t = str(t).strip()
    if '*' in t or t.endswith(']') or not t:
        return False
    words = t.replace('*', ' ').split()
    # 双词标量(unsigned int/unsigned char/unsigned long)逐词核验
    return all(w in SCALAR for w in words)

changes = []
archive = {'_doc': 'deleting dtor sig_model 虚构参数清除 2026-11-19 (A族)',
           'entries': []}

for fp in sorted(glob.glob(str(REPO / 'data/annotations/structs/*.json'))):
    d = json.loads(Path(fp).read_text(encoding='utf-8'))
    cls = d.get('name')
    dirty = False
    for a, m in (d.get('methods') or {}).items():
        fl = m.get('flags') or []
        if 'deleting' not in fl:
            continue
        sm = m.get('sig_model')
        if not sm:
            continue
        params = sm.get('params') or []
        nonthis = [p for p in params if 'this' not in str(p.get('type', ''))]
        scalars = [p for p in nonthis if is_scalar_flag(p.get('type'))]
        fictions = [p for p in nonthis if not is_scalar_flag(p.get('type'))]
        if not fictions:
            continue  # B 族或健康
        if len(scalars) != 1:
            # 零标量(B 族/归属债)或多标量(真 flags 需逐案证据) → 记账不动
            archive['entries'].append({'cls': cls, 'addr': a, 'action': 'SKIP_manual',
                                       'reason': 'scalars=%d' % len(scalars),
                                       'params': [p.get('type') for p in params]})
            continue
        old = [p.get('type') for p in params]
        new_params = [p for p in params if (p in nonthis and is_scalar_flag(p.get('type'))) or
                      ('this' in str(p.get('type', '')))]
        sm['params'] = new_params
        dirty = True
        changes.append('%s %s %s: %r -> %r' % (cls, a, m.get('name'), old,
                                                [p.get('type') for p in new_params]))
        archive['entries'].append({'cls': cls, 'addr': a, 'action': 'drop_fiction',
                                   'old_params': old,
                                   'new_params': [p.get('type') for p in new_params]})
    if dirty and not DRY:
        Path(fp).write_text(json.dumps(d, ensure_ascii=False, indent=1), encoding='utf-8')

print('修改 %d 处 (dry=%s):' % (len(changes), DRY))
for c in changes[:20]:
    print('  ' + c)
if len(changes) > 20:
    print('  ... 共 %d' % len(changes))

if not DRY:
    outp = REPO / 'data/annotations/archive/dtor_sig_poison_fix_20261119.json'
    outp.write_text(json.dumps(archive, ensure_ascii=False, indent=1), encoding='utf-8')
    print('归档 -> %s' % outp.name)
