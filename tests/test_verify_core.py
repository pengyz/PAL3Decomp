"""B 转换证明 Task 3：verify_core 纯函数核（task-3-brief Step 1，TDD 红→绿）。

真值锚（spec v2 §1 docs/specs/2026-11-04-converter-proof-design.md）：
- R1 铁则：期望投影独立实现——verify_core 禁 import 转换器模块（共享 bug 双侧
  一致=diff 假绿；复核实锤例=变体键 int('144_1') 双侧同错证成"正确"）。
- extra 域过滤：B 侧自动分析产物名（FUN_/AUTO_/thunk_）不计 extra（否则恒红）。
- 归一：地址 int 归一切片 [2:]（禁 lstrip('0x') 前导零陷阱）。
- 归并 tie-break 与 Task 2 同语义但代码独立：owner>confirmed>sorted 文件名序>首个。
"""
import ast
import json
import os
import pathlib

from ghidra_track.verify_core import (
    diff_facts,
    norm_addr,
    norm_facts,
    project_ann_facts,
)

_ROOT = pathlib.Path(__file__).resolve().parent.parent


def test_norm_addr_no_lstrip_trap():
    assert norm_addr('0x00523b90') == 0x523b90
    assert norm_addr('0x0abc') == 0x0abc, "禁 lstrip('0x')：'0x0abc' 不得丢前导 0"
    assert norm_addr('401000') == 0x401000


def test_extra_filtered():
    d = diff_facts({}, {'functions': {1: {'name': 'FUN_00400001'}}})
    assert d['extra'] == [], '自动名不计 extra（否则恒红）'
    d2 = diff_facts({}, {'functions': {2: {'name': 'AUTO_x'}, 3: {'name': 'thunk_y'}}})
    assert d2['extra'] == [], 'AUTO_/thunk_ 同滤'


def test_diff_catches_rename():
    exp = {'functions': {0x401000: {'name': 'Foo', 'signature': 'void f()'}}}
    act = {'functions': {0x401000: {'name': 'Bar', 'signature': 'void f()'}}}
    d = diff_facts(exp, act)
    assert d['missing'] == [] and d['extra'] == []
    assert len(d['changed']) == 1
    c = d['changed'][0]
    assert c['path'] == 'functions/0x401000.name'
    assert c['expected'] == 'Foo' and c['actual'] == 'Bar'


def test_diff_catches_offset_shift():
    exp = {'structs': {'S': {'size': 8, 'members': {4: {'name': 'm_b', 'type': 'int'}}}}}
    act = {'structs': {'S': {'size': 8, 'members': {8: {'name': 'm_b', 'type': 'int'}}}}}
    d = diff_facts(exp, act)
    assert any('members' in x['path'] and x['reason'] != 'no carrier' for x in d['changed']) or \
           any('m_b' == (x['expected'] or {}).get('name') if isinstance(x['expected'], dict) else False
               for x in d['changed']) or d['missing'], \
        '偏移漂移必须被抓（missing/changed 至少一路）'


def test_diff_match_counts():
    exp = {'globals': {0x500000: {'name': 'g_X', 'type': 'int'}}}
    act = {'globals': {0x500000: {'name': 'g_X', 'type': 'int'}}}
    d = diff_facts(exp, act)
    assert d['missing'] == [] and d['changed'] == [] and d['extra'] == []
    assert len(d['match']) == 1


def test_adjudication_winner_semantics(tmp_path):
    """假绿反例钉（R1）：同址双认领——expected 取 confirmed 胜者；
    actual 若为败者名 ⇒ changed（若期望侧复用败者则此测必红）。"""
    s = tmp_path / 'structs'
    s.mkdir()
    (s / 'a_loser.json').write_text(json.dumps(
        {'name': 'Z_cls', 'methods': {'0x401000': {'name': 'loser_name'}}}))
    (s / 'b_winner.json').write_text(json.dumps(
        {'name': 'A_cls', 'methods': {'0x401000': {'name': 'winner', 'adjudication': 'confirmed'}}}))
    exp = project_ann_facts(str(tmp_path))
    assert exp['functions'][0x401000]['name'] == 'winner', 'confirmed 胜者（tie-break 期望侧独立实现）'
    act = {'functions': {0x401000: {'name': 'loser_name'}}}
    d = diff_facts(exp, act)
    assert len(d['changed']) == 1 and d['changed'][0]['expected'] == 'winner', \
        '败者名入 actual 必须 changed（双侧独立才有判别力）'


def test_unverifiable_requires_reason():
    """无载体字段必须进 unverifiable 且带 reason——禁静默丢（R4）。"""
    exp = {'functions': {0x401000: {'name': 'F', 'evidence': 'A 级取证串'}}}
    act = {'functions': {0x401000: {'name': 'F'}}}
    d = diff_facts(exp, act)
    assert d['changed'] == [], 'evidence 非可比字段'
    assert len(d['unverifiable']) == 1
    u = d['unverifiable'][0]
    assert u['reason'], 'unverifiable 必须带理由（无理由=红）'


def test_norm_facts_addr_keys_int():
    f = {'functions': {'0x401000': {'name': 'F'}}, 'globals': {'0x500000': {'name': 'g'}}}
    n = norm_facts(f)
    assert 0x401000 in n['functions'] and 0x500000 in n['globals']


def test_verify_core_has_no_converter_imports():
    src = pathlib.Path('ghidra_track/verify_core.py').read_text()
    tree = ast.parse(src)
    for node in ast.walk(tree):
        if isinstance(node, ast.ImportFrom):
            assert not any(m in (node.module or '') for m in
                           ('gen_plan', 'import_annotation', 'plan_to_changeset',
                            'import_standard')), 'R1 铁则：禁 import 转换器'
        if isinstance(node, ast.Import):
            for a in node.names:
                assert not any(m in (a.name or '') for m in
                               ('gen_plan', 'import_annotation', 'plan_to_changeset',
                                'import_standard')), 'R1 铁则：禁 import 转换器'
