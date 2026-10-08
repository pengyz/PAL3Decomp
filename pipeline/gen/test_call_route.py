"""调用路由修 TDD（复核 R-A/R-B/R-C）：stage5:1655 门控——成员形/保留原文。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestCallRoute(unittest.TestCase):
    def test_global_name_keeps_original(self):
        # 病灶样张1：UIScene_InitScriptScene((int)this) in CUtil → 保留原文（还原实参）
        from stage5_fixup import call_route
        v = call_route('UIScene_InitScriptScene', 'CUtil',
                       member_index={'CUtil': set()}, classless={'UIScene_InitScriptScene'})
        self.assertEqual(v, 'keep')

    def test_true_self_call_member(self):
        # 样张2：Destroy((int)this) in CCBControlWindow（基类链 UIFrameWnd 命中）→ member
        from stage5_fixup import call_route
        v = call_route('Destroy', 'CCBControlWindow',
                       member_index={'CCBControlWindow': set(),
                                     'UIFrameWnd': {'Destroy'}},
                       classless={'Destroy'})
        self.assertEqual(v, 'member')

    def test_same_name_member_wins(self):
        # 样张3：同名歧义——类+基类链有成员 ⇒ member（保守）
        from stage5_fixup import call_route
        v = call_route('X', 'A',
                       member_index={'A': {'X'}}, classless={'X'})
        self.assertEqual(v, 'member')

    def test_no_hit_keeps_original(self):
        # 样张4：全无命中→keep（不编造）
        from stage5_fixup import call_route
        v = call_route('Unknown', 'A',
                       member_index={'A': set()}, classless=set())
        self.assertEqual(v, 'keep')


if __name__ == '__main__':
    unittest.main()
