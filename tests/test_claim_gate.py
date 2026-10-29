"""R1 产生端闸（复核 8c777315 最小根因修复集）——证据纪律机制化：
未验认领禁增长（棘轮）+ 新多认领必入裁定台账。不准确=不判定的产生端面。
运行: pytest tests/test_claim_gate.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from claim_gate import evaluate_claim_gate


def test_unverified_growth_blocked():
    errs = evaluate_claim_gate(unverified_count=3529, unverified_baseline=3528,
                               multi_claims={}, multi_baseline=set(), ledger=set())
    assert errs == ['CLAIM_GATE:unverified_growth 3529>3528'], errs


def test_unverified_shrink_or_hold_ok():
    assert evaluate_claim_gate(3500, 3528, {}, set(), set()) == []


def test_new_multi_claim_needs_ledger():
    errs = evaluate_claim_gate(3528, 3528,
                               multi_claims={'0x00001234': ['A', 'B']},
                               multi_baseline=set(), ledger=set())
    assert errs == ['CLAIM_GATE:multi_claim_unadjudicated:0x00001234'], errs


def test_grandfathered_multi_ok():
    assert evaluate_claim_gate(3528, 3528,
                              multi_claims={'0x00001234': ['A', 'B']},
                              multi_baseline={'0x00001234'}, ledger={'0x00001234'}) == []
