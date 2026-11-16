#!/usr/bin/env python3
"""[G2 2026-11-15] 折叠地址 0x43de40 的 C7 条目补齐。

二进制证据:
- 函数 0x43de40 体 = Release(m_TempStorageNGH) + 委托 0x445c10(UIWnd slot3),
  registry 名 CCBStage::slot_3(bisect 名, 语义无名) → canonical = slot_3(位次,
  与 UIWnd slot3 正名对齐——C++ override 链每槽一名)
- .rdata 多表 slot3 位含此指针(UI 族表) = 34 类各自 override slot3,
  同体 ICF 折叠(链接器 /OPT:ICF 会再折叠, 每类独立条目+定义=既定模型)

C7 修法: claim 类 methods 无 0x43de40 条目 → 补 slot_3 条目。
守卫: 类内已有 slot_3 异址条目 → C8 风险, 跳过并报告(人工定谳)。
"""
import json
import glob
import sys

ROOT = __file__.rsplit('/tools/', 1)[0]
TARGET = '0x0043de40'
NAME = 'slot_3'
SIG = 'void __thiscall()'


def main():
    added, skipped_has, skipped_c8 = [], [], []
    for p in sorted(glob.glob(ROOT + '/data/annotations/structs/*.json')):
        cls = p.split('/')[-1][:-5]
        d = json.load(open(p, encoding='utf-8'))
        changed = False
        for vt in (d.get('vtables') or []):
            hit = any(str(sl.get('addr', '')).lower() == TARGET for sl in (vt.get('slots') or []))
            if not hit:
                continue
            ms = d.setdefault('methods', {})
            if TARGET in ms:
                skipped_has.append(cls)
                continue
            # C8 守卫: 类内已有同名异址
            dup = [k for k, v in ms.items()
                   if str(v.get('name')) == NAME and str(k).lower() != TARGET]
            if dup:
                skipped_c8.append((cls, dup))
                continue
            ms[TARGET] = {
                'name': NAME,
                'signature': SIG,
                'semantic_name': 'CCBStage::slot_3(void)',
                'name_note': ('G2折叠定谳: 体=ReleaseTempStorage+委托0x445c10(UIWnd slot3); '
                              'registry bisect名无语义; override链对齐UIWnd slot3正名slot_3'),
            }
            changed = True
            added.append(cls)
        if changed:
            json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('added: %d 类' % len(added))
    print('已有条目跳过: %d' % len(skipped_has))
    print('C8守卫跳过: %d %s' % (len(skipped_c8), skipped_c8[:5]))
    return 0


if __name__ == '__main__':
    sys.exit(main())
