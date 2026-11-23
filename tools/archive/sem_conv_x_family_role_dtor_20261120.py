#!/usr/bin/env python3
"""[X族定案 2026-11-20] 0x411ca0/0x411bd0 归属重裁: Object→Role。

决定性证据链:
  1. 0x411CA0 反汇编写三张 vptr 表: [esi]=0x56A9BC / [esi+0x38]=0x56A9B0 /
     [esi+0x40]=0x56A9A4 —— 三表偏移 0/0x38/0x40 与 Role.json bases
     [Object@0, PalScriptWaitObj@56(=0x38), GlowObj@64(=0x40)] **精确对齐**
     ⇒ 0x411CA0 = ??1Role (complete dtor, MI 三基表重置)
  2. 0x411CA0 访问偏移至 0x2A8 —— Role 8704B 装得下; Object 56B 装不下
     (16:19 终裁"归 Object"的 0x2AC 矛盾由此消解)
  3. 0x411BD0 = 调 0x411CA0 + test flags&1 + operator delete + ret 4
     = ??_G 标准形 ⇒ ??_GRole
  4. 主表 0x56A9BC slot0=0x411BD0 (slot0 律自洽: 该表=Role 的 Object 基子对象表)
  5. dtor 体首调 0x412680 = PalScript::DestroyScript (PalScript.json 在案;
     Role 经 PalScriptWaitObj 基关联——链自洽)

旧 IDB 名 _PalScript 的来历=早期分析者的方向性猜测, 表偏移证据推翻。

处置:
  - Object.json 摘 0x00411ca0/0x00411bd0 (盗名定谳)
  - Role.json 认领: 0x00411ca0 = ~Role complete (定义载体);
    0x00411bd0 = ~Role deleting + declaration_only (??_G 织入物, VC6 自生)
  - 0x411b80(Role 第三基表 slot0 ??_G)/0x411bb0(GameObject 表类 ??_G)挂账
    (0x411b80 认领会与 0x411bd0 产生 ??_GRole mangled 撞名, 需先解 N18-MI
    多 deleting 命名豁免——独立跟进)

用法: python3 tools/sem_conv_x_family_role_dtor_20261120.py [--dry]
归档: data/annotations/archive/x_family_role_dtor_20261120.json
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv

# ── Object.json 摘两条 ──
fp_obj = REPO / 'data/annotations/structs/Object.json'
d_obj = json.loads(fp_obj.read_text(encoding='utf-8'))
removed = {}
for addr in ('0x00411ca0', '0x00411bd0'):
    assert addr in d_obj['methods'], '%s 缺条目' % addr
    removed[addr] = d_obj['methods'].pop(addr)
assert not d_obj['methods'].get('0x00411ca0') and not d_obj['methods'].get('0x00411bd0')

# ── Role.json 认领 ──
fp_role = REPO / 'data/annotations/structs/Role.json'
d_role = json.loads(fp_role.read_text(encoding='utf-8'))
assert '0x00411ca0' not in d_role['methods'], 'Role 已有 0x411ca0?'
assert '0x00411bd0' not in d_role['methods'], 'Role 已有 0x411bd0?'

d_role['methods']['0x00411ca0'] = {
    'name': '~Role',
    'source': 'X族定案20261120(原Object盗名): 三基表偏移0/0x38/0x40与bases'
              '[Object@0,PalScriptWaitObj@0x38,GlowObj@0x40]精确对齐+调PalScript::DestroyScript'
              '(0x412680)+访问0x2A8<8704B | 旧IDB名_PalScript=早期猜测,表偏移证据推翻',
    'evidence_level': 'binary_ctor_write_tables',
    'sig_model': {'return': 'void', 'cc': 'thiscall', 'params': [],
                  'varargs': False, 'pending': False},
    'flags': ['dtor'],
}
d_role['methods']['0x00411bd0'] = {
    'name': '~Role',
    'source': 'X族定案20261120: 调??1Role(0x411ca0)+test flags&1+operator delete'
              '+ret 4=??_G标准形; 主表0x56A9BC slot0(slot0律) ⇒ ??_GRole(Object基表视角)',
    'evidence_level': 'binary_ctor_write_tables',
    'sig_model': {'return': 'int', 'cc': 'thiscall',
                  'params': [{'type': 'char', 'name': None}],
                  'varargs': False, 'pending': False},
    'flags': ['dtor', 'deleting'],
    'declaration_only': True,
}

archive = {
    '_doc': 'X族定案 2026-11-20: 0x411ca0/0x411bd0 Object→Role 归属重裁',
    'evidence': [
        '0x411CA0 写三表 [esi]=0x56A9BC/[esi+0x38]=0x56A9B0/[esi+0x40]=0x56A9A4',
        '三表偏移 0/0x38/0x40 与 Role bases [Object@0,PalScriptWaitObj@56,GlowObj@64] 精确对齐',
        '0x411CA0 访问 0x2A8 (Role 8704B 装得下 / Object 56B 装不下)',
        '0x411CA0 调 0x412680=PalScript::DestroyScript (PalScript.json 在案)',
        '0x411BD0=??_G标准形调0x411CA0; 主表0x56A9BC slot0=0x411BD0',
    ],
    'moved': {'0x00411ca0': 'Object→Role (~Role complete, 定义载体)',
              '0x00411bd0': 'Object→Role (~Role deleting, declaration_only)'},
    'pending': [
        '0x411b80 = Role 第三基表(0x56A9CC, Role.json vtables 已登记) slot0 ??_G '
        '—— 认领需先解 N18-MI 多 deleting mangled 撞名(与 0x411bd0 同形 ??_GRole@@...)',
        '0x411bb0 = GameObject 表类(0x56A9C0) ??_G —— GameObject 独立类建档待考',
        'Role.json 0x41be30 ~Role deleting 挂 Glow 表 slot2 —— 槽位归属待重审',
        '表拓扑: 0x56A9A4(Glow)/0x56A9B0(PSWO)/0x56A9BC(Object基)/0x56A9C0(GameObject)/'
        '0x56A9CC(Role第三基) 五表族, Role.json vtables 仅登记 1 张',
        '0x4AF760 三表共享空槽(slot_unk_f760) —— 独立虚函数同实现, 归属保持',
    ],
}
print('摘 Object 2 条 + Role 认领 2 条 (dry=%s)' % DRY)
if not DRY:
    fp_obj.write_text(json.dumps(d_obj, ensure_ascii=False, indent=1), encoding='utf-8')
    fp_role.write_text(json.dumps(d_role, ensure_ascii=False, indent=1), encoding='utf-8')
    outp = REPO / 'data/annotations/archive/x_family_role_dtor_20261120.json'
    outp.write_text(json.dumps(archive, ensure_ascii=False, indent=1), encoding='utf-8')
    print('归档 ->', outp.name)
