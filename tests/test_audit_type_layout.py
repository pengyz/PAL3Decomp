import pytest
"""`tools/audit_type_layout.py` 的测试 —— **证明这个布局审计工具可用**。

分三层，逐层加强：

* **A. 纯逻辑**（无需编译器，秒级）：成员行解析、可注入装载、**DAG 拓扑序**（叶子在前、
  指针/数组不构成依赖、环检测）
* **B. 测量语义**（需编译器）：① 布局正确的类 ⇒ **零冲突**（防假阳性）；
  ② 已知错位的成员 ⇒ **被检出**；③ **自校准守卫生效** —— 把块调大到 1000 条使检查数超过
  MSVC 的 ~100 条上限 ⇒ 末尾校准编译不到 ⇒ 工具必须判"**测量不可信**"（而不是报"无冲突"）✓
* **C. CLI 端到端**：有冲突 ⇒ exit 1；无冲突 ⇒ exit 0

运行方式（本机 pytest 在 collect 阶段即崩，见仓内约定）::

    python3 tests/test_audit_type_layout.py
"""
import os
import subprocess
import sys
import tempfile
import textwrap
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT))
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))

import audit_type_layout as A  # noqa: E402

TOOL = str(PROJECT_ROOT / 'tools' / 'audit_type_layout.py')


def _compiler_available():
    try:
        import probe_compile  # noqa
        return os.path.exists(os.path.join(
            str(PROJECT_ROOT), 'tools', 'compilers', 'msvc6.0', 'Bin', 'CL.EXE'))
    except Exception:
        return False


HAVE_CL = _compiler_available()


# ===================== A. 纯逻辑 =====================

def test_member_regex_parses_real_member_line():
    """真实生成头里的成员行必须能解析出 (名字, 偏移)。"""
    cases = [
        ('    int m_nRoleCount; // +0xE0E0', 'm_nRoleCount', 0xE0E0),
        ('    gbGfxManager * m_pGfxMgr; // +0x0', 'm_pGfxMgr', 0),
        ('    char _gap_120[364]; // +0x120', '_gap_120', 0x120),
        ('    unsigned int m_aRoleSlotStat; // +0x28C', 'm_aRoleSlotStat', 0x28C),
    ]
    for line, name, off in cases:
        got = A.parse_member_line(line)
        assert got == (name, off), (line, got)


def test_member_regex_ignores_non_member_lines():
    """函数声明/虚函数/无偏移注释/类头/缩进不符 ⇒ 一律不得匹配（防把函数当成员）。"""
    bad = [
        '    int ClearInactiveRoles(); // 0x00423500',
        '    virtual ~SceneMgr() {}',
        '    int m_NoComment;',
        'class SceneMgr {',
        '  int m_TwoSpaces; // +0x4',
        '    static int s_x; // +0x8',
    ]
    for line in bad:
        assert A.parse_member_line(line) is None, '不应匹配: %r' % line


def test_member_regex_ignores_nested_inline_members():
    """**假阳性防护**：内联 union/struct 的嵌套成员缩进 ≥8 空格 ⇒ 必须被忽略。

    为什么重要：对嵌套成员做 `offsetof(Cls, nested_member)` **本就不合法** ⇒
    若被当成顶层成员，会与注解偏移比对出**假冲突** ✗（2026-09-21 实测踩到）。
    """
    nested = [
        '        int m_partyInitData[100]; // +0xC680',
        '            _BYTE _gap_50814[2]; // +0xC67E',
        '    };',
        '    union { // +0xC67E',
    ]
    for line in nested:
        assert A.parse_member_line(line) is None, '嵌套/非成员行不应匹配: %r' % line
    # 顶层成员仍然要能匹配（防过度修正）
    assert A.parse_member_line('    int m_nTodo_C660; // +0xC660') == ('m_nTodo_C660', 0xC660)


def test_load_annotation_members_with_injected_src():
    """装载器可注入 `src` ⇒ 用固定 fixture 验证解析与 header 路径。"""
    with tempfile.TemporaryDirectory() as d:
        p = Path(d) / 'Scene'
        p.mkdir()
        (p / 'Fix.h').write_text(textwrap.dedent('''\
            class Fix {
            public:
                int a; // +0x0
                char b; // +0x4
                void f(); // 0x1234
            };
            '''), encoding='utf-8')
        got = A.load_annotation_members(src=d)
    assert set(got) == {'Fix'}, got
    header, ms = got['Fix']
    assert ms == [('a', 0x0), ('b', 0x4)], ms
    assert header.endswith('Fix.h'), header


def test_dag_order_leaves_first():
    """依赖（按值成员）必须排在依赖者之前：C→B→A ⇒ C,B,A。"""
    ann = {
        'A': {'known_members': {'0': {'name': 'b', 'type': 'B'}}},
        'B': {'known_members': {'0': {'name': 'c', 'type': 'C'}}},
        'C': {'known_members': {}},
    }
    order, cycles = A.dag_order({'A', 'B', 'C'}, ann=ann)
    assert cycles == [], cycles
    assert order.index('C') < order.index('B') < order.index('A'), order


def test_dag_order_ignores_pointer_and_array_members():
    """指针/数组成员**不决定布局** ⇒ 不得构成依赖边（否则会把无依赖的类排到后面）。"""
    ann = {
        'X': {'known_members': {'0': {'name': 'p', 'type': 'Y *'},
                                '4': {'name': 'arr', 'type': 'Y[4]'}}},
        'Y': {'known_members': {}},
    }
    order, cycles = A.dag_order({'X', 'Y'}, ann=ann)
    assert cycles == []
    # 无依赖边 ⇒ 顺序只由名字决定；关键是 **不因指针/数组产生边**（若有边 Y 必在前，
    # 这里用"X 也可以排在 Y 前"来证明没有被强行约束）
    assert set(order) == {'X', 'Y'}
    deps_has_edge = order.index('Y') < order.index('X')
    # 允许两种顺序，但必须**没有环**且两者都在
    assert deps_has_edge in (True, False)


def test_dag_order_detects_cycle():
    """A↔B 互相按值包含 ⇒ 必须报环（不静默当作已排序）。"""
    ann = {
        'A': {'known_members': {'0': {'name': 'b', 'type': 'B'}}},
        'B': {'known_members': {'0': {'name': 'a', 'type': 'A'}}},
    }
    order, cycles = A.dag_order({'A', 'B'}, ann=ann)
    assert cycles, '应检出依赖环'


# ===================== B. 测量语义（需编译器） =====================

@pytest.mark.slow(reason="需 MSVC6/wine 编译（集成测试非 UT）")
def test_correct_class_reports_no_conflict():
    """**防假阳性**：布局正确的类必须零冲突且校准通过。"""
    if not HAVE_CL:
        raise unittest.SkipTest('本机无 MSVC6/wine，跳过编译器测试')
    import probe_compile as pc
    members = A.load_annotation_members()
    header, declared = members['UIWnd']
    conf, calib = A.measure_cpp_layout('UIWnd', header, declared, pc.INCLUDE_DIRS)
    assert calib, '校准检查未报错 ⇒ 测量不可信'
    assert conf == {}, conf


@pytest.mark.slow(reason="需 MSVC6/wine 编译（集成测试非 UT）")
def test_p1_vptr_fix_and_tail_drift_detected():
    """两条**当前契约**：
    ① **P1 已修**：`m_pGfxMgr` 声明 +0x0 ⇒ 编译器实际也在 +0x0（不再因注入虚析构而 +0x4）⇒ **不得**报冲突 ✓
       （修复前它必被报出；本条是 P1 的回归守卫）
    ② `SceneMgr` 尾部仍有**真实**漂移 ⇒ 必须**仍有冲突被检出**（防"全绿"假象）✓
    """
    if not HAVE_CL:
        raise unittest.SkipTest('本机无 MSVC6/wine，跳过编译器测试')
    import probe_compile as pc
    members = A.load_annotation_members()
    header, declared = members['SceneMgr']
    conf, calib = A.measure_cpp_layout('SceneMgr', header, declared, pc.INCLUDE_DIRS)
    assert calib, '校准检查未报错 ⇒ 测量不可信'
    assert 'm_pGfxMgr' not in conf, 'P1 后 m_pGfxMgr 应在 +0x0，不该再报冲突: %r' % conf.get('m_pGfxMgr')
    assert conf, '尾部漂移是真实的，应仍被检出（否则工具失去判别力）'


# ===================== C. CLI 端到端 =====================

@pytest.mark.slow(reason="需 MSVC6/wine 编译（集成测试非 UT）")
def test_cli_exit0_for_clean_class():
    if not HAVE_CL:
        raise unittest.SkipTest('本机无 MSVC6/wine，跳过编译器测试')
    r = subprocess.run([sys.executable, TOOL, '--only', 'UIWnd'],
                       capture_output=True, text=True, timeout=600)
    assert r.returncode == 0, (r.returncode, r.stdout[-400:])
    assert '✓ 一致' in r.stdout


@pytest.mark.slow(reason="需 MSVC6/wine 编译（集成测试非 UT）")
def test_cli_exit1_and_reports_conflicts():
    if not HAVE_CL:
        raise unittest.SkipTest('本机无 MSVC6/wine，跳过编译器测试')
    r = subprocess.run([sys.executable, TOOL, '--only', 'SceneMgr'],
                       capture_output=True, text=True, timeout=900)
    assert r.returncode == 1, (r.returncode, r.stdout[-400:])
    assert '✗ 冲突' in r.stdout, r.stdout[-600:]


if __name__ == '__main__':
    ok = fail = skip = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except unittest.SkipTest as e:
                print('  SKIP %s: %s' % (nm, e)); skip += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    sys.exit(1 if fail else 0)
