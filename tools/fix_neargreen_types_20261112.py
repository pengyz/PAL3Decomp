#!/usr/bin/env python3
"""[近绿池机械族落标 2026-11-12] 三站点证据修复。

G. UIRoleSelectDialog::HandleInput(0x00529E40) lvars v10
   现状: `int v10;` + `v10 = PtInRect;`(×2) → C2440 fn-ptr→int ×2
   证据: v10 无后续读用(dead store 持函数地址); `v10 = 0` 对指针型合法
   (null 常量); PtInRect 原型 BOOL(__stdcall*)(const RECT*, POINT) 与
   `int (__stdcall *)(const tagRECT *, tagPOINT)` 类型恒等(typedef 同一)。

F. D3DXVec3Normalize 导入签名(0x00542533 IAT槽)
   现状: functions.json 已有诚实sig(D3DXVECTOR3*双参)但白名单
   _GB_IMPORT_SIGS 未收录 → IDB槽无型 → Hex-Rays 渲染 (int)&v45 casts
   → C2664(sg_emission_control:376)
   证据: functions.json sig + til 已含 D3DXVECTOR3(实测 True)。
   (白名单收录落在 pipeline/ida/apply_annotations.py——既有正道, 前例
   GetCenter/Normalize/CreateEff)

B. stru_5D550C 全局 retyp Logger→char[6360]
   现状: IDB typed Logger → 成员式渲染 → &m_callbacks[4].pfn 当字符串传
   NewTexture → C2664 ×2 (C2DSpark:115/C3DSpark:118)
   证据: 全部使用点皆字符串语义(UIWnd:349 strcat读, C2DSpark/C3DSpark
   NewTexture传, CEffect:972 FormatException经cast)且无一处以Logger
   对象语义直用(方法调用全经显式cast); extent=Logger尺寸6360(IDB现有
   item尺寸, 无邻居重叠)。

用法: python3 tools/fix_neargreen_types_20261112.py [--apply]
"""
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv

# --- G: lvars v10 ---
fp = os.path.join(ROOT, 'data', 'annotations', 'structs', 'UIRoleSelectDialog.json')
d = json.load(open(fp, encoding='utf-8'))
me = d.setdefault('methods', {}).setdefault('0x00529E40', {})
lv = me.setdefault('lvars', {})
old = lv.get('v10')
lv['v10'] = 'int (__stdcall *)(const tagRECT *, tagPOINT)'
me['lvars_source'] = (me.get('lvars_source', '') +
    ' | v10=PtInRect死存(×2站)持函数地址无读用; 与PtInRect型恒等; v10=0对指针型合法(null常量)').strip(' |')
print('G. UIRoleSelectDialog 0x00529E40 v10: %r -> fn-ptr' % old)
if APPLY:
    json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

# --- B: stru_5D550C 全局 retyp ---
fp = os.path.join(ROOT, 'data', 'annotations', 'globals.json')
d = json.load(open(fp, encoding='utf-8'))
key = None
for k in d:
    if '5D550C' in k.upper():
        key = k
        break
entry = {
    'name': 'stru_5D550C',
    'type': 'char[6360]',
    'category': 'data',
    'source': 'use_site_enumeration 2026-11-12: 全部使用点皆字符串/字节语义'
              '(UIWnd:349 strcat读/C2DSpark:115+C3DSpark:118 NewTexture传/'
              'CEffect:972 FormatException经cast); Logger成员访问零直用; '
              'extent=Logger尺寸6360(IDB现有item无重叠)',
    'audit': {
        'level': 'audited',
        'method': 'use_site_enumeration',
        'sites_checked': 5,
        'sites_consistent': 5,
        'sites_contradicted': 0,
        'contradictions': [],
        'timestamp': '2026-11-12',
    },
}
if key:
    old = d[key]
    d[key] = entry
    print('B. globals[%s]: %r -> char[6360]' % (key, (old or {}).get('type') if isinstance(old, dict) else old))
else:
    d['0x005D550C'] = entry
    print('B. globals 新增 0x005D550C -> char[6360]')
if APPLY:
    json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

if not APPLY:
    print('\n[dry-run] 加 --apply 落盘')
