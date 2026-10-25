"""vfptr_slot 标记 × _has_dtor 门拆分（R94c·2026-10-25）。

背景（CEffect 案第八轮）：@0=__vftable+vfptr_slot:true 的类若 methods 带
~Cls ⇒ _will_inject_vptr=False ⇒ static 占位不触发 ⇒ _gap_004 照发 ⇒ +4。
门语义混淆：_has_dtor 本意管"虚析构注入"（防 C2535 重复 dtor），
不该连带否决 static 占位/尾部预留（这两者与 dtor 注入正交）。

拆分：
  _will_inject_vptr —— 仅 dtor 注入（2783），原语义不变（CEff* 家族回归锁）
  _vfptr_reserved   —— static 占位（2434）+ 尾部预留（2758），
                       = _will_inject_vptr or (vfptr_slot 标记 and not template_expr)
"""
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / "pipeline" / "gen"))
sys.path.insert(0, str(REPO / "pipeline" / "gen" / "stages"))


def _gate(cls_name, methods, vfptr_slot_marked=True, template_expr=None,
          offset0_is_vptr=False, scalar_dtor_cls=False, offset0_placeholder=False):
    """复刻 emit_headers 的门逻辑（拆分后形态），返回 (inject, reserved)。"""
    import emit_headers as EH
    has_dtor = any(m for m, _, _ in (methods or []) if m == '~' + cls_name)
    # 模拟 _vfptr_slot_marked/_offset0_* 的注入式判定
    marked = vfptr_slot_marked
    inject = (not has_dtor) and not template_expr and (
        marked or (offset0_is_vptr and (scalar_dtor_cls or offset0_placeholder)))
    reserved = inject or (marked and not template_expr)
    return inject, reserved


def test_dtor_plus_vfptr_slot_reserved_not_inject():
    """CEffect 形态：有 dtor + vfptr_slot 标记 ⇒ 占位/预留 True，dtor 注入 False."""
    inject, reserved = _gate('CEffect', [('~CEffect', 'void __fastcall(CEffect *this)', '0x4D3950')])
    assert inject is False, "有 dtor 不得再注入 virtual ~Cls（C2535）"
    assert reserved is True, "vfptr_slot 标记 ⇒ static 占位+尾部预留必须生效"


def test_no_dtor_vfptr_slot_unchanged():
    """CEff* 家族回归锁：无 dtor + 标记 ⇒ 注入/预留都 True（原行为）。"""
    inject, reserved = _gate('CEffShock', [])
    assert inject is True
    assert reserved is True


def test_no_mark_no_inject():
    """无标记无 dtor ⇒ 原语义（不注入不预留）。"""
    inject, reserved = _gate('PlainCls', [('Foo', 'int __thiscall(int)', '0x1')],
                             vfptr_slot_marked=False)
    assert inject is False
    assert reserved is False


def test_template_expr_blocks_both():
    """模板特化：两者都 False（C2523 回归锁）。"""
    inject, reserved = _gate('CTaskTpl_X', [], template_expr='CTaskTpl<int>')
    assert inject is False
    assert reserved is False
