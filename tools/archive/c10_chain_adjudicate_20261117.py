#!/usr/bin/env python3
"""[C10链法定谳 2026-11-17] 7类基构造链定谳(ctor首调+dtor尾调+存表律三证)。

证据(data/status/base_chain_evidence_20261117.json, 本机capstone):
- PalScript: ctor 0x43A160 call UIWnd ctor(0x445AA0)+存己表0x56AC4C@+0 → [UIWnd]保,
  幽灵[0,68)摘(16个)
- CGameData: dtor 0x44F050 call UIWnd~(0x445B40) → [UIWnd]保, 幽灵[0,68)摘(12个;
  含_vftable@0)
- CScreenMode: ctor 0x523F30 call UIListBox ctor+存己表0x570630@+0; dtor 0x524130
  UIFrameContainer~×6后UIListBox~尾调(基类最后析构) → 真基UIListBox(声明UIWnd错),
  base_size=72, 幽灵[0,72)摘(18个); UIFrameContainer×6=嵌入成员
- SaleUI: ctor 0x45A7B0 call UIListBox ctor首调; dtor 0x45AE60 UIListBox~尾调
  → 真基UIListBox(声明UIFrameWnd错), 幽灵[0,72)摘(3个)
- StateUI/EquipUI/CCBUI: 同构(UIListBox ctor首调+~尾调; 己表存@+0实证) → [UIListBox],
  幽灵摘(各1个: +0x0空名UIFrameWnd型基区标记)
延后(证据已录ledger): scScriptInstance(UIWnd@0+Object@68 MI, Object真实尺寸未知)/
UIEmote(其"表"0x56B044=scScriptInstance次表, 身份未知)/UIRoleSelect/UIRoleDialog/
UIHeadDialog(UIDialog ctor未注册)/TextureLib_Data/RoleCamera(无写入者)/UIAnimateCtrlEX
(UIAnimateCtrl身份未定)。
"""
import json
import copy

ORPHAN = 'data/status/pending/orphan_entries_unknown_classes_20261116.json'
LEDGER = 'data/status/pending/multi_claim_ledger.json'
ADJ = 'data/status/bases_adjudications.json'


def load(fp):
    return json.load(open(fp, encoding='utf-8'))


def save(fp, d):
    json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)


def purge(d, cls, lo, hi, reason):
    km = d.get('known_members') or {}
    ghosts = {k: v for k, v in km.items() if lo <= int(str(k).split('_')[0], 16) < hi}
    if ghosts:
        orphan = load(ORPHAN)
        orphan.setdefault('base_region_ghost_members', {})['%s:%d-%d' % (cls, lo, hi)] = {
            'reason': reason, 'members': copy.deepcopy(ghosts)}
        save(ORPHAN, orphan)
        for k in ghosts:
            del km[k]
        d['known_members'] = km
    return len(ghosts)


PLAN = [
    # (cls, bases, base_size, purge_hi, evidence)
    ('PalScript', None, None, 68,
     'ctor 0x43A160 call UIWnd ctor(0x445AA0)+存己表0x56AC4C@+0(本机capstone) → [UIWnd]保'),
    ('CGameData', None, None, 68,
     'dtor 0x44F050 call UIWnd~(0x445B40) → [UIWnd]保; ctor 0x44EB40存表待深trace'),
    ('CScreenMode', ['UIListBox'], 72, 72,
     'ctor 0x523F30 call UIListBox ctor+存己表0x570630@+0; dtor 0x524130: UIFrameContainer~×6'
     '(嵌入成员)后UIListBox~尾调 → 真基UIListBox; 声明UIWnd错'),
    ('SaleUI', ['UIListBox'], 72, 72,
     'ctor 0x45A7B0 UIListBox ctor首调; dtor 0x45AE60: UIFrameContainer~×16后UIListBox~尾调'
     ' → 真基UIListBox; 声明UIFrameWnd错'),
    ('StateUI', ['UIListBox'], 72, 72,
     'ctor 0x482ED0 UIListBox ctor首调; dtor 0x483380 UIListBox~尾调 → 真基UIListBox'),
    ('EquipUI', ['UIListBox'], 72, 72,
     'ctor 0x498820 UIListBox ctor首调; dtor 0x499030 UIListBox~尾调 → 真基UIListBox'),
    ('CCBUI', ['UIListBox'], 72, 72,
     'ctor 0x519310 UIListBox ctor+存己表0x5704C8@+0; dtor 0x519380 UIListBox~ → 真基UIListBox'),
]


def main():
    adj = load(ADJ)
    for cls, bases, bsize, hi, ev in PLAN:
        fp = 'data/annotations/structs/%s.json' % cls
        d = load(fp)
        if bases is not None:
            d['bases'] = [{'name': b, 'offset': 0} for b in bases]
            d['base_size'] = bsize
            adj[cls] = {'bases': bases, 'date': '2026-11-17',
                        'ctor_evidence': ev, 'verdict_by': 'base_chain_tracer+存表律'}
        else:
            d['bases_note'] = (d.get('bases_note') or '') + ' | 链法定谳20261117: ' + ev
        n = purge(d, cls, 0, hi,
                  '基区幽灵(census错挂): ctor/dtor链证据=' + ev)
        save(fp, d)
        print('%s: bases=%s 摘幽灵%d (%s)' % (cls, bases or '保', n, ev[:40]))
    save(ADJ, adj)

    # C11快照更新(新批准态)
    snap = {}
    import glob as _g
    import os as _o
    for f in sorted(_g.glob('data/annotations/structs/*.json')):
        c = _o.path.basename(f)[:-5]
        dd = json.load(open(f, encoding='utf-8'))
        snap[c] = [(b.get('name') if isinstance(b, dict) else b) for b in (dd.get('bases') or [])]
    save('data/status/bases_snapshot.json', {'date': '2026-11-17',
         'note': 'bases棘轮快照: 变更须有bases_adjudications条目(ctor链证据)', 'snapshot': snap})

    # 延后案台账
    led = load(LEDGER)
    have = {x['addr'] for x in led.get('adjudicated', [])}
    for addr, ans in (
        ('scScriptInstance', 'MI类: UIWnd@0+Object@68(ctor存Object表0x56A9C0@+68实证); '
         'Object真实尺寸未知待建档; 延后'),
        ('UIEmote', '身份案: 其"主表"0x56B044=scScriptInstance次表(ctor 0x44E530存@+68实证); '
         '真实表未知; 延后'),
        ('UIDialog', 'ctor未注册(UIRoleDialog系链前置); 延后'),
        ('UIAnimateCtrl', 'ctor未注册(UIAnimateCtrlEX链前置); 延后'),
    ):
        if addr not in have:
            led['adjudicated'].append({'addr': addr, 'answer': ans, 'adjudicated': True})
    save(LEDGER, led)
    print('快照+台账更新完成')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
