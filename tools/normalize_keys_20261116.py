#!/usr/bin/env python3
"""[全量键形归一 2026-11-16] structs注解地址/偏移键一次归一 + 冲突守卫。

用户裁定: 不合法十六进制一起ban(门禁拒绝) + known_members也用十六进制。
规范形:
- 地址(methods键/表址/槽址): ^0x[0-9a-f]{8}$ 小写8位; 'external'+external:true=合法豁免
- known_members键: ^0x[0-9a-f]+(_N)?$ 偏移小写hex(不补零), N_N数组后缀保留
冲突守卫: 归一后键相撞→值全等则合并, 不等则报错拒写(不静默合并)。
"""
import json
import glob
import os
import re

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))


def norm_addr(a):
    return '0x%08x' % int(str(a), 16)


def norm_off(k):
    s = str(k)
    m = re.match(r'^([^_]+)((?:_[^_]+)*)$', s)
    base, suffix = m.group(1), m.group(2) or ''
    return '0x%x%s' % (int(base, 0), suffix.lower())


def main():
    n_files = n_addr = n_off = n_merge = 0
    conflicts = []
    for fp in sorted(glob.glob(os.path.join(ROOT, 'data', 'annotations', 'structs', '*.json'))):
        cls = os.path.basename(fp)[:-5]
        d = json.load(open(fp, encoding='utf-8'))
        changed = False

        # methods键
        ms = d.get('methods')
        if isinstance(ms, dict) and ms:
            nms = {}
            for k, v in ms.items():
                nk = norm_addr(k)
                if nk in nms and nms[nk] != v:
                    conflicts.append((cls, 'methods', k, nk))
                nms[nk] = v
            if nms != ms:
                d['methods'] = nms
                changed = True
                n_addr += sum(1 for k in ms if k != norm_addr(k))

        # vtables表址+槽址
        for vt in d.get('vtables') or []:
            a = vt.get('addr')
            if isinstance(a, str) and re.match(r'^0[xX][0-9a-fA-F]+$', a):
                na = norm_addr(a)
                if na != a:
                    vt['addr'] = na
                    changed = True
                    n_addr += 1
            for s in (vt.get('slots') or []):
                a = s.get('addr')
                if isinstance(a, str) and re.match(r'^0[xX][0-9a-fA-F]+$', a):
                    na = norm_addr(a)
                    if na != a:
                        s['addr'] = na
                        changed = True
                        n_addr += 1

        # known_members键 dec→hex(全量)
        km = d.get('known_members')
        if isinstance(km, dict) and km:
            nkm = {}
            for k, v in km.items():
                nk = norm_off(k)
                if nk in nkm and nkm[nk] != v:
                    conflicts.append((cls, 'known_members', k, nk))
                nkm[nk] = v
            if nkm != km:
                d['known_members'] = nkm
                changed = True
                n_off += sum(1 for k in km if norm_off(k) != k)

        if changed:
            json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
            n_files += 1

    print('归一: %d文件, 地址键%d处, 偏移键%d处' % (n_files, n_addr, n_off))
    if conflicts:
        print('!! 键冲突%d处(拒合并):' % len(conflicts))
        for c in conflicts[:10]:
            print('  ', c)
        return 1
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
