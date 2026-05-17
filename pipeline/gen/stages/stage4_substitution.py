"""Stage 4: Token-level substitution using tree-sitter AST.

Walks the AST token nodes (identifiers, types) and applies replacements.
No structural analysis needed — just token-level text mapping.
Single parse, single walk, batch edits.
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
    # Thunks: sub_XXX → TargetFunc, ClassName_thunk → real name
    m.update(store.thunks)
    # Thunk class types: j_UIWnd → UIWnd (for pointer casts)
    # Handled separately because it's "j_UIWnd *" not just "j_UIWnd"
    return m


def _try_literal_replacement(name):
    """Check if an identifier should be replaced with a literal value."""
    if name in store.literals:
        return store.literals[name]
    # On-demand .rdata string lookup for dword_ addresses
    if name.startswith('dword_'):
        try:
            va = int(name.split('_')[1], 16)
        except (IndexError, ValueError):
            return None
        if 0x56A000 <= va <= 0x5D6000 and va % 4 == 0:
            s = store.try_read_rdata_string(va)
            if s is not None and len(s) >= 2:
                escaped = s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n').replace('\t', '\\t')
                replacement = '"%s"' % escaped
                store.literals[name] = replacement
                return replacement
    elif name.startswith('asc_'):
        try:
            va = int(name.split('_')[1], 16)
        except (IndexError, ValueError):
            return None
        if 0x56A000 <= va <= 0x5D6000:
            s = store.try_read_rdata_string(va)
            if s is not None:
                escaped = s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n').replace('\t', '\\t')
                replacement = '"%s"' % escaped
                store.literals[name] = replacement
                return replacement
    return None


def _try_struct_member_resolution(name):
    """Check if identifier is a global struct instance member."""
    if name in store.literals:
        return None
    try:
        parts = name.split('_', 1)
        prefix, addr_hex = parts[0], parts[1]
        addr = int(addr_hex, 16)
    except (IndexError, ValueError):
        return None
    if prefix not in ('dword', 'byte', 'word', 'off', 'flt', 'unk'):
        return None
    for base, end, gname, gtype in store.struct_instances:
        if base <= addr < end:
            offset = addr - base
            members = store.struct_members.get(gtype, {})
            member_info = members.get(offset)
            if member_info:
                mname, mtype = member_info
                # Width compatibility check
                mt = mtype.strip().lower()
                if prefix == 'dword':
                    pass  # always compatible
                elif prefix == 'byte' and not any(t in mt for t in ('char', 'byte', 'bool')):
                    return None
                elif prefix == 'word' and not any(t in mt for t in ('short', 'word', 'wchar')):
                    return None
                elif prefix == 'off' and '*' not in mtype:
                    return None
                elif prefix == 'flt' and 'float' not in mt:
                    return None
                return '%s.%s' % (gname, mname)
            return None
    return None


def _try_global_name(name):
    """Check if identifier has a global name mapping."""
    try:
        pfx, hexpart = name.split('_', 1)
    except ValueError:
        return None
    if pfx not in ('dword', 'byte', 'word', 'stru', 'off', 'unk', 'flt'):
        return None
    key = '%s_%s' % (pfx, hexpart.upper())
    return store.globals_map.get(key)


# ============================================================
# AST-based token replacement
# ============================================================

def _collect_token_edits(code_bytes, tree, ctx):
    """Walk AST and collect identifier/type replacement edits."""
    edits = []  # [(start, end, replacement_bytes)]
    thunk_map = _build_identifier_map()

    def visit(node):
        # Identifier nodes (variable/function names)
        if node.type == 'identifier' and node.child_count == 0:
            name = node.text.decode('utf-8')
            replacement = None

            # Priority 1: struct member resolution
            if name.startswith(('dword_', 'byte_', 'word_', 'off_', 'flt_', 'unk_')):
                replacement = _try_struct_member_resolution(name)

            # Priority 2: global name mapping
            if not replacement and name.startswith(('dword_', 'byte_', 'word_', 'stru_', 'off_', 'unk_', 'flt_')):
                replacement = _try_global_name(name)

            # Priority 3: literal replacement
            if not replacement:
                replacement = _try_literal_replacement(name)

            # Priority 4: thunk replacement
            if not replacement and name in thunk_map:
                replacement = thunk_map[name]

            # Priority 5: aXxx string names
            if not replacement and name.startswith('a') and len(name) > 1 and name[1].isupper():
                replacement = _try_literal_replacement(name)

            if replacement:
                edits.append((node.start_byte, node.end_byte, replacement.encode('utf-8')))
                return  # Don't recurse into replaced nodes

        # Type identifiers
        elif node.type == 'type_identifier' and node.child_count == 0:
            name = node.text.decode('utf-8')
            # vtbl_XXXXXXXX → void
            if name.startswith('vtbl_') and all(c in '0123456789ABCDEFabcdef' for c in name[5:]):
                edits.append((node.start_byte, node.end_byte, b'void'))
                return

        # 'this' keyword in free functions → '_this'
        elif node.type == 'this' and ctx.is_free_function:
            edits.append((node.start_byte, node.end_byte, b'_this'))
            return

        # Recurse
        for child in node.children:
            visit(child)

    visit(tree.root_node)
    return edits


# ============================================================
# Non-AST substitutions (simple text operations without structural meaning)
# ============================================================

def _apply_text_substitutions(code, ctx):
    """Apply remaining text substitutions that are simpler as string operations."""
    # Thunk class type casts: j_ClassName * → ClassName *
    for cls in store.thunk_classes:
        if cls in code:
            real_cls = cls[2:] if cls.startswith('j_') else cls
            code = code.replace(cls + ' *', real_cls + ' *')
            code = code.replace(cls + ' **', real_cls + ' **')

    # IDA type aliases → standard C
    code = code.replace('unsigned __int8', 'unsigned char')
    code = code.replace('signed __int8', 'signed char')
    code = code.replace('unsigned __int16', 'unsigned short')
    code = code.replace('signed __int16', 'short')
    # Standalone __int8/__int16 (regex needed for word boundary)
    code = re.sub(r'\b__int8\b', 'char', code)
    code = re.sub(r'\b__int16\b', 'short', code)

    # LL suffix → i64 (regex for boundary)
    code = re.sub(r'(\b0x[0-9A-Fa-f]+)uLL\b', r'\1ui64', code)
    code = re.sub(r'(\b0x[0-9A-Fa-f]+)LL\b', r'\1i64', code)
    code = re.sub(r'(\b\d+)LL\b', r'\1i64', code)

    # _ThrowInfo (only for class methods — matches old behavior)
    if not ctx.is_free_function:
        code = code.replace('(_ThrowInfo *)', '(_s__ThrowInfo *)')

    # stdiobuf fix (free functions only)
    if ctx.is_free_function:
        code = code.replace('stdiobuf *', 'UIWnd *')
        code = code.replace('stdiobuf::', 'UIWnd::')
        code = code.replace('std::ios_base *', 'UIWnd *')

    return code


def _fix_ref_params(code):
    """Remove & for known reference-parameter method calls."""
    _REF_METHODS = {
        'Rotate': {1, 2}, 'Translate': {1}, 'Scale': {1},
        'RightMultiply': {1}, 'LeftMultiply': {1},
        'RightTranslate': {1}, 'LeftTranslate': {1},
        'MakeMatrix': {1, 2, 3}, 'IntersectPlane': {1, 2},
        'IsColTriangle': {1, 2, 3, 4}, 'IsColOBB': {1}, 'IsColOBB_H': {1},
        'IsColAABB': {1}, 'PointWorldToScr': {2, 3}, 'PointScrToWorld': {2, 3},
    }
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


# ============================================================
# Main entry
# ============================================================

def run(code, ctx):
    """Stage 4: token-level substitutions."""
    # AST-based identifier/type resolution
    code_bytes = code.encode('utf-8')
    tree = _parser.parse(code_bytes)
    edits = _collect_token_edits(code_bytes, tree, ctx)

    # Apply AST edits in reverse order
    result = code_bytes
    for start, end, replacement in sorted(edits, reverse=True):
        result = result[:start] + replacement + result[end:]
    code = result.decode('utf-8')

    # Text-level substitutions (type aliases, suffixes, thunk classes)
    code = _apply_text_substitutions(code, ctx)

    # Reference parameter fix (depends on OOP having produced ->Method() form)
    if not ctx.is_free_function:
        code = _fix_ref_params(code)

    return code
