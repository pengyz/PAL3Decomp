#!/usr/bin/env python3
"""[坏 JSON 盲区治理 2026-10-16] annotation_view 记账 fail-visible 单测（R15）。

病灶：坏 JSON（并发半写/控制字符）被 iter_structs/load_annotation_json **静默跳过**
——check_annotations 能报、codegen 侧无声 ✗ 盲区。修法：SKIPPED_ANNOTATIONS 记账
+ stderr 响亮告警（不改跳过语义，fail-visible）。
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))

from data import store  # noqa: E402,F401
import annotation_view as av  # noqa: E402


def test_bad_struct_json_is_recorded_and_warned(tmp_path, capsys):
    bad = tmp_path / 'Bad.json'
    bad.write_text('{"name": "X", "broken": "unterminated', encoding='utf-8')
    av.SKIPPED_ANNOTATIONS.clear()
    out = av.load_struct(str(bad))
    assert out is None
    assert any(str(bad) in p for p, _e in av.SKIPPED_ANNOTATIONS), av.SKIPPED_ANNOTATIONS
    err = capsys.readouterr().err
    assert 'WARN' in err and 'Bad.json' in err   # 响亮告警 ✓ 非静默


def test_control_character_json_recorded(tmp_path, capsys):
    # L8 坏字符形（实测竞态半写症状）：字符串内裸控制字符
    bad = tmp_path / 'Ctrl.json'
    bad.write_bytes(b'{"name": "X",\n "a": 1,\n "b": 2,\n "c": 3,\n "d": 4,\n "e": 5,\n "f": 6,\n "g": "\x0b"}')
    av.SKIPPED_ANNOTATIONS.clear()
    out = av.load_struct(str(bad))
    assert out is None
    assert len(av.SKIPPED_ANNOTATIONS) == 1


def test_good_json_not_recorded_and_iter_structs_yields(tmp_path):
    good = tmp_path / 'Good.json'
    good.write_text(json.dumps({'name': 'G', 'known_members': {}}), encoding='utf-8')
    av.SKIPPED_ANNOTATIONS.clear()
    got = list(av.iter_structs(str(tmp_path)))
    assert len(got) == 1 and got[0][1]['name'] == 'G'
    assert av.SKIPPED_ANNOTATIONS == []


def test_current_repo_annotations_all_clean():
    """全库自检（R13 预检）：当前 data/annotations 零坏 JSON（竞态残余清零）。"""
    av.SKIPPED_ANNOTATIONS.clear()
    list(av.iter_structs(None))          # 全 structs 目录
    assert av.SKIPPED_ANNOTATIONS == [], av.SKIPPED_ANNOTATIONS


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
