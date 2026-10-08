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

    def test_mi_positive_accepted(self):
        """MI 正向：Role 场景（56+8+32=96）应通过。"""
        ok, reason = check_chain(
            derived_size=8704,
            base_sizes=[56, 8, 32],
            declared_base_size=96,
        )
        self.assertTrue(ok, reason)

    def test_declared_base_size_not_enforced(self):
        """base_size 语义不一致（CEffSParticle 反例）⇒ 仅 informational，不硬拒。"""
        ok, reason = check_chain(
            derived_size=100,
            base_sizes=[12, 36],
            declared_base_size=16,   # ≠ sum(48)，但本仓有此类不自洽
        )
        self.assertTrue(ok, 'declared_base_size 不应硬拒')


if __name__ == '__main__':
    unittest.main()
