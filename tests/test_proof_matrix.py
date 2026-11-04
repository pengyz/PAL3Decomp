"""B 转换证明 Task 5：矩阵语料扫描器（task-5-brief Step 1，TDD 红→绿）。

R5（spec v2 §2）：矩阵=语料机械键扫描（机器触发，禁手维护清单）+人写 disposition
分类账。测试断言：扫描出的每个键路径在矩阵有条目（无条目=红——schema 演进自动守护）。
"""
import json
import os
import pathlib

from ghidra_track.proof_matrix import build_matrix, scan_corpus_keys

_ROOT = pathlib.Path(__file__).resolve().parent.parent
_FIXTURE = _ROOT / 'ghidra_track' / 'fixture' / 'cases' / 'case-01-struct-union-overload' / 'annotations'
_REAL = _ROOT / 'data' / 'annotations'


def test_scan_finds_fixture_keys():
    keys = scan_corpus_keys(str(_FIXTURE))
    assert keys, '扫描必须出键集（fixture 语料在）'
    # 关键域在场（复核实测键域：struct/member/methods/functions/globals）
    assert any(k.startswith('struct.') for k in keys)
    assert any(k.startswith('member.') for k in keys)
    assert any(k.startswith('methods.') for k in keys)
    assert all(isinstance(v, int) and v > 0 for v in keys.values()), '计数必须为正'


def test_build_matrix_reports_missing():
    keys = scan_corpus_keys(str(_FIXTURE))
    r = build_matrix(str(_FIXTURE), dispositions={})
    assert r['missing'], '空分类账必须报缺（禁静默全过）'
    assert set(r['missing']) == set(keys), '缺=扫描全集（每键都须有条目）'


def test_build_matrix_complete_when_all_disposed():
    keys = scan_corpus_keys(str(_FIXTURE))
    disp = {k: {'transfer': 'op', 'reason': 't', 'verify': 'direct'} for k in keys}
    r = build_matrix(str(_FIXTURE), dispositions=disp)
    assert r['missing'] == [], '全条目时缺=空'
    assert len(r['matrix']) == len(keys)


def test_real_corpus_full_coverage():
    """Step 4 绿的单测化：真语料 data/annotations 全键在 proof_matrix.json 有条目。"""
    mp = json.loads((_ROOT / 'ghidra_track' / 'proof_matrix.json').read_text())
    r = build_matrix(str(_REAL), dispositions=mp)
    assert r['missing'] == [], '真语料键缺条目（schema 演进未入矩阵=红）: %s' % r['missing'][:5]
