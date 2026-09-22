"""`tools/audit_attribution.py` 的测试 —— **先写测试**（TDD）。

归属可证性判据（本会话确立）：函数体内 `[this+off]` 的**成员访问集合**与候选类的成员偏移表比对：
* **恰好一个类相容** ⇒ `unique` ⇒ **归属可证** ✓
* **≥2 个类相容** ⇒ `ambiguous` ⇒ **不可证**，只报警 ✓
* **没有任何类相容** ⇒ `contradiction` ⇒ **最强告警**（归属错或成员表错）✓
* **访问集合为空** ⇒ `no-evidence` ⇒ 不得下任何结论 ✓（"未观测 ≠ 不存在"）

运行：`python3 tests/test_audit_attribution.py`
"""
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))

import audit_attribution as A  # noqa: E402


# ---------------- 纯逻辑：verdict() ----------------

def test_unique_when_exactly_one_class_covers_accesses():
    cands = {'RoleSystem': {0x10, 0x14, 0x20}, 'SceneMgr': {0x100, 0x104}}
    assert A.verdict({0x10, 0x20}, cands) == ('unique', 'RoleSystem')


def test_ambiguous_when_two_classes_cover():
    """两个类都能容纳该访问集合 ⇒ **不可证** ⇒ 必须报警，不得挑一个当结论 ✗"""
    cands = {'A': {0x10, 0x14}, 'B': {0x10, 0x14, 0x18}}
    v, who = A.verdict({0x10}, cands)
    assert v == 'ambiguous' and sorted(who) == ['A', 'B'], (v, who)


def test_contradiction_when_no_class_covers():
    """没有任何候选类含该偏移 ⇒ 归属错或成员表错 ⇒ 最强告警 ✓"""
    cands = {'A': {0x10}, 'B': {0x20}}
    assert A.verdict({0x30}, cands) == ('contradiction', [])


def test_empty_accesses_is_no_evidence():
    """空访问集合**不是**"唯一相容" ✗ ⇒ 必须 `no-evidence`（未观测 ≠ 不存在）✓"""
    cands = {'A': {0x10}, 'B': {0x20}}
    assert A.verdict(set(), cands) == ('no-evidence', None)


def test_no_candidates_is_no_evidence():
    assert A.verdict({0x10}, {}) == ('no-evidence', None)


def test_contradiction_outranks_partial_coverage():
    """有的类部分覆盖（缺一个偏移）而无一完全覆盖 ⇒ 仍是 contradiction ✓"""
    cands = {'A': {0x10}, 'B': {0x20}}
    assert A.verdict({0x10, 0x20}, cands) == ('contradiction', [])


def test_unique_ignores_classes_that_only_partially_cover():
    cands = {'A': {0x10, 0x14}, 'B': {0x10}, 'C': {0x99}}
    assert A.verdict({0x10, 0x14}, cands) == ('unique', 'A')


# ---------------- 兼容集合的来源（从生成头/注解成员表构建） ----------------

def test_candidate_sets_from_last_checked_generation():
    """`candidate_offsets()` 必须真的从**生成头**读出成员偏移（至少包含已核对的几个类）"""
    cands = A.candidate_offsets()
    assert 'SceneMgr' in cands and 'RoleSystem' in cands, list(cands)[:5]
    # SceneMgr 的 m_pGfxMgr 在 +0x0（P1 已修 ⇒ 无 vptr）✓
    assert 0x0 in cands['SceneMgr'], 'SceneMgr 应含 +0x0'
    assert 0xC660 in cands['SceneMgr'], 'SceneMgr 应含 +0xC660'


# ---------------- 报告格式（供人读 + 机器读） ----------------

def test_render_line_marks_all_four_verdicts():
    line = A.render_line('Foo::bar', 'SceneMgr', ('contradiction', []))
    assert 'contradiction' in line and 'Foo::bar' in line
    line2 = A.render_line('Foo::baz', 'SceneMgr', ('ambiguous', ['A', 'B']))
    assert 'ambiguous' in line2 and 'A' in line2 and 'B' in line2


if __name__ == '__main__':
    ok = fail = skip = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except unittest.SkipTest as e:
                print('  SKIP %s: %s' % (nm, e)); skip += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    sys.exit(1 if fail else 0)