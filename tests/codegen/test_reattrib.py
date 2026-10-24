"""重归属判定 + 调用形转写（R91·2026-10-24 战役 Phase 1，TDD）。

对应 spec: docs/specs/2026-10-24-free-function-reattribution-campaign.md §3
门语义见 pipeline/gen/reattrib.py 模块 docstring。
"""
import os
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / "pipeline" / "gen"))
sys.path.insert(0, str(REPO / "pipeline" / "gen" / "stages"))

from reattrib import (ROUTED_BATCH0_NAMES, build_attribution_index,
                      decide_routing, _nonthis_param_count)

# ---------------------------------------------------------------- 谓词判定

def _mk_index():
    structs = [
        ('RoleSystem.json', {'name': 'RoleSystem', 'methods': {
            '0x0041C090': {'name': 'FlushCommandQueue',
                           'signature': 'int __thiscall(RoleSystem *this)'}}}),
        ('PAL_GDB.json', {'name': 'PAL_GDB', 'methods': {
            '0x479080': {'name': 'GDB_GetRoleNum', 'signature': 'int __thiscall(int)'},
            '0x4791E0': {'name': 'GDB_GetRoleNum', 'signature': 'int __thiscall(int)'},
            '0x479200': {'name': 'GDB_GetItemNum', 'signature': 'int __thiscall(int)'},
            '0x479210': {'name': 'GDB_GetItemNum', 'signature': 'int __thiscall(int)'}}}),
        ('Actor.json', {'name': 'Actor', 'methods': {
            '0x00536160': {'name': 'SetParam',
                           'signature': 'int __thiscall(Actor *this, int a, int b)'}}}),
    ]
    return build_attribution_index(iter(structs))


def test_index_builds_addr_and_multi():
    idx, multi = _mk_index()
    assert idx[0x41C090] == ('RoleSystem', 'FlushCommandQueue')
    assert len(multi[('PAL_GDB', 'GDB_GetRoleNum')]) == 2


def test_route_hit_and_gates():
    idx, multi = _mk_index()
    cands = [
        ('FlushCommandQueue', '0x0041C090', 'int __thiscall(RoleSystem *this)'),
        # G2 撞名：PAL_GDB 两个同名地址 ⇒ 双双不路由（C2084）
        ('GDB_GetRoleNum', '0x479080', 'int __thiscall(int)'),
        ('GDB_GetItemNum', '0x479200', 'int __thiscall(int)'),
        # G3 名字漂移：decomp 名 != 注解名 ⇒ 不路由
        ('todo_004B7560', '0x00536160', 'int __thiscall(int)'),
        # G4 待裁排除
        ('ReleaseAllTextures', '0x00536160', 'int __thiscall(int)'),
    ]
    os.environ['REATTRIB_SCOPE'] = 'all'
    try:
        by_addr, by_name = decide_routing(cands, idx, multi)
    finally:
        os.environ['REATTRIB_SCOPE'] = 'batch0'
    assert 0x41C090 in by_addr
    assert by_name['FlushCommandQueue'] == ('RoleSystem', 'FlushCommandQueue', 0)
    assert 'GDB_GetRoleNum' not in by_name and 'GDB_GetItemNum' not in by_name
    assert 'todo_004B7560' not in by_name
    assert 'ReleaseAllTextures' not in by_name


def test_scope_all_default_and_batch0_explicit():
    """默认 scope=all（44 条验证后翻转）；batch0 保守集仍可显式选用."""
    idx, multi = _mk_index()
    cands = [('SetParam', '0x00536160', 'int __thiscall(Actor *this, int a, int b)')]
    # 默认 all：SetParam（类一致、在名单）路由
    by_addr, by_name = decide_routing(cands, idx, multi)
    assert by_name.get('SetParam') == ('Actor', 'SetParam', 2)
    # 显式 batch0：同样路由（SetParam 在名单）
    by_addr2, _ = decide_routing(cands, idx, multi, scope='batch0')
    assert 0x00536160 in by_addr2
    # 显式 batch0 拒绝非名单名
    idx3, multi3 = _mk_index()
    structs = [('RoleSystem.json', {'name': 'RoleSystem', 'methods': {
        '0x0041C091': {'name': 'SomeOtherMethod',
                       'signature': 'int __thiscall(RoleSystem *this)'}}})]
    idx3, multi3 = build_attribution_index(iter(structs))
    cands3 = [('SomeOtherMethod', '0x0041C091', 'int __thiscall(RoleSystem *this)')]
    by_addr3, _ = decide_routing(cands3, idx3, multi3, scope='batch0')
    assert not by_addr3


def test_scope_off_disables():
    idx, multi = _mk_index()
    os.environ['REATTRIB_SCOPE'] = 'off'
    try:
        by_addr, by_name = decide_routing(
            [('FlushCommandQueue', '0x0041C090', 'int __thiscall(RoleSystem *this)')],
            idx, multi)
    finally:
        os.environ['REATTRIB_SCOPE'] = 'batch0'
    assert not by_addr and not by_name


def test_nonthis_param_count():
    assert _nonthis_param_count('int __thiscall(RoleSystem *this)') == 0
    assert _nonthis_param_count('int __thiscall(Actor *this, int a, int b)') == 2
    assert _nonthis_param_count('void __thiscall(int this, char *a2)') == 1
    assert _nonthis_param_count('int __thiscall(_DWORD *this, RECT *a2, int a3)') == 2
    assert _nonthis_param_count('garbage') is None


def test_batch0_list_matches_review():
    assert 'FlushCommandQueue' in ROUTED_BATCH0_NAMES
    assert 'SetEnable' not in ROUTED_BATCH0_NAMES      # 386 裸站，批 2
    assert 'ReleaseAllTextures' not in ROUTED_BATCH0_NAMES  # G4 待裁


def test_value_reference_gate_g6():
    """G6：名字被当值传递（回调/取址）⇒ 不路由（ProcCommonTask__ovl 实证）."""
    idx, multi = _mk_index()
    cands = [('FlushCommandQueue', '0x0041C090', 'int __thiscall(RoleSystem *this)')]
    corpus = 'todo(v4, (int)FlushCommandQueue, 0, 0);\n'   # 值引用（非调用）
    by_addr, by_name = decide_routing(cands, idx, multi, corpus_text=corpus)
    assert not by_addr and not by_name
    # 调用形态（含空格）不误伤
    corpus2 = 'FlushCommandQueue (r);\n x = FlushCommandQueue(r2);\n'
    by_addr2, by_name2 = decide_routing(cands, idx, multi, corpus_text=corpus2)
    assert 0x41C090 in by_addr2


def test_this_type_gate_g7():
    """G7：decomp this 型 != 归属类（泛型 _BYTE*）⇒ 不路由（GetUpdateFlag +14 实证）."""
    idx, multi = _mk_index()
    cands = [
        ('FlushCommandQueue', '0x0041C090', 'int __thiscall(RoleSystem *this)'),   # 类一致 ✓
        ('SetParam', '0x00536160', 'int __thiscall(_BYTE *this, int a)'),          # 泛型 ✗
    ]
    by_addr, by_name = decide_routing(cands, idx, multi)
    assert 0x41C090 in by_addr
    assert 'SetParam' not in by_name


def test_ovl_suffix_gate_g8():
    """G8：__ovl_ 后缀自由名 ⇒ 不路由（Create__ovl_1 头体 ovl 失配 C2039 ×3 实证）."""
    idx, multi = _mk_index()
    structs = [('ARC_PlayerAtt.json', {'name': 'ARC_PlayerAtt', 'methods': {
        '0x0048A2B0': {'name': 'Create__ovl_1',
                       'signature': 'int __thiscall(ARC_PlayerAtt *this)'}}})]
    idx2, multi2 = build_attribution_index(iter(structs))
    cands = [('Create__ovl_1', '0x0048A2B0',
              'int __thiscall(ARC_PlayerAtt *this)')]
    by_addr, by_name = decide_routing(cands, idx2, multi2)
    assert not by_addr and not by_name


# ---------------------------------------------------------------- 调用形转写

def test_rewrite_bare_and_cast_forms():
    from ast_transform import rewrite_routed_free_calls
    routed = {'FlushCommandQueue': ('RoleSystem', 'FlushCommandQueue', 0),
              'SetParam': ('Actor', 'SetParam', 2)}
    code = (
        'int f(RoleSystem *r) {\n'
        '  FlushCommandQueue(r);\n'
        '  SetParam((Actor *)this->m_pActor, 1, 2);\n'
        '  p->FlushCommandQueue();\n'          # 成员形态不动
        '  RoleSystem::FlushCommandQueue();\n'  # 限定形态不动
        '  Other(x);\n'                          # 非路由名不动
        '  SetParam(r, 1);\n'                    # 元数不符不动（1+1!=3）
        '}'
    )
    out = rewrite_routed_free_calls(code, routed)
    assert '(((RoleSystem *)r))->RoleSystem::FlushCommandQueue()' in out
    assert '(((Actor *)this->m_pActor))->Actor::SetParam(1, 2)' in out
    assert 'p->FlushCommandQueue()' in out
    assert 'RoleSystem::FlushCommandQueue()' in out
    assert 'Other(x)' in out
    assert 'SetParam(r, 1)' in out


def test_rewrite_bare_form_nested_args_balanced():
    from ast_transform import rewrite_routed_free_calls
    routed = {'SetParam': ('Actor', 'SetParam', 2)}
    code = 'SetParam(w, g(x, y), 1);\n'
    out = rewrite_routed_free_calls(code, routed)
    assert '(((Actor *)w))->Actor::SetParam(g(x, y), 1)' in out


def test_rewrite_recv_grammar_exclusions():
    from ast_transform import rewrite_routed_free_calls
    routed = {'FlushCommandQueue': ('RoleSystem', 'FlushCommandQueue', 0)}
    code = (
        '&FlushCommandQueue(v);\n'        # 取址不动
        'x = a && FlushCommandQueue(v);\n'  # && 后不动（保守）
    )
    out = rewrite_routed_free_calls(code, routed)
    assert 'FlushCommandQueue(v)' in out
