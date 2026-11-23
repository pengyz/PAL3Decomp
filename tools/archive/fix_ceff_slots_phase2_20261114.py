#!/usr/bin/env python3
"""[CEff族槽位补齐 2026-11-14 phase2] 走二进制表填 slots + methods 占位, 消 own_unresolved。

规则(vtable_mapper 判据): 每个非空 slots 条目必须 本类methods有 或 from基类methods有。
- slot0(删除式dtor) = 自有槽
- 共享start槽(CEffObj基实现) = from: CEffObj
- 类自有覆写槽 = 自有(补 slot_N 占位, gap_fill 惯例)
用法: python3 tools/fix_ceff_slots_phase2_20261114.py [--apply]
"""
import json, os, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv
S = lambda c: os.path.join(ROOT, 'data/annotations/structs/%s.json' % c)

data = open(os.path.join(ROOT, 'original/PAL3.exe'), 'rb').read()
pe = struct.unpack_from('<I', data, 0x3C)[0]
nsec = struct.unpack_from('<H', data, pe+6)[0]
opt = pe + 24
sec = opt + struct.unpack_from('<H', data, pe+20)[0]
sections = []
for i in range(nsec):
    o = sec + i*40
    sections.append((struct.unpack_from('<I', data, o+12)[0], struct.unpack_from('<I', data, o+16)[0],
                     struct.unpack_from('<I', data, o+20)[0]))
def rd32(va):
    rva = va - 0x400000
    for sva, rsz, raw in sections:
        if sva <= rva < sva + rsz:
            return struct.unpack_from('<I', data, raw + (rva - sva))[0]
    return None

# 已知表起点集(ctor 写表证据) = 边界
import json as _json
_known_starts = sorted(set(int(r['table'], 16) for r in _json.load(open(os.path.join(ROOT, 'data/status/true_vtable_map_20261114.json')))))
_known_set = set(_known_starts)
def walk_table(va, maxn=64):
    out = []
    for k in range(maxn):
        cur = va + 4*k
        if k > 0 and cur in _known_set:
            break  # cur 即下一张已知表的起点 = 本表边界
        t = rd32(cur)
        if t is None or not (0x401000 <= t < 0x56A000) or t % 4 != 0:
            break  # 非对齐目标 = 表尾(0x55434F 类数据伪槽)
        out.append('0x%08X' % t)
    return out

# [动态化 2026-11-14] VT 取自注解自报表址(ctor裁决后已就位); 覆盖全家族
import glob as _glob
VT = {}
for _fp in sorted(_glob.glob(os.path.join(ROOT, 'data/annotations/structs/CEff*.json'))):
    _c = os.path.basename(_fp)[:-5]
    if _c == 'CEffObj': continue
    try:
        _d = json.load(open(_fp, encoding='utf-8'))
        _vts = _d.get('vtables') or []
        if len(_vts) >= 1 and _vts[0].get('addr'):
            VT[_c] = (_vts[0]['addr'], _vts[1]['addr'] if len(_vts) > 1 else _vts[0]['addr'])
    except Exception:
        pass

obj = json.load(open(S('CEffObj'), encoding='utf-8'))
obj_methods = obj.get('methods', {})

# 全局 owner 映射: addr → 有命名方法的类 (优先非 slot_N 名; ICF 共享函数单主)
import glob as _glob
_owner = {}
_owner_name = {}
for _fp in sorted(_glob.glob(os.path.join(ROOT, 'data/annotations/structs/*.json'))):
    _c = os.path.basename(_fp)[:-5]
    try:
        _d = _json.load(open(_fp, encoding='utf-8'))
    except Exception:
        continue
    for _a, _m in (_d.get('methods') or {}).items():
        _n = (_m or {}).get('name', '')
        if not _n:
            continue
        _is_placeholder = _n.startswith('slot_')
        _prev = _owner.get(_a)
        if _prev is None or (_owner_name.get(_a, '').startswith('slot_') and not _is_placeholder):
            _owner[_a] = _c
            _owner_name[_a] = _n

for cls, (t1, t2) in VT.items():
    d = json.load(open(S(cls), encoding='utf-8'))
    methods = d.setdefault('methods', {})
    slots1 = walk_table(int(t1, 16))
    slots2 = walk_table(int(t2, 16), maxn=8)
    new_slots = []
    added = []
    seen = set()
    for si, addr in enumerate(slots1):
        if addr in seen:
            # 重复槽(同函数多槽位): 与首现同判据(owner map)
            a2 = addr.lower()
            oc2 = _owner.get(addr) or _owner.get(a2)
            if addr in methods or a2 in methods:
                frm2 = None
            elif oc2 and oc2 != cls:
                frm2 = oc2
            else:
                frm2 = None
            new_slots.append({'addr': addr, 'from': frm2})
            continue
        seen.add(addr)
        a_hex = '0x%08X' % int(addr, 16)
        a_alt = a_hex.lower()
        own = a_hex in methods or a_alt in methods
        # owner 裁决: 本类有 → 自有; 他类有命名 → from=owner; 全无 → 本类建占位并注册为 owner
        oc = _owner.get(a_hex) or _owner.get(a_alt)
        if own:
            frm = None
        elif (a_hex in obj_methods or a_alt in obj_methods) and cls != 'CEffObj':
            frm = 'CEffObj'  # 基表实现优先(叶值==基值=真继承)
        elif oc and oc != cls:
            frm = oc
        else:
            methods[a_hex] = {'name': 'slot_%d' % si, 'signature': 'void __thiscall()',
                              'source': 'binary:vtable_walk %s slot%d (ceff_family_adjudication_20261114)' % (t1, si),
                              'evidence_level': 'binary_vtable_slot'}
            _owner[a_hex] = cls; _owner_name[a_hex] = 'slot_%d' % si
            added.append(a_hex)
            frm = None
        new_slots.append({'addr': a_hex, 'from': frm})
    # [name/sig保持 2026-11-14] 重建不得覆写正名账字段(按位置继承既有name/sig)
    _old_slots = (d.get('vtables') or [{}])[0].get('slots') or []
    for _i, _ns in enumerate(new_slots):
        if _i < len(_old_slots):
            for _k in ('name', 'sig'):
                if _k in _old_slots[_i]:
                    _ns[_k] = _old_slots[_i][_k]
    d['vtables'] = [
        {'addr': t1, 'base': None, 'slots': new_slots,
         'source': 'binary:vtable_walk 20261114 (ctor写表三元组裁决)', 'evidence_level': 'binary_ctor_write'},
        {'addr': t2, 'base': 'CTaskTpl', 'slots': [],
         'source': 'binary:ctor [@0xC] 终值写(第二链, 3槽; 槽内容parked=第二链走B2路线, 见ceff_family_adjudication)',
         'evidence_level': 'binary_ctor_write'},
    ]
    print('%-16s 主表%d槽(补%d占位, from-CEffObj:%d) 第二表%d槽' % (
        cls, len(new_slots), len(added),
        sum(1 for s in new_slots if s.get('from') == 'CEffObj'), len(slots2)))
    if added:
        print('    占位: %s' % added)
    if APPLY:
        json.dump(d, open(S(cls), 'w', encoding='utf-8'), ensure_ascii=False, indent=1)


if APPLY:
    json.dump(obj, open(S('CEffObj'), 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
else:
    print('\n[dry-run] 加 --apply 落盘')
