"""R15 单测：stage5 `qualify_shadowed_free_calls`（C2660 修·自由函数被类成员遮蔽）。

背景（2026-10-20 当场读定谳，纠正了「receiver 未解析」的初判）：
  pal3/src/free_functions.h:225
      int MoveToAbsolute(_DWORD *_this, int a2, int a3);   // 自由函数 3 参
  pal3/src/Combat/CCBStage.h:356
      bool MoveToAbsolute(int fp, int dwTaskID);           // 类成员 2 参（遮蔽）
  调用（CCBStage 成员函数体内）`MoveToAbsolute(recv, formal, nVal)` 3 实参
  ⇒ C++ 名字查找先搜类作用域 ⇒ 绑到 2 参成员 ⇒ C2660 "does not take 3 parameters"。
  实测 I3 命中的 19 站**全部**是这一类（19/19 零例外）。

修法（等价变换）：名 N 同时是自由函数与当前类成员 ⇒ 无限定调用加 `::`
  → 绑定到全局自由函数，不改实参与语义。
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline'))

from pipeline.gen.stages.stage5_fixup import (  # noqa: E402
    qualify_shadowed_free_calls, _load_free_func_names)


FREE = {'MoveToAbsolute', 'strcpy', 'DoFreeThing'}
MEMBER = {'MoveToAbsolute'}


def test_shadowed_call_gets_global_qualifier():
    out = qualify_shadowed_free_calls(
        '  MoveToAbsolute(m_pUI->arr[i], formal, nVal);\n', FREE, MEMBER)
    assert out == '  ::MoveToAbsolute(m_pUI->arr[i], formal, nVal);\n'


def test_non_member_name_untouched():
    src = '  strcpy(a, b);\n'
    assert qualify_shadowed_free_calls(src, FREE, MEMBER) == src


def test_already_qualified_untouched():
    src = '  ::MoveToAbsolute(a, b, c);\n'
    assert qualify_shadowed_free_calls(src, FREE, MEMBER) == src


def test_member_access_not_touched():
    """`x->MoveToAbsolute(...)` 是成员调用，不得加 `::`"""
    src = '  obj->MoveToAbsolute(a, b);\n'
    assert qualify_shadowed_free_calls(src, FREE, MEMBER) == src


def test_class_scope_call_not_touched():
    """`CCBStage::MoveToAbsolute(...)` 已限定，不动"""
    src = '  CCBStage::MoveToAbsolute(a, b);\n'
    assert qualify_shadowed_free_calls(src, FREE, MEMBER) == src


def test_free_but_not_member_no_change():
    src = '  DoFreeThing(a, b);\n'
    assert qualify_shadowed_free_calls(src, FREE, MEMBER) == src


def test_empty_free_set_noop():
    src = '  MoveToAbsolute(a, b, c);\n'
    assert qualify_shadowed_free_calls(src, set(), MEMBER) == src


def test_real_free_func_names_loaded():
    """实测：free_functions.h 的自由函数名能被收集（401 个），且含 MoveToAbsolute"""
    names = _load_free_func_names()
    assert len(names) > 100, 'free_functions.h 应收集到上百个自由函数名'
    assert 'MoveToAbsolute' in names


def test_in_string_ignored():
    src = '  s = "MoveToAbsolute(a, b, c)";\n'
    assert qualify_shadowed_free_calls(src, FREE, MEMBER) == src
