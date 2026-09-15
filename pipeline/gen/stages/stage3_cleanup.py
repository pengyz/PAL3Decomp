"""Stage 3: Post-OOP cleanup using tree-sitter AST.

All structural detection is done through AST node types.
No regex is used for pattern recognition — only for simple text substitution
where no structural understanding is needed (e.g., __thiscall removal).
"""
import re
import struct as _struct
import sys

import tree_sitter_cpp as tscpp
import tree_sitter

from data import store

_lang = tree_sitter.Language(tscpp.language())
_parser = tree_sitter.Parser(_lang)


# ============================================================
# AST node analysis (pure structural — no regex matching)
# ============================================================

def _node_contains_text(node, text):
    """Check if any descendant token contains exact text."""
    if node.text and text.encode() in node.text:
        return True
    return False


def _is_vftable_field(node):
    """Check if a field_expression accesses __vftable."""
    if node.type == 'field_expression':
        field = node.child_by_field_name('field')
        if field and field.text == b'__vftable':
            return True
    return False


def _find_vftable_in_subtree(node):
    """Check if any node in subtree is a __vftable field access."""
    if _is_vftable_field(node):
        return True
    for child in node.children:
        if _find_vftable_in_subtree(child):
            return True
    return False


def _is_vftable_assignment(node):
    """Detect: this->__vftable = expr (assignment to vftable pointer).

    NOTE (t7 audit): this branch is preempted by `_comment_vptr_stores()` in
    `run()`, which runs *before* `_ast_cleanup()` and already rewrites or
    comments every `__vftable` statement.  It is kept because it is the
    correct AST-level description of the pattern and becomes reachable again
    if that earlier pass is ever narrowed; it is currently dead in practice
    (verified with a direct `stage3_run` harness, see
    data/status/_cleanup_fix_vftable_comment.md §7).
    """
    if node.type == 'assignment_expression':
        left = node.child_by_field_name('left')
        if left and _is_vftable_field(left):
            return True
    return False


def _is_vftable_call(node):
    """Detect: ((Type*)obj->__vftable)->Method(args) or similar vftable dispatch."""
    if node.type == 'call_expression':
        func = node.child_by_field_name('function')
        if func and _find_vftable_in_subtree(func):
            return True
    return False


def _try_resolve_vftable(expr):
    """Resolve (*(void (**)(Type*))(obj->__vftable + N))(args) → obj->Method(args).

    Uses vtable slot annotations to map byte offset to method name.
    Returns None if resolution fails.
    """
    m = re.match(
        r'\(\s*\*\s*\(\s*void\s+'
        r'\(\s*(?:__thiscall|__stdcall|\s*)\s*'
        r'\*\s*\*\s*\)'
        r'\s*\(\s*(\w+)\s*\*'
        r'[^)]*\)\s*\)'
        r'\s*\(\s*(\w+(?:\s*->\s*\w+)*)\s*->\s*__vftable\s*\+\s*(\d+)\s*\)'
        r'\s*\)\s*\((.*)\)\s*;\s*$',
        expr, re.DOTALL
    )
    if not m:
        return None

    class_type = m.group(1)
    obj_expr = m.group(2)
    offset = int(m.group(3))
    args = m.group(4)
    slot_index = offset // 4

    try:
        import json, os
        _d = os.path.dirname
        ann_path = os.path.join(_d(_d(_d(_d(os.path.abspath(__file__))))),
                                'data', 'annotations', 'structs', '%s.json' % class_type)
        if not os.path.exists(ann_path):
            return None
        ann = json.load(open(ann_path))
        vtables = ann.get('vtables', [])
        if not vtables:
            return None
        slots = vtables[0].get('slots', [])
        if slot_index >= len(slots):
            return None
        entry = ann.get('methods', {}).get(slots[slot_index].get('addr', ''), {})
        name = entry.get('name', '')
        if not name or '::' not in name:
            return None
        method = name.split('::')[-1]
    except (OSError, ValueError, KeyError, IndexError, TypeError) as _e:
        # t7: was a bare `except Exception`.  This helper only reads a JSON
        # annotation file and walks its dicts, so the failures above are the
        # expected ones; anything else (e.g. a refactor breaking the shape of
        # `struct_vtables` data) now surfaces instead of silently degrading
        # every vtable call to a stub.
        sys.stderr.write('[stage3] vftable resolution failed for %s: %r\n'
                         % (class_type, _e))
        return None

    _args = [a.strip() for a in args.split(',')]
    _args = [a for a in _args if a != obj_expr]
    return '%s->%s(%s);' % (obj_expr, method, ', '.join(_args))


def _get_ctor_call_info(node):
    """Detect explicit ctor: ((Type*)expr)->Type(args) where cast_type == method.

    Returns (method_name, object_expr_text) if ctor detected, else (None, None).
    """
    if node.type != 'call_expression':
        return None, None

    func = node.child_by_field_name('function')
    if not func or func.type != 'field_expression':
        return None, None

    # Get method name
    field = func.child_by_field_name('field')
    if not field:
        return None, None
    method_name = field.text.decode('utf-8')

    # Get object expression
    obj = func.child_by_field_name('argument')
    if not obj:
        return None, None

    # Extract cast type from object
    cast_type = _extract_cast_type(obj)

    # Check: cast_type == method_name (strict ctor pattern)
    if cast_type and cast_type == method_name:
        return method_name, obj.text.decode('utf-8')

    # Check: method_name is a known game class (game_classes ctor pattern)
    if method_name in store.game_classes:
        return method_name, obj.text.decode('utf-8')

    # Check: destructor pattern this->~ClassName() or (cast)->~ClassName()
    if method_name.startswith('~'):
        return method_name, obj.text.decode('utf-8')

    return None, None


def _extract_cast_type(node):
    """Extract outermost cast type from complex expressions.

    Handles: ((Type *)expr), ((Type *)(char*)this + N), etc.
    Walks through parenthesized/binary/cast layers to find the first cast_expression.
    """
    # Unwrap parenthesized_expression layers
    while node.type == 'parenthesized_expression':
        children = [c for c in node.children if c.type not in ('(', ')')]
        if len(children) == 1:
            node = children[0]
        else:
            break

    # Direct cast
    if node.type == 'cast_expression':
        type_desc = node.child_by_field_name('type')
        if type_desc:
            for child in _iter_all(type_desc):
                if child.type == 'type_identifier':
                    return child.text.decode('utf-8')

    # Binary expression: (Type*)(char*)this + N → look at left operand
    if node.type == 'binary_expression':
        left = node.child_by_field_name('left')
        if left:
            return _extract_cast_type(left)

    return None


def _iter_all(node):
    """Recursively yield all descendant nodes."""
    yield node
    for child in node.children:
        yield from _iter_all(child)


def _fold_ctor_call_value(line, call_node):
    """Fold an explicit ctor call that is used as a *value* into a typed pointer.

    Hex-Rays renders `obj.Cls(args)` / `obj->Cls(args)` for an explicit
    constructor call and gives it the class pointer as its "return value".
    When that value is consumed (assigned, member-accessed, passed on), the
    surrounding statement is real code and must not be dropped.

    `obj.Cls(args)`  -> `((Cls *)&obj)`     (object addressed through '.')
    `obj->Cls(args)` -> `((Cls *)obj)`      (object already a pointer)

    Returns the rewritten line, or None when the call cannot be folded
    (caller then keeps the previous comment-out behaviour).
    """
    func = call_node.child_by_field_name('function')
    if func is None or func.type != 'field_expression':
        return None
    method, _obj_text = _get_ctor_call_info(call_node)
    if not method:
        return None
    obj_node = func.child_by_field_name('argument')
    if obj_node is None:
        return None
    op = func.child_by_field_name('operator')
    arrow = (op is not None and op.text == b'->')
    cls = method[1:] if method.startswith('~') else method
    obj = obj_node.text.decode('utf-8', errors='replace')
    ptr = '((%s *)%s)' % (cls, obj) if arrow else '((%s *)&%s)' % (cls, obj)
    call_text = call_node.text.decode('utf-8', errors='replace')
    pos = line.find(call_text)
    if pos < 0:
        return None
    return line[:pos] + ptr + line[pos + len(call_text):]


# ============================================================
# AST cleanup pass
# ============================================================

def _ast_cleanup(code, ctx):
    """Walk AST and generate edits for vftable/ctor patterns."""
    tree = _parser.parse(code.encode('utf-8'))
    lines = code.split('\n')
    edits = {}  # line_idx -> (action, data)

    def visit(node):
        # Only examine statement-level nodes
        if node.type == 'expression_statement':
            line_idx = node.start_point[0]
            if line_idx in edits:
                return

            # Check for vftable assignment
            for child in _iter_all(node):
                if _is_vftable_assignment(child):
                    edits[line_idx] = ('delete', None)
                    return

            # Vftable calls are handled by regex preprocessing (above).
            # AST detection is unreliable for complex function-pointer call syntax.

            # Check for explicit ctor/dtor call
            for child in _iter_all(node):
                if child.type == 'call_expression':
                    method, obj_text = _get_ctor_call_info(child)
                    if method:
                        stripped = lines[line_idx].strip() if line_idx < len(lines) else ''
                        # Standalone at line start with ((Type*) pattern → delete
                        if child.parent == node or (child.parent and child.parent.type == 'cast_expression'):
                            # Check if it's truly standalone (no assignment/return wrapping)
                            is_standalone = node.child_count <= 2  # expr + ;
                            if is_standalone:
                                edits[line_idx] = ('delete', None)
                                return

                        # game_classes pattern: comment out if not in if/while
                        if not ctx.is_free_function:
                            if '=' not in stripped and not stripped.startswith('return') \
                                    and not stripped.startswith('if') \
                                    and not stripped.startswith('while'):
                                edits[line_idx] = ('comment_ctor', stripped)
                                return
                            elif '=' in stripped:
                                # t7: this used to be commented out wholesale,
                                # which discarded the assignment's *value* even
                                # when later statements consume it
                                # (e.g. CCBStage.cpp `Color = v22.gbColorQuad(..)->Color;`).
                                # Hex-Rays models an explicit ctor call as a
                                # value-returning call whose value is the object
                                # address, so fold the call to a typed pointer to
                                # the object and keep the assignment intact.
                                folded = _fold_ctor_call_value(lines[line_idx], child) \
                                    if line_idx < len(lines) else None
                                if folded is not None:
                                    edits[line_idx] = ('assign_ctor', folded)
                                else:
                                    edits[line_idx] = ('comment_ctor', stripped)
                                return
                        break

        elif node.type == 'return_statement' and not ctx.is_free_function:
            line_idx = node.start_point[0]
            if line_idx in edits:
                return

            # Check for return ctor call
            for child in _iter_all(node):
                if child.type == 'call_expression':
                    method, obj_text = _get_ctor_call_info(child)
                    if method:
                        # Try to get the object expression for "return obj;"
                        func_node = child.child_by_field_name('function')
                        if func_node and func_node.type == 'field_expression':
                            obj_node = func_node.child_by_field_name('argument')
                            if obj_node:
                                edits[line_idx] = ('return_expr', obj_node.text.decode('utf-8'))
                            else:
                                edits[line_idx] = ('return_this', None)
                        else:
                            edits[line_idx] = ('return_this', None)
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
        action, data = edits[i]
        indent = line[:len(line) - len(line.lstrip())]
        if action == 'delete':
            continue
        elif action == 'comment_ctor':
            out.append(indent + '// [AUTO-COMMENTED] ' + data)
        elif action == 'assign_ctor':
            # t7: value-preserving restoration of a commented-out assignment.
            out.append(data)
        elif action == 'return_expr':
            out.append(indent + 'return %s; // ctor auto-called' % data)
        elif action == 'return_this':
            out.append(indent + 'return this; // [ctor replaced]')
        else:
            out.append(line)

    # t7: two edit actions were deleted here because they had no producer
    # anywhere in the tree (`[IDA_VFTABLE]` was measured at 0 occurrences and
    # `'insert'` was never emitted by `_ast_cleanup` or any other stage):
    #   elif action == 'insert':       out.append(data)
    #   elif action == 'comment_vft':  out.append(indent + '// [IDA_VFTABLE] ' + data)
    # Original intent (documented, not re-implemented): `comment_vft` was meant
    # for IDA-layer-emitted vftable annotations — an "the IDB already told us
    # this is a vftable" marker distinct from the codegen-side `// [VFTABLE]`
    # fallback below. The IDA layer never produced that action, so the marker
    # was unreachable and its spelling (`[IDA_VFTABLE]`, no dash) was one of
    # the four non-mergeable spellings flagged in the cleanup handoff §2.3.

    return '\n'.join(out)


# ============================================================
# Backtick removal (line-based — backtick strings don't parse as AST nodes)
# ============================================================

_BACKTICK_PATTERNS = (
    "`eh vector constructor iterator'",
    "`eh vector destructor iterator'",
    "`default constructor closure'",
    "`scalar deleting destructor'",
    "`vftable'",
)


def _remove_backtick_calls(code):
    """Remove backtick compiler calls (multi-line skip)."""
    lines = code.split('\n')
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
    return '\n'.join(out)


# ============================================================
# Main entry
# ============================================================

# ============================================================
# AST-based vtable call resolution
# ============================================================
# Hex-Rays renders virtual dispatch two ways:
#   direct body call:   A::f((A*)p, x)            -> p->A::f(x)  (handled in ast_transform)
#   vtable dispatch:    ((R (*)(...))p->__vftable->f)(p, x)      (vtable struct typed)
#                       (*(R (**)(...))(p->__vftable + N))(p, x) (raw offset)
# A vtable dispatch rewritten as p->f(x) is byte-faithful: headers declare
# vtable slots `virtual`, so the compiler emits call [vtbl+slot] again.
# Slot maps come from annotations: struct_vtables[cls] = {slot_index: method}.
# Calls we cannot resolve get a signature-accurate static stub so the
# enclosing expression survives compilable (marked [VFTABLE-STUB]).

_VTBL_STUB_MARK = '[VFTABLE-STUB]'


def _decode_vtbl_call(call_node):
    """Decode a vtable dispatch call_expression.

    Returns dict(obj, method, offset, cls_hint, ret, params) or None.
    method is set for named-slot form; offset (0 when absent) for raw form.
    """
    func = call_node.child_by_field_name('function')
    if func is None:
        return None

    # unwrap redundant parens around the function sub-expression
    while func is not None and func.type == 'parenthesized_expression':
        inner = func.named_children
        func = inner[0] if inner else None
    if func is None:
        return None

    text = func.text.decode('utf-8', errors='replace')

    ret = None
    params = None
    cls_hint = None

    type_node = None
    if func.type == 'cast_expression':
        type_node = func.child_by_field_name('type')
    if type_node is not None:
        type_text = type_node.text.decode('utf-8', errors='replace')
        m = re.match(r'^\s*(.*?)\(\s*\*+\s*\)\s*\((.*)\)\s*$', type_text, re.DOTALL)
        if m:
            ret = ' '.join(m.group(1).split())
            params = ' '.join(m.group(2).split())
    if ret is None:
        # fallback: first "ret (*)(params)" shape anywhere in the function text
        m = re.search(r'([\w ]+?)\(\s*\*+\s*\)\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)', text)
        if m:
            ret = ' '.join(m.group(1).split())
            params = ' '.join(m.group(2).split())
    if params:
        first = params.split(',')[0].strip()
        if first and first != 'void':
            cls_hint = re.sub(r'\*+\s*$', '', first).strip()

    # object chain: the identifier chain immediately feeding __vftable
    mn = re.search(r'(\w+(?:\s*->\s*\w+)*)\s*->\s*__vftable\s*->\s*(\w+)', text)
    if mn:
        return {'obj': mn.group(1), 'method': mn.group(2), 'offset': None,
                'cls_hint': cls_hint, 'ret': ret, 'params': params}
    mo = re.search(r'(\w+(?:\s*->\s*\w+)*)\s*->\s*__vftable\s*(?:\+\s*(\d+))?', text)
    if mo:
        return {'obj': mo.group(1), 'method': None,
                'offset': int(mo.group(2)) if mo.group(2) else 0,
                'cls_hint': cls_hint, 'ret': ret, 'params': params}
    return None


def _resolve_vtbl_method(d):
    """Map decoded call to a method name declared virtual in some header."""
    sv = store.struct_vtables
    if d['method']:
        # verify the method really is a vtable slot of the hinted class
        if d['cls_hint'] and d['method'] in sv.get(d['cls_hint'], {}).values():
            return d['method']
        owners = [c for c, slots in sv.items() if d['method'] in slots.values()]
        if len(owners) == 1:
            return d['method']
        return None
    if d['offset'] is not None and d['cls_hint']:
        slots = sv.get(d['cls_hint'], {})
        if d['cls_hint'] in sv:
            return slots.get(d['offset'] // 4)
    return None


def _vtbl_stub_names(ret, params, idx):
    """Build thunk declaration+definition preserving cast signature."""
    is_ptr = ret.rstrip().endswith('*')
    is_void = ret.strip() == 'void'
    is_scalar = any(k in ret for k in ('int', 'long', 'short', 'char', 'float',
                                       'double', 'bool', '__int', 'signed',
                                       'unsigned', 'size_t', 'BOOL'))
    if is_void:
        body = ''
    elif is_ptr or is_scalar:
        body = 'return 0;'
    else:
        body = 'return %s();' % ret
    decl = 'static %s pal3_vtbl_unk_%d(%s);' % (ret, idx, params)
    definition = ('static %s pal3_vtbl_unk_%d(%s)\n{\n    %s\n}'
                  % (ret, idx, params, body))
    return decl, definition


def _resolve_vftable_calls_ast(code, ctx):
    tree = _parser.parse(code.encode('utf-8'))
    edits = []          # (start_byte, end_byte, replacement)
    stub_items = []     # (decl, definition) in emission order
    covered = []        # byte ranges already replaced (skip nested nodes)

    def _inside_covered(n):
        s, e = n.start_byte, n.end_byte
        return any(s >= cs and e <= ce for cs, ce in covered)

    def _split_args(args_text):
        args, depth, cur = [], 0, ''
        for ch in args_text:
            if ch in '([':
                depth += 1
            elif ch in ')]':
                depth -= 1
            if ch == ',' and depth == 0:
                args.append(cur.strip())
                cur = ''
            else:
                cur += ch
        if cur.strip():
            args.append(cur.strip())
        return args

    def _drop_self_arg(args, obj):
        if not args:
            return args
        first = args[0].strip()
        obj_n = ' '.join(obj.split())
        # "(Class *)obj" / "obj" forms both count as the self argument
        stripped = re.sub(r'^\(\s*[\w :]+\*+\s*\)\s*', '', first).strip()
        if first == obj_n or stripped == obj_n:
            return args[1:]
        return args

    def visit(node):
        if node.type == 'call_expression' and not _inside_covered(node):
            func = node.child_by_field_name('function')
            if func is not None and _find_vftable_in_subtree(func):
                d = _decode_vtbl_call(node)
                if d is not None:
                    args_node = node.child_by_field_name('arguments')
                    raw_args = args_node.text.decode('utf-8', errors='replace')
                    args = _split_args(raw_args[1:-1] if raw_args.startswith('(') else raw_args)
                    method = _resolve_vtbl_method(d)
                    if method:
                        keep = _drop_self_arg(args, d['obj'])
                        repl = '%s->%s(%s)' % (d['obj'], method, ', '.join(keep))
                    else:
                        if d['ret'] is not None and d['params'] is not None:
                            idx = len(stub_items)
                            decl, definition = _vtbl_stub_names(d['ret'], d['params'], idx)
                            stub_items.append(
                                (decl, definition,
                                 '// %s original: %s'
                                 % (_VTBL_STUB_MARK,
                                    ' '.join(node.text.decode('utf-8', errors='replace').split()))))
                            repl = 'pal3_vtbl_unk_%d(%s) /* %s */' % (
                                idx, ', '.join(args), _VTBL_STUB_MARK)
                        else:
                            # no cast info at all — leave for legacy fallbacks
                            repl = None
                    if repl is not None:
                        edits.append((node.start_byte, node.end_byte, repl))
                        covered.append((node.start_byte, node.end_byte))
                        return  # don't descend into replaced node
        for child in node.children:
            visit(child)

    visit(tree.root_node)

    if not edits and not stub_items:
        return code

    for s, e, repl in sorted(edits, key=lambda t: -t[0]):
        code = code[:s] + repl + code[e:]

    if stub_items:
        block = ['\n// ---- synthesized vtable stubs (unresolved slots) ----']
        for decl, definition, comment in stub_items:
            block.append(comment)
            block.append(decl)
        block.append('')
        thunk_block = '\n'.join(block) + '\n'
        m = re.search(r'(?:^#[^\n]*\n)+', code, re.MULTILINE)
        if m:
            code = code[:m.end()] + thunk_block + code[m.end():]
        else:
            code = thunk_block + code
        # definitions at end of file: declared above first use, valid C++
        defs = '\n'.join(dfn for _, dfn, _ in stub_items)
        code = code.rstrip('\n') + '\n\n' + defs + '\n'

    return code


# ============================================================
# t7: __vftable statement handling
# ============================================================
# Context for the two passes below (full audit in
# data/status/_cleanup_fix_vftable_comment.md):
#   * the header generator emits only `data_members`; the `__vftable`
#     `_variants` of `ida_structs.json` are dropped, so *no* generated header
#     declares `__vftable` — raw text can never compile;
#   * every exported `__vftable` variant sits at offset 0 of its own struct
#     (118/118 in the annotations, 116/116 in `ida_structs.json._variants`);
#   * a *qualified* access (`this->GlowObj::__vftable`) is a base subobject at
#     a non-zero offset (SceneObj: GlowObj +8, TaskMgr_SceneObjParam_SceneObj
#     +40), which the decomp text does not carry — those are left verbatim
#     instead of being folded to a wrong offset.

# `<obj>[Base::]__vftable = <rhs>;` (whole statement on one line)
_VPTR_STORE_RE = re.compile(
    r'^[ \t]*(?P<pre>[^=;]*?)__vftable\s*=\s*(?!=)(?P<rhs>[^;]*?)\s*;\s*(?://.*)?$')

# Positive evidence that <rhs> is a *vtable address*: only these lines are
# genuine compiler-managed vptr setup and may take the comment-out path.
# Deliberately narrow — `(vtbl_XXXX *)` is the declared type of the field and
# Hex-Rays emits it for data stores as well, and `= 0` / `= <local>` show up
# in the tree as genuine data writes (verified contexts in the .md).
_VPTR_RHS_EVIDENCE = re.compile(r"`vftable'")

# Decisive evidence that <rhs> is a data value (float/int bit pattern).
_VPTR_RHS_DATA = re.compile(
    r"\(\s*[A-Za-z_][\w:]*\s*\*+\s*\)\s*-?\s*(?:0[xX][0-9A-Fa-f]+|\d+)\s*$"
    r"|LODWORD\s*\(|HIDWORD\s*\(|\*\s*\(\s*float\s*\*")


def _vptr_store_kind(line):
    """Return 'store' when `line` is a positively-evidenced vptr store."""
    body = re.sub(r'/\*.*?\*/', '', line)      # ignore stub/original comments
    tag = body.find('__vftable')
    if tag < 0:
        return None
    slash = body.find('//')
    if slash >= 0 and slash < tag:
        return None                            # only referenced in a comment
    m = _VPTR_STORE_RE.match(body)
    if not m:
        return None
    pre = m.group('pre').rstrip()
    if not (pre.endswith('>') or pre.endswith('.') or pre.endswith('::')):
        return None                            # `*(float *)&x.__vftable = ..`
    rhs = m.group('rhs').strip()
    if _VPTR_RHS_DATA.search(rhs):
        return None
    if rhs.startswith('&') or _VPTR_RHS_EVIDENCE.search(rhs):
        return 'store'
    return None


def _comment_vptr_stores(code):
    """Comment out genuine vptr stores only (the only allowed comment path).

    t7: replaces the two blanket scanners that commented out *every* line
    containing `__vftable` (a bracket-depth block scanner plus a
    `^...__vftable[^;]*;.*$` regex).  Everything else is left for
    `_fold_vftable_mask()`.
    """
    lines = code.split('\n')
    out = []
    i = 0
    in_block = False
    while i < len(lines):
        line = lines[i]
        if in_block:
            out.append(line)
            if '*/' in line:
                in_block = False
            i += 1
            continue
        if '/*' in line and '*/' not in line:
            in_block = True
        if _vptr_store_kind(line) == 'store':
            commented = ['// [VFTABLE] ' + line.lstrip()]
            depth = line.count('(') - line.count(')')
            has_semi = line.rstrip().endswith(';')
            i += 1
            while i < len(lines) and not has_semi and depth > 0:
                cont_line = lines[i]
                commented.append('// [VFTABLE]   ' + cont_line.lstrip())
                depth += cont_line.count('(') - cont_line.count(')')
                has_semi = cont_line.rstrip().endswith(';')
                i += 1
            out.extend(commented)
        else:
            out.append(line)
            i += 1
    return '\n'.join(out)


def _needs_ptr_wrap(rhs):
    """True when a restored assignment RHS must be made pointer-shaped."""
    r = rhs.strip()
    if r.startswith('&') or '__vftable' in r:
        return False
    if re.match(r'^\(\s*[A-Za-z_][\w:\s]*\*+\s*\)', r):
        return False
    return True


def _fold_vftable_mask(code):
    """Restore every *unqualified* `__vftable` access as an offset-0 access.

    Byte-exact equivalences (the vfptr variant is at offset 0 of its object):
        X->__vftable    -> (*(void **)(X))       value/lvalue, type `void *`
        X.__vftable     -> (*(void **)&(X))
        &X->__vftable   -> ((void **)(X))        address,     type `void **`
        &X.__vftable    -> ((void **)&(X))

    Skipped (left verbatim, reported as a gap in the .md):
      * qualified base accesses `X->Base::__vftable` — base offset unknown;
      * `X->__vftable->M` / `X->__vftable[i]` — the vptr value is used as an
        object and `void *` cannot be dereferenced.

    For `X->__vftable = rhs` the RHS is additionally wrapped in `(void *)`
    when it is not already pointer-shaped, because the field's declared type
    is `void *`.
    """
    raw = code.encode('utf-8')
    tree = _parser.parse(raw)
    edits = []
    covered = []

    def _overlaps(s, e):
        return any(not (e <= cs or s >= ce) for cs, ce in covered)

    def visit(node):
        if node.type == 'field_expression':
            field = node.child_by_field_name('field')
            if field is not None and field.text == b'__vftable' \
                    and field.type != 'qualified_identifier':
                arg = node.child_by_field_name('argument')
                op = node.child_by_field_name('operator')
                if arg is not None and op is not None:
                    target = node
                    parent = node.parent
                    if parent is not None and parent.type == 'pointer_expression' \
                            and parent.child_by_field_name('operator') is not None \
                            and parent.child_by_field_name('operator').text == b'&':
                        target = parent
                    p = target.parent
                    used_as_object = (
                        p is not None
                        and p.type in ('field_expression', 'subscript_expression')
                        and p.child_by_field_name('argument') is not None
                        and p.child_by_field_name('argument').id == target.id)
                    if not used_as_object and not _overlaps(target.start_byte, target.end_byte):
                        obj = raw[arg.start_byte:arg.end_byte].decode('utf-8')
                        arrow = (op.text == b'->')
                        deref = '(%s)' % obj if arrow else '&(%s)' % obj
                        if target is parent:
                            repl = '((void **)%s)' % deref
                        else:
                            repl = '(*(void **)%s)' % deref
                        edits.append((target.start_byte, target.end_byte, repl))
                        covered.append((target.start_byte, target.end_byte))
                        ap = target.parent
                        if ap is not None and ap.type == 'assignment_expression':
                            left = ap.child_by_field_name('left')
                            right = ap.child_by_field_name('right')
                            aop = ap.child_by_field_name('operator')
                            if left is not None and left.id == target.id \
                                    and right is not None and aop is not None \
                                    and aop.text == b'=' \
                                    and raw[right.start_byte:right.end_byte].decode('utf-8').strip():
                                rhs = raw[right.start_byte:right.end_byte].decode('utf-8')
                                if _needs_ptr_wrap(rhs):
                                    edits.append((right.start_byte, right.end_byte,
                                                  '(void *)(%s)' % rhs))
                                    covered.append((right.start_byte, right.end_byte))
        for child in node.children:
            visit(child)

    visit(tree.root_node)
    if not edits:
        return code
    for s, e, repl in sorted(edits, key=lambda t: -t[0]):
        raw = raw[:s] + repl.encode('utf-8') + raw[e:]
    return raw.decode('utf-8')


def run(code, ctx):
    """Stage 3: post-OOP cleanup."""
    cls_name = ctx.cls_name

    # --- Simple text substitutions (no structural analysis needed) ---

    # Remove 'this' variable declaration (for class methods)
    if not ctx.is_free_function and cls_name:
        code = re.sub(r'^\s*%s\s*\*\s*this\s*;.*$' % re.escape(cls_name), '', code, flags=re.MULTILINE)

    # Operator new fix
    code = re.sub(r'\(\(operator \*\)(0x[0-9A-Fa-f]+u?)\)->new\(\)', r'operator new(\1)', code)
    # CC removal from body (function pointer casts)
    code = re.sub(r'__thiscall\s+', '', code)
    code = re.sub(r'__userpurge\s+', '', code)
    code = re.sub(r'__usercall\s+', '', code)

    # Hex-Rays ".0" member access (offset-0 field): obj[N].0 → obj[N], obj.member.0 → obj.member
    code = re.sub(r'(?<=[\]a-zA-Z_])\.0\b', '', code)

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

    # Dereference fix and ctor return
    code = re.sub(r'\(\*\)(\w+)', r'(*\1)', code)
    if not ctx.is_free_function:
        code = re.sub(r'return\s+&this->__vftable\s*;', 'return this;', code)
        code = re.sub(r'return\s+\([^)]+\)\s*&this->__vftable\s*;', 'return this;', code)
        # REMOVED: this->\w+() regex was too broad — it deleted ALL zero-arg
        # this->Method() calls including legitimate ones like SetupCamControl().
        # Base class ctor calls are rare in decomp and harmless if present
        # (MSVC6 treats them as method calls, not ctor re-invocation).

    # Try to resolve vtable dispatch calls to direct method calls before commenting out.

    # AST-based generalized resolver FIRST (handles every syntactic form the
    # tree-sitter parse can see: named-slot cast calls, raw-offset casts,
    # plain __vftable->Method). Unresolved calls are rewritten to synthesized
    # signature-accurate stubs so the surrounding expression survives —
    # the old "comment out the statement" fallback destroyed enclosing
    # expressions (e.g. `sqrt(v) * scale[vtcall(...)]` lost the multiply).
    code = _resolve_vftable_calls_ast(code, ctx)

    # Pattern: (*(ret_type (callconv **)(Type*))(obj->__vftable + N))(args);
    # Matches any return type (void, int, gbTexture*, etc.)
    _vtable_re = re.compile(
        r'\(\s*\*\s*\(\s*\(?\s*\w+(?:\s*\*)*\s+'               # ret_type (int, gbTexture*, etc.)
        r'\(\s*(?:__thiscall|__stdcall|\s*)\s*'
        r'\*\s*\*\s*\)'
        r'\s*\(\s*(\w+)\s*\*'                                    # (Type*
        r'[^)]*\)\s*\)'
        r'\s*\(?\s*(\w+(?:\s*->\s*\w+)*)\s*->\s*__vftable\s*(?:\+\s*(\d+))?\s*\)'
        r'\s*\)\s*\((.*?)\)\s*;\s*')
    def _try_resolve_vtable(m):
        cls = m.group(1)
        obj = m.group(2)
        off_str = m.group(3)
        off = int(off_str) if off_str else 0
        args_str = m.group(4)
        slot = off
        _indent = m.group(0)[:len(m.group(0)) - len(m.group(0).lstrip())]
        try:
            _slots = store.struct_vtables.get(cls, {})
            if slot in _slots:
                _method = _slots[slot]
                _args = [a.strip() for a in args_str.split(',')]
                _args = [a for a in _args if a.replace('&', '').strip() != obj]
                return '%s->%s(%s);\n%s' % (obj, _method, ', '.join(_args), _indent)
        except (AttributeError, KeyError, TypeError, IndexError, ValueError) as _e:
            # t7: was a bare `except: pass` (three legacy resolvers).  They only
            # read `store.struct_vtables`; unexpected shapes must not be swallowed
            # (cf. the silent-degradation class of bugs in the cleanup handoff).
            sys.stderr.write('[stage3] legacy vtable resolver failed (%s): %r\n' % (cls, _e))
        return None
    code = _vtable_re.sub(lambda m: _try_resolve_vtable(m) or m.group(0), code)

    # Pattern: ((void (callconv *)(Type))obj->__vftable)(args) — cast style, no * deref
    _vtable_re3 = re.compile(
        r'\(\(\s*void\s+'
        r'\(\s*(?:__thiscall|__stdcall|\s*)\s*\*'
        r'\s*\)'
        r'\s*\(\s*(\w+)\s*\*'
        r'[^)]*\)\s*\)'
        r'\s*(\w+(?:\s*->\s*\w+)*)\s*->\s*'
        r'__vftable\)'
        r'\s*\((.*?)\)\s*;\s*')
    def _try_resolve_vtable3(m):
        cls, obj, args = m.group(1), m.group(2), m.group(3)
        slot = 0
        _indent = m.group(0)[:len(m.group(0)) - len(m.group(0).lstrip())]
        try:
            _slots = store.struct_vtables.get(cls, {})
            if slot in _slots:
                _method = _slots[slot]
                _args = [a.strip() for a in args.split(',')]
                _args = [a for a in _args if a.replace('&', '').strip() != obj]
                return '%s->%s(%s);\n%s' % (obj, _method, ', '.join(_args), _indent)
        except (AttributeError, KeyError, TypeError, IndexError, ValueError) as _e:
            # t7: was a bare `except: pass` (three legacy resolvers).  They only
            # read `store.struct_vtables`; unexpected shapes must not be swallowed
            # (cf. the silent-degradation class of bugs in the cleanup handoff).
            sys.stderr.write('[stage3] legacy vtable resolver failed (%s): %r\n' % (cls, _e))
        return None
    code = _vtable_re3.sub(lambda m: _try_resolve_vtable3(m) or m.group(0), code)

    _vtable_re2 = re.compile(
        r'\s*(?:\w+\s*=\s*)?'
        r'\(\s*\(\s*(\w+)\s+'
        r'\(\s*(?:__thiscall|__stdcall|\s*)\s*\*\s*\)'
        r'\s*\(\s*(\w+)\s*\*'
        r'[^)]*\)\s*\)'
        r'\s*(?:\(\s*\*\s*(\w+)\)|(\w+(?:\s*->\s*\w+)*))\s*->\s*__vftable\s*\)'
        r'\s*\(((?:[^)]|\([^)]*\))*)\)\s*;\s*')
    def _try_resolve_vtable2(m):
        _ret = m.group(1)
        cls = m.group(2)
        obj = m.group(3) if m.group(3) else m.group(4)
        args = m.group(5)
        _obj_expr = '(*%s)' % obj if m.group(3) else obj
        try:
            _slots = store.struct_vtables.get(cls, {})
            if 0 in _slots:
                _method = _slots[0]
                _args = [a.strip() for a in args.split(',')]
                _args = [a for a in _args if a.replace('&', '').strip() != obj]
                return '%s->%s(%s);\n' % (_obj_expr, _method, ', '.join(_args))
        except (AttributeError, KeyError, TypeError, IndexError, ValueError) as _e:
            # t7: was a bare `except: pass` (third legacy resolver) — see above.
            sys.stderr.write('[stage3] legacy vtable resolver failed (%s): %r\n' % (cls, _e))
        return None
    code = _vtable_re2.sub(lambda m: _try_resolve_vtable2(m) or m.group(0), code)

    # Generic OOP substitution: obj->__vftable->Method(obj, ...) → obj->Method(...)
    # Pattern 1: this->member->__vftable->Method(this->member, extra_args) → this->member->Method(extra_args)
    code = re.sub(
        r'\(\(\s*[\w\s]+(?:\s*\*)*\s*'               # ((type... (*
        r'\(\s*(?:__thiscall\s*)?\s*\*\s*\)'          # (__thiscall**)
        r'\s*\([^)]*\)\s*\)\s*'                       # )(type_params))
        r'(\w+(?:\s*->\s*\w+)*)\s*->\s*'              # this->member ->  (capture full chain)
        r'__vftable\s*->\s*(\w+)\)'                   # __vftable->Method)
        r'\s*\(\s*\1\s*(?:,\s*)?'                     # (same_expr, ...)
        r'([^)]*)\)\s*;',                             # extra_args);
        r'\1->\2(\3);',
        code
    )
    # Pattern 2: (*ptr)->__vftable->Method(*ptr, extra_args) → ptr->Method(extra_args)
    code = re.sub(
        r'\(\(\s*[\w\s]+(?:\s*\*)*\s*'               # ((type... (*
        r'\(\s*(?:__thiscall\s*)?\s*\*\s*\)'          # (__thiscall**)
        r'\s*\([^)]*\)\s*\)\s*'                       # )(type_params))
        r'\(\s*\*\s*(\w+)\)\s*->\s*'                  # (*ptr)->
        r'__vftable\s*->\s*(\w+)\)'                   # __vftable->Method)
        r'\s*\(\s*\*\s*\1\s*(?:,\s*)?'                # (*ptr, ...)
        r'([^)]*)\)\s*;',                             # extra_args);
        r'\1->\2(\3);',
        code
    )


    # Cleanup: remove redundant self-arg from already-converted calls
    # obj->Method(obj, ...) → obj->Method(...)  and  obj->Method(*obj, ...) → obj->Method(...)
    code = re.sub(
        r'(?<!\w)(\w+(?:\s*->\s*\w+)*)->(\w+)\(\s*\1\s*(?:,\s*)?',
        r'\1->\2(',
        code
    )
    code = re.sub(
        r'(\w+(?:\s*->\s*\w+)*)->(\w+)\(\s*\*\s*\1\s*(?:,\s*)?',
        r'\1->\2(',
        code
    )

    # ------------------------------------------------------------------
    # __vftable handling (t7 rewrite)
    # ------------------------------------------------------------------
    # Old behaviour: every line containing `__vftable` was commented out
    # (`// [VFTABLE]`), first by a bracket-depth block scanner and then by a
    # `^...__vftable[^;]*;.*$` regex.  Measured on the 2026-09-15 tree that
    # destroyed 1935 lines, of which only a couple of dozen are genuine
    # compiler-managed vptr setup; the rest are real data accesses, real
    # control-flow, real dispatch and real conversions (see
    # data/status/_cleanup_fix_vftable_comment.md).
    #
    # New behaviour, two passes:
    #   1. `_comment_vptr_stores()` — the ONLY path allowed to comment, and
    #      only for statements carrying positive evidence that the store
    #      target is a vtable pointer (vptr copy / vtable symbol / a load
    #      through a vtable-typed pointer).  A store the compiler regenerates
    #      from the class definition must not appear in the source.
    #   2. `_fold_vftable_mask()` — everything else is restored in a form that
    #      compiles: the `__vftable` member is not emitted by the header
    #      generator (`_variants` are dropped; only `data_members` are
    #      written), so the raw text could never compile.  The vfptr sits at
    #      offset 0 of its own object in every exported struct, so the access
    #      is rewritten to the byte-exact offset-0 equivalent.
    code = _comment_vptr_stores(code)
    code = _fold_vftable_mask(code)

    # --- Reference parameter adaptation (gbengine &param fix) ---
    code = _fix_ref_params(code)

    # --- AST-based structural detection ---
    code = _ast_cleanup(code, ctx)

    # --- Post-AST simple fixes ---

    # Hex-Rays _OWORD struct load: (RECT)*(_OWORD*)addr → *(RECT*)(addr)
    code = re.sub(r'\((\w+)\)\s*\*\(\(_OWORD\s*\*\)([^)]+)\)', r'*(\1 *)(\2)', code)

    code = re.sub(r'((?:LODWORD|HIDWORD)\s*\([^)]+\))\s*=\s*(&\w+)', r'\1 = (unsigned long)\2', code)

    def _fix_mfp(m):
        cm = m.group(1)
        a = re.search(r'_([0-9A-Fa-f]{5,})$', cm.split('::')[-1])
        return ('0x%s' % a.group(1)) if a else ('0 /* TODO: (int)%s */' % cm)
    code = re.sub(r'\(int\)\s*(\w+::(?:~?\w+))\b(?!\s*\()', _fix_mfp, code)

    # COM C-mode vtbl calls → C++ direct calls: obj->lpVtbl->Method(obj, args) → obj->Method(args)
    code = re.sub(
        r'([\w.]+(?:->[\w.]+)*)->lpVtbl->(\w+)\(\1(?:,\s*)?',
        lambda m: '%s->%s(' % (m.group(1), m.group(2)),
        code
    )
    # Handle (*ptr)->lpVtbl->Method(*ptr, args) pattern
    def _fix_deref_com(m):
        obj = m.group(1)  # e.g. (*p_m_lpDIDMouse)
        method = m.group(2)
        inner = obj[2:-1]  # strip (* and ) → p_m_lpDIDMouse
        return '%s->%s(' % (obj, method)
    code = re.sub(
        r'(\(\*(\w+)\))->lpVtbl->(\w+)\(\*?\2(?:,\s*)?',
        lambda m: '(*%s)->%s(' % (m.group(2), m.group(3)),
        code
    )

    # Backtick removal
    code = _remove_backtick_calls(code)

    # Comment out __asm lines with IDA-style operands (MSVC doesn't support [esp+XXh+var] syntax)
    lines = code.split('\n')
    for i, line in enumerate(lines):
        stripped = line.strip()
        if stripped.startswith('__asm') and ('[' in stripped and '+' in stripped and 'h' in stripped.lower()):
            lines[i] = line.replace(stripped, '// ' + stripped)
    code = '\n'.join(lines)

    # Replace IDA code labels (loc_XXXXXX, qword_XXXXXX) with (void*)0
    # Handle both &loc_XXX (address-of) and bare loc_XXX references
    import re as _re_loc
    code = _re_loc.sub(r'&loc_[0-9A-Fa-f]+\b', '((void*)0)', code)
    code = _re_loc.sub(r'\bloc_[0-9A-Fa-f]+\b', '((void*)0)', code)
    code = _re_loc.sub(r'&qword_[0-9A-Fa-f]+\b', '((void*)0)', code)
    code = _re_loc.sub(r'\bqword_[0-9A-Fa-f]+\b', '((void*)0)', code)

    # Replace IDA CRT internal function calls (_E68, _E158 etc) — only in call context
    code = _re_loc.sub(r'\b_E\d+(?=\s*\()', '((void(*)(void))0)', code)
    # Replace IDA label _L references
    code = _re_loc.sub(r'\b_L\d+\b', '((void*)0)', code)
    # Replace __SPAIR64__ IDA macro with equivalent
    code = code.replace('__SPAIR64__', '__PAIR64__')

    # Comment out Hex-Rays "->0" / "->0 + N" vtable dispatch (invalid C syntax).
    # Root cause: structs lack vfptr member at offset 0 in exported data_members.
    # Pattern: "->0)" (slot 0) or "->0 + N)" (slot N) — both are vtable dispatches.
    # Cannot fix at annotation layer (gbengine structs, no IDA available for re-export).
    # Information IS recoverable here: the vtable dispatch pattern is unambiguous.
    lines = code.split('\n')
    out_lines = []
    commenting = False
    for line in lines:
        _needs_comment = (not commenting and '//' not in line
                         and re.search(r'->0\s*[)+\s]', line))
        if not commenting and _needs_comment:
            commenting = True
            out_lines.append(line[:len(line) - len(line.lstrip())] + '// [VTBL_DISPATCH] ' + line.strip())
            if line.rstrip().endswith(';'):
                commenting = False
        elif commenting:
            out_lines.append(line[:len(line) - len(line.lstrip())] + '// [VTBL_DISPATCH]   ' + line.strip())
            if line.rstrip().endswith(';'):
                commenting = False
        else:
            out_lines.append(line)
    code = '\n'.join(out_lines)

    return code


# ============================================================
# Reference parameter adaptation (gbengine DLL uses references,
# Hex-Rays outputs pointer-style &var calls)
# ============================================================

# Functions whose parameters are references (non-const &) in gbengine.
# Key = method name, Value = set of 0-based param indices (excluding this).
_GB_REF_PARAM_FUNCS = {
    'Translate': {0},
    'Rotate': {1},  # Rotate(float, gbVec3D&) - param 1 is ref
    'Scale': {0},
    'LeftTranslate': {0},
    'RightTranslate': {0},
    'MakeMatrix': {0, 1, 2},
    'IntersectPlane': {0, 1},
    'IsColAABB': {0},
    'IsColOBB': {0},
    'IsColOBB_H': {0},
    'IsColPoint': {0},
    'IsColQuad': {0, 1, 2},
    'IsColSphere': {0},
    'IsColTriangle': {0, 1, 2, 3},
    'GetAABBox': {0},
    'GetSphere': {0},
    'GetCollideOBB': {0},
    'SetPosition': {0},
    'GetPosition': {0},
    'SetVelocity': {0},
    'SetOrientation': {0},
    'SetListenerPosition': {0},
    'SetListenerOrientation': {0, 1},
    'GetListenerPosition': {0},
    'PushMessage': {0},
    'PopMessage': {0},
    'GetViewport': {0},
    'GetViewSizeOnNearPlane': {0, 1},
    'GetViewPort': {0, 1, 2, 3},
}


def _fix_ref_params(code):
    """Strip '&' from arguments to functions that take reference params.
    
    Hex-Rays outputs: obj->Translate(&vec);
    Correct C++:      obj->Translate(vec);
    """
    import re as _re
    
    for func_name, ref_indices in _GB_REF_PARAM_FUNCS.items():
        # Match: ->FuncName( or ::FuncName( followed by arguments
        # Pattern finds the function call and we process arguments
        pattern = r'(?:->|::|\.)' + _re.escape(func_name) + r'\s*\('
        
        pos = 0
        result = []
        while True:
            m = _re.search(pattern, code[pos:])
            if not m:
                result.append(code[pos:])
                break
            
            # Add everything up to the opening paren
            call_start = pos + m.end()
            result.append(code[pos:call_start])
            
            # Parse arguments (track parenthesis depth)
            depth = 1
            arg_start = call_start
            arg_idx = 0
            i = call_start
            while i < len(code) and depth > 0:
                ch = code[i]
                if ch == '(':
                    depth += 1
                elif ch == ')':
                    depth -= 1
                    if depth == 0:
                        # Process last argument
                        arg = code[arg_start:i]
                        if arg_idx in ref_indices:
                            arg = arg.lstrip()
                            if arg.startswith('&') and not arg.startswith('&&'):
                                arg = arg[1:]
                        result.append(arg)
                        result.append(')')
                        break
                elif ch == ',' and depth == 1:
                    # Process this argument
                    arg = code[arg_start:i]
                    if arg_idx in ref_indices:
                        arg = arg.lstrip()
                        if arg.startswith('&') and not arg.startswith('&&'):
                            arg = arg[1:]
                    result.append(arg)
                    result.append(', ')
                    arg_idx += 1
                    arg_start = i + 1
                i += 1
            
            pos = i + 1
        
        code = ''.join(result)
    
    return code
