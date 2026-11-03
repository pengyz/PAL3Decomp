"""转换器 v2（2026-11-03 标准通路）：plan → apply_changeset 批（≤250/批·同目标禁双 op）。
纯函数先行（R15）。"""

from ghidra_track.plan_to_changeset import plan_to_changesets


def test_op_mapping():
    plan = [
        {'kind': 'set_name', 'addr': '0x401000', 'name': 'Foo'},
        {'kind': 'set_func_sig', 'addr': '0x401000', 'name': 'Foo', 'ret': 'void', 'params': [], 'conv': '__cdecl'},
        {'kind': 'define_global', 'addr': '0x500000', 'name': 'g_X'},
    ]
    batches = plan_to_changesets(plan)
    ops = [o for b in batches for o in b['ops']]
    kinds = {o['op'] for o in ops}
    assert 'rename_function' in kinds or 'rename_global' in kinds
    assert 'set_prototype' in kinds


def test_batch_limit_250():
    plan = [{'kind': 'set_name', 'addr': '0x401%03d' % i, 'name': 'F%d' % i} for i in range(600)]
    batches = plan_to_changesets(plan)
    assert all(len(b['ops']) <= 250 for b in batches)
    assert sum(len(b['ops']) for b in batches) == 600


def test_same_target_dedup_keeps_last():
    plan = [
        {'kind': 'set_name', 'addr': '0x401000', 'name': 'A'},
        {'kind': 'set_name', 'addr': '0x401000', 'name': 'B'},
    ]
    batches = plan_to_changesets(plan)
    ops = [o for b in batches for o in b['ops']]
    renames = [o for o in ops if o['op'] in ('rename_function', 'rename_global')]
    assert len(renames) == 1 and renames[0]['name'] == 'B'
