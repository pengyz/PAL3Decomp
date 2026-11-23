#!/usr/bin/env python3
"""[from退役 2026-11-15 用户裁定] 全树清除 vtable slots.from 字段。

用户裁定原文: "本来就没必要加这个字段, annotation既然能建模类继承关系,
它就不需要额外字段"。

法理链:
- from 语义("槽函数实现归属谁")可由 bases链+表槽地址推导: MSVC 未override槽
  槽值=基类同槽地址 ⇒ 地址∈祖先表=继承, 否则=自有。
- 物化副本必然漂移: 实证~40类 from 指向 scScriptInstance/CCBStage 等错误层级
  (收敛工具陈旧产物)。同款病灶链第三次: slot sig冗余 → vtables_retired → from。

消费方同步退役:
- check_annotations.py C7: 改地址推导; C2(from悬空)整体删除
- ida/export_full.py: 归属判据 from is None → 地址推导
- ida/apply_annotations.py: resolve_vtable_slots 4元组→3元组(_from死代码)
- tools/refresh_vtable_froms_20261115.py: 整体退役
"""
import json
import glob
import sys

ROOT = __file__.rsplit('/tools/', 1)[0]


def main():
    n_files = 0
    n_slots = 0
    n_bound = 0
    for p in sorted(glob.glob(ROOT + '/data/annotations/structs/*.json')):
        d = json.load(open(p, encoding='utf-8'))
        changed = False
        for vt in (d.get('vtables') or []):
            for sl in (vt.get('slots') or []):
                if 'from' in sl:
                    if sl.get('from'):
                        n_bound += 1
                    del sl['from']
                    n_slots += 1
                    changed = True
        if changed:
            json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
            n_files += 1
    print('files touched: %d, slots cleaned: %d (bound removed: %d)' % (n_files, n_slots, n_bound))
    return 0


if __name__ == '__main__':
    sys.exit(main())
