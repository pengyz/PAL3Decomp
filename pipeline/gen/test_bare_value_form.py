"""C2273 值形扩展 TDD（B1 裸值读形——纪律流程：TDD 先行）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestBareValueReadForm(unittest.TestCase):
    def test_bare_value_read(self):
        # 样张：x = this->m_dlg.UIWnd;（裸值读——非赋值形）→ *(W*)&this->m_dlg
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'v = this->m_dlg.UIWnd;'
        out = rewrite_base_suffix_bare_form(s, base_names={'UIWnd'}, base_sizes={'UIWnd': 4})
        self.assertIn('*(_DWORD *)&this->m_dlg', out)
        self.assertIn(';', out)              # 分号保全（复核红线）

    def test_semicolon_preserved(self):
        # 复核红线：分号保全
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'x.Base = 1;'
        out = rewrite_base_suffix_bare_form(s, base_names={'Base'}, base_sizes={'Base': 4})
        self.assertTrue(out.rstrip().endswith(';'))

    def test_non_base_name_untouched(self):
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'x.m_value = 1;'
        self.assertEqual(rewrite_base_suffix_bare_form(s, base_names={'UIWnd'}, base_sizes={'UIWnd': 4}), s)


if __name__ == '__main__':
    unittest.main()
