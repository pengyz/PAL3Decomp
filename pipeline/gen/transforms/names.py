"""Name resolution transforms.

Order 300-399: Replace IDA-generated names with proper identifiers.
"""
import re
from transforms import register
from data import store


@register(order=300)
def replace_thunks(code, ctx):
    """Replace thunk calls and type casts with direct target equivalents."""
    for thunk_name, target_name in store.thunks.items():
        if thunk_name in code:
            code = code.replace(thunk_name, target_name)
    return code


@register(order=310)
def replace_literals(code, ctx):
    """Replace .rdata literal references (floats + strings) with inline values."""
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


def _is_access_width_compatible(ida_prefix, member_type):
    mt = member_type.strip().lower()
    if ida_prefix == 'dword':
        return True
    if ida_prefix == 'byte':
        return any(t in mt for t in ('char', 'byte', 'bool'))
    if ida_prefix == 'word':
        return any(t in mt for t in ('short', 'word', 'wchar'))
    if ida_prefix == 'off':
        return '*' in member_type
    if ida_prefix == 'flt':
        return 'float' in mt
    return True


@register(order=320)
def replace_struct_member_refs(code, ctx):
    """Replace IDA default names that are global struct instance members."""
    if not store.struct_instances:
        return code
    _pat = re.compile(r'\b((?:dword|byte|word|off|flt|unk)_[0-9A-Fa-f]+)\b')

    def _repl(m):
        name = m.group(0)
        if name in store.literals:
            return name
        try:
            parts = name.split('_', 1)
            prefix = parts[0]
            addr = int(parts[1], 16)
        except (IndexError, ValueError):
            return name
        for base, end, gname, gtype in store.struct_instances:
            if base <= addr < end:
                offset = addr - base
                members = store.struct_members.get(gtype, {})
                member_info = members.get(offset)
                if member_info:
                    member_name, member_type = member_info
                    if _is_access_width_compatible(prefix, member_type):
                        return '%s.%s' % (gname, member_name)
                return name
        return name
    return _pat.sub(_repl, code)


@register(order=330)
def replace_global_names(code, ctx):
    """Replace IDA default global names with annotated proper names."""
    if not store.globals_map:
        return code
    _pat = re.compile(r'\b((?:dword|byte|word|stru|off|unk|flt)_[0-9A-Fa-f]+)\b')

    def _repl(m):
        name = m.group(0)
        pfx, hexpart = name.split('_', 1)
        key = '%s_%s' % (pfx, hexpart.upper())
        return store.globals_map.get(key, name)
    return _pat.sub(_repl, code)
