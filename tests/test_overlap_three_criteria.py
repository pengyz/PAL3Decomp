# R15（data/status/_d1_ledger.md）：三判据机械扫纯函数单测（值位面/取址/重解释）
from tools.audit_member_semantics import overlap_three_criteria as T

def test_value_bitplane_int_write():
    frags = ['g_17A8Data.m_nEffParam10 = -1054867456;', 'm_nEffParam0 = 1065353216']
    r = T(frags, 'm_nEffParam10')
    assert r['值位面'] == 1
    r2 = T(frags, 'm_nEffParam0')
    assert r2['值位面'] == 1

def test_address_of_member():
    frags = ['v = (const char *)&m_nEffParam0 + 4;', 'p = &g.m_x']
    r = T(frags, 'm_nEffParam0')
    assert r['取址'] >= 1

def test_cast_deref_reinterpret():
    frags = ['*(float *)&this->m_InnerActor = acos(v);', 'w = *(float *)&m_nEffParamBase[2]']
    r = T(frags, 'm_InnerActor')
    assert r['重解释'] >= 1

def test_plain_assignment_is_not_enough():
    frags = ['g.m_nEffParam10 = v34;']
    r = T(frags, 'm_nEffParam10')
    assert r['值位面'] == 0 and r['取址'] == 0 and r['重解释'] == 0

def test_name_match_is_exact_token():
    frags = ['g.m_nEffParam100 = 1;']
    r = T(frags, 'm_nEffParam10')
    assert sum(r.values()) == 0

def test_verdict_helper():
    from tools.audit_member_semantics import overlap_verdict as V
    assert V({'值位面':1,'取址':0,'重解释':0}) == 'member-真'
    assert V({'值位面':0,'取址':0,'重解释':0}) == '无多视图形'
