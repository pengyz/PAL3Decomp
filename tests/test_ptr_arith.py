"""TDD：指针算术优先级 bug——*(T*)this + N 应为 *(T*)((char*)this + N)。"""
import re
import sys

sys.path.insert(0, 'pipeline/gen')


def test_ptr_arith_precdence_fix():
    """*(T*)expr + N 应修正为 *(T*)((char*)expr + N)（字节偏移算术）。"""
    code = 'x = *(gbVec3D *)this + 14;'
    # 修复正则：*(T*)expr + N → *(T*)((char*)expr + N)
    fixed = re.sub(
        r'\*\(\s*(\w+)\s*\*\s*\)\s*(\w+)\s*\+\s*(\d+)',
        r'*(\1 *)((char *)\2 + \3)',
        code)
    assert '(char *)this + 14' in fixed, f'应修正指针算术: {fixed}'
    assert 'gbVec3D *)this + 14' not in fixed, f'不应保留旧形: {fixed}'


def test_ptr_arith_preserve_valid():
    """合法的指针算术不变（已有括号）。"""
    code = 'x = *((gbVec3D *)this + 14);'
    fixed = re.sub(
        r'\*\(\s*(\w+)\s*\*\s*\)\s*(\w+)\s*\+\s*(\d+)',
        r'*(\1 *)((char *)\2 + \3)',
        code)
    # 这个形是 *((T*)this + N) = 指针算术（元素偏移），不该改
    # 但正则不匹配（因为 * 后面是 ( 不是 ((T*)），所以不变
    assert fixed == code, f'不应变: {fixed}'


def test_ptr_arith_member_access():
    """成员访问形不变。"""
    code = 'x = this->field + 14;'
    fixed = re.sub(
        r'\*\(\s*(\w+)\s*\*\s*\)\s*(\w+)\s*\+\s*(\d+)',
        r'*(\1 *)((char *)\2 + \3)',
        code)
    assert fixed == code, f'不应变: {fixed}'


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
