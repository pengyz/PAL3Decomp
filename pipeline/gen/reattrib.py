#!/usr/bin/env python3
"""自由函数重归属：纯判定逻辑（R91·2026-10-24 战役 Phase 1）。

## 判定谓词（v2 对抗复核换轴）

    裸名 → decomp 名索引唯一地址 → 地址归属唯一 (Cls, Method)

不用 (name,元数)-in-method_sigs 作主门：SetEnable/Update 被 50+ 类同名同元数
命中 ⇒ 恒不转 ⇒ 拆自由声明即 N1 复发（C2065 洪泛，2026-09-29 实证 S2 100→91）。

## 门（全部拒绝时保留自由形态，禁猜测）

  G1 地址归属存在          —— addr ∈ 注解 methods
  G2 类内撞名拒绝          —— (Cls, Method) 对应 ≥2 地址 ⇒ 双双不路由（C2084 实证：
                              PAL_GDB 0x479080/0x4791E0 同名同 sig）
  G3 名字一致              —— decomp 裸名 == 注解方法名（禁止改名路由；`_` 前缀漂移族
                              留给 Phase 2 逐条裁）
  G4 待裁排除              —— ReleaseAllTextures（归属类 vs 自由声明接收者类型矛盾，
                              复核裁决单列）
  G5 范围                  —— REATTRIB_SCOPE: batch0（默认，复核核实的 28 条零裸调用
                              名单）/ all / off
  G6 值引用拒绝            —— 名字在 decomp 语料中存在**非调用形态**引用（`(int)Name`
                              回调传值 / `&Name` 取址）⇒ 不路由（实证
                              ProcCommonTask__ovl 于 CEffect.cpp:560 作回调传值，
                              拆声明即 C2065；值传递只取地址无 ABI 损害，回调
                              调用约定属 Phase 2）
  G7 this 类型一致         —— decomp this 形参类型必须 == 归属类名（如 `RoleSystem *this`）。
                              泛型 this（`_BYTE *this` 族）的体按泛型渲染，路由成成员后
                              this 变 `Cls *const` ⇒ 体内部 vtable 调用/转型 C2664 浮出
                              （实测 GetUpdateFlag/GetInputFlag +14）。泛型 this = IDB
                              未重定型 ⇒ 留 Phase 2（IDB 重定型+重导出后自然过门）
"""
import os
import re

# 复核员 B 精确裸形态重数（29 条零裸调用）− ReleaseAllTextures（G4）= 28
ROUTED_BATCH0_NAMES = frozenset([
    'ClearActionArrays', 'ClearActionFlags', 'ClearAllActions', 'ClearAllocBuffers',
    'ClearModelFlag', 'ClearPathBuffer', 'CountAttackSequences', 'Create__ovl_1_0',
    'FlushCommandQueue', 'GetInputFlag', 'GetUpdateFlag', 'InitAnimSequence',
    'InitRound', 'LoadActions', 'LoadActorVisual', 'ProcCommonTask__ovl',
    'PtrVec_InsertN_64', 'PtrVec_InsertN_elem',
    'RenderActorGeometry', 'RenderActorTransform', 'RenderActorTransform2',
    'ResetAll', 'ResetDefaultState', 'ResetNameField', 'ResetTransformState',
    'SetCurrentAction', 'SetParam', 'operator_',
])

EXCLUDED_PENDING_ADJUDICATION = frozenset([
    'ReleaseAllTextures',   # 归属类 vs 自由声明接收者类型矛盾（复核 A 裁决单列）
    'InitRound',            # 体含 gbVec3D(&v,…) 显式 ctor 调用：free_functions.cpp 的
                            # include 集可见 4 参 ctor 而 CCBStage.cpp 不可见 ⇒ 路由后
                            # C2661 ×7（2026-10-24 实测）——待 include 层修复后放行
])


def _norm_addr(a):
    if isinstance(a, int):
        return a
    s = str(a).strip()
    try:
        return int(s, 16) if s.lower().startswith('0x') else int(s)
    except ValueError:
        return None


def build_attribution_index(structs_iter):
    """structs_iter: iterable of (path_or_key, struct_dict)（methods: addr→{name,signature}）

    → (addr_index {int_addr: (cls, method)}, multi {(cls, method): [addr, ...]})
    """
    addr_index = {}
    multi = {}
    for key, sd in structs_iter:
        # 类名唯一权威 = JSON 的 name 字段（T27 同约定）；回退 key 文件名
        cls = (sd or {}).get('name') or ''
        if not cls and isinstance(key, str):
            cls = os.path.basename(key)[:-5] if key.endswith('.json') else key
        if not cls:
            continue
        for addr_s, mv in ((sd or {}).get('methods') or {}).items():
            if not isinstance(mv, dict):
                continue
            m = str(mv.get('name') or '').split('(')[0]
            a = _norm_addr(addr_s)
            if not m or a is None:
                continue
            addr_index[a] = (cls, m)
            multi.setdefault((cls, m), []).append(a)
    return addr_index, multi


_PARAM_SPLIT = re.compile(r'\((.*)\)\s*$', re.S)
_THIS_TYPE = re.compile(r'__thiscall\s*\(\s*([\w]+)\s*\*?\s*(?:this\b)?')


def _decomp_this_type(sig):
    """decomp sig `int __thiscall(RoleSystem *this)` → 'RoleSystem'；解析失败 → None"""
    if not sig:
        return None
    m = _THIS_TYPE.search(sig)
    return m.group(1) if m else None


def _nonthis_param_count(sig):
    """decomp sig `int __thiscall(RoleSystem *this, int a)` → 非 this 形参数；解析失败 → None"""
    if not sig:
        return None
    m = _PARAM_SPLIT.search(sig)
    if not m:
        return None
    depth = 0
    parts, cur = [], ''
    for ch in m.group(1):
        if ch in '(<[':
            depth += 1
        elif ch in ')>]':
            depth -= 1
        if ch == ',' and depth == 0:
            parts.append(cur)
            cur = ''
        else:
            cur += ch
    if cur.strip():
        parts.append(cur)
    params = [p.strip() for p in parts if p.strip()]
    nonthis = [p for p in params if not re.search(r'\bthis\s*$', p)]
    return len(nonthis)


def decide_routing(free_candidates, addr_index, multi, scope=None, corpus_text=None):
    """free_candidates: [(name, addr, sig)]（decomp 无 :: 且 __thiscall 的候选）
    corpus_text: 全 decomp 体拼接文本（G6 值引用扫描；None = 跳过该门）

    → (routed_by_addr {int: (cls, method)}, routed_by_name {name: (cls, method, nparams)})
    """
    scope = scope or os.environ.get('REATTRIB_SCOPE', 'batch0')
    if scope == 'off':
        return {}, {}
    by_addr, by_name = {}, {}
    for name, addr, sig in free_candidates:
        a = _norm_addr(addr)
        hit = addr_index.get(a) if a is not None else None
        if not hit:                                              # G1
            continue
        cls, method = hit
        if len(multi.get((cls, method) or ('', ''), [])) > 1:    # G2
            continue
        if name != method:                                       # G3
            continue
        if name in EXCLUDED_PENDING_ADJUDICATION:                # G4
            continue
        if scope == 'batch0' and name not in ROUTED_BATCH0_NAMES:  # G5
            continue
        if corpus_text is not None and re.search(                # G6
                r'\b%s\b(?!\s*\()' % re.escape(name), corpus_text):
            continue
        if _decomp_this_type(sig) != cls:                        # G7
            continue
        n = _nonthis_param_count(sig)
        if n is None:
            continue
        by_addr[a] = (cls, method)
        by_name[name] = (cls, method, n)
    return by_addr, by_name
