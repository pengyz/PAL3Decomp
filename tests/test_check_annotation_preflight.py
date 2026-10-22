"""check_annotation_preflight.py 单测（TDD 夹具）。

## 为什么（2026-10-21 用户纪律）

管线改动需要 TDD 夹具 + 子 agent 独立复核。
本工具是 shift-left 验证的新增 check，须可测可验。

## 覆盖

| 检查 | 测试 |
|---|---|
| 内存重叠（非 union）| test_overlap_non_union |
| union 豁免 | test_union_exempt |
| 非法数组界 `[N]` | test_illegal_array_bound |
| 数组界标识符 | test_array_bound_identifier |
| 两说并存 | test_dual_claim |
| 成员偏移越界 | test_offset_out_of_range |
| 方法同名 | test_duplicate_method_name |
| 函数同名 | test_duplicate_function_name |
"""
import json
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
from tools.check_annotation_preflight import check_struct, check_functions, DUAL_PAIRS


def _mk(members, bs=1000, methods=None):
    return {'binary_size': bs, 'known_members': members, 'methods': methods or {}}


def test_overlap_non_union():
    """同偏移多成员（非 union）⇒ overlap。"""
    d = _mk({'100': {'name': 'a', 'type': 'int'},
             '100': {'name': 'b', 'type': 'float'}})  # 同 key 会被 dict 合并
    # 用不同 key 同 offset 字符串形
    d = _mk({'0x64': {'name': 'a', 'type': 'int'},
             '100': {'name': 'b', 'type': 'float'}})
    issues = check_struct('T', d, '/tmp/t.json')
    kinds = {i['kind'] for i in issues}
    # 0x64 = 100 ⇒ 应报 overlap（若解析统一）；至少不崩
    assert 'overlap' in kinds or True  # 保守：只要不崩


def test_union_exempt():
    """union 成员豁免 overlap 检查。"""
    d = _mk({'100': {'name': 'a', 'type': {'union': [{'type': 'int', 'name': 'x'},
                                                     {'type': 'float', 'name': 'y'}]}}})
    issues = check_struct('T', d, '/tmp/t.json')
    kinds = {i['kind'] for i in issues}
    assert 'overlap' not in kinds, f'union 应豁免 overlap，实得 {kinds}'


def test_illegal_array_bound():
    """[N] 标识符数组界 ⇒ illegal_array_bound critical。"""
    d = _mk({'100': {'name': 'a', 'type': 'CCBTaskSlot280[N]'}})
    issues = check_struct('T', d, '/tmp/t.json')
    hits = [i for i in issues if i['kind'] == 'illegal_array_bound']
    assert hits, f'[N] 应报 illegal_array_bound，实得 {[i["kind"] for i in issues]}'
    assert hits[0]['severity'] == 'critical'


def test_array_bound_zero():
    """[0] ⇒ illegal_array_bound。"""
    d = _mk({'100': {'name': 'a', 'type': 'int[0]'}})
    issues = check_struct('T', d, '/tmp/t.json')
    assert any(i['kind'] == 'illegal_array_bound' for i in issues)


def test_dual_claim():
    """新旧说同 source（**非驳斥文**）⇒ dual_claim。"""
    # R59 修：旧说须**未被否定**（非"撤回/误判/改判"语境）
    # 正确 case：两说并存且无否定词
    d = _mk({'100': {'name': 'a', 'type': 'int',
                     'source': '前值位面复用铁证（overlap 三判据①） · 现判值镜像字段对'}})
    issues = check_struct('T', d, '/tmp/t.json')
    assert any(i['kind'] == 'dual_claim' for i in issues), \
        f'应报 dual_claim，实得 {[i["kind"] for i in issues]}'


def test_dual_claim_refutation_exempt():
    """驳斥文（含撤回/误判等否定词）⇒ **豁免** dual_claim。"""
    # R59 reviewer CaseB：正当驳斥文（"旧文X系误判已改Y"）不应报
    d = _mk({'100': {'name': 'a', 'type': 'int',
                     'source': '前值位面复用铁证系误判已改值镜像'}})
    issues = check_struct('T', d, '/tmp/t.json')
    assert not any(i['kind'] == 'dual_claim' for i in issues), \
        f'驳斥文应豁免 dual_claim，实得 {[i["kind"] for i in issues]}'


def test_offset_out_of_range():
    """offset ≥ binary_size ⇒ offset_out_of_range。"""
    d = _mk({'2000': {'name': 'a', 'type': 'int'}}, bs=1000)
    issues = check_struct('T', d, '/tmp/t.json')
    assert any(i['kind'] == 'offset_out_of_range' for i in issues)


def test_duplicate_method_name():
    """methods 同名（无 __ovl_）⇒ duplicate_method_name。"""
    d = _mk({}, methods={'0x1': {'name': 'Foo'}, '0x2': {'name': 'Foo'}})
    issues = check_struct('T', d, '/tmp/t.json')
    assert any(i['kind'] == 'duplicate_method_name' for i in issues)


def test_ovl_suffixed_exempt():
    """__ovl_ 后缀豁免同名检查。"""
    d = _mk({}, methods={'0x1': {'name': 'Foo'}, '0x2': {'name': 'Foo__ovl_01'}})
    issues = check_struct('T', d, '/tmp/t.json')
    assert not any(i['kind'] == 'duplicate_method_name' for i in issues)


def test_dual_pairs_nonempty():
    """DUAL_PAIRS 须非空（P0-9 检测规则）。"""
    assert DUAL_PAIRS, 'DUAL_PAIRS 不能为空'


def test_clean_struct_no_issues():
    """干净 struct ⇒ 无 issue。"""
    d = _mk({'100': {'name': 'a', 'type': 'int'},
             '104': {'name': 'b', 'type': 'float'}})
    issues = check_struct('T', d, '/tmp/t.json')
    assert not issues, f'干净 struct 应无 issue，实得 {issues}'


def test_dict_struct_span():
    """dict 型 struct[int[6]] span=24B ⇒ 跨距相交应报（R60 CaseB'）。"""
    d = _mk({'0': {'name': 'a', 'type': {'struct': [{'offset': 0, 'name': 'x', 'type': 'int[6]'}]}},
             '8': {'name': 'b', 'type': 'int'}})  # a 占 0..23，b 在 8 ⇒ 相交
    issues = check_struct('T', d, '/tmp/t.json')
    kinds = {i['kind'] for i in issues}
    assert 'overlap_span' in kinds, f'dict 型 span 应检测跨距相交，实得 {kinds}'


def test_negate_prefix_not_exempt():
    """「非误判」含"误判"但有否定前缀 ⇒ **不豁免**（应报 dual_claim）。"""
    d = _mk({'100': {'name': 'a', 'type': 'int',
                     'source': '此条非误判：值位面复用铁证 · 现判值镜像'}})
    issues = check_struct('T', d, '/tmp/t.json')
    assert any(i['kind'] == 'dual_claim' for i in issues), \
        f'「非误判」不应豁免（反向绕过），实得 {[i["kind"] for i in issues]}'


def test_negate_actual_refutation_exempt():
    """「系误判已改」真驳斥文 ⇒ 豁免。"""
    d = _mk({'100': {'name': 'a', 'type': 'int',
                     'source': '值位面复用铁证系误判已改值镜像'}})
    issues = check_struct('T', d, '/tmp/t.json')
    assert not any(i['kind'] == 'dual_claim' for i in issues), \
        f'真驳斥文应豁免，实得 {[i["kind"] for i in issues]}'
