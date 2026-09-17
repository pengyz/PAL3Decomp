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

from ast_transform import transform_oop_calls, transform_coerce_calls
from data import store


def run(code, ctx):
    """Apply OOP call transformation."""
    code = transform_oop_calls(code, static_methods=store.static_methods,
                               cls_name=ctx.cls_name)
    # 【2026-09-15 加】COERCE_FLOAT/T 实参为**函数调用**时改用辅助函数
    # （宏内部对实参取地址，而 MSVC6 不允许对 rvalue 取地址 ⇒ C2102）。
    # 放在 OOP 变换**之后**：此时调用形态已稳定，再判"实参是不是调用"更准。
    code = transform_coerce_calls(code)
    return code
