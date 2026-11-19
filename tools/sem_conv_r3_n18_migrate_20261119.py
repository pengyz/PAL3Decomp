#!/usr/bin/env python3
"""[R3-T2·N18迁移 2026-11-19] 形态名清出名字槽——130 处 dtor 条目名归一 ~类名。

规则(用户裁定, N18 门禁同步落):
  flags(dtor/deleting) 与名形互为双向断言。析构源名唯一可推导(~类名——
  源码一个类只许一个析构声明, VC6 实测 C2524 拒 ~X(int)), 名字对 dtor
  条目零自由度; 二进制形态(_sdtor/_scalar_dtor/deleting/伴生)信息全部
  上移 flags + declaration_only 承载。
迁移形态:
  _scalar_dtor_XXXX / _scalar_dtor / _sdtor_call_dtor / _dtor_thunk 等
  + flags含dtor/deleting → name = '~' + 类名
  伴生判定(declaration_only): 同类同址族已有独立 ??1 主条目(另一地址
  名已呈 ~X 形) → 本条 declaration_only=true; 否则单条目即主条目。
双向违例二类:
  名呈~X形但flags缺dtor → flags 补 ['dtor'] (身份补注)
  deleting 无 dtor 同现 → 合并
归档: 全量 before/after 存 archive/n18_migration_20261119.json。

用法: python3 tools/sem_conv_r3_n18_migrate_20261119.py
"""
import json
import re
from collections import defaultdict
from pathlib import Path

REPO = Path(__file__).parent.parent
SDIR = REPO / 'data/annotations/structs'
ARCH = REPO / 'data/annotations/archive/n18_migration_20261119.json'

DTOR_NAME_RE = re.compile(r'^(_sdtor|_scalar_dtor|_vector_dtor|_dtor_thunk|.*scalar_deleting)')

stats = defaultdict(int)
migration = []
for fp in sorted(SDIR.glob('*.json')):
    try:
        d = json.loads(fp.read_text(encoding='utf-8'))
    except Exception:
        continue
    cls = d.get('name') or fp.stem
    methods = d.get('methods') or {}
    if not methods:
        continue
    changed = False
    # 先建该类 ~X 名地址集(判伴生)
    tilde_addrs = {k for k, m in methods.items()
                   if isinstance(m, dict) and str(m.get('name') or '').startswith('~')}
    entries = list(methods.items())
    for k, m in entries:
        if not isinstance(m, dict):
            continue
        nm = str(m.get('name') or '')
        fl = m.get('flags') or []
        is_dtor_flag = 'dtor' in fl or 'deleting' in fl
        is_tilde = nm.startswith('~')
        before = {'key': k, 'name': nm, 'flags': list(fl),
                  'declaration_only': m.get('declaration_only')}
        after = dict(before)
        if is_dtor_flag and not is_tilde:
            if DTOR_NAME_RE.match(nm) or nm == cls:
                m['name'] = '~' + cls
                after['name'] = m['name']
                stats['renamed'] += 1
            else:
                continue  # 非形态名(如 slot_N)不属本轮——N18 会另行报
        elif is_tilde and not is_dtor_flag:
            fl = m.get('flags') or []
            fl.append('dtor') if 'dtor' not in fl else None
            m['flags'] = fl
            after['flags'] = list(fl)
            stats['flags_added'] += 1
        if 'deleting' in (m.get('flags') or []) and 'dtor' not in (m.get('flags') or []):
            m['flags'].append('dtor')
            after['flags'] = list(m['flags'])
            stats['deleting_merged'] += 1
        # 伴生判定: 归一后同类存在另一 ~X 地址(主条目) → 本条=伴生
        if str(m.get('name') or '').startswith('~'):
            siblings = tilde_addrs - {k} | {k2 for k2, m2 in methods.items()
                                            if isinstance(m2, dict)
                                            and str(m2.get('name') or '').startswith('~')
                                            and k2 != k}
            if siblings:
                if not m.get('declaration_only'):
                    m['declaration_only'] = True
                    after['declaration_only'] = True
                    stats['companion_marked'] += 1
        if before != after:
            migration.append({'class': cls, 'file': fp.name, 'before': before,
                              'after': after})
            changed = True
    if changed:
        fp.write_text(json.dumps(d, indent=1, ensure_ascii=False), encoding='utf-8')

ARCH.write_text(json.dumps({
    '_doc': 'N18 迁移 2026-11-19: dtor 形态名清出名字槽(~类名归一), 形态上移 '
            'flags(deleting)+declaration_only。规则=名槽只承载可推导标签, '
            '二进制形态信息归 flags(用户裁定 2026-11-19)。',
    'stats': dict(stats),
    'entries': migration,
}, indent=1, ensure_ascii=False), encoding='utf-8')
print('[N18迁移] %s' % dict(stats))
print('[N18迁移] 归档 %d 条 → %s' % (len(migration), ARCH.name))
