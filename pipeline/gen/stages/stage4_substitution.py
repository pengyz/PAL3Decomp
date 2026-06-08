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
    m['Buffer'] = 'g_ScriptRoleBuf'
    return m


# ============================================================
# Literal + global resolution helpers
# ============================================================

def _try_literal_replacement(name):
    """Check if an identifier should be replaced with a literal value."""
    if name in store.literals:
        return store.literals[name]
    if name.startswith('dword_'):
        try:
            va = int(name.split('_')[1], 16)
        except (IndexError, ValueError):
            return None
        if 0x56A000 <= va <= 0x57F178 and va % 4 == 0:
            s = store.try_read_rdata_string(va)
            if s is not None and len(s) >= 2:
                escaped = s.replace('\\', '\\\\').replace('"', '\\"')
                escaped = escaped.replace('\n', '\\n').replace('\t', '\\t')
                replacement = '"%s"' % escaped
                store.literals[name] = replacement
                return replacement
    elif name.startswith('asc_'):
        try:
            va = int(name.split('_')[1], 16)
        except (IndexError, ValueError):
            return None
        if 0x56A000 <= va <= 0x57F178:
            s = store.try_read_rdata_string(va)
            if s is not None:
                escaped = s.replace('\\', '\\\\').replace('"', '\\"')
                escaped = escaped.replace('\n', '\\n').replace('\t', '\\t')
                replacement = '"%s"' % escaped
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
            elem_sz = _ELEM_SIZES.get(elem_type, store.struct_members.get(elem_type) and 4 or 0)
            if not elem_sz:
                sub_m = store.struct_members.get(elem_type)
                if sub_m:
                    elem_sz = 4
            if elem_sz and rel < arr_count * elem_sz and rel % elem_sz == 0:
                idx = rel // elem_sz
                sub_rel = rel - idx * elem_sz
                if sub_rel == 0:
                    return '.%s[%d]' % (mname, idx)
                sub_members = store.struct_members.get(elem_type)
                if sub_members:
                    sub = _resolve_offset(elem_type, sub_rel, prefix)
                    if sub:
                        return '.%s[%d]%s' % (mname, idx, sub)
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
    if addr < 0x00401000 or addr > 0x0057F178:
        return None
    prefix = name.split('_')[0]
    for base, end, gname, gtype in store.struct_instances:
        if base <= addr < end:
            offset = addr - base
            resolved = _resolve_offset(gtype, offset, prefix)
            if resolved:
                return '%s%s' % (gname, resolved)
    return None


def _try_global_name(name):
    """Map IDA unnamed globals (dword_XXX) → annotated name via globals_map + direct lookup."""
    if name in store.globals_map:
        return store.globals_map[name]
    if not (name.startswith(('dword_', 'byte_', 'word_', 'off_', 'unk_', 'stru_', 'flt_'))):
        return None
    try:
        addr = int(name.split('_', 1)[1], 16)
    except (ValueError, IndexError):
        return None
    for base, end, gname, _ in store.struct_instances:
        if base <= addr < end:
            store.globals_map[name] = gname
            return gname
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

    def visit(node):
        if node.type == 'identifier' and node.child_count == 0:
            name = node.text.decode('utf-8')
            replacement = None
            if name.startswith(('dword_', 'byte_', 'word_', 'off_', 'flt_', 'unk_')):
                replacement = _try_struct_member_resolution(name)
            if not replacement:
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

def run(code, ctx):
    """Stage 4: pure AST-based identifier/type resolution."""
    code_bytes = code.encode('utf-8')
    tree = _parser.parse(code_bytes)
    edits = _collect_token_edits(code_bytes, tree, ctx)
    result = code_bytes
    for start, end, replacement in sorted(edits, reverse=True):
        result = result[:start] + replacement + result[end:]
    return result.decode('utf-8')
