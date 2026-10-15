"""Stage 3: Post-OOP cleanup using tree-sitter AST.

All structural detection is done through AST node types.
No regex is used for pattern recognition — only for simple text substitution
where no structural understanding is needed (e.g., __thiscall removal).
"""
import hashlib as _hashlib
import json
import os
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


# ===== S1（2026-09-21）：owner 的**唯一表示**与**唯一渲染器** =====
# 目的（见 docs/specs/2026-09-21-vtable-resolver-refactor-design.md §3/§4 的 S1 ✓）：
#   把散落在 9 处正则里的"owner 文本"收拢为**一个类型**，并使**文本只在 render_owner 里产生** ✓
# **S1 的硬要求：零字节变化** ✗ —— 因此本阶段的 render_owner **默认返回 raw**
#   （即**复刻旧的截断行为**，包括它的 bug ✗）；结构化渲染留到 S2 显式启用 ✓
#   （这正是 codex 复核的提醒：S1 若"顺手改对"就会立刻打破零字节铁律 ✓）
class OwnerPath(object):
    """owner 链：(raw 原文, accessors 结构化访问器列表)。

    raw      —— 旧正则实际匹配到的文本（S1 用它 ⇒ 输出逐字节不变 ✓）
    accessors—— [(name, subscript_or_None), ...]，为 S2 的语义修正准备 ✓
    """
    __slots__ = ('raw', 'accessors')

    def __init__(self, raw, accessors=None):
        self.raw = raw
        self.accessors = accessors if accessors is not None else []

    @classmethod
    def from_match(cls, text):
        """从旧正则的 group 文本构造（保持 raw 不变 ✓）"""
        raw = (text or '').strip()
        return cls(raw, _parse_accessors(raw))

    def render(self):
        """**唯一**产生 owner 文本之处 ✓ —— S1：返回 raw（逐字节不变 ✓）"""
        return self.raw

    def __str__(self):
        return self.render()


def _parse_accessors(raw):
    """把 owner 文本解析成访问器列表（**只读、不改写** ✓；供 S2 使用）"""
    out, i, n = [], 0, len(raw)
    cur = ''
    while i < n:
        ch = raw[i]
        if ch in '.>' or (i + 1 < n and raw[i:i+2] == '->'):
            name = (cur or '').strip()
            if name:
                out.append((name, None))
            cur = ''
            i += 2 if raw[i:i+2] == '->' else 1
            continue
        if ch == '[':
            j = raw.find(']', i)
            sub = raw[i+1:j] if j > 0 else ''
            name = (cur or '').strip()
            out.append((name, sub) if name else ('', sub))
            cur = ''
            i = (j + 1) if j > 0 else i + 1
            continue
        cur += ch
        i += 1
    name = cur.strip()
    if name:
        out.append((name, None))
    return out


def render_owner(path):
    """模块级唯一渲染入口 ✓（其余各处一律通过它取文本 ✓）"""
    if isinstance(path, OwnerPath):
        return path.render()
    return str(path)


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
                        # [T20] 标量删除析构（dtor 调用 + operator delete + return
                        # 三形）内的显式析构调用是**真调用**，非 Hex-Rays 噪声：
                        # `~` 形且函数体含 operator delete ⇒ 保留（A 级：
                        # CCBSkillWindow::Destroy_12@0x0051BBE0 体含 dtor call +
                        # operator delete 两条真调用，误删即字节腐蚀）。
                        if (method.startswith('~')
                                and (any('operator delete' in l for l in lines)
                                     # [T87] thunk 体内的 dtor 调用是**真调用**
                                     # （ctor→dtor COMDAT 别名的目标）——
                                     # `// attributes: thunk` 注记体同样保留。
                                     or any('attributes: thunk' in l for l in lines))):
                            return                # 真调用：整行不动（跳过全部清理形）
                        # Standalone at line start with ((Type*) pattern → delete
                        elif child.parent == node or (child.parent and child.parent.type == 'cast_expression'):
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
        # P1(b) 2026-09-19（长线计划）：**裸链没有 cast ⇒ ret/params 为 None ⇒ 第 591 行的
        # stub 兜底被跳过 ⇒ 调用文本被原样保留（`__vftable` 残留 → C2227）**。
        # 通用补救：用注解里该方法的一致签名补出 ret/params（不针对任何具体方法名）。
        # `store.method_sigs` 的键是 "Class::Method"，值是 decomp 签名如
        # `int __thiscall(int nVal, int nMsg, int wParam)`。
        _synthetic_self = False
        if ret is None:
            _sigs = {s for k, s in store.method_sigs.items()
                     if k.endswith('::' + mn.group(2))}
            if len(_sigs) == 1:                      # 所有声明者签名一致才敢用
                _m2 = re.match(r'^\s*(.*?)\s*\((.*)\)\s*$', _sigs.pop())
                if _m2:
                    _r = re.sub(r'\b(?:__thiscall|__cdecl|__stdcall|__fastcall)\b', '',
                                _m2.group(1)).strip()
                    ret = _r or 'void'
                    _plist = _m2.group(2).strip()
                    # stub 的形参表要把**对象指针**放首位（现有 `_vtbl_stub_names` 的约定）
                    params = 'void *' + (', ' + _plist if _plist and _plist != 'void' else '')
                    _synthetic_self = True
        return {'obj': OwnerPath.from_match(mn.group(1)).render(), 'method': mn.group(2), 'offset': None,
                'cls_hint': cls_hint, 'ret': ret, 'params': params,
                'synthetic_self': _synthetic_self,
                'owner': OwnerPath.from_match(mn.group(1))}
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


# ============================================================
# 虚调用转换：三形态识别（Task 7）
# 规格：docs/superpowers/specs/2026-09-25-vtable-mapping-design.md §4.3
# ============================================================
# 目标形态恒为直接虚调用 `obj->MethodName(args)`。三形态（都在本解码分支内处理）：
#   1 inline            (*(R (__thiscall **)(Cls *, ...))(*(T *)OBJ + N))(OBJ, args)
#   2 局部 vftable 变量  v5 = *(T *)OBJ; … (*(R …)(v5 + N))(OBJ, args)
#   3 裸 vptr 读         (*(R …)(*(void **)(OBJ)))(OBJ)          —— 偏移 0
#
# **字节偏移语义（二进制实证，勿再引入 `//4` 之外的猜测）**：
#   `*(_DWORD *)X + 8` 里的 8 是**字节偏移**，槽下标 = 8/4 = 2。
#   证据（original/PAL3.exe.asm）：C2DSpark::C2DSpark @0x4D5AB0
#       mov ecx, dword_BFDA60 ; mov edx,[ecx] ; call dword ptr [edx+8]
#   ⇔ decomp `(*(int (__thiscall **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, aTga)`
#   ⇒ 槽2 = gbGfxManager::NewTexture(char const *)（实参 aTga 与之相符）。
#   对照：AStarPathFinder::TryExpand @0x4012A0 `call dword ptr [eax+4]` ⇔ `*(_DWORD *)this + 4`
#   （槽1 = IsInBounds，实参 (this,nTileX,nTileY) 相符）。
#   （`obj->__vftable + N` 是另一族：那里 N 是**槽下标**（vtable 结构体指针运算），
#     仍由 `_decode_vtbl_call` / `_resolve_vtbl_method` 处理，本段不改其语义。）
#
# **名称解析链（不用 mangling）**：
#   类名(cast 首参) → 注解 `vtables[0].addr` → IDB `vtbl_<ADDR>.data_members`
#   → 注解 `methods[槽地址].name`（缺省回落 IDB `data_members[i].name`）
#   `vtables[]` 是唯一的多态声明点（无 ⇒ 未声明为多态 ⇒ 不转换，记账）。
#   `::` 限定一律剥掉 ⇒ **绝不发射 `obj->Base::Method()`**（限定调用抑制虚派发 ⇒ 字节必不匹配）。
#
# **失败输出契约**：识别为虚调用却**无法转换**时 ⇒ **原文本逐字保留**（绝不伪造
#   `_tail_00N` / 伪成员这类裸偏移形态），并记账到 `data/status/vtable_transform_failures.md`。
#   既有 `__vftable` 路径的 stub 语义（`pal3_vtbl_unk_*`）**逐字不变**（本段是**并列**分支，
#   不进入 legacy 分支的判定）。

# vptr 读的 cast 目标类型白名单（只认标量/void 指针；带括号的嵌套 cast 不属于三形态）
_VTBL_VPTR_TYPES = frozenset((
    '_DWORD', 'void', 'int', 'char', '_BYTE', '_WORD',
    'unsigned int', 'unsigned __int8', 'unsigned __int16', 'unsigned',
))

# 非类 hint（cast 首参不是类，而是标量/typedef）——单独归因，便于台账分流
_VTBL_NON_CLASS_HINTS = frozenset((
    'int', 'char', '_DWORD', '_BYTE', '_WORD', 'void', 'float', 'double',
    'LONG', 'DWORD', 'unsigned int', 'unsigned __int8', 'unsigned __int16',
    'unsigned', 'bool', 'short', 'long', 'size_t', 'BOOL',
))

# IDB/注解里的"占位名"：不是方法名，不能发射成 `obj->_tail_000()`
_VTBL_PLACEHOLDER_NAME = re.compile(
    r'^(?:_tail_\d+|sub_[0-9A-Fa-f]+|unknown\w*|nullsub\w*|nullsub_\d+|'
    r'j_[A-Za-z_]\w*|loc_[0-9A-Fa-f]+|unk_\w+|dword_[0-9A-Fa-f]+)$')
# 合法方法名：标识符（可带 ~ 前缀 = 析构）或 operator 形式
_VTBL_NAME_OK = re.compile(r'^(?:~?[A-Za-z_]\w*|operator\s*\S+)$')

_VTBL_FAILURE_LOG_DEFAULT = ('data', 'status', 'vtable_transform_failures.md')
_VTBL_FAILURE_HEADER = (
    '# 虚调用转换失败台账（Task 7）\n'
    '\n'
    '生成物 —— 由 `pipeline/gen/stages/stage3_cleanup.py` 在**识别为虚调用但无法转换**时追加。\n'
    '规格：`docs/superpowers/specs/2026-09-25-vtable-mapping-design.md` §4.3。\n'
    '\n'
    '契约：失败时**原文逐字保留**（不降级为裸偏移形态），并在此记账。每行一个\n'
    '`(方法, 形态, cls_hint, 字节偏移, 原因)` 唯一站点（幂等：重复运行不重复追加）。\n'
    '\n'
    '| 位置 | 形态 | cls_hint(cast 首参) | 字节偏移 | 原因 | 原始调用文本 |\n'
    '|---|---|---|---|---|---|\n'
)
# 行格式必须与上面的表头列一一对应（`_load_failure_keys` 靠它做跨进程幂等）
_VTBL_FAILURE_ROW = '| `%s::%s` | %s | `%s` | %d | %s | `%s` |\n'

_VTBL_INDEX = None              # 懒加载的解析链索引（测试直接注入）
_VTBL_FAILURE_WRITTEN = set()   # 已写入的 key（含从既有文件恢复的）
_VTBL_FAILURE_LOADED = set()    # 已做过"既有行恢复"的台账路径

_VTBL_FN_CAST = re.compile(
    r'^(?P<ret>.*?)\(\s*(?:__thiscall|__stdcall|__cdecl|__fastcall)?\s*'
    r'(?P<stars>\*+)\s*\)\s*\((?P<params>.*)\)\s*$', re.S)
# 评审 R=1 M1：前缀收紧为**单** `*`。原 `^\*+` 会把 `**(int **)this`（双解引用：
# `this` → vptr → slot0 指针，两次 load）误读成"一次 vptr 读" ⇒ 发射 `this->M()`
# 会**丢掉一次 load**（语义/字节必不同）。实测该形态在当前语料有 30 个文本命中
# （`**( _DWORD **)this + N` 等），其中 12 个原本被误记为 `self_arg_mismatch`；
# 收紧后**全语料输出 0 字节变化**（3598 文件逐文件比对：changed=0），只让台账
# 少 12 条误报、露出 2 条原本被幂等键压掉的真行 ⇒ 零风险 + 假阳性收口。
# 说明：`**(_DWORD **)&this->m_X` 这类 `&` 形态在运行时其实只有一次 load
# （`&` 不读内存），但当前解码器把 obj 写成 `&this->m_X`（未剥 `&`）⇒ 本就不能正确
# 转换（首参比对必失配）；收紧后它们只是从"误识别"变为"未识别"，无转换损失。
_VTBL_VPTR_READ = re.compile(
    r'^\*\s*\(\s*(?P<vt>[A-Za-z_][\w ]*?)\s*\*+\s*\)\s*(?P<obj>.+)$', re.S)
_VTBL_TAIL_MEMBER = re.compile(r'^(?P<obj>.+?)\s*->\s*_tail_\d+$', re.S)
_VTBL_ROW = re.compile(
    r'^\|\s*`(?P<loc>[^`]*)`\s*\|\s*(?P<form>\S+)\s*\|\s*`(?P<hint>[^`]*)`\s*\|'
    r'\s*(?P<off>\d+)\s*\|\s*(?P<reason>\w+)\s*\|')


def _vtbl_method_name(name):
    """方法名归一：剥 `::` 限定（禁止 `obj->Base::Method()`）+ 拒绝占位名。

    返回 '' 表示这个名字不可用（由调用方决定回落或记账）。
    """
    n = str(name or '').strip()
    if not n:
        return ''
    n = n.split('::')[-1].strip()          # 只管剥限定，不做任何拼写猜测
    if not n or _VTBL_PLACEHOLDER_NAME.match(n) or not _VTBL_NAME_OK.match(n):
        return ''
    return n


def _load_vtbl_index():
    """建名称解析链的三张表。

    返回 {'class_addr': {cls: addr}, 'by_addr': {addr: {slot: name}},
          'idb_members': {addr: [name（按槽下标，缺槽为 '')]}}。

    数据源（都是**只读**）：
      * `data/annotations/structs/*.json` 的 `vtables[0].addr` / `slots[i].addr` / `methods[addr].name`
        —— 已声明的多态类与其槽位方法名；
      * `asm/pal3/ida_structs.json` 的 `vtbl_<ADDR>` —— IDB 侧的 vtable 结构（槽存在性的二进制侧确认）。
    **不使用 mangling**。
    """
    root = os.path.dirname(os.path.dirname(os.path.dirname(
        os.path.dirname(os.path.abspath(__file__)))))
    class_addr, by_addr = {}, {}
    class_slot_addrs, class_decl = {}, {}
    # 单一读点：`annotation_view`（CLAUDE.md 红线：「新增注解直读必须走 annotation_view」）。
    # 评审 R=1 I-2：原实现 `os.listdir` + `json.load(data/annotations/structs/*.json)`
    # 绕过读点。替换为 `structs_dir()` + `iter_structs()`，语义逐字等价：
    #   * `iter_struct_files` = `sorted(glob('*.json'))`（原 `sorted(listdir)` + 后缀过滤，同序）；
    #   * `iter_structs` 跳过坏 JSON/非 dict（原 `except (OSError, ValueError): continue`
    #     + `isinstance(ann, dict)`；宽捕获仍只是"坏文件即跳过"）；
    #   * 路径来源同为 `<root>/data/annotations/structs`（`structs_dir()` 无 store 时逐字如此）。
    # 等价性有全量实测：替换前后 `_load_vtbl_index()` 的索引逐字段相同 + 27 条原测试全绿。
    try:
        import annotation_view as _av
    except ImportError:                             # pragma: no cover
        from pipeline.gen import annotation_view as _av
    structs_dir = _av.structs_dir()
    if os.path.isdir(structs_dir):
        for path, ann in _av.iter_structs(structs_dir):
            fn = os.path.basename(path)
            if not isinstance(ann, dict):
                continue
            vtables = ann.get('vtables') or []
            if not vtables or not isinstance(vtables[0], dict):
                continue
            cls = ann.get('name') or fn[:-5]
            addr = str(vtables[0].get('addr') or '').lower()
            if not addr:
                continue
            methods = ann.get('methods') or {}
            slot_map = {}
            slot_addrs = {}
            for i, slot in enumerate(vtables[0].get('slots') or []):
                if not isinstance(slot, dict):
                    continue
                saddr = str(slot.get('addr') or '').lower()
                if saddr:
                    slot_addrs[i] = saddr
                entry = methods.get(slot.get('addr', '')) or {}
                name = _vtbl_method_name(entry.get('name', ''))
                if name:
                    slot_map[i] = name
            class_addr[cls] = addr
            by_addr.setdefault(addr, {}).update(slot_map)
            class_slot_addrs[cls] = slot_addrs
            # 类的**声明名表**（name → 声明地址集合）——头文件一致性的护栏依据。
            # 头文件的名字来源（emit_headers.collect_methods）：
            #   ① decomp JSON 的 `Cls::Method`（**取不到**：不做 3598 文件扫描，故本护栏宁可保守）
            #   ② IDB 类结构的 methods    ③ 注解 known_methods（人工策展，如 UIWnd::OnMessage）
            #   ④ 注解 methods
            decl = {}
            for maddr, entry in methods.items():
                if isinstance(entry, dict):
                    nm = _vtbl_method_name(entry.get('name', ''))
                    if nm:
                        decl.setdefault(nm, set()).add(str(maddr).lower())
            for entry in (ann.get('known_methods') or {}).values():
                if isinstance(entry, dict):
                    nm = _vtbl_method_name(entry.get('name', ''))
                    if nm and entry.get('address'):
                        decl.setdefault(nm, set()).add(str(entry['address']).lower())
            class_decl[cls] = decl
    idb_members = {}
    ida_path = os.path.join(root, 'asm', 'pal3', 'ida_structs.json')
    if os.path.exists(ida_path):
        try:
            with open(ida_path, encoding='utf-8') as fh:
                ida = json.load(fh)
        except (OSError, ValueError):
            ida = {}
        if isinstance(ida, dict):
            for key, ent in ida.items():
                if not isinstance(key, str) or not key.lower().startswith('vtbl_'):
                    continue
                if not isinstance(ent, dict):
                    continue
                members = ent.get('data_members') or []
                slots = []
                for dm in members:
                    if not isinstance(dm, dict):
                        continue
                    try:
                        idx = int(dm.get('offset', 0)) // 4
                    except (TypeError, ValueError):
                        continue
                    if idx < 0 or idx > 4096:
                        continue
                    while len(slots) <= idx:
                        slots.append('')
                    slots[idx] = str(dm.get('name') or '')
                if slots:
                    idb_members['0x' + key[5:].lower()] = slots
            # 头文件名字来源 ②：IDB **类结构**的 methods（collect_methods 的 supplement）
            for cname, ent in ida.items():
                if cname not in class_decl or not isinstance(ent, dict):
                    continue
                for maddr, entry in (ent.get('methods') or {}).items():
                    if not isinstance(entry, dict):
                        continue
                    nm = _vtbl_method_name(entry.get('name', ''))
                    if nm:
                        class_decl[cname].setdefault(nm, set()).add(str(maddr).lower())
    return {'class_addr': class_addr, 'by_addr': by_addr,
            'idb_members': idb_members,
            'class_slot_addrs': class_slot_addrs, 'class_decl': class_decl}


def _vtbl_index():
    """懒加载索引（测试通过 `_VTBL_INDEX` 注入夹具）。"""
    global _VTBL_INDEX
    if _VTBL_INDEX is None:
        _VTBL_INDEX = _load_vtbl_index()
    return _VTBL_INDEX


def _resolve_vtbl_name_chain(cls_hint, byte_off):
    """名称解析链 → (method_name, None) 或 (None, 原因)。

    链：类名(cast 首参) → 注解 vtables[0].addr → IDB `vtbl_<ADDR>.data_members`
        → 注解 methods[槽地址].name（缺省回落 IDB data_members[i].name）

    **头文件一致性护栏**（实测必需，2026-09-25）：
    头文件只为"该类声明过的方法名"发 virtual（占位槽发 `slot_<i>`）。
    真实反例：`UIWnd` 槽3（0x00442420）在 IDB `vtbl_0056AE2C` 里叫 `Destroy`，
    而该类的 `Destroy` **声明在 0x0043BBB0 且非 virtual**（`pal3/src/UI/UIWnd.h:45`），
    槽3 在头文件里是 `virtual void slot_3()` ⇒ 若发射 `p->Destroy(...)` 会绑定到
    **非虚**的另一个函数（直接调用 ⇒ 字节必不匹配）。故名字必须在本类**声明于该槽地址**。
    （已知保守处：decomp JSON 是头文件的头号名字来源，本索引不扫 3598 个 decomp 文件 ⇒
      个别"仅 decomp 声明"的名字会被记进台账而不是转换；宁可少转不可错转。）

    原因取值：no_class_hint / non_class_hint / no_vtables_declaration /
              no_idb_vtbl_struct / slot_out_of_range / no_method_name /
              no_slot_addr / name_declared_at_other_address /
              name_not_declared_for_class
    """
    if not cls_hint:
        return None, 'no_class_hint'
    if cls_hint in _VTBL_NON_CLASS_HINTS:
        return None, 'non_class_hint'
    idx = _vtbl_index()
    addr = idx.get('class_addr', {}).get(cls_hint)
    if not addr:
        return None, 'no_vtables_declaration'
    members = idx.get('idb_members', {}).get(addr)
    if members is None:
        return None, 'no_idb_vtbl_struct'
    try:
        slot = int(byte_off) // 4
    except (TypeError, ValueError):
        return None, 'no_method_name'
    if slot < 0 or slot >= len(members):
        return None, 'slot_out_of_range'
    name = _vtbl_method_name((idx.get('by_addr', {}).get(addr) or {}).get(slot, ''))
    if not name:
        name = _vtbl_method_name(members[slot])
    if not name:
        return None, 'no_method_name'
    # ★ 头文件一致性护栏
    # 评审 R=1 I-1：`slot_addr` 缺失时必须 **fail-closed**。原实现把 `slot_addr`
    # 当内层判定的**前置条件**（`if slot_addr and slot_addr not in decl_addrs`），
    # 于是槽地址缺失时 `if decl_addrs:` 的内层判定与 `elif slot_addr:` **双双跳过**
    # ⇒ 直接 `return name`（既没查声明地址，也没查"名字在本类是否声明过"）。
    # 实测暴露 10 个 (类, 槽)：`CCBPanelSlot` 槽3-6（Destroy/Create/_sdtor_call_dtor/
    # OnMessage，本类均无声明）、`PalScriptMgr` 槽0-5；例如
    # `_resolve_vtbl_name_chain('PalScriptMgr', 12)` 原样返回 `('Destroy_3', None)`
    # —— 头文件与注解都没有这个名字 ⇒ 一旦有调用点即发射凭空名 C2039；而
    # `PalScriptMgr` 的 IDB `vtbl_0056ABB8` 槽名与二进制槽序**已实证错位**
    # （IDB offset0='Destroy'，二进制 0x56ABB8 slot0=0x434D50，注解 Destroy=0x00432170）
    # ⇒ 走 IDB 回落的会是字节错误的虚调用。当前语料 0 次触发（907 次解析全量计量），
    # 故这是**潜伏**缺陷：触发即 Critical ⇒ 判据不完整时一律拒绝。
    slot_addr = (idx.get('class_slot_addrs', {}).get(cls_hint) or {}).get(slot, '')
    if not slot_addr:
        return None, 'no_slot_addr'
    decl = idx.get('class_decl', {}).get(cls_hint) or {}
    decl_addrs = decl.get(name)
    if decl_addrs:
        if slot_addr not in decl_addrs:
            return None, 'name_declared_at_other_address'
    else:
        # 该名字在本类没有任何声明 ⇒ 头文件不会发它（会发占位 `slot_<i>`，
        # 或在该地址声明了**别的**名字）⇒ 发射必然是 C2039
        return None, 'name_not_declared_for_class'
    return name, None


def _strip_outer_parens(text):
    """剥掉**完整包裹**在最外层的圆括号（`(a) + (b)` 这类不剥）。"""
    s = str(text or '').strip()
    while s.startswith('(') and s.endswith(')'):
        depth, complete = 0, True
        for i, ch in enumerate(s):
            if ch == '(':
                depth += 1
            elif ch == ')':
                depth -= 1
                if depth == 0 and i != len(s) - 1:
                    complete = False
                    break
        if not complete or depth != 0:
            break
        s = s[1:-1].strip()
    return s


def _split_expr_offset(text):
    """`EXPR + N` → (EXPR, N)；末尾无整数偏移时 N = None。"""
    s = str(text or '').strip()
    m = re.match(r'^(?P<head>.*?)\s*\+\s*(?P<off>0x[0-9A-Fa-f]+|\d+)\s*$', s, re.S)
    if not m:
        return s, None
    try:
        return m.group('head').strip(), int(m.group('off'), 0)
    except ValueError:
        return s, None


def _vptr_read_of(text, vptr_locals=None):
    """把 slot base 文本译成 (对象表达式, 字节偏移, 形态) 或 None。

    只接受**有显式 vptr 读**的形态：`*(T *)OBJ [± N]`、`*(T *)OBJ->_tail_NN`、
    以及（形态 2）已知持有 vptr 的局部变量 `V [± N]`。
    **裸标识符/成员链一律返回 None** —— 那些是函数指针成员或 COM 接口表
    （实测：`this->m_NewItem[7].fnHP`、`m_pData`），把它们当虚调用会改坏语义。
    """
    if not text:
        return None
    # 先剥完整外层括号：tree-sitter 的 slot base 常是 parenthesized_expression
    # （`(*(_DWORD *)this + 4)`），不剥则末尾 `+ N` 与 `)` 争位 ⇒ 解析不到偏移。
    head, off = _split_expr_offset(_strip_outer_parens(text))
    if not head:
        return None
    m = _VTBL_VPTR_READ.match(head)
    if m:
        if ' '.join(m.group('vt').split()) not in _VTBL_VPTR_TYPES:
            return None
        obj = _strip_outer_parens(m.group('obj'))
        tm = _VTBL_TAIL_MEMBER.match(obj)          # 形态 3 的输入侧：`OBJ->_tail_000` 即偏移 0 的 vptr
        if tm:
            obj = _strip_outer_parens(tm.group('obj'))
        if not obj:
            return None
        if off is None:
            return obj, 0, 'vptr_read'
        return obj, off, 'inline'
    if vptr_locals:
        bare = _strip_outer_parens(head)
        if bare in vptr_locals:
            return vptr_locals[bare], (off or 0), 'vftable_local'
    return None


def _fn_cast_of(call_node):
    """取「函数指针 cast」三元组 (cast_node, value_node, 解引用层数)。"""
    func = call_node.child_by_field_name('function')
    n, stars = func, 0
    while n is not None and n.type == 'parenthesized_expression':
        kids = n.named_children
        n = kids[0] if kids else None
    while n is not None and n.type == 'pointer_expression':
        stars += 1
        n = n.child_by_field_name('argument')
        while n is not None and n.type == 'parenthesized_expression':
            kids = n.named_children
            n = kids[0] if kids else None
    if n is None or n.type != 'cast_expression':
        return None, None, 0
    return n, n.child_by_field_name('value'), stars


def _decode_vptr_dispatch(call_node, vptr_locals=None):
    """三形态解码器（形态 1/2/3）。返回与 `_decode_vtbl_call` 兼容的 dict + dispatch/form。"""
    cast, value, stars = _fn_cast_of(call_node)
    if cast is None or value is None or stars < 1:
        return None
    type_node = cast.child_by_field_name('type')
    if type_node is None:
        return None
    ctype = ' '.join(type_node.text.decode('utf-8', 'replace').split())
    m = _VTBL_FN_CAST.match(ctype)
    if not m or len(m.group('stars')) < 2:         # 必须是指向成员函数指针的指针
        return None
    ret = ' '.join(m.group('ret').split()) or 'void'
    params = ' '.join(m.group('params').split())
    cls_hint = None
    first = params.split(',')[0].strip() if params else ''
    if first and first != 'void':
        cls_hint = re.sub(r'\*+\s*$', '', first).replace('const ', '').strip()
    base = _vptr_read_of(' '.join(value.text.decode('utf-8', 'replace').split()),
                         vptr_locals)
    if base is None:
        return None
    obj, off, form = base
    return {'obj': obj, 'method': None, 'offset': off, 'cls_hint': cls_hint,
            'ret': ret, 'params': params, 'dispatch': True, 'form': form}


def _collect_vptr_locals(tree):
    """形态 2：`V = <vptr 读>` ⇒ V 是局部 vftable 变量，值来源的对象即虚调用的对象。"""
    out = {}
    stack = [tree.root_node]
    while stack:
        n = stack.pop()
        if n.type == 'assignment_expression':
            left = n.child_by_field_name('left')
            right = n.child_by_field_name('right')
            if left is not None and right is not None and left.type == 'identifier':
                rhs = ' '.join(right.text.decode('utf-8', 'replace').split())
                src = _vptr_read_of(rhs)
                if src is None:                     # `V = OBJ->__vftable` 也是 vptr 源
                    vm = re.match(r'^(?P<obj>.+?)\s*->\s*__vftable$', rhs, re.S)
                    if vm:
                        src = (_strip_outer_parens(vm.group('obj')), 0, 'vptr_read')
                if src is not None and src[1] == 0 and src[0]:
                    out[left.text.decode('utf-8', 'replace')] = src[0]
        stack.extend(n.children)
    return out


def _same_self_arg(args, obj):
    """首个实参是否就是 vptr 的持有者（`this` 必须一致，否则不敢判定）。"""
    if not args:
        return False
    first = ' '.join(args[0].split())
    o = ' '.join(str(obj).split())
    if first == o or _strip_outer_parens(first) == o:
        return True
    return re.sub(r'^\(\s*[\w: ]+\*+\s*\)\s*', '', first).strip() == o


def _vtable_failure_log_path(ctx):
    """台账路径：ctx 注入 > 环境变量 > 仓库默认 `data/status/vtable_transform_failures.md`。"""
    p = getattr(ctx, 'vtable_failure_log', None) if ctx is not None else None
    if p:
        return str(p)
    env = os.environ.get('PAL3_VTABLE_FAILURE_LOG')
    if env:
        return env
    root = os.path.dirname(os.path.dirname(os.path.dirname(
        os.path.dirname(os.path.abspath(__file__)))))
    return os.path.join(root, *_VTBL_FAILURE_LOG_DEFAULT)


def _load_failure_keys(path):
    """把既有台账行恢复进 `_VTBL_FAILURE_WRITTEN` ⇒ 跨进程幂等（重复运行不重复追加）。"""
    try:
        with open(path, encoding='utf-8', errors='replace') as fh:
            for line in fh:
                m = _VTBL_ROW.match(line)
                if not m:
                    continue
                loc = m.group('loc')
                loc_cls, _, loc_m = loc.rpartition('::')
                _VTBL_FAILURE_WRITTEN.add(
                    (path, loc_cls, loc_m, m.group('form'), m.group('hint'),
                     m.group('off'), m.group('reason')))
    except OSError:
        return


def _record_vtable_failure(ctx, d, reason, call_text=''):
    """失败记账（追加 + 幂等）。I/O 失败只报 stderr，绝不吞掉其它异常。"""
    try:
        path = _vtable_failure_log_path(ctx)
    except Exception:                                # ctx 形状异常不该打断 codegen
        return
    cls = str(getattr(ctx, 'cls_name', '') or '')
    method = str(getattr(ctx, 'method_name', '') or '')
    try:
        off = int(d.get('offset') or 0)
    except (TypeError, ValueError):
        off = 0
    key = (path, cls, method, str(d.get('form', '')), str(d.get('cls_hint', '') or ''),
           str(off), str(reason))
    if path not in _VTBL_FAILURE_LOADED:
        _VTBL_FAILURE_LOADED.add(path)
        _load_failure_keys(path)
    if key in _VTBL_FAILURE_WRITTEN:
        return
    _VTBL_FAILURE_WRITTEN.add(key)
    try:
        fresh = (not os.path.exists(path)) or os.path.getsize(path) == 0
        d_dir = os.path.dirname(path)
        if d_dir and not os.path.isdir(d_dir):
            os.makedirs(d_dir, exist_ok=True)
        with open(path, 'a', encoding='utf-8') as fh:
            if fresh:
                fh.write(_VTBL_FAILURE_HEADER)
            fh.write(_VTBL_FAILURE_ROW % (
                cls, method, str(d.get('form', '')), str(d.get('cls_hint', '') or ''),
                off, str(reason),
                ' '.join(str(call_text).split()).replace('|', '\\|')[:180]))
    except OSError as _e:
        sys.stderr.write('[stage3] vtable failure ledger write failed (%s): %r\n'
                         % (path, _e))


def _sanitize_stub_sig(ret, params):
    """stub 签名清洗（2026-09-19，长线计划第 2 条）。

    实测 `pal3/src/Combat/CCBUI.cpp:554/584` 发射的是
    `static virtual int pal3_vtbl_unk_9349112a(void *, UIFrameWnd *this, void *Block, char a3)`
    —— `virtual` 与 `static` 不能并用、`this` 不能作形参名，两者都是硬语法错误（C2059/C2143）。
    签名里出现它们只可能来自反编译文本/cast 的转写，属于**纯清洗**，不改变任何调用语义。
    """
    ret = re.sub(r'\b(?:static|virtual|inline|explicit)\b\s*', '', str(ret or 'void')).strip()
    pl = str(params or '')
    # 形参名里的 C++ 关键字：`this` 只可能出现在**形参名**位置（类型名不可能是 this），
    # 判定为"后面跟 , 或结尾（允许数组后缀）"。`UIFrameWnd *this` / `int this` 都要覆盖。
    pl = re.sub(r'\bthis\b(\s*\[[^\]]*\])?\s*(?=,|$)', r'this_\1', pl)
    return (ret or 'void'), pl.strip()


def _vtbl_stub_name(ret, params):
    """stub 名由**签名**决定（不再是每函数从 0 开始的序号）。

    旧实现用 `idx = len(stub_items)`，而 `stub_items` 是**每次
    `_resolve_vftable_calls_ast` 调用（= 每个函数）局部新建**的 ⇒ 同一个 .cpp 里
    每个函数都从 `_0` 重新编号。实测：51 个文件含 stub 块，其中 **22 个含多于一个块**
    （`Combat/CCBUI.cpp` 16 个），**22 个文件存在同名但不同签名的重复定义** ⇒
    MSVC `C2084`(already has a body) / `C2371`(redefinition) /
    `C2556`(overloaded function differs only by return type)。
    改成签名哈希后，不同签名永不同名。
    """
    ret, params = _sanitize_stub_sig(ret, params)
    key = '%s|%s' % (' '.join(str(ret).split()), ' '.join(str(params).split()))
    return 'pal3_vtbl_unk_%s' % _hashlib.md5(key.encode('utf-8')).hexdigest()[:8]


def _vtbl_stub_names(ret, params, name):
    """Build thunk declaration+definition preserving cast signature."""
    ret, params = _sanitize_stub_sig(ret, params)
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
    decl = 'static %s %s(%s);' % (ret, name, params)
    definition = ('static %s %s(%s)\n{\n    %s\n}'
                  % (ret, name, params, body))
    return decl, definition


def _resolve_vftable_calls_ast(code, ctx):
    tree = _parser.parse(code.encode('utf-8'))
    # Task 7 形态 2：本函数内的 `V = <vptr 读>` 表（`run()` 的一次调用 = 一个函数）
    vptr_locals = _collect_vptr_locals(tree)
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
            d = None
            if func is not None:
                if _find_vftable_in_subtree(func):
                    d = _decode_vtbl_call(node)
                if d is None:
                    # Task 7：三形态（inline / 局部 vftable 变量 / 裸 vptr 读）。
                    # 与 legacy `__vftable` 分支**并列** ⇒ legacy 语义不受影响。
                    d = _decode_vptr_dispatch(node, vptr_locals)
            if d is not None and d.get('dispatch'):
                args_node = node.child_by_field_name('arguments')
                if args_node is None:            # 语法树残缺：不猜，直接放行到子节点
                    for child in node.children:
                        visit(child)
                    return
                raw_args = args_node.text.decode('utf-8', errors='replace')
                args = _split_args(raw_args[1:-1] if raw_args.startswith('(') else raw_args)
                _call_text = node.text.decode('utf-8', errors='replace')
                if not _same_self_arg(args, d['obj']):
                    # vptr 持有者 ≠ 自身实参 ⇒ this 不同（子对象/偏移视图）⇒ 不敢判定
                    _record_vtable_failure(ctx, d, 'self_arg_mismatch', _call_text)
                else:
                    method, _why = _resolve_vtbl_name_chain(d['cls_hint'], d['offset'])
                    if method:
                        repl = '%s->%s(%s)' % (d['obj'], method, ', '.join(args[1:]))
                        edits.append((node.start_byte, node.end_byte, repl))
                        covered.append((node.start_byte, node.end_byte))
                        return          # don't descend into replaced node
                    # 失败输出契约：原文逐字保留（绝不伪造裸偏移形态）+ 记账
                    _record_vtable_failure(ctx, d, _why or 'unresolved', _call_text)
            elif d is not None:
                args_node = node.child_by_field_name('arguments')
                raw_args = args_node.text.decode('utf-8', errors='replace')
                args = _split_args(raw_args[1:-1] if raw_args.startswith('(') else raw_args)
                method = _resolve_vtbl_method(d)
                if method:
                    keep = _drop_self_arg(args, d['obj'])
                    repl = '%s->%s(%s)' % (d['obj'], method, ', '.join(keep))
                else:
                    if d['ret'] is not None and d['params'] is not None:
                        name = _vtbl_stub_name(d['ret'], d['params'])
                        # 同文件去重：同一个签名在**本输出文件**里只发射一次
                        # 声明+定义（第二次起调用点仍引用该名字，声明已在其上方）。
                        # registry 由 emit_cpp 按输出文件创建并传入（见 TransformContext.
                        # stub_registry）；未传时退化为"每次都发射"（旧行为，安全）。
                        _reg = getattr(ctx, 'stub_registry', None)
                        if _reg is None or name not in _reg:
                            if _reg is not None:
                                _reg.add(name)
                            decl, definition = _vtbl_stub_names(d['ret'], d['params'], name)
                            stub_items.append(
                                (decl, definition,
                                 '// %s original: %s'
                                 % (_VTBL_STUB_MARK,
                                    ' '.join(node.text.decode('utf-8', errors='replace').split()))))
                        # P1(b)：裸链（无 cast）的实参里**没有对象**，
                        # 而 stub 的形参表把对象放在首位 ⇒ 调用时要把对象补回去。
                        _callargs = ', '.join(args)
                        if d.get('synthetic_self'):
                            _callargs = d['obj'] + (', ' + _callargs if _callargs else '')
                        repl = '%s(%s) /* %s */' % (
                            name, _callargs, _VTBL_STUB_MARK)
                    else:
                        # 无 cast 信息（裸链 `RECV->__vftable->NAME(args)`：ret/params 都是 None）。
                        # 本函数的设计意图是"未解析的虚调用改写为合成 stub"（见上方注释），
                        # 这里原来直接放弃 ⇒ `__vftable` 文本残留 ⇒ C2039/C2227（21 文件/135 站点）。
                        # 只在**语句位置**（返回值未被使用）补一个通用可变参数 stub：
                        # 签名无关 ⇒ 必然可编译；它不是字节忠实的调用，但本来就没有可编译的写法。
                        _par = getattr(node, 'parent', None)
                        if d['method'] and _par is not None and \
                                _par.type == 'expression_statement':
                            _reg = getattr(ctx, 'stub_registry', None)
                            _va = 'pal3_vtbl_unk_va'
                            if _reg is None or _va not in _reg:
                                if _reg is not None:
                                    _reg.add(_va)
                                stub_items.append(
                                    ('static void %s(...);' % _va,
                                     'static void %s(...)\n{\n}' % _va,
                                     '// %s original: %s'
                                     % (_VTBL_STUB_MARK,
                                        ' '.join(node.text.decode('utf-8', errors='replace').split()))))
                            _callargs = ', '.join([d['obj']] + args)
                            repl = '%s(%s) /* %s */' % (_va, _callargs, _VTBL_STUB_MARK)
                        else:
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


def _base_names_of(cls_name, depth=0):
    """`cls_name` 的**传递基类名集合**（只用 `store.struct_base_names`，**不需要偏移**）。

    用途：判定限定链上的某个名字"**到底是不是**该类的基类" —— 这决定了遇到
    "是基类但偏移未知"（保持原样）还是"根本不是基类"（限定符是 IDB 残留，按未限定处理）。
    走 `store` 而不是自读 annotation JSON：`data.py` 是 codegen 读 annotation 的唯一获准位置。
    """
    seen = set()
    cur = [cls_name]
    while cur and depth < 12:
        nxt = []
        for c in cur:
            for n in (store.struct_base_names.get(c) or []):
                if n and n not in seen:
                    seen.add(n)
                    nxt.append(n)
        cur = nxt
        depth += 1
    return seen


def _static_member_type(cls_name, member, depth=0):
    """成员在其类（含继承链）里的声明类型；找不到返回 None。"""
    if not cls_name or depth > 12:
        return None
    for _o, v in (store.struct_members.get(cls_name) or {}).items():
        if v and v[0] == member:
            t = str(v[1] or '').strip()
            return t or None
    for b in (store.struct_base_names.get(cls_name) or []):
        t = _static_member_type(b, member, depth + 1)
        if t:
            return t
    return None


def _static_type_of_object(obj_text, ctx):
    """对象表达式的静态类型名（尽力而为）：`this` / 成员名。**取不到就返回 None**
    —— 调用方据此不做任何推断。"""
    obj = obj_text.strip()
    while obj.startswith('(') and obj.endswith(')'):
        obj = obj[1:-1].strip()
    if obj == 'this':
        return getattr(ctx, 'cls_name', None) or None
    m = re.match(r'^(?:this\s*->\s*)?([A-Za-z_]\w*)$', obj)
    if not m:
        return None
    base = getattr(ctx, 'cls_name', None) or None
    if not base:
        return None
    t = _static_member_type(base, m.group(1))
    if not t:
        return None
    t = re.sub(r'\[[^\]]*\]', '', t).replace('*', '').strip()
    return t or None


def _qualified_vftable_offset(qual_text, cls_name):
    """限定链 `A::B::__vftable` -> (动作, 偏移)。

    动作：
      'offset' —— 链的每一级都是**已知偏移的基类**，返回距对象起点的字节偏移；
      'strip'  —— 链上某一级**根本不是**所在类的基类（用 `base_class` 名单可证），
                  说明该限定符是 IDB 残留 ⇒ 回落成**未限定**语义（对象自身的 vfptr，偏移 0）；
      'skip'   —— 该级**是**基类但偏移未知 ⇒ 不猜，原样保留。
    """
    if not cls_name:
        return ('skip', None)
    qual = qual_text.decode('utf-8')
    if not qual.endswith('::__vftable'):
        return ('skip', None)
    parts = [x for x in qual[:-len('::__vftable')].split('::') if x]
    if not parts:
        return ('skip', None)
    off = 0
    cur = cls_name
    for p in parts:
        bases = store.struct_bases.get(cur) or {}
        if p in bases:
            off += bases[p]
            cur = p
            continue
        if p in _base_names_of(cur):
            return ('skip', None)        # 是基类，但偏移未知 —— 不猜
        # 'strip' 需正证（test_qualified_vftable_left_alone：6 存量红测根因）：
        # 限定名必须是**已知类名**（struct_bases 注册过）才能断言"类限定残留"
        # （UIScrollBar/UIListBox 尺寸反证族 ✓）；若是**成员名**（GlowObj=成员 +8）
        # 或未知名 —— `X->Mem::__vftable` 是成员子对象限定，盲折偏移 0=**静默错址写**
        # ⇒ 'skip' 原样保留（编译错可见、错址写不可见——W1 优先级律）。
        if p in store.struct_bases:
            return ('strip', None)       # 已知类名但非基类 —— 限定符是残留
        return ('skip', None)            # 成员名/未知 —— 不猜不折
    return ('offset', off)


def _fold_vftable_mask(code, ctx=None):
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
            _qoff = None
            _qstrip = False
            if field is not None and field.type == 'qualified_identifier' \
                    and field.text.endswith(b'::__vftable') and ctx is not None:
                _a = node.child_by_field_name('argument')
                if _a is not None:
                    # 对象的静态类型：`this` 用 ctx.cls_name；成员名走注解的继承链查
                    # （`store.struct_members` 同源）。**取不到类型就不动**。
                    _otype = _static_type_of_object(
                        raw[_a.start_byte:_a.end_byte].decode('utf-8'), ctx)
                    _act, _off = _qualified_vftable_offset(field.text, _otype)
                    if _act == 'offset':
                        _qoff = _off
                    elif _act == 'strip':
                        # 链上某级**根本不是**所在类的基类（base_class 名单可证，
                        # 例如 UIScrollBar 的尺寸 352 < UIListBox 的 1208 ⇒ 不可能派生）
                        # ⇒ 该限定符是 IDB 残留，按**未限定**语义处理（对象自身 vfptr，偏移 0）
                        _qstrip = True
                    # 'skip'：是基类但偏移未知 ⇒ 原样保留，不猜
            if field is not None and (
                    (field.text == b'__vftable' and field.type != 'qualified_identifier')
                    or _qoff is not None or _qstrip):
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
                        # 限定链：把总偏移折进地址（偏移 0 时保持与未限定形完全相同的写法，
                        # 避免对 38 处"首基类偏移 0"的位点产生无谓文本改动）
                        deref = ('((char *)%s + %d)' % (deref, _qoff)) if _qoff else deref
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


def _expand_pair64_double(code):
    """(double)__PAIR64__(H, L) → ((double)(unsigned int)(H) * 4294967296.0
                                    + (double)(unsigned int)(L))
    （批 E 单点：MSVC6 无 unsigned __int64→double，C2520；等价展开双精无损。
    d0643565 反例：H 有符号负值无铸形不等价——**双侧 (unsigned int) 铸**对齐宏语义。
    07fe8e00 返工：**外层匹配改扫描器**（原正则在字符串内 `)` 处截断 ⇒ 内层跳串逻辑
    看不到完整参数）——`(double)__PAIR64__(` 起点后逐字符扫真闭括号（跳字符串/字符
    字面量/`//`/`/* */`）；`//` 尾注释形保换行（l.strip() 剥换行致 `));` 被注释的洞）。"""
    def _scan_close(s, i):
        """从 s[i]（左括号后）扫到配对右括号位（跳字面量/注释）；无配对返回 None。"""
        depth, n = 1, len(s)
        while i < n:
            ch = s[i]
            if ch in '"\'':
                q = ch
                i += 1
                while i < n and s[i] != q:
                    i += 2 if s[i] == '\\' else 1
                i += 1
                continue
            if ch == '/' and i + 1 < n and s[i + 1] == '/':
                while i < n and s[i] != '\n':
                    i += 1
                continue
            if ch == '/' and i + 1 < n and s[i + 1] == '*':
                i += 2
                while i + 1 < n and not (s[i] == '*' and s[i + 1] == '/'):
                    i += 1
                i += 2
                continue
            if ch == '(':
                depth += 1
            elif ch == ')':
                depth -= 1
                if depth == 0:
                    return i
            i += 1
        return None

    def _split_top(inner):
        """顶层逗号位（跳字面量/注释）；无则 None。"""
        depth, n = 0, len(inner)
        i = 0
        while i < n:
            ch = inner[i]
            if ch in '"\'':
                q = ch
                i += 1
                while i < n and inner[i] != q:
                    i += 2 if inner[i] == '\\' else 1
                i += 1
                continue
            if ch == '/' and i + 1 < n and inner[i + 1] == '/':
                while i < n and inner[i] != '\n':
                    i += 1
                continue
            if ch == '/' and i + 1 < n and inner[i + 1] == '*':
                i += 2
                while i + 1 < n and not (inner[i] == '*' and inner[i + 1] == '/'):
                    i += 1
                i += 2
                continue
            if ch == '(':
                depth += 1
            elif ch == ')':
                depth -= 1
            elif ch == ',' and depth == 0:
                return i
            i += 1
        return None

    out = []
    pos = 0
    # 5a7a3b86 新洞-2：pat.search 须在**掩码**上做（串/注释内形改写=字节风险、T15 真崩）
    # ——E-1 的 _mask_strings_comments 同长遮蔽贯彻 E-2（替换落回原文保位移）。
    try:
        from ast_transform import _mask_strings_comments as _msc
    except Exception:
        try:
            from gen.stages.ast_transform import _mask_strings_comments as _msc
        except Exception:
            _msc = None
    masked = _msc(code) if _msc else code
    pat = re.compile(r'\(double\)\s*__PAIR64__\(')
    while True:
        m = pat.search(masked, pos)
        if not m:
            out.append(code[pos:])
            break
        inner_start = m.end()
        close = _scan_close(masked, inner_start)
        if close is None:
            out.append(code[pos:])
            break
        inner = code[inner_start:close]
        comma = _split_top(inner)
        if comma is None:
            out.append(code[pos:close + 1])   # 单参畸形形：原样保留
        else:
            h, l = inner[:comma], inner[comma + 1:]
            # 尾注释保换行（C8）——**h/l 双侧**（5a7a3b86 新洞-1：h 侧漏致语法崩）
            def _keep(x):
                if re.search(r'//[^\n]*$', x.strip()):
                    return x.rstrip() + '\n'
                return x.strip()
            out.append(code[pos:m.start()])
            out.append('((double)(unsigned int)(%s) * 4294967296.0'
                       ' + (double)(unsigned int)(%s))' % (_keep(h), _keep(l)))
        pos = close + 1
    return ''.join(out)


def _expand_pair64_point(code):
    """[F-CG#19 2026-10-15] (POINT)__PAIR64__(H, L) → _pal3_pair_to_point(H, L)。

    覆盖缺口补：__PAIR64__ 展开族此前只有 `(double)` 形 ⇒ `(POINT)__PAIR64__`
    经宏展开得 `(POINT)(((unsigned __int64)(H) << 32) | (unsigned int)(L))`
    ——__int64→struct POINT 转换 MSVC6 拒绝（C2440/C2102 族 2 错）。
    位等价：宏的低 32=L=POINT.x、高 32=H=POINT.y（PtInRect 按值传 8B）⇒
    helper `_pal3_pair_to_point(H,L)` 内联返回 POINT{x=L,y=H}（ida_defs.h）。
    实参**原文搬运**（括号配平扫描同 _expand_pair64_double）⇒ 注释/空白零风险。
    """
    out, pos = [], 0
    pat = re.compile(r'\(POINT\)\s*__PAIR64__\(')
    while True:
        m = pat.search(code, pos)
        if not m:
            out.append(code[pos:])
            break
        depth, i, n = 1, m.end(), len(code)
        close = None
        while i < n:
            ch = code[i]
            if ch in '"\'':
                q = ch
                i += 1
                while i < n and code[i] != q:
                    i += 2 if code[i] == '\\' else 1
                i += 1
                continue
            if ch == '(':
                depth += 1
            elif ch == ')':
                depth -= 1
                if depth == 0:
                    close = i
                    break
            i += 1
        if close is None:
            out.append(code[pos:])
            break
        inner = code[m.end():close]
        out.append(code[pos:m.start()])
        out.append('_pal3_pair_to_point(%s)' % inner)
        pos = close + 1
    return ''.join(out)


# ============================================================
# [T12] M3 lvar 重复声明归并（接线 TDD 存量 dedupe_identical_lvars 语义）
# ============================================================
# 病灶（2026-10-12 实测）：Hex-Rays 对同一栈槽的类型复用拆出多个 lvar_t
# （PAL3::FullInit@0x00408FD0 槽 56 共 14 个：pSceneName/pNewBuffer ×
# void*/int/gbVec3D*，槽 60 共 2 个 pSceneName）⇒ 渲染成同名多条声明
# ⇒ C2086×10 + C2371×2 + C2040×2（生成 PAL3.cpp:2162-2175 共 14 错）。
# 一个 C++ 标识符只能有一条声明——同名多条本身不可编译；同槽多名在原始源里
# 是**不重叠生命期的独立变量被编译器合槽**（VC6 槽复用）⇒ 每名保留一条
# 声明即忠实重建。
# 修法（等价变换）：同名声明**首条保留、其余删除**（全等或异型皆然——异型
# 即 C2371 源）。保留类型的仲裁（pSceneName 的 int 视图 vs void* 视图等）
# 是 adjudicate_lvar_type 显式挂账的「接线批」，本次不动（禁猜测）。
_LVAR_DECL_RE = re.compile(
    r'^(?![^;]*=)[\w:<>,\s\*&]*?(\w+)\s*(?:\[[^\]]*\])?\s*;\s*'
    r'//\s*\[esp\+(?:0x[0-9A-Fa-f]+|[0-9A-Fa-f]+h)\]'
    r'\s*\[ebp-(?:0x[0-9A-Fa-f]+|[0-9A-Fa-f]+h)\]')


def dedupe_lvar_decls(code):
    """同名 lvar 声明归并（首条保留）；只认带 [esp..][ebp..] 注释的声明行。"""
    seen = set()
    out = []
    dropped = 0
    for line in code.split('\n'):
        m = _LVAR_DECL_RE.match(line)
        if m:
            name = m.group(1)
            if name in seen:
                dropped += 1
                continue
            seen.add(name)
        out.append(line)
    return '\n'.join(out) if not dropped else '\n'.join(out)


def run(code, ctx):
    """Stage 3: post-OOP cleanup."""
    cls_name = ctx.cls_name

    # [T12] M3：同名 lvar 重复声明归并（C2086/C2371/C2040 源头）
    code = dedupe_lvar_decls(code)

    # --- Simple text substitutions (no structural analysis needed) ---

    # Remove 'this' variable declaration (for class methods)
    if not ctx.is_free_function and cls_name:
        code = re.sub(r'^\s*%s\s*\*\s*this\s*;.*$' % re.escape(cls_name), '', code, flags=re.MULTILINE)

    # Operator new fix
    code = re.sub(r'\(\(operator \*\)(0x[0-9A-Fa-f]+u?)\)->new\(\)', r'operator new(\1)', code)
    # CC removal from body (function pointer casts)
    # [批1-5#2 2026-10-15] fnptr 声明位的 __thiscall **不得剥**：MSVC6 拒绝该拼法
    # （受控实验 C4234 'keyword reserved for future use'）⇒ stage4
    # `rewrite_thiscall_fnptr_param` 需要它转成员指针形。全局剥除使 stage4 pass 0
    # 失配 ⇒ 头（成员指针）/定义（普通指针）两形对峙 C2511（实测
    # RenderTarget2::AdjustThisCall@0x4C2850，1 错卡整个单元 S2 +1）。
    # 护位符保护 → 剥除 → 还原（等价变换：仅对非 fnptr 位剥除）。
    _fp_saves = []
    for _m in re.finditer(r'\(\s*__thiscall\s*\*\s*\w+\s*\)\s*\([^()]*\)', code):
        _fp_saves.append(_m.group(0))
    if _fp_saves:
        for _i in range(len(_fp_saves) - 1, -1, -1):
            code = code.replace(_fp_saves[_i], '\x00FP%d\x00' % _i, 1)
    code = re.sub(r'__thiscall\s+', '', code)
    for _i, _saved in enumerate(_fp_saves):
        code = code.replace('\x00FP%d\x00' % _i, _saved)
    code = re.sub(r'__userpurge\s+', '', code)
    code = re.sub(r'__usercall\s+', '', code)

    # Hex-Rays ".0" member access (offset-0 field): obj[N].0 → obj[N], obj.member.0 → obj.member
    code = re.sub(r'(?<=[\]a-zA-Z_])\.0\b', '', code)

    # 基类名后缀访问等价重写（批 E 族 1）——**接线已回退**（2026-09-28 链验 C2102 +286
    # /S2 95→86 净回归：`&recv.Base` 取址形与调用形未覆盖 ⇒ 纯文本重写上下文盲）。
    # 纯函数与 7 测保留（test_base_suffix_rewrite.py）；重设计=AST 级/全上下文形（挂账）。
    # try:
    #     from gen.stages.base_suffix_rewrite import apply_base_suffix_rewrite as _bsr
    #     _st = getattr(ctx, 'store', None)
    #     if _st is None:
    #         from data import store as _st
    #     code = _bsr(code, _st)
    # except Exception:
    #     pass

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

    # 【2026-09-15】`COERCE_FLOAT/T` 实参为**非字面量**的情形**不在这里处理**——
    # 这里只能做文本替换，而"实参是不是 lvalue / 是不是函数调用"是**语法结构**判断，
    # 正则做不可靠（实测我在此连错 4 次：交替顺序、贪婪匹配、`->` 误判、`i64` 后缀）。
    # ⇒ 改由 **AST 层**处理：`ast_transform.transform_coerce_calls()`，
    #    在 `stage2_semantic` 里调用（该 stage 已用 tree-sitter）。

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
    #
    # ⚠️ 2026-09-21 **已实测的缺陷（尚未修）**：这里的 repl `\1->\2(\3)` **丢掉了 `(*...)` 的
    # 解引用层级**。`ptr` 的类型必然是多级指针/数组（`UIStatic **p_m_pBack`、`UIListBox *m_pMagicList[6]`），
    # 丢掉 `*` 后接收者不是类类型 ⇒ C2227 `left of '->X' must point to class/struct/union`。
    # decomp 语料里该形态 **76 站点 / 29 文件**（ShowWindow 53、Create 16、_sdtor_call_dtor 7）。
    #
    # **单改这一行会被门禁拦下**（2026-09-21 单变量 A/B 实测）：
    #   C2227 −41 ✓ / C2039 +22 ✗ / S2 ok 75→74 ✗ / **L1 35→34 ✗** / matched 265/319→256/309 ✗
    # 原因是"保留解引用"只解决**接收者类型**，不解决**方法是否是该类成员**：
    #   `(*p)->ShowWindow(1)` 能编译（UIStatic : UIWnd，继承到 `virtual int ShowWindow(int)`），
    #   但 `(*p)->Create(1)` / `(*p)->_sdtor_call_dtor(1)` 仍报 C2039 ——
    #   `Create` 未在 UIStatic/UIPushButton/UIListBox/UIScene 里声明（UIStatic 的 methods/vtables
    #   系上一会话因真实 vtable(0x56B018) 未定而**刻意剥离**，不可凭猜测恢复）；
    #   `_sdtor_call_dtor` 则依赖 stage5_fixup.py:892-898 的 `delete \1` 规则，而该规则只接受**裸标识符**
    #   接收者 ⇒ `(*ptr)->_sdtor_call_dtor(1)` 不再被转成 `delete`（这正是那个 1 个 ok→fail 单元）。
    # ⇒ 要拿到收益，必须**同批**补齐：① stage5_fixup 的 `(*ident)` 形态；② 目标类对槽位方法名的声明
    #   （或让解析器在"目标类没有该方法"时回退到既有 stub 路径 —— 即 vtable 解析器 S2/S3 的设计内容）。
    # 验收测试（自门控，修好即生效）：tests/test_vftable_deref_preserved.py
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
    code = _fold_vftable_mask(code, ctx)

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
    # 批 E 单点（TextureLibDataBase:391 C2520）：MSVC6 无 unsigned __int64→double 转换
    # ——(double)__PAIR64__(H,L) 等价展开 H*4294967296.0+L（双精对 32+32 位无损）。
    code = _expand_pair64_double(code)
    # [F-CG#19 2026-10-15] (POINT)__PAIR64__(H,L) → _pal3_pair_to_point(H,L)
    # （__int64→POINT 转换 MSVC6 拒绝；位等价 helper 详见函数 docstring）
    code = _expand_pair64_point(code)

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
    'Scale': {0},
    'LeftTranslate': {0},
    'RightTranslate': {0},
    'MakeMatrix': {0, 1, 2},
    'IntersectPlane': {0, 1},
    'IsColAABB': {0},
    'IsColOBB_H': {0},
    # 【B 修同款（方案复核）】PAU 指针形出表/AAU 引用形留表——限定键+元数感知
    'gbMatrixStack::Rotate': {2: {1}, 1: {0}},
    'gbRay::IsColOBB': {0}, 'gbPlane::IsColOBB': {0},
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
        # 【B 修】限定键（Cls::fn）与裸名双形+元数感知（PAU/AAU 分流随行）
        if '::' in func_name:
            pattern = _re.escape(func_name) + r'\s*\('
        else:
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
            # 【B 修】元数预数（dict 形 ref_indices 需 arity 定位）
            if isinstance(ref_indices, dict):
                _d, _j, _na = 1, call_start, 1
                while _j < len(code) and _d > 0:
                    _c = code[_j]
                    if _c == '(':
                        _d += 1
                    elif _c == ')':
                        _d -= 1
                    elif _c == ',' and _d == 1:
                        _na += 1
                    _j += 1
                ref_positions = ref_indices.get(_na, set())
            else:
                ref_positions = ref_indices
            
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
                        if arg_idx in ref_positions:
                            arg = arg.lstrip()
                            if arg.startswith('&') and not arg.startswith('&&'):
                                arg = arg[1:]
                        result.append(arg)
                        result.append(')')
                        break
                elif ch == ',' and depth == 1:
                    # Process this argument
                    arg = code[arg_start:i]
                    if arg_idx in ref_positions:
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
    
    # _tail_000 兼容转换（2026-09-25）：gbGfxManager offset0 旧 IDA 名 → 裸偏移
    code = re.sub(r'(\w+)->_tail_000\b(?!\[)', r'*(void**)(\1)', code)
    return code
