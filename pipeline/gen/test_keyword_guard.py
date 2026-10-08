"""codegen 关键字守卫 TDD（Phase 2——复核方案·纪律流程）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestKeywordGuard(unittest.TestCase):
    def test_keyword_name_rejected(self):
        # 毒名样张：int/void 当函数名——拒收
        from ast_transform import is_valid_identifier
        self.assertFalse(is_valid_identifier('int'))
        self.assertFalse(is_valid_identifier('void'))
        self.assertFalse(is_valid_identifier('char'))

    def test_valid_name_accepted(self):
        from ast_transform import is_valid_identifier
        self.assertTrue(is_valid_identifier('ActArray_Assign'))
        self.assertTrue(is_valid_identifier('_todo_0053BAE0'))

    def test_keyword_set(self):
        from ast_transform import CPP_KEYWORDS
        self.assertIn('int', CPP_KEYWORDS)
        self.assertIn('void', CPP_KEYWORDS)
        self.assertNotIn('MyFunc', CPP_KEYWORDS)


if __name__ == '__main__':
    unittest.main()
