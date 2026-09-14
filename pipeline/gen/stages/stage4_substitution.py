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

def _try_literal_address(name):
    """Address constant for a skip-annotated global, for use under unary &.

    `&stru_XXXX` must become the data address itself, never the dword loaded
    from it (_try_literal_replacement would emit `&0xVAL` — C2101)."""
    for prefix in ('dword_', 'byte_', 'word_', 'off_', 'flt_', 'unk_', 'stru_', 'asc_'):
        if name.startswith(prefix):
            try:
                va = int(name.split('_')[1], 16)
            except (IndexError, ValueError):
                return None
            break
    else:
        return None
    if any(sa == va for _sn, sa in store.skip_globals.items()):
        return '0x%X' % va
    return None


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

_MEMBER_NAMES = None


def _load_member_names():
    """Union of annotated member names across structs/*.json.

    Guards the type-named-subobject rewrite below: a field spelled exactly
    like a class name could still be a genuinely declared member, in which
    case `&x->Name` is legal C++ and must be left alone."""
    global _MEMBER_NAMES
    if _MEMBER_NAMES is None:
        import json as _json
        names = set()
        try:
            for p in (store.annotations_dir / 'structs').glob('*.json'):
                try:
                    d = _json.loads(p.read_text(encoding='utf-8'))
                except Exception:
                    continue
                for m in (d.get('known_members') or {}).values():
                    if isinstance(m, dict) and m.get('name'):
                        names.add(m['name'])
        except Exception:
            pass
        _MEMBER_NAMES = names
    return _MEMBER_NAMES


def _declarator_name(node):
    """Leftmost identifier of a declarator chain (pointer/array/function)."""
    if node is None:
        return None
    if node.type == 'identifier':
        return node.text.decode('utf-8')
    for ch in node.children:
        r = _declarator_name(ch)
        if r:
            return r
    return None


def _collect_reserved_names(tree, ctx):
    """Names declared in this function's scope: parameters + locals.

    Hex-Rays parameter conventions (nVal, pnVal, ...) occasionally collide
    with IDA data names; a declared name must shadow any same-named global,
    thunk, or literal inside its own function (C++ scoping)."""
    reserved = set()
    m = re.match(r'^[^(]*\(([^)]*)\)', getattr(ctx, 'sig', '') or '')
    if m:
        inner = m.group(1).strip()
        if inner and inner != 'void':
            for p in inner.split(','):
                pm = re.search(r'([A-Za-z_]\w*)\s*(?:\[[^\]]*\])*\s*$', p.strip())
                if pm:
                    reserved.add(pm.group(1))

    def _walk(node):
        if node.type == 'declaration':
            for ch in node.children:
                if ch.type == 'init_declarator':
                    n = _declarator_name(ch.child_by_field_name('declarator'))
                    if n:
                        reserved.add(n)
                elif ch.type in ('identifier', 'pointer_declarator',
                                 'array_declarator', 'function_declarator'):
                    n = _declarator_name(ch)
                    if n:
                        reserved.add(n)
        for ch in node.children:
            _walk(ch)

    _walk(tree.root_node)
    return reserved


_MEMBER_KIND = None
_DECLARED_NAMES = None


def _load_member_kind():
    """member name -> 'scalar' | 'agg' | 'mixed', from IDB data_members.

    'agg' = declared array or pointer; 'mixed' = same name declared both
    ways across structs (rewrite disabled for safety).
    Also collects _DECLARED_NAMES: every declared member name + global
    name — paths through such names are safe to embed verbatim."""
    global _MEMBER_KIND, _DECLARED_NAMES
    if _MEMBER_KIND is not None:
        return _MEMBER_KIND
    mk = {}
    declared = set(store.global_addrs.keys())
    for tname, offs in (store.struct_members or {}).items():
        for off, mi in offs.items():
            try:
                name, mtype = mi
            except Exception:
                continue
            mtype = mtype or ''
            declared.add(name)
            kind = 'agg' if ('[' in mtype or '*' in mtype) else 'scalar'
            prev = mk.get(name)
            if prev is None:
                mk[name] = kind
            elif prev != kind:
                mk[name] = 'mixed'
    _MEMBER_KIND = mk
    _DECLARED_NAMES = declared
    return mk


def _collect_token_edits(code_bytes, tree, ctx):
    """Walk AST once, collect identifier/type replacement edits."""
    edits = []
    thunk_map = _build_identifier_map()
    reserved = _collect_reserved_names(tree, ctx)

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
        if node.type == 'subscript_expression':
            # `path.m_member[idx]` where m_member is a declared SCALAR:
            # does not compile (C2109). Taking the member's address and
            # indexing that is isomorphic and address-identical:
            # `(&path.m_member)[idx]`. Array/pointer members keep normal
            # indexing; unknown/mixed names are left untouched (conservative).
            base = node.child_by_field_name('argument')
            if base is not None and base.type == 'field_expression':
                fnode = base.child_by_field_name('field')
                if fnode is not None:
                    fname = fnode.text.decode('utf-8')
                    mk = _load_member_kind()
                    if mk.get(fname) == 'scalar':
                        base_txt = base.text.decode('utf-8')
                        # skip bases containing IDA-artifact names UNLESS every
                        # one is a declared global/member name (safe to embed)
                        artifacts = re.findall(r'\b(?:dword|byte|word|off|flt|unk|stru|sub)_[0-9A-Fa-f]{4,}\b',
                                               base_txt)
                        if artifacts and any(a not in _DECLARED_NAMES for a in artifacts):
                            pass
                        else:
                            idx = node.child_by_field_name('index')
                            idx_txt = idx.text.decode('utf-8') if idx is not None else '0'
                            repl = '(&%s)[%s]' % (base_txt, idx_txt)
                            edits.append((node.start_byte, node.end_byte,
                                          repl.encode('utf-8')))
                            return

        if node.type == 'pointer_expression':
            # &E->T / &E.T where T is a class-type-named (IDA-unnamed)
            # subobject. MSVC6 parses `->TypeName` as a function-style cast
            # (C2273/C2274). Taking a subobject's address is isomorphic to a
            # pointer-to-T cast, so rewrite to that form.
            # Assumption: the casted base expression needs no identifier
            # substitution itself (it is `this`, a local, or a plain member
            # chain — never an IDA-artifact name).
            op = node.child_by_field_name('operator')
            arg = node.child_by_field_name('argument')
            if op is not None and op.text == b'&' and arg is not None:
                while arg.type == 'parenthesized_expression' and arg.child_count >= 2:
                    arg = arg.children[1]
                if arg.type == 'field_expression':
                    fnode = arg.child_by_field_name('field')
                    base = arg.child_by_field_name('argument')
                    if fnode is not None and base is not None:
                        fname = fnode.text.decode('utf-8')
                        if (fname in store.game_classes
                                and fname not in _load_member_names()):
                            aop = arg.child_by_field_name('operator')
                            aop_text = aop.text.decode('utf-8') if aop is not None else '->'
                            base_txt = base.text.decode('utf-8')
                            if ctx.is_free_function and base_txt == 'this':
                                base_txt = '_this'
                            if aop_text == '->':
                                repl = '((%s *)%s)' % (fname, base_txt)
                            else:
                                repl = '((%s *)&%s)' % (fname, base_txt)
                            edits.append((node.start_byte, node.end_byte,
                                          repl.encode('utf-8')))
                            return

        if node.type == 'identifier' and node.child_count == 0:
            name = node.text.decode('utf-8')
            # Scoped name shadows any same-named global/thunk/literal — unless
            # the use is `::name` (qualified_identifier), which is an explicit
            # global-scope reference despite the collision.
            parent = node.parent
            if (name in reserved
                    and not (parent is not None and parent.type == 'qualified_identifier')):
                return
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
                # skip when this identifier is the METHOD of a qualified call
                # (parent qualified_identifier): replacing it would stack the
                # qualifier (NPC::UpdateAnim -> NPC::NPC::UpdateAnim)
                parent = node.parent
                if not (parent is not None and parent.type == 'qualified_identifier'):
                    replacement = thunk_map[name]
            if not replacement and name.startswith('a') and len(name) > 1 and name[1].isupper():
                replacement = _try_literal_replacement(name)
            if not replacement and name == 'this' and ctx.is_free_function:
                replacement = '_this'
            if replacement:
                # Member path whose FINAL member is a declared scalar, used
                # with a subscript: `path.tail[idx]` cannot compile (C2109 —
                # scalar has no operator[]). Taking the member's address and
                # indexing that is isomorphic and address-identical:
                # `(&path.tail)[idx]`.
                p = node.parent
                if (p is not None and p.type == 'subscript_expression'
                        and '.' in replacement):
                    arg = p.child_by_field_name('argument')
                    # tree-sitter wrappers are fresh objects per access:
                    # compare by span, not identity
                    if arg is not None and arg.start_byte == node.start_byte:
                        tail = replacement.split('.')[-1]
                        mk_all = _load_member_kind()
                        if mk_all.get(tail) == 'scalar':
                            indices = p.child_by_field_name('indices')
                            idx_txt = indices.text.decode('utf-8') if indices is not None else '[0]'
                            repl = '(&%s)%s' % (replacement, idx_txt)
                            edits.append((p.start_byte, p.end_byte,
                                          repl.encode('utf-8')))
                            return
                # Under unary &, a skip-global replacement must be the data
                # address itself, not the dword loaded from it (&0xVAL = C2101).
                # Replace the whole `&name` node so the & disappears with it.
                p = node.parent
                if (p is not None and p.type == 'pointer_expression'
                        and replacement.startswith('0x')):
                    pop = p.child_by_field_name('operator')
                    if pop is not None and pop.text == b'&':
                        addr = _try_literal_address(name)
                        if addr:
                            edits.append((p.start_byte, p.end_byte,
                                          addr.encode('utf-8')))
                            return
                edits.append((node.start_byte, node.end_byte, replacement.encode('utf-8')))
                return

        elif node.type == 'field_identifier' and node.child_count == 0:
            # field_identifier nodes (after -> or .) — only thunk_map applies.
            # Skip when the field_identifier is the METHOD of a qualified call
            # (its parent is a qualified_identifier): replacing the method
            # name inside an already-qualified call stacks the qualification
            # (NPC::UpdateAnim -> NPC::NPC::UpdateAnim, C2653/C2039).
            parent = node.parent
            if parent is not None and parent.type == 'qualified_identifier':
                return
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
