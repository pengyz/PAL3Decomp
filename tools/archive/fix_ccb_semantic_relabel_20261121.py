#!/usr/bin/env python3
"""[CCB 语义换牌 2026-11-21] 类名跟行为走: class-2→CCBUI, class-1→CCBUICtrl(假设标签), CCBProtectWindow回归真身。

证据结构(三线收敛才动牌——用户律: PDB参考非真值, 函数语义定名):
  线1 PAL3函数语义: class-2调用图=装配全部战斗子窗+五主角InitRoleDisplay串(景天/雪见/龙葵/紫萱/长卿,
      PAL3本体串)+胜负流程 = 战斗界面装配总管
  线2 PAL3本体串: D:\\Project\\PAL3\\Combat\\CBUI.cpp(源文件)+ui\\combat\\资源路径
  线3 PAL3A-PDB参考: CCBUI成员表≡class-2的57成员集; CCBUI::CCBUI(CCBSystem*)单参↔ctor 0x5160a0
      retn 4 + 分配点ProcNormalAttack传this; 完全dtor 0x516120写表0x5704A8@0x51613d+尾call
      ??1UIListBox@0x51615a(bases=UIListBox体证, 纠正旧UIFrameWnd误标)

换牌:
  S1 class-2(0x5704A8/2632B) → CCBUI.json (名 CCBUI, bases修正UIListBox)
  S2 class-1(0x5704C8/116B)  → CCBUICtrl.json (名 CCBUICtrl 假设标签+非权威声明)
  S3 CCBProtectWindow 回归真身: 6成员+ValidateSlot+96B(成员末端界, PAL3A参考, 待锚), 表/族/57成员已随CCBUI走
  S4 bases_adjudications: CCBUICtrl 新条目(ctor/dtor基构造链)

用法: python3 tools/fix_ccb_semantic_relabel_20261121.py [--dry]
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv
S = REPO / 'data' / 'annotations' / 'structs'
OPS = []

# 读三份
c1 = json.loads((S / 'CCBUI.json').read_text(encoding='utf-8'))              # class-1
c2 = json.loads((S / 'CCBProtectWindow.json').read_text(encoding='utf-8'))   # class-2
assert c2['binary_size'] == 2632 and c1['binary_size'] == 116

# ── S2: class-1 → CCBUICtrl ──────────────────────────────────────
c1['name'] = 'CCBUICtrl'
c1['_naming_note'] = (
    '类名标签 "CCBUICtrl" = 假设标签+非权威声明(20261121换牌): 语义角色=战斗控制窗条目构建'
    '(AddTask/CreateButton: UIListBox选中项→UIPushButton模板+现场构造CCBControlWindow+scrollbar资源)+'
    '五灵法阵脚本流(CreateImbibeNimbus/SetNimbusToNimbusControl→OpenScript@PalScript/'
    'WriteNimbusToPlayerMgr写回PlayerMgr)+攻击序列状态(Clear/Count)+动画(GravityDown/LineMove); '
    '真名待符号源。参考线: PAL3A-PDB记nimbus族为CCBUI方法(PAL3可能重构拆出——不可裁)。'
    '类身份二进制定谳: 表0x5704C8+分配0x74@0x51ccfb+dtor对0x519360(slot5)/0x519380+11槽成员图72+44=116')
c1['note'] = (c1.get('note') or '') + (
    ' | 换牌20261121: 本文件名CCBUICtrl(原CCBUI名让位于战斗界面装配总管=0x5704A8类, 语义+PDB参考收敛); '
    '本类语义角色=控制窗条目构建+五灵驱动(见_naming_note)')
ops1 = 'S2 class-1 → CCBUICtrl.json (假设标签+角色声明, 116B/表0x5704C8不变)'
OPS.append(ops1)

# ── S1: class-2 → CCBUI ──────────────────────────────────────────
c2['name'] = 'CCBUI'
c2['bases'] = [{"name": "UIListBox", "offset": 0}]
c2['_naming_note'] = (
    '类名标签 "CCBUI" 落定20261121(语义+参考三线收敛, 换牌自CCBProtectWindow): '
    '线1 PAL3函数语义=战斗界面装配总管(调用图建齐控制窗/攻击序列/战地属性/物品/仙术/技能/布阵/保护/'
    '战果/五灵/AI各子窗+五主角InitRoleDisplay串"Jingtian/Xuejian/Longkui/Zixuan/Changqing"∈PAL3本体+胜负流程); '
    '线2 PAL3本体串 D:\\Project\\PAL3\\Combat\\CBUI.cpp; '
    '线3 PAL3A-PDB参考: CCBUI成员表≡本类57成员集+CCBUI::CCBUI(CCBSystem*)单参↔ctor 0x5160a0 retn4+'
    '分配点ProcNormalAttack传this。类身份二进制定谳: 表0x5704A8+分配0xA48@0x51269a+dtor对0x516100(slot5)/'
    '0x516120+57成员访问谱。旧名CCBProtectWindow=name-pass槽标签误导(0x518b30等同族函数标签噪声)')
c2['note'] = (c2.get('note') or '') + (
    ' | 换牌20261121: 名CCBUI落地(三线收敛, 见_naming_note); bases修正UIListBox'
    '(完全dtor 0x516120尾call ??1UIListBox@0x51615a体证, 旧UIFrameWnd=legacy误标)')
ops2 = 'S1 class-2 → CCBUI.json (名CCBUI落地, bases修正UIListBox体证, 2632B/表0x5704A8/29方法/59成员)'
OPS.append(ops2)

# ── S3: CCBProtectWindow 回归真身 ────────────────────────────────
pw = {
    "name": "CCBProtectWindow",
    "binary_size": 96,
    "size_evidence": "临时界=成员末端(6成员@72..92+4=96); PAL3A参考同族=96B(CBUI.cpp); 待PAL3分配锚钉死",
    "base_size": 72,
    "bases": [{"name": "UIFrameWnd", "offset": 0}],
    "methods": {},
    "known_members": {},
    "_naming_note": (
        '类名标签 "CCBProtectWindow" 源自PAL3A-PDB参考(其CCBProtectWindow=96B/6成员/CBUI.cpp)——参考级。'
        '类身份: 本类真身=保护窗(6成员: m_pBack/m_pWHFace/m_pWPXFace/m_pWHLove/m_pWPXLove/m_pOk@72..92), '
        '20261121换牌回归真身: 旧注(0x5704A8表+0x516xxx族+57成员+2632锚)实为CCBUI内容(name-pass槽标签'
        '@CCBProtectWindow误导所致), 已随CCBUI名迁出。真表/真dtor/分配锚待裁。'
        '语义呼应: class-2的CreateProtectWindow条目即创建本类窗口(IsJingtianProtect@CCBRoleState=景天保护)')
}
# 6 protect成员抽回
allm = c2.get('known_members') or {}
protect_names = {'m_pBack', 'm_pWHFace', 'm_pWPXFace', 'm_pWHLove', 'm_pWPXLove', 'm_pOk'}
for off, mm in sorted(allm.items(), key=lambda kv: int(kv[0], 16)):
    if mm.get('name') in protect_names:
        pw['known_members'][off] = mm
assert len(pw['known_members']) == 6, len(pw['known_members'])
# ValidateSlot 留守(原注册残段, 无类证据, 惯性保留)
vs = c2.get('methods', {}).get('0x00449be0')
if vs:
    pw['methods']['0x00449be0'] = vs
pw['note'] = (
    ' | 换牌20261121: 回归真身(96B/6成员/ValidateSlot残段); '
    '真表/真dtor/真分配锚待裁——0x5704A8表+29方法+53成员已随CCBUI走')
OPS.append('S3 CCBProtectWindow 回归真身 (96B临时界/6成员/ValidateSlot残段; 表族成员随CCBUI)')

# ── S4: C11 裁决条目 ─────────────────────────────────────────────
adjp = REPO / 'data' / 'status' / 'bases_adjudications.json'
adj = json.loads(adjp.read_text(encoding='utf-8'))
adj['CCBUICtrl'] = {
    "bases": ["UIListBox"],
    "date": "2026-11-21",
    "ctor_evidence": "ctor 0x519310 call ??0UIListBox@0x43dcd0@0x51932d + 写表0x5704C8@0x51933c",
    "dtor_evidence": "删除式0x519360(slot5)→完全dtor 0x519380 call ??1UIListBox@0x43dd10@0x5193ba",
    "verdict_by": "本机idalib探针(probe_ccbui_identity系列)"
}
adj['CCBUI'] = {
    "bases": ["UIListBox"],
    "date": "2026-11-21",
    "ctor_evidence": "ctor 0x5160a0 call UIListBox族构造 + 写表0x5704A8@0x51613d(完全dtor内同址复证)",
    "dtor_evidence": "删除式0x516100(slot5)→完全dtor 0x516120 call ??1UIListBox@0x51615a + operator delete",
    "verdict_by": "本机idalib探针21(probe_ccbui_identity系列)"
}
if not DRY:
    adjp.write_text(json.dumps(adj, ensure_ascii=False, indent=1), encoding='utf-8')
OPS.append('S4 bases_adjudications: CCBUICtrl/CCBUI 新条目(基构造/基析构直调链)')

# ── 写盘 ─────────────────────────────────────────────────────────
if not DRY:
    (S / 'CCBUICtrl.json').write_text(json.dumps(c1, ensure_ascii=False, indent=1), encoding='utf-8')
    (S / 'CCBUI.json').write_text(json.dumps(c2, ensure_ascii=False, indent=1), encoding='utf-8')
    (S / 'CCBProtectWindow.json').write_text(json.dumps(pw, ensure_ascii=False, indent=1), encoding='utf-8')

for op in OPS:
    print(' ', op)
print('\ndone (dry=%s)' % DRY)
