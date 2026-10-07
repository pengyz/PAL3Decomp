"""宏规避形修 TDD（CreateDialog 型——C2629 根因·纪律流程）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestMacroSafeForm(unittest.TestCase):
    def test_paren_name_form(self):
        # 样张：int (CreateDialog)(...) → int CreateDialog_(...)（宏安全后缀）
        from ast_transform import fix_macro_safe_decl
        s = 'int (CreateDialog)(int id);'
        out = fix_macro_safe_decl(s)
        self.assertNotIn('(CreateDialog)', out)

    def test_normal_decl_untouched(self):
        from ast_transform import fix_macro_safe_decl
        s = 'int MyFunc(int id);'
        self.assertEqual(fix_macro_safe_decl(s), s)

    def test_semicolon_preserved(self):
        from ast_transform import fix_macro_safe_decl
        s = 'int (CreateDialog)(int id);'
        out = fix_macro_safe_decl(s)
        self.assertIn(';', out)


if __name__ == '__main__':
    unittest.main()
