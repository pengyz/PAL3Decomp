"""归属守卫（B1）——CLAUDE.md 归属规则工具化：成员访问证据判归属。
红牌=体访问 this->X 且 X 不在声明类而在他类；黄牌=未验认领+异类转换。
运行: pytest tests/test_attribution_guard.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from audit_attribution_guard import extract_this_member_refs, classify_claim


def test_extract_this_member_refs():
    body = 'v2 = &this->m_AnimWndC + 280;\n  x = this->m_nState;\n  ((CCBLineupWindow *)this)->Reset();'
    refs = extract_this_member_refs(body)
    assert refs == {'m_AnimWndC', 'm_nState'}, refs


def test_red_flag_member_in_other_class_only():
    r = classify_claim(
        body='x = this->m_AnimWndC;', claimed='NPC',
        claimed_members={'m_nHP', 'm_nState'}, other_classes={'CCBLineupWindow': {'m_AnimWndC'}},
        evidence_level='unverified', cross_casts={'CCBLineupWindow'})
    assert r['flags'] == ['RED:member_in_other_class'], r


def test_yellow_unverified_with_crosscast():
    r = classify_claim(
        body='x = this->m_nState;', claimed='NPC',
        claimed_members={'m_nState'}, other_classes={},
        evidence_level='unverified', cross_casts={'CCBLineupWindow'})
    assert r['flags'] == ['YELLOW:unverified+crosscast'], r


def test_clean_verified_no_flag():
    r = classify_claim(
        body='x = this->m_nState;', claimed='NPC',
        claimed_members={'m_nState'}, other_classes={},
        evidence_level='A', cross_casts=set())
    assert r['flags'] == [], r


def test_b2b_build_member_index_merges_ida_structs():
    """B2b：成员索引=ida_structs.data_members ∪ structs.known_members（双源合并）。"""
    from audit_attribution_guard import build_member_index
    ida = {'UIListBox': {'data_members': [{'name': 'm_scrollbar', 'offset': 80}]},
           'NPC': {'data_members': [{'name': 'm_nHP', 'offset': 16}]}}
    structs = {'UIListBox': {'known_members': [{'name': 'm_selcolor'}]},
               'CCBLineupWindow': {'known_members': [{'name': 'm_AnimWndC'}]}}
    idx = build_member_index(ida, structs)
    assert idx['UIListBox'] == {'m_scrollbar', 'm_selcolor'}, idx
    assert idx['CCBLineupWindow'] == {'m_AnimWndC'}
    assert idx['NPC'] == {'m_nHP'}
