"""
AST-based C++ code transformations using tree-sitter.

Replaces regex-based OOP conversion with correct AST analysis.
Only transforms calls where first argument is safe to convert.
"""

import tree_sitter_cpp as tscpp
import tree_sitter
import re
import os
import json

_lang = tree_sitter.Language(tscpp.language())
_parser = tree_sitter.Parser(_lang)

# Cache class hierarchy from annotation data
_CLASS_BASES = None

def _ensure_bases():
    global _CLASS_BASES
    if _CLASS_BASES is not None:
        return
    _CLASS_BASES = {}
    _gen_dir = os.path.dirname(os.path.abspath(__file__))
    _proj = os.path.dirname(os.path.dirname(_gen_dir))
    _structs_dir = os.path.join(_proj, 'data', 'annotations', 'structs')
    if not os.path.isdir(_structs_dir):
        return
    for _f in sorted(os.listdir(_structs_dir)):
        if not _f.endswith('.json'):
            continue
        _sd = json.load(open(os.path.join(_structs_dir, _f), encoding='utf-8'))
        _c = _sd.get('name', '')
        _b = _sd.get('base_class')
        if _b:
            if isinstance(_b, str):
                _b = [_b]
            _CLASS_BASES[_c] = _b

def _is_derived_from(derived, base):
    """Check if derived class inherits from base (directly or transitively)."""
    if derived == base:
        return True
    if not _CLASS_BASES:
        return False
    _bases = _CLASS_BASES.get(derived, [])
    for _b in _bases:
        if _is_derived_from(_b, base):
            return True
    return False


def transform_oop_calls(code, static_methods=None, cls_name=None):
    """
    Transform Class::Method(obj, args) -> obj->Method(args)
    Only when:
    - Function is qualified (Class::Method)
    - First argument is a simple identifier or 'this'
    - Function is NOT a static (__cdecl) method

    Does NOT transform when first arg is:
    - Cast expression: (Type *)expr
    - Member access: obj->field
    - Array subscript: arr[i]
    - Any other complex expression
    """
    if static_methods is None:
        static_methods = set()

    # Preprocess Hex-Rays ->N (offset N access) patterns before tree-sitter parsing.
    # Hex-Rays generates "&var->N" meaning "address of member at offset N" which in C
    # is just "var" (the pointer itself). "var->N" alone means "first DWORD at *var".
    # tree-sitter can't parse ->N as valid C++, so we must normalize first.
    code = re.sub(r'&(\w+(?:\s*->\s*\w+)*)\s*->\s*0\b', r'\1', code)
    code = re.sub(r'\b(\w+(?:\s*->\s*\w+)*)\s*->\s*0\b', r'*((_DWORD *)\1)', code)

    code_bytes = code.encode('utf-8')
    tree = _parser.parse(code_bytes)

    # Collect replacements (offset, length, new_text)
    replacements = []

    def process_node(node):
        if node.type == 'call_expression':
            func_node = node.child_by_field_name('function')
            args_node = node.child_by_field_name('arguments')

            if func_node and args_node and func_node.type == 'qualified_identifier':
                # It's a Class::Method(...) call
                scope_node = func_node.child_by_field_name('scope')
                name_node = func_node.child_by_field_name('name')

                if scope_node and name_node:
                    class_name = scope_node.text.decode('utf-8').rstrip(':')
                    method_name = name_node.text.decode('utf-8')

                    # Skip static (__cdecl) methods — their first arg is data, not this
                    qualified = '%s::%s' % (class_name, method_name)
                    if qualified in static_methods:
                        return

                    # Skip operator calls (operator new, operator delete, etc.)
                    if class_name == 'operator' or method_name == 'operator':
                        return

                    # Get arguments (skip parens and commas)
                    arg_nodes = [c for c in args_node.children
                                 if c.type not in ('(', ')', ',', 'comment')]

                    # Primitive-type class names are Hex-Rays misattributions.
                    # Strip the class qualifier to produce a free-function call.
                    # E.g. BYTE::_sub_4CD0D0(args) → _sub_4CD0D0(args)
                    _PRIMITIVE_TYPES = frozenset({
                        'BYTE', 'CHAR', 'WPARAM', 'float', 'double',
                        'int', 'long', 'short', 'char', 'void',
                        '_BYTE', '_DWORD', '_WORD', 'signed',
                        'unsigned', 'BOOL', 'DWORD', 'WORD',
                    })
                    if class_name in _PRIMITIVE_TYPES:
                        arg_texts = [a.text.decode('utf-8') for a in arg_nodes]
                        new_text = '%s(%s)' % (method_name, ', '.join(arg_texts))
                        replacements.append((
                            node.start_byte, node.end_byte, new_text))
                        import sys as _sys
                        print('[WARN] Hex-Rays misattribution: %s::%s → %s' % (
                            class_name, method_name, new_text[:80]), file=_sys.stderr)
                        return

                    if arg_nodes:
                        first_arg = arg_nodes[0]
                        first_arg_text = first_arg.text.decode('utf-8')

                        # Constructor call: Class::Class(&var, args) -> var.Class(args)
                        # Hex-Rays emits explicit-this ctor calls (placement style).
                        _short_cls = class_name.split('::')[-1]
                        if method_name == _short_cls:
                            _ctor_rest = ', '.join(
                                a.text.decode('utf-8') for a in arg_nodes[1:])
                            if first_arg_text.startswith('&'):
                                # Construct at address &var -> var.Class(args)
                                _obj = first_arg_text[1:]
                                new_text = '%s.%s(%s)' % (
                                    _obj, _short_cls, _ctor_rest)
                            elif first_arg_text == 'this':
                                new_text = 'this->%s(%s)' % (
                                    _short_cls, _ctor_rest)
                            else:
                                # Class::Class(ptr) -> ptr->Class()
                                new_text = '%s->%s(%s)' % (
                                    first_arg_text, _short_cls, _ctor_rest)
                            replacements.append((
                                node.start_byte, node.end_byte, new_text))
                            return

                        # Determine conversion strategy based on first arg type
                        rest_args = [a.text.decode('utf-8')
                                     for a in arg_nodes[1:]]
                        rest_str = ', '.join(rest_args)

                        if first_arg.type == 'this':
                            # Map IDA internal destructor name _ClassName -> ~ClassName
                            _method_out = method_name
                            if method_name == '_' + class_name.split('::')[-1]:
                                _method_out = '~' + class_name.split('::')[-1]
                            
                            # Constructor call: Class::Class(this) -> this->Class()
                            _short_cls = class_name.split('::')[-1]
                            if method_name == _short_cls:
                                _ensure_bases()
                                _is_base = _is_derived_from(cls_name, class_name)
                                if _is_base and class_name != cls_name:
                                    new_text = '%s::%s(%s)' % (class_name, _method_out, rest_str)
                                else:
                                    new_text = 'this->%s(%s)' % (_method_out, rest_str)
                                replacements.append((
                                    node.start_byte, node.end_byte, new_text))
                                return
                            
                            _ensure_bases()
                            _is_base = _is_derived_from(cls_name, class_name)
                            # Use qualified Base::Method(rest) when calling base class method
                            # from derived class that may SHADOW the base method.
                            if _is_base and class_name != cls_name:
                                new_text = '%s::%s(%s)' % (class_name, _method_out, rest_str)
                            elif class_name == cls_name or _is_base:
                                new_text = 'this->%s(%s)' % (_method_out, rest_str)
                            else:
                                # Non-base class destructor: output this->~Class()
                                # Stage 3 cleanup detects and deletes these (compiler handles chain).
                                if _method_out.startswith('~'):
                                    new_text = 'this->%s()' % _method_out
                                else:
                                    # Inter-class call with this as first arg.
                                    # Convert to ((Class *)this)->Method(rest) to remove
                                    # the explicit this and match header signature.
                                    new_text = '((%s *)this)->%s(%s)' % (
                                        class_name, _method_out, rest_str)
                            replacements.append((
                                node.start_byte, node.end_byte, new_text))
                            return
                        elif first_arg.type == 'identifier':
                            # Simple var: direct member access (no cast)
                            # Type safety is the annotation's job, not codegen's.
                            # If the type is wrong, the compiler error is a clear
                            # signal that the annotation needs fixing.
                            _strip = first_arg_text.lstrip(':')
                            _needs_addr = (
                                class_name[0].isupper()
                                and _strip.startswith('g_')
                                and _strip not in static_methods
                            )
                            _obj = '&' + first_arg_text if _needs_addr else first_arg_text
                            new_text = '%s->%s(%s)' % (
                                _obj, method_name, rest_str)
                            replacements.append((
                                node.start_byte, node.end_byte, new_text))
                            return
                        else:
                            # Complex expression as this-pointer
                            # Literals (numbers/strings/chars) can NEVER be a this
                            # pointer. Hex-Rays emits e.g. std::string::_Tidy(1)
                            # where 1 is a real parameter. Keep the static call
                            # form so the compiler reports an accurate error.
                            if first_arg.type in ('number', 'string_literal', 'character_literal'):
                                return
                            # Skip function call results — they return values, not objects
                            if first_arg.type == 'call_expression':
                                return
                            if first_arg.type == 'cast_expression':
                                val_node = first_arg.child_by_field_name('value')
                                inner = val_node.text.decode('utf-8') if val_node else first_arg_text
                                _inner_strip = inner.lstrip(':')
                                _qualified = '%s::%s' % (class_name, method_name)
                                if _qualified in static_methods:
                                    return
                                # If inner starts with &, it's a pointer to a local
                                # variable. Convert ONLY when cast type matches the
                                # class (explicit this), e.g. (Logger*)&ArgList.
                                _cast_type = first_arg_text.split('(')[-1].split(')')[0] if ')' in first_arg_text else ''
                                _cls_short = class_name.split('::')[-1]
                                if inner.startswith('&'):
                                    if _cls_short in _cast_type:
                                        # Explicit this cast: (Logger*)&var -> ((Logger*)&var)->Method
                                        new_text = '((%s))->%s(%s)' % (
                                            first_arg_text, method_name, rest_str)
                                        replacements.append((
                                            node.start_byte, node.end_byte, new_text))
                                        return
                                    return
                                _needs_addr = bool(re.match(r'^g_[A-Z]', _inner_strip))
                                _inner = '&' + inner if _needs_addr else inner
                                # When inner is 'this' with a cast to a different class:
                                # - If cast type is a base class → qualified call: this->Base::Method()
                                # - Otherwise → strip cast, let compiler error surface annotation issues
                                if inner == 'this' and _cast_type and _cls_short not in _cast_type:
                                    _ensure_bases()
                                    _cast_cls = _cast_type.replace('*', '').strip()
                                    if _is_derived_from(cls_name, _cast_cls):
                                        new_text = 'this->%s::%s(%s)' % (
                                            _cast_cls, method_name, rest_str)
                                    else:
                                        # Not inheritance — let compiler error surface
                                        new_text = '%s->%s(%s)' % (
                                            _inner, method_name, rest_str)
                                else:
                                    new_text = '%s->%s(%s)' % (
                                        _inner, method_name, rest_str)
                            elif first_arg.type == 'qualified_identifier':
                                _scope = first_arg.child_by_field_name('scope')
                                _name = first_arg.child_by_field_name('name')
                                _inner = (_scope.text.decode() if _scope else '') + (_name.text.decode() if _name else '')
                                _strip = _inner.lstrip(':')
                                _needs_addr = (
                                    class_name[0].isupper()
                                    and _strip.startswith('g_')
                                )
                                _inner = '&' + _inner if _needs_addr else _inner
                                new_text = '%s->%s(%s)' % (
                                    _inner, method_name, rest_str)
                            elif first_arg.type == 'pointer_expression':
                                # &expr as first arg.
                                # &g_Global implies a VALUE-type global (a pointer
                                # wouldn't need the address-of). Method call on a
                                # value uses '.', not '->'.
                                # Local variables (&local) → keep as Class::Method
                                _ptr_inner = first_arg_text[1:]  # strip &
                                _ptr_strip = _ptr_inner.lstrip(':')
                                if re.match(r'^g_[A-Z]', _ptr_strip):
                                    new_text = '%s.%s(%s)' % (
                                        _ptr_inner, method_name, rest_str)
                                else:
                                    return
                            elif first_arg.type in ('binary_expression', 'parenthesized_expression'):
                                # Complex expression like (Type*)ptr - offset or (ptr + N)
                                # Need parentheses to preserve operator precedence
                                new_text = '(%s)->%s(%s)' % (
                                    first_arg_text, method_name, rest_str)
                            else:
                                new_text = '%s->%s(%s)' % (
                                    first_arg_text, method_name, rest_str)
                            replacements.append((
                                node.start_byte, node.end_byte, new_text))
                            return

        for child in node.children:
            process_node(child)

    process_node(tree.root_node)

    # Apply replacements in reverse order (to preserve offsets)
    result = code_bytes
    for start, end, new_text in sorted(replacements, reverse=True):
        result = result[:start] + new_text.encode('utf-8') + result[end:]

    return result.decode('utf-8')


if __name__ == '__main__':
    # Test
    test_code = """
int CCBRoleState::Update()
{
  CCBRoleState::CheckStatus(this);
  CCBRoleState::ProcessActions(this);
  CCBStage::Update((CCBStage *)this->m_pStage);
  CCBControl::Update(v3);
  sub_4F3020(this, 3);
  return CCBRoleState::UpdateEffects(this);
}
"""
    result = transform_oop_calls(test_code, cls_name='CCBRoleState')
    print('=== cls matches ===')
    print(result)
    print()
    ok = True
    for desc, check in [
        ('this->CheckStatus()', 'this->CheckStatus' in result),
        ('this->ProcessActions()', 'this->ProcessActions' in result),
        ('((CCBStage *)this->m_pStage)->Update', '((CCBStage *)this->m_pStage)->Update' in result),
        ('sub_4F3020 unchanged', 'sub_4F3020(this, 3)' in result),
    ]:
        st = '✅' if check else '❌'
        print(f'{st} {desc}')
        ok = ok and check
    
    # Test with derived class context (base class Method calls)
    test_code2 = """
void CCBControlWindow::_CCBControlWindow()
{
  UIListBox::_UIListBox(this);
}
UIListBox * CCBControlWindow::CreateButton()
{
  PalScript::Create(this, 1879048195, (tagRECT *)pRect, parent);
  UIWnd::Create(this, 1879048196, (tagRECT *)pRect, parent);
  return this;
}
"""
    result2 = transform_oop_calls(test_code2, cls_name='CCBControlWindow')
    print()
    print('=== derived context ===')
    print(result2)
    print()
    for desc, check in [
        ('this->~UIListBox() for dtor', 'this->~UIListBox()' in result2),
        ('No _UIListBox call', 'UIListBox::_UIListBox' not in result2),
        ('PalScript::Create(this,...) kept',
         'PalScript::Create(this, 1879048195' in result2),
        ('UIWnd::Create(...) for base call (avoid shadow)',
         'UIWnd::Create(1879048196' in result2),
        ('NOT this->Create', 'this->Create(1879048196' not in result2),
    ]:
        st = '✅' if check else '❌'
        print(f'{st} {desc}')
        ok = ok and check
    
    status = 'PASSED' if ok else 'FAILED'
    print(f'\nAll: {status}')
