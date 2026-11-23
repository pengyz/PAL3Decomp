#!/usr/bin/env python3
"""[vtable调用点lvars 2026-11-12] vtable裸调用迭代变量的类typed标注。

病灶: (***vN)(_DWORD,_DWORD) 迭代form 的 (**vN)(vN,arg) 调用——Hex-Rays 对
char* 算术派生指针自猜 fn-ptr 类型, this 参数铸成 int/_DWORD ⇒ C2664。
vptr offset0 标注(fix_vptr_offset0_20261112)只对 typed 对象表达式生效;
两者组合: lvars typed 对象指针 + 类 __vftable(现已落) ⇒ 成员式渲染。

本轮4站点(证据纪律: Array.cpp 3错挂起——4892字节记录类身份未定谳,
标 UIWnd* 属伪证):
  1. LineupComp::ShowById      v5=UIPushButton*  同址 UIPushButton::CreateFromTemplate
  2. LineupComp::CallSlotMethod v4=UIPushButton*  stride 248=UIPushButton.binary_size;
                                                 int返回槽0=ShowClipped(UIWnd族)
  3. UITitle_XJTM::SetMonsterState  v5=UIWnd*     LayoutGetRects 全块 UIWnd::SetRect((UIWnd*)..)
  4. UITitle_XJTM::SetMonsterState2 v5=UIWnd*     同上

用法: python3 tools/fix_lvars_vtable_calls_20261112.py [--apply]
"""
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv

EDITS = [
    ('LineupComp', '0x00483FA0', 'v5', 'UIPushButton *',
     '同址v4+161520被UIPushButton::CreateFromTemplate((UIPushButton*)..)调用; '
     '姊妹站L38带(UIPushButton*,_DWORD)精确cast可编译'),
    ('LineupComp', '0x00484140', 'v4', 'UIPushButton *',
     '迭代stride 248=UIPushButton.binary_size; int返回+u8参=ShowClipped(UIWnd族slot0=0x445E70)'),
    ('UITitle_XJTM', '0x00488C70', 'v5', 'UIWnd *',
     '块内窗口全块UIWnd::SetRect((UIWnd*)..)cast(GridLayoutGetRects实证); '
     'stride 152, Hex-Rays按字节精确重渲算术'),
    ('UITitle_XJTM', '0x0049A980', 'v5', 'UIWnd *', '同SetMonsterState'),
]

for cls, addr, var, typ, ev in EDITS:
    fp = os.path.join(ROOT, 'data', 'annotations', 'structs', '%s.json' % cls)
    d = json.load(open(fp, encoding='utf-8'))
    me = d.setdefault('methods', {}).setdefault(addr, {})
    lv = me.setdefault('lvars', {})
    old = lv.get(var)
    lv[var] = typ
    me['lvars_source'] = (me.get('lvars_source', '') + ' | vtable调用点typed: ' + ev).strip(' |')
    print('%s %s %s: %r -> %r' % (cls, addr, var, old, typ))
    if APPLY:
        json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

if not APPLY:
    print('\n[dry-run] 加 --apply 落盘')
