"""per-lvar ordinal 定位 TDD（复核 R4——同址多 lvar 拆名）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestLvarOrdinal(unittest.TestCase):
    def test_ordinal_positioning(self):
        # 样张：同址 14 lvar——ordinal 定位（第 2..14 个）
        from ast_transform import position_lvar_by_ordinal
        lvars = [{'stkoff': 56, 'name': 'a', 'type': 'void*'},
                 {'stkoff': 56, 'name': 'b', 'type': 'int'},
                 {'stkoff': 56, 'name': 'c', 'type': 'gbVec3D*'}]
        v = position_lvar_by_ordinal(lvars, stkoff=56, ordinal=1)
        self.assertEqual(v['name'], 'b')       # ordinal=1=第 2 个

    def test_ordinal_out_of_range(self):
        from ast_transform import position_lvar_by_ordinal
        lvars = [{'stkoff': 56, 'name': 'a'}]
        v = position_lvar_by_ordinal(lvars, stkoff=56, ordinal=5)
        self.assertIsNone(v)

    def test_name_collision_split(self):
        # 样张：pSceneName 跨址（56/60）——按址归名
        from ast_transform import split_lvar_names_by_addr
        lvars = [{'stkoff': 56, 'name': 'pSceneName', 'type': 'void*'},
                 {'stkoff': 60, 'name': 'pSceneName', 'type': 'gbVec3D*'}]
        out = split_lvar_names_by_addr(lvars)
        names = set(v['name'] for v in out)
        self.assertEqual(len(names), 2)         # 跨址拆名


if __name__ == '__main__':
    unittest.main()
