#!/usr/bin/env python3
"""[C9血统批量2 2026-11-16] 多主争夺裁决: 名盗条目归真/摘除+orphan保全+台账落账。

机器码写表实证链:
- 0x444ac0 写0x56AE84 = CCBResultWindow表 → complete dtor归真(冒领~UIFrameWnd_Full摘)
- 0x43be30 写0x56ACD8 ≠ CCBResultWindow表 → 名盗#6(真主=0x56acd8未知类), 摘除
- 0x442e80 写0x56AE10 / 0x442e60=其对dtor / 0x442e90=0x56AE10表slot1 → 未知类(ctor 0x4423df
  间接构造无直调), 摘除保全
- 0x443530 写表空(调complete dtor型) → 同簇摘除保全
- 0x442420 五主裁定: UIFrameContainer(slot3=0x442420实证)+CCBPanelSlot+CCBResultWindow
  → HideAll(链律); UIWnd/UIFrameWnd表内无此址 → 陈年误录摘除
- 0x4431b0 = CCBPanelSlot表slot5值 → UIWnd冒领_sdtor_call_dtor摘除
全部摘除条目保全至 data/status/pending/orphan_entries_unknown_classes_20261116.json
"""
import json
import copy

ORPHAN = 'data/status/pending/orphan_entries_unknown_classes_20261116.json'
LEDGER = 'data/status/pending/multi_claim_ledger.json'


def load(fp):
    return json.load(open(fp, encoding='utf-8'))


def save(fp, d):
    json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)


orphan = {'date': '2026-11-16',
          'note': '未知类条目保全(0x56ae10/0x56acd8类无标注文件, ctor间接构造无直调; '
                  '身份定谳后按证据归建类文件)',
          'unknown_class_0x56ae10': {'evidence': '表[445e70,442e90,442ff0,442420,445b90,442e60,445d10] '
                                               'UIWnd骨架; ctor=0x4423df(成员清零+[esi]=表); '
                                               'complete dtor 0x442e80机器码写本表',
                                     'entries': {}},
          'unknown_class_0x56acd8': {'evidence': '表邻接UIFrameWnd(0x56acb8+0x20); complete dtor '
                                               '0x43be30机器码写本表',
                                     'entries': {}}}

# (file, addr, 期望现名, 去向)
moves = [
    ('data/annotations/structs/UIFrameWnd.json', '0x00444ac0', '~UIFrameWnd_Full', 'CCBResultWindow已落真条目'),
    ('data/annotations/structs/UIFrameWnd.json', '0x00442e80', '~UIFrameWnd', 'orphan:0x56ae10'),
    ('data/annotations/structs/UIFrameWnd.json', '0x00442e60', '_scalar_dtor_2E60', 'orphan:0x56ae10'),
    ('data/annotations/structs/UIFrameWnd.json', '0x00442e90', 'RenderWithTexture', 'orphan:0x56ae10'),
    ('data/annotations/structs/UIFrameWnd.json', '0x00443530', '_scalar_dtor_3530', 'orphan:0x56ae10簇'),
    ('data/annotations/structs/UIFrameWnd.json', '0x00442420', 'v1_slot_3', '摘除(表内无此址, N12占位)'),
    ('data/annotations/structs/UIWnd.json', '0x00442420', 'Destroy_2420', '摘除(表内无此址)'),
    ('data/annotations/structs/UIWnd.json', '0x004431b0', '_sdtor_call_dtor', 'CCBPanelSlot已落真条目'),
    ('data/annotations/structs/UIWnd.json', '0x00442e90', 'RenderWithTexture', 'orphan:0x56ae10'),
    ('data/annotations/structs/UIWnd.json', '0x00442e60', '_scalar_dtor_2E60', 'orphan:0x56ae10'),
    ('data/annotations/structs/CCBResultWindow.json', '0x0043be30', '~CCBResultWindow', 'orphan:0x56acd8'),
]

for fp, addr, expect, dest in moves:
    d = load(fp)
    ms = d.get('methods') or {}
    e = ms.get(addr)
    assert e is not None, '%s 缺 %s' % (fp, addr)
    assert e.get('name') == expect, '%s %s 名漂移: %s ≠ %s' % (fp, addr, e.get('name'), expect)
    bucket = orphan['unknown_class_0x56acd8']['entries'] if '0x56acd8' in dest else \
        orphan['unknown_class_0x56ae10']['entries']
    bucket[addr] = {'from_class': fp.split('/')[-1][:-5], 'was_name': expect, 'entry': copy.deepcopy(e),
                    'dest': dest}
    del ms[addr]
    save(fp, d)
    print('摘除 %s %s(%s) → %s' % (fp.split('/')[-1], addr, expect, dest))

# UIFrameContainer: slot3实证 → HideAll正名
fp = 'data/annotations/structs/UIFrameContainer.json'
d = load(fp)
e = d['methods']['0x00442420']
assert e['name'] == 'Destroy_2420'
e['name'] = 'HideAll'
e['semantic_name'] = 'UIFrameContainer::HideAll(void)'
e['evidence_level'] = 'verified'
e['name_note'] = ('C9血统修复20261116: 本类表0x56ADD0 slot3=0x442420(机器码骨架: slot0=445e70/'
                  'slot4=445b90/slot6=445d10与UIWnd同值) + RET 0 + 体=Release纹理引用(四类ICF折叠载体) '
                  '→ 链律名HideAll; 原名Destroy_2420=N12地址后缀形')
save(fp, d)
print('UIFrameContainer: 0x442420 Destroy_2420→HideAll')

# 台账落账
led = load(LEDGER)
have = {e['addr'] for e in led.get('adjudicated', [])}
new = [
    {'addr': '0x00442420', 'answer': '五主裁定20261116: ICF折叠载体=UIFrameContainer/CCBPanelSlot/'
     'CCBResultWindow/未知0x56ae10类四类HideAll折叠(slot3位+RET 0+体同构); UIWnd/UIFrameWnd'
     '表内无此址, 陈年误录已摘', 'adjudicated': True},
    {'addr': '0x004431b0', 'answer': 'CCBPanelSlot表slot5值(删除式dtor位); UIWnd冒领_sdtor_call_dtor已摘',
     'adjudicated': True},
    {'addr': '0x00444ac0', 'answer': '机器码写0x56AE84=CCBResultWindow表 → complete dtor归真'
     '~CCBResultWindow; UIFrameWnd冒领已摘', 'adjudicated': True},
    {'addr': '0x0043be30', 'answer': '机器码写0x56ACD8≠CCBResultWindow表 → 名盗#6(真主=0x56acd8'
     '未知类), 条目已摘至orphan保全', 'adjudicated': True},
    {'addr': '0x00442e60', 'answer': '0x56ae10未知类对dtor(deleting); UIFrameWnd/UIWnd冒领已摘orphan',
     'adjudicated': True},
    {'addr': '0x00442e80', 'answer': '机器码写0x56AE10 → 未知类complete dtor; UIFrameWnd冒领已摘',
     'adjudicated': True},
    {'addr': '0x00442e90', 'answer': '0x56ae10表slot1值(Render位) → 未知类Render; '
     'UIFrameWnd/UIWnd冒领RenderWithTexture已摘', 'adjudicated': True},
    {'addr': '0x00443530', 'answer': '调complete dtor型scalar dtor, 空表写; 簇归属0x56ae10邻域, '
     '摘除保全待身份定谳', 'adjudicated': True},
]
for e in new:
    if e['addr'] not in have:
        led.setdefault('adjudicated', []).append(e)
save(LEDGER, led)
print('台账: +%d条裁决' % len(new))
save(ORPHAN, orphan)
print('orphan保全: %s' % ORPHAN)
