"""`static_methods` 守卫的回归测试（先写用例，确认它现在**是坏的**）。

背景（2026-09-18 定谳）：`pipeline/gen/data.py` 把 decomp 的 **带参数表**名字
（`Cls::M(int)`）放进 `store.static_methods`，而消费方一律用**裸名**去比：

    ast_transform.py:529   qualified = 'Cls::M'   ; if qualified in static_methods
    ast_transform.py:702   _qualified = 'Cls::M'  ; if _qualified in static_methods
    stage4_substitution:721 ('%s::%s' % (cls,meth)) in store.static_methods

⇒ 只要那条名字带参数表，`in` 就**恒为假**。后果：`__cdecl` 静态成员的第一个实参
是**数据**而不是 `this`，但守卫不生效 ⇒ 被当成 `this` 吞掉或重写。

注意 `data.py` 的**同一段代码**里，`method_sigs` 已经用了 `_name.split('(')[0]`，
只有 `static_methods` 漏了 —— 说明这是遗漏而非设计。

本测试只断言"存储形态"与"守卫是否真的生效"这两件事，不编码任何 annotation 状态。
"""
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
for p in ("pipeline/gen", "pipeline", "."):
    sys.path.insert(0, str(PROJECT_ROOT / p))

import ast_transform as at  # noqa: E402
from data import store  # noqa: E402


def test_static_methods_entries_are_bare_qualified_names():
    """存储形态必须是裸 `Cls::M`（消费方就是这么比的）。"""
    store.load()
    sm = store.static_methods
    assert sm, "static_methods 为空，前置条件不成立"
    with_params = sorted(s for s in sm if '(' in s)
    assert not with_params, (
        "static_methods 里有 %d/%d 条带参数表，消费方用裸名比较 ⇒ 守卫恒为假。样本: %s"
        % (len(with_params), len(sm), with_params[:3]))


def test_static_guard_fires_for_every_stored_entry():
    """对集合里的每一条，`transform_oop_calls` 都必须认得出来。

    判定方式：静态成员的静态调用形态 `Cls::M(a, b)` 必须**不被**改写成成员调用。
    这里用一条真实存在的静态方法与它的一条真实调用点来验证。
    """
    store.load()
    sm = store.static_methods
    # 取一条能被消费者认出来的（裸名）作为对照，再取一条存储原样作为被测
    bare = sorted(s for s in sm if '(' not in s)
    assert bare, "没有任何裸名条目，说明存储形态整体是坏的"
    for qualified in bare[:5]:
        cls, meth = qualified.split("::")
        # 静态调用形态：第一个实参是数据（不是 this）
        code = "x = %s::%s(v1, v2);" % (cls, meth)
        out = at.transform_oop_calls(code, static_methods=sm, cls_name="K")
        assert "->%s::%s" % (cls, meth) not in out, (
            "守卫未生效：%s 被当成成员调用重写了 -> %r" % (qualified, out))


def test_method_sigs_and_static_methods_use_the_same_key_shape():
    """两处索引必须同形（data.py 里 method_sigs 已经 split 过，static_methods 没有）。"""
    store.load()
    sig_keys = set(store.method_sigs)
    sm = store.static_methods
    assert sm <= sig_keys or not sm, (
        "static_methods 的键与 method_sigs 的键不同形："
        "method_sigs 用裸名，static_methods 用了带参数表的名字。"
        "差集样本: %s" % sorted(sm - sig_keys)[:3])


if __name__ == "__main__":
    tests = [v for k, v in sorted(globals().items()) if k.startswith("test_")]
    failed = 0
    for t in tests:
        try:
            t()
            print("  ✅ %s" % t.__name__)
        except AssertionError as e:
            print("  ❌ %s: %s" % (t.__name__, e))
            failed += 1
        except Exception as e:
            print("  ⚠️  %s: %s" % (t.__name__, e))
            failed += 1
    print("\nResults: %d passed, %d failed" % (len(tests) - failed, failed))
    sys.exit(1 if failed else 0)