#!/usr/bin/env python3
"""annotation 批量修复 2026-11-11c（P-A16⑤退役的 lvars 承接 + pszRoleDir 定谳）。

1. CGameData 0x0044F8D0 lvars: {v10: CCBUI *}
   证据: decomp `v10 = (CCBUI *)v9`（赋值 cast 即意图证据）+ `result = v10`
   （返回链同型）。P-A16⑤ 曾用 void* 全局文本替换承接，退役后由本注解承接。
2. globals.json + 0x0058619C pszRoleDir: type char *
   证据: PAL_GDB_LoadSkillData `strlen(pszRoleDir)` + `&pszRoleDir[v11]`
   ——char 指针语境（strlen 实参 + char 下标）。psz_ 前缀=IDA 语义命名。
   原 extern int（无前缀回退）⇒ 下标/strlen 双炸。

用法: python3 tools/fix_annotation_batch_20261111c.py [--apply]
"""
import json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv

def main():
    # 1. CGameData lvars
    p = os.path.join(ROOT, 'data/annotations/structs/CGameData.json')
    d = json.load(open(p, encoding='utf-8'))
    me = d.setdefault('methods', {}).setdefault('0x0044F8D0', {})
    me.setdefault('lvars', {})['v10'] = 'CCBUI *'
    me['lvars_source'] = (' | L-VAR 2026-11-11c(P-A16⑤退役承接): decomp '
        'v10=(CCBUI*)v9 赋值 cast 即类型意图, result=v10 返回链同型; '
        '全局文本替换(全局裸 replace)误伤 CCBUI 同形声明, 改由本注解按地址承接')
    print('lvars CGameData 0x44F8D0: v10 -> CCBUI *')
    if APPLY:
        json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    # 2. pszRoleDir
    p2 = os.path.join(ROOT, 'data/annotations/globals.json')
    g = json.load(open(p2, encoding='utf-8'))
    key = '0x0058619C'
    e = g.setdefault(key, {})
    e.setdefault('name', 'pszRoleDir')
    old = e.get('type')
    e['type'] = 'char *'
    e['evidence_level'] = 'use_site_majority'
    e['source'] = (' | L-VAR 2026-11-11c: strlen(pszRoleDir)+&pszRoleDir[v11] '
                   'char 指针语境实证(PAL_GDB_LoadSkillData); psz_ 前缀=IDA 语义命名'
                   + ('; 原类型=%s 退役(无前缀回退产物)' % old if old else ''))
    print('pszRoleDir@0x58619C: %s -> char *' % (old or '(缺省int)'))
    if APPLY:
        json.dump(g, open(p2, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    print('=== %s ===' % ('APPLIED' if APPLY else 'DRY-RUN'))

if __name__ == '__main__':
    main()
