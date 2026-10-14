"""__noreturn 剥除回归测试（T145 · R15：改工具必须跑其测试）。

病灶：`emit_headers.py` / `stage5_fixup.py` 的 `\b__noreturn\s*(?=\()` **只匹配
`__noreturn(` 形**，漏掉 `void __noreturn Cls::M()` 声明符形
⇒ RenderTarget2.cpp:3260 `void __noreturn RenderTarget2::FatalExit()`
  产生 C2143 / C2182 / C1004 三错（同族语法遮蔽）。
修法：`\b__noreturn\b\s*`（两种形均覆盖）。
"""
import os
import re
import sys
import unittest

_GEN = os.path.dirname(os.path.abspath(__file__))
_REPO = os.path.dirname(os.path.dirname(_GEN))
sys.path.insert(0, _GEN)
sys.path.insert(0, _REPO)
os.environ.setdefault('PROJECT_ROOT', _REPO)

# 与被测实现保持一致的正则（两处相同）
NEW_RE = re.compile(r'\b__noreturn\b\s*')


class TestNoreturnStrip(unittest.TestCase):
    def test_declspec_form_stripped(self):
        # 病灶形：`void __noreturn Cls::M()`
        s = 'void __noreturn RenderTarget2::FatalExit()'
        out = NEW_RE.sub('', s)
        self.assertEqual(out, 'void RenderTarget2::FatalExit()')
        self.assertNotIn('__noreturn', out)

    def test_paren_form_stripped(self):
        # 原正则本就覆盖的形：`__noreturn()` / `__noreturn ()`
        for s in ('__noreturn()', '__noreturn ()'):
            out = NEW_RE.sub('', s)
            self.assertNotIn('__noreturn', out)
            self.assertTrue(out.startswith('(') or out.startswith(' ('))

    def test_old_regex_missed_declspec_form(self):
        # 反证：旧正则确实漏掉声明符形（否则这个 bug 不可能存在）
        old = re.compile(r'\b__noreturn\s*(?=\()')
        s = 'void __noreturn RenderTarget2::FatalExit()'
        self.assertEqual(old.sub('', s), s)

    def test_body_form_stripped(self):
        s = '  __noreturn _amsg_exit(0x19u);'
        self.assertNotIn('__noreturn', NEW_RE.sub('', s))

    def test_stage5_actual_codepath(self):
        # 走 stage5_fixup._run_inner 真实代码路径（ctx 只需 is_free_function）
        sys.path.insert(0, os.path.join(_GEN, 'stages'))
        from stage5_fixup import _run_inner

        class _Ctx(object):
            is_free_function = False
            cls_name = None

            def __getattr__(self, k):
                return None

        code = 'void __noreturn RenderTarget2::FatalExit()\n{\n  _amsg_exit(0x19u);\n}\n'
        out = _run_inner(code, _Ctx())
        self.assertNotIn('__noreturn', out)
        self.assertIn('void RenderTarget2::FatalExit()', out)


if __name__ == '__main__':
    unittest.main()
