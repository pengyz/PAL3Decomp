"""B2a vtable 槽归属对账（T1 27 槽法推广）——认领×二进制逐槽对证，产出 P 档判定。
运行: pytest tests/test_vtable_ownership.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from audit_vtable_ownership import verify_slot_claim, classify_ownership


def test_verify_slot_claim_mismatch():
    assert verify_slot_claim('0x0043E8A0', 0x0043E8A0) is True
    assert verify_slot_claim('0x0043E8A0', 0x0043E8B0) is False


def test_classify_confirmed_and_misowned():
    own = {'0x00517CF0': [('CCBLineupWindow', 5, '0x0056B800')]}
    assert classify_ownership('CCBLineupWindow', '0x00517CF0', own) == 'P:vtable_confirmed'
    assert classify_ownership('NPC', '0x00517CF0', own) == 'P:misowned'


def test_classify_multi_and_absent():
    own = {'0x0043DE40': [('UIListBox', 3, '0x0056AD20'), ('UICoverFrm', 3, '0x0056B100')]}
    assert classify_ownership('UIListBox', '0x0043DE40', own) == 'P:multi_owned'
    assert classify_ownership('NPC', '0x00999999', own) == 'not_in_vtables'
