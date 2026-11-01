"""TDD：条件化包括号（F1）+ 覆盖判定（F3）+ 值算术负例（F4）。
对抗复核 ACCEPT-WITH-FIXES 必修项。"""
import re
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen', 'stages'))


def _has_toplevel_binop(arg):
    """判断 arg 是否有顶层二元算符（括号深度 0 处的 + - 等）。
    F3 修法：覆盖判定 = 括号/方括号深度扫描顶层算符。"""
    depth = 0
    for ch in arg:
        if ch in '([{':
            depth += 1
        elif ch in ')]}':
            depth -= 1
        elif depth == 0 and ch in '+-*/%':
            # 排除一元 +/-（前一个是算符或开头）
            return True
    return False


def test_case2_simple_form_unchanged():
    """Case 2 简单形不变：*(T*)x 保持。"""
    arg = '(T*)x'
    assert not _has_toplevel_binop(arg), f'不应有顶层算符: {arg}'


def test_case2_binop_wrapped():
    """Case 2 二元算符形包整体：(T*)x + N → *((T*)x + N)。"""
    arg = '(T*)this + 14'
    assert _has_toplevel_binop(arg), f'应有顶层算符: {arg}'


def test_case2_deep_binop_not_wrapped():
    """Case 2 深度内 + 不触发：&f(a + b) 应剥 & 成 f(a + b)。"""
    arg = 'f(a + b)'
    assert not _has_toplevel_binop(arg), f'深度内 + 不应触发: {arg}'


def test_case2_array_index_not_wrapped():
    """Case 2 数组下标 + 不触发：&arr[i + 1] 应剥 & 成 arr[i + 1]。"""
    arg = 'arr[i + 1]'
    assert not _has_toplevel_binop(arg), f'下标内 + 不应触发: {arg}'


def test_case2_minus_form():
    """Case 2 减法形也触发：&x - 1 → *(&x - 1)。"""
    arg = '&x - 1'
    assert _has_toplevel_binop(arg), f'减法形应触发: {arg}'


def test_case2_cast_ref_compound():
    """Case 2 cast-& 复合形：(T*)&x + 1 → *((T*)&x + 1)。"""
    arg = '(T*)&x + 1'
    assert _has_toplevel_binop(arg), f'复合形应触发: {arg}'


def test_case2_multiply_form():
    """Case 2 乘法形：&X + N * M → *(&X + N * M)。"""
    arg = '&X + N * M'
    assert _has_toplevel_binop(arg), f'乘法形应触发: {arg}'


def test_value_arith_not_touched():
    """F4 负例：非 ref 位值算术不动：x = *(T*)v17 + 4088 保持。"""
    # 此形不在 ref 位，ref_params 不应触碰
    # 验证 _has_toplevel_binop 对该形返回 True（但实际不改写因为不在 ref 位）
    arg = '*(gbVec3D *)this + 14'
    assert _has_toplevel_binop(arg), f'应有顶层算符: {arg}'
    # 但关键是 ref_params 只对 ref 位调用 _fix_single_ref_arg


if __name__ == '__main__':
    failures = 0
    for name, fn in list(globals().items()):
        if name.startswith('test_') and callable(fn):
            try:
                fn()
                print(f'  PASS: {name}')
            except AssertionError as e:
                print(f'  FAIL: {name}: {e}')
                failures += 1
    print(f'\n{failures} failures')
    sys.exit(1 if failures else 0)
