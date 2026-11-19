#!/usr/bin/env python3
"""[X族定案第二段 2026-11-20] 表拓扑收口——Role 五表族 + GameObject 表壳类 + 槽认领。

拓扑终局 (证据: Role bases 三基偏移 + 0x411CA0 三表写 + GameObject 4B 壳):
  GameObject(4B vptr-only 根基) → Object(56B: vptr@0+5成员@0x4起) →
  Role(8704B MI: Object@0 + PalScriptWaitObj@0x38 + GlowObj@0x40)

五张表族:
  0x56A9C0 = Role 主表 (GameObject 原生表, slot0 被 Role override 合并——
             Role 是 GameObject 唯一派生)
  0x56A9BC = Role 的 Object 基子对象表 (slot0=??_GRole override)
  0x56A9CC = Role 第三基表 (Role.json 已登记)
  0x56A9B0/0x56A9A4 = PSWO/Glow 基表 (归各自基类 json, 本轮不动)

Role dtor 全家 (MI 四 deleting 形态 + 一 complete):
  0x411CA0 ??1Role complete (定义载体)
  0x411BD0 ??_GRole @Object基表 (decl_only)
  0x411BB0 ??_GRole @主表 (decl_only)
  0x411B80 ??_GRole @第三基表 (decl_only)
  三 deleting 同 mangle 形 → IDA SN_FORCE _0/_1 区分——decl_only 不发射, 无编译面伤

槽认领: 0x4AF760 (主表 slot3=UpdateFrame 虚方法) Object→Role;
GameObject.json 摘 vtables 登记 (表→Role), ctor 条目保留 (表归属者)。

用法: python3 tools/sem_conv_x_family_tables_20261120.py [--dry]
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv

# ── Role.json: 认领 0x411bb0/0x411b80 + vtables 补主表/Object基表 ──
fp_role = REPO / 'data/annotations/structs/Role.json'
d = json.loads(fp_role.read_text(encoding='utf-8'))
for addr in ('0x00411bb0', '0x00411b80'):
    assert addr not in d['methods'], 'Role 已有 %s' % addr
    d['methods'][addr] = {
        'name': '~Role',
        'source': 'X族定案二段20261120: MI 删除析构 %s 形态 (写%s)——'
                  '%s; decl_only=织入物 VC6 自生' % (
                      '主表0x56A9C0 slot0 内联' if addr == '0x00411bb0' else '第三基表0x56A9CC slot0',
                      '0x56a9c0' if addr == '0x00411bb0' else '0x56a9cc',
                      '反汇编写表直证'),
        'evidence_level': 'binary_ctor_write_tables',
        'sig_model': {'return': 'int', 'cc': 'thiscall',
                      'params': [{'type': 'char', 'name': None}],
                      'varargs': False, 'pending': False},
        'flags': ['dtor', 'deleting'],
        'declaration_only': True,
    }
# 0x4AF760 UpdateFrame (主表 slot3 虚方法)
if '0x004af760' not in d['methods']:
    d['methods']['0x004af760'] = {
        'name': 'UpdateFrame',
        'source': 'X族定案二段20261120: Role 主表 0x56A9C0 slot3 (GameObject 表登记 '
                  'slot2 name=UpdateFrame 迁移); 空函数体, 三表共享实现',
        'evidence_level': 'binary_vtable_slot',
        'sig_model': {'return': 'void', 'cc': 'thiscall', 'params': [],
                      'varargs': False, 'pending': False},
    }
# vtables: 0x56a9cc 已有——补 0x56a9c0 主表 + 0x56a9bc Object基表
_vt_existing = {v.get('addr', '').lower() for v in (d.get('vtables') or [])}
for vt_addr, slots in [
    ('0x0056a9c0', [{'addr': '0x00411bb0'}, {'addr': '0x0055434f'},
                    {'addr': '0x004af760', 'name': 'UpdateFrame'}, {'addr': '0x00411b80'}]),
    ('0x0056a9bc', [{'addr': '0x00411bd0'}, {'addr': '0x00411bb0'},
                    {'addr': '0x0055434f'}, {'addr': '0x004af760', 'name': 'UpdateFrame'},
                    {'addr': '0x00411b80'}]),
]:
    if vt_addr not in _vt_existing:
        d.setdefault('vtables', []).append({
            'addr': vt_addr, 'base': None, 'slots': slots,
            'source': 'X族定案二段20261120: %s (0x411CA0 写表/0x411BB0 写表直证; '
                      '原 GameObject/Object 登记转移)' % ('Role 主表' if 'a9c0' in vt_addr else 'Role Object基表'),
        })
if not DRY:
    fp_role.write_text(json.dumps(d, ensure_ascii=False, indent=1), encoding='utf-8')

# ── GameObject.json: 摘 vtables (表→Role), ctor 保留 ──
fp_go = REPO / 'data/annotations/structs/GameObject.json'
g = json.loads(fp_go.read_text(encoding='utf-8'))
if g.get('vtables'):
    g['_vtables_removed'] = 'X族定案二段20261120: 0x56A9C0=Role 主表(GameObject 原生表被唯一派生 override 合并) → Role.json vtables; GameObject=4B vptr-only 根基类'
    g['vtables'] = []
if not DRY:
    fp_go.write_text(json.dumps(g, ensure_ascii=False, indent=1), encoding='utf-8')

# ── Object.json: 摘 0x4af760 (→Role) ──
fp_obj = REPO / 'data/annotations/structs/Object.json'
o = json.loads(fp_obj.read_text(encoding='utf-8'))
if '0x004af760' in o.get('methods', {}):
    o['methods'].pop('0x004af760')
    print('Object.json 摘 0x4af760 (→Role UpdateFrame)')
if not DRY:
    fp_obj.write_text(json.dumps(o, ensure_ascii=False, indent=1), encoding='utf-8')

print('Role: +2 dtor 形态 +UpdateFrame +2 表登记 | GameObject: 摘表登记 | Object: 摘 0x4af760 (dry=%s)' % DRY)
