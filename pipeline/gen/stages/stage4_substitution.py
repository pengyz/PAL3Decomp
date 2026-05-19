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
            # Apply identifier map (e.g. TextureLib_Data → _TextureLib_Data)
            if name in thunk_map:
                edits.append((node.start_byte, node.end_byte, thunk_map[name].encode('utf-8')))
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

    Hex-Rays exposes string::_Tidy, string::_Eos, string::_Split etc.
    These are protected methods of basic_string — compiler generates them,
    not expressible in source.
    """
    if '->string::' not in code:
        return code
    lines = code.split('\n')
    result = []
    for line in lines:
        if '->string::' in line and '// [STL]' not in line:
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
