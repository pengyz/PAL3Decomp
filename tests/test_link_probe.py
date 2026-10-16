#!/usr/bin/env python3
"""[link 门禁 2026-10-16] link_probe 纯函数单测（R15）+ 最小 smoke。

覆盖：
  ① parse_link_output：LNK2001/LNK2019（unresolved 归并）、LNK2005（duplicate）、
     LNK1120/杂行（by_code 计数、不入 unresolved/duplicates）
  ② diff_census：棘轮判据四态
     - LNK2005 增长 ⇒ 硬回归（单元数无关）
     - units_linked 未增而 unresolved 增长 ⇒ 硬回归
     - units_linked 增长期 unresolved 增长 ⇒ 仅 advisory（视野扩大）
     - 改善/持平 ⇒ 无回归
  ③ smoke：census 结构可写可读（round-trip）

不触 wine/链接器（纯函数面）——真跑链路见 `python pipeline/link_probe.py --check`。
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline'))

import link_probe as lp  # noqa: E402


LINK_OUT = """
x.obj : error LNK2001: unresolved external symbol "?Foo@@YAXXZ"
y.obj : error LNK2019: unresolved external symbol "?Bar@@YAXXZ" referenced in function "?Baz@@YAXXZ"
z.obj : error LNK2001: unresolved external symbol "?Bar@@YAXXZ"
a.obj : error LNK2005: "?Dup@@YAXXZ" already defined in b.obj
c.obj : fatal error LNK1120: 2 unresolved externals
noise line that should be ignored
"""


def test_parse_link_output_codes():
    by_code, unresolved, duplicates = lp.parse_link_output(LINK_OUT)
    assert by_code['LNK2001'] == 2
    assert by_code['LNK2019'] == 1
    assert by_code['LNK2005'] == 1
    assert by_code['LNK1120'] == 1
    # Foo 1 站点 · Bar 跨 x/y 两 TU 归并为 1 符号 2 站点
    assert '?Foo@@YAXXZ' in unresolved
    assert len(unresolved['?Bar@@YAXXZ']) == 2
    assert len(duplicates) == 1


def test_parse_link_output_duplicate_where():
    _, _, duplicates = lp.parse_link_output(
        'a.obj : error LNK2005: "?Dup@@YAXXZ" already defined in b.obj')
    assert duplicates['?Dup@@YAXXZ'] == ['b.obj']


def _census(units, unr, dup):
    return {'units_linked': units,
            'unresolved': {('s%d' % i): [] for i in range(unr)},
            'duplicates': {('d%d' % i): [] for i in range(dup)}}


def test_diff_census_duplicate_growth_is_hard_regression():
    d = lp.diff_census(_census(10, 5, 1), _census(10, 5, 2))
    assert d['regressed'] and any('LNK2005' in r for r in d['reasons'])


def test_diff_census_unresolved_growth_without_unit_growth_is_regression():
    d = lp.diff_census(_census(10, 5, 0), _census(10, 7, 0))
    assert d['regressed'] and any('unresolved' in r for r in d['reasons'])


def test_diff_census_unresolved_growth_with_unit_growth_is_advisory_only():
    d = lp.diff_census(_census(10, 5, 0), _census(14, 9, 0))
    assert not d['regressed']
    assert d['advisory'] and not d['reasons']


def test_diff_census_improvement_or_flat_is_clean():
    assert not lp.diff_census(_census(10, 9, 2), _census(10, 5, 0))['regressed']
    assert not lp.diff_census(_census(10, 5, 1), _census(11, 5, 1))['regressed']


def test_census_schema_roundtrip(tmp_path):
    p = tmp_path / 'link_census.json'
    summary = {'generated_at': '2026-10-16T00:00:00', 'units_linked': 3,
               'units_skipped': 0, 'skipped': [], 'errors_by_code': {'LNK2001': 2},
               'unresolved': {'?Foo@@YAXXZ': ['x.obj']}, 'duplicates': {}}
    p.write_text(json.dumps(summary, indent=1), encoding='utf-8')
    back = json.loads(p.read_text(encoding='utf-8'))
    assert back == summary
    assert not lp.diff_census(back, summary)['regressed']
