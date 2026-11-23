#!/usr/bin/env python3
"""annotation 批量修复 2026-11-11（L-VAR 首批：三处数据层修复，全部编译器/使用点证据）。

修1  globals.json + 0x0058B770 nIndex: 新增 type=int
    证据: 全树使用点全为 int 语境——循环上界(Scene_Render2 `i < nIndex` /
    ScriptSystem_Cleanup 同形)、SetAt(nIndex,..) 追加式(=count 语义)、
    `v5 = nIndex - 1`(InputSystem:36 后退一步索引)。原 globals.h 发射
    `extern char nIndex[]`(无前缀回退) → 比较/算术全炸。
    修2  structs/ScriptSystemData.json known_members["3992"] m_pCurrentBlock:
    char * → PalScript *
    证据: 原 evidence "malloc(48)+store" 只证明'堆指针'未证指向类型; 5 个独立
    使用点全部 PalScript* 语境——PalScript.cpp:602/772/809/882/913 与
    `(PalScript *)vN` 比较及 `v6->m_nState` 成员访问。IDB struct compat 备注
    是占位猜测，使用点证据升级覆盖。
    修3  lvars 首批两函数（S1 float→ptr 槽，cast 目标即需求类型，使用点全查为纯赢）:
    - structs/CCBSystem.json methods["0x00513120"].lvars = {"v3": "CCBStage *"}
      证据: v3 声明 float 但唯一使用 `(CCBStage *)v3`（EditorUpdate 调用），
      无 float 生命期使用行（提取器 uses 全列 2 行）。
    - structs/UIRoleSelectDialog.json methods["0x0052AAB0"].lvars = {"v5": "char *"}
      证据: v5 声明 float；写侧 `v5 = &this->m_list.m_column[5].head[24]`(char*)；
      读侧全为 `(_DWORD *)v5` cast-deref(char* cast 合法) —— char* 全自洽，
      CCBStage* 形态反而破写侧(C2440 char*→_DWORD*)。

用法: python3 tools/fix_annotation_batch_20261111.py [--apply]
"""
import json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv

def load(p):
    return json.load(open(p, encoding='utf-8'))

def save(p, d):
    json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

def main():
    # 修1: nIndex 全局
    p1 = os.path.join(ROOT, 'data/annotations/globals.json')
    g = load(p1)
    key = '0x0058B770'
    if key not in g:
        g[key] = {}
    e = g[key]
    e.setdefault('name', 'nIndex')
    old_t = e.get('type')
    e['type'] = 'int'
    e['category'] = e.get('category', 'pending')
    e['source'] = (' | L-VAR 2026-11-11: 类型定谳 int——全树使用点全 int 语境'
                   '(循环上界/追加式 SetAt 首参/-1 算术), 与 g_pScriptObjArray 配对=count'
                   + ('; 原类型=%s 退役(无前缀回退产物)' % old_t if old_t else ''))
    e['evidence_level'] = 'use_site_majority'
    print('修1 nIndex@0x58B770: %s -> int' % (old_t or '(缺省char[])'))
    if APPLY: save(p1, g)

    # 修2: m_pCurrentBlock
    p2 = os.path.join(ROOT, 'data/annotations/structs/ScriptSystemData.json')
    d = load(p2)
    m = d['known_members']['3992']
    old_t2 = m.get('type')
    m['type'] = 'PalScript *'
    m['source'] = m.get('source', '') + ' | L-VAR 2026-11-11: 指向类型定谳 PalScript*——' \
        '5 使用点全 PalScript* 语境(PalScript.cpp:602/772/809/882/913 与 (PalScript*)vN 比较' \
        '+ v6->m_nState 访问); 原 char* 为 IDB-compat 占位(只证堆指针未证指向)'
    m['evidence_level'] = 'use_site_majority'
    print('修2 m_pCurrentBlock@3992: %s -> PalScript *' % old_t2)
    if APPLY: save(p2, d)

    # 修3: lvars 两函数
    for cls, addr, var, typ, ev in (
        ('CCBSystem',          '0x00513120', 'v3', 'CCBStage *',
         'v3 声明 float 唯一使用 (CCBStage *)v3 (EditorUpdate 调用), 无 float 生命期'),
        ('UIRoleSelectDialog', '0x0052AAB0', 'v5', 'char *',
         'v5 声明 float; 写侧 v5=&m_list.m_column[5].head[24](char*); 读侧全 (_DWORD*)v5 cast'),
    ):
        p3 = os.path.join(ROOT, 'data/annotations/structs/%s.json' % cls)
        d3 = load(p3)
        me = d3.setdefault('methods', {}).setdefault(addr, {})
        lv = me.setdefault('lvars', {})
        lv[var] = typ
        me['lvars_source'] = ' | L-VAR 2026-11-11 S1槽位首批判定(纯赢=全部使用点自洽): ' + ev
        print('修3 %s%s lvars: %s -> %s' % (cls, addr, var, typ))
        if APPLY: save(p3, d3)

    print('=== %s ===' % ('APPLIED' if APPLY else 'DRY-RUN(加 --apply 落盘)'))

if __name__ == '__main__':
    main()
