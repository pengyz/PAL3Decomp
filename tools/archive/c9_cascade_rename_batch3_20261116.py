#!/usr/bin/env python3
"""[C9级联改名批量3 2026-11-16] 三关验证安全集批量正名(76条)。

三关: ①表归属CONFIRMED(ctor写表机器码) ②ABI参个数与根槽一致(RET普查)
③根名语义(非v1_/slot_/sub_且非dtor族)。
判据: MSVC单继承槽号对位 + C++ override同名规则(每槽一名, override承基名)。
改名=链律强制, 原体读数名保留于name_note。
"""
import json
import glob
import os
import re

# 与dry-run同构的预扫
pre_slot_addrs, pre_bases, pre_methods = {}, {}, {}
for fp in sorted(glob.glob('data/annotations/structs/*.json')):
    cls = os.path.basename(fp)[:-5]
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


def main():
    # 按类聚合改名计划
    plan = {}
    for cls in sorted(pre_methods):
        if attr.get(cls) != 'CONFIRMED':
            continue
        d = json.load(open('data/annotations/structs/%s.json' % cls, encoding='utf-8'))
        my_slots = {}
        for vt in (d.get('vtables') or []):
            for si, s in enumerate(vt.get('slots') or []):
                try:
                    my_slots[int(s.get('addr'), 16)] = si
                except (ValueError, TypeError):
                    pass
        for a, e in (d.get('methods') or {}).items():
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
            plan.setdefault(cls, []).append((a, nm, bnm, si))

    n = 0
    for cls, items in sorted(plan.items()):
        fp = 'data/annotations/structs/%s.json' % cls
        d = json.load(open(fp, encoding='utf-8'))
        ms = d['methods']
        names_now = {}
        for a2, e2 in ms.items():
            names_now.setdefault(e2.get('name'), []).append(a2)
        for a, old, new, si in items:
            # C8守卫: 目标名不得已被类内其他地址占用
            holders = [x for x in names_now.get(new, []) if x != a]
            if holders:
                print('C8跳过 %s %s@%s → %s (被%s占用)' % (cls, old, a, new, holders))
                continue
            e = ms[a]
            assert e['name'] == old, '%s %s 名漂移' % (cls, a)
            e['name'] = new
            e['semantic_name'] = '%s::%s' % (cls, new)
            e['evidence_level'] = 'verified'
            e['name_note'] = ('C9级联正名20261116: slot%d位+表归属CONFIRMED(ctor写表)+ABI与根槽'
                              '一致(RET普查) → 链律名%s(基类同槽); 原名%s=体读数命名' % (si, new, old))
            n += 1
        json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('级联改名: %d 条' % n)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
