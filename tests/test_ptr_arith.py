"""TDD：指针算术优先级修已停用（对抗审核 F1 BLOCKER：语义破坏器）。"""
import re
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen', 'stages'))


def test_ptr_arith_fix_disabled():
    """_fix_ptr_arith_precedence 已停用，应原样返回。"""
    sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen', 'stages'))
    from stage5_fixup import _fix_ptr_arith_precedence
    code = 'x = *(gbVec3D *)this + 14;'
    result = _fix_ptr_arith_precedence(code)
    assert result == code, f'已停用不应改写: {result}'


def test_ptr_arith_original_preserved():
    """原始代码（解引用后加）不应被改写——这是合法值算术。"""
    code = 'v23 = *(_DWORD *)v17 + 4088;'
    # 验证停用后正则不匹配
    pat = re.compile(r'\*\(\s*(\w+)\s*\*\s*\)\s*(\w+)\s*\+\s*(\d+)')
    m = pat.search(code)
    # 即使正则匹配，_fix_ptr_arith_precedence 已停用不应改写
    sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen', 'stages'))
    from stage5_fixup import _fix_ptr_arith_precedence
    result = _fix_ptr_arith_precedence(code)
    assert result == code, f'已停用不应改写: {result}'


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
