"""[T62/T60-F2] R15 单测：stage4 LOBYTE 截断-return 坍缩（T59）。

三形契约（T38-F1/T52-F1 同型）：
① 正形：LOBYTE(v)=EXPR; return v; ⇒ return EXPR;（thunk #2 尾直通形）
② 非正形不动（不同名 return / 非相邻 / 非 LOBYTE 形）
③ 幂等（二次套用不双转）

⚠️ A 级：thunk `e9 0b 00 00 00` jmp 形=尾直通（LOBYTE 截断形挡尾调用优化）。
R11：改动 _fix_lobyte_return 后强制复跑本测。
"""
import sys
import os
import unittest

_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
sys.path.insert(0, _ROOT)
sys.path.insert(0, os.path.join(_ROOT, 'pipeline', 'gen'))
sys.path.insert(0, os.path.join(_ROOT, 'pipeline', 'gen', 'stages'))

from data import store            # noqa: E402
store.load()

import stage4_substitution as s4  # noqa: E402


POS = '  LOBYTE(result) = CCBAI::SpecAI(this);\n  return result;\n'
POS_OUT = '  return CCBAI::SpecAI(this);\n'


class TestLobyeReturn(unittest.TestCase):
    def test_positive_collapsed(self):
        out = s4._fix_lobyte_return(POS)
        self.assertIn('return CCBAI::SpecAI(this);', out)
        self.assertNotIn('LOBYTE', out)

    def test_non_positive_untouched(self):
        # 不同名 return ⇒ 不动
        s1 = '  LOBYTE(result) = f(this);\n  return v9;\n'
        self.assertEqual(s4._fix_lobyte_return(s1), s1)
        # 非相邻（中间隔语句）⇒ 不动
        s2 = '  LOBYTE(result) = f(this);\n  x = 1;\n  return result;\n'
        self.assertEqual(s4._fix_lobyte_return(s2), s2)
        # [T65/T63-F1] 非 LOBYTE 形（HIDWORD 别名族）⇒ 不动（契约三子形补齐）
        s3 = '  HIDWORD(result) = f(this);\n  return result;\n'
        self.assertEqual(s4._fix_lobyte_return(s3), s3)
        # [T68/T66-F1] 行中形 ⇒ 不动（行首锚收窄；行中形截断语义等价面未证
        # ——thunk#2 的 jmp 透传 EAX 论证不推广到任意函数）
        s4m = '  x = 1; LOBYTE(result) = f(this);\n  return result;\n'
        self.assertEqual(s4._fix_lobyte_return(s4m), s4m)

    def test_idempotent(self):
        once = s4._fix_lobyte_return(POS)
        twice = s4._fix_lobyte_return(once)
        self.assertEqual(once, twice)
        self.assertEqual(once, POS_OUT)


if __name__ == '__main__':
    unittest.main()
