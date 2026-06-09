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
}


def _fix_ref_params(code):
    """Strip '&' from arguments to functions that take reference params.
    
    Hex-Rays outputs: obj->Translate(&vec);
    Correct C++:      obj->Translate(vec);
    """
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
                            arg = arg.lstrip()
                            if arg.startswith('&') and not arg.startswith('&&'):
                                arg = arg[1:]
                        result.append(arg)
                        result.append(')')
                        break
                elif ch == ',' and depth == 1:
                    arg = code[arg_start:i]
                    if arg_idx in ref_indices:
                        arg = arg.lstrip()
                        if arg.startswith('&') and not arg.startswith('&&'):
                            arg = arg[1:]
                    result.append(arg)
                    result.append(', ')
                    arg_idx += 1
                    arg_start = i + 1
                i += 1
            pos = i + 1
        code = ''.join(result)
    return code


# ============================================================
# MSVC6 pointer/int cast fixups
# ============================================================

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


# ============================================================
# struct_instances overlap resolution: dword_XXXX.member → cast
# ============================================================

def _resolve_stru_overlap(code):
    """Replace stru_XXXX.member[N] with (cast to containing struct) access."""
    for base, end, gname, gtype in store.struct_instances:
        _stru_name = 'stru_%X' % base
        _pattern = r'\b' + _stru_name + r'\.([a-zA-Z_]\w*(?:\[\d+\])?)'
        _replacement = r'((%s *)&%s)->\1' % (gtype, gname)
        code = re.sub(_pattern, _replacement, code)
    return code


# ============================================================
# Main entry
# ============================================================

def run(code, ctx):
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

    # Strip Hex-Rays mangled name decorations in qualified method calls:
    #   obj->Class::?method@namespace@@...() → obj->Class::method()
    #   obj->?method@namespace@@...()        → obj->method()
    # The ?...@...@...@... suffix is MSVC mangling that leaks through
    # when Hex-Rays can't resolve the call target.
    code = re.sub(r'::\?(\w+)@[A-Za-z0-9_@]+(?=\()', r'::\1', code)
    code = re.sub(r'->\?(\w+)@[A-Za-z0-9_@]+(?=\()', r'->\1', code)

    # Text-level substitutions (type aliases, suffixes, thunk classes)
    code = _apply_text_substitutions(code, ctx)

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
    code = _fix_ref_params(code)

    # ulong* → uint* cast fix
    code = _fix_ulong_uint_cast(code)

    # Pointer → unsigned long assignment cast (MSVC6 incompatibility)

    # Empty if-body before else
    code = re.sub(
        r'^(\s*)if\s*\((.*?)\)\s*\n\s*else\b',
        r'\1if (\2)\n\1{\n\1}\n\1else',
        code, flags=re.MULTILINE
    )

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

    return code
