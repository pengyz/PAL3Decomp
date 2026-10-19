#!/usr/bin/env python3
"""[C2273 修 2026-10-19] ctor 调用限定化渲染单测（R15）。

病灶：`Class::Class(this)` → `this->Class()` = MSVC 函数式 cast（C2273 ×919）。
修：限定形 `this->Class::Class()`（既有制式 ✓ 限定直调）。
"""
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))
sys.path.insert(0, str(REPO))

from data import store  # noqa: E402,F401
import ast_transform as at  # noqa: E402


def test_ctor_this_call_renders_qualified_form():
    """核心锁：Cls::Cls(this) ⇒ this->Cls::Cls()（非 this->Cls() ✗ C2273 形）。"""
    out = at.transform_oop_calls('void Foo::Foo() { Foo::Foo(this); }',
                                 static_methods=set(), cls_name='Foo')
    # [T56 #16 修正] 静态成员式（verifier：this->Cls::Cls() 非法 ✗）
    # [终裁实证 2026-10-19] 限定箭头形（MSVC6 test7 编译过 ✓✓）
    assert 'this->Foo::Foo()' in out, out
    assert '->Foo()' not in out.replace('->Foo::Foo()', ''), '非限定形复现（C2273）✗'


def test_base_ctor_still_qualified_direct():
    """基类 ctor 形保持 Class::Class(...)（既有路径不破）。"""
    out = at.transform_oop_calls('void Der::Der() { Base::Base(this); }',
                                 static_methods=set(), cls_name='Der')
    assert 'Base::Base(' in out or 'this->Base::Base(' in out, out


def test_regular_method_call_unaffected():
    """普通方法调用不受扰（虚调用形保持）。"""
    out = at.transform_oop_calls('void Foo::Bar() { this->Baz(1); }',
                                 static_methods=set(), cls_name='Foo')
    assert 'Baz(1)' in out


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
