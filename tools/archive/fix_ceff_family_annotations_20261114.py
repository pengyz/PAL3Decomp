#!/usr/bin/env python3
"""[CEff族注解修正 2026-11-14] 基于二进制裁决(ceff_family_adjudication_20261114.json)。

建模(b): CEffObj = 12B 多态抽象基(vptr@0 + m_pEM@4 + m_bIdle@8, 永不实例化故无真表);
派生类共享 vptr@0(各自 T1 主表 = CEffObj 槽实现 + 派生覆写); CTaskTpl 第二基本轮不动。

裁决依据:
- ctor 三段写: [@0xC]=CTaskTpl初始表 → [@0x0]=主表 → [@0xC]=第二表
- alloc wrapper(0x4D32C0 push 0x30→CEffQuake 48B; 0x4D3910 push 0x10B0→CEffShock)
- slot0=删除式dtor; xref 唯一性(0x4D3300←0x4D32E0 only, 0x4D3950←0x4D3930 only)

用法: python3 tools/fix_ceff_family_annotations_20261114.py [--apply]
"""
import json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv

S = 'data/annotations/structs/%s.json'

# vtables 真值 (主表, 第二表) — ctor 写表证据
VT = {
    'CEffQuake':      ('0x0056FA88', '0x0056FA7C'),
    'CEffShock':      ('0x0056FADC', '0x0056FAD0'),
    'CEffQuad':       ('0x0056FA30', '0x0056FA24'),
    'CEffAction':     ('0x0056F5E4', '0x0056F5D8'),
    'CEffgbParticle': ('0x0056F8CC', '0x0056F8C0'),
    'CEffExplosive':  ('0x0056F878', '0x0056F86C'),
    'CEffModel':      ('0x0056F9DC', '0x0056F9D0'),
    'CEffCylinder':   ('0x0056F7C8', '0x0056F7BC'),
    'CEffGrid':       ('0x0056F920', '0x0056F914'),
    'CEffMeteor':     ('0x0056F978', '0x0056F96C'),
    'CEffBink':       ('0x0056F674', '0x0056F668'),
    'CEffCallBack':   ('0x0056F71C', '0x0056F710'),
}

# CEffQuake 主表 0x56FA88 槽位 (15槽, ctor 0x4D3280 [@0]=0x56FA88 终值写)
# slot0 = del-dtor(CEffQuake自有, 保留CEffQuake); slot1-14 = CEffObj 基实现(共享start无覆写)
QUAKE_PRIMARY_SLOTS = ['0x004D32E0','0x004C0650','0x004D33A0','0x00408BD0','0x00408BD0',
                       '0x004C29A0','0x00408BD0','0x004D32C0','0x004C0500','0x004AF760',
                       '0x004C0510','0x004AF760','0x004D33B0','0x004C15D0','0x004D3660']

def load(cls):
    return json.load(open(S % cls, encoding='utf-8'))

def save(cls, d):
    if APPLY:
        json.dump(d, open(S % cls, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

# ---- 1) CEffObj: vtables 平反 + 接收基实现 ----
qk = load('CEffQuake')
obj = load('CEffObj')
moved = []
obj['vtables'] = [{'addr': '0x0056FA88', 'base': None,
                   'slots': [{'addr': a, 'from': None} for a in QUAKE_PRIMARY_SLOTS],
                   'source': 'binary:ctor 0x4D3280 [@0]=0x56FA88 终值写(三段式第2段); CEffObj多态抽象基永不实例化, CEffQuake主链零覆写故共享start; 裁决=ceff_family_adjudication_20261114',
                   'evidence_level': 'binary_ctor_write'}]
# 从 CEffQuake methods 移交 slot1-14 的实现 (slot0=0x4D32E0 del-dtor 保留CEffQuake)
KEEP_QK = {'0x004D32E0'}  # del-dtor
qk_methods = qk.get('methods', {})
obj_methods = obj.setdefault('methods', {})
for addr, m in list(qk_methods.items()):
    a = addr.upper().replace('0X', '0x')
    if addr in KEEP_QK or a in KEEP_QK:
        continue
    # 槽内函数 → CEffObj (槽证据)
    a_norm = '0x00%s' % addr[-6:] if addr.startswith('0x00') else addr
    in_slots = any(s['addr'].lower() == addr.lower() for s in obj['vtables'][0]['slots'][1:])
    if in_slots and addr not in obj_methods:
        m2 = dict(m)
        m2['source'] = (m.get('source','') + ' | binary:ceff_family_adjudication_20261114 主表0x56FA88槽内=CEffObj基实现(CEffQuake共享start零覆写) — 自CEffQuake移交').strip(' |')
        obj_methods[addr] = m2
        moved.append(addr)
for addr in moved:
    qk_methods.pop(addr, None)
print('CEffObj: vtables→0x56FA88(15槽), 接收 %d 个基实现: %s' % (len(moved), moved))
save('CEffObj', obj)

# ---- 2) CEffQuake: 尺寸48 + vtables 真值 ----
qk['binary_size'] = 48
qk['vtables'] = [
    {'addr': VT['CEffQuake'][0], 'base': None,
     'slots': [{'addr': a, 'from': None} for a in QUAKE_PRIMARY_SLOTS],
     'source': 'binary:ctor 0x4D3280 [@0] 终值写; 与CEffObj共享start(主链零覆写); slot0=del-dtor 0x4D32E0',
     'evidence_level': 'binary_ctor_write'},
    {'addr': VT['CEffQuake'][1], 'base': 'CTaskTpl_tagEffTaskParam_CEffQuake',
     'slots': [],
     'source': 'binary:ctor 0x4D3280 [@0xC]=0x56FA7C 终值写(第二链); dtor 0x4D3300 同址佐证',
     'evidence_level': 'binary_ctor_write'},
]
print('CEffQuake: binary_size→48, vtables→[0x56FA88, 0x56FA7C], methods剩 %d' % len(qk['methods']))
save('CEffQuake', qk)

# ---- 3) 其余类 vtables 真值替换 ----
for cls, (t1, t2) in VT.items():
    if cls == 'CEffQuake':
        continue
    d = load(cls)
    old = [(v.get('addr'), v.get('base')) for v in d.get('vtables', [])]
    slots1 = []
    # 尽量保留原主表槽内容(若地址一致)
    for v in d.get('vtables', []):
        if (v.get('addr') or '').lower() == t1.lower():
            slots1 = v.get('slots', [])
    d['vtables'] = [
        {'addr': t1, 'base': None, 'slots': slots1,
         'source': 'binary:ctor写表证据(ceff_alloc_map_20261114); 旧值=%s' % old,
         'evidence_level': 'binary_ctor_write'},
        {'addr': t2, 'base': 'CTaskTpl', 'slots': [],
         'source': 'binary:ctor [@0xC] 终值写(第二链)', 'evidence_level': 'binary_ctor_write'},
    ]
    print('%-16s vtables %s → [%s, %s]' % (cls, old, t1, t2))
    save(cls, d)

if not APPLY:
    print('\n[dry-run] 加 --apply 落盘')
