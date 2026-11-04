"""B 转换证明 Task 8：case-02 缺形 fixture+独立 oracle+链跑器（task-8-brief Step 1，TDD 红→绿）。

oracle 独立性（R8·防循环论证）：expected/facts_oracle.json=**手写**（来源逐行注
expected/README.md，禁从 annotation 脚本派生）；fixture_proof.run_fixture 跑
annotation→plan→facts 机械投影 vs 手写 oracle=零差（正确性锚）。
链路（控制器裁定·记账）：run_fixture=离线链证明（计划级）；活体全链=verify_b_import（T4）。
"""
import json
import pathlib

from ghidra_track.fixture_proof import run_fixture

_ROOT = pathlib.Path(__file__).resolve().parent.parent
_CASES = _ROOT / 'ghidra_track' / 'fixture' / 'cases'


def test_case01_oracle_zero_diff():
    r = run_fixture(str(_CASES / 'case-01-struct-union-overload'))
    assert r['verdict'] == 'PASS', 'case-01 零差: %s' % json.dumps(
        {k: v for k, v in r['diffs'].items() if v}, ensure_ascii=False)[:400]


def test_case02_oracle_zero_diff():
    r = run_fixture(str(_CASES / 'case-02-missing-shapes'))
    assert r['verdict'] == 'PASS', 'case-02 零差: %s' % json.dumps(
        {k: v for k, v in r['diffs'].items() if v}, ensure_ascii=False)[:600]


def test_case02_covers_missing_shapes():
    """case-02 必须真含缺形（防空 fixture 空过）：oracle 里能看到各形产物。"""
    o = json.loads((_CASES / 'case-02-missing-shapes' / 'expected' /
                    'facts_oracle.json').read_text())
    # 嵌套 union 产物
    assert 'UNION_Nested_4' in o['structs'], '嵌套 union 产物缺席'
    # inline-struct 产物（T7④）
    assert 'INLINE_Nested_8' in o['structs'], 'inline-struct 产物缺席'
    # adjudication 对胜者（rejected 败者禁出）
    assert o['functions']['0x402000']['name'] == 'winner_m'
    assert not any(f.get('name') == 'loser_m' for f in o['functions'].values()), \
        'rejected 败者禁入 oracle'
    # 占位名原样过
    assert any(f.get('name', '').startswith('_todo_') for f in o['functions'].values()), \
        '占位名缺席'
    # 变体键视图=域外（T1 裁定：变体视图出 plan，README 记载回补待 union 折叠）
    nested_members = o['structs']['Nested']['members']
    assert not any(m.get('name') == 'm_variant_view' for m in nested_members.values()), \
        '变体键视图不得入 oracle（converter 契约=域外）'


def test_oracle_handwritten_sources_documented():
    """oracle 来源逐行注 README（R8 独立性文档面）。"""
    for case in ('case-01-struct-union-overload', 'case-02-missing-shapes'):
        rd = _CASES / case / 'expected' / 'README.md'
        assert rd.exists(), '%s 缺 expected/README.md（oracle 来源注记）' % case
        assert '来源' in rd.read_text() or 'source' in rd.read_text().lower()
