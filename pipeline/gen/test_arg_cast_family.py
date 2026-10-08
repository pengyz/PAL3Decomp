"""C2664 参型铸族级批 TDD（优先③·纪律流程）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestArgCastFamily(unittest.TestCase):
    def test_multi_param_cast(self):
        # 族级：多参铸补（sig 多参）
        from ast_transform import fix_arg_type_casts
        s = 'X->M(&a, &b);'
        out = fix_arg_type_casts(s, sig_params=['const char *', 'int *'])
        self.assertIn('(const char *)', out)
        self.assertIn('(int *)', out)

    def test_single_param(self):
        from ast_transform import fix_arg_type_casts
        s = 'X->M(&a);'
        out = fix_arg_type_casts(s, sig_params=['const char *'])
        self.assertIn('(const char *)', out)

    def test_arity_mismatch_untouched(self):
        from ast_transform import fix_arg_type_casts
        s = 'X->M(&a, &b, &c);'
        self.assertEqual(fix_arg_type_casts(s, sig_params=['const char *']), s)


if __name__ == '__main__':
    unittest.main()
