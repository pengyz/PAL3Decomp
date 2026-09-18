"""Transform pipeline: 5 deterministic stages.

Stage 1 - structural:     Function signature modification (before OOP)
Stage 2 - semantic:       OOP call rewrite (tree-sitter AST)
Stage 3 - cleanup:        Remove/comment IDA artifacts (depends on Stage 2)
Stage 4 - resolution:     AST-based identifier/type resolution (no text hacks)
Stage 5 - fixup:          Compiler compatibility patches (text-level, no AST)
"""
from dataclasses import dataclass
from stages import stage1_structural, stage2_semantic, stage3_cleanup
from stages import stage4_substitution, stage5_fixup


@dataclass
class TransformContext:
    cls_name: str
    method_name: str
    sig: str
    is_ctor: bool
    is_dtor: bool
    is_free_function: bool
    # 同一**输出文件**内共享的 stub 去重集合（由 emit_cpp 按文件创建）。
    # None ⇒ 不去重（旧行为，安全回退）。
    stub_registry: object = None


def make_context(cls_name, method_name, sig='', is_free=False, stub_registry=None):
    is_ctor = (method_name == cls_name) if cls_name else False
    is_dtor = (method_name == '~%s' % cls_name) if cls_name else False
    return TransformContext(
        cls_name=cls_name, method_name=method_name, sig=sig,
        is_ctor=is_ctor, is_dtor=is_dtor, is_free_function=is_free,
        stub_registry=stub_registry)


def run_transforms(code, ctx):
    """Execute 5 stages in strict order."""
    code = stage1_structural.run(code, ctx)
    code = stage2_semantic.run(code, ctx)
    code = stage3_cleanup.run(code, ctx)
    code = stage4_substitution.run(code, ctx)
    code = stage5_fixup.run(code, ctx)
    return code
