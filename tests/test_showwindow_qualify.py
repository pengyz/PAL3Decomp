"""Win32 `ShowWindow` 被继承来的成员遮蔽 ⇒ 补 `::` 的单元测试（**真实样本**）。

# 机制（2026-09-21 编译器实测复现 ✓）

    struct UIWnd { virtual int ShowWindow(int nFlags); };   // 1 参成员
    struct CCBUI : UIWnd { void f(void *h){ ShowWindow(h, 4); } };
    ⇒ C2660 'ShowWindow' : function does not take 2 parameters      // 命中继承来的 1 参成员
    ⇒ 命名空间作用域同一调用：C2065（含 windows.h 时绑定 Win32 ::ShowWindow）

# 为什么补 `::` 是安全的

被遮蔽的成员是 **1 参** ⇒ **任何 2 实参**的 `ShowWindow(...)` 都不可能是它 ✓。
可见性：`include/pal3/ida_defs.h:5` = `#include <windows.h>`，每个生成 .cpp 首位 include ✓。
实测规模：生成树里非限定调用 **11 处，全部 2 实参**（第 2 参为 4/5 = `SW_*`）✓。

运行方式: python3 tests/test_showwindow_qualify.py
"""
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
for p in ("pipeline/gen", "pipeline", "."):
    sys.path.insert(0, str(PROJECT_ROOT / p))

from stages.stage5_fixup import _qualify_win32_showwindow, is_win32_showwindow  # noqa: E402

# 真实站点（取自生成树）
REAL = [
    "            ShowWindow(g_hMainWnd, 4);",
    "          ShowWindow(g_RoleSystemCombat.m_teamSlotsB.combat.g_hCBStageCamDlg, 5);",
    "      ShowWindow(g_hCombatDlg2, 5);",
    "    ShowWindow(hDlg, 4);",
    "  return ShowWindow((HWND)g_RoleSystemCombat.m_teamSlotsB.combat.m_nActorRenderCount, 5);",
]


def test_real_sites_are_qualified():
    for code in REAL:
        out = _qualify_win32_showwindow(code)
        assert '::ShowWindow(' in out, (code, out)
        # 只在前面插入 `::`，其余逐字节不变
        assert out == code.replace('ShowWindow(', '::ShowWindow('), (code, out)


def test_member_access_forms_untouched():
    for code in ("  p->ShowWindow(1);", "  this->m_pBack.ShowWindow(1);",
                 "  (*p)->ShowWindow(1);"):
        assert _qualify_win32_showwindow(code) == code, code


def test_already_qualified_untouched():
    code = "  ::ShowWindow(g_hMainWnd, 4);"
    assert _qualify_win32_showwindow(code) == code


def test_one_arg_call_untouched():
    """1 实参 = 合法成员调用 ⇒ 绝不动。"""
    code = "  ShowWindow(1);"
    assert _qualify_win32_showwindow(code) == code


def test_three_arg_call_untouched():
    code = "  ShowWindow(a, b, c);"
    assert _qualify_win32_showwindow(code) == code


def test_qualified_member_call_untouched():
    code = "  p->UIWnd::ShowWindow(1);"
    assert _qualify_win32_showwindow(code) == code


def test_arg_count_with_nested_parens():
    """第 1 实参含函数指针 cast 时，顶层切分仍必须得到 2。"""
    code = "  ShowWindow((HWND)(*(int (__stdcall **)(int))f)(1), 4);"
    out = _qualify_win32_showwindow(code)
    assert out.startswith('  ::ShowWindow('), out


def test_pure_predicate():
    assert is_win32_showwindow('g_hMainWnd, 4')
    assert is_win32_showwindow('(HWND)x, 5')
    assert not is_win32_showwindow('1')
    assert not is_win32_showwindow('a, b, c')
    assert not is_win32_showwindow('')


def test_unbalanced_parens_no_crash():
    code = "  ShowWindow(a, b"
    assert _qualify_win32_showwindow(code) == code


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
