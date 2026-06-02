"""Stage 2: Semantic OOP rewrite (tree-sitter AST).

Converts Class::Method(obj, ...) -> obj->Method(...).
This is the only stage that produces NEW patterns (->ClassName(), ->__vftable->).
"""
import sys
import os

# Ensure ast_transform is importable
_gen_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _gen_dir not in sys.path:
    sys.path.insert(0, _gen_dir)

from ast_transform import transform_oop_calls
from data import store


def run(code, ctx):
    """Apply OOP call transformation."""
    return transform_oop_calls(code, static_methods=store.static_methods,
                               cls_name=ctx.cls_name)
