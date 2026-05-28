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
    # Hex-Rays strips leading underscore from class names in casts.
    # Map stripped names back to the real annotation name.
    for cls in store.game_classes:
        if cls.startswith('_') and cls[1:] not in store.game_classes:
            m[cls[1:]] = cls
    # IDA unnamed struct globals → known global names
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
        if 0x56A000 <= va <= 0x57F178 and va % 4 == 0:
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
        if 0x56A000 <= va <= 0x57F178:
            s = store.try_read_rdata_string(va)
            if s is not None:
                escaped = s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n').replace('\t', '\\t')
                replacement = '"%s"' % escaped
                store.literals[name] = replacement
                return replacement
    return None


import re as _re_smr

_ELEM_SIZES = {'int': 4, 'float': 4, 'unsigned int': 4, 'unsigned long': 4,
               'char': 1, 'unsigned char': 1, 'bool': 1,
               'short': 2, 'unsigned short': 2, 'double': 8, 'long long': 8}


def _resolve_offset(type_name, offset, prefix):
    """Recursively resolve an offset within a type, returning a suffix like '.member[N]'."""
    members = store.struct_members.get(type_name, {})

    # Exact match at this offset
    info = members.get(offset)
    if info:
        mname, mtype = info
        # Width check for exact match
        mt = mtype.strip().lower()
        if prefix == 'byte' and not any(t in mt for t in ('char', 'byte', 'bool')) and '*' not in mtype:
            pass  # fall through to sub-resolution
        elif prefix == 'word' and not any(t in mt for t in ('short', 'word', 'wchar')):
            pass
        elif prefix == 'off' and '*' not in mtype:
            pass
        elif prefix == 'flt' and 'float' not in mt:
            pass
        else:
            return '.%s' % mname

    # No exact match - find the member that contains this offset
    for moff, (mname, mtype) in sorted(members.items(), reverse=True):
        if moff > offset:
            continue
        rel = offset - moff
        if rel == 0:
            continue  # already tried exact match above

        # Array member: TypeName[N]
        arr_m = _re_smr.match(r'^([\w\s\*]+?)\[(\d+)\]$', mtype.strip())
        if arr_m:
            elem_type = arr_m.group(1).strip()
            arr_count = int(arr_m.group(2))
            elem_sz = _ELEM_SIZES.get(elem_type, store.struct_members.get(elem_type) and 4 or 0)
            if not elem_sz:
                # Try struct element size
                sub_m = store.struct_members.get(elem_type)
                if sub_m:
                    # estimate from member offsets
                    elem_sz = 4  # fallback
            if elem_sz and rel < arr_count * elem_sz and rel % elem_sz == 0:
                idx = rel // elem_sz
                sub_rel = rel - idx * elem_sz  # should be 0 for primitive arrays
                if sub_rel == 0:
                    # Check if elem_type is a struct with sub-members
                    sub_suffix = _resolve_offset(elem_type, 0, prefix)
                    if sub_suffix and sub_suffix != '.':
                        return '.%s[%d]%s' % (mname, idx, sub_suffix)
                    return '.%s[%d]' % (mname, idx)
                else:
                    sub_suffix = _resolve_offset(elem_type, sub_rel, prefix)
                    if sub_suffix:
                        return '.%s[%d]%s' % (mname, idx, sub_suffix)
            continue

        # Embedded struct member (non-pointer, no array)
        if '*' in mtype:
            continue
        base_type = _re_smr.sub(r'\[.*\]', '', mtype).replace('const ', '').strip()
        if not base_type or not base_type[0].isupper() and base_type not in _ELEM_SIZES:
            continue
        if base_type in _ELEM_SIZES:
            continue  # primitive, can't recurse
        sub_suffix = _resolve_offset(base_type, rel, prefix)
        if sub_suffix:
            return '.%s%s' % (mname, sub_suffix)

    return None


def _try_struct_member_resolution(name):
    """Resolve dword_XXXX to g_Instance.member[N].sub_member etc. (recursive)."""
    if name in store.literals:
        return None
    try:
        prefix, addr_hex = name.split('_', 1)
        addr = int(addr_hex, 16)
    except (ValueError, AttributeError):
        return None
    if prefix not in ('dword', 'byte', 'word', 'off', 'flt', 'unk'):
        return None
    for base, end, gname, gtype in store.struct_instances:
        if base <= addr < end:
            suffix = _resolve_offset(gtype, addr - base, prefix)
            if suffix:
                return gname + suffix
            return None
    return None


def _try_global_name(name):
    """Check if identifier has a global name mapping."""
    # First check direct match (decompiler-generated names like 'Buffer')
    direct = store.globals_map.get(name)
    if direct:
        return direct
    # Then check prefix-based match (dword_XXXX, etc.)
    try:
        pfx, hexpart = name.split('_', 1)
    except ValueError:
        return None
    if pfx not in ('dword', 'byte', 'word', 'stru', 'off', 'unk', 'flt'):
        return None
    key = '%s_%s' % (pfx, hexpart.upper())
    return store.globals_map.get(key)


_INT_CONSTANTS = {
    301: 'ROLEID_JINGTIAN',
    302: 'ROLEID_XUEJIAN',
    303: 'ROLEID_LONGKUI',
    304: 'ROLEID_ZIXUAN',
    305: 'ROLEID_CHANGQING',
    306: 'ROLEID_HUAYING',
    311: 'ROLEID_CHONGLOU',
    50529027: 'MAGIC_SLOT_INIT',   # 0x03030303
    2949123: 'SUBGROUP_FLAG_MASK',  # 0x2D0003
    983043: 'SUBGROUP_FLAG_ALT',    # 0x0F0003
}

# Array index constants: (field_name, index) -> constant_name
_ARRAY_INDEX_CONSTANTS = {
    # _todo_694 (TeamConfigSlot array, stride=52)
    ('_todo_694', 89):  'TCS_TEAM_SIZE',     # team 1 count
    ('_todo_694', 90):  'TCS_CHAR_BASE',      # team 1 char vals start
    ('_todo_694', 95):  'TCS_FORM_BASE',      # team 1 formation start
    ('_todo_694', 116): 'TCS_TEAM_SIZE',       # (slot 2) reused constant
    ('_todo_694', 159): 'TCS_SKILL_ID',        # team 1 skill resource ID
    ('_todo_694', 160): 'TCS_SKILL_EN',        # team 1 skill enable
    ('_todo_694', 161): 'TCS_SKILL_NUM',       # team 1 skill gdb num
    # _todo_C00
    ('_todo_C00', 94):  'TC1_TEAM_SIZE',
    ('_todo_C00', 95):  'TC1_CHAR_BASE',
    ('_todo_C00', 100): 'TC1_FORM_BASE',
    ('_todo_C00', 164): 'TC1_SKILL_ID',
    ('_todo_C00', 165): 'TC1_SKILL_EN',
    ('_todo_C00', 166): 'TC1_SKILL_NUM',
    # _todo_UI4540_ext
    ('_todo_UI4540_ext', 26): 'UI3_TEAM_SIZE',
    ('_todo_UI4540_ext', 27): 'UI3_CHAR_BASE',
    ('_todo_UI4540_ext', 32): 'UI3_FORM_BASE',
    ('_todo_UI4540_ext', 53): 'UI3_MISC_ID',
    # _todo_UI5908_ext
    ('_todo_UI5908_ext', 36):  'UI5_TEAM_SIZE',
    ('_todo_UI5908_ext', 37):  'UI5_CHAR_BASE',
    ('_todo_UI5908_ext', 42):  'UI5_FORM_BASE',
    ('_todo_UI5908_ext', 63):  'UI5_MONSTER_ID',
    ('_todo_UI5908_ext', 106): 'UI5_SKILL_ID',
    ('_todo_UI5908_ext', 107): 'UI5_SKILL_EN',
    ('_todo_UI5908_ext', 108): 'UI5_SKILL_NUM',
    ('_todo_UI5908_ext', 126): 'UI5_EXT_FORM',
}

# Reverse lookup: index value -> list of (field_name, constant_name)
_ARRAY_IDX_BY_VAL = {}
for (field, idx), cname in _ARRAY_INDEX_CONSTANTS.items():
    _ARRAY_IDX_BY_VAL.setdefault(idx, []).append((field, cname))


def _get_subscript_array_name(node):
    """Extract the array field name from a subscript expression's argument.
    
    Handles patterns: field_expression (.field), identifier, etc.
    """
    if node is None:
        return None
    t = node.type
    if t == 'field_expression':
        field_node = node.child_by_field_name('field')
        if field_node:
            return field_node.text.decode('utf-8')
    elif t == 'identifier':
        return node.text.decode('utf-8')
    # Recurse through casts/parens
    elif t in ('cast_expression', 'parenthesized_expression'):
        return _get_subscript_array_name(node.child_by_field_name('argument'))
    return None

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

            # Priority 2: global name mapping (try always; _try_global_name handles prefix check internally)
            if not replacement:
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

            # 'this' as identifier in free function params → '_this'
            if not replacement and name == 'this' and ctx.is_free_function:
                replacement = '_this'

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
            # Apply identifier map (e.g. TextureLib_Data → _TextureLib_Data)
            if name in thunk_map:
                edits.append((node.start_byte, node.end_byte, thunk_map[name].encode('utf-8')))
                return

        # 'this' keyword in free functions → '_this'
        elif node.type == 'this' and ctx.is_free_function:
            edits.append((node.start_byte, node.end_byte, b'_this'))
            return

        # Integer literal replacement for known game constants
        elif node.type == 'number_literal' and node.child_count == 0:
            text = node.text.decode('utf-8')
            try:
                val = int(text, 0)  # handles hex (0x), octal (0o), decimal
                # Priority: array index constant (check AST parent)
                replacement = None
                if val in _ARRAY_IDX_BY_VAL:
                    # Check if this literal is an array subscript
                    parent = node.parent
                    if parent and parent.type == 'subscript_argument_list':
                        sub_expr = parent.parent
                        if sub_expr and sub_expr.type == 'subscript_expression':
                            obj_node = sub_expr.child_by_field_name('argument')
                            arr_name = _get_subscript_array_name(obj_node)
                            key = (arr_name, val)
                            if key in _ARRAY_INDEX_CONSTANTS:
                                replacement = _ARRAY_INDEX_CONSTANTS[key]
                # Fallback: general value constant
                if not replacement and val in _INT_CONSTANTS:
                    replacement = _INT_CONSTANTS[val]
                if replacement:
                    edits.append((node.start_byte, node.end_byte,
                                  replacement.encode('utf-8')))
                    return
            except (ValueError, OverflowError):
                pass

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
    # Orphan ordinal placeholders: struct $OrdN → void
    # (ordinals that Hex-Rays couldn't resolve to type names)
    code = re.sub(r'struct \$Ord\d+', 'void', code)

    # Thunk class type casts: j_ClassName * → ClassName *
    for cls in store.thunk_classes:
        if cls in code:
            real_cls = cls[2:] if cls.startswith('j_') else cls
            code = code.replace(cls + ' *', real_cls + ' *')
            code = code.replace(cls + ' **', real_cls + ' **')

    # Strip _misattrib_ prefix from type casts and references
    # (misattrib functions are grouped under their base class name in codegen,
    #  but Hex-Rays output still references the _misattrib_ prefix in casts)
    code = re.sub(r'_misattrib_(\w+)', r'\1', code)

    # IDA type aliases → standard C
    code = code.replace('unsigned __int8', 'unsigned char')
    code = code.replace('signed __int8', 'signed char')
    code = code.replace('unsigned __int16', 'unsigned short')
    code = code.replace('signed __int16', 'short')
    # Standalone __int8/__int16 (regex needed for word boundary)
    code = re.sub(r'\b__int8\b', 'char', code)
    code = re.sub(r'\b__int16\b', 'short', code)

    # LL/i64 suffix removal — VC6 doesn't recognize i64/LL suffixes.
    # Large hex constants are auto-promoted to __int64 by VC6 without suffix.
    code = re.sub(r'(\b0x[0-9A-Fa-f]+)(?:uLL|LL|ui64|i64)\b', r'\1', code)
    code = re.sub(r'(\b\d+)(?:uLL|LL|ui64|i64)\b', r'\1', code)

    code = code.replace('(_ThrowInfo *)', '(_s__ThrowInfo *)')

    # Hex-Rays raw offset access: &this->0 means "address of member at offset 0" = this
    # this->0 standalone means "value of first DWORD" = *(_DWORD*)this
    code = re.sub(r'&this->0\b', 'this', code)
    code = re.sub(r'\bthis->0\b', '*(_DWORD *)this', code)

    # stdiobuf misidentification fix
    code = code.replace('stdiobuf *', 'UIWnd *')
    code = code.replace('stdiobuf::', 'UIWnd::')
    code = code.replace('std::ios_base *', 'UIWnd *')

    # IDA 'std' type = std::basic_string<char> abbreviated
    code = re.sub(r'\bstd\s*\*', 'string *', code)
    code = re.sub(r'\(std\)', '(string)', code)

    return code


def _fix_register_this_alias(code):
    """Replace Hex-Rays register-this pattern: _ESI = this; ... _ESI->x → this->x.

    Hex-Rays uses pseudo-register variables (_ESI, _EDI etc.) to bridge
    asm blocks and C code in large functions. When assigned from 'this',
    all subsequent uses of that register are equivalent to 'this'.
    Only replaces in C code, not inside __asm blocks.
    """
    for reg in ('_ESI', '_EDI', '_EBX', '_ECX'):
        assign_pat = re.compile(r'^\s*' + re.escape(reg) + r'\s*=\s*this\s*;', re.MULTILINE)
        if not assign_pat.search(code):
            continue
        # Remove the assignment line
        code = assign_pat.sub('', code)
        # Split into asm/non-asm segments, only replace in non-asm
        parts = re.split(r'(__asm\s*\{[^}]*\})', code, flags=re.DOTALL)
        for i in range(len(parts)):
            if not parts[i].strip().startswith('__asm'):
                parts[i] = re.sub(r'\b' + re.escape(reg) + r'\s*->', 'this->', parts[i])
                parts[i] = re.sub(r'\b' + re.escape(reg) + r'\b', 'this', parts[i])
        code = ''.join(parts)
    return code


def _fix_static_method_calls(code):
    """Convert ((ClassName *)0)->Method(...) to ClassName::Method(...).

    Hex-Rays emits this pattern for static/singleton getter calls where this=NULL.
    """
    # Pattern: ((ClassName *)0)->Method( or ((ClassName *)expr)->Method(
    # Only convert for methods known to be static (in store.static_methods)
    from data import store
    for qualified in store.static_methods:
        cls, method = qualified.split('::', 1)
        # ((ClassName *)0)->Method(  →  ClassName::Method(
        pattern = r'\(\(' + re.escape(cls) + r'\s*\*\s*\)\s*0\)\s*->\s*' + re.escape(method) + r'\s*\('
        replacement = cls + '::' + method + '('
        code = re.sub(pattern, replacement, code)
        # ((ClassName *)expr)->Method(  →  ClassName::Method(  (drop expr for static)
        pattern2 = r'\(\(' + re.escape(cls) + r'\s*\*\s*\)\s*\w+\)\s*->\s*' + re.escape(method) + r'\s*\('
        code = re.sub(pattern2, replacement, code)
    return code


def _fix_ulong_uint_cast(code):
    """Add explicit casts for pointer type mismatches due to IDA type inference errors.

    On x86 Windows, unsigned long/unsigned int/long/int are all 32-bit.
    Handles:
    1. unsigned long* vs unsigned int* (user structs)
    2. long* vs int* (Windows API types like RECT.left/right/top/bottom)

    Conservative approach: handle known patterns.
    """
    # Pattern 1: EffMgr unsigned long fields
    patterns = [
        r'&g_EffMgr\.m_EffTable\[[^\]]+\]\.dwRunGroupID',
        r'&g_EffMgr\.m_EffTable\[[^\]]+\]\.dwClassNameCRC',
        r'&g_EffMgr\.m_EffTable\[[^\]]+\]\.dwTypeNameCRC',
    ]

    for pattern in patterns:
        code = re.sub(
            r'(?<!\(unsigned int \*\))(' + pattern + r')',
            r'(unsigned int *)\1',
            code
        )

    # Pattern 2: Windows RECT members (LONG = long, but function expects int*)
    # Match: &this[N].m_rect.{left|right|top|bottom}
    # Also: &variable.m_rect.{left|right|top|bottom}
    rect_members = r'\.(left|right|top|bottom)'

    # Case 2a: &this[N].m_rect.member or &this[N].xxx.m_rect.member
    code = re.sub(
        r'(?<!\(int \*\))(&this\[\d+\](?:\.\w+)*\.m_rect' + rect_members + r')',
        r'(int *)\1',
        code
    )

    # Case 2b: &var.m_rect.member
    code = re.sub(
        r'(?<!\(int \*\))(&\w+\.m_rect' + rect_members + r')',
        r'(int *)\1',
        code
    )

    return code


def _fix_ref_params(code):
    """Restore reference parameters for known gbengine methods.

    IDA flattens C++ references to pointers. Hex-Rays outputs &var for these.
    For methods declared with & params in gbengine headers, remove the &.
    Only applies to ->Method() calls (instance methods via gbMatrixStack etc.),
    NOT to Class::Method() calls (which may be gbMatrix4 taking pointers).
    """
    # Methods with reference params: {name: set of 1-based param positions}
    _REF_METHODS = {
        'Rotate': {1, 2}, 'Translate': {1}, 'Scale': {1},
        'RightMultiply': {1}, 'LeftMultiply': {1},
        'RightTranslate': {1}, 'LeftTranslate': {1},
        'MakeMatrix': {1, 2, 3}, 'IntersectPlane': {1, 2},
        'IsColTriangle': {1, 2, 3, 4}, 'IsColOBB': {1}, 'IsColOBB_H': {1},
        'IsColAABB': {1}, 'PointWorldToScr': {2, 3}, 'PointScrToWorld': {2, 3},
        'PopMessage': {1}, 'IsColPoint': {1}, 'IsColSphere': {1},
    }
    for method_name, ref_pos in _REF_METHODS.items():
        if method_name not in code:
            continue
        # Only match ->Method( pattern (instance call), NOT Class::Method(
        if ref_pos == {1}:
            code = re.sub(r'(->' + re.escape(method_name) + r'\s*\()&(\w)', r'\1\2', code)
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


def _comment_stl_internals(code):
    """Comment out STL internal method calls that can't compile in user code.

    Hex-Rays exposes string::_Tidy, string::_Eos, string::_Split, _Xlen etc.
    These are protected methods of basic_string — compiler generates them,
    not expressible in source.
    """
    _stl_methods = ('->string::', '->_Xlen(', '->_Tidy(', '->_Eos(', '->_Split(',
                    '->codecvt_base::', '->strstreambuf::', '->ios_base::')
    if not any(pat in code for pat in _stl_methods):
        return code
    lines = code.split('\n')
    result = []
    for line in lines:
        if any(pat in line for pat in _stl_methods) and '// [STL]' not in line:
            result.append(line.replace(line.lstrip(), '// [STL] ' + line.lstrip()))
        else:
            result.append(line)
    return '\n'.join(result)


def _fix_asm_data_labels(code):
    """Replace IDA asm 'ds:flt_XXXX' / 'ds:dbl_XXXX' with static const float variable.

    If the literal value is known (from store.literals), declare a static const
    and reference it. Otherwise use dword ptr [flt_XXXX] with extern decl.
    """
    from data import store
    if 'ds:flt_' not in code and 'ds:dbl_' not in code:
        return code

    # Collect all flt_/dbl_ labels referenced in asm
    flt_labels = set(re.findall(r'ds:(flt_[0-9A-Fa-f]+)', code))
    dbl_labels = set(re.findall(r'ds:(dbl_[0-9A-Fa-f]+)', code))

    # For flt_ with known literal values: declare static const float
    consts = {}
    for label in flt_labels:
        if label in store.literals:
            val = store.literals[label]
            varname = '_k_' + label
            consts[label] = (varname, val)

    # Replace ds:label with dword ptr [var]
    for label in flt_labels:
        if label in consts:
            varname = consts[label][0]
            code = re.sub(r'ds:' + re.escape(label), 'dword ptr [%s]' % varname, code)
        else:
            code = re.sub(r'ds:' + re.escape(label), 'dword ptr [%s]' % label, code)
    for label in dbl_labels:
        code = re.sub(r'ds:' + re.escape(label), 'qword ptr [%s]' % label, code)

    # Prepend static const declarations
    if consts:
        lines = code.split('\n')
        insert_idx = 0
        for i, line in enumerate(lines):
            if line.strip() == '{':
                insert_idx = i + 1
                break
        decls = []
        for label, (varname, val) in sorted(consts.items()):
            clean_val = val.rstrip('f')
            decls.append('  static const float %s = %sf;' % (varname, clean_val))
        if decls and insert_idx > 0:
            lines = lines[:insert_idx] + decls + lines[insert_idx:]
            code = '\n'.join(lines)

    return code


def _fix_asm_hex_ambiguity(code):
    """Fix MASM hex constants that look like C float literals.

    0E0h, 0A4h etc. are valid MASM hex but VC6 C parser sees '0E0' as float exponent.
    Fix by converting to 0x prefix format in __asm blocks.
    """
    if '__asm' not in code:
        return code
    return re.sub(r'\b(0[A-Fa-f][0-9A-Fa-f]*)h\b', lambda m: '0x' + m.group(1)[1:], code)


def _fix_asm_float_constants(code):
    """Replace IDA asm 'ds:1.2f' with static const float variable references.

    VC6 inline asm cannot use 'ds:' prefix. We replace with dword ptr [VAR].
    The static const declarations are collected and prepended to the function.
    """
    float_re = re.compile(r'ds:(-?\d+\.[\d]*f?)')
    matches = float_re.findall(code)
    if not matches:
        return code

    consts = {}
    for val in set(matches):
        clean = val.rstrip('f')
        varname = '_flt_' + clean.replace('.', '_').replace('-', 'neg')
        consts[val] = varname

    def _repl(m):
        return 'dword ptr [%s]' % consts[m.group(1)]

    code = float_re.sub(_repl, code)

    # Prepend static const declarations before function body
    lines = code.split('\n')
    insert_idx = 0
    for i, line in enumerate(lines):
        if line.strip() == '{':
            insert_idx = i + 1
            break

    decls = []
    for val, varname in sorted(consts.items(), key=lambda x: x[1]):
        clean = val.rstrip('f')
        decls.append('  static const float %s = %sf;' % (varname, clean))

    if decls and insert_idx > 0:
        lines = lines[:insert_idx] + decls + lines[insert_idx:]
        code = '\n'.join(lines)

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
        'PopMessage': {1}, 'IsColPoint': {1}, 'IsColSphere': {1},
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

    # Fix IDA asm float constants: ds:1.2f → static const float variable
    code = _fix_asm_float_constants(code)

    # Fix IDA asm data labels: ds:flt_XXXX → dword ptr [flt_XXXX]
    code = _fix_asm_data_labels(code)

    # Fix MASM hex ambiguity: 0E0h → 0xE0 (prevents C parser float confusion)
    code = _fix_asm_hex_ambiguity(code)

    # Convert ((ClassName *)0)->Method() to ClassName::Method() for static methods
    code = _fix_static_method_calls(code)

    # Replace _REG = this; ... _REG->xxx with this->xxx
    code = _fix_register_this_alias(code)

    # Restore reference parameters: ->Method(&var) → ->Method(var)
    # IDA flattens references to pointers; this restores for known ref-param methods
    code = _fix_ref_params(code)

    # Add explicit casts for unsigned long* → unsigned int* conversions
    # x86 safe: both 32-bit, fixes IDA function pointer type inference errors
    code = _fix_ulong_uint_cast(code)

    # Comment out STL internal method calls (string::_Tidy, string::_Eos, string::_Split)
    # These are compiler-generated operations not expressible in user source code.
    code = _comment_stl_internals(code)

    # Qualify Win32 API calls that may be shadowed by class methods
    # Only replace standalone calls (not ->API or .API or ::API)
    import re as _re_qualify
    _win32_apis = ['SendMessageA', 'lstrcpyA', 'GetCursorPos']
    for api in _win32_apis:
        code = _re_qualify.sub(
            r'(?<![->.:])' + api + r'\(',
            '::' + api + '(',
            code
        )

    return code
