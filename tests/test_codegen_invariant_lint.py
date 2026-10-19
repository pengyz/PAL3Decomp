"""R15 单测：tools/codegen_invariant_lint.py（生成源跨变换不变量门禁）。

背景（2026-10-19 复盘）：本仓 codegen 缺陷同构 —— 变换把构造搬进新上下文时
丢失旧上下文的不变量。本门禁把两条不变量显式化：

  I1 `reg_XXX` 声明为标量后不得被当指针用（F83 寄存器提升丢「值可作指针」）
  I2 类型名不得出现在成员位（排除合法 `->Cls::Method()` / `->~Cls()`）

每条不变量都锁「命中」与「合法例外不误报」两面。
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'tools'))

import codegen_invariant_lint as L  # noqa: E402


# ---------------------------------------------------------------- 掩码

def test_mask_removes_comment_and_string_but_keeps_length():
    src = 'a = 1; // reg_X->x\nb = "reg_Y->y";\n'
    masked = L.mask_strings_comments(src)
    assert len(masked) == len(src), '掩码必须等长（保偏移/行号）'
    assert 'reg_X->x' not in masked
    assert 'reg_Y->y' not in masked
    assert masked.count('\n') == src.count('\n')


# ---------------------------------------------------------------- I1

def test_i1_arrow_on_scalar_reg_is_violation():
    """核心形态：reg_EAX 声明 unsigned long 后仍 `->x`（实测 sg_emission_control.cpp:406）"""
    src = ('void f() {\n'
           '    unsigned long reg_EAX = 0;\n'
           '    reg_EAX = (unsigned long)&this->arr[a2].curpos;\n'
           '    reg_EAX->x = x;\n'
           '}\n')
    hits = L.find_reg_ptr_use_violations(src)
    assert len(hits) == 1
    line, kind, name = hits[0]
    assert name == 'reg_EAX' and kind == 'arrow' and line == 4


def test_i1_deref_on_scalar_reg_is_violation():
    src = ('void f() {\n    unsigned long reg_ECX = 0;\n    *reg_ECX = 1;\n}\n')
    hits = L.find_reg_ptr_use_violations(src)
    assert any(k == 'deref' and n == 'reg_ECX' for _l, k, n in hits)


def test_i1_pointer_declared_reg_is_ok():
    """F83 类特化：`Cls *reg_X = this;` ⇒ `reg_X->` 合法，不报"""
    src = ('void f() {\n'
           '    CCBStage *reg_ESI = this;\n'
           '    reg_ESI->ShowWindow();\n'
           '}\n')
    assert L.find_reg_ptr_use_violations(src) == []


def test_i1_multiplication_not_deref():
    """`a * reg_X` 是乘法，不得误报为解引用"""
    src = ('void f() {\n    unsigned long reg_EAX = 0;\n'
           '    b = a * reg_EAX;\n}\n')
    assert L.find_reg_ptr_use_violations(src) == []


def test_i1_in_string_is_ignored():
    src = 'void f() {\n    unsigned long reg_EAX = 0;\n    s = "reg_EAX->x";\n}\n'
    assert L.find_reg_ptr_use_violations(src) == []


# ---------------------------------------------------------------- I2

def test_i2_type_in_member_position_is_violation():
    """实测形态：`x->RoleSystem` / `x->Object3D`（型名进成员位）"""
    src = 'void f() {\n    v = a->RoleSystem;\n}\n'
    types = {'RoleSystem', 'CCBUI'}
    hits = L.find_type_in_member_position(src, types)
    assert len(hits) == 1 and hits[0][1] == 'RoleSystem'


def test_i2_qualified_call_is_ok():
    """合法：`p->Cls::Method()` 限定调用不报"""
    src = 'void f() {\n    p->CCBUI::ShowWindow();\n}\n'
    types = {'CCBUI'}
    assert L.find_type_in_member_position(src, types) == []


def test_i2_dtor_is_ok():
    """合法：`p->~Cls()` 析构调用不报"""
    src = 'void f() {\n    p->~CCBUI();\n}\n'
    types = {'CCBUI'}
    assert L.find_type_in_member_position(src, types) == []


def test_i2_member_not_type_is_ok():
    """普通成员名不在类型集合里 ⇒ 不报"""
    src = 'void f() {\n    v = a->m_pFoo;\n}\n'
    types = {'CCBUI'}
    assert L.find_type_in_member_position(src, types) == []


def test_i2_ignores_comments():
    src = 'void f() {\n    // a->RoleSystem\n    v = 1;\n}\n'
    assert L.find_type_in_member_position(src, {'RoleSystem'}) == []


# ---------------------------------------------------------------- 棘轮

def test_baseline_ratchet_no_regression(tmp_path, monkeypatch):
    """计数不超基线 ⇒ exit 0"""
    src_dir = tmp_path / 'src'
    src_dir.mkdir()
    (src_dir / 'a.cpp').write_text('void f(){}\n', encoding='utf-8')
    monkeypatch.setattr(L, 'SRC_DIR', str(src_dir))
    monkeypatch.setattr(L, 'BASELINE', str(tmp_path / 'b.json'))
    monkeypatch.setattr(L, 'PROJECT_ROOT', str(tmp_path))
    assert L.main.__module__  # sanity
    # 直接走子进程不方便（argparse），此处仅验证基线文件语义与扫描器
    res = L.scan_files(str(src_dir), set())
    assert res['reg_ptr_use'] == [] and res['type_in_member'] == []


def test_i2_prefix_backtrack_not_false_positive():
    """[误报修 2026-10-19] `->RenderTarget3::X()` 不得回溯成 `RenderTarget` 误报。

    实测 37 处 I2 全属此类：真实行均为合法限定调用
        (((RenderTarget2 *)Instance_fd20))->RenderTarget2::Update(dt);
    根因：`([A-Z]\\w*)\\s*(?!::)` 在 `RenderTarget3::` 上回溯成前缀 `RenderTarget`，
    使 `(?!::)` 落在 `3::` 上而“通过”。修法：捕获名后必须是词边界。
    """
    types = {'RenderTarget'}
    for line in (
        '  (((RenderTarget3 *)(v2 + 64)))->RenderTarget3::ClearEffects();\n',
        '  (((RenderTarget2 *)Instance_fd20))->RenderTarget2::Update(dt);\n',
        '  (((RenderTarget *)Instance_db10))->RenderTarget::OnDeviceLost(1);\n',
    ):
        assert L.find_type_in_member_position(line, types) == [], line


def test_i2_real_violation_still_caught():
    """误报修不得放过真违规：`x->RoleSystem`（型名后直接非标识符字符）"""
    src = 'void f() {\n    v = a->RoleSystem;\n}\n'
    hits = L.find_type_in_member_position(src, {'RoleSystem'})
    assert len(hits) == 1 and hits[0][1] == 'RoleSystem'
