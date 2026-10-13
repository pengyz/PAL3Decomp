"""[T76] R15 单测：cross_source_reconcile 四源对照（三形）。"""
import sys
import os
import unittest

_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
sys.path.insert(0, os.path.join(_ROOT, 'tools'))

from cross_source_reconcile import reconcile_member  # noqa: E402


class TestReconcile(unittest.TestCase):
    def test_consistent(self):
        r = reconcile_member({'type': 'int'}, {'type': 'int'}, {'type': 'int'}, {'type': 'int'})
        self.assertEqual(r['verdict'], 'consistent')

    def test_inconsistent(self):
        r = reconcile_member({'type': 'int'}, {'type': 'float'}, {'type': 'int'}, {'type': 'int'})
        self.assertEqual(r['verdict'], 'inconsistent')
        self.assertIn('IDB', r['sources_diff'])

    def test_missing_source(self):
        r = reconcile_member({'type': 'int'}, None, {'type': 'int'}, None)
        self.assertEqual(r['verdict'], 'missing')


if __name__ == '__main__':
    unittest.main()
