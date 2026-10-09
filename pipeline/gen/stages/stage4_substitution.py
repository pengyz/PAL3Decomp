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


def _anon_aggregate(mtype):
    """inline union/struct 递归引用形——emit_headers._keep_anonymous 同族谓词
    （2026-09-28 bDestRole/_field_C67E 双层实证：匿名聚合内层名提升，不得合成外层名）。"""
    t = (mtype or '').strip()
    return t.startswith('_inline_') or '::$' in t


def _resolve_offset(type_name, offset, prefix):
    """Recursively resolve an offset within a type to '.member' or '.member[N]'。
    2026-09-28 修（悬空渲染根因）：导出 data_members 可带 **空串 name**（匿名 union 族）
    ⇒ `'.%s' % ''` 产出 `g_SceneMgr.` 悬空。合成实名（与 emit_headers 同公式
    `_field_%04X % off` ⇒ 头文件与渲染同名一致）；**匿名聚合体豁免合成**（内层名提升）。"""
    members = store.struct_members.get(type_name, {})
    info = members.get(offset)
    if info:
        mname, mtype = info
        if not mname and not _anon_aggregate(mtype):
            mname = '_field_%04X' % offset          # 标量空名合成
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
            return ('.%s' % mname) if mname else None    # 匿名聚合无路径分量（内层名另行提升）
    for moff, (mname, mtype) in sorted(members.items(), reverse=True):
        if not mname and not _anon_aggregate(mtype):
            mname = '_field_%04X' % moff       # 标量空名合成（匿名聚合豁免，同上）
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
                    return (('.%s[%d]' % (mname, idx)) if mname else None)   # 空名数组形态保守弃
                if not _is_primitive:
                    sub_members = store.struct_members.get(elem_type)
                    if sub_members:
                        sub = _resolve_offset(elem_type, sub_rel, prefix)
                        if sub:
                            return (('.%s[%d]%s' % (mname, idx, sub)) if mname else sub)
                if _is_primitive:
                    continue
                return (('.%s[%d]' % (mname, idx)) if mname else None)
        embedded = store.struct_members.get(mtype.strip().rstrip('*').strip())
        if embedded and '*' not in mtype:
            # Use struct's full size as threshold (not primitive default 0x1000)
            _embedded_offsets = list(embedded.keys())
            _max_off = max(_embedded_offsets) if _embedded_offsets else 0
            _struct_sz = max(rel + 1, _max_off + 4)
            if rel < _struct_sz:
                sub = _resolve_offset(mtype.strip(), rel, prefix)
                if sub:
                    return (('.%s%s' % (mname, sub)) if mname else sub)   # 匿名聚合：内层名提升直用
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
        # 2026-09-20 审计 P1-5（第一批）：直读收敛到单一读点
        # `pipeline/gen/annotation_view.py`。逻辑**逐字等价**（只取 known_members 下
        # 的 dict 且带 name 的条目；坏文件静默跳过）⇒ 产物必须字节不变。
        try:
            import annotation_view as _av
        except ImportError:
            from pipeline.gen import annotation_view as _av
        _MEMBER_NAMES = _av.member_names(store=store)
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


_globals_h_cache = None


def _globals_h_types():
    """`include/pal3/globals.h` 的 `extern <type> <name>;` → {name: type}。

    生成代码里有一部分全局**只**在这个手写头里声明（不在 export/annotations 的
    `store.global_types` 里），例如 `extern void * g_ArcSceneMonsterTable;`。
    类型判据必须能看见它们，否则 `*(&g_X + n)` 这类元素访问判不出类型，
    经函数指针 cast 的间接调用就永远补不上显式转换（第 133 轮实测：ArcSceneMonster.cpp
    一族 42 条 C2664 全卡在这里）。读的是本仓自己的声明，不含任何猜测。
    """
    global _globals_h_cache
    if _globals_h_cache is None:
        import os
        out = {}
        p = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                         '..', '..', '..', 'include', 'pal3', 'globals.h')
        try:
            with open(p, encoding='utf-8', errors='replace') as fh:
                for line in fh:
                    m = re.match(r'\s*extern\s+(.+?)\s+(\w+)\s*(\[[^\]]*\])?\s*;', line)
                    if m:
                        t = m.group(1).strip()
                        if m.group(3):          # 数组：元素类型即声明类型
                            out.setdefault(m.group(2), t)
                        else:
                            out.setdefault(m.group(2), t)
        except OSError:
            pass
        _globals_h_cache = out
    return _globals_h_cache


def _type_text_of(decl):
    """声明/形参的类型文本（把 `const struct gbVec3D *` 收成 `gbVec3D *`）。

    F78 修正：`struct_specifier`（`struct gbVec3D *p` 这种拼法）以前完全没收进来 ——
    只在**直接子节点**里找 `type_identifier` ⇒ `struct gbVec3D *ViewTarget;` 的类型文本
    退化成 `'*'`，结构体名丢失 ⇒ 依赖"指针指向哪个类"的判据（F78）永远不成立。
    这里改为只取 specifier 的 `name`（不递归进成员，避免把内联结构体的成员类型混进来），
    指针层级按嵌套 `pointer_declarator` 计数。
    """
    parts = []

    def walk(n):
        for ch in n.children:
            if ch.type in ('primitive_type', 'type_identifier', 'sized_type_specifier'):
                parts.append(ch.text.decode('utf-8'))
            elif ch.type in ('struct_specifier', 'enum_specifier', 'union_specifier'):
                nm = ch.child_by_field_name('name')
                if nm is not None:
                    parts.append(nm.text.decode('utf-8'))
                else:
                    walk(ch)
            elif ch.type == 'pointer_declarator':
                parts.append('*')

    walk(decl)
    return ' '.join(parts)


def _declared_local_types(tree, code_bytes):
    """Top-level function-scope locals: {name: type_text}."""
    out = {}

    def type_text_of(decl):
        return _type_text_of(decl)

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
            # `&v19`（v19 是结构体实例）：`_classify_type_text('gbVec3D')` 返回
            # `(None, 'gbVec3D', 'gbVec3D')` ⇒ base[0] 为 None，但**被指向的类名是已知的**。
            # 丢掉它会让"&obj 是指向某类的指针"这一事实消失（F78 的 `*(&v19)` 判据就靠它）。
            return ('pointer', '', base[2])
        base = _expr_type(arg, locals_, ctx, depth + 1)
        if base[0] == 'pointer':
            return _classify_type_text(base[1].rstrip('* ').strip() and
                                       base[1].rstrip().rstrip('*').strip() or 'int')
        # `*(&X + n)` / `*(&X)`：Hex-Rays 用"取址 + 解引用"表达数组/全局的元素访问，
        # 元素类型就是 **X 自身的类型**（不是 `&X` 的指针类型的 pointee 之外的猜测）。
        # 该形状在经函数指针 cast 的间接调用里正是 C2664 的主角（第 133 轮量化 175 条）：
        #   (*(void (**)(char *, _DWORD, int *, ArcSceneMonster *))(v22 + 16))(
        #       v8 + 215804, *(&g_ArcSceneMonsterTable + nVal), &v39, this);
        # 这里的第 2 实参 VC6 判为 `void *`（`q_ArcSceneMonsterTable` 是指针数组）而形参是
        # `_DWORD` ⇒ 需要显式转换。原 `_expr_type` 落到 binary_expression 分支后只会返回
        # 索引变量 `nVal` 的类型（integral），因此这族永远判不出来。
        _inner = arg
        # 剥括号
        while _inner is not None and _inner.type == 'parenthesized_expression':
            _inner = next((c for c in _inner.children if c.type != '(' and c.type != ')'),
                          None)
        if _inner is not None and _inner.type == 'binary_expression':
            # `&X + n`：只看**左操作数**（右操作数是下标，与元素类型无关）
            _inner = _inner.child_by_field_name('left')
            while _inner is not None and _inner.type == 'parenthesized_expression':
                _inner = next((c for c in _inner.children
                               if c.type != '(' and c.type != ')'), None)
        if _inner is not None and _inner.type == 'pointer_expression':
            _op2 = _inner.child_by_field_name('operator')
            if _op2 is not None and _op2.text == b'&':
                _tgt = _inner.child_by_field_name('argument') or _inner.children[-1]
                r = _expr_type(_tgt, locals_, ctx, depth + 1)
                if r[0]:
                    return r
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
        gh = _globals_h_types().get(name)
        if gh:
            return _classify_type_text(gh)
        return (None, '', None)
    if nt == 'this':
        # 成员函数的 this 永远是指针（类型未知也不影响"是指针"这一事实）
        return ('pointer', (ctx.cls_name + ' *') if (ctx and ctx.cls_name) else 'void *',
                ctx.cls_name if ctx else None)
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


# ============================================================
# tagRECT* 伪装改写（任务 1：UIPushButton ③ 的 4 条 C2440 之 A 族）
# ============================================================
#
# 病灶层三问（2026-10-09 只读实测，答案随 commit 存档）：
#   ① 病灶在哪一层：**codegen**（Hex-Rays 把 m_texarray/m_texarrayInfo 的双槽指针
#      遍历渲成 `tagRECT*` 形 `p_m_rect->left/right`；标注层的
#      `gbTexture * m_texarray[2]; // +0x54` 本身是对的，不改标注）。
#   ② 消费者实际读哪份声明：`pal3/src/Misc/UIPushButton.h:23`
#      `gbTexture * m_texarray[2]; // +0x54`（+0x5C 是 `_PlugInfo * m_texarrayInfo[2]`）。
#   ③ 报错还缺什么：C2440 只说 `from 'class gbTexture *' to 'long'`，不说是哪个
#      cast 引入的 `long` ⇒ 用二进制步长裁决（`add esi,0x4` ⇒ 步长 4，非 tagRECT 的 16）。
#
# 判据**三条合取**（计划写死；任一不成立即不改——宁可漏，不可错）：
#   ① 左值 `base->field`，field ∈ tagRECT 四字段，base 静态类型为 `tagRECT *`
#   ② 右值是**类指针**（`gbTexture *` 这类指向类的指针；整数 / char* / void* 不算）
#   ③ 同一局部变量二进制步长 4 —— 只认下面 objdump 实证白名单，且同名变量在本函数
#      有 `v = (T *)((char *)v + 4)` 步进形（Hex-Rays 对 `add reg,4` 的固定渲染）
#
# 改写形（**等价变换**：地址与写入值逐位不变，转换不产码）：
#   `p->left = X;`  ⇒  `*(DWORD *)((char *)p + 0*4) = (DWORD)X;`
#   字段序号 n：left=0 / top=1 / right=2 / bottom=3 ⇒ `+ n*4` = tagRECT 字段字节偏移，
#   与二进制的 `mov [esi],eax` / `mov [esi+0x8],eax` 槽位一一对应。
#   右值 `(DWORD)` 显式转换必须一起补（否则 C2440 只是换成 unsigned long 说法），
#   与原码里的 `(LONG)ParentData` 显式转换同语义。
#
# 实测（2026-10-09 全链当场读数，前后同法 `cli.py codegen all --skip-probe` + `probe`）：
# UIPushButton.cpp C2440 −2（codegen all 产物行 173/180 消失；行 523/528 属 stage3 虚表
# 改名丢补偿转换的 B 族，判据①不全 ⇒ 原样保留）/ 总错误 1721→1719 / 全语料仅此 1 单元
# 错误数变化（4→2）· 其余 58 错误码多重集逐项全同 / S2 102→102（单元仍红）/ L1 86→86。
# 判据不全站点的逐条核证记录见
# `.superpowers/sdd/2026-10-09-restore-10-green-units/task-1-report.md`。

_TAGRECT_FIELDS = {'left': 0, 'top': 1, 'right': 2, 'bottom': 3}

# 判据③唯一裁决来源：**objdump 实证白名单**。新增站点必须先经
# `tools/audit_callsite_evidence.py`（任务 0）+ 全量反汇编缓存核证再入表。
_PTR_DISGUISE_STRIDE4 = {
    # (类, 方法, 变量) -> {va, stride, evidence}
    ('UIPushButton', 'CreateWithTextures', 'p_m_rect'): {
        'va': '0x00440810',
        'stride': 4,
        # 全量反汇编核证（data/status/_disasm_cache.txt 与 objdump 原文逐字一致）：
        'evidence': (
            '0x44086a 8d 75 54    lea esi,[ebp+0x54]          ; m_texarray（gbTexture*[2] @+0x54）',
            '0x4408bd 89 06       mov DWORD PTR [esi],eax     ; 每轮第 1 写：m_texarray[i]（NewTexture 返回值）',
            '0x4408ce 89 46 08    mov DWORD PTR [esi+0x8],eax ; 每轮第 2 写：m_texarrayInfo[i]（@+0x5C）',
            '0x4408f4 83 c6 04    add esi,0x4                 ; 步长 4',
        ),
    },
}

_method_ret_cache = None


def _method_return_index():
    """方法短名 → 返回类型文本；**所有**声明者不一致则不收录（宁可漏）。

    注解读取经 `annotation_view` 单一读点（2026-09-20 规则：新增注解直读必须走它）。
    """
    global _method_ret_cache
    if _method_ret_cache is None:
        from annotation_view import iter_structs, structs_dir
        acc = {}
        for _p, d in iter_structs(structs_dir()):
            for mv in (d.get('methods') or {}).values():
                if not isinstance(mv, dict):
                    continue
                name = str(mv.get('name') or '').split('(')[0]
                sig = str(mv.get('signature') or '')
                if not name or '(' not in sig:
                    continue
                head = sig[:sig.find('(')]
                head = re.sub(
                    r'\b(?:virtual|__thiscall|__cdecl|__stdcall|__fastcall|__hidden)\b',
                    ' ', head)
                ret = head.strip()
                if ret:
                    acc.setdefault(name, set()).add(ret)
        _method_ret_cache = {k: sorted(v)[0] for k, v in acc.items() if len(v) == 1}
    return _method_ret_cache


def _is_class_pointer_type(t):
    """类指针判据（判据②）：`gbTexture *` 这类"指向类"的指针；char*/void*/整数不算。"""
    kind, _text, cls = _classify_type_text(t)
    return kind == 'pointer' and bool(cls)


def _call_return_type(node):
    """call_expression → 返回类型文本（只认注解方法签名；解析不出返回 ''）。"""
    func = node.child_by_field_name('function')
    if func is None:
        return ''
    name = None
    if func.type == 'field_expression':
        f = func.child_by_field_name('field')
        name = f.text.decode('utf-8') if f is not None else None
    elif func.type == 'identifier':
        name = func.text.decode('utf-8')
    if not name:
        return ''
    return _method_return_index().get(name, '')


def _stride4_bumped_vars(tree):
    """{变量名: 4} —— `v = (T *)((char *)v + 4)` 步进形（`add reg,4` 的固定渲染）。"""
    out = {}

    def _strip(n):
        while n is not None:
            if n.type == 'cast_expression':
                n = n.child_by_field_name('value')
            elif n.type == 'parenthesized_expression':
                n = n.named_children[0] if n.named_children else None
            else:
                break
        return n

    def visit(node):
        if node.type == 'assignment_expression':
            left = node.child_by_field_name('left')
            right = node.child_by_field_name('right')
            if left is not None and left.type == 'identifier' and right is not None:
                b = _strip(right)
                if b is not None and b.type == 'binary_expression':
                    op = b.child_by_field_name('operator')
                    if op is not None and op.text == b'+':
                        pairs = ((b.child_by_field_name('left'),
                                  b.child_by_field_name('right')),
                                 (b.child_by_field_name('right'),
                                  b.child_by_field_name('left')))
                        for a, c in pairs:
                            if c is not None and c.text == b'4':
                                aa = _strip(a)
                                if (aa is not None and aa.type == 'identifier'
                                        and aa.text == left.text):
                                    out[left.text.decode('utf-8')] = 4
        for ch in node.children:
            visit(ch)

    visit(tree.root_node)
    return out


def _collect_ptr_disguise_edits(code_bytes, tree, ctx):
    """tagRECT* 伪装改写（判据①②③合取；判据不全一律不改）。

    对外产出 Edit 列表：(start, end, replacement)。
    """
    edits = []
    if ctx is None:
        return edits
    cls_name = getattr(ctx, 'cls_name', None)
    method_name = getattr(ctx, 'method_name', None)
    locals_ = _declared_local_types(tree, code_bytes)
    stride4 = _stride4_bumped_vars(tree)

    def visit(node):
        if node.type == 'assignment_expression':
            op = node.child_by_field_name('operator')
            left = node.child_by_field_name('left')
            right = node.child_by_field_name('right')
            if (op is not None and op.text == b'=' and left is not None
                    and left.type == 'field_expression' and right is not None):
                field = left.child_by_field_name('field')
                base = left.child_by_field_name('argument')
                fname = field.text.decode('utf-8') if field is not None else ''
                if (fname in _TAGRECT_FIELDS and base is not None
                        and base.type == 'identifier'):
                    # ① base 静态类型必须是 `tagRECT *`
                    bt = _expr_type(base, locals_, ctx)
                    if bt[0] == 'pointer' and bt[2] == 'tagRECT':
                        # ② 右值必须是类指针
                        rt = _expr_type(right, locals_, ctx)
                        rhs_ok = rt[0] == 'pointer' and bool(rt[2])
                        if not rhs_ok and right.type == 'call_expression':
                            ret = _call_return_type(right)
                            rhs_ok = bool(ret) and _is_class_pointer_type(ret)
                        if rhs_ok:
                            # ③ 同名局部变量二进制步长 4（实证白名单 + 步进形）
                            var = base.text.decode('utf-8')
                            ev = _PTR_DISGUISE_STRIDE4.get(
                                (cls_name, method_name, var))
                            if (ev is not None and ev.get('stride') == 4
                                    and stride4.get(var) == 4):
                                n = _TAGRECT_FIELDS[fname]
                                repl = ('*(DWORD *)((char *)%s + %d*4)'
                                        % (var, n)).encode('utf-8')
                                edits.append((left.start_byte, left.end_byte, repl))
                                edits.append((right.start_byte, right.start_byte,
                                              b'(DWORD)'))
        for ch in node.children:
            visit(ch)

    visit(tree.root_node)
    return edits


# ============================================================
# Indirect-call argument cast insertion (VC6 C2664)
# ============================================================
#
# Hex-Rays renders an indirect vtable/function-pointer call as an explicit cast:
#     (*(void (**)(char *, _DWORD, int *, ArcSceneMonster *))(v22 + 16))(
#         v8 + 215804, *(&g_ArcSceneMonsterTable + nVal), &v39, this);
# VC6 **type-checks the arguments against the cast prototype**, so an argument whose
# recovered type is a pointer (`this`, `&x`, a pointer global) cannot be passed to a
# parameter the cast spells as `_DWORD`/`unsigned long` ⇒ C2664
#   'void (char *,unsigned long,int *,class ArcSceneMonster *)' :
#       cannot convert parameter 2 from 'void *' to 'unsigned long'
# 实测（第 133 轮量化）：报文里 callee 名是"类型串"的错误共 **175 条**（38 个文件），
# 是当前剩余错误里最大的单一机制。原源码在这里带显式转换，Hex-Rays 把它丢了。
# 重新插入显式转换是**字节等价**的（同一个 32 位值进同一个槽，转换本身不产码，
# 与上面 C2440 赋值批同一判据）；且只在"实参/形参一边指针一边整数"时才插，
# 因此在**能编译的单元里这些站点根本不存在** ⇒ 不可能改变已通过的字节。
#
# 形状（tree-sitter）：call_expression
#   function → parenthesized_expression → pointer_expression → cast_expression
#     cast_expression.type_descriptor → abstract_function_declarator → parameter_list
#   arguments → argument_list（逐个实参节点）

def _fnptr_param_texts(type_descriptor):
    """`type_descriptor` → 形参类型文本列表（按 parameter_list 顺序）。"""
    out = []
    pl, stack = None, [type_descriptor]
    while stack:
        n = stack.pop()
        if n.type == 'parameter_list':
            pl = n
            break
        stack.extend(n.children)
    if pl is None:
        return out
    for ch in pl.children:
        if ch.type == 'parameter_declaration':
            out.append(ch.text.decode('utf-8'))
    return out


def _declared_fnptr_params(tree):
    """{变量名: [形参类型文本]} —— 只收"指向函数的指针"局部/全局声明。

    例：`void ( ***v5)(_DWORD, int);` ⇒ {'v5': ['_DWORD', 'int']}。
    这类间接调用（`(**v5)(v5, 1)`）与"显式 cast"形态是同一族 C2664，
    但形参表在**变量声明**里；`_declared_local_types` 只记 '*'，把参数表丢了。
    """
    out = {}

    def _pl(decl):
        stack = [decl]
        while stack:
            n = stack.pop()
            if n.type == 'function_declarator':
                for ch in n.children:
                    if ch.type == 'parameter_list':
                        return [c.text.decode('utf-8') for c in ch.children
                                if c.type == 'parameter_declaration']
                return None
            stack.extend(n.children)
        return None

    def walk(node):
        if node.type == 'declaration':
            pl = _pl(node)
            if pl is not None:
                nm = _declarator_name(node)
                if nm:
                    out.setdefault(nm, pl)
        for ch in node.children:
            walk(ch)

    walk(tree.root_node)
    return out


def _collect_indirect_call_cast_edits(code_bytes, tree, ctx):
    """给"经函数指针的间接调用"插入实参显式转换（指针 ←→ 整数）。

    两种形态：
      1. 显式 cast：`(*(void (**)(char *, _DWORD, ...))(EXPR))(A1, A2, ...)`
      2. 函数指针变量：`(**v5)(v5, 1)`（形参表取自 `v5` 的声明）
    """
    edits = []
    locals_ = _declared_local_types(tree, code_bytes)
    for _pn, _pt in _param_types(tree).items():
        locals_.setdefault(_pn, _pt)
    fnptr = _declared_fnptr_params(tree)

    SKIP = ('(', ')', ',', 'comment')

    def _widen(pt, an, pk, ak):
        if not pt or pk is None or ak is None:
            return
        if ((pk == 'integral' and ak == 'pointer')
                or (pk == 'pointer' and ak == 'integral')):
            edits.append((an.start_byte, an.start_byte,
                          ('(%s)(' % pt).encode('utf-8')))
            edits.append((an.end_byte, an.end_byte, b')'))

    def _apply(ptypes, args):
        anodes = [c for c in args.children if c.type not in SKIP]
        if len(ptypes) != len(anodes):
            return
        for ptext, an in zip(ptypes, anodes):
            pk, pt, _ = _classify_type_text(ptext)
            # 形如 `void ( ***v5)(_DWORD, int);` 的声明，`_declared_local_types` 只看见
            # 返回类型（`void`）⇒ 推断不出"是指针"。这类变量在 fnptr 表里，直接判为指针。
            if an.text.decode('utf-8').strip() in fnptr:
                ak = 'pointer'
            else:
                ak, _, _ = _expr_type(an, locals_, ctx)
            _widen(pt, an, pk, ak)

    def _callee_ident(node):
        stack = [node]
        while stack:
            n = stack.pop()
            if n.type == 'identifier':
                return n.text.decode('utf-8')
            for ch in n.children:
                stack.append(ch)
        return None

    def visit(node):
        if node.type == 'call_expression':
            fn = node.child_by_field_name('function')
            args = node.child_by_field_name('arguments')
            if fn is not None and args is not None:
                td = None
                if fn.type == 'parenthesized_expression':
                    ptr = next((c for c in fn.children
                                if c.type == 'pointer_expression'), None)
                    cast = None
                    if ptr is not None:
                        cast = next((c for c in ptr.children
                                     if c.type == 'cast_expression'), None)
                    if cast is not None:
                        td = next((c for c in cast.children
                                   if c.type == 'type_descriptor'), None)
                if td is not None:
                    _apply(_fnptr_param_texts(td), args)
                else:
                    nm = _callee_ident(fn)
                    if nm and nm in fnptr:
                        _apply(fnptr[nm], args)
        for ch in node.children:
            visit(ch)

    visit(tree.root_node)
    return edits



# ============================================================
# Float literal promotion (`x > 0.0` → `x > 0.0f` when x is float)
# ============================================================
#
# In C++ a `float` compared against a *double* literal is promoted to
# `double`, so MSVC6 emits a 64-bit compare:
#       FCOMP qword ptr [__real@0000000000000000]    (DC 1D <reloc>)
# The original source compared in float, so PAL3.exe has
#       FCOMP dword ptr ds:flt_56A644                (D8 1D 44 A6 56 00)
# (evidence: UIProgressBar::FindChildByName @0x0043FDF0, first 9 bytes
#  `D9 41 7C D8 1D 44 A6 56 00` = FLD m32fp + FCOMP m32fp).
#
# The only thing to fix is the *type* of the literal. Appending `f` keeps the
# comparison in float precision and is value-neutral **iff** the literal is
# exactly representable as a float (`(double)(float)v == v`); for a non-exact
# literal (`1.570796370506287`, `0.1`, `3.1415927`, …) `f` would round it and
# test a different number, so those are left alone. Integer literals are never
# touched: `float > int` converts the int to *float* (no double promotion), so
# `x > 0` is already a 32-bit compare.
#
# Type-conditioned, never textual: the non-literal operand must be *provably*
# `float` — a local, a parameter, `this->member`, `g_Global.member`, a
# `(float)` / `*(float *)&…` cast, or a float subscript — resolved with the
# same `_expr_type` machinery the C2440 cast pass above already uses. Anything
# resolving to `double`, an integer, a pointer, or nothing at all is skipped.
# Assignments are not touched either: for a float target MSVC6 already folds
# the double literal to a 32-bit constant (measured: `float m; m = 0.0;`
# emits `D9 05 <reloc>` = FLD m32fp in both arms).
#
# Every edit appends a single `f` to an existing number literal, so it cannot
# alter the token stream in any other way.  Measured blast radius on the
# committed tree: 272 sites in 44 files (0.0 ×220, 1.0 ×16, 255.0 ×16,
# -700.0 ×4, 2.0 ×3, 20.0 ×2, 4.5/19.0/36.0/-36.0/160.0/200.0/270.0/358.5/
# 359.0/360.0/470.0 ×1); 9 of them are in S2-passing units.

_FLOAT_CMP_OPS = {'<', '>', '<=', '>=', '==', '!='}
_FLOAT_LIT_SUFFIXES = ('f', 'F', 'l', 'L')


def _is_exact_float_literal(text):
    """True iff the C literal `text` may be rewritten as a float literal.

    F67（第 114 轮）：**不再要求"精确可表示"**。原先只放行 `(double)(float)v == v` 的字面量
    （0.0/1.0/255.0/…），把 `318.60001`、`0.0099999998`、`3.1415927` 这类**Hex-Rays 用 `%.7g`
    打印出来的 float 值**排除在外——但它们恰恰就是原二进制里的 float 常量：Hex-Rays 把 float
    渲染成 double 字面量，我们照抄成 double ⇒ 比较被提升为 64 位（`DC 1D` = FCOMP m64fp），
    而二进制是 `D8 1D` = FCOMP **m32fp**。补 `f` 后编译器会把它舍入到**最近的 float**——
    正是原常量的值。判据因此简化为"是浮点字面量（含 `.`/`e`）且无后缀"；整数字面量仍排除
    （`float > int` 本来就不提升）。
    """
    t = text.strip()
    if not t or t.endswith(_FLOAT_LIT_SUFFIXES):
        return False
    if '.' not in t and 'e' not in t and 'E' not in t:
        return False            # integer literal -> int-to-float, no promotion
    try:
        float(t)
    except ValueError:
        return False
    return True


def _param_types(tree):
    """{parameter_name: type_text} for the definition's parameter list.

    Parameters are not `declaration` nodes, so `_declared_local_types` misses
    them; without this a `float fValue` parameter would resolve to nothing and
    the rule would silently skip it.  Bodies are not descended into (nested
    lambdas would otherwise leak their parameters into this scope)."""
    out = {}

    def type_text_of(decl):
        # 与 _declared_local_types 共用同一实现（F78：必须能收 `struct X *` 的拼法）
        return _type_text_of(decl)

    def walk(node):
        if node.type == 'parameter_declaration':
            ttext = type_text_of(node)
            if ttext:
                nm = _declarator_name(node)
                if nm:
                    out.setdefault(nm, ttext)
            return
        if node.type == 'compound_statement':
            return
        for ch in node.children:
            walk(ch)

    for ch in tree.root_node.children:
        if ch.type in ('function_definition', 'declaration'):
            walk(ch)
    return out


# ============================================================
# CRT/Win32 call argument casts (VC6 C2664)
# ============================================================
#
# 这几个函数的原型**不是我们的注解**，而是系统/CRT 的固定 API（A 级、可枚举），
# 所以"注解改错"的解释不适用：错的是 Hex-Rays 给实参推断出的类型。
# 例：
#   MessageBoxA(hwnd, (int *)lpText, ...)   →  p2 应为 `const char *`
#   sprintf(buf,    (int *)fmt,    ...)     →  p2 应为 `const char *`
#   _mbsrchr((const unsigned __int8 *)s, c) →  p1 应为 `const unsigned char *`
#   lstrcpyA((unsigned char *)dst, src)     →  p1 应为 `char *`
# 插显式转换与 F74 同判据：同一寄存器/同一值进同一槽，转换本身不产码 ⇒ 字节等价；
# 只对**指针/整数**实参插（结构体、浮点一律跳过 ⇒ 不可能出现非法转换），
# 其中不兼容的那些站点本来编译不过；兼容站点最多得到一个恒等转换（不产码、不改字节）。
_CRT_ARG_TYPES = {
    'MessageBoxA': {2: 'const char *'},
    'MessageBoxW': {2: 'const unsigned short *'},
    'sprintf': {2: 'const char *'},
    'lstrcpyA': {1: 'char *'},
    'lstrcatA': {1: 'char *'},
    'lstrlenA': {1: 'const char *'},
    '_mbsrchr': {1: 'const unsigned char *'},
    '_mbschr': {1: 'const unsigned char *'},
    'strcpy': {1: 'char *', 2: 'const char *'},
    'strcat': {1: 'char *', 2: 'const char *'},
    'strlen': {1: 'const char *'},
    'atoi': {1: 'const char *'},
    'atof': {1: 'const char *'},
}


def _norm_ptr(t):
    """指针类型文本归一化：`const unsigned char *` → `unsigned char`。"""
    return re.sub(r'^const\s+', '', (t or '').rstrip('* ').strip()).strip()


def _collect_crt_arg_cast_edits(code_bytes, tree, ctx):
    """按固定 API 原型给 CRT/Win32 调用的实参插显式转换。"""
    edits = []
    locals_ = _declared_local_types(tree, code_bytes)
    for _pn, _pt in _param_types(tree).items():
        locals_.setdefault(_pn, _pt)

    def visit(node):
        if node.type == 'call_expression':
            fn = node.child_by_field_name('function')
            args = node.child_by_field_name('arguments')
            if (fn is not None and args is not None and fn.type == 'identifier'):
                table = _CRT_ARG_TYPES.get(fn.text.decode('utf-8'))
                if table:
                    anodes = [c for c in args.children
                              if c.type not in ('(', ')', ',', 'comment')]
                    for idx, ptext in table.items():
                        if idx - 1 >= len(anodes):
                            continue
                        an = anodes[idx - 1]
                        pk, _, _ = _classify_type_text(ptext)
                        ak, at, _ = _expr_type(an, locals_, ctx)
                        if pk != 'pointer' or ak is None:
                            continue
                        same = (ak == 'pointer'
                                and _norm_ptr(at) == _norm_ptr(ptext))
                        if same:
                            continue
                        if ak in ('pointer', 'integral'):
                            edits.append((an.start_byte, an.start_byte,
                                          ('(%s)' % ptext).encode('utf-8')))
        for ch in node.children:
            visit(ch)

    visit(tree.root_node)
    return edits


# ============================================================
# 引用形参 + 同类指针实参 ⇒ `*(arg)`（F78）
# ============================================================
#
# F77 把 `??4gbVec3D@@QAEXABU0@@Z` 一类的导入槽类型从 `int __thiscall(_DWORD, _DWORD)`
# 纠正成按修饰名的 `void (__thiscall *)(gbVec3D *, const gbVec3D *)` 之后，Hex-Rays 不再把
# 实参降级成 `float *`（旧错误 `cannot convert parameter 1 from 'float *' to 'const gbVec3D &'`），
# 而是原样传 `gbVec3D *` ⇒ 新错误 `... from 'const struct gbVec3D *' to 'const struct gbVec3D &'`。
# 同一族 52 条只是换了报法（第 137 轮实测：消失 52 / 新增 52）。
#
# 为什么不在 IDA 侧把槽设成真正的引用：IDA 的 Python 类型 API **构造不出引用类型** ——
# `ida_typeinf.parse_decl` 与 `idc.SetType` 都把 `T &` 落成 `T *`（实测 `dstr()` 打印为 `*`），
# 也没有 `create_ref`。所以只能在生成侧做**地址等价**改写：
# 传给 `const T &` 的 `*(p)` 与传给 `const T *` 的 `p` 是同一条指令、同一个地址 ⇒ 字节等价。
# 门（防止把"形参本来就是指针"的站点改坏）：被调必须是**运算符**（C++ 约定取 `const T &`）、
# 实参必须是指向**被调类自身**的指针、且不是显式 this 形态的接收者那一位。
_REF_OPERATOR_RE = re.compile(r'([A-Za-z_]\w*)\s*::\s*(operator\s*[^\s(]*)')


def _norm_struct_name(t):
    """`const struct gbVec3D` → `gbVec3D`（去掉 const/struct/class 前缀）。"""
    s = (t or '').strip()
    while True:
        m = re.match(r'^(?:const|volatile|struct|class|unsigned|signed)\s+(.*)$', s)
        if not m:
            return s
        s = m.group(1).strip()


def _collect_ref_arg_deref_edits(code_bytes, tree, ctx):
    """引用形参 + 同类指针实参 ⇒ 加 `*`（见上方说明）。"""
    edits = []
    locals_ = _declared_local_types(tree, code_bytes)
    for _pn, _pt in _param_types(tree).items():
        locals_.setdefault(_pn, _pt)

    def visit(node):
        if node.type == 'call_expression':
            fn = node.child_by_field_name('function')
            args = node.child_by_field_name('arguments')
            if fn is not None and args is not None:
                ftxt = fn.text.decode('utf-8')
                cls, meth, skip_first = None, None, False
                m = _REF_OPERATOR_RE.search(ftxt)
                if m and m.group(2).startswith('operator'):
                    cls, meth = _norm_struct_name(m.group(1)), m.group(2)
                    skip_first = ('->' not in ftxt)      # 显式 this：首参是接收者
                else:
                    # tree-sitter-cpp 对 `ptr->Class::method(args)` 这种**限定成员调用**
                    # 会产出 ERROR 节点（`->gbVec3D::operator=`），此时 function 字段是
                    # 接收者表达式、真正的方法名在 ERROR 子节点里（实测 AST：
                    # call_expression → parenthesized_expression + ERROR + argument_list）。
                    for ch in node.children:
                        if ch.type == 'ERROR':
                            m2 = re.search(
                                r'->\s*([A-Za-z_]\w*)\s*::\s*(operator\s*[^\s(]*)',
                                ch.text.decode('utf-8'))
                            if m2:
                                cls, meth = _norm_struct_name(m2.group(1)), m2.group(2)
                                break
                if cls and meth:
                    anodes = [c for c in args.children
                              if c.type not in ('(', ')', ',', 'comment')]
                    if skip_first and anodes:
                        anodes = anodes[1:]
                    for an in anodes:
                        if an.text.decode('utf-8').lstrip().startswith('*'):
                            continue
                        k, t, st = _expr_type(an, locals_, ctx)
                        # 只要求"是指针且指向被调类自身"：`&v19`（v19 是 gbVec3D）由
                        # `_expr_type` 的取址分支返回 ('pointer','gbVec3D','gbVec3D')，
                        # 类型文本可能是类名而不是 `T *`，所以不再要求 endswith('*')。
                        if k == 'pointer' and _norm_struct_name(st) == cls:
                            edits.append((an.start_byte, an.start_byte, b'*('))
                            edits.append((an.end_byte, an.end_byte, b')'))
        for ch in node.children:
            visit(ch)

    visit(tree.root_node)
    return edits


def _collect_float_literal_promotion_edits(code_bytes, tree, ctx):
    """Append `f` to double literals compared against a provably-float operand."""
    edits = []
    locals_ = _declared_local_types(tree, code_bytes)
    for _pn, _pt in _param_types(tree).items():
        locals_.setdefault(_pn, _pt)

    def visit(node):
        if node.type == 'binary_expression':
            op = node.child_by_field_name('operator')
            left = node.child_by_field_name('left')
            right = node.child_by_field_name('right')
            if (op is not None and left is not None and right is not None
                    and op.text.decode('utf-8') in _FLOAT_CMP_OPS):
                for lit, other in ((left, right), (right, left)):
                    if lit.type != 'number_literal':
                        continue
                    if not _is_exact_float_literal(lit.text.decode('utf-8')):
                        continue
                    if _expr_type(other, locals_, ctx)[1].strip() != 'float':
                        continue
                    edits.append((lit.end_byte, lit.end_byte, b'f'))
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
    edits += _collect_ptr_disguise_edits(code_bytes, tree, ctx)
    edits += _collect_indirect_call_cast_edits(code_bytes, tree, ctx)
    edits += _collect_crt_arg_cast_edits(code_bytes, tree, ctx)
    edits += _collect_ref_arg_deref_edits(code_bytes, tree, ctx)
    edits += _collect_float_literal_promotion_edits(code_bytes, tree, ctx)
    result = code_bytes
    for start, end, replacement in sorted(edits, reverse=True):
        result = result[:start] + replacement + result[end:]
    result = _fix_base_qualified_access(result.decode('utf-8'), ctx)
    # fn-ptr 限定形接线 2026-10-07（C2273 族——子对象引用形）
    try:
        from ast_transform import fix_fnptr_qualified_call
        result = fix_fnptr_qualified_call(result, base_names={'UIWnd', 'gbRefObject', 'ObjectInfoBase'})
    except Exception:
        pass
    # F2 offset 形接线 2026-10-07（非零基类——复核 N4/N5 通路）
    try:
        from ast_transform import rewrite_base_offset_read
        _bo = {('CCBRoleState', 'TaskMgr_SceneObjParam_SceneObj'): 40}
        result = rewrite_base_offset_read(result, base_offsets=_bo)
    except Exception:
        pass
    # 参铸接线 2026-10-07（C2664 族通解——元数门保守）
    # 根因修（96 轮）：sig=**被调函数** sig（非含函数）——method_sigs 查表
    try:
        from ast_transform import fix_arg_type_casts
        import re as _re
        # sig 源=注解直读（懒加载修——method_sigs 空实证）
        global _SIG_CACHE
        if _SIG_CACHE is None:
            import glob as _g, os as _o, json as _j
            _SIG_CACHE = {}
            for _p in _g.glob(_o.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), 'data', 'annotations', 'structs', '*.json')):
                try:
                    _d = _j.load(open(_p, encoding='utf-8'))
                    for _mk, _mv in (_d.get('methods') or {}).items():
                        if isinstance(_mv, dict) and _mv.get('name') and _mv.get('signature'):
                            _SIG_CACHE[str(_mv['name']).split('(')[0]] = _mv['signature']
                except Exception:
                    continue
        _ms = _SIG_CACHE
        def _callee_sig(name):
            for k, v in _ms.items():
                if k.endswith('::' + name) or k == name:
                    return v or ''
            return ''
        for _cm in _re.finditer(r'(?:->|\.)(\w+)\([^;]*\)\s*;', result):
            _nm = _cm.group(1)
            _sig = _callee_sig(_nm)
            if '(' not in _sig:
                continue
            _inner = _sig[_sig.find('(') + 1:_sig.rfind(')')]
            _sp = [x.strip() for x in _inner.split(',') if x.strip() and x.strip() != 'void']
            if _sp:
                result = fix_arg_type_casts(result, sig_params=_sp)
                break
    except Exception:
        pass
    # C2036 形修 2026-10-07：(void*)p+N → (char*)p+N（字节算术等价）
    try:
        from ast_transform import fix_void_ptr_arith_cast
        result = fix_void_ptr_arith_cast(result)
    except Exception:
        pass
    # B′ 窄形接线 2026-10-07（C2100 教训——this-> 链限定）
    global _BASE_NAMES_CACHE
    try:
        if _BASE_NAMES_CACHE is None:
            import glob as _g, os as _o, json as _j
            _bn = set()
            _bs = {}
            for _p in _g.glob(_o.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), 'data', 'annotations', 'structs', '*.json')):
                try:
                    _d = _j.load(open(_p, encoding='utf-8'))
                    for _b in (_d.get('base_class') or []):
                        if isinstance(_b, str) and len(_b) >= 3:
                            _bn.add(_b)      # 短/泛名拒（B 型污染教训 2026-10-07）
                            _bs[_b] = 4
                except Exception:
                    continue
            _BASE_NAMES_CACHE = (_bn, _bs)
        _bn, _bs = _BASE_NAMES_CACHE
        if _bn:
            from ast_transform import rewrite_base_suffix_bare_form
            result = rewrite_base_suffix_bare_form(result, base_names=_bn, base_sizes=_bs)
    except Exception:
        pass
    # 接线批 2026-10-07（三清账全备）：限定链冗余中间段删除（C2039 通路）
    # pairs=基链（类→基类）——判别器（合法三段形拒）。pairs 源：struct_bases（载后）+
    # 注解 base_class 直构（懒加载空时备选——2026-10-07 no-op 实证修）
    try:
        from ast_transform import drop_redundant_mid_qualifier
        _pairs = set()
        _bm = getattr(store, 'struct_bases', None) or {}
        for _c, _bs in _bm.items():
            for _b in (_bs or {}):
                _pairs.add((_c, _b))
        if not _pairs:
            # 备选源：注解 base_class 直读（struct_bases 懒加载空时——declared-exception 族）
            import glob as _glob
            import json as _json
            import os as _os
            for _f in _glob.glob(_os.path.join(
                    getattr(store, 'PROJECT_ROOT', os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))),
                    'data', 'annotations', 'structs', '*.json')):
                try:
                    _d = _json.load(open(_f, encoding='utf-8'))
                    _c = _d.get('name') or _os.path.basename(_f)[:-5]
                    for _b in (_d.get('base_class') or []):
                        if isinstance(_b, dict):
                            _b = _b.get('baseName') or _b.get('name')
                        if _b:
                            _pairs.add((_c, _b))
                    for _b in (_d.get('bases') or []):
                        if isinstance(_b, dict):
                            _b = _b.get('baseName') or _b.get('name')
                        if _b:
                            _pairs.add((_c, _b))
                except Exception:
                    continue
        if _pairs:
            result = drop_redundant_mid_qualifier(result, pairs=_pairs)
    except Exception:
        pass
    return _fix_member_fn_callbacks(result, ctx)


# ============================================================
# 基类限定的成员访问：`this->Cls::Base::member` → `this->Base::member`（F79）
# ============================================================
#
# **判定性实验（第 138 轮，用本仓自带 VC6）**：
#     class A { public: int x; };
#     class B : public A { };
#     void f(B *p) { p->B::A::x = 1; }   // error C2039: 'A' : is not a member of 'B'
#     void g(B *p) { p->A::x   = 1; }   // 合法
# ⇒ `this->Cls::Base::member` 把基类名当成了**成员名**（C++ 里 `X::Y::Z` 的 `Y` 必须是 X 的成员），
#   而 Hex-Rays 会用基类限定的写法表达"这个成员来自基类子对象"：正确拼法是 `this->Base::member`。
#
# 命中族（本轮 census）：`this->SceneObj::GlowObj::m_nTodo_000`（GlowObj 是 SceneObj 的基类）
# 与 `this->SceneObj::TaskMgr_SceneObjParam_SceneObj::m_nTodo_000`（同为基类）。
# 基类表直接读**生成头**的继承列表（编译器看到的就是它，与 IDB 侧 `store.struct_bases`
# 只有单个基类的情况不同 —— 生成头里 SceneObj 有三个基类）。
_CLASS_BASES_CACHE = None
_BASE_NAMES_CACHE = None
_SIG_CACHE = None


def _class_bases_index():
    """{类名: {基类名}} —— 来自 `pal3/src/**/*.h` 的 `class X : public A, public B {`。"""
    global _CLASS_BASES_CACHE
    if _CLASS_BASES_CACHE is None:
        import glob
        import os
        idx = {}
        root = getattr(store, 'output_dir', None) or 'pal3/src'
        for p in glob.glob(os.path.join(root, '**', '*.h'), recursive=True):
            try:
                with open(p, encoding='utf-8', errors='replace') as fh:
                    txt = fh.read()
            except OSError:
                continue
            for m in re.finditer(r'^\s*(?:class|struct)\s+(\w+)\s*:\s*([^{]+)\{',
                                 txt, re.M):
                bases = idx.setdefault(m.group(1), set())
                for b in m.group(2).split(','):
                    b = re.sub(r'\b(?:public|protected|private|virtual)\b', '', b)
                    b = b.split('<')[0].strip()          # 去模板实参
                    b = b.split('::')[-1].strip()         # 去命名空间前缀
                    if b and b != m.group(1):
                        bases.add(b)
        _CLASS_BASES_CACHE = idx
    return _CLASS_BASES_CACHE


def _reachable_bases(idx, cls):
    """cls 的全部直接/间接基类（闭包）。"""
    out, stack = set(), list(idx.get(cls, ()))
    while stack:
        b = stack.pop()
        if b in out or b == cls:
            continue
        out.add(b)
        stack.extend(idx.get(b, ()))
    return out


def _fix_base_qualified_access(code, ctx):
    """把 `this->X::Y::member` 改写成 `this->Y::member`（X 是当前类的基类、Y 是 X 的基类）。

    实例（本轮 census）：当前类 `CCBRoleState : public SceneObj`，
    `SceneObj : public PalScriptWaitObj, public GlowObj, public TaskMgr_SceneObjParam_SceneObj`；
    Hex-Rays 写 `this->SceneObj::GlowObj::m_nTodo_000` ⇒ C2039。多级路径（`this->A::B::C::`）
    逐轮收敛到 `this->C::`。
    """
    cls = getattr(ctx, 'cls_name', None) if ctx is not None else None
    if not cls:
        return code
    idx = _class_bases_index()
    reach = _reachable_bases(idx, cls)
    if not reach:
        return code
    pairs = []
    for x in [cls] + sorted(reach, key=len, reverse=True):
        for y in sorted(idx.get(x, ()), key=len, reverse=True):
            pairs.append((x, y))
    if not pairs:
        return code
    out = code
    for _ in range(3):                      # 最多收敛 3 层
        before = out
        for x, y in pairs:
            pat = re.compile(r'\bthis\s*->\s*' + re.escape(x) + r'\s*::\s*'
                             + re.escape(y) + r'\s*::')
            out = pat.sub('this->%s::' % y, out)
        if out == before:
            break
    return out
