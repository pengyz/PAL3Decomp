# tests/test_size_grid_gate.py
import unittest
from tools.size_grid_gate import check_chain


class TestSizeGridGate(unittest.TestCase):
    def test_kb_chain_rejected(self):
        """KB 链 UIWnd→SceneObj→CGameData 应被尺寸格否决（68<1784<28268）。"""
        # 派生尺寸必须 ≥ 每个基类尺寸
        ok, reason = check_chain(
            derived_size=68,
            base_sizes=[1784, 28268],   # SceneObj, CGameData
        )
        self.assertFalse(ok)
        self.assertIn('68', reason)

    def test_correct_chain_accepted(self):
        """正确链 SceneObj(1784) : UIWnd(68) 应通过。"""
        ok, reason = check_chain(
            derived_size=1784,
            base_sizes=[68],
        )
        self.assertTrue(ok, reason)

    def test_base_size_must_match_first_base(self):
        """base_size 必须 == 首基尺寸。"""
        ok, reason = check_chain(
            derived_size=1784,
            base_sizes=[68],
            declared_base_size=100,  # 与基类之和 68 不符
        )
        self.assertFalse(ok)
        self.assertIn('base_size', reason)


if __name__ == '__main__':
    unittest.main()
