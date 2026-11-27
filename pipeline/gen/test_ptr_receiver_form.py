"""C2273 指针接收者扩展 TDD（B1 值形——v11-> 型·纪律流程）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestPtrReceiverValueForm(unittest.TestCase):
    def test_ptr_receiver_value_read(self):
        # 样张：v11->m_FrameA.UIWnd → *(W*)&v11->m_FrameA（指针接收者）
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'x = v11->m_FrameA.UIWnd;'
        out = rewrite_base_suffix_bare_form(s, base_names={'UIWnd'}, base_sizes={'UIWnd': 4})
        self.assertIn('*(_DWORD *)&v11->m_FrameA', out)
        self.assertIn(';', out)

    def test_semicolon_preserved(self):
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'x = v11->m_FrameA.UIWnd;'
        out = rewrite_base_suffix_bare_form(s, base_names={'UIWnd'}, base_sizes={'UIWnd': 4})
        self.assertTrue(out.rstrip().endswith(';'))

    # ---- #63 回归：箭头形 + 真指针接收者 ----
    def test_arrow_ptr_receiver_value_write(self):
        # `p->Base = 0;` 里 p 是真指针 ⇒ 取 `*(T*)p`，绝不能出 `&p`（那是指针变量自身的地址）
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'p_m_fadeIn->PalScriptWaitObj = 0;'
        out = rewrite_base_suffix_bare_form(
            s, base_names={'PalScriptWaitObj'}, base_sizes={'PalScriptWaitObj': 4})
        self.assertEqual(out.strip(), '*(_DWORD *)p_m_fadeIn = 0;')
        self.assertNotIn('&p_m_fadeIn', out)

    def test_arrow_ptr_receiver_value_read(self):
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'v = p_m_fadeIn->PalScriptWaitObj;'
        out = rewrite_base_suffix_bare_form(
            s, base_names={'PalScriptWaitObj'}, base_sizes={'PalScriptWaitObj': 4})
        self.assertEqual(out.strip(), 'v = *(_DWORD *)p_m_fadeIn;')
        self.assertNotIn('&p_m_fadeIn', out)


if __name__ == '__main__':
    unittest.main()
