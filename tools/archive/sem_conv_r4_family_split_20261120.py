#!/usr/bin/env python3
"""[R4 分家手术 2026-11-20] CGameData known_members → UITitle.json 迁移（InitRoles 访问族）。

依据: 13 方法 this 普查定谳——InitRoles(0x44ade0) this=+0x1394(UITitle 子对象),
其 this->member 访问族(33 条)=UITitle 内部偏移, 错标 CGameData 顶层。
迁移: offset 不变(相对 UITitle 头), 迁入 UITitle.json known_members。
冲突合并: UITitle 已有同址条目时保留 UITitle 名(类主档案), 迁入名记入 source。
C10 预演: 迁出后顶层 0x374-0x2528 区间仅剩锚点, 无重叠。

用法: python3 tools/sem_conv_r4_family_split_20261120.py [--dry]
归档: data/annotations/archive/family_split_20261120.json
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv

MIGRATE = ['0x4c', '0x5c', '0x6c', '0x70', '0x7c', '0x114', '0x1ac', '0x374',
           '0x3dc', '0x3e0', '0x4cc', '0x534', '0x538', '0x624', '0x68c', '0x690',
           '0x77c', '0xcd4', '0xcd8', '0xce8', '0xce9', '0xcec', '0x1244', '0x179c',
           '0x1cf4', '0x1cf8', '0x2510', '0x2514', '0x2518', '0x251c', '0x2520',
           '0x2524', '0x2528']

fp_cg = REPO / 'data/annotations/structs/CGameData.json'
fp_ut = REPO / 'data/annotations/structs/UITitle.json'
d_cg = json.loads(fp_cg.read_text(encoding='utf-8'))
d_ut = json.loads(fp_ut.read_text(encoding='utf-8'))

km_cg = d_cg['known_members']
km_ut = d_ut.setdefault('known_members', {})

archive = {'_doc': 'CGameData→UITitle 分家手术 2026-11-20', 'migrated': [],
           'merged': [], 'skipped': []}

for off in MIGRATE:
    m = km_cg.get(off)
    if m is None:
        archive['skipped'].append(off)
        continue
    ev = m.get('source') or ''
    old = dict(m)
    del km_cg[off]
    m['source'] = (ev + ' | 分家迁移20261120: InitRoles(this=+0x1394) 访问族——'
                   '13方法this普查定谳(调用链0x44f38c直证), 原 CGameData 顶层错标').strip(' |')
    if off in km_ut:
        # 冲突合并: 保留 UITitle 名(类主档案), 迁入名/访问语义记 source
        ut_m = km_ut[off]
        ut_m['source'] = (ut_m.get('source') or '') + \
            ' | 合并20261120: CGameData 错标别名 %r (InitRoles 清零/写访问) 同址归并' % m.get('name')
        archive['merged'].append({'off': off, 'kept': ut_m.get('name'), 'absorbed': m.get('name')})
    else:
        km_ut[off] = m
        archive['migrated'].append({'off': off, 'name': m.get('name')})
    _ = old

if not DRY:
    fp_cg.write_text(json.dumps(d_cg, ensure_ascii=False, indent=1), encoding='utf-8')
    fp_ut.write_text(json.dumps(d_ut, ensure_ascii=False, indent=1), encoding='utf-8')
    outp = REPO / 'data/annotations/archive/family_split_20261120.json'
    outp.write_text(json.dumps(archive, ensure_ascii=False, indent=1), encoding='utf-8')
    print('归档 ->', outp.name)

print('迁移 %d | 合并 %d | 跳过 %d (dry=%s)' % (
    len(archive['migrated']), len(archive['merged']), len(archive['skipped']), DRY))
for mg in archive['merged']:
    print('  合并 0x%s: 保留 %r 吸收 %r' % (mg['off'][2:], mg['kept'], mg['absorbed']))
print('CGameData known_members 剩: %d' % len(km_cg))
print('UITitle known_members 现: %d' % len(km_ut))
