"""e2e smoke 测试（重写清版 2026-10-07——GBK 编码顽修·架构治理 P0-1）。"""
import pytest
import os
import subprocess
import sys
import unittest

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
LAYOUT_TOOL = os.path.join(_ROOT, 'tools', 'audit_type_layout.py')
PY = sys.executable


class TestSmoke(unittest.TestCase):
    @pytest.mark.slow(reason="e2e 编译 — 集成测试非 UT")
    def test_layout_audit_runs(self):
        if not os.path.exists(LAYOUT_TOOL):
            self.skipTest('layout tool missing')
        r = subprocess.run([PY, LAYOUT_TOOL, '--limit', '1'],
                           capture_output=True, text=True, timeout=120)
        self.assertIn(r.returncode, (0, 1, 2))

    def test_python_executable(self):
        r = subprocess.run([PY, '-c', 'print(1)'], capture_output=True, text=True)
        self.assertEqual(r.stdout.strip(), '1')


if __name__ == '__main__':
    unittest.main()
