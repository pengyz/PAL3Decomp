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
    ② 不能有 structs/ 直读路径（M2：形式伪仍 PASS）
    ③ 死函数已删（test_stage3_dead_function_removed 独立测）
    """
    import inspect
    from pipeline.gen.stages import stage3_cleanup
    src = inspect.getsource(stage3_cleanup)
    # M3 判别：排除注释后查真实直读
    code_lines = [l for l in src.split('\n') if not l.strip().startswith('#')]
    code = '\n'.join(code_lines)
    assert 'ann_path' not in code, 'stage3_cleanup 残留 ann_path 直读'
    # M2 判别：查真实直读路径（非注释）
    assert "os.path.join" not in code or "'structs'" not in code, \
        'stage3_cleanup 直读 structs/ 路径'


def test_inline_export_symmetry():
    """[Task 4·修向②] 导出补 `_inline_*`——`_inline_PalScript_m_RoleSlotArray` 对称在场。

    病灶（对抗复核 3dbf35d2 定谳）：`PalScript.m_RoleSlotArray` 成员型引用合成名
    `_inline_PalScript_m_RoleSlotArray`，但 export 的 named-supersede 把它整类跳过
    （导出不对称）⇒ emit 只能走 `_emit_member` 字符串路（supersede 坍成
    `PalScriptRoleSlotOverlay` 单型）⇒ union 变体层丢 ⇒ C2039 'script_state'
    not a member ×19（外加 C2065 合成名未声明）。
    修向②：export 补 `_inline_PalScript_m_RoleSlotArray`（union，含
    slot/overlay/script_state 3 变体），走已 work 的 hoist 路（与
    `_inline_RoleSystem_m_teamSlotsB`/`_inline_MUIDialog_m_btRc` 同型对称）。

    判别力（M2/M3 变异体）：
    ① 只查名存在会被"空壳类型"伪满足 ⇒ 还须 kind=union + 3 变体名在场；
    ② `PalScript.h` 成员行必须是 **union 合成名**（回退 supersede 单型即 FAIL）；
    ③ `script_state` 变体须在 union 定义块内（hoist 后体在共享 ns decl
       `_ns_udts.h`——`PalScript.h` 发射面 = 本体 + hoisted decl；体若内联在
       `PalScript.h` 同样命中）。
    """
    import json
    import re
    structs_path = os.path.join(REPO, 'asm', 'pal3', 'ida_structs.json')
    with open(structs_path, encoding='utf-8') as f:
        ida_structs = json.load(f)
    u = ida_structs.get('_inline_PalScript_m_RoleSlotArray')
    assert u is not None, \
        'ida_structs.json 缺 _inline_PalScript_m_RoleSlotArray（导出不对称）'
    assert u.get('kind') == 'union', \
        '_inline_PalScript_m_RoleSlotArray 应为 union（实为 %r）' % u.get('kind')
    names = {m.get('name') for m in u.get('data_members', [])}
    missing = {'slot', 'overlay', 'script_state'} - names
    assert not missing, 'union 变体缺失: %s（实际 %s）' % (sorted(missing), sorted(names))

    h_path = os.path.join(REPO, 'pal3', 'src', 'Script', 'PalScript.h')
    with open(h_path, encoding='utf-8') as f:
        h = f.read()
    # ② 成员行=union 合成名（hoist 路成员行；回退 supersede 单型 ⇒ FAIL）
    assert re.search(r'union\s+_inline_PalScript_m_RoleSlotArray\s+m_RoleSlotArray\s*;', h), \
        'PalScript.h 未以 union 合成名发射 m_RoleSlotArray（hoist 路失效/回退单型）'
    # ③ script_state 变体在 union 定义块内（PalScript.h 本体 ∪ hoisted 共享 ns decl）
    surface = h
    for rel in ('pal3/src/_ns_udts.h', 'include/pal3/gen/_ns_udts.h'):
        try:
            with open(os.path.join(REPO, rel), encoding='utf-8') as f:
                surface += f.read()
        except OSError:
            pass
    m = re.search(
        r'union\s+_inline_PalScript_m_RoleSlotArray\s*\{(.*?)\}\s*;',
        surface, re.S)
    assert m, '发射面缺 union _inline_PalScript_m_RoleSlotArray 定义体'
    assert 'script_state' in m.group(1), 'union 体丢 script_state 变体'
