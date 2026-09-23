"""对齐语义测试 —— ARC_PlayerAtt / sg_* 家族（TDD 留存，实现待落）。

问题定义（确定性）：C++ struct 布局由成员类型与顺序唯一决定。
`ARC_PlayerItem`（DWORD+int+short=10 字节）按对齐 4 编译实占 **12**，
发射器若按 ida_structs['size']=10 记账 ⇒ 0x36A 错误 gap ⇒ +4 漂移 ✗。

已验证 ✗ 的路线（r10，勿重复）：
- `_estimate_member_size` 全局对齐取整 ⇒ S2 76→36 灾难（内嵌奇尺寸类布局翻转无级联）
- `_gap_needed` 自然填充抑制 ⇒ Role 42/47（对齐推断 ≠ 真实打包）
⇒ 正解：**逐类型证据落地**（如 ARC_PlayerItem binary_size 10→12 须伴随 ARC_PlayerAtt 级联，
  而该类注解内部 stride 自相矛盾 ⇒ 判定整类重建，见 ledger goal r11）。

本文件暂存对齐语义断言，待实现落地时启用（当前部分 RED 属预期）。
运行：`python3 tests/test_gap_alignment.py`
"""
import sys
from pathlib import Path
PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT)); sys.path.insert(0, str(PROJECT_ROOT/'pipeline')); sys.path.insert(0, str(PROJECT_ROOT/'pipeline'/'gen'))
from stages import emit_headers as E
import unittest

@unittest.skip("对齐取整实现待按类级联落地（r10 回退，见 ledger）")
class TestPending(unittest.TestCase):
    def test_estimate_uses_aligned_size(self):
        self.assertEqual(E._estimate_member_size('ARC_PlayerItem'), 12)

class TestLanded(unittest.TestCase):
    def test_d3dx_estimate(self):
        """D3DX 类型尺寸（已落地 ✓ sdk_types 8 条）"""
        self.assertEqual(E._estimate_member_size('D3DXVECTOR3'), 12)
        self.assertEqual(E._estimate_member_size('D3DXCOLOR'), 16)

    def test_primitives_unchanged(self):
        assert E._estimate_member_size('int') == 4
        assert E._estimate_member_size('unsigned char') == 1
        assert E._estimate_member_size('void *') == 4

if __name__ == '__main__':
    unittest.main(verbosity=2)
