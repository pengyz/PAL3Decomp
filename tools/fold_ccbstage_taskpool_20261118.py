#!/usr/bin/env python3
"""[折叠 2026-11-18] CCBStage 嵌合体成员 → m_TaskPool 扁平数组。

定谳链（原始汇编 disp，零标注依赖，tools/probe_ccbstage_layout_20261118.py 产出）：
  1. ForceDelTask(0x4fca00): `lea eax,[ecx+0A8h]` 基址 0xa8, `add eax,0A48h`
     stride 2632, `cmp edx,100h` 计数 256 → **this+0xa8 起 256×2632=673792B 任务池**。
     类尾 0xa48a8..0xa48c4(28B) 在池外（0xa48a8 int / 0xa48c0 uint m_dwAniFlagOver）。
  2. 三视图字段互洽（同址不同锚）:
     - 队列视图(GetProperCurAction 0x50ad30): token@376(0x178), 游标@392(0x188),
       条目@416(0x1A0)+96i: +0..15 四参数(nVal=回调fn*), +24 三快照, +36 blob44,
       +80 ProcProtect, +84 type, +88 occupied。
     - 槽视图(GetTask 0x4fca80 / GetTaskID 0x4fcbd0 / StartSubTask 0x4fce00):
       记录锚 this+120+2632g+80s (g<256, s<32 双循环界汇编直证):
       +0 gate(int==2) +8 ts(f32) +64 cb(fn*) +68 param(this'=this+param!)
       +80 state(GetTaskID写3/StartSubTask写4/dispatcher读{2,3,4}三方同址)
       +88 ts2(f32) +92 dur(f32) +104 activebyte +105 inuse +107 state2。
     - 组控制视图: +4 gate(int==3) +8 curSlot +2576 EndTask旗标(0x4fc9a0
       [ecx+eax*8+0AB8h]=2632n+2744) +2580 +2628 inuse(ForceDelTask [eax+0A44h]
       与 GetTask [edi] 同址)。
  3. 回调调用语义(GetTask 0x4fcb8e): `mov ecx,[edi+44h]; add ecx,esi; call
     [edi+40h]` = thiscall, this' = this+param —— 回调成员函数挂子对象。
  4. 现标注 63 成员中 [0xa8,0xa48a8) 全部落进池区间 = 三视图叠影嵌合体
     (m_nForceDelTask@0xa8 实为数组基址/m_bPaused@0xb0=组+8 游标槽/
     m_TaskQueue@0xac0=EndTask 旗标区/m_TaskArrC@0x118 CCBTaskSlot280[1] 虚构型)。
     m_nClearRoleAllTask@0xa0/m_nRoleSlot@0xa4 由 StartSubTask
     `mov eax,[ecx+0A0h]`/`[ecx+0A4h]` 汇编直证为真成员, 保留。

动作:
  - CCBStage.json: 删除 0xa8..0xa4898 全部嵌合成员, 合并为单一
    m_TaskPool _BYTE[673792] @0xa8 (evidence_level A, 汇编循环界直证);
    原 known_members 全文归档进池 note(members_note)。
  - structs/CCBTaskSlot280.json → archive/ccbtaskslot280_fictional_20261118.json
    (虚构型定谳: 0x118 锚来自叠影渲染非对象边界)。

用法: python3 tools/fold_ccbstage_taskpool_20261118.py
"""
import json
import shutil
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
CCB = REPO / 'data/annotations/structs/CCBStage.json'
SLOT = REPO / 'data/annotations/structs/CCBTaskSlot280.json'
ARCH = REPO / 'data/annotations/archive/ccbtaskslot280_fictional_20261118.json'

POOL_LO = 0xa8
POOL_HI = 0xa48a8
POOL_SIZE = POOL_HI - POOL_LO
assert POOL_SIZE == 673792, POOL_SIZE

VIEW_NOTE = (
    '三视图汇编目录(原始disp, tools/probe_ccbstage_layout_20261118.py 2026-11-18):\n'
    '[池] ForceDelTask(0x4fca00) lea [ecx+0A8h]+add 0A48h+cmp edx,100h → '
    '基址0xa8 stride2632 count256; 类尾池外28B(0xa48a8 int/0xa48c0 m_dwAniFlagOver)。\n'
    '[队列] GetProperCurAction(0x50ad30): token@376(0x178) 游标@392(0x188) '
    '条目@416(0x1A0)+96i: +0..15四参数(nVal=回调fn*经(int)cast传参) +24三快照'
    '(g_nCBRoleMoveTable 0x50/54/58) +36 blob44(qmemcpy pData 0x2C) +80 ProcProtect '
    '+84 type(2/3) +88 occupied=1。\n'
    '[槽] GetTask(0x4fca80)/GetTaskID(0x4fcbd0)/StartSubTask(0x4fce00): '
    '记录锚 this+120+2632g+80s(g<256,s<32循环界汇编直证): +0 gate(int==2) +8 ts '
    '+64 cb(fn*) +68 param(thiscall this%=this+param) +80 state(GetTaskID写3/'
    'StartSubTask写4/dispatcher读{2,3,4}三方同址互证) +88 ts2 +92 dur +104 active '
    '+105 inuse +107 state2。\n'
    '[组控] +4 gate(int==3) +8 curSlot(==4分支取X=s+1派发前槽回调) '
    '+2576 EndTask旗标(0x4fc9a0 [ecx+e*8+0AB8h]) +2580 +2628 inuse'
    '(ForceDelTask [eax+0A44h]≡GetTask [edi])。\n'
    '[回调] GetTask 0x4fcb8e mov ecx,[edi+44h]/add ecx,esi/call [edi+40h] = '
    'thiscall this%=this+param —— 成员回调挂子对象。\n'
    '[嵌合体清算] 原0xa8..0xa4898成员(m_nForceDelTask=池基址1B误注/m_bPaused='
    '组+8游标槽/m_TaskQueue=EndTask旗标区/m_TaskArrC CCBTaskSlot280[1]虚构型/'
    'm_TaskSlots _BYTE[96]=槽(0,0)+64锚片段...)全为三视图叠影, 已归档原文于'
    'archive/ccbtaskslot280_fictional_20261118.json。'
)

chimed = []
doc = json.loads(CCB.read_text(encoding='utf-8'))
km = doc['known_members']
for k in sorted(km, key=lambda x: int(x, 16)):
    off = int(k, 16)
    if POOL_LO <= off < POOL_HI:
        chimed.append(k)
if not chimed:
    print('[fold] no chimera members in [%#x,%#x) — nothing to do' % (POOL_LO, POOL_HI))
    sys.exit(0)

arch = {
    '_doc': 'CCBStage 嵌合体成员清算 2026-11-18: [0xa8,0xa48a8) 区间原逐成员标注'
            '为三视图叠影产物, 已折叠为 m_TaskPool 扁平数组。本文件为原文存档。',
    'folded_into': {'name': 'm_TaskPool', 'offset': hex(POOL_LO), 'size': POOL_SIZE},
    'members': {k: km[k] for k in chimed},
}
# 归档全文(嵌合成员 + CCBTaskSlot280 虚构型全文)
if SLOT.exists():
    arch['ccbtaskslot280'] = json.loads(SLOT.read_text(encoding='utf-8'))
ARCH.write_text(json.dumps(arch, indent=1, ensure_ascii=False), encoding='utf-8')

# 折叠: 删嵌合成员, 建池成员
for k in chimed:
    del km[k]
km[hex(POOL_LO)] = {
    'name': 'm_TaskPool',
    'type': '_BYTE[%d]' % POOL_SIZE,
    'source': '[A 级汇编直证 2026-11-18] ForceDelTask(0x4fca00) 循环界三合一直证: '
              '基址lea[ecx+0A8h]/stride add 0A48h/count cmp edx,100h; 类尾池外28B'
              '边界互证(0xa48a8/0xa48c0 池外) · 三视图字段目录见 members_note',
    'evidence_level': 'A',
}
doc['members_note'] = VIEW_NOTE

CCB.write_text(json.dumps(doc, indent=1, ensure_ascii=False), encoding='utf-8')

# CCBTaskSlot280 退役归档
if SLOT.exists():
    SLOT.unlink()

print('[fold] chimera members folded: %d (%s .. %s)' % (
    len(chimed), chimed[0], chimed[-1]))
print('[fold] pool member: m_TaskPool _BYTE[%d] @ %#x' % (POOL_SIZE, POOL_LO))
print('[fold] archive -> %s' % ARCH)
print('[fold] CCBTaskSlot280.json retired')
