"""`audit_type_layout.rank_targets` 的测试 —— **先写测试**（TDD）。

## 为什么（2026-09-22 使用者确立的**闭环方法论**）

布局更新会产生**传播效应**（按值内嵌/DAG ⇒ 修一个类会顺带修好/改变别的类）⇒
**每批修完必须重新测量 + 重建 DAG/问题规模 + 重新选目标** ✗（预排批次会立刻失真 ✗
—— 实测：旧清单里 `SwordUI`/`PropUI`/`MainEquipUI` 3 个"冲突"类已被此前的修复**顺带解决** ✗）

## 排序判据（`rank_targets`）
* 输入：`conflicts` = {cls: 冲突成员数}（**当前测量** ✓）· `embed_map` = {类型: [内嵌它的类…]}（杠杆 ✓）
* **排除已解决** ✓（旧清单里的 ✓）· **杠杆优先**（被内嵌次数多者优先 ✓）· 冲突数次之 ✓
* 环安全 ✓（embed_map 的环不得死循环 ✗）

运行：`python3 tests/test_rank_targets.py`
"""
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT))
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))

import audit_type_layout as A  # noqa: E402


def test_rank_prefers_embed_leverage_then_conflicts():
    """杠杆（被内嵌次数）优先，冲突数次之 ✓"""
    conflicts = {'A': 100, 'B': 90, 'C': 5}
    embed = {'A': ['x', 'y', 'z'], 'B': ['x'], 'C': []}
    top = A.rank_targets(conflicts, embed, top=3)
    assert [t[0] for t in top] == ['A', 'B', 'C'], top


def test_rank_excludes_resolved_classes():
    """已解决的类必须被排除 ✓（旧清单会立刻失真 ✗）"""
    conflicts = {'A': 10, 'B': 0}          # B 已 0 冲突 ⇒ 排除 ✓
    embed = {'A': [], 'B': []}
    top = A.rank_targets(conflicts, embed, top=5)
    assert [t[0] for t in top] == ['A'], top


def test_rank_cycle_safe_and_stable():
    conf = {'A': 3, 'B': 3}
    emb = {'A': ['B'], 'B': ['A']}
    assert A.rank_targets(conf, emb, top=2) == [('A', 3, 1), ('B', 3, 1)] or \
           A.rank_targets(conf, emb, top=2) == [('B', 3, 1), ('A', 3, 1)]


def test_rank_tie_break_alphabetical():
    conf = {'B': 7, 'A': 7}
    emb = {'A': [], 'B': []}
    assert [t[0] for t in A.rank_targets(conf, emb, top=2)] == ['A', 'B']


def test_render_rank_line_includes_counts():
    line = A.render_rank('Cls', conflicts=12, embeds=3)
    assert 'Cls' in line and '12' in line and '3' in line


# ---------------- CLI 集成：--rank 从 JSON 报告重排（不重跑测量 ✓）----------------

def test_rank_from_json_report(tmp_path=None):
    import tempfile, json
    report = {'PalScriptMgr': {'conflicts': 269, 'total': 269},
              'SceneMgr': {'conflicts': 1, 'total': 167},
              'SwordUI': {'conflicts': 0, 'total': 182}}
    embed = {'UITextArea': ['Comp_DonateUI']}
    d = tempfile.mkdtemp()
    p = os.path.join(d, 'report.json')
    json.dump(report, open(p, 'w', encoding='utf-8'))
    top = A.rank_from_report(p, embed, top=5)
    assert [t[0] for t in top] == ['PalScriptMgr', 'SceneMgr'], top


import os  # noqa: E402

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