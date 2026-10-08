"""B′ 形扩展 TDD（复核样张表——F1 裸值形/F3 函数式铸·"+0 全称"守卫）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestBaseSuffixForm(unittest.TestCase):
    def test_f1_write_value_form(self):
        # 样张1：this->info.ObjectInfoBase = 0 → *(_DWORD *)&this->info = 0
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'this->info.ObjectInfoBase = 0;'
        out = rewrite_base_suffix_bare_form(s, base_names={'ObjectInfoBase'},
                                            base_sizes={'ObjectInfoBase': 4})
        self.assertIn('*(_DWORD *)&this->info', out)

    def test_f1_bare_read_form(self):
        # 样张2：LODWORD(x) = this->m_FrameA.UIWnd → = *(_DWORD *)&this->m_FrameA
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'LODWORD(x) = this->m_FrameA.UIWnd;'
        out = rewrite_base_suffix_bare_form(s, base_names={'UIWnd'},
                                            base_sizes={'UIWnd': 4})
        self.assertIn('*(_DWORD *)&this->m_FrameA', out)

    def test_f1_indexed_chain(self):
        # 样张3：(int)this->m_ani[6].UIWnd → *(W *)&this->m_ani[6]（宽度语义——型名等宽）
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'v9 = (int)this->m_ani[6].UIWnd;'
        out = rewrite_base_suffix_bare_form(s, base_names={'UIWnd'},
                                            base_sizes={'UIWnd': 4})
        self.assertIn('&this->m_ani[6]', out)      # recv 链+下标保持
        self.assertNotIn('.UIWnd', out)            # 基类后缀消

    def test_zero_offset_universal_guard(self):
        # 反例：+0 全称守卫——UIFrameWnd 混偏移（MUIDialog@76）不得名字级改写
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'x = this->m_dlg.UIFrameWnd;'
        out = rewrite_base_suffix_bare_form(s, base_names={'UIFrameWnd'},
                                            base_sizes={'UIFrameWnd': 4},
                                            nonzero_offsets={('MUIDialog', 'UIFrameWnd'): 76})
        self.assertEqual(out, s)   # 混偏移名——不动

    def test_qualified_form_untouched(self):
        # 反例：`::` 守卫（x.Base::m 不动）
        from ast_transform import rewrite_base_suffix_bare_form
        s = 'x.Base::m = 1;'
        self.assertEqual(rewrite_base_suffix_bare_form(s, base_names={'Base'},
                                                       base_sizes={'Base': 4}), s)


if __name__ == '__main__':
    unittest.main()
