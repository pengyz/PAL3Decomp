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


# ---------------- 精化判据（尺寸边界 + 匹配率/领先幅度）----------------
# 背景：单纯"访问集合 ⊆ 声明成员"判别力不足 —— 实测 SceneMgr::Create 被误判为"唯一相容 CEffMgr" ✗
# 原因：① 大类的成员表**稀疏**，落在对象范围内但未声明的偏移应视为**相容**（gap/未知）✓
#       ② 小类只要凑上几个偏移就可能"唯一" ⇒ 必须要求**匹配率**高且**领先第二名有幅度** ✓

def test_offset_inside_size_but_not_declared_is_compatible():
    """范围内但未声明 ⇒ 相容（gap/未知空间），不得判不相容 ✗"""
    classes = {'A': {'members': {0x10}, 'size': 0x1000}}
    v, who = A.verdict_bounded({0x10, 0x800}, classes)
    assert v == 'unique' and who == 'A', (v, who)


def test_offset_beyond_size_is_incompatible():
    """超出对象尺寸 ⇒ **不相容**（这是最强的判别信号 ✓）"""
    classes = {'A': {'members': {0x10}, 'size': 0x100}, 'B': {'members': {0x10}, 'size': 0x1000}}
    v, who = A.verdict_bounded({0x10, 0x800}, classes)
    assert v == 'unique' and who == 'B', (v, who)


def test_no_class_can_contain_is_contradiction():
    classes = {'A': {'members': {0x10}, 'size': 0x100}, 'B': {'members': {0x20}, 'size': 0x200}}
    assert A.verdict_bounded({0x900}, classes) == ('contradiction', [])


def test_ambiguous_when_two_classes_both_contain_and_match_equally():
    classes = {'A': {'members': {0x10, 0x14}, 'size': 0x1000},
               'B': {'members': {0x10, 0x14}, 'size': 0x1000}}
    v, who = A.verdict_bounded({0x10, 0x14}, classes)
    assert v == 'ambiguous' and sorted(who) == ['A', 'B'], (v, who)


def test_unique_requires_clear_margin_in_match_rate():
    """两个类都容纳，但**匹配率**差距显著 ⇒ 判 unique 于高匹配者 ✓（并要求其匹配率 ≥ 阈值）"""
    classes = {'A': {'members': {0x10, 0x14, 0x18, 0x1C}, 'size': 0x1000},
               'B': {'members': {0x10}, 'size': 0x1000}}
    v, who = A.verdict_bounded({0x10, 0x14, 0x18, 0x1C}, classes)
    assert v == 'unique' and who == 'A', (v, who)


def test_low_match_rate_is_ambiguous_not_unique():
    """都容纳但匹配率都很低（多落在 gap 里）⇒ 不可证 ⇒ ambiguous ✓（防止"凑上几个"就下结论 ✗）"""
    classes = {'A': {'members': {0x10}, 'size': 0x10000},
               'B': {'members': {0x20}, 'size': 0x10000}}
    v, who = A.verdict_bounded({0x10, 0x9000, 0x9100, 0x9200}, classes)
    assert v == 'ambiguous', (v, who)


def test_bounded_empty_accesses_is_no_evidence():
    classes = {'A': {'members': {0x10}, 'size': 0x100}}
    assert A.verdict_bounded(set(), classes) == ('no-evidence', None)


# ---------------- 访问偏移提取（`this` 来源追踪 + 绝对地址排除）----------------
# 背景（2026-09-22 实测）：提取器把 `[eax+0xC109F0]` 这类**绝对地址访问**（全局对象）当成成员偏移 ✗
# ⇒ 出现 off=0xC109F0 这种远超任何类尺寸的值 ⇒ 只有"极大类"能相容 ⇒ 判据被污染 ✗

def _l(addr, ins):
    return {'addr': addr, 'instruction': ins}


def test_extract_this_based_member_access():
    lines = [_l('0x1000', 'push esi'), _l('0x1001', 'mov esi, ecx'),
             _l('0x1003', 'mov eax, [esi+20h]'), _l('0x1006', 'mov [esi+0x2BC], edx')]
    assert A.accessed_offsets(lines) == {0x20, 0x2BC}


def test_extract_excludes_absolute_address_access():
    """`[eax+0xC109F0]` 是**全局对象**访问（绝对地址），不是成员偏移 ⇒ 必须排除 ✓"""
    lines = [_l('0x2000', 'mov eax, ecx'), _l('0x2002', 'mov edx, [eax+0C109F0h]'),
             _l('0x2008', 'mov ecx, [ecx+14h]')]
    got = A.accessed_offsets(lines)
    assert 0xC109F0 not in got, got
    assert 0x14 in got, got


def test_extract_excludes_stack_accesses():
    lines = [_l('0x3000', 'mov [esp+1Ch], eax'), _l('0x3003', 'mov eax, [ebp-8]'),
             _l('0x3006', 'mov ecx, [ecx+8]')]
    assert A.accessed_offsets(lines) == {0x8}


def test_extract_drops_register_after_overwrite():
    """`mov ecx, eax` 覆盖 ⇒ ecx **不再**是 this ⇒ 其后的 `[ecx+…]` 不得计入 ✓"""
    lines = [_l('0x4000', 'mov ecx, eax'), _l('0x4002', 'mov edx, [ecx+10h]')]
    assert A.accessed_offsets(lines) == set()


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