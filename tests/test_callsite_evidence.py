"""P3 调用面证据（2026-10-30）——调用形三分类：归属第三证据源（质疑级增强，非判定）。
运行: pytest tests/test_callsite_evidence.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from audit_callsite_evidence import classify_call_form, summarize_callsites


def test_member_qualified_and_bare():
    assert classify_call_form('  v->CCBLineupWindow::Reset(x);', 'Reset') == 'member'
    assert classify_call_form('  p->Reset(x);', 'Reset') == 'member'
    assert classify_call_form('  CCBLineupWindow::Reset((X *)this, x);', 'Reset') == 'qualified'
    assert classify_call_form('  Reset(x);', 'Reset') == 'bare'


def test_non_call_untouched():
    assert classify_call_form('  m_nReset = 1;', 'Reset') is None
    assert classify_call_form('  v->Resetting(x);', 'Reset') is None


def test_summarize_counts():
    texts = ['v->NPC::Reset(1);', 'NPC::Reset(2);', 'Reset(3);', 'v->Reset(4);']
    s = summarize_callsites(texts, 'Reset')
    assert s == {'member': 2, 'qualified': 1, 'bare': 1}, s
