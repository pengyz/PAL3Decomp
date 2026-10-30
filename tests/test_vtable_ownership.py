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
    assert classify_ownership('CCBLineupWindow', '0x00517CF0', own, {'CCBLineupWindow'}) == 'P:vtable_confirmed'
    assert classify_ownership('NPC', '0x00517CF0', own, {'NPC', 'CCBLineupWindow'}) == 'P:misowned'
    assert classify_ownership('NPC', '0x00517CF0', own, {'CCBLineupWindow'}) == 'Q:table_not_located'


def test_classify_multi_and_absent():
    own = {'0x0043DE40': [('UIListBox', 3, '0x0056AD20'), ('UICoverFrm', 3, '0x0056B100')]}
    assert classify_ownership('UIListBox', '0x0043DE40', own, {'UIListBox'}) == 'P:multi_owned'
    assert classify_ownership('NPC', '0x00999999', own, {'NPC'}) == 'Q:not_in_located_tables'


def test_r2_absence_verdict_is_question_not_p():
    """R2：表未定位/缺位一律 Q 档（不准确=不判定——absence 禁判 P）。"""
    own = {'0x0043de40': [('Object', 0, '0x00500000')]}   # 持有表部分定位
    assert classify_ownership('ScriptObj', '0x0043de40', own, {'Object'}) == 'Q:table_not_located'
    assert classify_ownership('NPC', '0x00999999', own) == 'Q:not_in_located_tables'


def test_b_findh_table_hole_tolerant():
    """B：容洞序列定位——认领槽序在表中允许跳洞（非连续认领/继承槽空隙）。"""
    from audit_vtable_ownership import find_table_holes
    mem = {}
    # 表址 0x560000：slot0=0x401000, [洞 2 槽], slot=0x402000, [洞], slot=0x403000
    seq = [0x401000, 0x402000, 0x403000]
    for i, v in [(0, 0x401000), (3, 0x402000), (5, 0x403000)]:
        for b in range(4):
            mem[0x560000 + 4*i + b] = (v >> (8*b)) & 0xFF
    assert find_table_holes(mem, seq, max_gap=3) == 0x560000


def test_b_findh_rejects_scattered():
    from audit_vtable_ownership import find_table_holes
    mem = {}
    for i, v in [(0, 0x401000), (20, 0x402000)]:   # 巨洞=拒绝
        for b in range(4):
            mem[0x560000 + 4*i + b] = (v >> (8*b)) & 0xFF
    assert find_table_holes(mem, [0x401000, 0x402000], max_gap=3) is None


def test_c_find_table_cluster_locates():
    """骨架认领复活：全 mem 聚集扫描（类方法址 ≥2 聚窗 → 真表址）。"""
    from audit_vtable_ownership import find_table_cluster
    mem = {}
    # 真表在 0x571000（认领址 0x56abb8 无关）：窗内聚集 2 方法址
    for i, v in [(0, 0x402000), (2, 0x403000), (4, 0x401000)]:
        for b in range(4):
            mem[0x571000 + 4*i + b] = (v >> (8*b)) & 0xFF
    got = find_table_cluster(mem, [0x402000, 0x403000, 0x404000])
    assert got == 0x571000, got


def test_c_find_table_cluster_rejects_scattered():
    from audit_vtable_ownership import find_table_cluster
    mem = {}
    for i, v in [(0, 0x402000), (50, 0x403000)]:
        for b in range(4):
            mem[0x571000 + 4*i + b] = (v >> (8*b)) & 0xFF
    assert find_table_cluster(mem, [0x402000, 0x403000]) is None
