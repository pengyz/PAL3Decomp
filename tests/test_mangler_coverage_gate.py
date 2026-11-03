"""unmatched 率门禁（plan-1to5 §487 缺口收口）：mangler 覆盖率棘轮。
R15：判定纯函数先行单测。"""

from tools.mangler_coverage_gate import evaluate_coverage


def test_improvement_passes():
    v = evaluate_coverage(matched=300, unmatched=71, baseline={'matched': 293, 'unmatched': 78})
    assert v['ok'] and v['reason'] == 'improved'


def test_equal_passes():
    v = evaluate_coverage(matched=293, unmatched=78, baseline={'matched': 293, 'unmatched': 78})
    assert v['ok'] and v['reason'] == 'held'


def test_rate_worsened_fails():
    # 率恶化（unmatched 率升）⇒ fail-loud 不放行
    v = evaluate_coverage(matched=200, unmatched=80, baseline={'matched': 293, 'unmatched': 78})
    assert not v['ok'] and v['reason'] == 'rate-worse'


def test_shrink_corpus_rate_holds_passes():
    # 语料收缩但率不降 ⇒ 放行（scope 变化记 reason）
    v = evaluate_coverage(matched=100, unmatched=26, baseline={'matched': 293, 'unmatched': 78})
    assert v['ok'] and v['reason'] in ('held', 'improved')


def test_no_baseline_admits():
    v = evaluate_coverage(matched=10, unmatched=2, baseline=None)
    assert v['ok'] and v['reason'] == 'first-run'
