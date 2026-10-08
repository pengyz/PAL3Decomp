"""批 5（工具批）：reg_ 伪名赋值 RHS 显式铸统一测试（import 生产函数——影子副本教训）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
sys.path.insert(0, os.path.join(_GEN, 'stages'))
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))
from stage5_fixup import cast_reg_assignments


class TestCastRegAssignments(unittest.TestCase):
    def test_addr_rhs_cast(self):
        s = 'reg_EDI = &this->m_ptr_20 + 2;'
        out = cast_reg_assignments(s)
        self.assertIn('(unsigned long)(&this->m_ptr_20 + 2)', out)

    def test_member_read_cast(self):
        s = 'reg_EBP = g_pRoleSystem;'
        self.assertIn('(unsigned long)(g_pRoleSystem)', cast_reg_assignments(s))

    def test_int_literal_untouched(self):
        s = 'reg_EAX = 0;'
        self.assertEqual(cast_reg_assignments(s), s)

    def test_reg_to_reg_untouched(self):
        s = 'reg_EAX = reg_EBX;'
        self.assertEqual(cast_reg_assignments(s), s)

    def test_already_cast_untouched(self):
        s = 'reg_EAX = (unsigned long)x;'
        self.assertEqual(cast_reg_assignments(s), s)

    def test_non_reg_untouched(self):
        s = 'v1 = this->m_x;'
        self.assertEqual(cast_reg_assignments(s), s)

    def test_double_equal_not_eaten(self):
        # 复核 B1（RoleSystem.cpp:802 真语料形）
        s = 'if (reg_EAX == g_pRoleSystem) return 1;'
        self.assertEqual(cast_reg_assignments(s), s)

    def test_comma_rhs_conservative(self):
        # 复核 B2（逗号表达式语义反转）
        s = 'reg_EAX = a, b;'
        self.assertEqual(cast_reg_assignments(s), s)

    def test_string_content_untouched(self):
        # 掩码纪律（E-1）
        s = 'sprintf(buf, "reg_EAX = x;");'
        self.assertEqual(cast_reg_assignments(s), s)

    def test_mixed_arith_rhs_cast(self):
        # MUT-B 杀手（数字豁免放宽的检测）
        s = 'reg_EAX = 4 + v61;'
        self.assertIn('(unsigned long)(4 + v61)', cast_reg_assignments(s))

    def test_chained_assign_conservative(self):
        s = 'reg_A = reg_B = ptr;'
        self.assertEqual(cast_reg_assignments(s), s)

    def test_rhs_string_preserved(self):
        # 复判 M5（掩码 x 替身毁字面量——rhs 须从原文取）
        s = 'reg_EAX = (int)"TEXT";'
        out = cast_reg_assignments(s)
        self.assertIn('"TEXT"', out)
        self.assertNotIn('"xxxx"', out)

    def test_non_statement_boundary_conservative(self):
        # A8/A9（非语句边界错捕保守）——终验建议补 while 形（判别力钉边界判）
        s = 'f(reg_EAX = p);'
        self.assertEqual(cast_reg_assignments(s), s)
        s2 = 'while (x) reg_EAX = p;'
        self.assertEqual(cast_reg_assignments(s2), s2)

    def test_unbalanced_paren_conservative(self):
        s = 'reg_EAX = f(a, b;'
        self.assertEqual(cast_reg_assignments(s), s)

    def test_vt_initializer_decl_locked(self):
        # 批 7 锁定测试（复核必补欠账①）：初始化声明入 vt + 既有精确铸触发
        from stage5_fixup import _build_var_types, _fix_line_plain_var_assign
        code = ('void F(void)\n{\n'
                '    unsigned long reg_EDI = 0;\n'
                '    reg_EDI = &this->m_ptr_20 + 2;\n}\n')
        vt = _build_var_types(code, None)
        self.assertIn('reg_EDI', vt)                      # 突变杀点（旧正则不收）
        out = _fix_line_plain_var_assign(
            '    reg_EDI = &this->m_ptr_20 + 2;', vt, None)
        self.assertIn('(unsigned long)(&this->m_ptr_20 + 2)', out)  # 正识别铸断言

    def test_rolled_back_batch8_behavior(self):
        # 【批 8 回退态断言】三修件已撤（零回归门：撤载重铸真新增 2——
        # "撤铸≠恒等"教训）。断言现行为：箭头分裂保留/单星判指针保留/歧义不标。
        from stage5_fixup import _build_var_types, _expr_is_pointer
        code = ('void F(void)\n{\n    RoleAtt *v208;\n    int *p;\n'
                '    int result;\n}\nvoid G(void)\n{\n    RoleAtt *result;\n}\n')
        vt = _build_var_types(code, None)
        # 箭头分裂保留（回退态：v208 指针 ⇒ True）
        self.assertTrue(_expr_is_pointer('v208->m_anything', vt, None))
        # 单星判指针保留（回退态：*p p=int* ⇒ True）
        self.assertTrue(_expr_is_pointer('*p', vt, None))
        # 歧义追踪亦已撤（批 8 全撤——_add 回 setdefault）
        self.assertFalse(bool(vt['result'].get('ambiguous')))


if __name__ == '__main__':
    unittest.main()
