"""mutation_proof — 证明器自证（spec v2 §1·R2·6 类注入逐类抓红）。

最大风险=假绿（复核裁定）：diff 引擎自身有 bug ⇒ PROVEN 是假绿。
本套件向合成 base facts 注入 6 类已知错误，diff 必须逐类抓到——
任一类未抓红 ⇒ verdict FAIL（门语义：mutation 不绿不得进 Task 7）。
「调换多注胜者」=复核点名的假绿风险件（expected 侧复用败者语义则此测红）。
"""
import copy
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))  # 包内平导（同 verify_b_import）
from verify_core import diff_facts  # noqa: E402


def _m_rename(f):
    f['functions'][0x401000]['name'] = 'renamed'
    return f


def _m_offset_shift(f):
    m = f['structs']['S']['members']
    m[8] = m.pop(4)
    return f


def _m_type_swap(f):
    f['structs']['S']['members'][4]['type'] = 'float'
    return f


def _m_field_delete(f):
    del f['functions'][0x401004]['signature']
    return f


def _m_extra_field(f):
    # 改靶 struct 幽灵成员（T10 裁定：functions/globals extra=覆盖信号非缺陷——
    # 注入 B 不应发明的 struct 成员=真缺陷形，躲 unnamed 过滤）
    f['structs']['S']['members'][12] = {'name': 'phantom_member', 'type': 'int'}
    return f


def _m_swap_winner(f):
    # 多注胜者调换：winner(confirmed) → 败者名（假绿风险件——期望侧若同错则 diff 空）
    f['functions'][0x401000]['name'] = 'loser_name'
    f['functions'][0x401000]['adjudication'] = None
    return f


MUTATIONS = [
    ('rename', _m_rename),
    ('offset_shift', _m_offset_shift),
    ('type_swap', _m_type_swap),
    ('field_delete', _m_field_delete),
    ('extra_field', _m_extra_field),
    ('swap_multi_claim_winner', _m_swap_winner),
]

_CAUGHT_KEYS = ('missing', 'changed', 'extra')


def run_mutation_suite(base=None, diff=diff_facts):
    """逐类注入 → diff(base, mutated) 必须非空（missing/changed/extra 任一）。
    任一类未抓红 ⇒ FAIL。base 只读（deepcopy 注入）。"""
    if base is None:
        base = {'functions': {0x401000: {'name': 'winner', 'signature': 'void f()',
                                         'class': 'C', 'adjudication': 'confirmed'},
                              0x401004: {'name': 'G', 'signature': 'void g()'}},
                'structs': {'S': {'size': 8, 'members': {4: {'name': 'm_b', 'type': 'int'}}}},
                'globals': {0x500000: {'name': 'g_X', 'type': 'int'}},
                'skips': {}}
    report = {'mutations': [], 'caught': 0, 'total': 0, 'verdict': 'PASS'}
    for name, fn in MUTATIONS:
        mutated = fn(copy.deepcopy(base))
        d = diff(base, mutated)
        hit = any(d.get(k) for k in _CAUGHT_KEYS)
        report['mutations'].append({
            'name': name, 'caught': hit,
            'counts': {k: len(v) for k, v in d.items()},
        })
        report['total'] += 1
        if hit:
            report['caught'] += 1
    report['verdict'] = 'PASS' if report['caught'] == report['total'] else 'FAIL'
    return report
