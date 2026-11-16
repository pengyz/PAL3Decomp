#!/usr/bin/env python3
"""[C10复核修复 2026-11-17] 对抗复核(agent_34c483be)P0裁决落地——真基链重建。

独立验证已过(本机capstone):
- 0x445AA0=UIWnd ctor(call 0x432660构造m_childs + 存表0x56AEC8)
- 0x445B20(slot5)=deleting dtor(call 0x445B40 complete + 0x541D10 operator delete)
- 0x43DCD0=UIListBox ctor(call 0x445AA0 + 存表0x56AD20) → UIListBox:UIWnd=72B骨架
修复项:
1. UIWnd ctor/dtor角色归正(语料系统性错名: 0x445AA0误名ClearSubArraySlot/0x445B40
   实为complete dtor误名_UIWnd; dtor单点律→slot5 deleting dtor承~UIWnd, complete
   dtor伴生条目摘orphan)
2. UIListBox chimera矫正: binary_size 1208→72(ctor 3指令只构72B骨架;
   CCBRoleState ctor own写从0x48起=UIListBox恰72B旁证); ≥0x48的23成员=chimera尾部
   摘orphan(真实字段属他类, 身份待定)
3. CCBRoleState: bases=[UIListBox](ctor 0x456AB0→call 0x43DCD0铁证; dtor 0x456B80→
   0x43DD10→0x445B40链) base_size=72; <0x48幽灵成员摘orphan; 角色归正(0x456AB0
   Init_6AB0→ctor/0x457070误名ctor→OnMessage(slot6 override RET 12)/0x456B60
   _scalar_dtor_6B60→~CCBStage...); 第二表0x5708E8+0x5362F0/0x5363C0/0x5368A0=
   兄弟类摘orphan(其ctor 0x536260存表)
4. CCBStage: bases=[UIListBox](真ctor 0x51D710→call 0x43DCD0@0x51D732; 真dtor
   0x51DDA0→call 0x43DD10@0x51DFB4) base_size=72; <0x58幽灵摘orphan; 角色归正
   (0x51D710 Initialize→CCBStage/0x4FB9A0误名CCBStage→InitFromDescriptor
   [caller-delivered表+[4]=[arg+0x10]实证]/0x51DDA0 ShowWindow→complete dtor摘orphan单点律)
5. CCBPanelSlot: 幽灵成员[0,0xB4)摘orphan(复核ctor链: 0x10-0x1C=UIWnd::m_rect/
   0x20=m_pfather/0x24-0x34=m_childs/0x5C=UIFrameContainer字段; 中间类0x56AE10
   身份未定谳, bases重建待其建档)
RenderTarget: 延后(两类chimera拆分手术, 本轮不动)。
"""
import json
import copy

ORPHAN = 'data/status/pending/orphan_entries_unknown_classes_20261116.json'
LEDGER = 'data/status/pending/multi_claim_ledger.json'


def load(fp):
    return json.load(open(fp, encoding='utf-8'))


def save(fp, d):
    json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)


def purge_members(d, cls, lo, hi, reason):
    """摘[lo,hi)成员至orphan。"""
    km = d.get('known_members') or {}
    ghosts = {k: v for k, v in km.items()
              if lo <= int(str(k).split('_')[0], 16) < hi}
    if ghosts:
        orphan = load(ORPHAN)
        orphan.setdefault('base_region_ghost_members', {})['%s:%d-%d' % (cls, lo, hi)] = {
            'reason': reason, 'members': copy.deepcopy(ghosts)}
        save(ORPHAN, orphan)
        for k in ghosts:
            del km[k]
        d['known_members'] = km
    return len(ghosts)


def main():
    n_fix = 0

    # ── 1. UIWnd 角色归正 ──
    fp = 'data/annotations/structs/UIWnd.json'
    d = load(fp)
    ms = d['methods']
    assert ms['0x00445b40']['name'] == '_UIWnd'
    assert ms['0x00445b20']['name'] == '_scalar_dtor_5B20'
    assert '0x00445aa0' not in ms
    # complete dtor伴生条目摘orphan(单点律)
    orphan = load(ORPHAN)
    orphan.setdefault('companion_dtor_entries', {})['UIWnd:0x00445b40'] = {
        'was_name': '_UIWnd', 'entry': copy.deepcopy(ms['0x00445b40']),
        'reason': 'complete dtor(被slot5 deleting dtor 0x445B20调用, 本机capstone实证); '
                  '语料误名_UIWnd; dtor单点律=slot5 deleting dtor承~UIWnd, 伴生不进清单'}
    del ms['0x00445b40']
    # slot5 deleting dtor正名
    e = ms['0x00445b20']
    e['name'] = '~UIWnd'
    e['semantic_name'] = 'UIWnd::~UIWnd(del)'
    e['sig_model']['return'] = 'void *'
    e['signature'] = 'void * __thiscall(int)'
    e['evidence_level'] = 'verified'
    e['name_note'] = ('角色归正20261117: slot5 deleting dtor(体=call 0x445B40 complete dtor '
                      '+ call 0x541D10 operator delete, 本机capstone实证); '
                      '原名_scalar_dtor_5B20=N12形')
    # ctor补条目
    ms['0x00445aa0'] = {
        'name': 'UIWnd', 'evidence_level': 'verified',
        'semantic_name': 'UIWnd::UIWnd(void)',
        'sig_model': {'return': 'void', 'cc': 'thiscall', 'params': [],
                      'varargs': False, 'pending': False},
        'signature': 'void __thiscall()',
        'name_note': ('ctor归正20261117: 体=call 0x432660(构造m_childs@+0x24) + 存表'
                      '0x56AEC8(本机capstone实证); 语料误名ClearSubArraySlot; '
                      '0x445B40为dtor非ctor(语料ctor/dtor名标反)')}
    save(fp, d)
    n_fix += 3
    print('UIWnd: +ctor 0x445AA0, slot5→~UIWnd, complete dtor 0x445B40摘orphan')

    # ── 2. UIListBox chimera矫正 ──
    fp = 'data/annotations/structs/UIListBox.json'
    d = load(fp)
    assert d['binary_size'] == 1208
    d['binary_size'] = 72
    d['size_note'] = ('chimera矫正20261117: 1208→72。证据=ctor 0x43DCD0仅3指令(call 0x445AA0'
                      'UIWnd ctor+存表0x56AD20, 本机capstone实证, 无字段构造) + '
                      'CCBRoleState ctor own字段写从0x48起(基区恰72B旁证); '
                      '原1208=chimera(72B骨架+他类字段)')
    n = purge_members(d, 'UIListBox', 0x48, 0x7FFFFFFF,
                      'chimera尾部(>72B): m_scrollbar/m_numcol/m_column等真实字段属他类'
                      '(UIListBox ctor 0x43DCD0仅构72B骨架), 身份待定谳')
    save(fp, d)
    n_fix += 1
    print('UIListBox: binary_size 1208→72, 摘chimera尾部%d成员' % n)

    # ── 3. CCBRoleState ──
    fp = 'data/annotations/structs/CCBRoleState.json'
    d = load(fp)
    ms = d['methods']
    d['bases'] = [{'name': 'UIListBox', 'offset': 0}]
    d['base_size'] = 72
    d['bases_note'] = ('真基链重建20261117(复核P0-2): bases=[UIListBox]。铁证=ctor 0x456AB0'
                       'call 0x43DCD0(UIListBox ctor, 语料自证UIListBox::UIListBox(this))'
                       '+dtor 0x456B80→0x43DD10(UIListBox dtor)→0x445B40(UIWnd dtor)链; '
                       '原bases=[SceneObj(1784)]与[UIWnd]均为census错挂(摘除正确)')
    n = purge_members(d, 'CCBRoleState', 0, 0x48,
                      '幽灵基区条目([0,0x48)=[vfptr+UIWnd 68B+UIListBox m_selcolor]): '
                      'm_sCombatDialog@0x0等与ctor写入矛盾(真ctor写own从0x48起)')
    # 兄弟类条目摘除
    sib = {}
    for a in ('0x5362f0', '0x5363c0', '0x5368a0'):
        if a in ms:
            sib[a] = copy.deepcopy(ms[a])
            del ms[a]
    vt2 = [v for v in d.get('vtables') or [] if str(v.get('addr')).upper() == '0X005708E8']
    if vt2:
        d['vtables'] = [v for v in d['vtables'] if str(v.get('addr')).upper() != '0X005708E8']
        orphan2 = load(ORPHAN)
        orphan2.setdefault('sibling_class_0x5708e8', {})['from_CCBRoleState'] = {
            'reason': '第二表0x5708E8+方法0x5362F0/0x5363C0/0x5368A0属兄弟类'
                      '(其ctor 0x536260存表@0x5362CE, 仅两处写入; 复核P1)', 'vtable': copy.deepcopy(vt2[0]),
            'methods': sib}
        save(ORPHAN, orphan2)
    elif sib:
        orphan2 = load(ORPHAN)
        orphan2.setdefault('sibling_class_0x5708e8', {})['from_CCBRoleState'] = {
            'reason': '兄弟类方法摘除(复核P1)', 'methods': sib}
        save(ORPHAN, orphan2)
    # 角色归正
    assert ms['0x00456ab0']['name'] == 'Init_6AB0'
    ms['0x00456ab0']['name'] = 'CCBRoleState'
    ms['0x00456ab0']['semantic_name'] = 'CCBRoleState::CCBRoleState(void)'
    ms['0x00456ab0']['name_note'] = ('ctor归正20261117: 体首行call 0x43DCD0(UIListBox ctor)+'
                                     '存表0x56B364+own字段写0x48/0x4C/0x50/0x54(复核实证); '
                                     '原名Init_6AB0=N12形')
    if ms.get('0x00457070', {}).get('name') == 'CCBRoleState':
        e = ms['0x00457070']
        e['name'] = 'OnMessage'
        e['semantic_name'] = 'CCBRoleState::OnMessage(int, int, int)'
        e['name_note'] = ('角色归正20261117: slot6位(OnMessage位, RET 12=3参与根契约一致); '
                          '原误名CCBRoleState(ctor错标)')
    if ms.get('0x00456b60', {}).get('name') == '_scalar_dtor_6B60':
        e = ms['0x00456b60']
        e['name'] = '~CCBRoleState'
        e['semantic_name'] = 'CCBRoleState::~CCBRoleState(del)'
        e['name_note'] = 'slot5 deleting dtor正名20261117(原名N12形)'
    save(fp, d)
    n_fix += 1
    print('CCBRoleState: bases=[UIListBox] base_size=72, 摘幽灵%d+兄弟类方法%d, 角色归正'
          % (n, len(sib)))

    # ── 4. CCBStage ──
    fp = 'data/annotations/structs/CCBStage.json'
    d = load(fp)
    ms = d['methods']
    d['bases'] = [{'name': 'UIListBox', 'offset': 0}]
    d['base_size'] = 72
    d['bases_note'] = ('真基链重建20261117(复核P0-3): bases=[UIListBox]。铁证=真ctor 0x51D710'
                       'call 0x43DCD0(UIListBox ctor)@0x51D732+真dtor 0x51DDA0 call 0x43DD10'
                       '(UIListBox dtor)@0x51DFB4; 原0x4FB9A0=blob reset非ctor(误名CCBStage)')
    n = purge_members(d, 'CCBStage', 0, 0x58,
                      '幽灵基区条目(m_pCBSystem@0x0等7个指针字段, [0,0x58)=[vfptr+UIWnd+'
                      'UIListBox m_selcolor]: 与真ctor 0x51D710字段构造序矛盾')
    assert ms['0x0051d710']['name'] == 'Initialize'
    ms['0x0051d710']['name'] = 'CCBStage'
    ms['0x0051d710']['semantic_name'] = 'CCBStage::CCBStage(void)'
    ms['0x0051d710']['name_note'] = ('ctor归正20261117: 体=call 0x43DCD0(UIListBox ctor)+30+字段'
                                     '依序构造(0x168/0x200/0x298/0x330[6×0x98]...)+存表0x5705D0'
                                     '(复核实证); 原名Initialize=体读数')
    assert ms['0x004fb9a0']['name'] == 'CCBStage'
    ms['0x004fb9a0']['name'] = 'InitFromDescriptor'
    ms['0x004fb9a0']['semantic_name'] = 'CCBStage::InitFromDescriptor(int)'
    ms['0x004fb9a0']['name_note'] = ('角色归正20261117: 非ctor——体=rep stosd清零+[0]=arg'
                                     '(caller-delivered表)+[4]=[arg+0x10](描述符初始化模式, '
                                     '本机capstone实证); 原误名CCBStage(与真ctor 0x51D710让位)')
    # complete dtor伴生摘orphan(单点律; slot5=0x51DD80已承~CCBStage)
    if ms.get('0x0051dda0', {}).get('name') == 'ShowWindow':
        orphan = load(ORPHAN)
        orphan.setdefault('companion_dtor_entries', {})['CCBStage:0x0051dda0'] = {
            'was_name': 'ShowWindow', 'entry': copy.deepcopy(ms['0x0051dda0']),
            'reason': 'complete dtor(体=存表0x5705D0+逆序析构+call 0x43DD10 UIListBox dtor'
                      '@0x51DFB4, 复核实证); 语料误名ShowWindow; dtor单点律伴生摘除'}
        del ms['0x0051dda0']
        save(ORPHAN, orphan)
    save(fp, d)
    n_fix += 1
    print('CCBStage: bases=[UIListBox] base_size=72, 摘幽灵%d, 角色归正×3' % n)

    # ── 5. CCBPanelSlot 幽灵成员摘除 ──
    fp = 'data/annotations/structs/CCBPanelSlot.json'
    d = load(fp)
    n = purge_members(d, 'CCBPanelSlot', 0, 0xB4,
                      '幽灵基区条目(复核P0-1 ctor链: CCBPanelSlot真链=本类:中间类0x56AE10:'
                      'UIFrameContainer:UIWnd, 基区[0,0xB4); 0x10-0x1C=UIWnd::m_rect/'
                      '0x20=m_pfather/0x24-0x34=m_childs/0x5C=UIFrameContainer字段; '
                      '原注解名m_nDimH等=decomp循环产物)')
    d['bases_note'] = ('真链20261117(复核P0-1): CCBPanelSlot:中间类(表0x56AE10, ctor 0x442E10'
                       ', 身份未定谳):UIFrameContainer:UIWnd(ctor链0x443190→0x442E10→0x4422E0'
                       '→0x445AA0全实证); bases重建待中间类建档; 槽值共享=真继承非ICF折叠'
                       '(前判修正)')
    save(fp, d)
    n_fix += 1
    print('CCBPanelSlot: 摘幽灵%d, bases重建待中间类0x56AE10建档' % n)

    # 台账
    led = load(LEDGER)
    have = {x['addr'] for x in led.get('adjudicated', [])}
    for addr, ans in (
        ('0x00445aa0', 'UIWnd ctor归正(存表0x56AEC8+m_childs构造实证; 语料ctor/dtor标反修正)'),
        ('0x00445b40', 'UIWnd complete dtor归正(被slot5 0x445B20调用; 伴生摘orphan)'),
        ('0x0043dcd0', 'UIListBox ctor确认(3指令=72B骨架; UIListBox 1208→72 chimera矫正)'),
        ('0x00456ab0', 'CCBRoleState真ctor(call 0x43DCD0; bases=[UIListBox]重建)'),
        ('0x0051d710', 'CCBStage真ctor(call 0x43DCD0; 0x4FB9A0为blob reset非ctor)'),
        ('0x004867f0', 'RenderTarget真ctor(call 0x43DCD0; 拆分手术延后)'),
    ):
        if addr not in have:
            led['adjudicated'].append({'addr': addr, 'answer': ans, 'adjudicated': True})
    save(LEDGER, led)
    print('台账落账完成; 总修复项: %d' % n_fix)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
