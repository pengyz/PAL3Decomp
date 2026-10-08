import pytest
"""`pipeline/preflight.py` + `cli.py loop` 的读数/断言单元测试。

# 背景（2026-09-21）

管线有**三份互不相干的基线**，实测互相矛盾（`compile_baseline.json` 76/206 vs
`baselines/latest.json` 75/205）⇒ 在干净 HEAD 上 `codegen all` 与 `match` **恒 exit 1**，
自动化循环无法区分信号与噪声。`status`/`loop` 就是为了把状态与断言**机械化**。

本测试断言的是**契约**（不依赖仓库当前状态）：喂合成状态，必须得到正确的对照/判定/解析。
运行方式: python3 tests/test_preflight.py
"""
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT))

from pipeline import preflight as pf  # noqa: E402
from pipeline.cli import _loop_parse  # noqa: E402


def _state(compile_ok=None, compile_tot=None, latest_ok=None, latest_tot=None,
           l1=None, live_l1=None):
    rows = {}
    if latest_ok is not None:
        rows = {'u%d.cpp' % i: {'status': 'ok' if i < latest_ok else 'fail'}
                for i in range(latest_tot)}
    return {
        'compile_baseline': ({'s2': {'ok': compile_ok, 'total': compile_tot},
                              'timestamp': 'T1'} if compile_ok is not None else None),
        'latest_baseline': ({'results': rows, 'timestamp': 'T2'} if rows else None),
        's4_baseline': ({'stats': {'match_L1': l1}} if l1 is not None else None),
        # ⚠️ 必须是 `loop` 真实写出的形状 `{'stages': {'match': {...}}}`
        #（曾按 `{'match': {...}}` 写 fixture ⇒ 单测全绿而真实 --expect-l1 恒失败）
        'loop_last': ({'stages': {'match': {'L1': live_l1, 'rc': 1}}} if live_l1 is not None
                      else None),
        'live_s2': None,
    }


# ===== ① 三方基线对照 =====
def test_rows_report_both_s2_baselines():
    st = _state(compile_ok=76, compile_tot=206, latest_ok=75, latest_tot=205, l1=38)
    rows = pf.baseline_rows(st)
    assert [(r['ok'], r['total']) for r in rows[:2]] == [(76, 206), (75, 205)]
    assert '38' in rows[2]['note'], rows[2]['note']


def test_l1_read_from_stats_key():
    """回归守卫：L1 在 `stats.match_L1` 里（顶层键不存在）—— 读错会显示 None。"""
    assert pf._l1_of_s4({'stats': {'match_L1': 38}}) == 38
    assert pf._l1_of_s4({'match_L1': 35}) == 35        # 后备路径
    assert pf._l1_of_s4({}) is None


# ===== ② 恒红门禁识别 =====
def test_competing_s2_baselines_flagged_red():
    st = _state(compile_ok=76, compile_tot=206, latest_ok=75, latest_tot=205)
    red = pf.known_red_gates(st)
    assert len(red) == 1 and 'compile_regression' in red[0]['gate'], red
    assert red[0]['recorded'] == '76/206' and red[0]['live_baseline'] == '75/205'


def test_consistent_baselines_are_not_red():
    st = _state(compile_ok=75, compile_tot=205, latest_ok=75, latest_tot=205, l1=35, live_l1=35)
    assert pf.known_red_gates(st) == []


def test_live_l1_below_ratchet_is_red():
    st = _state(compile_ok=75, compile_tot=205, latest_ok=75, latest_tot=205, l1=38, live_l1=35)
    red = pf.known_red_gates(st)
    assert [g['gate'] for g in red] == ['match → L1 棘轮'], red


def test_l1_unknown_when_no_loop_run():
    st = _state(compile_ok=75, compile_tot=205, latest_ok=75, latest_tot=205, l1=38)
    red = pf.known_red_gates(st)
    assert len(red) == 1 and '待测' in red[0]['gate'], red


# ===== ③ --expect-* 解析与断言 =====
def test_parse_expect_forms():
    assert pf.parse_expect('75/205', '2150', '35') == {'s2': (75, 205), 'errors': 2150, 'l1': 35}
    assert pf.parse_expect(' 75 / 205 ') == {'s2': (75, 205)}
    assert pf.parse_expect() == {}


def test_parse_expect_rejects_bad_form():
    for bad in ('75', '75/205/3', 'abc'):
        try:
            pf.parse_expect(bad)
        except ValueError:
            continue
        raise AssertionError('should reject %r' % bad)


def test_check_expectations_reports_mismatch():
    st = _state(live_l1=35)
    st['live_s2'] = {'ok': 74, 'total': 205, 'errors': 2150}
    fails = pf.check_expectations(st, {'s2': (75, 205), 'errors': 2150, 'l1': 35})
    assert len(fails) == 1 and 'S2 期望 75/205' in fails[0], fails
    assert pf.check_expectations(st, {'errors': 2150, 'l1': 35}) == []


# ===== ④ loop 的阶段输出解析 =====
def test_loop_parse_s2_from_probe_and_codegen():
    assert _loop_parse('probe', 'S2 cpp: 75/205 ok | own-fail 130')['s2_total'] == 205
    d = _loop_parse('codegen', 'S2-passing units: 75')
    assert d['s2_ok'] == 75 and 's2_total' not in d


def test_loop_parse_match_readings():
    t = ('matched 265/319 symbols | L1 35 | partial 198 | oob 0\n'
         '[L1 ratchet] previous 38 -> current 35')
    d = _loop_parse('match', t)
    assert (d['matched'], d['symbols'], d['L1']) == (265, 319, 35)
    assert (d['L1_prev'], d['L1_cur']) == (38, 35)


def test_loop_parse_missing_is_empty_not_crash():
    assert _loop_parse('match', 'nothing here') == {}
    assert _loop_parse('apply', '') == {}


# ===== ⑤ 渲染包含关键警示（防"报告静默降级"）=====
def test_render_surfaces_inconsistency_and_red_gates():
    st = _state(compile_ok=76, compile_tot=206, latest_ok=75, latest_tot=205, l1=38, live_l1=35)
    txt = pf.render(st)
    assert '互相矛盾' in txt, txt
    assert 'python3 pipeline/cli.py loop' in txt
    assert '拼' in txt or '唯一权威顺序' in txt


# ===== ⑥ 截断单元：聚合指标失明 ⇒ 必须单独报出（含"列表内最大行号"）=====
def _census_with_capped(unit, errs_before, max_line):
    return {'s2': {'ok': 1, 'total': 1, 'results': [
        {'unit': unit, 'status': 'fail',
         'errors': [{'file': unit, 'line': 10 + i, 'code': 'C2660', 'msg': 'x'}
                    for i in range(errs_before - 1)]
                   + [{'file': unit, 'line': max_line, 'code': 'C1003', 'msg': 'stop'}]}]}}


def test_truncated_units_reported_with_max_line():
    st = {'live_census': _census_with_capped('pal3/src/X.cpp', 5, 3823)}
    t = pf.truncated_units(st)
    assert len(t) == 1 and t[0]['errors'] == 5 and t[0]['max_line'] == 3823, t


def test_non_capped_units_not_reported():
    cen = {'s2': {'results': [{'unit': 'u.cpp', 'status': 'fail',
                               'errors': [{'file': 'u.cpp', 'line': 3, 'code': 'C1', 'msg': 'm'}]}]}}
    assert pf.truncated_units({'live_census': cen}) == []


def test_truncation_progress_is_visible_in_render():
    """**F3a 的教训**：修掉早期错误后总数不变，但最大行号必须变大。"""
    a = pf.render({'live_census': _census_with_capped('u.cpp', 3, 3389)})
    b = pf.render({'live_census': _census_with_capped('u.cpp', 3, 3787)})
    assert '列表内最大行号=3389' in a and '列表内最大行号=3787' in b, (a, b)
    assert 'C1003 截断单元' in a


# ===== ⑦ 契约：与**真实生产者**产出的 `_loop_last.json` 对齐 =====
def test_real_loop_last_shape_matches_reader():
    """防"fixture 与真实文件形状不一致"（曾导致单测全绿而 --expect-l1 恒失败）。"""
    import json
    p = PROJECT_ROOT / 'data' / 'status' / '_loop_last.json'
    if not p.exists():
        import unittest
        raise unittest.SkipTest('尚无 _loop_last.json（跑一次 `cli.py loop` 生成）')
    real = json.loads(p.read_text(encoding='utf-8'))
    assert 'stages' in real, list(real)
    assert isinstance(real['stages'].get('match'), dict), real['stages'].keys()
    # 读取器必须在**真实文件**上取出 L1（而不是 None）
    st = pf.collect_state()
    st['loop_last'] = real
    got = pf._loop_match(st).get('L1')
    assert got is not None, 'reader must find L1 in the real _loop_last.json: %r' % real
    assert pf.check_expectations(st, {'l1': got}) == []


if __name__ == '__main__':
    ok = fail = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed' % (ok, fail))
    sys.exit(1 if fail else 0)
