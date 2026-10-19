"""R15 单测：stage5 `cast_reg_ptr_rhs`（型判别铸）。

背景（2026-10-19 C2440 修）：
    F83 把寄存器伪名 `reg_EDI` 提升为 `unsigned long`，而 RHS 常为显式指针铸表达式
    （`reg_EDI = (float *)(&this->m_nTodo_20 + 9);`）⇒ 指针→整型隐式转换非法 ⇒ C2440。

    2026-09-29 曾有 `cast_reg_assignments` 无条件铸被**回退**（实测新增 15：
    UIScene +13 C2227/C2228 类值/指针链 RHS 铸坏成员访问、PAL3 +2 C2679、
    ScriptVM 60→102 级联）。故本次只做**型判别**：仅顶层显式指针铸才补铸。

三形覆盖：
    1. 指针铸 RHS  ⇒ 补 `(unsigned long)`（恒等，32-bit 同宽）
    2. 类值/裸变量 RHS ⇒ **豁免**（这是 09-29 回退的根因，必须锁死）
    3. 已含 `(unsigned long)` ⇒ 不重复补（防双重铸）
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline'))

from pipeline.gen.stages.stage5_fixup import cast_reg_ptr_rhs  # noqa: E402


def test_ptr_cast_rhs_gets_int_cast():
    """形1：显式指针铸 RHS ⇒ 补 (unsigned long)"""
    src = "  reg_EDI = (float *)(&this->m_nTodo_20 + 9);\n"
    out = cast_reg_ptr_rhs(src)
    assert out == "  reg_EDI = (unsigned long)(float *)(&this->m_nTodo_20 + 9);\n"


def test_char_ptr_cast_rhs():
    """形1b：char* 铸同样补"""
    src = "  reg_EAX = (char *)(&v196.x + (_DWORD)dword_C10CC8);\n"
    out = cast_reg_ptr_rhs(src)
    assert '(unsigned long)(char *)' in out


def test_qualified_ptr_cast_rhs():
    """形1c：带 :: 限定的型名也识别"""
    src = "  reg_EBX = (NS::Foo *)buf;\n"
    out = cast_reg_ptr_rhs(src)
    assert '(unsigned long)(NS::Foo *)' in out


def test_class_value_rhs_exempt():
    """形2（回退教训锁）：类值 RHS 不得补铸 —— 会改变重载决议/成员访问"""
    src = "  reg_EDI = someObject;\n"
    out = cast_reg_ptr_rhs(src)
    assert out == src, "类值 RHS 必须豁免（2026-09-29 回退根因）"


def test_bare_ptr_var_rhs_exempt():
    """形2b：裸指针变量 RHS 不得补铸（无类型信息，保守不动）"""
    src = "  reg_EDI = RolePtr;\n"
    out = cast_reg_ptr_rhs(src)
    assert out == src


def test_member_chain_rhs_exempt():
    """形2c：指针链成员访问 RHS 不得补铸"""
    src = "  reg_EDI = this->m_pFoo->m_bar;\n"
    out = cast_reg_ptr_rhs(src)
    assert out == src, "指针链成员 RHS 必须豁免"


def test_already_cast_not_doubled():
    """形3：已含 (unsigned long) 不重复补"""
    src = "  reg_EDI = (unsigned long)(float *)(&x + 9);\n"
    out = cast_reg_ptr_rhs(src)
    assert out.count('(unsigned long)') == 1


def test_float_value_rhs_exempt():
    """标量浮点表达式不带指针铸 ⇒ 不匹配（非本函数职责）"""
    src = "  reg_EDI = 3.5;\n"
    out = cast_reg_ptr_rhs(src)
    assert out == src


def test_empty_and_no_reg():
    """空串 / 无 reg_ 快速返回"""
    assert cast_reg_ptr_rhs("") == ""
    assert cast_reg_ptr_rhs("int x = 1;\n") == "int x = 1;\n"
