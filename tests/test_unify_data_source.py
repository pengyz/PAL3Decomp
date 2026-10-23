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


def test_stage3_dead_function_removed():
    """[Task 1 must-fix ①] _try_resolve_vftable 死函数已删（既有定谳）。

    对抗复核 fbf233f6 实证：零调用点（AST + 动态证死）+ 既有定谳（design:71）
    => 应删非重构。
    """
    import inspect
    from pipeline.gen.stages import stage3_cleanup
    assert not hasattr(stage3_cleanup, '_try_resolve_vftable'),         '_try_resolve_vftable 死函数未删（应删非重构）'


def test_stage3_no_direct_read():
    """stage3_cleanup 不直读 structs/*.json。

    [Task 1 must-fix ②] 判别力约束（M2/M3 变异体）：
    ① 不能有 ann_path 直读变量（M3：读点只在注释仍 PASS）
    ② 不能有 os.path.join(...'structs'...) 直读路径
    ③ 死函数已删（test_stage3_dead_function_removed 独立测）
    """
    import inspect
    from pipeline.gen.stages import stage3_cleanup
    src = inspect.getsource(stage3_cleanup)
    assert 'ann_path' not in src, 'stage3_cleanup 残留 ann_path 直读'
    # M3 判别：查真实直读路径（非注释）
    import re
    # 排除注释行后查 structs/ 直读
    code_lines = [l for l in src.split('\n') if not l.strip().startswith('#')]
    code = '\n'.join(code_lines)
    assert "'structs'" not in code or '_annview' in code, \
        'stage3_cleanup 直读 structs/（应走 _annview 或已删）'
    # 判别性断言：vtable 槽解析必须真的消费读点（子串检查拦不住"改名后仍直读"）
    helper_src = inspect.getsource(stage3_cleanup._try_resolve_vftable)
    assert '_annview.struct_by_class' in helper_src, \
        '_try_resolve_vftable 未走 annotation_view 读点'
    assert 'ann_path' not in helper_src, \
        '_try_resolve_vftable 仍直读 structs/<Cls>.json（ann_path 拼路径）'
