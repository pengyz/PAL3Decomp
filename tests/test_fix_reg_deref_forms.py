"""R15 单测：stage5 `fix_reg_deref_forms`（I1 残 13 处 · reg_ 解引用形）。

背景（2026-10-19 门禁 I1 残修）：
A) 真读 `pfVal2.x = *reg_EDI;` —— reg_EDI 被 F83 声明为 unsigned long（标量），
   但此处按指针取值。目标 `.x/.y/.z` 是 float ⇒ pointee 必为 float。
   修：`*(float *)reg_EDI`（读 4 字节 → float，位等价）。
B) 占位宏镜像 `*reg_EDI = _ET1;` —— `_ET1` 是 ida_defs.h 的只读占位宏
   （`#define _ET1 0`），当右值赋值无可表达语义；且前邻 asm 已含真实存储。
   若铸成 `*(float *)reg_EDI = (float)_ET1;` 会多一条 `mov [reg],0` ⇒ 字节不匹配。
   故降为注释（零代码产出、信息不丢）。
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline'))

from pipeline.gen.stages.stage5_fixup import fix_reg_deref_forms  # noqa: E402


def test_read_gets_float_cast():
    """A) 真读：`.x = *reg_EDI` ⇒ `*(float *)reg_EDI`"""
    out = fix_reg_deref_forms('  pfVal2.x = *reg_EDI;\n')
    assert 'pfVal2.x = *(float *)reg_EDI;' in out


def test_read_all_components():
    for comp in ('x', 'y', 'z', 'w'):
        out = fix_reg_deref_forms('  v.%s = *reg_EBP;\n' % comp)
        assert '*(float *)reg_EBP' in out


def test_et_placeholder_becomes_comment():
    """B) 占位镜像：`*reg_EBP = _ET1;` ⇒ 注释（无代码产出）"""
    out = fix_reg_deref_forms('    *reg_EBP = _ET1;\n')
    assert '*reg_EBP = _ET1;' not in out.split('//')[0]
    assert out.lstrip().startswith('// [I1]')
    assert '_ET1' in out                    # 信息保留
    assert 'asm' in out                     # 说明真实存储来源


def test_et_placeholder_multi_digit():
    out = fix_reg_deref_forms('    *reg_EDI = _ET7;\n')
    assert out.lstrip().startswith('// [I1]') and '_ET7' in out


def test_multiplication_untouched():
    """乘法不得被当成解引用"""
    src = '    total = a * reg_EAX;\n'
    assert fix_reg_deref_forms(src) == src


def test_plain_assignment_untouched():
    """`reg_X = expr;`（非解引用）不动"""
    src = '    reg_EAX = (unsigned long)&v;\n'
    assert fix_reg_deref_forms(src) == src


def test_empty_and_no_reg():
    assert fix_reg_deref_forms('') == ''
    assert fix_reg_deref_forms('int x;\n') == 'int x;\n'


def test_mirror_preserves_indent():
    """降注释后保持原缩进（避免 reindent 副作用）"""
    out = fix_reg_deref_forms('        *reg_EDI = _ET1;\n')
    assert out.startswith('        // [I1]')
