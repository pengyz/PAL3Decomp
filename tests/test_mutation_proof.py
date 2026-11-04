"""B 转换证明 Task 6：mutation 自证（task-6-brief Step 1，TDD 红→绿）。

证明器有效性门（spec v2 §1·R2·复核最大风险=假绿）：向转换链注入 6 类已知错误，
diff 必须逐类抓红——任一类未抓红 ⇒ suite FAIL（mutation 不绿不得进 Task 7）。
「调换多注胜者」=复核点名的假绿风险件（expected 侧若复用败者语义则此测必红）。
"""
import copy

from ghidra_track.mutation_proof import MUTATIONS, run_mutation_suite


def _base():
    return {'functions': {0x401000: {'name': 'winner', 'signature': 'void f()',
                                     'class': 'C', 'adjudication': 'confirmed'},
                          0x401004: {'name': 'G', 'signature': 'void g()'}},
            'structs': {'S': {'size': 8, 'members': {4: {'name': 'm_b', 'type': 'int'}}}},
            'globals': {0x500000: {'name': 'g_X', 'type': 'int'}},
            'skips': {}}


def test_six_mutations_defined():
    names = [n for n, _fn in MUTATIONS]
    assert names == ['rename', 'offset_shift', 'type_swap', 'field_delete',
                     'extra_field', 'swap_multi_claim_winner'], names


def test_all_six_caught():
    r = run_mutation_suite(_base())
    assert r['total'] == 6 and r['caught'] == 6, r
    assert r['verdict'] == 'PASS', r
    # 调换多注胜者=复核最大假绿风险件，必测
    w = [m for m in r['mutations'] if m['name'] == 'swap_multi_claim_winner'][0]
    assert w['caught'], '胜者调换必须被抓（假绿风险件）'


def test_suite_fails_when_detector_neutered():
    # 门语义：diff 引擎失效（恒空）⇒ suite FAIL（任一类未抓红即 FAIL）
    neutered = lambda a, b: {'match': [], 'missing': [], 'changed': [],
                             'extra': [], 'unverifiable': []}
    r = run_mutation_suite(_base(), diff=neutered)
    assert r['verdict'] == 'FAIL' and r['caught'] == 0, r


def test_base_not_mutated():
    base = _base()
    snap = copy.deepcopy(base)
    run_mutation_suite(base)
    assert base == snap, '注入必须 deepcopy（禁污染基座）'
