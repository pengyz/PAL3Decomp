"""TDD v2：只在调用形 `->Class::method(` 中剥 __ovl_，不动声明。"""
import re
import sys

sys.path.insert(0, 'pipeline/gen')


def test_strip_ovl_in_qualified_call():
    """->Class::method__ovl_XXX( 中的 __ovl_XXX 必须剥，但声明不动。"""
    code = 'x->ARC_PlayerAtt::Create__ovl_1();'
    result = re.sub(r'::(\w+?)__ovl_[0-9a-fA-F]+\(', r'::\1(', code)
    assert 'Create__ovl_1' not in result, f'调用未剥: {result}'
    assert 'Create(' in result, f'应有裸名: {result}'


def test_preserve_declaration_with_ovl():
    """声明中的 __ovl_ 不动（区分重载）。"""
    code = 'void Destroy__ovl_02(int nMode);'
    result = re.sub(r'::(\w+?)__ovl_[0-9a-fA-F]+\(', r'::\1(', code)
    assert 'Destroy__ovl_02' in result, f'声明不应变: {result}'


def test_preserve_plain_call():
    """无 __ovl_ 的调用不变。"""
    code = 'x->Class::Method();'
    result = re.sub(r'::(\w+?)__ovl_[0-9a-fA-F]+\(', r'::\1(', code)
    assert result == code, f'不应变: {result}'


def test_free_function_call_not_qualified():
    """自由函数调用（无 ::）不受影响。"""
    code = 'Destroy__ovl_02(v1);'
    result = re.sub(r'::(\w+?)__ovl_[0-9a-fA-F]+\(', r'::\1(', code)
    assert result == code, f'不应变: {result}'


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
