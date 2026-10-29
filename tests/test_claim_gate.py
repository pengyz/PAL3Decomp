"""R1 产生端闸（复核 8c777315 最小根因修复集）——证据纪律机制化：
未验认领禁增长（棘轮）+ 新多认领必入裁定台账。不准确=不判定的产生端面。
运行: pytest tests/test_claim_gate.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from claim_gate import evaluate_claim_gate


def test_unverified_growth_blocked():
    errs, _ = evaluate_claim_gate(unverified_count=3529, unverified_baseline=3528,
                               multi_claims={}, multi_baseline=set(), ledger=set())
    assert errs == ['CLAIM_GATE:unverified_growth 3529>3528'], errs


def test_unverified_shrink_or_hold_ok():
    assert evaluate_claim_gate(3500, 3528, {}, set(), set()) == ([], [])


def test_new_multi_claim_needs_ledger():
    errs, _ = evaluate_claim_gate(3528, 3528,
                               multi_claims={'0x00001234': ['A', 'B']},
                               multi_baseline=set(), ledger=set())
    assert errs == ['CLAIM_GATE:multi_claim_unadjudicated:0x00001234'], errs


def test_grandfathered_multi_ok():
    assert evaluate_claim_gate(3528, 3528,
                              multi_claims={'0x00001234': ['A', 'B']},
                              multi_baseline={'0x00001234'},
                              ledger={'0x00001234'}) == ([], [])


def test_b_gapfill_unadjudicated_warns():
    """P2(b)：gap_fill 移植件无裁定状态=黄牌（名字搬家非证据）。"""
    errs, warns = evaluate_claim_gate(
        3528, 3528, {}, set(), set(),
        gap_fill_unadjudicated=['0x0051B030'])
    assert errs == []
    assert warns == ['CLAIM_GATE:gap_fill_unadjudicated:0x0051B030'], warns


def test_c_redflag_member_counter_evidence_warns():
    """P2(c)：体成员反证红牌（索引不全⇒质疑级）=黄牌接进闸。"""
    errs, warns = evaluate_claim_gate(
        3528, 3528, {}, set(), set(),
        red_flags=['0x00517CF0'])
    assert errs == []
    assert warns == ['CLAIM_GATE:member_counter_evidence:0x00517CF0'], warns


def test_err_warns_split_contract():
    errs, warns = evaluate_claim_gate(3529, 3528, {}, set(), set(),
                                      gap_fill_unadjudicated=['0x1'], red_flags=['0x2'])
    assert errs and warns      # 硬错误与黄牌分轨


def test_f1_wash_level_without_evidence_still_unverified():
    """R1-a 堵洗绿：evidence_level=A 但无证据指针=仍计未验。"""
    errs, _ = evaluate_claim_gate(3528, 3528, {}, set(), set(),
                                  level_a_no_evidence_count=1)
    assert any('unverified_growth' in e for e in errs), errs


def test_f2_baseline_missing_fails_loud():
    from claim_gate import load_state
    import claim_gate as cg, json as _j, pathlib as _p
    old = cg.BASELINE
    cg.BASELINE = _p.Path('/tmp/nonexistent_baseline.json')
    try:
        b, _ = cg.load_state()
        assert b == {'ERROR': 'baseline_missing'}, b   # fail-loud 非自举
    finally:
        cg.BASELINE = old


def test_f3_ledger_requires_answer():
    errs, _ = evaluate_claim_gate(3528, 3528,
                                  multi_claims={'0x1': ['A', 'B']},
                                  multi_baseline=set(), ledger={'0x1'},
                                  ledger_entries={'0x1': {'answer': ''}})
    assert errs == ['CLAIM_GATE:multi_claim_unadjudicated:0x1'], errs


def test_f4_adjudication_valid_set_only():
    errs, _ = evaluate_claim_gate(3528, 3528, {}, set(), set(),
                                  gap_fill_unadjudicated=[],
                                  gap_fill_adjudged={'0x1': '随便写的'})
    assert any('gap_fill_invalid_adjudication' in e for e in errs), errs


def test_f5_p_verdict_regression_blocked():
    errs, _ = evaluate_claim_gate(3528, 3528, {}, set(), set(), p_count=800, p_baseline=821)
    assert any('p_verdict_regression' in e for e in errs), errs
