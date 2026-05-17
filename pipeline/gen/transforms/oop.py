"""OOP call transformations.

Order 200-299: Convert IDA C-style calls to C++ member calls.
"""
import re
import os
import sys
from transforms import register
from data import store


@register(order=200)
def transform_oop_calls(code, ctx):
    """AST-based OOP conversion: Class::Method(obj, ...) -> obj->Method(...)."""
    if ctx.is_free_function:
        return code
    sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    from ast_transform import transform_oop_calls as _ast_transform
    return _ast_transform(code, static_methods=store.static_methods)


@register(order=210)
def remove_this_declaration(code, ctx):
    """Remove variable declarations for 'this' pointer."""
    if ctx.is_free_function or not ctx.cls_name:
        return code
    return re.sub(
        r'^\s*%s\s*\*\s*this\s*;.*$' % re.escape(ctx.cls_name),
        '', code, flags=re.MULTILINE)


@register(order=220)
def rename_this_in_free_funcs(code, ctx):
    """In free functions, 'this' is not valid in C++. Rename to '_this'."""
    if not ctx.is_free_function:
        return code
    return re.sub(r'\bthis\b', '_this', code)


@register(order=230)
def fix_ref_params(code, ctx):
    """Remove & for known reference-parameter method calls (gbengine API)."""
    _REF_METHODS = {
        'Rotate': {1, 2},
        'Translate': {1},
        'Scale': {1},
        'RightMultiply': {1},
        'LeftMultiply': {1},
        'RightTranslate': {1},
        'LeftTranslate': {1},
        'MakeMatrix': {1, 2, 3},
        'IntersectPlane': {1, 2},
        'IsColTriangle': {1, 2, 3, 4},
        'IsColOBB': {1},
        'IsColOBB_H': {1},
        'IsColAABB': {1},
        'PointWorldToScr': {2, 3},
        'PointScrToWorld': {2, 3},
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
