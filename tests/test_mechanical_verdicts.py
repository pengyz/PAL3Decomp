"""R7×P 档机械裁定（字节真值=可判定，合「不准确=不判定」）——
P:vtable_confirmed→confirmed / P:misowned→rejected（附改判目标）/ P:multi_owned→shared_impl。
运行: pytest tests/test_mechanical_verdicts.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from answer_mechanical_verdicts import verdict_for


def test_confirmed_maps():
    p = {('CEffSParticle', 0x4C0500): ('P:vtable_confirmed', None)}
    v = verdict_for({'class': 'CEffSParticle', 'addr': '0x004C0500'}, p)
    assert v and v[0] == 'confirmed', v


def test_misowned_maps_with_target():
    p = {('NPC', 0x517CF0): ('P:misowned', 'CCBLineupWindow')}
    v = verdict_for({'class': 'NPC', 'addr': '0x00517CF0'}, p)
    assert v and v[0] == 'rejected' and 'CCBLineupWindow' in v[1], v


def test_multi_maps_shared():
    p = {('UIListBox', 0x43DE40): ('P:multi_owned', None)}
    v = verdict_for({'class': 'UIListBox', 'addr': '0x0043DE40'}, p)
    assert v and v[0] == 'shared_impl', v


def test_unlocated_stays_unjudged():
    assert verdict_for({'class': 'X', 'addr': '0x00999999'}, {}) is None
