"""Transform pipeline: 4 deterministic stages.

Stage 1 - structural:    Function signature modification (before OOP)
Stage 2 - semantic:      OOP call rewrite (tree-sitter AST)
Stage 3 - cleanup:       Remove/comment IDA artifacts (depends on Stage 2)
Stage 4 - substitution:  Pure text replacement (no context dependency)
"""
from dataclasses import dataclass
from stages import stage1_structural, stage2_semantic, stage3_cleanup, stage4_substitution


@dataclass
class TransformContext:
    cls_name: str
    method_name: str
    sig: str
    is_ctor: bool
    is_dtor: bool
    is_free_function: bool


def make_context(cls_name, method_name, sig='', is_free=False):
    is_ctor = (method_name == cls_name) if cls_name else False
    is_dtor = (method_name == '~%s' % cls_name) if cls_name else False
    return TransformContext(
        cls_name=cls_name, method_name=method_name, sig=sig,
        is_ctor=is_ctor, is_dtor=is_dtor, is_free_function=is_free)


def run_transforms(code, ctx):
    """Execute 4 stages in strict order."""
    code = stage1_structural.run(code, ctx)
    code = stage2_semantic.run(code, ctx)
    code = stage3_cleanup.run(code, ctx)
    code = stage4_substitution.run(code, ctx)
    return code
