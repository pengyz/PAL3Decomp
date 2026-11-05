"""L1 诊断工具层 ①：match_progress 聚合+同源校验（spec v2 §1.1·TDD 红→绿）。

复核实证硬伤：s4_baseline(stats.match_L1=161) 与 s4_diff_detail(l1=110) 不同源
（1 函数状态相反·疑棘轮回写旧 baseline）⇒ 跨文件聚合必须 fail-loud 禁自欺。
"""
import json

import pytest

from tools.match_progress import build_progress, check_same_source


def _base(l1=2, partial=1, rows=None):
    return {'stats': {'match_L1': l1, 'partial': partial, 'matched': l1 + partial},
            'rows': rows or [
                {'file': 'a.cpp', 'va': '0x401000', 'status': 'match_L1'},
                {'file': 'a.cpp', 'va': '0x401100', 'status': 'match_L1'},
                {'file': 'b.cpp', 'va': '0x402000', 'status': 'partial'}]}


def _det(l1=2):
    return {'l1': l1, 'partial': 1, 'units': {}}


def _census():
    return {'s2': {'results': [
        {'unit': 'a.cpp', 'status': 'ok', 'errors': json.dumps(['C2440 x1'])},
        {'unit': 'b.cpp', 'status': 'fail_own', 'errors': json.dumps(['C2660 x2', 'C2440 x1'])}]}}


def test_same_source_pass():
    ok, msg = check_same_source(_base(), _det(l1=2))
    assert ok, msg


def test_same_source_fail_loud():
    # 复核实测形：baseline 161（行数对齐=自洽过）vs detail 110 → 全局路径拒
    rows = [{'file': 'a.cpp', 'va': hex(0x400000 + i * 4), 'status': 'match_L1'}
            for i in range(161)]
    ok, msg = check_same_source(_base(l1=161, rows=rows), _det(l1=110))
    assert not ok and '161' in msg and '110' in msg, msg


def test_rows_internal_consistency():
    # rows status 计数必须 == stats.match_L1（同文件内自洽·键名写死 stats.match_L1）
    bad = _base()
    bad['rows'][1]['status'] = 'partial'   # 行和=1 ≠ stats2
    ok, msg = check_same_source(bad, _det(l1=2))
    assert not ok and 'match_L1' in msg, msg


def test_build_progress_table():
    p = build_progress(_base(), _census())
    assert len(p['units']) == 2
    a = [u for u in p['units'] if u['unit'] == 'a.cpp'][0]
    assert a['l1'] == 2 and a['s2'] == 'ok'
    b = [u for u in p['units'] if u['unit'] == 'b.cpp'][0]
    assert b['s2'] == 'fail_own' and b['partial'] == 1
    # top_error=出现最多的码（b: C2660/C2440 各出现…C2660 x2 解析出 1 码计 1）
    assert 'C2660' in b['top_error'] or 'C2440' in b['top_error']
    # 对账断言：L1 列总和 == stats.match_L1（键名写死）
    assert sum(u['l1'] for u in p['units']) == 2
    # 排序：partial 降序
    assert p['units'][0]['partial'] >= p['units'][1]['partial']


def test_build_progress_l1_sum_mismatch_fails():
    bad = _base()
    bad['rows'][0]['file'] = 'zzz.cpp'   # 行移到不存在 census 的 unit → 行和仍2
    # 行和==stats 仍过；改 stats 制造行/账不符
    bad['stats']['match_L1'] = 3
    with pytest.raises(ValueError, match='match_L1'):
        build_progress(bad, _census())


def test_same_source_scope_exempt():
    """detail.l1=全局 94·detail.units=仅含 partial 行的单元（compare 形证）：
    域内 baseline match_L1=87 vs 全局 94 是范围差（7 个 L1 在无 partial 单元）——
    且 detail.units 内不出现 L1 行（只装 partial）⇒ 无状态相反，必须过。"""
    rows, units = [], {}
    for u in ('u1', 'u2', 'u3'):
        for _ in range(29):
            rows.append({'file': u, 'va': hex(0x400000 + len(rows) * 4),
                         'status': 'match_L1'})
        va = hex(0x500000 + len(rows) * 4)
        rows.append({'file': u, 'va': va, 'status': 'partial'})
        units[u] = [{'va': va, 'n_diff': 5}]     # 只装 partial 行（真形）
    for i in range(7):
        rows.append({'file': 'nopart', 'va': hex(0x600000 + i * 4),
                     'status': 'match_L1'})     # 无 partial 单元的 L1 不入 units
    base = {'stats': {'match_L1': 94}, 'rows': rows}
    ok, msg = check_same_source(base, {'l1': 94, 'units': units})
    assert ok, '全局同源+域内范围差必须过: %s' % msg


def test_same_source_global_mismatch_fails():
    """跨 run 异源（原实证 161 vs 110·棘轮恢复单文件病灶）→ 全局对账必拒。"""
    rows = [{'file': 'a.cpp', 'va': hex(0x400000 + i * 4), 'status': 'match_L1'}
            for i in range(161)]
    base = {'stats': {'match_L1': 161}, 'rows': rows}
    ok, msg = check_same_source(base, {'l1': 110, 'units': {}})
    assert not ok and '161' in msg and '110' in msg, msg
