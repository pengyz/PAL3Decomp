"""Stage 5: Compiler compatibility fixups (pure text-level, no AST).

Applies ~20 independent regex/text transformations that make IDA-generated
code compile under MSVC6. Each transformation is self-contained and idempotent.

Topics:
- Type aliases and suffixes
- Algebraic pointer decomposition
- Inline asm fixes (float constants, data labels, MASM hex)
- Static method call conversion
- Register-this alias elimination
- Reference parameter restoration
- Pointer cast fixups for MSVC6 compatibility
- C2440 cast insertion (pointer RHS into DWORD slots, ptr/ptr sign)
- IDA artifact cleanup (null checks, return statements)
- Struct overlap resolution
- Struct global array access fix
"""
import re
import struct as _struct

from data import store


# ============================================================
# Type alias substitution (text-level, STL/GB engine patterns)
# ============================================================

def _apply_text_substitutions(code, ctx):
    """Apply text-level substitutions: type aliases, suffixes, thunk classes."""

    # Normalize IDA __hidden this marker in body text: it now appears inside
    # function-pointer declarators rendered from adopted definite types,
    # e.g. `unsigned int (__thiscall *v21)(Cls *__hidden, int)`. `__hidden`
    # is never valid C++ — global strip is safe (display-convention token).
    code = re.sub(r'\b__hidden\b\s*', '', code)

    # Replace IDA container structures with STL types
    _type_map = {
        'std::_String_iterator<char,std::char_traits<char>,std::allocator<char>>':
            'std::string::iterator',
        'std::_String_const_iterator<char,std::char_traits<char>,std::allocator<char>>':
            'std::string::const_iterator',
        'std::_String_iterator<char,std::char_traits<char>,std::allocator<char>>':
            'std::string::iterator',
        'std::_String_const_iterator<char,std::char_traits<char>,std::allocator<char>>':
            'std::string::const_iterator',
    }
    for old, new in sorted(_type_map.items(), key=lambda x: -len(x[0])):
        code = code.replace(old, new)

    # Replace 'class ' prefix on types used in variable declarations
    code = re.sub(r'\bclass\s+(\w[\w<>,: ]*\w)(\s+(?:\*|&|\w+))', r'\1\2', code)
    code = re.sub(r'class\s+', '', code)
    code = re.sub(r'\bstruct\s+(\w[\w<>,: ]*\w)(\s+(?:\*|&))', r'\1\2', code)

    # thunk class qualifier injection for Stage3 mis-removed ctors
    if ctx.cls_name in store.thunk_classes and ctx.cls_name and not ctx.is_free_function:
        code = code.replace(ctx.method_name, '%s::%s' % (ctx.cls_name, ctx.method_name), 1)

    # Remove redundant 'struct' before template function pointer params
    code = re.sub(r'struct\s+([A-Za-z_]\w*(?:<[^>]*>)?)\s*\(', r'\1 (', code)

    return code


# ============================================================
# Algebraic decomposition: (char *)this + S*var + C → this->array[var].field
# ============================================================

def _build_array_stride_index():
    idx = {}
    for type_name, members in store.struct_members.items():
        for offset, (mname, mtype) in members.items():
            m = re.match(r'^([\w\s\*]+?)\[(\d+)\]$', mtype.strip())
            if m:
                elem_type = m.group(1).strip()
                arr_count = int(m.group(2))
                _ELEM_SIZES = {
                    'int': 4, 'float': 4, 'unsigned int': 4,
                    'unsigned long': 4, 'char': 1, 'unsigned char': 1,
                    'bool': 1, 'short': 2, 'unsigned short': 2,
                    'double': 8, 'long long': 8,
                }
                elem_sz = _ELEM_SIZES.get(elem_type, 4)
                stride = elem_sz
                for off2, (mn2, mt2) in sorted(members.items()):
                    if off2 > offset and off2 < offset + arr_count * elem_sz:
                        stride = off2 - offset
                        break
                idx.setdefault(type_name, []).append({
                    'name': mname, 'offset': offset, 'stride': stride,
                    'elem_count': arr_count, 'elem_type': elem_type,
                })
    return idx


_ARRAY_STRIDE_INDEX = None


def _get_arrays_for(typename):
    global _ARRAY_STRIDE_INDEX
    if _ARRAY_STRIDE_INDEX is None:
        _ARRAY_STRIDE_INDEX = _build_array_stride_index()
    return _ARRAY_STRIDE_INDEX.get(typename, [])


def _decompose_raw_pointer_arithmetic(code):
    """Convert (char *)this + S*var + C → this->array[var].field pattern."""
    lines = code.split('\n')
    out = []
    for line in lines:
        if 'this' not in line:
            out.append(line)
            continue
        m = re.match(
            r'^(\s*)\*\(\(_BYTE\s*\*\)this\s*\+\s*(\d+)\s*\*\s*(\w+)\s*\+\s*(\d+)\)\s*=\s*(.*);$',
            line
        )
        if m:
            indent, stride, var, base, val = m.group(1), m.group(2), m.group(3), m.group(4), m.group(5)
            stride_val = int(stride, 0)
            base_val = int(base, 0)
            out.append('%sthis->m_pData[%d * %s + %d] = %s;' % (indent, stride_val, var, base_val, val))
        else:
            out.append(line)
    return '\n'.join(out)


# ============================================================
# Inline asm fixes
# ============================================================

def _fix_asm_float_constants(code):
    """Replace IDA 'ds:1.2f' style float constants with static const variable syntax.
    
    Hex-Rays generates inline float literals like 'ds:1.5f' inside __asm blocks.
    MSVC doesn't support this inline syntax, so we need to extract them.
    """
    floats = set(re.findall(r'ds:(-?\d+\.\d+[eE]?[+-]?\d*)[fF]?', code))
    lines = code.split('\n')
    out = []
    for f in sorted(floats):
        _varname = '_flt_%s' % f.replace('.', '_').replace('-', 'neg').replace('+', 'pos')
        code = code.replace('ds:%sf' % f, _varname)
        code = code.replace('ds:%s' % f, _varname)
    return code


def _fix_asm_data_labels(code):
    """Replace IDA ds:XXXXX references with dword ptr [...] syntax."""
    code = re.sub(r'\bds:([a-zA-Z_]\w*)\b', r'dword ptr [\1]', code)
    code = re.sub(r'\bds:([0-9A-Fa-f]+[hH])\b', r'dword ptr [\1]', code)
    return code


def _fix_asm_hex_ambiguity(code):
    """Fix MASM hex constants like 0E0h → 0xE0 to prevent C parser confusion."""
    def _fix_hex(m):
        digits = m.group(1)
        if digits[0].isdigit() or len(digits) <= 1:
            return '0x' + digits
        return m.group(0)
    code = re.sub(r'\b([0-9A-Fa-f]+)h\b', _fix_hex, code)
    return code


# ============================================================
# Static method call: ((Type*)0)->Method() → Type::Method()
# ============================================================

def _fix_static_method_calls(code):
    """Convert ((ClassName *)0)->Method() to ClassName::Method() for static methods."""
    code = re.sub(
        r'\(\((\w+)\s*\*\)\s*0\)\s*->\s*(\w+)\s*\(',
        r'\1::\2(',
        code
    )
    return code


# ============================================================
# Register-this alias: _REG = this; _REG->x → this->x
# ============================================================

def _fix_register_this_alias(code):
    """Replace register-variable aliases for 'this' with direct this-> access.
    
    Hex-Rays generates: _REG = this; ... _REG->field. MSVC6 may not handle
    the register alias correctly when _REG is a register variable.
    """
    m = re.search(r'^\s*(\w+)\s*=\s*this\s*;\s*$', code, re.MULTILINE)
    if m:
        alias = m.group(1)
        code = re.sub(r'\b' + re.escape(alias) + r'\s*->', 'this->', code)
        code = re.sub(r'\s*' + re.escape(alias) + r'\s*=\s*this\s*;\s*', '\n', code)
    return code


# ============================================================
# Reference parameter restoration (gbengine &param fix)
# ============================================================

_GB_REF_PARAM_FUNCS = {
    'Translate': {0}, 'Rotate': {1}, 'Scale': {0},
    'LeftTranslate': {0}, 'RightTranslate': {0},
    'MakeMatrix': {0, 1, 2}, 'IntersectPlane': {0, 1},
    'IsColAABB': {0}, 'IsColOBB': {0}, 'IsColOBB_H': {0},
    'IsColPoint': {0}, 'IsColQuad': {0, 1, 2},
    'IsColSphere': {0}, 'IsColTriangle': {0, 1, 2, 3},
    'GetAABBox': {0}, 'GetSphere': {0}, 'GetCollideOBB': {0},
    'SetPosition': {0}, 'GetPosition': {0}, 'SetVelocity': {0},
    'SetOrientation': {0}, 'SetListenerPosition': {0},
    'SetListenerOrientation': {0, 1}, 'GetListenerPosition': {0},
    'PushMessage': {0}, 'PopMessage': {0},
    'GetViewport': {0}, 'GetViewSizeOnNearPlane': {0, 1},
    'GetViewPort': {0, 1, 2, 3},
    'PointWorldToScr': {1, 2},  # (gbVec3D*, float&, float&)
    'GetBlend': {0}, 'SetBlend': {0},
    # 'SetAxisAngle' REMOVED — see the F1b note below.
    'RightMultiply': {0},
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

# Local kinds that are positive evidence the identifier is NOT a `T` pointed at
# by the reference parameter (see the F1a gate in `_fix_single_ref_arg`).
_NON_POINTER_LOCAL_KINDS = frozenset(('value', 'array', 'fnptr'))


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
            while i < len(code) and depth > 0:
                ch = code[i]
                if ch == '(':
                    depth += 1
                elif ch == ')':
                    depth -= 1
                    if depth == 0:
                        arg = code[arg_start:i]
                        if arg_idx in ref_indices:
                            arg = _fix_single_ref_arg(arg, vt)
                        result.append(arg)
                        result.append(')')
                        break
                elif ch == ',' and depth == 1:
                    arg = code[arg_start:i]
                    if arg_idx in ref_indices:
                        arg = _fix_single_ref_arg(arg, vt)
                    result.append(arg)
                    result.append(', ')
                    arg_idx += 1
                    arg_start = i + 1
                i += 1
            pos = i + 1
        code = ''.join(result)
    return code


def _fix_single_ref_arg(arg, vt=None):
    """Fix a single argument for a reference parameter.

    Case 1: starts with '&'  → strip '&'
    Case 2: cast-to-pointer  → add '*' before the cast: (T*)x → *(T*)x
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
    # Case 3: plain identifier (simple variable name, NOT numeric constants)
    ident_m = re.match(r'^(\s*)(\w+)\s*$', arg)
    if ident_m and not ident_m.group(2).isdigit():
        vt = vt or {}
        kind = (vt.get(ident_m.group(2)) or {}).get('kind')
        if kind in _NON_POINTER_LOCAL_KINDS:
            # Positive evidence this is not a pointer: the `&` stage 3 removed
            # was the reference-taking one.  Leave the object expression.
            return arg
        return ident_m.group(1) + '*' + ident_m.group(2)
    # Unknown pattern — leave unchanged to be safe
    return arg


# ============================================================
# C2440 fixups: MSVC6 strictness — pointer RHS into DWORD slots,
# and pointer/pointer assignment mismatches.
# ============================================================

# Element/pointee bases whose slots receive raw address bits (DWORD slots).
_DWORD_SLOT_BASES = frozenset((
    'unsigned long', 'unsigned int', '_DWORD', 'DWORD', 'long', 'int',
))

# Calls returning pointers that are not in decomp signatures (Win32/CRT).
_PTR_RETURN_FUNCS = frozenset((
    'operator new', 'GetDlgItem', 'malloc', 'calloc', 'realloc',
    'LocalAlloc', 'GlobalAlloc', 'HeapAlloc',
    'LoadIcon', 'LoadCursor', 'LoadBitmap', 'LoadMenu',
))

# IDA auto-named globals whose bare reference yields a pointer (address):
# byte_/off_/stru_/flt_/dbl_/asc_ name arrays/functions/data whose value in
# expression position is the address itself. word_/dword_ are VALUES → not here.
_IDA_PTR_GLOBAL_RE = re.compile(r'^(?:byte|off|stru|flt|dbl|asc)_[0-9A-Fa-f]+$')

# LHS forms that denote a DWORD slot (each alternative is anchored to the
# '=' that follows it, so == / != / >= can never match):
#   LODWORD(x) / BYTE1(x) / HIWORD(x) ...  — IDA byte/word/dword slot macros
#   *((_DWORD *)X + N) =       — DWORD slot by index
#   *(_DWORD *)X =             — DWORD slot by address
_SLOT_LHS_RE = re.compile(
    r'\b(?:LO|HI)?(?:BYTE|WORD|DWORD)[0-9]?\s*\([^()]*\)\s*=(?!=)'
    r'|\*\s*\(\s*\(\s*(?:_DWORD|unsigned long|unsigned int)\s*\*\s*\)[^;=]*?\)\s*=(?!=)'
    r'|\*\s*\(\s*(?:_DWORD|unsigned long|unsigned int)\s*\*\s*\)[^;=]+?\s*=(?!=)'
)

# Cast-to-pointer prefix: (T *), (unsigned int **), (int (__cdecl *)...)
_CAST_PTR_RE = re.compile(
    r'^\(\s*[A-Za-z_][\w:]*(?:\s+(?:unsigned|signed|long|short|char|int|double|float))*\s*'
    r'(?:__cdecl|__stdcall|__thiscall)?\s*\*+\s*\)'
)

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
    """Map local/param names to declared types for pointer-ness decisions."""
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
    # value locals:  int v10;  unsigned long v3;
    for m in re.finditer(r'^\s+((?:(?:unsigned|signed|const|struct|class|enum)\s+)*[A-Za-z_]\w*)'
                         r'\s+(\w+)\s*;', code, re.M):
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


_MEMBER_TYPE_INDEX = None


def _member_type(cls, member):
    """Declared type of a struct member, or None."""
    global _MEMBER_TYPE_INDEX
    if _MEMBER_TYPE_INDEX is None:
        idx = {}
        for type_name, members in store.struct_members.items():
            for _off, (mname, mtype) in members.items():
                idx.setdefault(type_name, {})[mname] = mtype
        _MEMBER_TYPE_INDEX = idx
    return _MEMBER_TYPE_INDEX.get(cls, {}).get(member)


def _call_return_type(name):
    """Return-type text for 'Cls::Method' or 'Func', or None if unknown."""
    sig = store.method_sigs.get(name)
    if sig is None:
        sig = store.free_func_sigs.get(name)
    if not sig:
        return None
    m = re.match(r'^(.*?)\s*__(?:thiscall|cdecl|stdcall)\b', sig)
    if not m:
        return None
    return re.sub(r'^virtual\s+', '', m.group(1).strip()) or None


def _strip_outer_parens(e):
    e = e.strip()
    while e.startswith('('):
        depth = 0
        for i, ch in enumerate(e):
            if ch == '(':
                depth += 1
            elif ch == ')':
                depth -= 1
                if depth == 0:
                    if i == len(e) - 1:
                        e = e[1:i].strip()
                    else:
                        return e
                    break
        else:
            return e
    return e


_GLOBAL_BASE_TYPE_MAP = None


def _global_base_type(name):
    """Struct type of a named global instance (g_X), or None."""
    global _GLOBAL_BASE_TYPE_MAP
    if _GLOBAL_BASE_TYPE_MAP is None:
        m = {}
        for _base, _end, gname, gtype in store.struct_instances:
            m[gname] = gtype
        _GLOBAL_BASE_TYPE_MAP = m
    return _GLOBAL_BASE_TYPE_MAP.get(name)


def _path_is_pointer(path, vt, ctx):
    """Resolve a member access path like g_X.a.b / this->m_x / p->a.b.

    Returns True/False when decidable, None when any link is unknown.
    """
    parts = re.split(r'(?:->|\.)', path.strip())
    if len(parts) < 2:
        return None
    parts = [re.sub(r'\s*\[[^\]]*\]', '', p).strip() for p in parts]
    base = parts[0]
    if base == 'this':
        cls = ctx.cls_name
    else:
        cls = _global_base_type(base)
        if not cls:
            t = vt.get(base)
            if t and t.get('base'):
                cls = t['base']
    if not cls:
        return None
    for member in parts[1:]:
        if not member:
            return None
        mt = _member_type(cls, member)
        if mt is None:
            return None
        mt = str(mt).strip()
        if '*' in mt:
            return True
        cls = re.sub(r'\s*\[[^\]]*\]\s*$', '', mt)
    return False


def _expr_is_pointer(e, vt, ctx):
    """Positive-only pointer detection.

    Returns True only when pointer-ness is provable from expression text +
    declarations; unknown forms return False (no cast inserted — a cast on a
    float/int RHS would silently change semantics, e.g. float→ulong converts
    the value instead of copying bits).
    """
    e = _strip_outer_parens(e)
    if not e:
        return False
    c0 = e[0]
    if c0 == '"' or c0 == '&':
        return True
    if c0 == '*':
        m = re.match(r'\*\s*(\w+)', e)
        if m:
            t = vt.get(m.group(1))
            return bool(t) and t['kind'] in ('ptr', 'fnptr')
        return False
    if _CAST_PTR_RE.match(e):
        return True
    m = re.match(r'^(%s)\b' % '|'.join(sorted(_PTR_RETURN_FUNCS)), e)
    if m:
        return True
    # qualified member call anywhere in the expression
    m = re.search(r'([A-Za-z_]\w*)::([A-Za-z_]\w*)\s*\(', e)
    if m:
        ret = _call_return_type('%s::%s' % (m.group(1), m.group(2)))
        return bool(ret) and '*' in ret
    # unqualified call at expression start
    m = re.match(r'([A-Za-z_]\w*)\s*\(', e)
    if m and '::' not in e:
        n = m.group(1)
        if n in _PTR_RETURN_FUNCS:
            return True
        ret = _call_return_type(n)
        return bool(ret) and '*' in ret
    # multi-level member path, with optional trailing subscripts:
    #   g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * n + 1]
    # (mid-path subscripts allowed; resolved after part-splitting)
    m = re.match(r'([\w>.\-\[\]]+?)\s*(?:\[[^\]]*\])+\s*$', e)
    if m:
        pt = _path_is_pointer(m.group(1), vt, ctx)
        if pt is not None:
            return pt
    if re.search(r'(?:->|\.)', e):
        pt = _path_is_pointer(e, vt, ctx)
        if pt is not None:
            return pt
    # subscript: base[...] keeps the base's pointer-ness
    m = re.match(r'(\w+)\s*\[', e)
    if m:
        t = vt.get(m.group(1))
        return bool(t) and t['kind'] in ('ptr', 'fnptr')
    # plain identifier
    m = re.match(r'^(\w+)$', e)
    if m:
        if _IDA_PTR_GLOBAL_RE.match(m.group(1)):
            return True
        t = vt.get(m.group(1))
        return bool(t) and t['kind'] in ('ptr', 'fnptr')
    # top-level +/- : pointer arithmetic preserves pointer-ness
    depth = 0
    for i, ch in enumerate(e):
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        elif ch in '+-' and depth == 0 and i > 0 and e[i - 1] not in 'eE':
            return _expr_is_pointer(e[:i], vt, ctx)
    return False


def _needs_parens(e):
    """True when a cast placed at the START of `e` would bind only to the
    first operand instead of the whole expression (top-level binary op)."""
    depth = 0
    prev = None  # last non-whitespace char seen
    for i, ch in enumerate(e):
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        elif depth == 0 and ch in '+-*/%&|^':
            if ch == '-' and i + 1 < len(e) and e[i + 1] == '>':
                pass  # '->' arrow operator, not subtraction
            elif prev is not None and (prev.isalnum() or prev in '_)]'):
                return True  # binary operator (operand before it)
        if ch not in ' \t':
            prev = ch
    return False


def _scan_rhs_end(line, start):
    """End of the assignment RHS: first ; , ) at bracket-depth 0."""
    depth = 0
    i = start
    while i < len(line):
        ch = line[i]
        if ch in '([':
            depth += 1
        elif ch in ')]':
            if depth == 0:
                return i
            depth -= 1
        elif ch in ';,' and depth == 0:
            return i
        i += 1
    return i


def _fix_line_dword_slots(line, vt, ctx):
    if '=' not in line:
        return line
    cand = []
    for m in _SLOT_LHS_RE.finditer(line):
        # m.end() is right after the assignment '='
        p = m.end()
        while p < len(line) and line[p] in ' \t':
            p += 1
        cand.append(p)
    for m in re.finditer(r'\b(\w+)\s*\[[^\]]*\]\s*=(?!=)', line):
        t = vt.get(m.group(1))
        if t and t.get('kind') in ('ptr', 'array') and t.get('base') in _DWORD_SLOT_BASES:
            p = m.end()
            while p < len(line) and line[p] in ' \t':
                p += 1
            cand.append(p)
    if not cand:
        return line
    inserts = []
    for p in sorted(set(cand)):
        rhs_end = _scan_rhs_end(line, p)
        rhs = line[p:rhs_end]
        if rhs.strip().startswith('(unsigned long)'):
            continue
        if _expr_is_pointer(rhs, vt, ctx):
            inserts.append(p)
    if not inserts:
        return line
    out = line
    for p in reversed(inserts):
        rhs_end = _scan_rhs_end(out, p)
        rhs = out[p:rhs_end]
        cast = '(unsigned long)'
        if _needs_parens(rhs):
            cast += '(%s)' % rhs
            out = out[:p] + cast + out[rhs_end:]
        else:
            out = out[:p] + cast + out[p:]
    return out


# ============================================================
# NOTE: explicit-this static-call rewriting (`Cls::M(obj, rest)` →
# `((Cls *)obj)->Cls::M(rest)`) deliberately does NOT live here.
# Call-form policy is single-sourced in ast_transform.transform_oop_calls
# (the OOP stage), which already has the first-arg branches and the
# ret-N evidence gate. Stage 5 is text-level compatibility fixups only.
# ============================================================


def _fix_line_plain_var_assign(line, vt, ctx):
    """Statement `ident = RHS;` where the LHS is a declared local/param:

    - LHS pointer decl + provably-pointer RHS (different pointee): insert a
      cast to the LHS declared type — pointer→pointer, byte-neutral.
    - LHS DWORD-width value decl + provably-pointer RHS: insert (unsigned long)
      — the mirror of the slot rule (ptr → 32-bit int slot).
    """
    m = re.match(r'^(\s*)([A-Za-z_]\w*)\s*=(?!=)\s*', line)
    if not m:
        return line
    t = vt.get(m.group(2))
    if not t:
        return line
    rhs_start = m.end()
    rhs_end = _scan_rhs_end(line, rhs_start)
    rhs = line[rhs_start:rhs_end]
    if rhs.strip().startswith('('):
        return line
    if not _expr_is_pointer(rhs, vt, ctx):
        return line
    if _needs_parens(rhs):
        rhs_wrapped = '(%s)' % rhs
    else:
        rhs_wrapped = rhs
    if t.get('kind') == 'ptr' and t.get('base'):
        base = t['base']
        # only build casts from clean type texts (defense against name leaks)
        if not re.match(r'^[A-Za-z_][\w:]*(?:\s+(?:unsigned|signed|const|long|short|int|char'
                        r'|double|float|struct|class|enum|__int8|__int16|__int32|__int64))*$', base):
            return line
        cast = '(%s %s)' % (base, '*' * max(t.get('stars', 1), 1))
        return line[:rhs_start] + cast + rhs_wrapped + line[rhs_end:]
    if t.get('kind') == 'value' and t.get('base') in _DWORD_SLOT_BASES:
        return line[:rhs_start] + '(unsigned long)' + rhs_wrapped + line[rhs_end:]
    return line


def _fix_c2440_casts(code, ctx):
    """Insert explicit casts where Hex-Rays relies on implicit pointer
    conversions MSVC6 rejects (C2440).

    Family 1 — pointer-valued RHS written into DWORD slots (LODWORD(...),
    BYTE1(x), *((_DWORD*)X+N), *(_DWORD*)X, ulong* element): insert
    (unsigned long). Pointer→ulong is a bit-preserving no-op on x86, so the
    cast is byte-neutral. Only positively-identified pointer RHS get casts.
    Family 2 — statement assignments: &-rooted or otherwise provably-pointer
    RHS into a differently-typed pointer local → cast to LHS declared type;
    pointer RHS into a DWORD-width value local → (unsigned long).
    """
    vt = _build_var_types(code, ctx)
    out = []
    for line in code.split('\n'):
        line = _fix_line_dword_slots(line, vt, ctx)
        line = _fix_line_plain_var_assign(line, vt, ctx)
        out.append(line)
    return '\n'.join(out)

def _fix_ulong_uint_cast(code):
    """Add explicit casts for unsigned long* → unsigned int* conversions.
    
    x86 safe: both are 32-bit, but MSVC6 requires explicit cast. Fixes IDA
    function pointer type inference errors.
    """
    _fixes = {
        'unsigned long *': 'unsigned int *',
    }
    for old, new in _fixes.items():
        code = code.replace(old, new)
    return code


def _fix_operator_new_cast(code):
    """Add explicit casts for operator new return values.

    MSVC6 does not allow implicit void* → T* conversion.
    Pattern: var = operator new(size);
    Fix:     var = (T *)operator new(size);

    Looks up variable type from declarations in the same function body.
    Falls back to (char *) if type not found.
    """
    # Build a map of variable names → pointer types from declarations
    # Matches:  Type *var;  or  Type *var = ...;  or  Type *var, ...
    var_types = {}
    for m in re.finditer(r'^\s+([\w:]+(?:\s+\w+)*)\s+\*\s*(\w+)', code, re.MULTILINE):
        var_types[m.group(2)] = m.group(1).strip()

    def _replace_new(m):
        prefix = m.group(1)  # whitespace + "var = "
        var_match = re.search(r'(\w+)\s*=\s*$', prefix)
        if var_match:
            var_name = var_match.group(1)
            typ = var_types.get(var_name)
            if typ:
                return '%s(%s *)operator new(' % (prefix, typ)
        # Fallback: cast to char * (always compatible with pointer types)
        return '%s(char *)operator new(' % prefix

    code = re.sub(r'^(\s+\w+\s*=\s*)operator new\(', _replace_new, code, flags=re.MULTILINE)
    return code


# ============================================================
# struct_instances overlap resolution: dword_XXXX.member → cast
# ============================================================

def _resolve_stru_overlap(code):
    """Replace stru_XXXX.member[N] with (cast to containing struct) access.

    Only rewrites stru_XXXX in *value position* (start of an expression).
    When stru_XXXX is itself a MEMBER name (e.g. an embedded struct member
    in SceneMgr named after its address: g_SceneMgr.stru_C059A0.m_retry),
    it is already legal C++ and must NOT be cast-rewritten — hence the
    negative lookbehind blocking '.', '->' and word chars before it.
    """
    for base, end, gname, gtype in store.struct_instances:
        _stru_name = 'stru_%X' % base
        _pattern = r'(?<![.>\w])' + _stru_name + r'\.([a-zA-Z_]\w*(?:\[\d+\])?)'
        _replacement = r'((%s *)&%s)->\1' % (gtype, gname)
        code = re.sub(_pattern, _replacement, code)
    return code


# ============================================================
# Main entry
# ============================================================

def _run_inner(code, ctx):
    """Stage 5: compiler compatibility fixups (text-level, no AST)."""
    # Strip __noreturn (VC6 doesn't support this IDA attribute)
    code = re.sub(r'\b__noreturn\s*(?=\()', '', code)

    # Strip 'virtual' from free function definitions (not valid for non-member functions)
    if ctx.is_free_function:
        code = re.sub(r'\bvirtual\s+', '', code)

    # Strip Hex-Rays j_ thunk class scope from member calls:
    #   obj->j_ClassName::Method() → obj->Method()
    # These are IDA decompiler artifacts — the binary has a direct call,
    # Hex-Rays incorrectly inserts the thunk class name as scope qualifier.
    # Only affects call sites (-> form), not function definitions.
    code = re.sub(r'->j_([A-Z]\w*)::', '->', code)

    # Strip j_ prefix from thunk-qualified casts:
    #   ((j_NPC *)nVal)->NPC::Method() → ((NPC *)nVal)->NPC::Method()
    # The explicit qualified call target is unchanged, so the cast type
    # spelling is cosmetic.
    code = re.sub(r'\(j_([A-Z]\w*)\s*\*', r'(\1 *', code)

    # Strip Hex-Rays mangled name decorations in qualified method calls:
    #   obj->Class::?method@namespace@@...() → obj->Class::method()
    #   obj->?method@namespace@@...()        → obj->method()
    # The ?...@...@...@... suffix is MSVC mangling that leaks through
    # when Hex-Rays can't resolve the call target.
    code = re.sub(r'::\?(\w+)@[A-Za-z0-9_@]+(?=\()', r'::\1', code)
    code = re.sub(r'->\?(\w+)@[A-Za-z0-9_@]+(?=\()', r'->\1', code)

    # Replace compiler-generated _scalar_dtor calls with equivalent expressions.
    # _scalar_dtor(this, 1) = delete + destructor = delete this
    # _scalar_dtor(this, 0) = destructor only = ~ClassName(this) -- handled by dtor body
    # _scalar_dtor may have address suffix (_scalar_dtor_XXXX)
    code = re.sub(r'(\w+)\s*->\s*_scalar_dtor\w*\s*\(\s*(\w+)\s*,\s*1\s*\)', r'delete \1', code)
    # also handle single-param form: _scalar_dtor(char deleting)
    code = re.sub(r'(\w+)\s*->\s*_scalar_dtor\w*\s*\(\s*1\s*\)', r'delete \1', code)
    code = re.sub(r'(\w+)\s*->\s*_scalar_dtor\w*\s*\(\s*0\s*\)', r'', code)

    # _sdtor_call_dtor is an alternate name for the scalar deleting destructor
    # generated by some Hex-Rays versions (same semantics as _scalar_dtor).
    # Also handles: _sdtor_N (address-suffixed), dot access (.), arrow (->).
    for _dtor_pat in (r'_sdtor_call_dtor', r'_sdtor_\w+'):
        code = re.sub(r'(\w+)\s*->\s*' + _dtor_pat + r'\s*\(\s*(\w+)\s*,\s*1\s*\)', r'delete \1', code)
        code = re.sub(r'(\w+)\s*\.\s*' + _dtor_pat + r'\s*\(\s*(\w+)\s*,\s*1\s*\)', r'delete \1', code)
        code = re.sub(r'(\w+)\s*->\s*' + _dtor_pat + r'\s*\(\s*1\s*\)', r'delete \1', code)
        code = re.sub(r'(\w+)\s*\.\s*' + _dtor_pat + r'\s*\(\s*1\s*\)', r'delete \1', code)
        code = re.sub(r'(\w+)\s*->\s*' + _dtor_pat + r'\s*\(\s*0\s*\)', r'', code)
        code = re.sub(r'(\w+)\s*\.\s*' + _dtor_pat + r'\s*\(\s*0\s*\)', r'', code)

    # UIScene::GetSys is a static method but Hex-Rays calls it without scope.
    code = re.sub(r'(?<!::)\bGetSys\s*\(', 'UIScene::GetSys(', code)

    # Text-level substitutions (type aliases, suffixes, thunk classes)
    code = _apply_text_substitutions(code, ctx)

    # VC6 doesn't know C99/C++11 integer literal suffixes LL/ULL/ll/ull.
    # The MSVC-specific equivalent is i64/ui64. Same 64-bit constant, same
    # generated code bytes. (Removing the suffix would change semantics:
    # constants wider than 32 bits would be truncated by VC6.)
    code = re.sub(r'\b([0-9][0-9a-fA-FxX]*)[uU][lL]{2}\b', r'\1ui64', code)
    code = re.sub(r'\b([0-9][0-9a-fA-FxX]*)[lL]{2}\b', r'\1i64', code)

    # Algebraic decomposition: (char *)this + S*var + C → this->array[var].field
    code = _decompose_raw_pointer_arithmetic(code)

    # ASM fixups
    code = _fix_asm_float_constants(code)
    code = _fix_asm_data_labels(code)
    code = _fix_asm_hex_ambiguity(code)

    # Static method call conversion
    code = _fix_static_method_calls(code)

    # Register-this alias elimination
    code = _fix_register_this_alias(code)

    # Reference parameter restoration
    code = _fix_ref_params(code, ctx)

    # ulong* → uint* cast fix
    code = _fix_ulong_uint_cast(code)

    # operator new return value cast (MSVC6 requires explicit void* → T*)
    code = _fix_operator_new_cast(code)

    # C2440 cast insertion: pointer RHS into DWORD slots + ptr/ptr sign
    code = _fix_c2440_casts(code, ctx)

    # Empty if-body before else
    code = re.sub(
        r'^(\s*)if\s*\((.*?)\)\s*\n\s*else\b',
        r'\1if (\2)\n\1{\n\1}\n\1else',
        code, flags=re.MULTILINE
    )

    # if-with-comment-body: stage3 comments out vtable accesses inside if
    # bodies, leaving bare comments without braces. MSVC6 C2143.
    code = re.sub(
        r'^(\s*)if\s*\((.*?)\)\s*\n(\s*//.*?)$',
        r'\1if (\2)\n\1{\n\3\n\1}',
        code, flags=re.MULTILINE
    )

    # Hex-Rays (int)this cast artifact: Method((int)this) → this->Method()
    # This is a self-call where Hex-Rays inserted an (int) cast on this.
    code = re.sub(r'\b(\w+)\(\(int\)this\)', r'this->\1()', code)

    # !this null check → (this == NULL)
    code = re.sub(r'\b!this\b', '(this == NULL)', code)
    code = re.sub(r'\bthis\s*==\s*0\b', '(this == NULL)', code)

    # return byte_1010101 → return (void*)byte_1010101
    code = re.sub(r'return\s+byte_1010101', r'return (void*)byte_1010101', code)

    # Struct overlap resolution
    code = _resolve_stru_overlap(code)

    # Typed pointer arithmetic: *(this + N) = (Type*)val
    code = re.sub(
        r'\*\(this\s*\+\s*(\d+)\)\s*=\s*\([^)]+\*\)\s*(\w+)',
        r'*((_DWORD *)this + \1) = (unsigned long)(\2)',
        code
    )

    # Struct global array access: g_StructName[N] → *(int *)((char *)&g_StructName + N*4)
    _array_globals = []
    for gname, gtype in store.global_types.items():
        if gname in store.globals_map:
            gname = store.globals_map[gname]
        if gname.startswith('g_') and gtype and '[' not in gtype:
            for base, end, _, _ in store.struct_instances:
                if base <= int(gname.split('_')[1], 16) < end if re.match(r'^g_\w+$', gname) and False else False:
                    _array_globals.append(gname)
                    break
    for _ag in _array_globals:
        code = re.sub(
            r'\b' + re.escape(_ag) + r'\[(\d+)\]',
            lambda m: '*(int *)((char *)&' + _ag + ' + ' + m.group(1) + ' * 4)',
            code
        )

    # --- H（2026-09-15）：dtor 形参被剥后残留的自由变量（必须放在本函数**最末**） ---
    #
    # 问题：`pipeline/gen/stages/stage1_structural.py:177-190` 对析构函数
    # 「Dtor: strip all params」**无差别剥掉全部形参**。其本意是剥掉隐式的 `Cls *this`，
    # 但当签名里除 `this` 外**还有真实语义形参**时（实测全树 9 个 dtor），
    # 该形参名会变成自由变量。例：
    #   decomp signature = `virtual void *__thiscall(AStarPathFinder *this, char a2)`
    #   decompiled_c     = `void *__thiscall AStarPathFinder::~AStarPathFinder(AStarPathFinder *this, char a2)`
    #                      `{ AStarPathFinder::ReleaseAll(this); if ((a2 & 1) != 0) operator delete(this); ... }`
    #   生成后 : .h `~AStarPathFinder();` / .cpp `AStarPathFinder::~AStarPathFinder()`
    #           但函数体仍写 `if ( (a2 & 1) != 0 )`
    #
    # 后果**不是恒定的**：`a2`/`nVal` 这类名字在 VC6 自动名体系里（`globals.h` 的
    # `char a2[]` 等）**常常恰好存在同名全局** → 于是**侥幸编译通过**；一旦 IDA 的自动名
    # 换代（干净重建后 `0x590638` 从 `int a2` 变成 `char a2[]`），同一行就报
    # `C2296 '&' : illegal, left operand has type 'char []'`。
    # ⇒ 这是"**看 globals.h 里恰好有没有那个名字**"的**假通过**路径，而非稳定的正确产物。
    # 该缺陷**长期存在**：2026-09-01 基线里同一行就是 `C2065 'a2' : undeclared identifier`。
    #
    # 修法：**每个函数体的调用形态已经蕴含了调用时传入的 flag 值**。签名里该形参名已被
    # stage1 删除，故把函数体内对它的引用**替换为那个常量**即恢复原语义 ——
    # 这不是猜测，是「调用点已给出该值」的直接推论。
    #
    # 单参形态（实测全树 9 个 dtor 中 6 个是单参）确定的语义只有一种：
    # VC6 标量删除析构的 deleting flag，且该析构体**自身**负责 `operator delete`，
    # 故它是在 `delete p` 路径上被调用的，flag 恒为 **1**。
    #   `CEffgbParticle::~CEffgbParticle(int,int,int,int *,int,int)` 等多参形态
    #   **无法从单点确定**，本处**不动**（留给 Phase 2 / 或改为保留形参的根治方案）。
    #
    # 【位置要求】必须放在本函数**末尾**：前面多处 `code = re.sub(...)` 会整体覆盖 `code`，
    # 放在中间会被覆盖掉（captain 第一版即因此静默失效）。
    _sig_h = getattr(ctx, 'sig', None) or ''
    # 真实 sig 形如 `virtual void *__thiscall(AStarPathFinder *this, char a2)` ——
    # **含显式 `this`**，故必须先剔除它，剩下的才是被 stage1 剥掉的语义形参。
    #
    # ⚠️⚠️ 必须有 `ctx.is_dtor` 守卫（2026-09-15 独立复核 M1 抓出，captain 补）：
    # 缺此守卫时，本块会命中**任何**「恰好 1 个 int/char 类形参」的**普通函数**，
    # 把该形参名在整段函数体里替换成常量 `1` ⇒ **语义损坏**，不只是语法错：
    #   decomp    : *(_DWORD *)(result + 362768) = a2;      // 存形参
    #   generated : int CEffCylinder::Update(int 1) { ... *(_DWORD *)(result + 362768) = 1; }
    # 实测半径：谓词命中 decomp 51 个函数，其中**真 dtor 只有 1 个**；
    # `pal3/src` 里 **30 处签名 / 17 个文件**被毁（含 `int 1`/`char 1` 这类非法形参名）。
    # 更危险的是**它让度量反向**：受害者文件本来全是 fail，被解析崩塌后
    # error_count 反而下降（18:24→18:40 的「−294 修正」里 −293 全是这个假降），
    # 而 `compile_regression.py` 只比 ok/fail ⇒ **无门禁可发现**。
    # 故本块**仅对析构函数**生效，且只限「单参标量 deleting flag」这一确定语义。
    _m_h = re.search(r'\(\s*([^)]*)\)', _sig_h)
    if _m_h and getattr(ctx, 'is_dtor', False):
        _params_h = [p.strip() for p in _m_h.group(1).split(',') if p.strip()]
        _params_h = [p for p in _params_h if not re.search(r'\bthis\b', p)]
        if len(_params_h) == 1:
            _pn_h = re.search(r'([A-Za-z_]\w*)\s*$', _params_h[0])
            _pt_h = _params_h[0][:_pn_h.start()].strip() if _pn_h else ''
            if _pn_h and re.fullmatch(r'a\d+', _pn_h.group(1)) and \
                    _pt_h in ('char', 'int', 'unsigned int', '__int8', '__int16', '__int32'):
                _flag_name = _pn_h.group(1)
                # 仅对 dtor：该形参名已从签名删除、函数体内无声明，**不可能是合法标识符**，
                # 故替换不可能覆盖真实的局部变量/参数。且该析构体自身负责 `operator delete`、
                # 只能由 `delete` 路径进入 ⇒ flag 恒为 1（否则 double-free）。
                code = re.sub(r'\b' + re.escape(_flag_name) + r'\b', '1', code)

    return code


def run(code, ctx):
    return _run_inner(code, ctx)
