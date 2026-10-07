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


if __name__ == '__main__':
    unittest.main()
