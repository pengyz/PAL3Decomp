"""B1 限定链最小修 TDD（复核修订 1-B：删冗余中间限定词）。
`recv->A::Base::m` → `recv->Base::m`（单层形现绿据——N5 越墙最小面）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
sys.path.insert(0, os.path.join(_GEN, 'stages'))
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestDropRedundantMidQualifier(unittest.TestCase):
    def test_multilevel_chain_simplified(self):
        # 病灶样张：m_pRoleState->SceneObj::GlowObj::m_nTodo_000 → m_pRoleState->GlowObj::m_nTodo_000
        from ast_transform import drop_redundant_mid_qualifier
        s = 'm_pRoleState->SceneObj::GlowObj::m_nTodo_000 = v7;'
        out = drop_redundant_mid_qualifier(s)
        self.assertIn('m_pRoleState->GlowObj::m_nTodo_000', out)
        self.assertNotIn('SceneObj::', out)

    def test_single_level_untouched(self):
        # N5 墙：单层 recv->Base::m 现绿不动
        from ast_transform import drop_redundant_mid_qualifier
        s = 'v4->UIWnd::sub_445FA0(1);'
        self.assertEqual(drop_redundant_mid_qualifier(s), s)

    def test_dot_receiver(self):
        from ast_transform import drop_redundant_mid_qualifier
        s = 'x.SceneObj::GlowObj::m_y = 1;'
        out = drop_redundant_mid_qualifier(s)
        self.assertIn('x.GlowObj::m_y', out)

    def test_masked_strings_untouched(self):
        from ast_transform import drop_redundant_mid_qualifier
        s = 'sprintf(buf, "a->A::B::m");'
        self.assertEqual(drop_redundant_mid_qualifier(s), s)

    def test_comment_adjacent_no_corrosion(self):
        # 返工（验收红线）：注释紧邻不腐蚀（掩码 x 禁入替换）
        from ast_transform import drop_redundant_mid_qualifier
        s = 'p->A::B::m/*c*/;'
        out = drop_redundant_mid_qualifier(s)
        self.assertIn('/*c*/', out)              # 注释保真
        self.assertNotIn('mxxx', out)             # 无静默改名

    def test_idempotent(self):
        from ast_transform import drop_redundant_mid_qualifier
        s = 'm_pRoleState->SceneObj::GlowObj::m_nTodo_000 = v7;'
        once = drop_redundant_mid_qualifier(s)
        twice = drop_redundant_mid_qualifier(once)
        self.assertEqual(once, twice)


if __name__ == '__main__':
    unittest.main()
