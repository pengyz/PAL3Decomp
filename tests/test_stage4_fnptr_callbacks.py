#!/usr/bin/env python3
"""[批1-5#2 2026-10-15] thiscall fnptr → 成员指针机制单测（R15）。

覆盖：
  ① rewrite_thiscall_fnptr_param_ex 合成 this 剥除：命名 this / 无名指针型首参
     ⇒ 剥；真首参 ⇒ 不剥（防误伤）
  ② _rewrite_member_ptr_calls：直调改写 `a2(OBJ,...)` → `(((CLS*)(OBJ))->*a2)(...)`；
     声明位 `*a2)(` 不受影响
  ③ _fix_member_fn_callbacks 组合：签名+调用同改（=RenderTarget2::AdjustThisCall 形）
"""
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen' / 'stages'))

from data import store  # noqa: E402,F401
import stage4_substitution as s4  # noqa: E402


class _Ctx(object):
    def __init__(self, cls):
        self.cls_name = cls


def test_synthetic_this_named_dropped():
    t, n, d = s4.rewrite_thiscall_fnptr_param_ex(
        'int (__thiscall *a2)(int this, int a2)', 'CLS')
    assert d and n == 'a2'
    assert t == 'int (CLS::*a2)(int a2)'   # 余参保留形参名（=CCBSystem 实测形）


def test_synthetic_this_anon_ptr_dropped():
    # [批1-5#2] AdjustThisCall 形：无名指针型首参 = 合成 this
    t, n, d = s4.rewrite_thiscall_fnptr_param_ex(
        'int (__thiscall *a2)(char *, int)', 'RenderTarget2')
    assert d and n == 'a2'
    assert t == 'int (RenderTarget2::*a2)(int)'


def test_genuine_first_arg_not_dropped():
    t, n, d = s4.rewrite_thiscall_fnptr_param_ex(
        'int (__thiscall *a2)(int nVal, int a2)', 'CLS')
    assert not d
    assert t == 'int (CLS::*a2)(int nVal, int a2)'


def test_member_ptr_call_rewrite():
    out = s4._rewrite_member_ptr_calls(
        'return a2((char *)this + a3 - 12, a4);', 'a2', 'RenderTarget2')
    assert out == ('return (((RenderTarget2 *)((char *)this + a3 - 12))->*a2)(a4);')


def test_member_ptr_call_no_args_and_decl_untouched():
    # 声明位 `*a2)(` 不匹配 ✓；零余参形 `a2(OBJ)` → `(...->*a2)()`
    code = 'int (CLS::*a2)(int);\n  a2(OBJ);\n'
    out = s4._rewrite_member_ptr_calls(code, 'a2', 'CLS')
    assert 'int (CLS::*a2)(int);' in out
    assert '(((CLS *)(OBJ))->*a2)();' in out


def test_unnamed_cast_form_not_rewritten():
    # [批1-5#2 回归修复] 无名 cast 形 `(__thiscall *)` 不得进转换（否则给 cast
    # 类型强塞 pFn 名 ⇒ C2061，实测 UIScene.cpp L123）——pass 0 只吃**命名**形参
    code = 'result = ((int (__thiscall *)(int))x->y)(p, 3);\n'
    out = s4._fix_member_fn_callbacks(code, _Ctx('UIScene'))
    assert out == code   # 原样（无名 cast 不匹配 \w+）


def test_fix_member_fn_callbacks_combined():
    # =RenderTarget2::AdjustThisCall 形：签名转成员指针 + 直调改写
    code = ('int RenderTarget2::AdjustThisCall('
            'int (__thiscall *a2)(char *, int), int a3, int a4)\n'
            '{\n'
            '  return a2((char *)this + a3 - 12, a4);\n'
            '}\n')
    out = s4._fix_member_fn_callbacks(code, _Ctx('RenderTarget2'))
    assert 'int (RenderTarget2::*a2)(int), int a3, int a4)' in out
    assert '(((RenderTarget2 *)((char *)this + a3 - 12))->*a2)(a4)' in out
    assert '__thiscall' not in out


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
