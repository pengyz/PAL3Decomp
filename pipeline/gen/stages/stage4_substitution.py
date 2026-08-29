"""Stage 4: AST-based identifier/type resolution (pure semantic, no text hacks).

Walks the AST and replaces standalone identifier/type nodes via:
- Struct member resolution (dword_XXXX → g_Struct.member)
- Global name mapping (Buffer → g_ScriptRoleBuf)
- Literal replacement (flt_XXXX → 1.0f)
- Thunk resolution (sub_XXXXX → TargetFunc)
- String literal lookup (aXxx → "string")
- Integer constant replacement (known game constants)
- vtbl_XXXXXX type → void

Does NOT do text-level substitutions — those belong in Stage5.
Every replacement is scoped to a single AST node (identifier, type_identifier,
field_identifier, number_literal). No blind text replace.
"""
import re
import struct as _struct

import tree_sitter_cpp as tscpp
import tree_sitter

from data import store

_lang = tree_sitter.Language(tscpp.language())
_parser = tree_sitter.Parser(_lang)


# ============================================================
# Replacement tables (built from DataStore)
# ============================================================

def _build_identifier_map():
    """Build a unified replacement map for identifiers."""
    m = {}
    m.update(store.thunks)
    for cls in store.game_classes:
        if cls.startswith('_') and cls[1:] not in store.game_classes:
            m[cls[1:]] = cls
    return m


# ============================================================
# Literal + global resolution helpers
# ============================================================

def _try_literal_replacement(name):
    """Check if an identifier should be replaced with a literal value.
    Uses annotation state: type=skip entries get replaced with .data/.rdata values."""
    if name in store.literals:
        return store.literals[name]
    
    # Only replace identifiers whose address can be determined from the name
    for prefix in ('dword_', 'byte_', 'word_', 'off_', 'flt_', 'unk_', 'stru_', 'asc_'):
        if name.startswith(prefix):
            try:
                va = int(name.split('_')[1], 16)
            except (IndexError, ValueError):
                continue
            break
    else:
        return None
    
    # Determine if this identifier is a skip global via address lookup.
    # Address is the stable key (names may differ due to IDA truncation:
    # code uses dword_DC373C, ida_structs has dword_C373C).
    _is_skip = False
    if va is not None:
        _is_skip = any(sa == va for sn, sa in store.skip_globals.items())
    if not _is_skip:
        return None
    
    # Try to read as dword from binary (handles .rdata and .data)
    if va % 4 == 0 and not name.startswith('asc_'):
        val = store.try_read_rdata_dword(va)
        if val is not None:
            replacement = '0x%X' % val
            store.literals[name] = replacement
            return replacement
    elif name.startswith('asc_'):
        try:
            va = int(name.split('_')[1], 16)
        except (IndexError, ValueError):
            return None
        # .rdata (56A000-57F178) + .data (580000-1897000) — string
        # constants live in both sections. try_read_rdata_string validates
        # file bounds, length, and GBK decodability; the _is_skip gate
        # above ensures only annotated-skip addresses reach here.
        if 0x56A000 <= va < 0x1897000:
            s = store.try_read_rdata_string(va)
            if s is not None:
                escaped = s.replace('\\', '\\\\').replace('"', '\\"')
                escaped = escaped.replace('\n', '\\n').replace('\t', '\\t')
                replacement = '"%s"' % escaped
                store.literals[name] = replacement
                return replacement
    elif name.startswith('byte_'):
        try:
            va = int(name.split('_')[1], 16)
        except (IndexError, ValueError):
            return None
        if va < 0x401000:
            replacement = '0x%08X' % va
            store.literals[name] = replacement
            return replacement
        # Known literal constant patterns used in sentinel operations
        if va in (0x01010101, 0x00FFFFFF, 0x01234567):
            replacement = '0x%08X' % va
            store.literals[name] = replacement
            return replacement
    return None


# ============================================================
# Offset-based struct member resolution
# ============================================================

_ELEM_SIZES = {'int': 4, 'float': 4, 'unsigned int': 4, 'unsigned long': 4,
               'char': 1, 'unsigned char': 1, 'bool': 1,
               'short': 2, 'unsigned short': 2, 'double': 8, 'long long': 8}


def _resolve_offset(type_name, offset, prefix):
    """Recursively resolve an offset within a type to '.member' or '.member[N]'."""
    members = store.struct_members.get(type_name, {})
    info = members.get(offset)
    if info:
        mname, mtype = info
        mt = mtype.strip().lower()
        if prefix == 'byte' and not any(t in mt for t in ('char', 'byte', 'bool')) and '*' not in mtype:
            pass
        elif prefix == 'word' and not any(t in mt for t in ('short', 'word', 'wchar')):
            pass
        elif prefix == 'off' and '*' not in mtype:
            pass
        elif prefix == 'flt' and 'float' not in mt:
            pass
        else:
            return '.%s' % mname
    for moff, (mname, mtype) in sorted(members.items(), reverse=True):
        if moff > offset:
            continue
        rel = offset - moff
        if rel == 0:
            continue
        arr_m = re.match(r'^([\w\s\*]+?)\[(\d+)\]$', mtype.strip())
        if arr_m:
            elem_type = arr_m.group(1).strip()
            arr_count = int(arr_m.group(2))
            elem_sz = _ELEM_SIZES.get(elem_type)
            if elem_sz is None:
                elem_sz = store.struct_sizes.get(elem_type, 0)
                if elem_sz == 0:
                    elem_sz = 4 if store.struct_members.get(elem_type) else 0
            if not elem_sz:
                sub_m = store.struct_members.get(elem_type)
                if sub_m:
                    elem_sz = 4
            if elem_sz and rel < arr_count * elem_sz:
                idx = rel // elem_sz
                sub_rel = rel - idx * elem_sz
                _is_primitive = elem_type in _ELEM_SIZES and not store.struct_members.get(elem_type)
                if sub_rel == 0:
                    if _is_primitive:
                        continue  # byte-level array, try structured array
                    return '.%s[%d]' % (mname, idx)
                if not _is_primitive:
                    sub_members = store.struct_members.get(elem_type)
                    if sub_members:
                        sub = _resolve_offset(elem_type, sub_rel, prefix)
                        if sub:
                            return '.%s[%d]%s' % (mname, idx, sub)
                if _is_primitive:
                    continue
                return '.%s[%d]' % (mname, idx)
        embedded = store.struct_members.get(mtype.strip().rstrip('*').strip())
        if embedded and '*' not in mtype:
            # Use struct's full size as threshold (not primitive default 0x1000)
            _embedded_offsets = list(embedded.keys())
            _max_off = max(_embedded_offsets) if _embedded_offsets else 0
            _struct_sz = max(rel + 1, _max_off + 4)
            if rel < _struct_sz:
                sub = _resolve_offset(mtype.strip(), rel, prefix)
                if sub:
                    return '.%s%s' % (mname, sub)
    return None


def _try_struct_member_resolution(name):
    """Resolve IDA unnamed references (dword_XXXX) to struct member expressions."""
    if name.startswith('sub_'):
        return None
    try:
        addr = int(name.split('_', 1)[1], 16)
    except (ValueError, IndexError):
        return None
    if addr < 0x00401000 or addr > 0x01800000:
        return None
    prefix = name.split('_')[0]
    for base, end, gname, gtype in store.struct_instances:
        if base <= addr < end:
            offset = addr - base
            # Check for a named global at the exact address within this range.
            # If it has its own struct_instance, it's independent — use its name directly.
            # Otherwise it's a phantom — resolve as parent.member access.
            has_own_instance = any(b == addr for b, e, _, _ in store.struct_instances)
            if has_own_instance:
                for _gn, _ga in store.global_addrs.items():
                    if _ga == addr:
                        return _gn
            resolved = _resolve_offset(gtype, offset, prefix)
            if resolved:
                return '%s%s' % (gname, resolved)
    return None


def _try_global_name(name):
    """Map IDA unnamed globals (dword_XXX) → annotated name via globals_map + direct lookup.
    Also resolves named globals within struct_instance ranges to g_Parent.field expressions."""
    if name in store.globals_map:
        return store.globals_map[name]
    # Handle IDA default names (dword_/byte_/etc.) via address lookup
    if name.startswith(('dword_', 'byte_', 'word_', 'off_', 'unk_', 'stru_', 'flt_')):
        try:
            addr = int(name.split('_', 1)[1], 16)
        except (ValueError, IndexError):
            return None
        for base, end, gname, gtype in store.struct_instances:
            if base <= addr < end:
                # Skip if the address has its own struct_instance (independent global)
                if any(b == addr for b, e, _, _ in store.struct_instances):
                    continue
                offset = addr - base
                resolved = _resolve_offset(gtype, offset, name.split('_')[0])
                if resolved:
                    result = '%s%s' % (gname, resolved)
                    store.globals_map[name] = result
                    return result
        return None
    # Handle named globals (e.g. Buffer): check struct_instance ranges
    if name in store.global_addrs:
        addr = store.global_addrs[name]
        # If the name has its own struct_instance (exact address match),
        # it's an independent global — don't resolve through parent
        for base, end, _, _ in store.struct_instances:
            if base == addr:
                return None
        # No exact match: try resolving through parent struct range
        for base, end, gname, gtype in store.struct_instances:
            if base < addr < end:
                offset = addr - base
                resolved = _resolve_offset(gtype, offset, '')
                if resolved:
                    return '%s%s' % (gname, resolved)
    return None


# ============================================================
# Integer constant replacement tables
# ============================================================

_INT_CONSTANTS = {
    50529027: 'MAGIC_SLOT_INIT',
    2949123: 'SUBGROUP_FLAG_MASK',
    983043: 'SUBGROUP_FLAG_ALT',
}

_ARRAY_INDEX_CONSTANTS = {
    ('_todo_694', 89):  'TCS_TEAM_SIZE',
    ('_todo_694', 90):  'TCS_CHAR_BASE',
    ('_todo_694', 95):  'TCS_FORM_BASE',
    ('_todo_UI5908_ext', 108): 'UI5_SKILL_NUM',
    ('_todo_UI5908_ext', 126): 'UI5_EXT_FORM',
}

_ARRAY_IDX_BY_VAL = {}
for (field, idx), cname in _ARRAY_INDEX_CONSTANTS.items():
    _ARRAY_IDX_BY_VAL.setdefault(idx, []).append((field, cname))


def _get_subscript_array_name(node):
    """Extract array field name from subscript expression."""
    if node is None:
        return None
    t = node.type
    if t == 'field_expression':
        field_node = node.child_by_field_name('field')
        if field_node:
            return field_node.text.decode('utf-8')
    elif t == 'identifier':
        return node.text.decode('utf-8')
    elif t in ('cast_expression', 'parenthesized_expression'):
        return _get_subscript_array_name(node.child_by_field_name('value')
                                          or node.child_by_field_name('argument'))
    return None


# ============================================================
# AST-based token replacement (single walk, batch edits)
# ============================================================

def _collect_token_edits(code_bytes, tree, ctx):
    """Walk AST once, collect identifier/type replacement edits."""
    edits = []
    thunk_map = _build_identifier_map()

    def _in_declaration(node):
        """Check if this node is within a variable declaration (not an expression)."""
        p = node.parent
        while p:
            if p.type in ('declaration', 'pointer_declarator', 'function_declarator',
                          'parameter_declaration', 'init_declarator'):
                return True
            p = p.parent
        return False

    def visit(node):
        if node.type == 'identifier' and node.child_count == 0:
            name = node.text.decode('utf-8')
            replacement = None
            if name.startswith(('dword_', 'byte_', 'word_', 'off_', 'flt_', 'unk_', 'stru_')):
                # Skip struct_instances resolution in declaration contexts
                # (dword_XXXX used as a variable name, not a field access)
                if not _in_declaration(node):
                    replacement = _try_struct_member_resolution(name)
            if not replacement:
                # In declaration context, only resolve dword_/byte_ patterns
                # (named locals like 'src' should not be resolved through globals)
                if not _in_declaration(node) or name.startswith(('dword_', 'byte_', 'word_', 'off_', 'unk_', 'stru_', 'flt_')):
                    replacement = _try_global_name(name)
            if not replacement:
                replacement = _try_literal_replacement(name)
            if not replacement and name in thunk_map:
                replacement = thunk_map[name]
            if not replacement and name.startswith('a') and len(name) > 1 and name[1].isupper():
                replacement = _try_literal_replacement(name)
            if not replacement and name == 'this' and ctx.is_free_function:
                replacement = '_this'
            if replacement:
                edits.append((node.start_byte, node.end_byte, replacement.encode('utf-8')))
                return

        elif node.type == 'field_identifier' and node.child_count == 0:
            # field_identifier nodes (after -> or .) — only thunk_map applies
            name = node.text.decode('utf-8')
            if name in thunk_map:
                edits.append((node.start_byte, node.end_byte, thunk_map[name].encode('utf-8')))
                return

        elif node.type == 'type_identifier' and node.child_count == 0:
            name = node.text.decode('utf-8')
            if name.startswith('vtbl_') and all(c in '0123456789ABCDEFabcdef' for c in name[5:]):
                edits.append((node.start_byte, node.end_byte, b'void'))
                return
            if name in thunk_map:
                edits.append((node.start_byte, node.end_byte, thunk_map[name].encode('utf-8')))
                return

        elif node.type == 'this' and ctx.is_free_function:
            edits.append((node.start_byte, node.end_byte, b'_this'))
            return

        elif node.type == 'number_literal' and node.child_count == 0:
            text = node.text.decode('utf-8')
            try:
                val = int(text, 0)
                replacement = None
                if val in _ARRAY_IDX_BY_VAL:
                    parent = node.parent
                    if parent and parent.type == 'subscript_argument_list':
                        sub_expr = parent.parent
                        if sub_expr and sub_expr.type == 'subscript_expression':
                            obj_node = sub_expr.child_by_field_name('argument')
                            arr_name = _get_subscript_array_name(obj_node)
                            key = (arr_name, val)
                            if key in _ARRAY_INDEX_CONSTANTS:
                                replacement = _ARRAY_INDEX_CONSTANTS[key]
                if not replacement and val in _INT_CONSTANTS:
                    replacement = _INT_CONSTANTS[val]
                if replacement:
                    edits.append((node.start_byte, node.end_byte, replacement.encode('utf-8')))
                    return
            except (ValueError, OverflowError):
                pass

        for child in node.children:
            visit(child)

    visit(tree.root_node)
    return edits


# ============================================================
# Main entry
# ============================================================

# ============================================================
# Member-pointer callback reconstruction (VC6 C2440/C4234)
# ============================================================
#
# Hex-Rays renders thiscall member callbacks as free-fn-ptr casts of
# 'Class::Method' values plus synthetic-this parameter types
# ('int (__thiscall *a2)(int this, int a2)').  VC6 cannot spell any of
# those (C2440 'cannot convert', C4234 '__thiscall' reserved).  The
# original source used member-pointer types; a single-inheritance member
# pointer is a 4-byte function address, so rewriting every site of the
# type chain to member-pointer form is byte-equivalent.

_CAST_MEMFN_RE = re.compile(
    r'\(\s*([A-Za-z_][\w:]*)\s*\(\s*\*\s*\)\s*\(([^()]*)\)\s*\)\s*'
    r'([A-Z]\w*(?:::[A-Z]\w*)*)::([A-Za-z_]\w*)')

_ASSIGN_MEMFN_RE = re.compile(
    r'(\w+)\s*=\s*\(([A-Za-z_][\w:]*)\s*\(([A-Z]\w*(?:::[A-Z]\w*)*)::\*\)'
    r'\s*\(([^()]*)\)\)\s*&')

_DECL_FNPTR_RE = re.compile(
    r'(?m)^(\s*[A-Za-z_][\w:]*)\s*\(\s*\*\s*(\w+)\s*\)\s*\(([^;()]*)\)\s*;')

_FPTR_PARAM_RE = re.compile(
    r'^(.*?)\(\s*__thiscall\s*\*\s*(\w*)\s*\)\s*\((.*)\)$', re.S)

_THIS_NAME_RE = re.compile(r'(?:^|\s)(?:\w+\s*\*+\s*)?(?:this|_this)$')


def rewrite_thiscall_fnptr_param(param, cls_name):
    """Rewrite one parameter spelled as a thiscall fn-ptr to member-ptr form.

    'int (__thiscall *a2)(int this, int a2)' — Hex-Rays' rendering of a
    member-pointer callback with a synthetic this argument — becomes
    'int (CLS::*a2)(int, int)'.  The callback class is the enclosing
    method's class (binary evidence: the values passed at call sites are
    methods of that same class).  VC6 cannot spell the __thiscall fn-ptr
    form at all (C4234).
    """
    m = _FPTR_PARAM_RE.match(param.strip())
    if not m:
        return param
    pre, name, inner = m.groups()
    depth = 0
    args, cur = [], ''
    for ch in inner:
        if ch in '(<':
            depth += 1
        elif ch in ')>':
            depth -= 1
        if ch == ',' and depth == 0:
            args.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip():
        args.append(cur.strip())
    if len(args) >= 2 and _THIS_NAME_RE.search(args[0]):
        args = args[1:]
    return '%s(%s::*%s)(%s)' % (
        pre, cls_name, name or 'pFn', ', '.join(args))


def _fix_member_fn_callbacks(code, ctx):
    out = code

    # pass 0 — thiscall fn-ptr parameters in the definition signature
    # (Hex-Rays synthetic-this form).  Class = the method's own class.
    if ctx is not None and getattr(ctx, 'cls_name', None):
        out = re.sub(
            r'[\w\s]*\(\s*__thiscall\s*\*\s*\w*\s*\)\s*\([^()]*\)',
            lambda m: rewrite_thiscall_fnptr_param(m.group(0), ctx.cls_name),
            out)

    # pass 1 — cast sites:
    #   (RET ( *)(ARGS))CLS::METH → (RET (CLS::*)(ARGS'))&CLS::METH
    # where ARGS' drops the leading synthetic this argument.  Static
    # members already decay legally and must keep the free-ptr form.
    def _cast_repl(m):
        ret, args, cls, meth = m.group(1), m.group(2), m.group(3), m.group(4)
        if ('%s::%s' % (cls, meth)) in store.static_methods:
            return m.group(0)
        argl = [a.strip() for a in args.split(',') if a.strip()]
        if not argl:
            return m.group(0)
        return '(%s (%s::*)(%s))&%s::%s' % (
            ret, cls, ', '.join(argl[1:]), cls, meth)

    out = _CAST_MEMFN_RE.sub(_cast_repl, out)

    # pass 1b — address-equality against a member function:
    #   (char *)a2 == (char *)CLS::METH → a2 == &CLS::METH
    # (after pass 0/1 'a2' is a member pointer; member-pointer equality is
    # legal C++ and compares the same 4 address bytes.  Only qualified
    # member names on the right are rewritten — plain char* comparisons
    # are left alone.)
    out = re.sub(
        r'\(\s*char\s*\*\s*\)\s*(\w+)\s*==\s*\(\s*char\s*\*\s*\)\s*'
        r'([A-Z]\w*(?:::[A-Z]\w*)*)::([A-Za-z_]\w*)',
        r'\1 == &\2::\3', out)

    # pass 2 — local declarations correlated with rewritten casts:
    #   RET (*v4)(int, int);  →  RET (CLS::*v4)(int);
    var_types = {}
    for m in _ASSIGN_MEMFN_RE.finditer(out):
        var_types[m.group(1)] = (m.group(2), m.group(3), m.group(4))

    def _decl_repl(m):
        ret, name, args = m.group(1), m.group(2), m.group(3)
        info = var_types.get(name)
        if info:
            return '%s (%s::*%s)(%s);' % (info[0], info[1], name, info[2])
        return m.group(0)

    out = _DECL_FNPTR_RE.sub(_decl_repl, out)
    return out


# ============================================================
# Pointer/integral assignment cast insertion (VC6 C2440)
# ============================================================
#
# VC6 C++ rejects implicit pointer<->integer assignments; the original
# source carried explicit casts that Hex-Rays' output drops.  Re-insert
# them where both sides' types are recoverable:
#   ulong_var = &global;            →  ulong_var = (unsigned long)&global;
#   *(DWORD *)x = ptr_field;        →  *(DWORD *)x = (DWORD)ptr_field;
#   char *a = unsigned char *b;     →  char *a = (char *)b;  (same-size bases)
# All insertions are byte-equivalent (the same mov; casts are free).
# Cross-class pointer mismatches are NOT cast — they signal annotation
# errors and need evidence-based review.

_INTEGRAL = {
    'int', 'unsigned int', 'long', 'unsigned long', 'short', 'unsigned short',
    'char', 'unsigned char', 'bool', '_DWORD', '_WORD', '_BYTE', '_QWORD',
    'UINT', 'DWORD', 'BOOL', 'BYTE', 'WORD', 'size_t', 'LPARAM', 'WPARAM',
    'ULONG', 'UINT32', 'uintptr_t', 'DWORD_PTR',
}
_SAME_SIZE_PTR_BASES = {
    'char', 'unsigned char', 'BYTE', '_BYTE',
    'int', 'unsigned int', 'UINT', 'DWORD', '_DWORD', 'long', 'unsigned long',
    'short', 'unsigned short', 'WORD', '_WORD',
    'void', 'float',
}

_mem_index_cache = None
_struct_inst_types_cache = None


def _struct_instance_types():
    """{global_instance_name: struct_type}"""
    global _struct_inst_types_cache
    if _struct_inst_types_cache is None:
        _struct_inst_types_cache = {
            item[2]: item[3] for item in store.struct_instances}
    return _struct_inst_types_cache


def _member_index():
    """{struct_name: {member_name: member_type}} built from the store."""
    global _mem_index_cache
    if _mem_index_cache is None:
        _mem_index_cache = {}
        for sname, offs in store.struct_members.items():
            idx = {}
            for _off, (mname, mtype) in offs.items():
                idx.setdefault(mname, mtype.strip())
            _mem_index_cache[sname] = idx
    return _mem_index_cache


def _classify_type_text(t):
    """type text → ('pointer'|'integral'|'struct'|None, text, struct_name)"""
    if not t:
        return (None, '', None)
    t = t.strip()
    core = t.rstrip('* ').strip()
    if t.endswith('*'):
        if core in _SAME_SIZE_PTR_BASES or core in _INTEGRAL:
            return ('pointer', t, None)
        return ('pointer', t, core)
    if core in _INTEGRAL:
        return ('integral', t, None)
    return (None, t, core)


def _declared_local_types(tree, code_bytes):
    """Top-level function-scope locals: {name: type_text}."""
    out = {}

    def type_text_of(decl):
        parts = []
        for ch in decl.children:
            if ch.type in ('primitive_type', 'type_identifier', 'sized_type_specifier'):
                parts.append(ch.text.decode('utf-8'))
            elif ch.type == 'pointer_declarator':
                parts.append('*')
        return ' '.join(parts)

    def walk(node):
        if node.type == 'declaration':
            ttext = type_text_of(node)
            if ttext:
                for d in node.children:
                    if d.type == 'pointer_declarator':
                        d = d.children[-1] if d.children else d
                    if d.type == 'identifier':
                        out[d.text.decode('utf-8')] = ttext
                    elif d.type == 'init_declarator':
                        for dd in d.children:
                            if dd.type == 'identifier':
                                out[dd.text.decode('utf-8')] = ttext
                                break
                    elif d.type == 'array_declarator':
                        for dd in d.children:
                            if dd.type == 'identifier':
                                out[dd.text.decode('utf-8')] = ttext
                                break
        for ch in node.children:
            walk(ch)

    walk(tree.root_node)
    return out


def _expr_type(node, locals_, ctx, depth=0):
    """Classify an expression: returns _classify_type_text tuple."""
    if depth > 8 or node is None:
        return (None, '', None)
    nt = node.type
    if nt == 'pointer_expression':
        # &x → pointer ; *x → pointee of operand
        op = node.child_by_field_name('operator')
        arg = node.child_by_field_name('argument') or node.children[-1]
        if op and op.text == b'&':
            base = _expr_type(arg, locals_, ctx, depth + 1)
            if base[0] in ('integral', 'struct'):
                return ('pointer', base[1], base[2])
            return ('pointer', '', None)
        base = _expr_type(arg, locals_, ctx, depth + 1)
        if base[0] == 'pointer':
            return _classify_type_text(base[1].rstrip('* ').strip() and
                                       base[1].rstrip().rstrip('*').strip() or 'int')
        return (None, '', None)
    if nt == 'cast_expression':
        # type text sits between the first ( ) pair
        src = node.text.decode('utf-8')
        close = src.find(')')
        ttext = src[1:close].strip()
        return _classify_type_text(ttext)
    if nt == 'identifier':
        name = node.text.decode('utf-8')
        if name in locals_:
            return _classify_type_text(locals_[name])
        gt = store.global_types.get(name)
        if gt:
            return _classify_type_text(gt)
        return (None, '', None)
    if nt == 'field_expression':
        field = node.child_by_field_name('field')
        arg = node.child_by_field_name('argument')
        if field is None:
            return (None, '', None)
        mname = field.text.decode('utf-8')
        base_txt = arg.text.decode('utf-8') if arg is not None else ''
        base_struct = None
        deref = False
        if arg is not None:
            if arg.type == 'this':
                base_struct = ctx.cls_name if ctx else None
                deref = True
            else:
                bt = _expr_type(arg, locals_, ctx, depth + 1)
                if bt[0] == 'pointer' and bt[2]:
                    base_struct, deref = bt[2], True
                elif bt[2]:
                    base_struct, deref = bt[2], False
        if base_struct is None:
            # 'g_Global.field' where the global is a struct instance
            base_struct = _struct_instance_types().get(base_txt)
            deref = True
        if base_struct:
            m = _member_index().get(base_struct, {}).get(mname)
            if m:
                return _classify_type_text(m)
        return (None, '', None)
    if nt == 'subscript_expression':
        base = _expr_type(node.child_by_field_name('argument') or node.children[0],
                          locals_, ctx, depth + 1)
        if base[0] == 'pointer':
            return _classify_type_text(base[1].rstrip().rstrip('*').strip() or 'int')
        return (None, '', None)
    if nt == 'binary_expression' or nt == 'parenthesized_expression':
        for ch in node.children:
            if ch.type in ('identifier', 'field_expression', 'subscript_expression'):
                r = _expr_type(ch, locals_, ctx, depth + 1)
                if r[0]:
                    return r
        return (None, '', None)
    return (None, '', None)


def _collect_ptr_cast_edits(code_bytes, tree, ctx):
    """Insert explicit casts on pointer<->integral assignments."""
    edits = []
    locals_ = _declared_local_types(tree, code_bytes)

    def visit(node):
        if node.type == 'assignment_expression':
            op = node.child_by_field_name('operator')
            left = node.child_by_field_name('left')
            right = node.child_by_field_name('right')
            if op is not None and op.text == b'=' and left is not None and right is not None:
                lt = _expr_type(left, locals_, ctx)
                rt = _expr_type(right, locals_, ctx)
                if lt[0] == 'integral' and rt[0] == 'pointer':
                    # pointer value stored into an integer lvalue
                    edits.append((right.start_byte, right.start_byte,
                                  ('(%s)' % lt[1]).encode('utf-8')))
                elif (lt[0] == 'pointer' and rt[0] == 'pointer'
                      and lt[1] and rt[1]):
                    lbase = lt[1].rstrip('* ').strip()
                    rbase = rt[1].rstrip('* ').strip()
                    if (lbase != rbase and lbase in _SAME_SIZE_PTR_BASES
                            and rbase in _SAME_SIZE_PTR_BASES):
                        edits.append((right.start_byte, right.start_byte,
                                      ('(%s)' % lt[1]).encode('utf-8')))
        for ch in node.children:
            visit(ch)

    visit(tree.root_node)
    return edits


def run(code, ctx):
    """Stage 4: pure AST-based identifier/type resolution."""
    code_bytes = code.encode('utf-8')
    tree = _parser.parse(code_bytes)
    edits = _collect_token_edits(code_bytes, tree, ctx)
    edits += _collect_ptr_cast_edits(code_bytes, tree, ctx)
    result = code_bytes
    for start, end, replacement in sorted(edits, reverse=True):
        result = result[:start] + replacement + result[end:]
    result = result.decode('utf-8')
    return _fix_member_fn_callbacks(result, ctx)
