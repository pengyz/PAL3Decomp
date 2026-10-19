#!/usr/bin/env python3
"""[P2b 2026-10-19] 指针/浮点→整型赋值补强转单测（R15 三形）。

病灶：reg_EDI 等整型标量（4B 位槽）被赋指针/浮点 ⇒ C2440 ×48。
修：补显式强转（等价变换 ✓）。
"""
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))


def _load_fn():
    src = (REPO / 'pipeline/gen/ast_transform.py').read_text(encoding='utf-8')
    m = re.search(r'def cast_ptr_int_assignments\(.*?\n(?=def )', src, re.S)
    ns = {'re': re}
    exec(m.group(0), ns)
    return ns['cast_ptr_int_assignments']


def test_ptr_to_int():
    fn = _load_fn()
    out = fn('void F() {\n  reg_EDI = (float *)(&this->m_x + 9);\n}\n')
    assert '(unsigned long)' in out, out


def test_float_to_int():
    fn = _load_fn()
    out = fn('void F() {\n  unsigned long v1 = 1.0f;\n}\n')
    assert '(unsigned long)(1.0f)' in out or '(unsigned long)( 1.0f)' in out, out


def test_int_to_ptr():
    fn = _load_fn()
    out = fn('void F() {\n  float *p = &this->m_x;\n}\n')
    # LHS 指针 + RHS 取址 = 合法 ✓ 不动
    assert '(unsigned long)' not in out, out


def test_explicit_cast_untouched():
    fn = _load_fn()
    out = fn('void F() {\n  reg_EDI = (unsigned long)(float *)(&x);\n}\n')
    assert out.count('(unsigned long)') == 1, out  # 不双重强转 ✓


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
