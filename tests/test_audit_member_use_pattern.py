"""[T76] R15 单测：audit_member_use_pattern 判定层（四形 + F3 路复核 4 反例）。"""
import sys
import os
import unittest

_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
sys.path.insert(0, os.path.join(_ROOT, 'tools'))

from audit_member_use_pattern import judge  # noqa: E402


class TestJudge(unittest.TestCase):
    def test_pointer_deref(self):
        self.assertEqual(
            judge('mov eax,DWORD PTR [esi+0x200]', ['mov ecx,DWORD PTR [eax]']), 'pointer')

    def test_scalar_arith(self):
        self.assertEqual(
            judge('mov ecx,DWORD PTR [esi+0x978]', ['add eax,ecx']), 'scalar')

    def test_float(self):
        self.assertEqual(judge('fstp DWORD PTR [ecx+0x200]', ['fld DWORD PTR [eax]']), 'float')

    def test_embedded(self):
        self.assertEqual(judge('lea ecx,[edi+0xa10]', ['mov eax,DWORD PTR [ecx]']), 'embedded-object')

    # [F3 反例 a] 不追踪载值寄存器：解引用的是 esi 不是 eax ⇒ 不得判 pointer
    def test_counterexample_a_wrong_register(self):
        out = judge('mov eax,DWORD PTR [esi+0x978]', ['mov ecx,DWORD PTR [esi+0x4c]'])
        self.assertNotEqual(out, 'pointer')

    # [F3 反例 b] 只看紧邻一条：窗口内第三条是算术 ⇒ 标量（不是 pointer）
    def test_counterexample_b_window(self):
        out = judge('mov eax,DWORD PTR [esi+0x978]',
                    ['mov ecx,DWORD PTR [esi+0x54]', 'sub eax,ecx', 'ret'])
        self.assertEqual(out, 'scalar')

    # [F3 反例 c] 指针判空 test eax,eax ⇒ pointer（不得落 scalar）
    def test_counterexample_c_null_check(self):
        out = judge('mov eax,DWORD PTR [esi+0x200]', ['test eax,eax'])
        self.assertEqual(out, 'pointer')

    # [F3 反例 d] 多证冲突 ⇒ undetermined（禁一票定案）
    def test_counterexample_d_conflict(self):
        out = judge('mov eax,DWORD PTR [esi+0x978]',
                    ['mov ecx,DWORD PTR [eax]', 'add eax,edx'])
        self.assertEqual(out, 'undetermined')


if __name__ == '__main__':
    unittest.main()
