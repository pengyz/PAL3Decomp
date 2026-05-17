"""Stage 1: Function signature/structure modification (before OOP transform).

Modifies the function definition line and structure.
Does NOT touch the function body content (that's Stage 3/4).
"""
import re


def run(code, ctx):
    """Apply structural transforms to function code."""
    lines = code.split('\n')

    # 1. Filter IDA header comments
    lines = [l for l in lines if not l.strip().startswith('// between_std_methods')]

    # 2. Find the function definition line
    cls_name = ctx.cls_name
    method_name = ctx.method_name
    cls_variants = [cls_name]
    if cls_name.startswith('_'):
        cls_variants.append(cls_name[1:])

    func_line_idx = 0
    for idx, l in enumerate(lines):
        if '(' in l and (any(cv + '::' in l for cv in cls_variants) or 'sub_' in l):
            func_line_idx = idx
            break

    # 3. Fix function definition line
    if lines and method_name:
        first_line = lines[func_line_idx]
        full_method = '%s::%s' % (cls_name, method_name)

        # Replace sub_XXXXX with correct name
        first_line = re.sub(r'\bsub_[0-9A-Fa-f]+\b', full_method, first_line, count=1)

        # Fix IDA stripping leading underscore
        for cv in cls_variants:
            if cv != cls_name and cv + '::' in first_line:
                first_line = first_line.replace(cv + '::', cls_name + '::')

        # Remove return type for ctor/dtor
        if ctx.is_ctor or ctx.is_dtor:
            first_line = re.sub(
                r'^.*?\b(%s::%s)' % (re.escape(cls_name), re.escape(method_name)),
                r'\1', first_line)

        lines[func_line_idx] = first_line

    # 4. Ctor/dtor: remove 'return expr;'
    if method_name and (ctx.is_ctor or ctx.is_dtor):
        for i in range(len(lines)):
            lines[i] = re.sub(r'^\s*return\s+(.+);', r'  \1;', lines[i])

    # 5. Fix function signature: remove this param, strip CC
    if lines:
        first = lines[func_line_idx]
        first = re.sub(r'\s*__thiscall\s*', ' ', first)
        first = re.sub(r'\s*__cdecl\s*', ' ', first)
        first = re.sub(r'\s*__stdcall\s*', ' ', first)
        first = re.sub(r'\s*__fastcall\s*', ' ', first)
        first = re.sub(r'\s*__userpurge\s*', ' ', first)
        first = re.sub(r'\s*__usercall\s*', ' ', first)
        # Remove "ClassName *this" from params
        first = re.sub(r'\(\s*\w[\w\s]*\*+\s*this\s*,\s*', '(', first)
        first = re.sub(r'\(\s*\w[\w\s]*\*+\s*this\s*\)', '()', first)
        # Destructors: strip all params
        if ctx.is_dtor:
            first = re.sub(r'\([^)]*\)', '()', first)
        first = re.sub(r'  +', ' ', first).strip()
        lines[func_line_idx] = first

    return '\n'.join(lines)
