#!/usr/bin/env python3
"""[归属修正 2026-11-18] 三个假 Actor dtor → 真实类归属（CEffGrid/CEffQuake/CEffShock）。

定谳链（tools/probe_sdtor_bytes_20261118.py + probe_vtable_region_56f9_20261118.py）：
  四函数各 129B, 唯一差异 = 第4条指令写 vptr 的目标表:
    mov dword ptr [esi], offset <vtable>
  CEffObj 链表尾 5 槽模式(slot13..17): UpdateParticles / GetEditorTaskDescription /
  UpdateDelta(0x4c2600 折叠载体) / Object_FatalExit(0x55434f 折叠载体) /
  scalar-deleting-dtor(各表独立地址, int 形参 a2&1)。
  四张表尾同构, 各指向本类 deleting dtor:
    0x4c9470 ← 0x56f910 (Actor 表尾,  mangle ??1Actor@@QAE@H@Z 官方)  保留
    0x4cb280 ← 0x56f964 (CEffGrid 表尾, 上槽 GetEditorTaskDescription@CEffGrid)
    0x4d37a0 ← 0x56facc (CEffQuake 表尾, 上槽 GetEditorTaskDescription@CEffQuake)
    0x4d4ca0 ← 0x56fb20 (CEffShock 表尾, 上槽 GetEditorTaskDescription@CEffShock)
  语料"同体"假象: hexrays 隐藏 vptr 写 → decompiled_c 相同, 物理字节仅 vtable
  立即数不同(bytes probe: first diff @+0x8)。ICF 未折叠(字节不等)。
  危害: 三假条目(~Actor_2/3/4 + flags=dtor) → stage1/emit_headers T23-F1 全改
  名 _sdtor_call_dtor → Actor.cpp 4 个同名重定义 C2084 + 头声明缺失 C2039
  (Actor.h 仅 virtual ~Actor()) + 调用点 C2673 —— Actor.cpp 101 错主体。

动作:
  Actor.json: 删 0x4cb280/0x4d37a0/0x4d4ca0 三条 (原文归档)。
  CEffGrid.json / CEffQuake.json / CEffShock.json: 各加 deleting dtor 条目
  (name=_sdtor_call_dtor 形态, flags=['dtor'], sig (int a2), evidence A)。

用法: python3 tools/rehome_sdtor_trio_20261118.py
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
SDIR = REPO / 'data/annotations/structs'
ARCH = REPO / 'data/annotations/archive/actor_sdtor_misnomer_trio_20261118.json'

MOVE = {
    '0x004cb280': 'CEffGrid',
    '0x004d37a0': 'CEffQuake',
    '0x004d4ca0': 'CEffShock',
}
TABLE_TAIL = {
    'CEffGrid': '0x56f964',
    'CEffQuake': '0x56facc',
    'CEffShock': '0x56fb20',
}

actor_p = SDIR / 'Actor.json'
actor = json.loads(actor_p.read_text(encoding='utf-8'))
methods = actor.get('methods') or {}
stolen = {}
for k in MOVE:
    if k in methods:
        stolen[k] = methods.pop(k)
if len(stolen) != len(MOVE):
    print('[rehome] 预期 3 条假 dtor, 实得 %d — 状态异常中止' % len(stolen))
    sys.exit(1)
actor_p.write_text(json.dumps(actor, indent=1, ensure_ascii=False), encoding='utf-8')

arch = {
    '_doc': 'Actor deleting-dtor 名盗用三连 2026-11-18: ~Actor_2/3/4 实为 '
            'CEffGrid/CEffQuake/CEffShock 的 scalar deleting dtor (129B 同构体, '
            '唯一差异=vptr 写目标表)。原文如下。',
    'evidence': 'probe_sdtor_bytes_20261118: first diff @+0x8 = vtable 立即数; '
                'probe_vtable_region_56f9: 四表尾同构 slot17=deleting dtor。',
    'stolen_entries': stolen,
}
ARCH.write_text(json.dumps(arch, indent=1, ensure_ascii=False), encoding='utf-8')

for k, cls in MOVE.items():
    fp = SDIR / ('%s.json' % cls)
    d = json.loads(fp.read_text(encoding='utf-8'))
    m = dict(stolen[k])
    m['name'] = '_sdtor_call_dtor'
    m['flags'] = ['dtor']
    m['flags_evidence'] = (
        '[A 级 2026-11-18] scalar deleting dtor 实锤: 函数序 mov [esi],offset '
        '%s (写本类 vptr) + a2&1 → operator delete(this); 表尾同构 slot17 '
        '(上槽 GetEditorTaskDescription@%s); 物理字节与 Actor::~Actor 仅差 '
        'vtable 立即数(bytes probe first diff @+0x8)。原误注 Actor::~Actor_N '
        '已归档 archive/actor_sdtor_misnomer_trio_20261118.json。' % (TABLE_TAIL[cls], cls))
    if 'name_note' in m:
        del m['name_note']
    d.setdefault('methods', {})[k] = m
    fp.write_text(json.dumps(d, indent=1, ensure_ascii=False), encoding='utf-8')
    print('[rehome] %s: %s → %s._sdtor_call_dtor' % (k, m.get('name_note', ''), cls))

print('[rehome] Actor.json 已摘除 3 条假 dtor; 归档 -> %s' % ARCH.name)
print('[done]')
