#!/usr/bin/env python3
"""[G2 2026-11-15] CEff 族 slot13 折叠地址 0x4c15d0 的 C7 条目补齐。

二进制证据:
- 函数 0x4c15d0 = CEffAction::UpdateParticles(void) (decomp体=粒子更新循环)
- 13 张 CEff 族表 s13 全指向它(CEffObj共享实现, canonical正名账 slot13=UpdateParticles
  见 canonical_slot_names_20261114) = 族成员继承实现, ICF下每类独立条目+定义
- CEffAction/CEffSParticle 已有条目, 其余 11 类缺 → C7 own 违规
"""
import json
import glob
import sys

ROOT = __file__.rsplit('/tools/', 1)[0]
TARGET = '0x004c15d0'
NAME = 'UpdateParticles'
SIG = 'void __thiscall()'


def main():
    added, skipped_has, skipped_c8 = [], [], []
    for p in sorted(glob.glob(ROOT + '/data/annotations/structs/*.json')):
        cls = p.split('/')[-1][:-5]
        d = json.load(open(p, encoding='utf-8'))
        changed = False
        for vt in (d.get('vtables') or []):
            if not any(str(sl.get('addr', '')).lower() == TARGET for sl in (vt.get('slots') or [])):
                continue
            ms = d.setdefault('methods', {})
            if TARGET in ms:
                skipped_has.append(cls)
                continue
            dup = [k for k, v in ms.items()
                   if str(v.get('name')) == NAME and str(k).lower() != TARGET]
            if dup:
                skipped_c8.append((cls, dup))
                continue
            ms[TARGET] = {
                'name': NAME,
                'signature': SIG,
                'semantic_name': 'CEffAction::UpdateParticles(void)',
                'name_note': 'G2定谳: CEff族slot13共享实现(canonical正名账slot13=UpdateParticles); '
                             '13族表s13同址=继承+ICF',
            }
            changed = True
            added.append(cls)
        if changed:
            json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('added: %d %s' % (len(added), added))
    print('已有条目跳过: %d' % len(skipped_has))
    print('C8守卫跳过: %d' % len(skipped_c8))
    return 0


if __name__ == '__main__':
    sys.exit(main())
