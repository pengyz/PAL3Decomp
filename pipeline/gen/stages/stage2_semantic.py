"""Stage 2: Semantic OOP rewrite (tree-sitter AST).

Converts Class::Method(obj, ...) -> obj->Method(...).
This is the only stage that produces NEW patterns (->ClassName(), ->__vftable->).
"""
from annotation_view import base_names as _base_names, base_entries as _base_entries
import sys
import os

# Ensure ast_transform is importable
_gen_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _gen_dir not in sys.path:
    sys.path.insert(0, _gen_dir)

from ast_transform import transform_oop_calls, transform_coerce_calls, cast_ptr_int_assignments
from data import store

_SLOTS_CACHE = None
_STRUCT_MEM_CACHE = None
_BASE_MAP_CACHE = None


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
        # [T56] 自由函数（functions.json → free_func_sigs）同喂 slots map：
        # thunk callee（compiler_init_* 族）是自由函数，method_sigs 不含 ⇒
        # sig_slots 门恒 None——T50/T56 两次 thunk 实验翻红的**真正根因**
        # （T51 修对了 this/thunk 门但 slots 喂入断，T26/T27 feed 族同根）。
        for _k, _sig in list((getattr(store, 'free_func_sigs', None) or {}).items()):
            _m = str(_k).split('(')[0]
            _pm2 = _re0.search(r'\((.*)\)\s*$', str(_sig))
            if not _pm2:
                continue
            _inner2 = _pm2.group(1).strip()
            if _inner2 == '...':
                continue                   # 变参形槽数未知 ⇒ 不入（禁猜测）
            _n2 = (_inner2.count(',') + 1) if (_inner2 and _inner2 != 'void') else 0
            _cnts.setdefault(_m, set()).add(_n2)
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
                _base_names = set()
                for _f, _ann in _av.iter_structs(directory=str(store.annotations_dir / 'structs')):
                    _cn = str(_ann.get('name') or _f[:-5])
                    for _mi in (_ann.get('known_members') or {}).values():
                        _pairs.append((str((_mi or {}).get('name') or ''),
                                       (_mi or {}).get('type'), _cn))
                    # 挂账② B1 步 2：+0 首基类名入集（非零偏移基类保守排除）
                    _bs = _ann.get('bases')
                    if isinstance(_bs, list):
                        for _bi, _b in enumerate(_bs):
                            if isinstance(_b, dict):
                                _off = _b.get('offset', 0 if _bi == 0 else None)
                                if _off == 0 and _b.get('name'):
                                    _base_names.add(str(_b['name']))
                    _bc = _base_names(_ann)
                    if _bc:
                        # N-F1 修（复核）：list 形（159/179）取 [0]——str.split 产垃圾名
                        if isinstance(_bc, list):
                            if _bc and _bc[0]:
                                _base_names.add(str(_bc[0]).split('::')[-1])
                        else:
                            _base_names.add(str(_bc).split('::')[-1])
                _STRUCT_MEM_CACHE = collect_struct_value_members(_pairs, _base_names)
            except Exception:
                pass
        code = fix_struct_value_casts(code, _STRUCT_MEM_CACHE)
        # 【挂账⑥类域数据源接线（复核 N-F2）】cls/base_map 生产启用——类域化收窄
        # （跨类同名标量防误伤的精确版；N-a 廉价收窄为兜底）
        _cls = getattr(ctx, 'cls_name', None) if ctx is not None else None
        if _cls and _STRUCT_MEM_CACHE:
            global _BASE_MAP_CACHE
            if _BASE_MAP_CACHE is None:
                _BASE_MAP_CACHE = {}
                try:
                    for _c, _bs in (getattr(store, 'struct_bases', None) or {}).items():
                        _BASE_MAP_CACHE[_c] = list((_bs or {}).keys())
                    import annotation_view as _av2
                    for _f, _ann in _av2.iter_structs(directory=str(store.annotations_dir / 'structs')):
                        _cn = str(_ann.get('name') or _f[:-5])
                        _BASE_MAP_CACHE[_cn + ':members'] = [
                            str((m or {}).get('name') or '')
                            for m in (_ann.get('known_members') or {}).values()]
                except Exception:
                    _BASE_MAP_CACHE = {}
            if _BASE_MAP_CACHE:
                code = fix_struct_value_casts(code, _STRUCT_MEM_CACHE,
                                              cls=_cls, base_map=_BASE_MAP_CACHE)
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
            slots_by_method=_SLOTS_CACHE,
            # [T27] 签名元数门：(name, 元数) 精准匹配 + sig 的 this 型为类
            sig_map=dict(getattr(store, 'method_sigs', None) or {}))
    except Exception:
        pass
    # [R91 2026-10-24·重归属战役 1a] 路由名调用形转写（裸形 + cast 形）。
    # 仅路由名（裸名→地址→归属唯一谓词，spec v2 换轴）——自由声明已移除的同批集合，
    # 与 data.py 的 free_func_sigs pop 成对（N1 教训：单侧拆拐杖 ⇒ C2065 洪泛）。
    # 时序保证：本器先于 stage5 的 `::` 加前缀；路由名不再在 free_func_sigs ⇒
    # stage5 自然跳过 ⇒ 不产生 ::Name( 形态（复核 B 顾虑的 16 站由此消解）。
    try:
        from ast_transform import rewrite_routed_free_calls
        code = rewrite_routed_free_calls(
            code, dict(getattr(store, 'routed_free_by_name', None) or {}))
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
    # [P2b 2026-10-19] 指针/浮点→整型赋值补强转（C2440 ×48 族 ✓ R15 三形）
    # 等价变换：4B 位槽不变（指针/float/ulong 同宽）✓ 字节等价
    code = cast_ptr_int_assignments(code)
    return code
