"""C2100 形归一 TDD（双括号歧义防）：`*(T**)(x)` → `*((T**)(x))`。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestDerefCastParens(unittest.TestCase):
    def test_deref_cast_parenthesized(self):
        from ast_transform import normalize_deref_cast_parens
        s = 'x = *(gbVisNode **)(this->m_p + 16);'
        out = normalize_deref_cast_parens(s)
        self.assertIn('*((gbVisNode **)(this->m_p + 16))', out)

    def test_nested_operand(self):
        from ast_transform import normalize_deref_cast_parens
        s = 'x = *(int *)(a + (b * 2));'
        out = normalize_deref_cast_parens(s)
        self.assertIn('*((int *)(a + (b * 2)))', out)

    def test_plain_deref_untouched(self):
        from ast_transform import normalize_deref_cast_parens
        s = 'x = *p;'
        self.assertEqual(normalize_deref_cast_parens(s), s)

    def test_idempotent(self):
        from ast_transform import normalize_deref_cast_parens
        s = 'x = *(int *)(y);'
        once = normalize_deref_cast_parens(s)
        self.assertEqual(normalize_deref_cast_parens(once), once)

    def test_masked_strings_untouched(self):
        from ast_transform import normalize_deref_cast_parens
        s = 'sprintf(b, "*(int *)(x)");'
        self.assertEqual(normalize_deref_cast_parens(s), s)


if __name__ == '__main__':
    unittest.main()
