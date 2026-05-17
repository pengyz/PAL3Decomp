"""Stage 4: Pure text substitution (no context dependencies).

All operations here are independent string replacements that don't
produce patterns for other transforms to match. Order within this
stage does not matter for correctness.
"""
import re
from data import store


# --- Name resolution helpers ---

def _replace_thunks(code):
    for thunk_name, target_name in store.thunks.items():
        if thunk_name in code:
            code = code.replace(thunk_name, target_name)
    return code


def _replace_literals(code):
    if not store.literals:
        return code

    def _repl_flt(m):
        return store.literals.get(m.group(0), m.group(0))

    def _repl_dword(m):
        name = m.group(0)
        if name in store.literals:
            return store.literals[name]
        try:
            va = int(name.split('_')[1], 16)
        except (IndexError, ValueError):
            return name
        if 0x56A000 <= va <= 0x5D6000 and va % 4 == 0:
            s = store.try_read_rdata_string(va)
            if s is not None and len(s) >= 2:
                escaped = s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n').replace('\t', '\\t')
                replacement = '"%s"' % escaped
                store.literals[name] = replacement
                return replacement
        return name

    def _repl_astring(m):
        return store.literals.get(m.group(0), m.group(0))

    def _repl_asc(m):
        name = m.group(0)
        if name in store.literals:
            return store.literals[name]
        try:
            va = int(name.split('_')[1], 16)
        except (IndexError, ValueError):
            return name
        if 0x56A000 <= va <= 0x5D6000:
            s = store.try_read_rdata_string(va)
            if s is not None:
                escaped = s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n').replace('\t', '\\t')
                replacement = '"%s"' % escaped
                store.literals[name] = replacement
                return replacement
        return name

    code = re.sub(r'\bflt_[0-9A-Fa-f]+\b', _repl_flt, code)
    code = re.sub(r'\bdword_[0-9A-Fa-f]+\b', _repl_dword, code)
    code = re.sub(r'\ba[A-Z]\w+\b', _repl_astring, code)
    code = re.sub(r'\basc_[0-9A-Fa-f]+\b', _repl_asc, code)
    return code


def _replace_struct_member_refs(code):
    if not store.struct_instances:
        return code
    _pat = re.compile(r'\b((?:dword|byte|word|off|flt|unk)_[0-9A-Fa-f]+)\b')

    def _is_width_ok(prefix, member_type):
        mt = member_type.strip().lower()
        if prefix == 'dword': return True
        if prefix == 'byte': return any(t in mt for t in ('char', 'byte', 'bool'))
        if prefix == 'word': return any(t in mt for t in ('short', 'word', 'wchar'))
        if prefix == 'off': return '*' in member_type
        if prefix == 'flt': return 'float' in mt
        return True

    def _repl(m):
        name = m.group(0)
        if name in store.literals:
            return name
        try:
            parts = name.split('_', 1)
            prefix, addr = parts[0], int(parts[1], 16)
        except (IndexError, ValueError):
            return name
        for base, end, gname, gtype in store.struct_instances:
            if base <= addr < end:
                offset = addr - base
                members = store.struct_members.get(gtype, {})
                member_info = members.get(offset)
                if member_info:
                    mname, mtype = member_info
                    if _is_width_ok(prefix, mtype):
                        return '%s.%s' % (gname, mname)
                return name
        return name
    return _pat.sub(_repl, code)


def _replace_global_names(code):
    if not store.globals_map:
        return code
    _pat = re.compile(r'\b((?:dword|byte|word|stru|off|unk|flt)_[0-9A-Fa-f]+)\b')

    def _repl(m):
        name = m.group(0)
        pfx, hexpart = name.split('_', 1)
        key = '%s_%s' % (pfx, hexpart.upper())
        return store.globals_map.get(key, name)
    return _pat.sub(_repl, code)


# --- Reference parameter fix ---

_REF_METHODS = {
    'Rotate': {1, 2}, 'Translate': {1}, 'Scale': {1},
    'RightMultiply': {1}, 'LeftMultiply': {1},
    'RightTranslate': {1}, 'LeftTranslate': {1},
    'MakeMatrix': {1, 2, 3}, 'IntersectPlane': {1, 2},
    'IsColTriangle': {1, 2, 3, 4}, 'IsColOBB': {1}, 'IsColOBB_H': {1},
    'IsColAABB': {1}, 'PointWorldToScr': {2, 3}, 'PointScrToWorld': {2, 3},
}


def _fix_ref_params(code):
    for method_name, ref_pos in _REF_METHODS.items():
        if method_name not in code:
            continue
        if ref_pos == {1}:
            code = re.sub(r'(->' + re.escape(method_name) + r'\s*\()&(\w)', r'\1\2', code)
            code = re.sub(r'(::' + re.escape(method_name) + r'\s*\([^,]+,\s*)&(\w)', r'\1\2', code)
        elif ref_pos == {1, 2}:
            code = re.sub(r'(->' + re.escape(method_name) + r'\s*\()&(\w)', r'\1\2', code)
            code = re.sub(r'(->' + re.escape(method_name) + r'\s*\([^,]+,\s*)&(\w)', r'\1\2', code)
        elif ref_pos == {2}:
            code = re.sub(r'(->' + re.escape(method_name) + r'\s*\([^,]+,\s*)&(\w)', r'\1\2', code)
        elif ref_pos == {2, 3}:
            code = re.sub(r'(->' + re.escape(method_name) + r'\s*\([^,]+,\s*)&(\w)', r'\1\2', code)
            code = re.sub(r'(->' + re.escape(method_name) + r'\s*\([^,]+,[^,]+,\s*)&(\w)', r'\1\2', code)
        elif ref_pos == {1, 2, 3}:
            code = re.sub(r'(->' + re.escape(method_name) + r'\s*\()&(\w)', r'\1\2', code)
            code = re.sub(r'(->' + re.escape(method_name) + r'\s*\([^,]+,\s*)&(\w)', r'\1\2', code)
            code = re.sub(r'(->' + re.escape(method_name) + r'\s*\([^,]+,[^,]+,\s*)&(\w)', r'\1\2', code)
        elif ref_pos == {1, 2, 3, 4}:
            for _ in range(4):
                code = re.sub(r'(->' + re.escape(method_name) + r'\([^)]*),\s*&(\w)', r'\1, \2', code)
                code = re.sub(r'(->' + re.escape(method_name) + r'\s*\()&(\w)', r'\1\2', code)
    return code


# --- Main stage entry ---

def run(code, ctx):
    """Apply pure text substitutions (order matches old gen_cpp.py exactly)."""
    # Name resolution (must be before type fixes since dword_ could be string)
    code = _replace_thunks(code)
    code = _replace_literals(code)
    code = _replace_struct_member_refs(code)
    code = _replace_global_names(code)

    # Type name substitutions
    code = re.sub(r'\bvtbl_[0-9A-Fa-f]+\b', 'void', code)
    code = code.replace('(_ThrowInfo *)', '(_s__ThrowInfo *)')
    code = re.sub(r'(\b0x[0-9A-Fa-f]+)uLL\b', r'\1ui64', code)
    code = re.sub(r'(\b0x[0-9A-Fa-f]+)LL\b', r'\1i64', code)
    code = re.sub(r'(\b\d+)LL\b', r'\1i64', code)
    code = code.replace('unsigned __int8', 'unsigned char')
    code = code.replace('signed __int8', 'signed char')
    code = code.replace('unsigned __int16', 'unsigned short')
    code = code.replace('signed __int16', 'short')
    code = re.sub(r'\b__int8\b', 'char', code)
    code = re.sub(r'\b__int16\b', 'short', code)

    # Reference parameter fix (depends on OOP having produced ->Method() form)
    code = _fix_ref_params(code)

    # Free function specific
    if ctx.is_free_function:
        code = re.sub(r'\bthis\b', '_this', code)
        code = code.replace('stdiobuf *', 'UIWnd *')
        code = code.replace('stdiobuf::', 'UIWnd::')
        code = code.replace('std::ios_base *', 'UIWnd *')

    return code
