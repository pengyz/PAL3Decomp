"""Transform pipeline runner.

Applies all registered transforms in order to a code string.
"""
from dataclasses import dataclass
from transforms import get_pipeline


@dataclass
class TransformContext:
    """Per-function metadata passed to each transform."""
    cls_name: str
    method_name: str
    sig: str
    is_ctor: bool
    is_dtor: bool
    is_free_function: bool


def make_context(cls_name, method_name, sig='', is_free=False):
    """Create a TransformContext from function info."""
    is_ctor = (method_name == cls_name) if cls_name else False
    is_dtor = (method_name == '~%s' % cls_name) if cls_name else False
    return TransformContext(
        cls_name=cls_name,
        method_name=method_name,
        sig=sig,
        is_ctor=is_ctor,
        is_dtor=is_dtor,
        is_free_function=is_free,
    )


def run_transforms(code, ctx):
    """Execute all registered transforms on code in order."""
    for transform_func in get_pipeline():
        code = transform_func(code, ctx)
    return code
