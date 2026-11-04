"""①改名落地（T10 双根因修·expect 乐观锁+非标识符通路）。

dryRun 实锤（2026-11-04）：rename_function 需 expect={name: 现名} 且 name 过
ProposalNorm.IDENT（字母/数字/_ ≤128）——注解的 ~dtor/?mangled 名被拒。
两阶段：read 现名 → ident 名走 changeset(带 expect) · 非 ident 名走 create_label
（标准工具面——非旁路，fixture 时代已证 create_label 收任意名）。
"""
from ghidra_track.import_standard import is_ident, split_renames
from ghidra_track.plan_to_changeset import plan_to_changesets


def test_is_ident():
    assert is_ident('Foo_bar123')
    assert is_ident('_x')
    assert not is_ident('~AStarPathFinder'), 'dtor 名非 ident'
    assert not is_ident('?fixture_get@@YAHXZ'), 'mangled 非 ident'
    assert not is_ident('1abc'), '数字开头非 ident'
    assert not is_ident('a b'), '含空格非 ident'
    assert not is_ident('x' * 129), '>128 非 ident'


def test_split_expect_from_readback():
    ops = [{'kind': 'set_name', 'addr': '0x401000', 'name': 'GoodName'},
           {'kind': 'set_name', 'addr': '0x401030', 'name': '~AStarPathFinder'},
           {'kind': 'set_func_sig', 'addr': '0x401000', 'name': 'GoodName'}]
    current = {0x401000: 'FUN_00401000', 0x401030: 'FUN_00401030'}
    cs0 = [o for b in plan_to_changesets(ops) for o in b['ops']]  # 真实管线序
    cs, labels = split_renames(cs0, current)
    # ident 名 → changeset 带 expect（现名）
    rn = [o for o in cs if o['op'] == 'rename_function']
    assert len(rn) == 1 and rn[0]['expect'] == {'name': 'FUN_00401000'}, rn
    # 非 ident 名 → label 面（禁进 changeset）
    assert len(labels) == 1
    assert labels[0] == {'address': '0x401030', 'name': '~AStarPathFinder'}
    # 非 set_name op 不动
    assert any(o['op'] == 'set_prototype' for o in cs)


def test_split_missing_current_fails_loud():
    # 现名读不到=禁盲发 expect（乐观锁语义）→ 归 label 面兜底（create_label 无 expect 需求）
    ops = [{'kind': 'set_name', 'addr': '0x409999', 'name': 'NewName'}]
    cs0 = [o for b in plan_to_changesets(ops) for o in b['ops']]
    cs, labels = split_renames(cs0, {})
    assert not any(o['op'] == 'rename_function' for o in cs)
    assert labels and labels[0]['address'] == '0x409999', '现名缺失=label 面兜底'
