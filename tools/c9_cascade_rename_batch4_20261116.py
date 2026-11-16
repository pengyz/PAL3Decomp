#!/usr/bin/env python3
"""[C9级联改名批量4 2026-11-16] 签名感知C8守卫重扫 + CCBUI冲突语义裁定。

用户裁定: 遇冲突必须做函数签名的语义裁定。
- C8同名闸本是签名感知(仅同签双址=违规, C++同名异签=合法重载) → 6例签名不同直接放行
- CCBUI真冲突裁定(同签int()):
  - 0x519510 slot3位, 体=ReleaseTempStorage+释放全控件 → 链律名HideAll
  - 0x518e60 非槽, 体=NPC::UpdateAnim循环扫(sin动画参数) → 现名HideAll为体漂移 → UpdateAnims
"""
import json
import glob
import re

pre_slot_addrs, pre_bases, pre_methods = {}, {}, {}
for fp in sorted(glob.glob('data/annotations/structs/*.json')):
    cls = os.path.basename(fp)[:-5] if (os := __import__('os')) else None
    d = json.load(open(fp, encoding='utf-8'))
    vts = d.get('vtables') or []
    if vts:
        lst = []
        for s in (vts[0].get('slots') or []):
            try:
                lst.append(int(s.get('addr') or 'x', 16))
            except (ValueError, TypeError):
                lst.append(None)
        pre_slot_addrs[cls] = lst
    pre_bases[cls] = [(b.get('name') if isinstance(b, dict) else b) for b in (d.get('bases') or [])
                      if (b.get('name') if isinstance(b, dict) else b)]
    ms = {}
    for k, v in (d.get('methods') or {}).items():
        try:
            ms[int(k, 16)] = v
        except (ValueError, TypeError):
            pass
    pre_methods[cls] = ms

cen = json.load(open('data/status/ret_param_census_20261116.json'))
abi = {i['addr']: i['abi_params'] for i in cen['items'] if i['abi_params'] is not None}
rep = json.load(open('data/status/ctor_write_table_census_20261116.json'))
attr = {c: r['verdict'] for c, r in rep['classes'].items()}

BANNED_TGT = re.compile(r'v\d_|slot_|_unk|sub_|_scalar_dtor|_sdtor|scalar_deleting')


def anc_chain(cls, si):
    seen = set()
    while True:
        if cls in seen:
            return None
        seen.add(cls)
        hit = None
        for bn in pre_bases.get(cls, []):
            adds = pre_slot_addrs.get(bn)
            if adds and si < len(adds) and adds[si] is not None:
                e = pre_methods.get(bn, {}).get(adds[si])
                if e and e.get('name'):
                    hit = (bn, adds[si], e)
                break
        if hit:
            return hit
        nxt = pre_bases.get(cls, [])
        if not nxt:
            return None
        cls = nxt[0]


def sig_of(e):
    return str(e.get('signature') or '')


def main():
    n = 0
    for cls in sorted(pre_methods):
        if attr.get(cls) != 'CONFIRMED':
            continue
        fp = 'data/annotations/structs/%s.json' % cls
        d = json.load(open(fp, encoding='utf-8'))
        ms = d.get('methods') or {}
        my_slots = {}
        for vt in (d.get('vtables') or []):
            for si, s in enumerate(vt.get('slots') or []):
                try:
                    my_slots[int(s.get('addr'), 16)] = si
                except (ValueError, TypeError):
                    pass
        changed = False
        for a, e in list(ms.items()):
            nm = str(e.get('name') or '')
            if not nm or nm.startswith('~') or re.search(r'_scalar_dtor|_sdtor|scalar_deleting', nm):
                continue
            try:
                ai = int(a, 16)
            except (ValueError, TypeError):
                continue
            si = my_slots.get(ai)
            if si is None:
                continue
            hit = anc_chain(cls, si)
            if not hit:
                continue
            bn, ba, be = hit
            bnm = str(be.get('name') or '')
            if nm == bnm or not bnm or BANNED_TGT.search(bnm):
                continue
            da, db = abi.get('0x%08x' % ai), abi.get('0x%08x' % ba)
            if db is None or da != db:
                continue
            # 签名感知C8守卫: 仅同签同名双址才真冲突
            collide = [(x2, e2) for x2, e2 in ms.items()
                       if x2 != a and str(e2.get('name') or '') == bnm
                       and sig_of(e2) == sig_of(e)]
            if collide:
                print('真冲突跳过 %s %s@%s → %s (同签双址: %s)'
                      % (cls, nm, a, bnm, [x for x, _ in collide]))
                continue
            e['name'] = bnm
            e['semantic_name'] = '%s::%s' % (cls, bnm)
            e['evidence_level'] = 'verified'
            e['name_note'] = ('C9级联正名batch4-20261116: slot%d位+归属CONFIRMED+ABI一致, '
                              'C8签名感知(与既有同名条目签名异=合法重载) → 链律名%s; 原名%s'
                              % (si, bnm, nm))
            n += 1
            changed = True
        if changed:
            json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('签名感知放行: %d 条' % n)

    # CCBUI真冲突语义裁定
    fp = 'data/annotations/structs/CCBUI.json'
    d = json.load(open(fp, encoding='utf-8'))
    ms = d['methods']
    e = ms['0x00519510']
    assert e['name'] == 'Destroy', e['name']
    e['name'] = 'HideAll'
    e['semantic_name'] = 'CCBUI::HideAll(void)'
    e['evidence_level'] = 'verified'
    e['name_note'] = ('语义裁定20261116: slot3位(0x5704c8表, 归属CONFIRMED) + RET 0(0参int) + '
                      '体=ReleaseTempStorage+释放m_pBack/Wind/Thunder/Water/Fire/Earth等全控件 '
                      '→ 链律名HideAll; 原名Destroy=体读数; decomp名CCBResultWindow::Destroy='
                      'hexrays类型传染错名')
    e = ms['0x00518e60']
    assert e['name'] == 'HideAll', e['name']
    e['name'] = 'UpdateAnims'
    e['semantic_name'] = 'CCBUI::UpdateAnims(void)'
    e['evidence_level'] = 'verified'
    e['name_note'] = ('语义裁定20261116: 体=NPC::UpdateAnim循环扫(m_pRoleStateAttackInc偏移数组, '
                      'sin()*50.0动画参数, 4×4展开) → 真语义UpdateAnims; 原名HideAll=体漂移误名; '
                      '非槽函数(不在任何slot位)')
    json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('CCBUI裁定: 0x519510 Destroy→HideAll; 0x518e60 HideAll→UpdateAnims')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
