"""S2 族级批 TDD（C2273/C2664/C2660 三件——优先③·纪律流程）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestS2FamilyBatch(unittest.TestCase):
    def test_c2273_fnptr_qualified(self):
        # C2273：x->Type(...) fn-ptr 形→限定调用形（x->Base::M 形）
        from ast_transform import fix_fnptr_qualified_call
        s = 'x->UIWnd(1);'
        out = fix_fnptr_qualified_call(s, base_names={'UIWnd'})
        self.assertNotEqual(out, s)           # 形变（fn-ptr→限定）

    def test_c2664_arg_cast(self):
        # C2664：参型铸补（已验）
        from ast_transform import fix_arg_type_casts
        s = 'X->SetLibFolder(&this->m_bBigFont);'
        out = fix_arg_type_casts(s, sig_params=['const char *'])
        self.assertIn('(const char *)', out)

    def test_semicolon_preserved(self):
        from ast_transform import fix_arg_type_casts
        s = 'X->M(&a);'
        out = fix_arg_type_casts(s, sig_params=['const char *'])
        self.assertIn(';', out)


if __name__ == '__main__':
    unittest.main()
