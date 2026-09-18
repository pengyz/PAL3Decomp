"""限定形 `this->A::B::__vftable` 的**三态判定**回归测试。

背景：`_fold_vftable_mask` 原先整块跳过限定形（docstring 记为
"qualified base accesses `X->Base::__vftable` — base offset unknown"），
那是全仓最大的单一机制（741 条错误 / 38 文件）。现在按**可证**的信息分三态处理：

| 态 | 条件 | 处理 |
|---|---|---|
| `offset` | 链上每一级都是**已知偏移**的基类 | 折算成 `(char *)OBJ + OFF` 的字节等价式 |
| `strip` | 链上某级**根本不是**所在类的基类（`base_class` 名单可证） | 该限定符是 IDB 残留 ⇒ 按**未限定**语义（对象自身 vfptr，偏移 0） |
| `skip` | 该级**是**基类但偏移未知 | **原样保留**，绝不猜 |

`strip` 的可证性举例：`UIScrollBar` 尺寸 352 < `UIListBox` 尺寸 1208，
而基类子对象必然包含在派生类里 ⇒ `UIScrollBar` 不可能派生自 `UIListBox`。
实测该情形在 `Misc/CCBUIPanel.cpp` 有 50 条（`this->m_scrollbar.UIListBox::__vftable`）。
"""
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
for p in ("pipeline/gen", "pipeline", "."):
    sys.path.insert(0, str(PROJECT_ROOT / p))

from stages import stage3_cleanup as s3  # noqa: E402
from data import store  # noqa: E402

store.load()          # 必须：struct_bases / struct_base_names / struct_members 都在 store 上


class _Ctx:
    def __init__(self, cls):
        self.cls_name = cls
        self.is_free_function = False
        self.sig = ''
        self.stub_registry = None


def _xform(cls, body):
    return s3.run('void %s::F()\n{\n  %s\n}\n' % (cls, body), _Ctx(cls))


def test_offset_state_ceff_family():
    """A 级偏移（CEff 族 CTaskTpl 基 = 12）⇒ 折算出 (char *)this + 12。"""
    out = _xform('CEffCylinder',
                 'int v = *((int *)&this->CTaskTpl_tagEffTaskParam_CEffCylinder::__vftable + 7);')
    assert '__vftable' not in out
    assert '+ 12' in out, out


def test_strip_state_not_a_base():
    """限定符不是基类 ⇒ 按未限定语义（offset 0），不得残留 `X::__vftable`。"""
    out = _xform('CCBUIPanel',
                 'this->m_scrollbar.UIListBox::__vftable = (void *)800;')
    assert '__vftable' not in out, out
    assert 'm_scrollbar' in out, out


def test_skip_state_is_a_base_but_offset_unknown():
    """是基类但偏移未知 ⇒ **必须原样保留**（不猜）。"""
    out = _xform('CCBRoleState',
                 '*((_DWORD *)&this->SceneObj::TaskMgr_SceneObjParam_SceneObj::__vftable + 9) = 0;')
    assert '__vftable' in out, "偏移未知时不该改写：%s" % out


def test_skip_state_glowobj():
    """`SceneObj::GlowObj` 同理：是基类、偏移无二进制证据 ⇒ 原样保留。"""
    out = _xform('SceneObj', '*((_DWORD *)&this->GlowObj::__vftable + 1) = 0;')
    assert '__vftable' in out, out


def test_unqualified_still_works():
    """未限定形不受影响（回归护栏）。

    注意：**vftable 调用**形态（`(*(...))(obj)`）由 `_resolve_vftable_calls_ast` 先消费成
    stub，`__vftable` 会留在 `// [VFTABLE-STUB] original:` **注释**里 ——
    所以这里用**读写**形态断言折叠结果。
    """
    out = _xform('Test', 'v = this->m_pObj->__vftable;')
    assert '__vftable' not in out, out
    assert '(*(void **)(this->m_pObj))' in out, out
    out2 = _xform('Test', 'this->m_pObj->__vftable = 0;')
    assert '(*(void **)(this->m_pObj))' in out2, out2


def test_unknown_object_type_is_left_alone():
    """对象类型取不到 ⇒ 不动（**不做任何推断**）。"""
    out = _xform('Test', 'v->UIListBox::__vftable = 0;')
    assert '__vftable' in out, "对象类型未知时不该改写：%s" % out


def test_evidence_for_strip_is_size_contradiction():
    """`strip` 的依据本身可复核：UIScrollBar 比 UIListBox 小 ⇒ 不可能派生。"""
    assert 'UIListBox' not in s3._base_names_of('UIScrollBar')
    assert 'UIWnd' in s3._base_names_of('UIScrollBar')


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