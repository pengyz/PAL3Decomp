"""R15 单测：stage5 `forward_addr_reg_uses`（I1 不变量修 · 地址寄存器前向替换）。

背景（2026-10-19 门禁驱动的根因修）：
    两个变换对 `reg_XXX` 的类型假设矛盾——
      · asm 提升变换把它当**指针**：`reg_EAX->x = x`
      · F83 寄存器提升把它声明成**标量**：`unsigned long reg_EAX = 0;`
    ⇒ 同一变量既作整数又作指针 ⇒ C2227（实测 33 站 · 见
      tools/codegen_invariant_lint.py 的 I1）。

修法恒等式（可证明等价，无需类型推断）：
    p = &e  时   p->m  ≡  (*p).m  ≡  e.m
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline'))

from pipeline.gen.stages.stage5_fixup import forward_addr_reg_uses  # noqa: E402


def test_basic_forward_with_ulong_cast():
    """核心形态（实测 sg_emission_control.cpp:405-406）"""
    src = ('  reg_EAX = (unsigned long)&this->particle_array[a2].curpos;\n'
           '  reg_EAX->x = x;\n'
           '  reg_EAX->y = y;\n')
    out = forward_addr_reg_uses(src)
    assert '(this->particle_array[a2].curpos).x = x;' in out
    assert '(this->particle_array[a2].curpos).y = y;' in out
    assert 'reg_EAX->' not in out
    # 赋值本身保留（整型铸合法且无害）
    assert 'reg_EAX = (unsigned long)&this->particle_array[a2].curpos;' in out


def test_forward_without_cast():
    """`reg_X = &e;` 无铸也识别"""
    src = '  reg_EDX = &v.field;\n  reg_EDX->m = 1;\n'
    out = forward_addr_reg_uses(src)
    assert '(v.field).m = 1;' in out
    assert 'reg_EDX->' not in out


def test_window_stops_at_reassignment():
    """reg 被重新赋值后不得继续前向（窗口语义）"""
    src = ('  reg_EAX = (unsigned long)&a.b;\n'
           '  reg_EAX->x = 1;\n'
           '  reg_EAX = (unsigned long)&c.d;\n'
           '  reg_EAX->y = 2;\n')
    out = forward_addr_reg_uses(src)
    assert '(a.b).x = 1;' in out
    # 第二段必须用新的 &c.d，不得用 a.b
    assert '(a.b).y' not in out


def test_no_arrow_use_untouched():
    """赋值存在但无 `->` 使用 ⇒ 原样返回（不制造无谓改动）"""
    src = '  reg_EAX = (unsigned long)&v;\n  foo(reg_EAX);\n'
    assert forward_addr_reg_uses(src) == src


def test_non_address_assign_untouched():
    """`reg_X = 5;` 不是地址赋值 ⇒ 不参与"""
    src = '  reg_EAX = 5;\n  reg_EAX->x = 1;\n'
    assert forward_addr_reg_uses(src) == src


def test_other_reg_name_not_affected():
    """窗口只作用于同名 reg，其他 reg 的 -> 不动"""
    src = ('  reg_EAX = (unsigned long)&a.b;\n'
           '  reg_ECX->z = 9;\n'
           '  reg_EAX->x = 1;\n')
    out = forward_addr_reg_uses(src)
    assert 'reg_ECX->z' in out
    assert '(a.b).x = 1;' in out


def test_empty_and_no_reg():
    assert forward_addr_reg_uses('') == ''
    assert forward_addr_reg_uses('int x = 1;\n') == 'int x = 1;\n'


def test_comment_and_string_ignored():
    """注释/字符串里的 reg_ 形不得被改写"""
    src = ('  reg_EAX = (unsigned long)&a.b;\n'
           '  // reg_EAX->x 说明\n'
           '  s = "reg_EAX->y";\n')
    out = forward_addr_reg_uses(src)
    assert '// reg_EAX->x 说明' in out
    assert '"reg_EAX->y"' in out
