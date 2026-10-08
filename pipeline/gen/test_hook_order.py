"""挂账⑥ N1 echo 门序敏感性钉测（hook 顺序固化——类判定挪前暴露 id_type_ 名裂口教训）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
sys.path.insert(0, os.path.join(_GEN, 'stages'))
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestHookOrderPinned(unittest.TestCase):
    def test_stage2_hook_order(self):
        # N1：hook 序=fix_struct_value_casts→rewrite_unqualified_member_call→drop_call_echo_arg
        # （类判定挪前=暴露 id_type_ 名裂口（s_RoleState 200→210 实证）——序固化）
        import inspect
        import stage2_semantic
        src = inspect.getsource(stage2_semantic)
        i1 = src.find('fix_struct_value_casts(')
        i2 = src.find('rewrite_unqualified_member_call(')
        i3 = src.find('drop_call_echo_arg(')
        self.assertTrue(0 < i1 < i2 < i3, "hook 序被改动：%d/%d/%d" % (i1, i2, i3))

    def test_echo_drop_after_member_rewrite(self):
        # 回波剔除必须在成员调用改写之后（echo 形=改写后才暴露）
        import inspect
        import stage2_semantic
        src = inspect.getsource(stage2_semantic)
        self.assertLess(src.find('rewrite_unqualified_member_call('),
                        src.find('drop_call_echo_arg('))


if __name__ == '__main__':
    unittest.main()
