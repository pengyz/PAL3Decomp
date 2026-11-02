"""apply_plan 纯逻辑层（Ghidra 脚本的可测内核）：两遍建分区/thiscall 注入/sizeof 对账。
运行: pytest ghidra_track/tests/test_apply_plan_logic.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'ghidra_track'))
from import_annotation import partition_struct_passes, ghidra_sig_params, reconcile_sizes


def test_partition_two_pass():
    plan = [
        {'kind': 'define_struct', 'name': 'A', 'size': 32,
         'members': [{'offset': 0, 'name': 'b', 'type': 'B'}, {'offset': 16, 'name': 'n', 'type': 'int'}]},
        {'kind': 'define_struct', 'name': 'B', 'size': 16, 'members': [{'offset': 0, 'name': 'x', 'type': 'int'}]},
    ]
    p1, p2 = partition_struct_passes(plan)
    assert [s['name'] for s in p1] == ['A', 'B']          # 壳先行（前向引用可用）
    assert {m['name'] for s in p2 for m in s['members']} == {'b', 'n', 'x'}


def test_thiscall_param_injection():
    sig = {'conv': '__thiscall', 'ret': 'void', 'params': ['int'], 'cls': 'NPC'}
    assert ghidra_sig_params(sig) == [('this', 'NPC *'), ('', 'int')]
    g = {'conv': '__cdecl', 'ret': 'int', 'params': ['char *'], 'cls': None}
    assert ghidra_sig_params(g) == [('', 'char *')]


def test_reconcile_sizes():
    diffs = reconcile_sizes({'A': 32, 'B': 16}, {'A': 32, 'B': 24})
    assert diffs == {'B': (16, 24)}   # 注解 vs 库内实际
