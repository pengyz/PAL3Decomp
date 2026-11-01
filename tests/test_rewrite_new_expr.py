"""TDD：_rewrite_new_expression 源形还原类别——掩码匹配 + 逐命中计数 + 负例语料。"""
import re
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen', 'stages'))


def test_rewrite_new_expression_masked():
    """字符串字面量中的 operator new 不应被改写（掩码保护）。"""
    from stage5_fixup import _rewrite_new_expression
    code = 'printf("v2 = (CCBUI *)operator new(0x74u);");\n  v2 = (CCBUI *)operator new(0x74u);\n  if ( v2 )\n    v2->CCBUI::CCBUI();\n  else\n    v3 = 0;\n'
    result, hits = _rewrite_new_expression(code)
    # 字符串内的 operator new 不应被改写
    assert 'printf("v2 = (CCBUI *)operator new(0x74u);")' in result, f'字符串被改写: {result}'
    # 真实代码的 operator new 应被改写
    assert 'new CCBUI()' in result, f'真实代码未改写: {result}'


def test_rewrite_new_expression_hit_count():
    """逐命中计数应正确。"""
    from stage5_fixup import _rewrite_new_expression
    code = ('  v2 = (CCBUI *)operator new(0x74u);\n  if ( v2 )\n    v2->CCBUI::CCBUI();\n  else\n    v3 = 0;\n'
            '  v4 = (UIButton *)operator new(0x54u);\n  if ( v4 )\n    v4->UIButton::UIButton();\n  else\n    v5 = 0;\n')
    result, hits = _rewrite_new_expression(code)
    assert hits == 2, f'应命中 2 次，得 {hits}'


def test_rewrite_new_expression_negative_case():
    """非构造形（普通方法调用）不应被改写。"""
    from stage5_fixup import _rewrite_new_expression
    code = '  v2 = (GRPinput *)operator new(0x24u);\n  if ( v2 )\n    v2->GRPinput::SetMousePos();\n  else\n    v3 = 0;\n'
    result, hits = _rewrite_new_expression(code)
    assert hits == 0, f'普通方法不应命中: {result}'
    assert 'operator new' in result, f'不应改写: {result}'


def test_rewrite_new_expression_no_ctor_call():
    """无构造调用（只有 operator new）不应被改写。"""
    from stage5_fixup import _rewrite_new_expression
    code = '  v2 = (CCBUI *)operator new(0x74u);\n  v3 = v2;'
    result, hits = _rewrite_new_expression(code)
    assert hits == 0, f'无构造不应命中: {result}'


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
            except Exception as e:
                print(f'  ERROR: {name}: {e}')
                failures += 1
    print(f'\n{failures} failures')
    sys.exit(1 if failures else 0)
