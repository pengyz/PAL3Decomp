"""L1 诊断工具层 ②：first_diff 薄 CLI（spec v2 §1.2·TDD 红→绿）。

复核缩编裁定：partial 行已含 first_diff/diffs/obj/compiled_len ⇒ 本件=addr 键
查找+窗口展示+缺失提示，非新比对引擎；比对语义=gbengine_compare 既有。
"""
from tools.first_diff import build_report, find_row, norm_va


def _det():
    return {'units': {'a.cpp': [
        {'va': '0x0040CFE0', 'symbol': '?X', 'first_diff': 3, 'n_diff': 33,
         'diffs': [3, 7, 8], 'obj': '/tmp/gone.obj', 'size': 40,
         'compiled_len': 40, 'reloc_skipped': 0},
        {'va': '0x0040D000', 'symbol': '?Y', 'first_diff': 0, 'n_diff': 0,
         'diffs': [], 'obj': None, 'size': 8, 'compiled_len': 8,
         'reloc_skipped': 0}]}}


def test_norm_va_forms():
    assert norm_va('0x0040CFE0') == norm_va('0x40cfe0') == 0x40CFE0
    assert norm_va('40CFE0') == 0x40CFE0


def test_find_row_hit_and_miss():
    r = find_row(_det(), '0x40cfe0')
    assert r and r['symbol'] == '?X'
    assert find_row(_det(), '0x999999') is None


def test_report_obj_missing_hint():
    rep = build_report(_det(), '0x40CFE0', obj_exists=False)
    assert rep['first_diff'] == 3 and rep['n_diff'] == 33
    assert '重跑 probe' in rep['next'] and 'hypothesis' in rep['next'], \
        'obj 已清（probe rmtree）必须给重算路径提示（match flags）'
    assert rep['window'] == [], '无字节禁造窗口（fail-loud 面）'


def test_report_obj_present_points_fdiff():
    rep = build_report(_det(), '0x40CFE0', obj_exists=True)
    assert 'fdiff' in rep['next'], 'obj 在场→指既有 fdiff（复用禁重造）'


def test_report_l1_row_zero_diff():
    rep = build_report(_det(), '0x40D000', obj_exists=False)
    assert rep['first_diff'] is None and rep['n_diff'] == 0, \
        'L1 行首差=None（v1 判别力缺陷修：0 行如实报 0/None）'
