"""codegen 参铸扩展 TDD（C2664 族通解——签名参型 vs 实参型铸补）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestArgTypeCast(unittest.TestCase):
    def test_arg_cast_insertion(self):
        # 样张：SetLibFolder(&this->m_bBigFont) vs const char* → (const char*)&this->m_bBigFont
        from ast_transform import fix_arg_type_casts
        s = 'X->SetLibFolder(&this->m_bBigFont);'
        out = fix_arg_type_casts(s, sig_params=['const char *'])
        self.assertIn('(const char *)&this->m_bBigFont', out)

    def test_already_casted_untouched(self):
        from ast_transform import fix_arg_type_casts
        s = 'X->SetLibFolder((const char *)&this->m_x);'
        self.assertEqual(fix_arg_type_casts(s, sig_params=['const char *']), s)

    def test_arity_mismatch_untouched(self):
        # 元数门（复核结论）：参不齐不动
        from ast_transform import fix_arg_type_casts
        s = 'X->SetLibFolder(&a, &b);'
        self.assertEqual(fix_arg_type_casts(s, sig_params=['const char *']), s)

    def test_no_sig_untouched(self):
        from ast_transform import fix_arg_type_casts
        s = 'X->SetLibFolder(&a);'
        self.assertEqual(fix_arg_type_casts(s, sig_params=[]), s)


if __name__ == '__main__':
    unittest.main()
