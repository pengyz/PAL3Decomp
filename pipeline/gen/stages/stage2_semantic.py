"""Stage 2: Semantic OOP rewrite (tree-sitter AST).

Converts Class::Method(obj, ...) -> obj->Method(...).
This is the only stage that produces NEW patterns (->ClassName(), ->__vftable->).
"""
import sys
import os

# Ensure ast_transform is importable
_gen_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _gen_dir not in sys.path:
    sys.path.insert(0, _gen_dir)

from ast_transform import transform_oop_calls, transform_coerce_calls
from data import store

_SLOTS_CACHE = None
_STRUCT_MEM_CACHE = None


def run(code, ctx):
    """Apply OOP call transformation."""
    global _SLOTS_CACHE
    if _SLOTS_CACHE is None:
        import re as _re0
        _cnts = {}
        for _k, _sig in list((getattr(store, 'method_sigs', None) or {}).items()):
            _m = _k.split('::')[-1].split('(')[0]
            _pm = _re0.search(r'\((.*)\)\s*$', str(_sig))
            if not _pm:
                continue
            _inner = _pm.group(1).strip()
            _n = (_inner.count(',') + 1) if (_inner and _inner != 'void') else 0
            if _re0.search(r'\bthis\b\s*$', _inner.split(',')[0]):
                _n = max(0, _n - 1)
            _cnts.setdefault(_m, set()).add(_n)
        _SLOTS_CACHE = {m: next(iter(s)) for m, s in _cnts.items() if len(s) == 1}
    code = transform_oop_calls(code, static_methods=store.static_methods,
                               cls_name=ctx.cls_name)
    # 【批 3】结构体值铸标量 &-补全（CCBUIPanel m_Slots 族）
    try:
        from ast_transform import fix_struct_value_casts
        global _STRUCT_MEM_CACHE
        if _STRUCT_MEM_CACHE is None:
            _STRUCT_MEM_CACHE = set()
            try:
                import annotation_view as _av
                from ast_transform import collect_struct_value_members
                _pairs = []
                for _f, _ann in _av.iter_structs(directory=str(store.annotations_dir / 'structs')):
                    for _mi in (_ann.get('known_members') or {}).values():
                        _pairs.append((str((_mi or {}).get('name') or ''),
                                       (_mi or {}).get('type')))
                _STRUCT_MEM_CACHE = collect_struct_value_members(_pairs)
            except Exception:
                pass
        code = fix_struct_value_casts(code, _STRUCT_MEM_CACHE)
    except Exception:
        pass
    # 【批 E C2065#1】丢类限定的成员调用转写（ReleaseTexture((UIScene*)this) 族）
    try:
        from ast_transform import rewrite_unqualified_member_call
        _map = {}
        for _k in list(getattr(store, 'method_sigs', None) or {}):
            if '::' in _k:
                _c, _m = _k.split('::', 1)
                _map.setdefault(_c, set()).add(_m.split('(')[0])
        # ⚠️ 宽 map（struct methods 全量）已证损伤（四绿丢失）⇒ 窄 map（method_sigs）=S2-100 态。
        # ⚠️ 失实修正（5a7a3b86）：此前注"OffsetRect 由 functions.json 条目喂入 ✓"——探针证伪
        # （PalScript::OffsetRect 不在 method_sigs、rewrite 不触发）——裸名方法的喂入路径仍断（挂账）。
        code = rewrite_unqualified_member_call(
            code, _map,
            exclude={str(s).split('(')[0] for s in (getattr(store, 'static_methods', None) or ())},
            slots_by_method=_SLOTS_CACHE)
    except Exception:
        pass
    # 【批 E C2660 族】echo 形剔除（(int)this 回波首参 + ret-N/签名槽数证据门）
    try:
        from ast_transform import drop_call_echo_arg
        code = drop_call_echo_arg(code, _SLOTS_CACHE or {})
    except Exception:
        pass
    # 【2026-09-15 加】COERCE_FLOAT/T 实参为**函数调用**时改用辅助函数
    # （宏内部对实参取地址，而 MSVC6 不允许对 rvalue 取地址 ⇒ C2102）。
    # 放在 OOP 变换**之后**：此时调用形态已稳定，再判"实参是不是调用"更准。
    code = transform_coerce_calls(code)
    return code
