#!/usr/bin/env python3
"""[C10首例重裁定 2026-11-16] RoleCameraCtrl 基归属+版面重建。

铁证链:
1. InitFrameUI@0x450a60 体首行 `UIFrameWnd::UIFrameWnd(this)` = 基类构造直调
   (继承铁证, vtable写表律调用侧) → 真基 = UIFrameWnd (非UIWnd, 原标注错)
2. 体访问 `(UITextArea*)((char*)this + 72)` = own成员 @+72 (UITextArea* 4B)
3. 尺寸算术: UIFrameWnd(72) + 4 = 76 = binary_size ✓ (CG_Scene跨度+20→+96三方互证)
4. 版面: 原known_members(+8 m_pVtable/m_type/m_time/m_targetdist/m_startyaw...)
   全部落+8..+68 = UIFrameWnd区内部 → census错型垃圾(相机语义名属他类), 摘至ledger
5. slot0 0x450d00 体=剪裁态检查+slot6调OnMessage(1000,flags,0)=ShowClipped模式
   → 链律名ShowClipped(原名ShowWindow=体读数误名)
"""
import json
import copy

FP = 'data/annotations/structs/RoleCameraCtrl.json'
LEDGER = 'data/status/pending/multi_claim_ledger.json'
ORPHAN = 'data/status/pending/orphan_entries_unknown_classes_20261116.json'


def main():
    d = json.load(open(FP, encoding='utf-8'))
    old_km = d.get('known_members') or {}

    # 1. 基归属重裁
    d['bases'] = [{'name': 'UIFrameWnd', 'offset': 0}]
    d['base_size'] = 72
    d['bases_note'] = ('重裁定20261116: InitFrameUI体首行UIFrameWnd::UIFrameWnd(this)=基类构造直调'
                       '(继承铁证); 尺寸算术UIFrameWnd(72)+4=76=bin_size(CG_Scene跨度三方互证); '
                       '原bases=[UIWnd]与版面矛盾(C10a抓捕)')

    # 2. known_members重建: 垃圾摘至orphan, 真成员+72
    orphan = json.load(open(ORPHAN, encoding='utf-8'))
    orphan.setdefault('census_misattributed_members', {})['RoleCameraCtrl'] = {
        'reason': '原known_members(+8..+64)全部落在UIFrameWnd区[0,72)内部=census错型'
                  '(相机语义名targetdist/startyaw属他类); 版面证据+72 UITextArea*',
        'members': copy.deepcopy(old_km)}
    d['known_members'] = {'0x48': {'name': 'm_pTextArea', 'type': 'UITextArea *',
                                   'evidence_level': 'verified',
                                   'note': 'InitFrameUI体访问(this+72)直证'}}

    # 3. 槽名链律
    ms = d.get('methods') or {}
    e = ms.get('0x00450d00')
    if e and e['name'] == 'ShowWindow':
        e['name'] = 'ShowClipped'
        e['semantic_name'] = 'RoleCameraCtrl::ShowClipped(int)'
        e['name_note'] = ('C10重裁定20261116链律: slot0位(UIWnd系ShowClipped位) + '
                          '体=剪裁态检查(+52)+slot6调OnMessage(1000,flags,0)=ShowClipped模式; '
                          '原名ShowWindow=体读数误名')
    e = ms.get('0x00450c90')
    if e and e['name'] == 'UpdatePosition':
        e['name'] = 'Update'
        e['semantic_name'] = 'RoleCameraCtrl::Update(int, int)'
        e['name_note'] = ('C10重裁定20261116链律: slot2位(Update BOOL(int,int)契约) → 链律名Update; '
                          '原名UpdatePosition=体读数; 待解异常: 体访问+244/+264超出bin_size 76, '
                          '疑hexrays错型或折叠加挂, 留L-TAILADDR批次复核')
    json.dump(d, open(FP, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    # 4. 台账
    led = json.load(open(LEDGER, encoding='utf-8'))
    have = {x['addr'] for x in led.get('adjudicated', [])}
    if 'RoleCameraCtrl' not in have:
        led['adjudicated'].append({'addr': 'RoleCameraCtrl', 'answer': '基归属重裁UIWnd→UIFrameWnd'
                                   '(基构造直调铁证+72/76尺寸算术); known_members重建', 'adjudicated': True})
    json.dump(led, open(LEDGER, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    json.dump(orphan, open(ORPHAN, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('RoleCameraCtrl: bases→[UIFrameWnd] base_size=72 known_members重建(1成员) '
          'ShowWindow→ShowClipped UpdatePosition→Update')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
