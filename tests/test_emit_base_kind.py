#!/usr/bin/env python3
"""[codegen 结构生成修复 2026-10-17] base kind 分派纯函数单测（R15）。

病灶：`_inline_*` 型被误渲染为基类 `: public _inline_X`——kind 分派修复。
"""
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))


def _load_fn():
    src = (REPO / 'pipeline/gen/stages/emit_headers.py').read_text(encoding='utf-8')
    m = re.search(r'def _classify_base_kind\(.*?\n(?=    def )', src, re.S)
    ns = {}
    exec(m.group(0), ns)
    return ns['_classify_base_kind']


def test_inline_prefix_dispatched_to_overlay():
    fn = _load_fn()
    assert fn('_inline_tagCam_yaw') == 'inline-overlay'
    assert fn('_inline_PalScript_m_RoleSlotArray') == 'inline-overlay'
    assert fn('_inline_SceneMgr_') == 'inline-overlay'


def test_regular_names_dispatched_to_base():
    fn = _load_fn()
    assert fn('UIWnd') == 'base'
    assert fn('UIFrameWnd') == 'base'
    assert fn('gbRenderEffect') == 'base'


def test_invalid_and_boundary():
    fn = _load_fn()
    assert fn('') == 'invalid'
    assert fn(None) == 'invalid'
    # 边界：_inline 恰好前缀但非 _inline_ 形（后缀非下划线）仍为 base？
    # 制式：_inline_ 八字符前缀判据——_inlineX（无尾下划线）不匹配 ⇒ base
    assert fn('_inlineX') == 'base'


def test_emission_wiring_excludes_inline_from_bases():
    """接线锁：_inline_* 不得出现在 base_names 装配路径。"""
    src = (REPO / 'pipeline/gen/stages/emit_headers.py').read_text(encoding='utf-8')
    # 两处 base 装配点均须有 kind 分派
    assert src.count("_classify_base_kind") >= 3, '分派接线缺失'
    assert "inline-overlay" in src
