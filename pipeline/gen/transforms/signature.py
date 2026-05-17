"""Function signature/definition line transforms.

Order 50-70: Fix the function definition line before body transforms run.
Must run after ida_cleanup (0-49) but before OOP (200+).
"""
import re
from transforms import register
from data import store


@register(order=55)
def fix_function_def_line(code, ctx):
    """Fix the function definition line: replace sub_XXXXX, fix class name, strip CC."""
    if ctx.is_free_function:
        return code
    lines = code.split('\n')
    cls_name = ctx.cls_name
    method_name = ctx.method_name

    # Find function definition line (has '(' and class name or sub_)
    cls_variants = [cls_name]
    if cls_name.startswith('_'):
        cls_variants.append(cls_name[1:])

    func_line_idx = 0
    for idx, l in enumerate(lines):
        if '(' in l and (any(cv + '::' in l for cv in cls_variants) or 'sub_' in l):
            func_line_idx = idx
            break

    if not lines:
        return code

    first_line = lines[func_line_idx]
    full_method = '%s::%s' % (cls_name, method_name)

    # Replace sub_XXXXX with correct name
    first_line = re.sub(r'\bsub_[0-9A-Fa-f]+\b', full_method, first_line, count=1)

    # Fix IDA stripping leading underscore from class name
    for cv in cls_variants:
        if cv != cls_name and cv + '::' in first_line:
            first_line = first_line.replace(cv + '::', cls_name + '::')

    # Remove return type for ctor/dtor
    if ctx.is_ctor or ctx.is_dtor:
        first_line = re.sub(
            r'^.*?\b(%s::%s)' % (re.escape(cls_name), re.escape(method_name)),
            r'\1', first_line)

    # Remove calling conventions
    first_line = re.sub(r'\s*__thiscall\s*', ' ', first_line)
    first_line = re.sub(r'\s*__cdecl\s*', ' ', first_line)
    first_line = re.sub(r'\s*__stdcall\s*', ' ', first_line)
    first_line = re.sub(r'\s*__fastcall\s*', ' ', first_line)
    first_line = re.sub(r'\s*__userpurge\s*', ' ', first_line)
    first_line = re.sub(r'\s*__usercall\s*', ' ', first_line)

    # Remove "ClassName *this" parameter
    first_line = re.sub(r'\(\s*\w[\w\s]*\*+\s*this\s*,\s*', '(', first_line)
    first_line = re.sub(r'\(\s*\w[\w\s]*\*+\s*this\s*\)', '()', first_line)

    # Destructors cannot have parameters
    if ctx.is_dtor:
        first_line = re.sub(r'\([^)]*\)', '()', first_line)

    # Clean double spaces
    first_line = re.sub(r'  +', ' ', first_line).strip()
    lines[func_line_idx] = first_line
    return '\n'.join(lines)


@register(order=60)
def remove_ctor_return_statements(code, ctx):
    """For ctors/dtors, remove 'return expr;' (they can't return values)."""
    if not ctx.is_ctor and not ctx.is_dtor:
        return code
    lines = code.split('\n')
    for i in range(len(lines)):
        lines[i] = re.sub(r'^\s*return\s+(.+);', r'  \1;', lines[i])
    return '\n'.join(lines)


@register(order=65)
def filter_ida_comments(code, ctx):
    """Filter IDA header comments (before function definition line)."""
    lines = code.split('\n')
    return '\n'.join(l for l in lines if not l.strip().startswith('// between_std_methods'))
