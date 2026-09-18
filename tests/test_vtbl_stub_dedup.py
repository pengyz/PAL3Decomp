"""vtable stub 命名与去重的回归测试（先写用例，确认它**现在是坏的**）。

# 已实测的缺陷（2026-09-18）

`pipeline/gen/stages/stage3_cleanup.py` 在遇到无法解析的 vtable 派发时合成一个 stub：

    static int pal3_vtbl_unk_0(UIStatic **, int);

stub 的名字用 `idx = len(stub_items)`，而 `stub_items` 是**每次 `_resolve_vftable_calls_ast`
调用（= 每个函数）局部新建**的 ⇒ **同一个 .cpp 里每个函数都从 `_0` 重新编号**。

实测后果（在当前提交态生成树上）：
- 51 个文件含 stub 块，其中 **22 个文件含多于一个块**（`Combat/CCBUI.cpp` 有 **16 个块**）
- **22 个文件存在同名但不同签名的重复定义** ⇒ MSVC 报
  `C2084`(already has a body) / `C2371`(redefinition; different basic types) /
  `C2556`(overloaded function differs only by return type)

本测试断言**应有的性质**，不依赖仓库当前状态：
1. stub 名由**签名**决定 —— 不同签名必须得到不同名字；
2. 同一文件内**同签名只发射一次定义**（靠传入的共享 registry 去重）；
3. 去重后调用点仍然引用该名字（声明在上面已可见）。
"""
import re
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
for p in ("pipeline/gen", "pipeline", "."):
    sys.path.insert(0, str(PROJECT_ROOT / p))

from stages.stage3_cleanup import run as stage3_run  # noqa: E402

# 两个**签名不同**、但按旧实现会拿到同名 `_0` 的输入
CALL_A = ("int CCBUI::F()\n{\n  int v2;\n"
          "  return ((int ( *)(UIStatic **, int))this->m_pAttackSequenBack->__vftable)"
          "(&this->m_pAttackSequenBack, v2);\n}\n")
CALL_B = ("int CCBUI::G()\n{\n"
          "  return (*(int (__thiscall **)(UIStatic *, int, int *, CCBUI *))v3->__vftable)"
          "(v3, 1, &v8, this);\n}\n")

_DEF = re.compile(r'^static\s+\S[^\n(]*?(pal3_vtbl_unk_\w+)\s*\([^;]*\)\s*$', re.M)
_NAME = re.compile(r'pal3_vtbl_unk_\w+')


class _Ctx:
    """最小 ctx；`stub_registry` 模拟"同一输出文件内共享"的去重集合。"""
    cls_name = 'CCBUI'
    is_free_function = False
    sig = ''

    def __init__(self, registry):
        self.stub_registry = registry


def _names(code):
    return set(_NAME.findall(code))


def _defined(code):
    """本段代码里**定义**（行尾无分号）的 stub 名。"""
    return set(_DEF.findall(code))


def test_different_signatures_get_different_stub_names():
    """不同签名 ⇒ 不同 stub 名（旧实现两者都是 pal3_vtbl_unk_0）。"""
    reg = set()
    a = stage3_run(CALL_A, _Ctx(reg))
    b = stage3_run(CALL_B, _Ctx(reg))
    assert 'pal3_vtbl_unk_' in a and 'pal3_vtbl_unk_' in b, (a, b)
    assert _names(a).isdisjoint(_names(b)), (
        "两个不同签名拿到了相同的 stub 名：%s vs %s" % (_names(a), _names(b)))


def test_same_signature_is_defined_once_per_file():
    """同一文件内同签名只发射一次定义；第二次只复用名字。"""
    reg = set()
    a1 = stage3_run(CALL_A, _Ctx(reg))
    a2 = stage3_run(CALL_A, _Ctx(reg))      # 同签名、同文件（共享 registry）
    assert len(_defined(a1)) == 1, _defined(a1)
    assert len(_defined(a2)) == 0, (
        "同签名第二次仍发射了定义（会触发 C2084）：%s" % _defined(a2))
    # 调用点仍必须引用该名字（声明在第一次时已发射、位于其上方）
    assert _names(a2), "第二次没有引用 stub 名字"


def test_assembled_file_has_one_definition_per_name():
    """把一段"文件"逐函数跑完后拼起来：每个 stub 名只应有一个定义。"""
    reg = set()
    parts = [stage3_run(CALL_A, _Ctx(reg)), stage3_run(CALL_B, _Ctx(reg)),
             stage3_run(CALL_A, _Ctx(reg)), stage3_run(CALL_B, _Ctx(reg))]
    whole = '\n'.join(parts)
    defs = _DEF.findall(whole)
    assert defs, "没有找到任何 stub 定义"
    dup = [n for n in set(defs) if defs.count(n) > 1]
    assert not dup, "拼接后仍有重复定义：%s" % dup
    # 两个签名 ⇒ 恰好两个名字
    assert len(set(defs)) == 2, set(defs)


def test_no_registry_degrades_safely():
    """未传 registry 时不得崩溃（保持可用），且名字仍由签名决定。"""
    class Ctx:
        cls_name = 'CCBUI'
        is_free_function = False
        sig = ''
    out = stage3_run(CALL_A, Ctx())
    assert 'pal3_vtbl_unk_' in out
    assert len(_defined(out)) == 1


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