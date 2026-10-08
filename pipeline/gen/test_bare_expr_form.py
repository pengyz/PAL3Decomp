"""C2273 裸表达式形 TDD（B1 值形——表达式内读·纪律流程）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestBareExprForm(unittest.TestCase):
    def test_bare_expr_read(self):
        # 样张：f(this->m_dlg.UIWnd)（表达式内裸读）→ f(*(W*)&this->m_dlg)
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'f(this->m_dlg.UIWnd);'
        out = rewrite_base_suffix_bare_form(s, base_names={'UIWnd'}, base_sizes={'UIWnd': 4})
        self.assertIn('*(_DWORD *)&this->m_dlg', out)

    def test_semicolon_preserved(self):
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'f(this->m_dlg.UIWnd);'
        out = rewrite_base_suffix_bare_form(s, base_names={'UIWnd'}, base_sizes={'UIWnd': 4})
        self.assertIn(';', out)


if __name__ == '__main__':
    unittest.main()
