#!/usr/bin/env python3
"""[R1-T2 2026-11-18] 语义收敛战役 R1：CCBCamControl 池骨架落地 + Actor 28 伪语义名降级。

== A. CCBCamControl 池区骨架 (汇编 disp 直证, tools/probe_ccbcamcontrol_pool_20261118.py) ==
池区 [0x24e4, 0x68fb0) 六个子视图 (全部以原始汇编 disp 为准, hexrays 渲染借位漂移 -0x20/-0x40 不采信):
  0x3CFB8  UIParticle[12]  m_RenderQueue   ProcessRenderQueue(0x48e600): v12=98 循环界 12 次,
           步进 584B (VA=0x48e75x add esi,248h); UIParticle sizeof=584 (注解) 匹配;
           LoadTexture/SetSize/SetColor/SetAlpha/UpdateTransform/SetScale 方法链。
  0x4AF4C  int[4]          m_SelectRect    ProcessRenderQueue: [ecx+4AF48h]/[4AF50h]/[4AF54h]
           = x1,x2,y2 (x1+deltas); 屏幕选择矩形。
  0x5D9EC  UIButton[5]     m_SlotButtons   ShowAllSlots(0x4a9ed0): lea [esi+5D9ECh] 起
           stride 344B (VA=0x4a9f07 lea [esi+ecx*8+5D9ECh] 的 86*4=344); UIButton
           sizeof=344 匹配; sub_445E50 链表头操作。
  0x5F360  _BYTE[6040]     m_TabLists      ShowAllSlots: lea [esi+5F360h]/[esi+5F818h]
           stride 1208B (5F818-5F360=0x4B8); 5 页签 x 1208B; 对象类型未证 (UIListBox
           方法经此调 ClearAll/GetItem, 但 UIListBox=72B, 1208B 身份未定谳) → _BYTE 占位。
  0x5578   int             m_nCurPageTab   ShowAllSlots 语料锚 *(&m_nCurCamIdx+3057)=nVal
           (0x2594+3057*4=0x5578); 页签选择写入; 汇编未直接捕获, B 级待复核。
未名 gap 不落占位成员 (自然 gap 保留), 总账挂账 note。

== B. Actor 28 伪语义名降级 (archive/pseudo_semantic_names_20261118.json R1 批次) ==
28 名 (RoleParam0-3/CachedA/B/RoleState0/1/UIFlagA/B/AnimParam0/1/MatrixA-C/
MatrixParamA-C/ActionFlag1-3/CloneParamB/CloneFlag1/2/ModelParamA/B/RoleState1)
全部降级为 _todo_<off> 占位。裁定依据: 语料取证显示这些偏移大量为**内嵌子对象头**
(0x3c 虚调用+AllocObject / 0x40 UIQPushButton::LoadTexture+CCBUI::SetRect /
0x58 ARC_PlayerAtt::Create+UIItem::SetData / 0x1b0 g_RoleSlotBuf 数组 stride 352)——
需要"Actor 内嵌子对象身份战役"逐对象定谳类身份后方可正名; 伪语义形态先行消灭
(用户裁定: 语义名无效=与占位同效)。旧名→偏移映射全量存档。

用法: python3 tools/sem_conv_r1_cambtn_demote_20261118.py
"""
import json
import re
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
SDIR = REPO / 'data/annotations/structs'
ARCH = REPO / 'data/annotations/archive'

def ev(text):
    return {'evidence_level': 'A', 'source': text}

# ── A. CCBCamControl ──
cam_p = SDIR / 'CCBCamControl.json'
cam = json.loads(cam_p.read_text(encoding='utf-8'))
km = cam.setdefault('known_members', {})
new_members = {
    '0x3cfb8': {'name': 'm_RenderQueue', 'type': 'UIParticle[12]', **ev(
        '[A 级汇编 2026-11-18] ProcessRenderQueue VA=0x48e600: 循环 v12=98→12 次, '
        'VA=0x48e75x: add <reg>,248h 步进 584B; UIParticle sizeof=584 (注解对账); '
        'RenderTarget::LoadTexture/SetSize/SetColor/SetAlpha/UpdateTransform/SetScale '
        '方法链 (语料渲染别名, 对象=584B 粒子)')},
    '0x4af4c': {'name': 'm_SelectRect', 'type': 'int[4]', **ev(
        '[A 级汇编 2026-11-18] ProcessRenderQueue VA=0x48e606: mov esi,[ecx+4AF48h] '
        '(x1) / VA=0x48e60d: [ecx+4AF50h] (x2) / VA=0x48e615: [ecx+4AF54h] (y2), '
        'y1@0x4AF4C 隐含; CalcRenderDimensions(v2=x2-x1, v6=y2-y1) 消费')},
    '0x5d9ec': {'name': 'm_SlotButtons', 'type': 'UIButton[5]', **ev(
        '[A 级汇编 2026-11-18] ShowAllSlots VA=0x4a9eda: lea edi,[esi+5D9ECh]; '
        'VA=0x4a9f07: lea ecx,[esi+ecx*8+5D9ECh] (86*4=344 stride), 循环界 v3=5; '
        'UIButton sizeof=344 (注解对账); sub_445E50 链表头操作')},
    '0x5f360': {'name': 'm_TabLists', 'type': '_BYTE[6040]', **ev(
        '[A 级汇编 2026-11-18] ShowAllSlots VA=0x4a9f32/0x4a9f50: lea [esi+5F360h]/'
        '[esi+5F818h] stride 1208B (0x5F818-0x5F360=0x4B8), 5 页签; UIListBox::'
        'ClearAll/GetItem 虚调用经此 (对象有 vptr 但 1208B 身份未定谳, UIListBox=72B '
        '不符) → _BYTE 占位, 身份定谳挂账')},
    '0x5578': {'name': 'm_nCurPageTab', 'type': 'int', 'evidence_level': 'B', **{
        'source': '[B 级语料锚 2026-11-18] ShowAllSlots: *(&m_nCurCamIdx+3057)=nVal '
                  '(0x2594+3057*4=0x5578), 页签选择写入; 汇编未直接捕获, R1-T4 复核验证'}},
}
overlap_check = []
for off_s, m in new_members.items():
    off = int(off_s, 16)
    sz = {'UIParticle[12]': 7008, 'int[4]': 16, 'UIButton[5]': 1720,
          '_BYTE[6040]': 6040, 'int': 4}[m['type']]
    overlap_check.append((off, off + sz, m['name']))
overlap_check.sort()
for (a1, b1, n1), (a2, b2, n2) in zip(overlap_check, overlap_check[1:]):
    assert b1 <= a2, '重叠: %s[%#x,%#x) vs %s[%#x,%#x)' % (n1, a1, b1, n2, a2, b2)
# 与既有成员也不重叠 (0x2594 m_nCurCamIdx / 0x68fb0 m_pStage)
assert 0x2594 + 4 <= 0x5578 and 0x60910 <= 0x68fb0
km.update(new_members)
note_add = ('\n[R1 2026-11-18] 池区骨架落地: 渲染队列(0x3CFB8 UIParticle[12])/选择矩形'
            '(0x4AF4C)/槽按钮(0x5D9EC UIButton[5])/页签区(0x5F360 5x1208B 身份未定谳)/'
            '页签索引(0x5578 B级)。未名 gap (约 190KB: [0x24e4,0x5578)+[0x557c,0x3cfb8)+'
            '[0x3f8c8,0x4af4c)+[0x4af58,0x5d9ec)+[0x5eb4c,0x5f360)+[0x60910,0x68fb0)) '
            '自然保留挂账, 后续轮汇编普查。')
cam['members_note'] = (cam.get('members_note') or '') + note_add
cam_p.write_text(json.dumps(cam, indent=1, ensure_ascii=False), encoding='utf-8')
print('[R1-A] CCBCamControl: +5 池区成员 (重叠断言通过)')

# ── B. Actor 28 伪语义名降级 ──
actor_p = SDIR / 'Actor.json'
actor = json.loads(actor_p.read_text(encoding='utf-8'))
HARD = re.compile(r'^(_todo_\w*|_field_\w*|_gap_\w*|unk_\w*|slot_unk\w*|_nearby_\w*|_inline_\w*|stru_\w*|method_\w*|v\d+_slot_*)$', re.I)
def suspect(name):
    if HARD.match(name): return False
    if re.search(r'(Cached|Temp|Param|Flag|State|Val|Data|Info|Arg|Buf)[A-E]$', name): return True
    if re.search(r'(Cached|Temp|Param|Flag|State|Val|Arg|Buf)\d{1,3}$', name): return True
    if re.search(r'[a-z][A-D]$', name): return True
    return False

akm = actor.get('known_members') or {}
demoted = {}
for off_s, m in list(akm.items()):
    nm = str(m.get('name') or '')
    if suspect(nm):
        demoted[nm] = {'offset': off_s, 'type': m.get('type'),
                       'old_name': nm, 'evidence_level': m.get('evidence_level')}
        m['name'] = '_todo_%s' % off_s[2:] if off_s.startswith('0x') else '_todo_' + off_s
        m['source'] = (m.get('source') or '') + (
            ' | [R1 降级 2026-11-18] 原名 %s 为序号后缀伪语义 (语义=0), 语料取证显示'
            '该偏移涉内嵌子对象头(虚调用/AllocObject/UI构造), 需内嵌对象身份战役定谳后'
            '正名; 伪语义形态先行消灭(用户裁定语义名无效=占位同效)。' % nm)
if len(demoted) != 28:
    print('[R1-B] 预期 28 名, 实得 %d — 中止' % len(demoted))
    sys.exit(1)
actor_p.write_text(json.dumps(actor, indent=1, ensure_ascii=False), encoding='utf-8')

(ARCH / 'actor_pseudo_demotion_20261118.json').write_text(json.dumps({
    '_doc': 'Actor 28 伪语义名降级 R1 2026-11-18: 序号后缀名 → _todo_<off> 占位; '
            '正名挂账=Actor 内嵌子对象身份战役 (0x3c/0x40/0x58 等偏移涉内嵌多态对象, '
            '语料: 虚调用/AllocObject/UIPushButton::LoadTexture/ARC_PlayerAtt::Create)。',
    'demoted': demoted,
}, indent=1, ensure_ascii=False), encoding='utf-8')
print('[R1-B] Actor: 28 名降级 _todo_<off>, 台账 -> archive/actor_pseudo_demotion_20261118.json')
print('[done]')
