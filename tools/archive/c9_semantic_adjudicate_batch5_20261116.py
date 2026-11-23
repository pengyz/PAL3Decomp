#!/usr/bin/env python3
"""[C9语义裁定批量5 2026-11-16] 折叠载体网逐址裁定(用户令: 冲突必须签名语义裁定)。

裁定集:
1. 0x43de40 (HideAll×14|ReleaseTempStorage×8): 全部slot3认主=UIWnd系HideAll位折叠
   (RET 0 + 体=释放临时资源=面板隐藏语义) → slot3类ReleaseTempStorage×6正名HideAll
   (CCBRoleState前置骨架验证/CCBStage/RenderTarget/StateUI/UICoverFrm/UITitle_YXXX);
   CCBUI非槽引用摘除(自有slot3 HideAll=0x519510, 双HideAll同签=C8);
   CUtil无表类引用摘除(地址属折叠族非其成员)
2. UITitle_YXXX 幻表0x56B898摘除(=0x56B8A4-12普查伪影, 二进制实证[0..2]=邻接数据非骨架)
3. 0x43d7a0 (ForwardOnMessage×2|OnMessage×1): 全slot6=OnMessage位 → UIScene正名;
   UIListBox非槽引用按撞名摘除或正名
4. 0x43d920: UI3DCtrl.HideAll@slot3链律成立; ArraySlots无表Destroy引用摘除(台账)
5. 0x44e980 OnVisible@slot5(UIEmote双继承第二表)|Update@slot2(scScriptInstance)
   = 跨位合法折叠(各自谱系链律自洽) → CXX基线冻结(先例0x438100)
"""
import json
import copy
import glob
import os

LEDGER = 'data/status/pending/multi_claim_ledger.json'
ORPHAN = 'data/status/pending/orphan_entries_unknown_classes_20261116.json'


def load(fp):
    return json.load(open(fp, encoding='utf-8'))


def save(fp, d):
    json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)


def skeleton_check(cls, expect_root=('0x00445E70',)):
    """UIWnd骨架验证: 含目标址的表 slot0=ShowClipped(445e70)+slot4=Create(445b90) 双锚
    (slot6常被覆写故不作锚; 链经SceneObj→UIWnd亦成立, SceneObj表slot2/3/4/6与UIWnd同值)。"""
    d = load('data/annotations/structs/%s.json' % cls)
    for vt in (d.get('vtables') or []):
        slots = [str(s.get('addr') or '').upper() for s in (vt.get('slots') or [])]
        if '0X0043DE40' in slots:
            return (len(slots) >= 5 and slots[0] == '0X00445E70'
                    and slots[4] == '0X00445B90')
    return False


def main():
    # 1. 0x43de40 slot3 ReleaseTempStorage→HideAll (骨架前置验证)
    for cls in ('CCBRoleState', 'CCBStage', 'RenderTarget', 'StateUI', 'UICoverFrm', 'UITitle_YXXX'):
        fp = 'data/annotations/structs/%s.json' % cls
        d = load(fp)
        ms = d.get('methods') or {}
        e = ms.get('0x0043de40')
        assert e and e['name'] == 'ReleaseTempStorage', '%s 状态漂移: %s' % (cls, e and e['name'])
        if not skeleton_check(cls):
            print('骨架未过, 跳过 %s (排队)' % cls)
            continue
        e['name'] = 'HideAll'
        e['semantic_name'] = '%s::HideAll(void)' % cls
        e['evidence_level'] = 'verified'
        e['name_note'] = ('语义裁定batch5-20261116: 0x43de40=UIWnd系slot3折叠载体(19+表slot3值, '
                          'RET 0参, 体=释放临时资源=面板隐藏即释放语义) → 链律名HideAll; '
                          '原名ReleaseTempStorage=G2体读数命名')
        save(fp, d)
        print('正名 %s ReleaseTempStorage→HideAll' % cls)

    # 2. UITitle_YXXX 幻表摘除
    fp = 'data/annotations/structs/UITitle_YXXX.json'
    d = load(fp)
    vts = d['vtables']
    assert len(vts) == 2 and str(vts[0]['addr']).upper() == '0X0056B898'
    phantom = vts.pop(0)
    d.setdefault('_phantom_tables_removed', []).append({
        'addr': phantom['addr'], 'date': '2026-11-16',
        'evidence': '真表0x56B8A4-12字节视图; 二进制[0..2]=47e570/47dd60/4af760=前邻接数据非'
                    'UIWnd骨架(445e70首槽); 无ctor写证据(普查G1a双表伪影)'})
    save(fp, d)
    print('UITitle_YXXX 幻表0x56B898摘除')

    # 3. CCBUI/CUtil 非槽0x43de40引用摘除 → orphan
    orphan = load(ORPHAN)
    for cls, reason in (('CCBUI', '自有slot3 HideAll=0x519510, 双HideAll同签将触发C8'),
                        ('CUtil', '无表类, 地址属折叠族非其成员')):
        fp = 'data/annotations/structs/%s.json' % cls
        d = load(fp)
        ms = d.get('methods') or {}
        e = ms.get('0x0043de40')
        if e is None:
            print('%s 无0x43de40条目(已处理?)' % cls)
            continue
        orphan.setdefault('fold_family_0x43de40_refs', {})[cls] = {
            'was_name': e.get('name'), 'entry': copy.deepcopy(e), 'reason': reason}
        del ms['0x0043de40']
        save(fp, d)
        print('摘除 %s 非槽引用0x43de40(%s)' % (cls, e.get('name')))

    # 4. 0x43d7a0 ForwardOnMessage→OnMessage
    for cls, is_slot in (('UIScene', True), ('UIListBox', False)):
        fp = 'data/annotations/structs/%s.json' % cls
        d = load(fp)
        ms = d.get('methods') or {}
        e = ms.get('0x0043d7a0')
        assert e and e['name'] == 'ForwardOnMessage', cls
        # C8守卫: 类内已有OnMessage同签?
        collide = [x for x, e2 in ms.items()
                   if x != '0x0043d7a0' and e2.get('name') == 'OnMessage'
                   and e2.get('signature') == e.get('signature')]
        if collide:
            orphan.setdefault('fold_family_0x43d7a0_refs', {})[cls] = {
                'was_name': e['name'], 'entry': copy.deepcopy(e),
                'reason': '与既有OnMessage条目同签撞名'}
            del ms['0x0043d7a0']
            print('摘除 %s 非槽ForwardOnMessage引用(撞名%s)' % (cls, collide))
        else:
            e['name'] = 'OnMessage'
            e['semantic_name'] = '%s::OnMessage' % cls
            e['evidence_level'] = 'verified'
            e['name_note'] = ('语义裁定batch5-20261116: 0x43d7a0=slot6(OnMessage位)折叠载体'
                              '(CCBProtectWindow/UIScene表slot6值) → 链律名OnMessage; '
                              '原名ForwardOnMessage=体读数(转发即调用)')
        save(fp, d)
        print('0x43d7a0 %s 裁定完成' % cls)

    # 5. 0x43d920: ArraySlots非槽引用摘除
    fp = 'data/annotations/structs/ArraySlots.json'
    d = load(fp)
    ms = d.get('methods') or {}
    e = ms.get('0x0043d920')
    if e:
        orphan.setdefault('fold_family_0x43d920_refs', {})['ArraySlots'] = {
            'was_name': e.get('name'), 'entry': copy.deepcopy(e),
            'reason': '地址=UI3DCtrl表slot3(HideAll位)折叠; ArraySlots无表无链, 非其成员'}
        del ms['0x0043d920']
        save(fp, d)
        print('摘除 ArraySlots 非槽引用0x43d920(Destroy)')

    # 6. 台账: 摘除与折叠裁决
    led = load(LEDGER)
    have = {x['addr'] for x in led.get('adjudicated', [])}
    for addr, ans in (
        ('0x0043de40', 'UIWnd系slot3折叠载体19+表; 全认主正名HideAll; CCBUI/CUtil非槽引用摘除'),
        ('0x0043d7a0', 'slot6(OnMessage位)折叠; ForwardOnMessage正名OnMessage; 非槽引用按撞名处理'),
        ('0x0043d920', 'UI3DCtrl表slot3(HideAll位); ArraySlots非槽引用摘除'),
        ('0x0044e980', '跨位合法折叠: UIEmote双继承第二表slot5(OnVisible)+scScriptInstance'
                       'slot2(Update), 各自谱系链律自洽'),
    ):
        if addr not in have:
            led.setdefault('adjudicated', []).append({'addr': addr, 'answer': ans, 'adjudicated': True})
    save(LEDGER, led)
    save(ORPHAN, orphan)
    print('台账+orphan落账完成')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
