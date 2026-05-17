"""Stage 3: Post-OOP cleanup.

Removes/comments IDA artifacts produced or exposed by Stage 2 (OOP transform).
Uses tree-sitter AST for ctor/vftable detection where beneficial,
with regex fallback for simple operations.
"""
import re
import struct as _struct

import tree_sitter_cpp as tscpp
import tree_sitter

from data import store

_lang = tree_sitter.Language(tscpp.language())
_parser = tree_sitter.Parser(_lang)


# ============================================================
# AST helpers
# ============================================================

def _get_call_method_and_cast_type(node):
    """For a call_expression, extract (method_name, cast_type_of_object).

    Returns (method_name, cast_type) or (None, None).
    Handles: ((Type *)expr)->Method(args) and expr->Method(args)
    """
    if node.type != 'call_expression':
        return None, None
    func = node.child_by_field_name('function')
    if not func or func.type != 'field_expression':
        return None, None
    field = func.child_by_field_name('field')
    if not field:
        return None, None
    method_name = field.text.decode('utf-8')

    # Get object and extract cast type
    obj = func.child_by_field_name('argument')
    cast_type = None
    if obj:
        cast_type = _extract_cast_type_name(obj)

    return method_name, cast_type


def _extract_cast_type_name(node):
    """Extract type name from cast: ((Type *)expr) → 'Type'."""
    # Unwrap parenthesized
    while node.type == 'parenthesized_expression':
        children = [c for c in node.children if c.type not in ('(', ')')]
        if len(children) == 1:
            node = children[0]
        else:
            break
    if node.type == 'cast_expression':
        type_node = node.child_by_field_name('type')
        if type_node:
            m = re.match(r'\s*(\w+)', type_node.text.decode('utf-8'))
            if m:
                return m.group(1)
    return None


# ============================================================
# Backtick patterns (kept as line-based — multi-line skip logic)
# ============================================================

_BACKTICK_PATTERNS = (
    "`eh vector constructor iterator'",
    "`eh vector destructor iterator'",
    "`default constructor closure'",
    "`scalar deleting destructor'",
    "`vftable'",
)


def _remove_backtick_calls(lines):
    """Remove backtick compiler calls (multi-line aware). Modifies list in-place."""
    out = []
    skip = False
    for line in lines:
        s = line.strip()
        if skip:
            if ';' in s:
                skip = False
            continue
        if any(p in s for p in _BACKTICK_PATTERNS):
            if ';' not in s:
                skip = True
            continue
        out.append(line)
    return out


# ============================================================
# AST-based cleanup pass
# ============================================================

def _ast_cleanup_pass(code, ctx):
    """Use tree-sitter to identify and handle vftable/ctor patterns.

    Returns modified code with same behavior as old regex-based logic.
    """
    tree = _parser.parse(code.encode('utf-8'))
    lines = code.split('\n')
    edits = {}  # line_idx -> action

    def visit(node):
        if node.type in ('expression_statement', 'return_statement'):
            line_idx = node.start_point[0]
            line_text = lines[line_idx] if line_idx < len(lines) else ''
            stripped = line_text.strip()

            # --- vftable assignment: this->__vftable = N ---
            if '__vftable' in stripped:
                if re.match(r'.*->?__vftable\s*=', stripped) or re.match(r'.*__vftable\s*=', stripped):
                    edits[line_idx] = 'delete'
                    return
                # vftable virtual call
                if ('->__vftable->' in stripped or '->__vftable)' in stripped) \
                        and stripped.endswith(';') and not stripped.startswith('//'):
                    edits[line_idx] = ('comment_vft', stripped)
                    return

            # --- Explicit ctor/dtor: ((Type*)expr)->Type(args); ---
            if '->' in stripped and stripped.endswith(';'):
                for child in _iter_descendants(node):
                    if child.type == 'call_expression':
                        method, cast_type = _get_call_method_and_cast_type(child)
                        if method and cast_type and cast_type == method:
                            # Standalone ctor/dtor at line start
                            if re.match(r'\s*\(\(', stripped):
                                edits[line_idx] = 'delete'
                                return

                # game_classes check (matches old _comment_out_explicit_ctor_calls)
                if not ctx.is_free_function:
                    m = re.search(r'->\s*([A-Z_]\w+)\s*\(', stripped)
                    if m and m.group(1) in store.game_classes:
                        called = m.group(1)
                        indent = line_text[:len(line_text) - len(line_text.lstrip())]
                        if '=' not in stripped and not stripped.startswith('return') \
                                and not stripped.startswith('if') \
                                and not stripped.startswith('while'):
                            edits[line_idx] = ('comment_ctor', stripped)
                            return
                        elif stripped.startswith('return'):
                            cast_m = re.match(
                                r'return\s+(.+?)\s*->\s*%s\s*\(' % re.escape(called), stripped)
                            if cast_m:
                                edits[line_idx] = ('return_expr', cast_m.group(1).rstrip())
                            else:
                                edits[line_idx] = ('return_this', None)
                            return
                        elif '=' in stripped:
                            edits[line_idx] = ('comment_ctor', stripped)
                            return

        for child in node.children:
            visit(child)

    visit(tree.root_node)

    # Apply edits
    out = []
    for i, line in enumerate(lines):
        if i not in edits:
            out.append(line)
            continue
        action = edits[i]
        indent = line[:len(line) - len(line.lstrip())]
        if action == 'delete':
            continue
        elif isinstance(action, tuple):
            kind = action[0]
            if kind == 'comment_vft':
                out.append(indent + '// [IDA_VFTABLE] ' + action[1])
            elif kind == 'comment_ctor':
                out.append(indent + '// [AUTO-COMMENTED] ' + action[1])
            elif kind == 'return_expr':
                out.append(indent + 'return %s; // ctor auto-called' % action[1])
            elif kind == 'return_this':
                out.append(indent + 'return this; // [ctor replaced]')
        else:
            out.append(line)

    return '\n'.join(out)


def _iter_descendants(node):
    """Yield all descendant nodes."""
    for child in node.children:
        yield child
        yield from _iter_descendants(child)


# ============================================================
# Main entry
# ============================================================

def run(code, ctx):
    """Stage 3: post-OOP cleanup."""
    cls_name = ctx.cls_name

    # Free functions: minimal path (TODO: expand after baseline stable)
    if ctx.is_free_function:
        code = re.sub(r'\(\*\)(\w+)', r'(*\1)', code)
        lines = code.split('\n')
        lines = _remove_backtick_calls(lines)
        # Inline vftable/ctor deletion for free functions (same as old _replace_ida_internals)
        out = []
        for line in lines:
            s = line.strip()
            if re.match(r'.*->?__vftable\s*=', s):
                continue
            if ('->__vftable->' in s or '->__vftable)' in s) and s.endswith(';') and not s.startswith('//'):
                indent = line[:len(line) - len(line.lstrip())]
                out.append(indent + '// [IDA_VFTABLE] ' + s)
                continue
            ctor_m = re.match(r'\s*\(\((\w+)\s*\*\)\s*[^)]*\)\s*->\s*~?(\w+)\s*\([^)]*\)\s*;', s)
            if ctor_m and ctor_m.group(1) == ctor_m.group(2):
                continue
            ctor_m2 = re.match(r'\s*\(\((\w+)\s*\*\)\s*\(\w+\s*\*\)\s*[^)]*\)\s*->\s*~?(\w+)\s*\([^)]*\)\s*;', s)
            if ctor_m2 and ctor_m2.group(1) == ctor_m2.group(2):
                continue
            out.append(line)
        return '\n'.join(out)

    # --- Class method full cleanup ---

    # Simple regex operations (no AST needed)
    if cls_name:
        code = re.sub(r'^\s*%s\s*\*\s*this\s*;.*$' % re.escape(cls_name), '', code, flags=re.MULTILINE)
    code = re.sub(r'\(\(operator \*\)(0x[0-9A-Fa-f]+u?)\)->new\(\)', r'operator new(\1)', code)
    code = re.sub(r'__thiscall\s+', '', code)
    code = re.sub(r'__userpurge\s+', '', code)
    code = re.sub(r'__usercall\s+', '', code)

    # COERCE_FLOAT
    def _fix_coerce(m):
        arg = m.group(1).strip()
        try:
            ival = int(arg, 0)
            if abs(ival) <= 100:
                return '%d.0f' % ival
            fval = _struct.unpack('f', _struct.pack('I', ival & 0xFFFFFFFF))[0]
            if abs(fval) < 1e10 and (abs(fval) > 1e-10 or fval == 0.0):
                if fval == int(fval) and abs(fval) < 1000000:
                    return '%d.0f' % int(fval)
                return '%.7gf' % fval
        except (ValueError, OverflowError):
            pass
        return m.group(0)
    code = re.sub(r'COERCE_FLOAT\((\s*-?(?:0x[0-9A-Fa-f]+|\d+)\s*)\)', _fix_coerce, code)

    # Simple fixes
    code = re.sub(r'\(\*\)(\w+)', r'(*\1)', code)
    code = re.sub(r'return\s+&this->__vftable\s*;', 'return this;', code)
    code = re.sub(r'return\s+\([^)]+\)\s*&this->__vftable\s*;', 'return this;', code)

    # AST-based ctor/vftable detection (replaces _comment_out_explicit_ctor_calls + part of _replace_ida_internals)
    code = _ast_cleanup_pass(code, ctx)

    # Post-AST simple regex
    code = re.sub(r'((?:LODWORD|HIDWORD)\s*\([^)]+\))\s*=\s*(&\w+)', r'\1 = (unsigned long)\2', code)

    def _fix_mfp(m):
        cm = m.group(1)
        a = re.search(r'_([0-9A-Fa-f]{5,})$', cm.split('::')[-1])
        return ('0x%s' % a.group(1)) if a else ('0 /* TODO: (int)%s */' % cm)
    code = re.sub(r'\(int\)\s*(\w+::(?:~?\w+))\b(?!\s*\()', _fix_mfp, code)

    # Backtick removal (line-based, after AST pass)
    lines = code.split('\n')
    lines = _remove_backtick_calls(lines)
    return '\n'.join(lines)
