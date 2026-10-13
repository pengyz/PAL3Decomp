"""[T40/T38-F1] R15 单测落盘：stage4 指针值→unsigned long 整型别名 cast（T37）。

四形契约：
① 目标 3 转——HIDWORD()/ *(T*) 解引用别名/下标形 × RHS 指针型证据
② 非目标不动——普通赋值、整型 RHS
③ 幂等——二次套用不双包
④ 基类回落（T38-F3 递归）——孙基类成员仍解析

⚠️ 口径（T38-F2 限缩）：本变换是**类型级字节等价**（x86-32 位拷贝成立），
非端到端 L1 实证（目标函数仍 partial）。
"""
import sys
import os
import unittest

_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
sys.path.insert(0, _ROOT)                                    # pipeline.config 包根
sys.path.insert(0, os.path.join(_ROOT, 'pipeline', 'gen'))
sys.path.insert(0, os.path.join(_ROOT, 'pipeline', 'gen', 'stages'))

from data import store            # noqa: E402
store.load()

import stage4_substitution as s4  # noqa: E402


class _Ctx(object):
    cls_name = 'UIEmote'
    is_free_function = False


TARGET_HIDWORD = '  HIDWORD(v6) = this->m_ani[7].m_childs.m_pData;'
TARGET_DEREF = '  *(_DWORD *)this->m_caption = gfxMgr->NewTexture((const char *)v7);'
TARGET_SUBSCRIPT = '  v19[2] = this->m_ani[9].m_pfather;'
NON_TARGET_PLAIN = '  x = this->m_ptr;'
NON_TARGET_INT = '  HIDWORD(y) = 3;'


class TestPtrToULong(unittest.TestCase):
    def test_target_hidword_form_wrapped(self):
        out = s4._fix_ptr_to_ulong_assigns(TARGET_HIDWORD, _Ctx())
        self.assertIn(' = (unsigned long)(', out)
        self.assertIn('m_pData)', out)

    def test_target_deref_alias_form_wrapped(self):
        out = s4._fix_ptr_to_ulong_assigns(TARGET_DEREF, _Ctx())
        self.assertIn(' = (unsigned long)(', out)

    def test_target_subscript_form_wrapped(self):
        out = s4._fix_ptr_to_ulong_assigns(TARGET_SUBSCRIPT, _Ctx())
        self.assertIn(' = (unsigned long)(', out)

    def test_non_target_plain_assign_untouched(self):
        self.assertEqual(s4._fix_ptr_to_ulong_assigns(NON_TARGET_PLAIN, _Ctx()),
                         NON_TARGET_PLAIN)

    def test_non_target_int_rhs_untouched(self):
        self.assertEqual(s4._fix_ptr_to_ulong_assigns(NON_TARGET_INT, _Ctx()),
                         NON_TARGET_INT)

    def test_idempotent(self):
        once = s4._fix_ptr_to_ulong_assigns(TARGET_HIDWORD, _Ctx())
        twice = s4._fix_ptr_to_ulong_assigns(once, _Ctx())
        self.assertEqual(once, twice)

    def test_base_fallback_recursive(self):
        # [T38-F3] 孙基类成员：链解析经 struct_bases 递归上溯
        # （UIEmote → UIAnimateCtrl → … → UIWnd.m_childs 族）。
        t = s4._member_type_of('this->m_ani', 'm_childs', _Ctx())
        self.assertTrue(t and '*' in t or t, 'base-class fallback must resolve: %r' % t)


if __name__ == '__main__':
    unittest.main()
