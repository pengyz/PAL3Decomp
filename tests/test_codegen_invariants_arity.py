"""`tools/codegen_invariants.py` 的形参元数判定（`_arity_of`）单元测试。

# 背景（2026-09-21 真实编译器实测）

`check_b` 的第二版判据把 `(...)` 当成 "1 参" ⇒ 报出 **56 处**"声明 1 参 vs 调用 N 实参"，
并断言这是 `C2660/C2664 的直接成因`。用真实 MSVC6 编译（`wine CL.EXE /TP /c`）证伪：

    int sub_401070(...);
    int sub_401070_user(void) { return sub_401070(1, 2, 3, 4, 5); }   // ⇒ 0 错误

C++ 里 `(...)` 是**合法的可变参原型**，任意个数实参都合法 ⇒ 永远不可能与调用点不一致。
（另：202 条 `C2660` 里指名叫省略号声明符号的 **0 条**。）

⇒ `_arity_of('...')` 必须返回 `None`（"元数不限"），使 `check_b` 跳过比较；
   其余形态的判定必须与旧实现**逐字节一致**（旧实现是 `args.count(',') + 1`）。

运行方式: python3 tests/test_codegen_invariants_arity.py
"""
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT))
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))

from tools.codegen_invariants import _arity_of  # noqa: E402


def test_variadic_is_unbounded():
    """核心修复：`(...)` ⇒ None（旧实现返回 1 ⇒ 56 个假阳性）。"""
    assert _arity_of('...') is None
    assert _arity_of(' ... ') is None
    assert _arity_of('\t...\n') is None


def test_zero_arity_forms():
    """空 / `void` ⇒ 0（这一条是更早一次修正，必须保持）。"""
    assert _arity_of('') == 0
    assert _arity_of('   ') == 0
    assert _arity_of('void') == 0
    assert _arity_of(' void ') == 0


def test_ordinary_arities_match_old_behaviour():
    """非可变参形态必须与旧实现 `args.count(',') + 1` 完全一致（含嵌套逗号的历史行为）。"""
    cases = ['int', 'int, int', 'char *, int, int *', 'int (*)(int, int), int',
             'UIStatic *, int', 'a,b,c,d,e,f']
    for c in cases:
        assert _arity_of(c) == c.strip().count(',') + 1, c


def test_variadic_not_counted_as_one():
    """回归守卫：修复后不得再出现"可变参被算成 1 参"这一假阳性来源。"""
    assert _arity_of('...') != 1


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