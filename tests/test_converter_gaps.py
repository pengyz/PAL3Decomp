"""B 转换证明 Task 7：转换器六缺口修（task-7-brief Step 1，TDD 红→绿）。

真值锚（spec v2 §4 缺口表 + 复核实测）：
①adjudication 不消费（rejected 照灌——25367 三连实锤）
②define_global type 不转（plan_to_changeset 注释声称 set_global_type 实未发）
③skip/墓碑不消费（skip_flagged 照当正常函数 claim）
④inline-struct dict 降 byte（静默——须显式 define_struct 引用）
⑤owner 不转（方法归属维缺失）
⑥import_standard fail>0 未入分账不 exit 1（24 条 No transaction 仅计数）
"""
from ghidra_track.import_annotation import build_import_plan, merge_method_claims
from ghidra_track.plan_to_changeset import plan_to_changesets
from ghidra_track.import_standard import fail_rc


def _addr(i):
    return '0x401%03d' % i


# ① rejected 过滤 + tie-break prefer
def test_rejected_claim_skipped():
    ann = {'a.json': {'name': 'A', 'methods': {_addr(1): {'name': 'bad',
                                                          'adjudication': 'rejected'}}}}
    assert merge_method_claims(ann) == {}, 'rejected 败者禁入（不消费=不产出 claim）'


def test_rejected_vs_confirmed_winner():
    ann = {'a.json': {'name': 'A', 'methods': {_addr(1): {'name': 'loser',
                                                          'adjudication': 'rejected'}}},
           'b.json': {'name': 'B', 'methods': {_addr(1): {'name': 'winner',
                                                          'adjudication': 'confirmed'}}}}
    m = merge_method_claims(ann)
    assert m[_addr(1)]['name'] == 'winner', 'rejected 跳过+confirmed 胜'


def test_build_plan_excludes_rejected():
    funcs = {_addr(2): {'name': 'ghost', 'adjudication': 'rejected', 'signature': 'void g()'}}
    plan = build_import_plan(functions=funcs)
    assert not any(o['kind'] == 'set_name' for o in plan), \
        'rejected 函数禁入 plan（gen_plan 缺口①落地面）'


# ② 全局 type op
def test_global_type_op_emitted():
    plan = [{'kind': 'define_global', 'addr': '0x500000', 'name': 'g_X', 'type': 'int'}]
    ops = [o for b in plan_to_changesets(plan) for o in b['ops']]
    kinds = {o['op'] for o in ops}
    assert 'set_global_type' in kinds, '带 type 的 define_global 必须发 set_global_type'
    t = [o for o in ops if o['op'] == 'set_global_type'][0]
    assert t['type'] == 'int'


# ③ skip 消费
def test_skip_flagged_not_claimed():
    funcs = {_addr(3): {'name': 'skipped_fn', 'skip': True}}
    plan = build_import_plan(functions=funcs)
    assert not any(o['kind'] == 'set_name' and o.get('addr') == _addr(3) for o in plan), \
        'skip=True 函数禁当正常 claim（skip 语义消费）'


# ④ inline-struct dict 显式（禁静默 byte/dict 直通）
def test_inline_struct_dict_explicit():
    structs = {'C': {'name': 'C', 'binary_size': 16,
                     'known_members': {'0': {'name': 'm_inner',
                                             'type': {'struct': [
                                                 {'offset': 0, 'name': 'a', 'type': 'int'}]}}}}}
    plan = build_import_plan(structs=structs)
    unions_or_structs = [o for o in plan if o['kind'] in ('define_union', 'define_struct')
                         and o.get('name', '').startswith(('INLINE_', 'UNION_'))]
    members = [m for o in plan if o['kind'] == 'define_struct' for m in o['members']]
    inner = [m for m in members if m['name'] == 'm_inner']
    assert inner, 'inline 成员必须在'
    ty = inner[0]['type']
    assert isinstance(ty, str) and ty not in ('byte', 'undefined'), \
        'inline-struct dict 禁静默降级（须显式型名引用）: %r' % ty
    assert unions_or_structs, 'inline-struct 必须产显式 define_struct/union op'


# ⑤ owner 转
def test_owner_transferred_to_plan():
    funcs = {_addr(4): {'name': 'm', 'signature': 'void m()', 'owner': 'C', 'class': 'C'}}
    plan = build_import_plan(functions=funcs)
    named = [o for o in plan if o['kind'] == 'set_name']
    assert named and named[0].get('owner') == 'C', \
        'owner 维必须入 plan（归属效果可验）'


# ⑥ fail-loud
def test_fail_rc_loud():
    assert fail_rc(fails=0, accounted=0) == 0, '零 fail=过'
    assert fail_rc(fails=5, accounted=5) == 0, '全入分账=过'
    assert fail_rc(fails=5, accounted=3) == 1, '未入分账 fail>0 ⇒ exit 1（禁静默）'
    assert fail_rc(fails=24, accounted=0) == 1, '24 条 No transaction 形=必须响'
