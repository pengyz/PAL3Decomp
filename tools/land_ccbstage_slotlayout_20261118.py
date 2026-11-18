#!/usr/bin/env python3
"""[落地 2026-11-18] CCBStage 任务池条目级布局 → CCBTaskSlot/CCBTaskGroup 嵌套类型。

定谳链（tools/probe_ccbstage_layout_20261118.py 原始汇编 + 全语料偏移普查）：
  槽记录 rec(s) = B+16+80s (B = this+0xa8+2632g)，13 字段四方互证：
    - cb@rec+0: dispatcher==3 派发(0x4fcb95 call [edi+0x40])；==4 与
      ProcFiveLienupFadeOut 比对(0x4fcb1a)；StartSubTask 锚(0x4fce29)
    - state@rec+16: GetTaskID 写3(0x4fcbf0)/StartSubTask 写4(0x4fce62)/
      dispatcher 读{2,3,4}(0x4fcac9)/GetTaskState 连续==4 扫描(0x4fcc2a 步80)
    - ts@rec+24: GetTaskID 写时钟(0x4fcbff)；StartSubTask/IsSubTaskFinished 读
    - maxWait@rec+28: dispatcher==2 now-ts(前槽)≥本值→派发(0x4fcb6c)
    - dur@rec+32: StartSubTask 超时强停(0x4fce4a)；IsSubTaskFinished ×0.25/×0.75
    - actionId@rec+36: dispatcher==4 → 写 slot0.arg0=B+20(0x4fcb17/3e)
    - active@40/registered@41/forceDone@43/turnState@64
  组级：id@0(ForceDelTask 0x4fca17)/state@4(0x4fca9c 门==3)/curSlot@8
    (GetTaskState 0x4fcc1e 进度上界 + dispatcher 0x4caf3 定位 slots[cs-1])/
    endFlag@2576(EndTask 0x4fc9ad)/delResult@2580(DelTask 0x4fc9f0)/
    inUse@2628(GetTask 0x4fca93 门==1 ≡ ForceDelTask 0x4fca0d 同址)
  边界收口：slots[32] = [16,2576) 恰抵 endFlag；池 256×2632 = [0xa8,0xa48a8)。

多态 arena 说明：组0 运行时为实例上下文复用区（GetProperCurAction 的
cursor@B(0)+224=slots[2]+48gap/token@208=slots[2].m_fDuration 位置/
roleIndex@284=slots[3]+28/UIPB 构造站跨组 3560+248k）——原 C++ 即 cast 叠印，
slot 字段名按任务视图起；组0 复用细节记 members_note 挂账。

用法: python3 tools/land_ccbstage_slotlayout_20261118.py
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
SDIR = REPO / 'data/annotations/structs'
CCB = SDIR / 'CCBStage.json'

def ev(text):
    return {'evidence_level': 'A', 'source': text}

SLOT = {
    'name': 'CCBTaskSlot',
    'binary_size': 80,
    'known_members': {
        '0x0': {'name': 'm_nTaskFn', 'type': 'int', **ev(
            '[A 级汇编 2026-11-18] 任务回调(int形态,调用方传 (int)CCBStage::ProcMagic 等)。'
            'dispatcher==3 派发 VA=0x4fcb95: call [edi+0x40]=本字段(ecx=this+[rec+4],push 0); '
            'dispatcher==4 VA=0x4fcb1a: 与 ProcFiveLienupFadeOut 比对; StartSubTask 锚 VA=0x4fce29: lea esi,[..+0xB8]')},
        '0x4': {'name': 'm_nTaskArg0', 'type': 'int', **ev(
            '[A] VA=0x4fcb8e: mov ecx,[edi+0x44] → this\'=this+本值 (==3 派发实参); '
            '==4 零检三元之一(0x4fcb29); slot0 本字段兼组级 actionId '
            '(dispatcher==4 VA=0x4fcb17: mov [edx-0x30]=B+20=slots[0]+4)')},
        '0x8': {'name': 'm_nTaskArg1', 'type': 'int', **ev(
            '[A] ==4 零检 VA=0x4fcb29: mov ecx,[eax-0x3Ch]')},
        '0xc': {'name': 'm_nTaskArg2', 'type': 'int', **ev(
            '[A] ==4 零检 VA=0x4fcb30: mov ecx,[eax-0x38h] (第三元 0x4fcb37)')},
        '0x10': {'name': 'm_nState', 'type': 'int', **ev(
            '[A] 四方同址互证: GetTaskID VA=0x4fcbf0 写3(任务已派发)/StartSubTask VA=0x4fce62 写4'
            '(完成或强停)/dispatcher VA=0x4fcac9 读{2,3,4}分支/GetTaskState VA=0x4fcc2a 从本址'
            '步进80 扫连续==4。语义: 2=等前置槽, 3=已派发运行, 4=完成')},
        '0x18': {'name': 'm_fStartTime', 'type': 'float', **ev(
            '[A] GetTaskID VA=0x4fcbff: fstp 本址=系统时钟([vptr+0x50]); '
            'StartSubTask VA=0x4fce47 与 IsSubTaskFinished 读 elapsed=now-本值')},
        '0x1c': {'name': 'm_fMaxWait', 'type': 'float', **ev(
            '[A] dispatcher==2 分支 VA=0x4fcb50: fld 本址 与 flt_56A644 比对(<0 疑禁用); '
            'VA=0x4fcb6c: now-ts(前槽) ≥ 本值 → GetTaskID 派发本槽(链式等待超时)')},
        '0x20': {'name': 'm_fDuration', 'type': 'float', **ev(
            '[A] StartSubTask VA=0x4fce4a: now-ts ≥ 本值 → 强停 state=4; '
            'IsSubTaskFinished: 本值×0.25 与 ×0.75 为回合推进里程碑阈值')},
        '0x24': {'name': 'm_nActionId', 'type': 'int', **ev(
            '[A] dispatcher==4 VA=0x4fcb09: v7=本值(前槽cs-1) → 写组头 slots[0].m_nTaskArg0(B+20); '
            'fallback VA=0x4fcb3e: 前二槽(cs-2)同字段(条件: 前槽回调==ProcFiveLienupFadeOut 且三参全零)')},
        '0x28': {'name': 'm_bActive', 'type': 'unsigned char', **ev(
            '[A] dispatcher 顶门 VA=0x4fcab1: mov al,[edi+0x68]=本字节, ==0 → break '
            '(槽未登记则跳过该组)')},
        '0x29': {'name': 'm_bRegistered', 'type': 'unsigned char', **ev(
            '[A] StartSubTask VA=0x4fce20 读/VA=0x4fce32 写1; IsSubTaskFinished 同址: '
            '0→1 时同时清 m_nTurnState (首访初始化对)')},
        '0x2b': {'name': 'm_bForceDone', 'type': 'unsigned char', **ev(
            '[A] StartSubTask VA=0x4fce3c: cmp 本字节,1 → 直接 state=4 强停'
            '(外部强制结束标志, SetForceFinishThrowingWeapon 族写入)')},
        '0x40': {'name': 'm_nTurnState', 'type': 'int', **ev(
            '[A] IsSubTaskFinished: m_bRegistered 0→1 时清零; 低字节作 EndTurnAndAdvance '
            '第5实参(回合状态码)')},
    },
}

GROUP = {
    'name': 'CCBTaskGroup',
    'binary_size': 2632,
    'known_members': {
        '0x0': {'name': 'm_nTaskId', 'type': 'int', **ev(
            '[A] ForceDelTask VA=0x4fca17: cmp ecx(nIndex),[eax]=本字段 (组任务标识匹配)')},
        '0x4': {'name': 'm_nState', 'type': 'int', **ev(
            '[A] GetTask 组门 VA=0x4fca9c: [edi-0xA40]==3 才扫槽; dispatcher==4 写4 '
            'VA=0x4fcaf9; DelTask VA=0x4fc9e1 读==4')},
        '0x8': {'name': 'm_nCurSlot', 'type': 'int', **ev(
            '[A] GetTaskState VA=0x4fcc1e: v6=本值, ≤0 即组完成, >0 时从 slots[0].m_nState '
            '步进80 扫连续==4 上界=本值(进度); dispatcher==4 VA=0x4fcaf3 读 → 定位 '
            'slots[cs-1] 取回调 (cs=下一分配槽索引)')},
        '0x10': {'name': 'm_Slots', 'type': 'CCBTaskSlot[32]', **ev(
            '[A] 槽流 rec(s)=B+16+80s: cb@rec+0=dispatcher[edi+0x40](VA=0x4fcb95); '
            'state@rec+16=GetTaskID 写址(VA=0x4fcbf0 [A+0xC8])+GetTaskState 扫描步长80 '
            '四方互证; slots[32] 恰抵 m_nEndFlag@2576 (16+2560=2576 边界收口)')},
        '0xa10': {'name': 'm_nEndFlag', 'type': 'int', **ev(
            '[A] EndTask VA=0x4fc9ad: mov eax,[ecx+2632n+0xAB8] 返回本值; 写入方未定谳挂账')},
        '0xa14': {'name': 'm_nDelResult', 'type': 'int', **ev(
            '[A] DelTask VA=0x4fc9f0: 组 m_nState==4 时经出参返回本值 (删除结果载荷); '
            '写入方未定谳挂账')},
        '0xa44': {'name': 'm_bInUse', 'type': 'unsigned char', **ev(
            '[A] GetTask 组门 VA=0x4fca93: byte==1 才处理; ForceDelTask VA=0x4fca0d '
            '[eax+0xA44] 同址互证 (双视图同字节)')},
    },
}

doc = json.loads(CCB.read_text(encoding='utf-8'))
km = doc['known_members']
if '0xa8' not in km or km['0xa8'].get('name') != 'm_TaskPool':
    print('[land] 0xa8 成员非 m_TaskPool — 状态异常, 中止')
    sys.exit(1)

km['0xa8'] = {
    'name': 'm_TaskGroups',
    'type': 'CCBTaskGroup[256]',
    'source': '[A 级汇编直证 2026-11-18] ForceDelTask(0x4fca00) 循环界三合一直证: '
              '基址lea[ecx+0A8h]/stride add 0A48h/count cmp edx,100h; 256×2632=673792 '
              '恰收口于类尾池外28B; 条目级布局见 CCBTaskGroup.json/CCBTaskSlot.json',
    'evidence_level': 'A',
}

doc['members_note'] = (
    '任务池四视图汇编目录(原始disp, tools/probe_ccbstage_layout_20261118.py + '
    'tools/land_ccbstage_slotlayout_20261118.py 2026-11-18):\n'
    '[组视图] B=0xa8+2632g: id@0/state@4/curSlot@8/slots@16..2576/endFlag@2576/'
    'delResult@2580/inUse@2628。slot0.m_nTaskArg0 兼组级 actionId '
    '(dispatcher==4 写 B+20=slots[0]+4)。\n'
    '[槽视图] rec(s)=B+16+80s(80B): cb/arg0..2/state(2=等前置,3=运行,4=完成)/'
    'ts/maxWait/dur/actionId/active/registered/forceDone/turnState — 链式任务: '
    '槽 s state==2 等前槽 state==4 或超时(maxWait)后 GetTaskID 派发。\n'
    '[回调] dispatcher==3: call [rec.cb] this\'=this+rec.arg0; ==4: 前槽回调'
    '==ProcFiveLienupFadeOut 且三参全零 → actionId 取前二槽。\n'
    '[组0 多态复用挂账] 组0 运行时为实例上下文区(原 C++ cast 叠印, 布局未定谳): '
    'GetProperCurAction cursor@B0+224(=slots[2]+48 gap)/token@208(渲染为 '
    'slots[2].m_fDuration 位)/roleIndex@284(=slots[3]+28)/队列条目 96B×26 '
    '@248+96i(占 slots[2..31] 区); UIPB(248B)构造站跨组 3560+248k 周期1008 '
    '(=248×3+264, 页基3560/4568/5576/6584/7592)。这些访问将渲染为组0 slot '
    '字段名 — 字节精确, 语义按任务视图, 待独立战役定谳。'
)

CCB.write_text(json.dumps(doc, indent=1, ensure_ascii=False), encoding='utf-8')
(SDIR / 'CCBTaskSlot.json').write_text(
    json.dumps(SLOT, indent=1, ensure_ascii=False), encoding='utf-8')
(SDIR / 'CCBTaskGroup.json').write_text(
    json.dumps(GROUP, indent=1, ensure_ascii=False), encoding='utf-8')

# 布局自检
slot_fields = sorted((int(k, 16), v['name']) for k, v in SLOT['known_members'].items())
print('[land] CCBTaskSlot fields:', slot_fields)
print('[land] CCBTaskGroup: slots[32]@[16,2576) endFlag@2576 delResult@2580 inUse@2628')
print('[land] CCBStage.m_TaskGroups = CCBTaskGroup[256] @0xa8 (673792B)')
print('[done]')
