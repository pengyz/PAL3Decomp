#!/usr/bin/env python3
"""[F-CG#2 2026-10-15] collect.py name 解析单测（R15）。

病灶：decomp name 的**参数表内含 `::`**（嵌套型 `AStarPathFinder::NODE *`）⇒
`name.rsplit('::', 1)` 切进参数表 ⇒ cls/method 双错 ⇒ stage1 双参表（C2091 族 49 错）。
修法：先剥参数表再 rsplit。实测影响面=decomp 全库 4 条（911 条扫描）。
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen' / 'stages'))

from data import store  # noqa: E402,F401
import collect as col  # noqa: E402


def _mk(tmp, fname, name, addr='0x00401000'):
    d = {
        'name': name, 'address': addr, 'size_bytes': 32,
        'signature': 'void __thiscall(void *this, void *p)',
        'decompiled_c': 'void __thiscall F(void *this, void *p)\n{\n}\n',
        'local_vars': [],
    }
    p = Path(tmp) / fname
    p.write_text(json.dumps(d), encoding='utf-8')
    return p


def test_nested_type_param_parsed_correctly(tmp_path):
    # 病灶形：参数表内含 `::`（AStarPathFinder::NODE *）
    _mk(tmp_path, 'AStarPathFinder_Release_00401590.json',
        'AStarPathFinder::Release(AStarPathFinder::NODE *)', '0x00401590')
    by_class, free_funcs = col.collect_functions(decomp_dir=str(tmp_path))
    assert 'AStarPathFinder' in by_class, list(by_class)
    methods = [m.get('method') for m in by_class['AStarPathFinder']]
    assert 'Release' in methods, methods      # 不是 'NODE *)' 等残片
    for m in by_class['AStarPathFinder']:
        assert '::' not in (m.get('method') or ''), m
        assert not (m.get('name') or '').endswith(')'), m


def test_plain_two_seg_name_unaffected(tmp_path):
    _mk(tmp_path, 'UIWnd_Show_00439000.json',
        'UIWnd::Show(int)', '0x00439000')
    by_class, free_funcs = col.collect_functions(decomp_dir=str(tmp_path))
    assert 'UIWnd' in by_class
    assert any(m.get('method') == 'Show' for m in by_class['UIWnd'])


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
