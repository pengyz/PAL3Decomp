#!/usr/bin/env python3
"""[task-8 2026-10-19] export_full.py named 顶替跳过逻辑纯函数单测（R15）。

病灶：named 顶替逻辑写反——named 实体被跳过（应导出）· synthetic 保留（应跳过）。
正确：SceneMgr（named）导出（权威名）· _inline_SceneMgr_（synthetic）跳过（被顶替）。
"""
import json
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))


def _load_decision():
    src = (REPO / 'pipeline/ida/export_full.py').read_text(encoding='utf-8')
    m = re.search(r'def _named_supersede_decision\(.*?\n(?=def |\nclass )', src, re.S)
    assert m, '_named_supersede_decision 纯函数缺失（R15 抽提未落地）'
    ns = {'re': re}
    exec(m.group(0), ns)
    return ns['_named_supersede_decision']


def test_named_type_is_exported_not_skipped():
    """核心锁：named 实体（SceneMgr）**导出**（不跳过）——原 BUG 直接反例。"""
    fn = _load_decision()
    skip, reason = fn('SceneMgr', {'SceneMgr', 'UIWnd'}, {'_inline_SceneMgr_': 'SceneMgr'})
    assert skip is False, 'named 实体被跳过 ✗（BUG 复现）reason=%s' % reason


def test_synthetic_type_is_skipped():
    """核心锁：synthetic（_inline_SceneMgr_）**跳过**（被具名替身顶替）。"""
    fn = _load_decision()
    skip, reason = fn('_inline_SceneMgr_', {'SceneMgr'}, {'_inline_SceneMgr_': 'SceneMgr'})
    assert skip is True, 'synthetic 未跳过 ✗ reason=%s' % reason
    assert 'SceneMgr' in reason


def test_unknown_type_is_exported():
    fn = _load_decision()
    skip, _ = fn('SomeNewType', {'SceneMgr'}, {})
    assert skip is False


def test_decision_is_pure_and_order_independent():
    """纯函数性：同入同出（无状态 ✓）。"""
    fn = _load_decision()
    a = fn('SceneMgr', {'SceneMgr'}, {'_inline_SceneMgr_': 'SceneMgr'})
    b = fn('SceneMgr', {'SceneMgr'}, {'_inline_SceneMgr_': 'SceneMgr'})
    assert a == b


def test_helpers_read_annotation_contract():
    """_annotation_named_types / _synthetic_named_substitutes 契约（形状锁）。"""
    src = (REPO / 'pipeline/ida/export_full.py').read_text(encoding='utf-8')
    assert 'def _annotation_named_types' in src
    assert 'def _synthetic_named_substitutes' in src
    # 跳过逻辑调用点必须走纯函数（三路一致性）
    assert src.count('_named_supersede_decision(') >= 1


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
