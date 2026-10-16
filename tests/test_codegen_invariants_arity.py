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

# [vptr 前置门查找面扩展 2026-10-16 verifier] 手写头并存制式（emit 跳过 handwritten
# 类防重复定义）⇒ [D] 门「未找到生成头」须回退查 include/ 手写声明（virtual/vptr 证据
# 判据与生成头一致），否则 gbChain1DNode/gbLightObj 等误报。纯函数单测（R15）。
def test_handwritten_vptr_ok_virtual():
    from codegen_invariants import handwritten_vptr_verdict
    v, detail = handwritten_vptr_verdict('gbChain1DNode', 'include')
    assert v == 'ok', (v, detail)


def test_handwritten_vptr_none_missing():
    from codegen_invariants import handwritten_vptr_verdict
    v, detail = handwritten_vptr_verdict('NoSuchClassXYZ', 'include')
    assert v == 'none'


def test_handwritten_vptr_bad_no_virtual():
    from codegen_invariants import handwritten_vptr_verdict
    v, detail = handwritten_vptr_verdict('filebuf', 'include')
    assert v in ('none', 'bad'), (v, detail)


# [tail_drift 判据修正 2026-10-16 verifier] 原 `_mx+8<bsize`（最大成员**起始偏移**）
# 当「成员末端」用（注释/代码不符）⇒ 大尾部成员类误报（ArcLocaleRole mx=1 bsize=28
# 实测 3/4 误报）。纯函数单测（R15）：判据=成员**末端** max(off+size) vs bsize。
def test_tail_drift_judgement_end_based():
    from audit_type_layout import tail_drift_conflict
    # ArcLocaleRole 形：active@0(BYTE) + offset@1(uchar[27]) ⇒ end=28=bsize ⇒ 无漂移
    assert tail_drift_conflict(28, [(0, 'BYTE'), (1, 'unsigned char[27]')]) is None
    # 真漂移形：end+8 < bsize
    assert tail_drift_conflict(100, [(0, 'BYTE')]) == 1
    # 对齐尾差（<=8 容差）：ComboAttack 形 end=630 bsize=632 ⇒ 无漂移
    assert tail_drift_conflict(632, [(606, 'short[12]')]) is None
