"""Unify Data Source（数据源统一到 annotation_view 单一读点）· 阶段 1 测试。

Spec: docs/specs/2026-10-23-unify-data-source.md（Task 1-5）
背景：CLAUDE.md「codegen 注解读取必须经单一读点 pipeline/gen/annotation_view.py」；
实测仍有 3 处直读（emit_headers / ast_transform / stage3_cleanup），本文件逐处清理。

⚠️ 判别力约束（2026-09-21 F3 教训，见 tests/test_advisory_wired_into_write_path.py 头注）：
纯源码子串检查零判别力（变异后仍 PASS）。故每条"不直读"断言除计划原文的
模块级子串检查外，**额外**对消费函数体内做判别性检查（必须出现读点调用 +
必须不出现旧直读局部变量），确保"回退成直读"的变异会被抓到。
"""
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
for _p in (REPO, os.path.join(REPO, 'pipeline', 'gen')):
    if _p not in sys.path:
        sys.path.insert(0, _p)


def test_stage3_no_direct_read():
    """stage3_cleanup 不直读 structs/*.json（走 annotation_view）。"""
    import inspect
    from pipeline.gen.stages import stage3_cleanup
    src = inspect.getsource(stage3_cleanup)
    assert 'structs/' not in src or '_annview' in src, \
        'stage3_cleanup 直读 structs/*.json（应走 annotation_view）'
    # 判别性断言：vtable 槽解析必须真的消费读点（子串检查拦不住"改名后仍直读"）
    helper_src = inspect.getsource(stage3_cleanup._try_resolve_vftable)
    assert '_annview.struct_by_class' in helper_src, \
        '_try_resolve_vftable 未走 annotation_view 读点'
    assert 'ann_path' not in helper_src, \
        '_try_resolve_vftable 仍直读 structs/<Cls>.json（ann_path 拼路径）'
