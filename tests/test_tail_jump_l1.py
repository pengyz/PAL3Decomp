"""PlanB-T3 尾跳 L1 空洞补环——判据核心（纯函数）。
现判据：尾跳族只证 E9 一字节+长度（rel32=reloc don't-care）=假 L1 温床。
补环：尾跳函数 byte-identical 须**加**目标符号等同；否则降级 partial。
运行: pytest tests/test_tail_jump_l1.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from gbengine_compare import is_tail_jump_form, decide_tail_jump_verdict


def test_tail_form_detect():
    assert is_tail_jump_form(bytes([0xE9, 0x0B, 0, 0, 0])) is True
    assert is_tail_jump_form(bytes([0xE9, 1, 0, 0, 0, 0x90])) is False   # 5B 形之外
    assert is_tail_jump_form(bytes([0x56, 0x8B, 0xF1])) is False


def test_target_equal_keeps_perfect():
    v = decide_tail_jump_verdict(True, bytes([0xE9, 0, 0, 0, 0]), 'sub_A', 'sub_A')
    assert v == 'perfect'


def test_target_mismatch_or_unresolved_downgrades():
    assert decide_tail_jump_verdict(True, bytes([0xE9, 0, 0, 0, 0]), 'sub_A', 'sub_B') == 'partial'
    assert decide_tail_jump_verdict(True, bytes([0xE9, 0, 0, 0, 0]), None, 'sub_B') == 'partial'


def test_non_tail_untouched():
    assert decide_tail_jump_verdict(True, bytes([0x56, 0x8B, 0xF1]), None, None) == 'perfect'
