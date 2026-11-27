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

    # ---- #63 回归：箭头形 + 内嵌接收者 ----
    def test_arrow_embedded_receiver_value(self):
        # `h->m.Base` 里 h->m 是内嵌对象 ⇒ 取址形 `*(T*)&h->m`（与真指针接收者相反）
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'v = p_holder->m_fadeIn.PalScriptWaitObj;'
        out = rewrite_base_suffix_bare_form(
            s, base_names={'PalScriptWaitObj'}, base_sizes={'PalScriptWaitObj': 4})
        self.assertEqual(out.strip(), 'v = *(_DWORD *)&p_holder->m_fadeIn;')
        self.assertIn('&p_holder->m_fadeIn', out)

    def test_qualified_base_name_untouched(self):
        # `x.Base::m` 是限定名，不是基类子对象访问 ⇒ 一个字都不改
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'x.PalScriptWaitObj::m_age = 1;'
        out = rewrite_base_suffix_bare_form(
            s, base_names={'PalScriptWaitObj'}, base_sizes={'PalScriptWaitObj': 4})
        self.assertEqual(out, s)


if __name__ == '__main__':
    unittest.main()
