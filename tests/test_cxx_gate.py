"""强检测闸（2026-11-02）——重名必被查出：三门
①同址大小写双录（int(addr) 重复）②同(类)全同名双址 ③C++ 铁律(类,归一名,严格签名)双址
棘轮：存量 grandfather（基线冻结）· 新增=硬红。运行: pytest tests/test_cxx_gate.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from cxx_gate import evaluate_cxx_gate


def test_new_violation_blocked():
    errs, warns = evaluate_cxx_gate(
        violations={'K1'}, baseline={'K1'}, resolved=set())
    assert errs == []
    errs, _ = evaluate_cxx_gate(violations={'K1', 'K2'}, baseline={'K1'}, resolved=set())
    assert errs == ['CXX_GATE:new_violation:K2'], errs


def test_resolved_warns_for_baseline_refresh():
    errs, warns = evaluate_cxx_gate(violations=set(), baseline={'K1'}, resolved={'K1'})
    assert errs == [] and warns == ['CXX_GATE:baseline_stale:K1'], warns


def test_same_addr_casedup_and_namedup():
    from cxx_gate import collect_violations
    v = collect_violations([
        {'addr': '0x00A5D0', 'class': 'CCBStage', 'name': 'AddTask_A5D0', 'sig': 'void __thiscall()'},
        {'addr': '0x00a5d0', 'class': 'CCBStage', 'name': 'AddTask_a5d0', 'sig': 'void __thiscall()'},
    ])
    assert any('same_addr' in k for k in v), v
    v2 = collect_violations([
        {'addr': '0x1', 'class': 'X', 'name': 'Foo_1', 'sig': 'void __thiscall()'},
        {'addr': '0x2', 'class': 'X', 'name': 'Foo_1', 'sig': 'void __thiscall()'},
    ])
    assert any('same_name' in k or 'cxx_rule' in k for k in v2), v2


def test_gate2_sig_aware_overload_legal():
    """G2 去戳产生同名异签双址=合法重载，闸②不得误炸（用户规则：A::m(int)/A::m() 不冲突）。"""
    from cxx_gate import collect_violations
    v = collect_violations([
        {'addr': '0x1', 'class': 'X', 'name': 'Destroy', 'sig': 'void __thiscall(int)'},
        {'addr': '0x2', 'class': 'X', 'name': 'Destroy', 'sig': 'int __thiscall()'},
    ])
    assert not any('same_name' in k for k in v), v
    assert not any('cxx_rule' in k for k in v), v
