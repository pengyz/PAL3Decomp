"""Stage 3: Post-OOP cleanup using tree-sitter AST.

All structural detection is done through AST node types.
No regex is used for pattern recognition — only for simple text substitution
where no structural understanding is needed (e.g., __thiscall removal).
"""
import re
import struct as _struct

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
    """Detect: this->__vftable = expr (assignment to vftable pointer)."""
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
    except Exception:
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
        elif action == 'insert':
            out.append(data)
        elif action == 'comment_vft':
            out.append(indent + '// [IDA_VFTABLE] ' + data)
        elif action == 'comment_ctor':
            out.append(indent + '// [AUTO-COMMENTED] ' + data)
        elif action == 'return_expr':
            out.append(indent + 'return %s; // ctor auto-called' % data)
        elif action == 'return_this':
            out.append(indent + 'return this; // [ctor replaced]')
        else:
            out.append(line)

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
        # Base class ctor call: this->BaseClassName() → implicit (compiler auto-calls)
        code = re.sub(r'^\s*this->\w+\(\);\s*$', '', code, flags=re.MULTILINE)

    # Try to resolve vtable dispatch calls to direct method calls before commenting out.
    # Pattern: (*(void (callconv **)(Type*))(obj->__vftable + N))(args);
    # Matches optional __thiscall/__stdcall or bare (**) after void.
    _vtable_re = re.compile(
        r'\(\s*\*\s*\(\s*\(?\s*void\s+'
        r'\(\s*(?:__thiscall|__stdcall|\s*)\s*'
        r'\*\s*\*\s*\)'
        r'\s*\(\s*(\w+)\s*\*'
        r'[^)]*\)\s*\)'
        r'\s*\(?\s*(\w+(?:\s*->\s*\w+)*)\s*->\s*__vftable\s*\+\s*(\d+)\s*\)'
        r'\s*\)\s*\((.*?)\)\s*;\s*')
    def _try_resolve_vtable(m):
        cls, obj, off, args = m.group(1), m.group(2), int(m.group(3)), m.group(4)
        slot = off
        _indent = m.group(0)[:len(m.group(0)) - len(m.group(0).lstrip())]
        try:
            _slots = store.struct_vtables.get(cls, {})
            if slot in _slots:
                _method = _slots[slot]
                _args = [a.strip() for a in args.split(',')]
                _args = [a for a in _args if a.replace('&', '').strip() != obj]
                return '%s->%s(%s);\n%s' % (obj, _method, ', '.join(_args), _indent)
        except: pass
        return None
    code = _vtable_re.sub(lambda m: _try_resolve_vtable(m) or m.group(0), code)

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
        except: pass
        return None
    code = _vtable_re2.sub(lambda m: _try_resolve_vtable2(m) or m.group(0), code)

    # Generic OOP substitution: obj->__vftable->Method(obj, ...) → obj->Method(...)
    # Match: ((type(...))(callconv*)(params))obj->__vftable->Method)(obj, args)
    code = re.sub(
        r'\(\(\s*[\w\s]+(?:\s*\*)*\s*'               # ((type... (*
        r'\(\s*(?:__thiscall\s*)?\s*\*\s*\)'          # (__thiscall**)
        r'\s*\([^)]*\)\s*\)\s*'                       # )(type_params))
        r'(\w+)\s*->\s*'                              # obj ->
        r'__vftable\s*->\s*(\w+)\)',                  # __vftable->Method)
        r'\1->\2',
        code
    )
    code = re.sub(
        r'(\w+)->(\w+)\(\1\s*(?:,\s*)?',
        r'\1->\2(',
        code
    )

    # Comment out remaining __vftable refs (unresolved = no method name for that slot)
    lines_arr = code.split('\n')
    result_lines = []
    i = 0
    while i < len(lines_arr):
        line = lines_arr[i]
        if '__vftable' in line and '//' not in line:
            commented = ['// [VFTABLE] ' + line.lstrip()]
            depth = line.count('(') - line.count(')')
            has_semi = line.rstrip().endswith(';')
            i += 1
            while i < len(lines_arr) and not has_semi and depth > 0:
                cont_line = lines_arr[i]
                commented.append('// [VFTABLE]   ' + cont_line.lstrip())
                depth += cont_line.count('(') - cont_line.count(')')
                has_semi = cont_line.rstrip().endswith(';')
                i += 1
            result_lines.extend(commented)
        else:
            result_lines.append(line)
            i += 1
    code = '\n'.join(result_lines)

    # Comment out remaining __vftable refs
    code = re.sub(
        r'^([ \t]*(?!/[/*]).*__vftable[^;]*;.*)$',
        r'// [VFTABLE] \1',
        code, flags=re.MULTILINE)

    # Comment out lines with IDA type misidentifications (FLIRT/TIL false matches)
    _IDA_MISID_PATTERNS = (
        'Concurrency', 'details::VirtualProcessor', 'NtTib', 'ExceptionList',
        'std::_Xlen', 'std::_Xran',
    )
    code = re.sub(
        r'^([ \t]*.*(?:' + '|'.join(re.escape(p) for p in _IDA_MISID_PATTERNS) + r').*)$',
        r'// [IDA_MISID] \1',
        code, flags=re.MULTILINE)

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
