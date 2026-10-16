#!/usr/bin/env python3
"""[R11 修 2026-10-16] verify_fix._type_text/consistency dict 型单测（R15）。

病灶：`(annot_type or '').lower()` 对 inline union/struct（dict 型）崩 AttributeError
——实测 verify_fix --class PalScript 崩溃阻塞四道门终验。
"""
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / 'tools'))

import verify_fix as vf  # noqa: E402


def test_type_text_str_and_none():
    assert vf._type_text('gbRenderEffect *') == 'gbrendereffect *'
    assert vf._type_text(None) == ''


def test_type_text_inline_union_collects_leaf_types():
    u = {'union': [
        {'type': 'BaseType', 'name': 'a'},
        {'type': {'struct': [{'offset': 0, 'name': 'm', 'type': 'float'}]}, 'name': 'b'},
    ]}
    t = vf._type_text(u)
    assert 'basetype' in t and 'float' in t


def test_consistency_accepts_dict_type():
    # 崩溃修复主锁：dict 型不再 AttributeError，且 float 检查语义保持
    u = {'union': [{'type': 'float', 'name': 'v'}]}
    st, why = vf.consistency(u, 4, 100, {'disp': 0, 'float_imm': True, 'width': 4})
    assert st == 'ok', (st, why)
    # 非浮点叶型写 float 立即数 ⇒ 仍报 contradiction
    u2 = {'union': [{'type': 'int', 'name': 'v'}]}
    st2, why2 = vf.consistency(u2, 4, 100, {'disp': 0, 'float_imm': True, 'width': 4})
    assert st2 == 'contradiction', (st2, why2)


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
