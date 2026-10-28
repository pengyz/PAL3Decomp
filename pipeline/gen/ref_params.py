"""[TOS 2026-10-28·ref 参数机制单一真相源] 唯一实现体。

合并自 stage3_cleanup._fix_ref_params（85 行子集+_tail_000 尾折叠）与
stage5_fixup._fix_ref_params（80 行超集：Case1 剥 & / Case2 指针→ref 补 * /
Case3 ctx 证据门 / 元数感知）。设计对抗复核定稿：
data/status/review_ref_tos_merge_design_20261028.md（D0 尾折叠随迁、
D0' 调用点必传 ctx 防无证据门退化）。宪法：stage↔stage 零互引，共享物下沉于此。

导入约定：`from pipeline.gen.ref_params import ...`（绝对形，禁相对/平铺形
——双注册会致 is 身份断言假红）；本模块内 store 用平铺形与 stage 同对象。
"""
import re

from data import store
from pipeline.gen.tables import _GB_REF_PARAM_FUNCS

_GB_REF_PARAM_TYPES = {
    ('gbMatrixStack::Rotate', 1): 'struct gbVec3D',  # B 修键随迁（失配致 Case2b 不触发 C2100 +24 实证）
    ('Translate', 0): 'struct gbVec3D',     # :158 Translate(gbVec3D&)
    ('Scale', 0): 'struct gbVec3D',         # :154 Scale(gbVec3D&)
    ('LeftTranslate', 0): 'struct gbVec3D', # gbengine_types.h:128
    ('RightTranslate', 0): 'struct gbVec3D',
    ('MakeMatrix', 0): 'struct gbVec3D',    # gbengine_types.h:131
    ('MakeMatrix', 1): 'struct gbVec3D',
    ('MakeMatrix', 2): 'struct gbVec3D',
    ('LeftMultiply', 0): 'struct gbMatrix4',
    ('IntersectPlane', 0): 'struct gbVec3D',  # gbengine_types.h:197
    ('IntersectPlane', 1): 'struct gbVec3D',
    ('IsColAABB', 0): 'struct gbAABBox',
    ('gbRay::IsColOBB', 0): 'struct gbOBBox', ('gbPlane::IsColOBB', 0): 'struct gbOBBox',
    ('IsColOBB_H', 0): 'struct gbOBBox',
    ('IsColQuad', 0): 'struct gbVec3D',
    ('IsColQuad', 1): 'struct gbVec3D',
    ('IsColQuad', 2): 'struct gbVec3D',
    ('IsColSphere', 0): 'struct gbSphere',
    ('IsColTriangle', 0): 'struct gbVec3D',
    ('IsColTriangle', 1): 'struct gbVec3D',
    ('IsColTriangle', 2): 'struct gbVec3D',
    ('IsColTriangle', 3): 'struct gbVec3D',
}

# NOTE (F1b): 'SetAxisAngle': {0} was WRONG and has been deleted.
# `gbengine/gbengine.def` (authoritative, compiler-emitted mangled names):
#   ?SetAxisAngle@gbQuaternion@@QAEXPAUgbVec3D@@M@Z  -> (gbVec3D *, float)  = POINTER
#   ?SetAxisAngle@gbMatrix4@@QAEXPAUgbVec3D@@M@Z     -> (gbVec3D *, float)  = POINTER
#   ?SetAxisAngle@gbMatrix4@@QAEXW4gbAxis@@M@Z       -> (gbAxis, float)
#   ?SetAxisAngle@gbMatrix4@@QAEXW4gbAxis@@MM@Z      -> (gbAxis, float, float)
# `PAU` = pointer, not `AAU` = reference — contradicting the `Translate`/`Rotate`
# family this table was built for.  Treating arg 0 as a reference (a) stripped a
# required `&`, and (b) for the static form `Cls::SetAxisAngle(&this_, axis, f)`
# it consumed the `this` argument and shifted every later argument by one.
# Deleting the entry makes the pass leave `SetAxisAngle` alone, restoring the
# decompiler's own `&` (e.g. `SetAxisAngle(&v4, 0, angle)`).

# NOTE (F3): 'SetBlend': {0} was WRONG and has been deleted (修复轮 2, 任务 3 副作用).
# `gbengine/gbengine.def` (authoritative, compiler-emitted mangled names):
#   ?SetBlend@gbVisNode@@QAEXW4NodeBlend@@M@Z  -> void (NodeBlend, float) = VALUE params
#   ?GetBlend@gbVisNode@@QAE?AW4NodeBlend@@AAM@Z -> NodeBlend (float &) = ref@0, stays
# `W4NodeBlend@@` + `M` carry neither `P` (pointer) nor `A` (reference) — and
# `include/gbengine/gbVisNode.h:78` agrees: `void SetBlend(NodeBlend mode, float value);`
# vs `:79  NodeBlend GetBlend(float& outValue);`.  Task 3 (enum IAT slot sigs) made
# Hex-Rays render enum constant names at these call sites; Case 3 then dereferenced
# the constant (`*BLEND_ALPHA`) => C2100.  Same lesion class as F1b.
# Measured (修复轮 2 full-chain, 2026-10-09):
#   C2100 27→18  (the 9 SetBlend sites: CCBStage 6→0, RoleSystem 8→6, RenderTarget2 1→0)
#   total errors 1724→1721  (C2100 −9, C2664 +6 — the +6 are CCBStage's C1003-capped
#     hidden tail surfacing at L8053..L8088 (max_line 8046→8088), 'sub_445D20' family,
#     unreachable by this change, which only touches `SetBlend(` args)
#   S2 102/210 unchanged (all 3 affected units stay red for unrelated errors)
#   L1 86 (521/614, partial 374) unchanged, ratchet 85→86, no --rebaseline

# Local kinds that are positive evidence the identifier is NOT a `T` pointed at
# by the reference parameter (see the F1a gate in `_fix_single_ref_arg`).

_NON_POINTER_LOCAL_KINDS = frozenset(('value', 'array', 'fnptr'))





_DECL_KEYWORDS = frozenset(('return', 'goto', 'case', 'delete', 'new', 'else', 'sizeof'))




def _split_top_commas(s):
    parts, depth, cur = [], 0, []
    for ch in s:
        if ch in '(<[':
            depth += 1
        elif ch in ')>]':
            depth -= 1
        if ch == ',' and depth == 0:
            parts.append(''.join(cur))
            cur = []
        else:
            cur.append(ch)
    if cur:
        parts.append(''.join(cur))
    return parts

def _build_var_types(code, ctx):
    """Map local/param names to declared types for pointer-ness decisions.
    批 8 修（vt 跨函数混淆）：同名多 kind ⇒ 标 ambiguous（判别保守 False——
    不按别的函数的声明裁决本函数表达式）。"""
    vt = {}
    # fnptr locals:  int ( **v12)(CEffect *, int);
    for m in re.finditer(r'^\s+([A-Za-z_]\w*)\s*\(\s*(\*+)\s*(\w+)\s*\)\s*\(([^()]*)\)\s*;',
                         code, re.M):
        vt[m.group(3)] = {'kind': 'fnptr', 'ret': m.group(1).strip(),
                          'params': m.group(4), 'stars': len(m.group(2))}
    # pointer locals:  UIButton *pButton;  unsigned char *v2;
    for m in re.finditer(r'^\s+((?:(?:unsigned|signed|const|struct|class|enum)\s+)*[A-Za-z_]\w*)'
                         r'\s*(\*+)\s*(\w+)\s*;', code, re.M):
        if m.group(1) not in _DECL_KEYWORDS:
            vt.setdefault(m.group(3), {'kind': 'ptr', 'base': m.group(1),
                                       'stars': len(m.group(2))})
    # value locals:  int v10;  unsigned long v3;  unsigned long reg_EDI = 0;（含初始化）
    # 批 7（2026-09-29）：初始化形补——F83 注入的 `unsigned long reg_X = 0;` 此前不入 vt
    # ⇒ reg_ 族 C2440 精确铸不触发（三判别器仅 vt 间隙，实测定位）
    for m in re.finditer(r'^\s+((?:(?:unsigned|signed|const|struct|class|enum)\s+)*[A-Za-z_]\w*)'
                         r'\s+(\w+)\s*(?:=\s*[^;]+)?;', code, re.M):
        if m.group(1) not in _DECL_KEYWORDS:
            vt.setdefault(m.group(2), {'kind': 'value', 'base': m.group(1), 'stars': 0})
    # array locals:  unsigned long v10[4];  (element type = base)
    for m in re.finditer(r'^\s+((?:(?:unsigned|signed|const|struct|class|enum)\s+)*[A-Za-z_]\w*)'
                         r'\s+(\w+)\s*\[[^\]]+\]\s*;', code, re.M):
        if m.group(1) not in _DECL_KEYWORDS:
            vt.setdefault(m.group(2), {'kind': 'array', 'base': m.group(1), 'stars': 0})
    # parameters from ctx.sig: "... __cc(Cls *this, int nVal)"
    sig = getattr(ctx, 'sig', '') or ''
    pm = re.search(r'__(?:thiscall|cdecl|stdcall)\s*(?:[A-Za-z_][\w:]*\s*)?\((.*)\)\s*$', sig)
    if pm:
        for p in _split_top_commas(pm.group(1)):
            p = p.strip()
            if not p or p == 'void':
                continue
            nm = re.search(r'(\w+)\s*(?:\[[^\]]*\])?\s*$', p)
            if not nm:
                continue
            name = nm.group(1)
            if name == 'this':
                continue  # `this` is never an assignable local; assigning to
                # it (Hex-Rays ctor artifact) must stay uncast
            # base = param text without the name (else the name leaks into
            # synthesized casts, e.g. `(Cls *this *)`)
            base = p[:nm.start()].strip() or p
            # array params decay to pointers
            is_ptr = '*' in p or '[' in p
            vt.setdefault(name, {'kind': 'ptr' if is_ptr else 'value',
                                 'base': base, 'stars': max(p.count('*'), 1)})
    return vt

def _fix_single_ref_arg(arg, vt=None, ref_type=None):
    """Fix a single argument for a reference parameter.

    Case 1: starts with '&'  → strip '&'
    Case 2: cast-to-pointer  → add '*' before the cast: (T*)x → *(T*)x
    Case 2b (F81): `*IDA-artifact global` with known ref type → *(T *)&global
    Case 3: plain identifier  → add '*':  pBox → *pBox  **only with evidence**

    Case 3 evidence gate (F1a).  Case 3 used to fire on the *text shape*
    alone (`^\\s*\\w+\\s*$`), which double-applies the `&`-strip that stage 3
    already performed on the SAME table:

        decomp `Rotate(v10, &v15)`  --stage3 Case1-->  `Rotate(v10, v15)`
                                    --stage5 Case3-->  `Rotate(v10,  *v15)`  (C2100)

    The generated text carries a reproducible fingerprint of this: the extra
    `', '` separator emitted by `_fix_ref_params` plus Case 3's preserved
    leading whitespace yields a DOUBLE space — `Rotate(v10,  *v15)`.  A
    decompiler-authored `*v15` would give a single space.

    The fix requires positive evidence from this function's own declarations
    (`_build_var_types`, the same table the C2440 fixer uses):

      * `ptr`               → keep the legacy `*`  (e.g. `Translate(*v5)`
                              where `gbVec3D *v5;` — genuinely a pointer)
      * `value`/`array`/
        `fnptr`             → leave the bare identifier alone.  `&`-stripping
                              is what produced this shape, so the reference
                              argument is the object itself (`Rotate(…, v15)`
                              with `struct gbVec3D v15; // BYREF`).
      * unknown (globals,
        members, …)         → keep the legacy `*` — conservative, no change.

    This is an equivalence-preserving transform, not invention: the verdict
    comes from declarations already present in the same function text.
    """
    arg_stripped = arg.lstrip()
    # Case 1: &arg → arg
    if arg_stripped.startswith('&') and not arg_stripped.startswith('&&'):
        return arg_stripped[1:]
    # Case 2: cast-to-pointer  (Type *)expr  or  (Type *)__thiscall
    cast_m = re.match(r'^(\s*\([^)]*\*\)\s*)', arg)
    if cast_m:
        return '*' + arg
    # Case 2b (F81): `*无型数据全局` 作引用实参 —— Hex-Rays 对未定型 stru_/dword_
    # 等全局渲染裸解引用，MSVC6 的 T& 只绑同型左值 ⇒ C2100。用被调方 SDK 头的
    # 参数类型重写为 `*(T *)&全局`（同一对象的再解释绑定，语义等价）。
    deref_m = re.match(r'^\s*\*\s*((?:stru|byte|word|dword|flt|dbl|unk)_[0-9A-Fa-f]+)\s*$', arg)
    if deref_m and ref_type:
        return '*(%s *)&%s' % (ref_type, deref_m.group(1))
    # Case 3: plain identifier (simple variable name, NOT numeric constants)
    ident_m = re.match(r'^(\s*)(\w+)\s*$', arg)
    if ident_m and not ident_m.group(2).isdigit():
        vt = vt or {}
        kind = (vt.get(ident_m.group(2)) or {}).get('kind')
        if kind in _NON_POINTER_LOCAL_KINDS:
            # Positive evidence this is not a pointer: the `&` stage 3 removed
            # was the reference-taking one.  Leave the object expression.
            # 【批 E】array 形补 [0]（Camera:165 pTarget gbVec3D[2]→gbVec3D& C2664
            # 缺角）：数组实参绑引用=首元素绑定，`arg[0]` 与基址传递字节等价。
            if kind == 'array':
                return ident_m.group(1) + ident_m.group(2) + '[0]'
            return arg
        # F81b: the identifier is an already-typed global - decide based on the emitted type. Example: stru_17A7E78 is
        # `struct gbVec3D` in globals.h (object not pointer), and the reference binding of Rotate(_, gbVec3D&)
        # wants the object itself => bare name; only pointer slots (`T *`) get `*` added.
        if ref_type:
            _gt = (store.global_types.get(ident_m.group(2)) or '').strip()
            if _gt:
                _norm = lambda t: re.sub(r'^(?:struct|class|enum|union)\s+', '', t.strip())
                if not _gt.endswith('*') and _norm(_gt) == _norm(ref_type):
                    return arg  # object-type global: bare name binds reference
                # 【批 E】全局数组型→引用参：`gbVec3D [2]` 形补 [0]（同局部 array 分支）
                if re.match(r'^%s\s*\[[0-9]+\]$' % re.escape(_norm(ref_type)), _norm(_gt)):
                    return ident_m.group(1) + ident_m.group(2) + '[0]'
                if _gt.endswith('*'):
                    return ident_m.group(1) + '*' + ident_m.group(2)
        return ident_m.group(1) + '*' + ident_m.group(2)
    # Unknown pattern — leave unchanged to be safe
    return arg

def _fix_ref_params(code, ctx=None):
    """Fix arguments passed to functions that take reference params.

    Two cases handled:
    1. Hex-Rays outputs &arg for reference params  → strip &:
       obj->Translate(&vec)   → obj->Translate(vec)
    2. Hex-Rays passes a pointer/cast-pointer to a reference param → add *:
       obj->GetAABBox(pBox)   → obj->GetAABBox(*pBox)
       obj->Translate((T*)&x) → obj->Translate(*(T*)&x)

    `ctx` is threaded in only to supply local-declaration evidence for the
    Case 3 gate in `_fix_single_ref_arg`; omitting it degrades to the legacy
    (evidence-free) behaviour.
    """
    vt = _build_var_types(code, ctx) if ctx is not None else {}
    for func_name, ref_indices in _GB_REF_PARAM_FUNCS.items():
        # B 修：限定键（`Cls::fn`）与裸名双形——限定形按全名匹配（类消歧），
        # 元数感知值（dict{arity:set}）按实参数选位（gbMatrixStack::Rotate 双载）
        if '::' in func_name:
            pattern = re.escape(func_name) + r'\s*\('
        else:
            pattern = r'(?:->|::|\.)' + re.escape(func_name) + r'\s*\('
        pos = 0
        result = []
        while True:
            m = re.search(pattern, code[pos:])
            if not m:
                result.append(code[pos:])
                break
            call_start = pos + m.end()
            result.append(code[pos:call_start])
            depth = 1
            arg_start = call_start
            arg_idx = 0
            i = call_start
            # B 修：元数预数（dict 形 ref_indices 需 arity 定位）
            if isinstance(ref_indices, dict):
                _d, _j, _na = 1, call_start, 1
                while _j < len(code) and _d > 0:
                    _c = code[_j]
                    if _c == '(':
                        _d += 1
                    elif _c == ')':
                        _d -= 1
                    elif _c == ',' and _d == 1:
                        _na += 1
                    _j += 1
                ref_positions = ref_indices.get(_na, set())
            else:
                ref_positions = ref_indices
            while i < len(code) and depth > 0:
                ch = code[i]
                if ch == '(':
                    depth += 1
                elif ch == ')':
                    depth -= 1
                    if depth == 0:
                        arg = code[arg_start:i]
                        if arg_idx in ref_positions:
                            arg = _fix_single_ref_arg(arg, vt, ref_type=_GB_REF_PARAM_TYPES.get((func_name, arg_idx)))
                        result.append(arg)
                        result.append(')')
                        break
                elif ch == ',' and depth == 1:
                    arg = code[arg_start:i]
                    if arg_idx in ref_positions:
                        arg = _fix_single_ref_arg(arg, vt, ref_type=_GB_REF_PARAM_TYPES.get((func_name, arg_idx)))
                    result.append(arg)
                    result.append(', ')
                    arg_idx += 1
                    arg_start = i + 1
                i += 1
            pos = i + 1
        code = ''.join(result)
    # [TOS 2026-10-28] _tail_000 兼容折叠（stage3:2248 原件随迁；对无 _tail_000 输入幂等）
    code = re.sub(r'(\w+)->_tail_000\b(?!\[)', r'*(void**)(\1)', code)
    return code
