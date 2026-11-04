"""B 导入转换层变体键解析（RED-0 · task-1-brief.md Task 1）。

真值锚（语料证据）：
- data/annotations/structs/PalScript.json:659,666 —— 键 '144_1'/'144_2'（off[_variant] 位面键谱系）
- data/annotations/structs/SceneMgr.json:138 —— 键 '50814_0'
- data/annotations/structs/scVARIANT_data.json —— 键 '0'/'0_1'

病灶实锤（ghidra_track/import_annotation.py:59 旧 `int(k)`）：PEP 515 下划线数字
分隔符语义 ⇒ int('144_1')==1441、int('50814_0')==508140、int('0_1')==1 —— 变体键被
int() 直吞即**发明偏移**（144 的 float 位面视图被错置到 1441）。
键谱系语义（pipeline/check_annotations.py:607 `base_offset[_variant]`）：变体键的存储
偏移归基键（'144'→144），不是独立偏移。
"""
from ghidra_track.import_annotation import parse_variant_key, build_import_plan


def test_variant_key_not_int_coerced():
    # '144_1' 不得变 1441（发明偏移）；'50814_0' 不得变 508140
    assert parse_variant_key('144_1') != 1441
    assert parse_variant_key('50814_0') != 508140


def test_plain_offset_key_passes():
    assert parse_variant_key('448') == 448


def test_variant_key_returned_as_is():
    # Step 3 契约：含 '_'/非数字 = 原样返回（下游显式处理，禁 int() 吞）
    assert parse_variant_key('144_1') == '144_1'
    assert parse_variant_key('50814_0') == '50814_0'
    assert parse_variant_key('0_1') == '0_1'
    # hex 异形键同样原样返回——禁 lstrip('0x') 前导零陷阱（'0x0abc'→'abc' 会丢位）
    assert parse_variant_key('0x0abc') == '0x0abc'


def test_int_key_passthrough():
    # list 形 known_members 的 int 键（offset 直存）原样直通
    assert parse_variant_key(144) == 144


def test_no_invented_offset_in_plan():
    # 真 bug call-site 回归（真值锚 PalScript.json:659,666）：变体键成员不得以发明偏移进 plan
    structs = {'PalScript': {'size': 1024, 'known_members': {
        '144': {'name': 'm_pCurrentTask', 'type': 'int', 'union': True},
        '144_1': {'name': 'm_pCurrentTask_f', 'type': 'float', 'union': True},
        '144_2': {'name': 'm_pCurrentTask_p', 'type': 'char *', 'union': True},
    }}}
    plan = build_import_plan(structs=structs)
    [ds] = [op for op in plan if op['kind'] == 'define_struct']
    offsets = [m['offset'] for m in ds['members']]
    assert 1441 not in offsets and 1442 not in offsets  # 禁发明偏移（144_1→1441 实锤）
    assert offsets == [144]  # 基键正常落位；变体视图形补（union 折叠）归 Task 7/8（missing-shapes）


def test_variant_only_group_no_invented_offset():
    # 真值锚 SceneMgr.json:138 键 '50814_0'（无基键 '50814'）：不得发明 508140 偏移/union 名
    structs = {'SceneMgr': {'size': 65536, 'known_members': {
        '50814_0': {'name': 'm_pRoleSystemArray', 'type': {'union': [
            {'type': 'RoleSystem *', 'name': 'm_pRoleSystemArrayEnd'},
            {'type': 'RoleSystem *', 'name': 'm_pRoleSystemArrayBegin'},
        ]}},
    }}}
    plan = build_import_plan(structs=structs)
    for op in plan:
        if op['kind'] == 'define_struct':
            assert 508140 not in [m['offset'] for m in op['members']]
        if op['kind'] == 'define_union':
            assert '508140' not in op['name']  # UNION 名后缀=真偏移，禁发明
