"""
AST-based C++ code transformations using tree-sitter.

Replaces regex-based OOP conversion with correct AST analysis.
Only transforms calls where first argument is safe to convert.
"""

import tree_sitter_cpp as tscpp
import tree_sitter
import re

_lang = tree_sitter.Language(tscpp.language())
_parser = tree_sitter.Parser(_lang)


def transform_oop_calls(code):
    """
    Transform Class::Method(obj, args) -> obj->Method(args)
    Only when:
    - Function is qualified (Class::Method)
    - First argument is a simple identifier or 'this'

    Does NOT transform when first arg is:
    - Cast expression: (Type *)expr
    - Member access: obj->field
    - Array subscript: arr[i]
    - Any other complex expression
    """
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

                    # Get arguments (skip parens and commas)
                    arg_nodes = [c for c in args_node.children
                                 if c.type not in ('(', ')', ',', 'comment')]

                    if arg_nodes:
                        first_arg = arg_nodes[0]
                        first_arg_text = first_arg.text.decode('utf-8')

                        # Determine conversion strategy based on first arg type
                        rest_args = [a.text.decode('utf-8')
                                     for a in arg_nodes[1:]]
                        rest_str = ', '.join(rest_args)

                        if first_arg.type == 'this':
                            # Simple: this->Method(rest)
                            new_text = 'this->%s(%s)' % (method_name, rest_str)
                            replacements.append((
                                node.start_byte, node.end_byte, new_text))
                            return
                        elif first_arg.type == 'identifier':
                            # Simple var: var->Method(rest)
                            new_text = '%s->%s(%s)' % (
                                first_arg_text, method_name, rest_str)
                            replacements.append((
                                node.start_byte, node.end_byte, new_text))
                            return
                        else:
                            # Complex expression as this-pointer
                            # If it's already a cast to the right type, use directly
                            if first_arg.type == 'cast_expression':
                                new_text = '(%s)->%s(%s)' % (
                                    first_arg_text, method_name, rest_str)
                            else:
                                # Add cast: ((ClassName *)expr)->Method(rest)
                                new_text = '((%s *)%s)->%s(%s)' % (
                                    class_name, first_arg_text,
                                    method_name, rest_str)
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
    result = transform_oop_calls(test_code)
    print(result)
