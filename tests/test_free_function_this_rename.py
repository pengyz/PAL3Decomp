"""自由函数 `this` 形参改名（`this`→`_this`）的单元测试（**真实样本**）。

# 规则（使用者定，2026-09-21）：自由函数的形参名不允许用 `this`

C++ 里 `this` 是关键字 ⇒ 写了就是**语法错误**。实证（基线普查）：
`pal3/src/free_functions.cpp:1702/1751/1897` 报 `C2143 syntax error : missing ')' before 'this'`。
系统性审核（`tools/audit_this_in_free_functions.py`）实测 **34 处**非法定义（全在 free_functions.cpp），
而普查里只见 **3 处** —— 其余 31 处被 **C1003 截断**挡住（见 gotcha_c1003_truncation_blinds_metric）。

# 为什么整体改名是**等价变换**

自由函数里 `this` **不是可用表达式**（没有隐式 this）⇒ 出现的该标识符**必指那个形参** ⇒ 改名安全 ✓。

# 唯一的坑：不得改到字符串/注释

字符串里的 `"this"` 被改会**改数据** ⇒ 破坏字节匹配 ✗ ⇒ 必须跳过引号与注释。

运行方式: python3 tests/test_free_function_this_rename.py
"""
import re
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
for p in ("pipeline/gen", "pipeline", "."):
    sys.path.insert(0, str(PROJECT_ROOT / p))

from stages.stage1_structural import (  # noqa: E402
    free_function_has_this_param, rename_this_identifier,
)

# 真实样本形态（free_functions.cpp:1702 / 10124 / 4558）
REAL = (
    "void FlushCommandQueue(RoleSystem *this)\n"
    "{\n"
    "  this->m_nPathState = 0;\n"
    "  if ( this->m_fontcolor.Color )\n"
    "    sub_449F80(this, 1);\n"
    "}\n"
)


def test_real_definition_renamed_everywhere():
    out = rename_this_identifier(REAL)
    assert 'RoleSystem *_this' in out, out
    assert not re.search(r'(?<![\w_])this->', out), out   # 注意 `_this->` 含子串 `this->`
    assert '_this->m_nPathState' in out
    assert 'sub_449F80(_this, 1)' in out


def test_predicate_detects_head_param():
    assert free_function_has_this_param(REAL)
    assert not free_function_has_this_param("void f(int a)\n{\n}\n")


def test_predicate_ignores_this_variants():
    """`_this` / `this_` / `this2` 都不是关键字 ⇒ 不得被当作命中（防重复改名）。"""
    for head in ("void f(RoleSystem *_this)", "void f(UIFrameWnd *this_)", "int f(int this2)"):
        assert not free_function_has_this_param(head + "\n{\n}\n"), head


def test_rename_leaves_this_variants_alone():
    code = "void f(RoleSystem *_this) { return _this->x; }\n"
    assert rename_this_identifier(code) == code
    code2 = "void g(UIFrameWnd *this_) { return this_->y; }\n"
    assert rename_this_identifier(code2) == code2


# ===== 唯一的坑：字符串 / 字符 / 注释 =====
def test_string_literal_is_not_touched():
    code = 'void f(int this)\n{\n  printf("this is data");\n}\n'
    out = rename_this_identifier(code)
    assert '"this is data"' in out, out          # 数据必须原样 ✓
    assert '(int _this)' in out                  # 形参必须改名 ✓


def test_char_literal_is_not_touched():
    code = "void f(int this) { char c = 't'; return; }\n"
    out = rename_this_identifier(code)
    assert "'t'" in out and '(int _this)' in out, out


def test_comments_are_not_touched():
    code = "// this is a comment\nvoid f(int this) { /* this too */ }\n"
    out = rename_this_identifier(code)
    assert '// this is a comment' in out and '/* this too */' in out, out
    assert '(int _this)' in out, out


def test_escaped_quote_inside_string():
    code = 'void f(int this) { s = "a\\"this\\"b"; }\n'
    out = rename_this_identifier(code)
    assert '"a\\"this\\"b"' in out, out
    assert '(int _this)' in out, out


def test_idempotent():
    once = rename_this_identifier(REAL)
    assert rename_this_identifier(once) == once


def test_custom_new_name():
    out = rename_this_identifier("void f(int this) { this = 1; }", new='self_')
    assert 'self_' in out and 'this' not in out.replace("'this'", ''), out


if __name__ == '__main__':
    ok = fail = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed' % (ok, fail))
    sys.exit(1 if fail else 0)
