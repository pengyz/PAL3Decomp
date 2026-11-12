#!/usr/bin/env python3
"""[归属族落标 2026-11-13] free_functions 归位 TOP5 成员函数。

病灶: 5 个真成员函数在 IDB 里是下划线裸名(TaskBookUI_RefreshElements 形态,
注解库无该 addr 条目 ⇒ apply 改名链没碰) ⇒ decomp name 无 :: ⇒ collect
归 free_funcs ⇒ 挤进 free_functions.cpp(无类头 include/无方法声明链)
⇒ 体内 90+ 错(C2660/C2065/C2027/虚调用洪泛)。

slot accounting 铁证(每个函数体):
  `int v1; // ecx` 未初始化即用(v3 = (void***)(v1 + 1252)) ⇒ ECX=this 被
  cdecl 渲染吞掉 = thiscall。1252 偏移落在 TaskBookUI binary_size=143672 内。
  体内 `void (__thiscall ***v14)` 虚表操作形态佐证。

效果链(与 thunk→槽 传播同源机制): apply 落 thiscall 型 + 改名 Cls::Method
⇒ Hex-Rays 重渲染调用点(ECX 数据流) + export name 带 :: ⇒ collect 归类
迁回类单元(自带 include/声明链) + 调用点成员化(rewrite_unqualified_member_call
[T27] 元数门: 剥 this 后元数匹配)。

用法: python3 tools/fix_member_attribution_top5_20261113.py [--apply]
"""
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv

EDITS = [
    ('TaskBookUI', '0x00455790', 'TaskBookUI::RefreshElements',
     'int __thiscall TaskBookUI::RefreshElements(int nVal)',
     '体内v1//ecx未初始化即用(v1+1252偏移在类内143672); vtable形态虚调用;'
     '调用点2个(free_functions内部5288/5470)'),
    ('CEffect', '0x0048E950', 'CEffect::UpdateState',
     'int __thiscall CEffect::UpdateState(int nVal)',
     '体内v1//ecx未初始化即用(16*nVal+v1数组基址); 调用点3个全在'
     'free_functions内部(CEffect_UpdateCallback族)'),
    ('MainPropUI', '0x00492BB0', 'MainPropUI::ShowSubPanels',
     'int __thiscall MainPropUI::ShowSubPanels(int nVal)',
     '调用点5个(EquipUI.cpp:501外部+free内部); 命名形态+UI族一致性'),
    ('MagicUI', '0x0048A390', 'MagicUI::InitUILayout',
     'int __thiscall MagicUI::InitUILayout(int nVal)',
     '调用点6个(RenderTarget.cpp:424/1246外部+free内部); 命名形态+UI族一致性'),
    ('ComposeUI', '0x0047E190', 'ComposeUI::ProcessFrame',
     'int __thiscall ComposeUI::ProcessFrame(int nVal)',
     '调用点2个(UITitle_YXXX.cpp:408外部+free内部); 命名形态+UI族一致性'),
]

for cls, addr, full_name, sig, ev in EDITS:
    fp = os.path.join(ROOT, 'data', 'annotations', 'structs', '%s.json' % cls)
    d = json.load(open(fp, encoding='utf-8'))
    me = d.setdefault('methods', {}).setdefault(addr, {})
    old = me.get('name')
    me['name'] = full_name
    me['signature'] = sig
    me['source'] = 'member_attribution_20261113: ' + ev
    me.setdefault('evidence_level', 'unverified')
    print('%s %s: %r -> %s' % (cls, addr, old, full_name))
    if APPLY:
        json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

if not APPLY:
    print('\n[dry-run] 加 --apply 落盘')
