#!/usr/bin/env python3
"""tools/guard 单元测试（零依赖，不依赖真实并发）。

跑法：
  python3 -m unittest tools.guard.test_guard -v
  python3 tools/guard/test_guard.py        # 直接跑也可以
"""
from __future__ import annotations

import os
import sys
import unittest
from unittest import mock

_HERE = os.path.dirname(os.path.abspath(__file__))
_ROOT = os.path.dirname(os.path.dirname(_HERE))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

import importlib  # noqa: E402

pf = importlib.import_module("tools.guard.preflight")
rg = importlib.import_module("tools.guard.reading_guard")


def _fake(rows):
    """把 [(pid, [argv...])] 包成 PopenSource。"""

    def source():
        return rows

    return source


CLI = "python3"
MAIN = "pipeline/cli.py"
CENSUS = "tools/census_struct_holes.py"


class ClassifyTests(unittest.TestCase):
    def test_cli_apply_is_occupying(self):
        self.assertEqual(pf.classify([CLI, MAIN, "apply"]), "apply")

    def test_cli_codegen_two_tokens(self):
        self.assertEqual(pf.classify([CLI, MAIN, "codegen", "all"]), "codegen")

    def test_cli_loop(self):
        self.assertEqual(pf.classify([CLI, MAIN, "loop", "--stages", "probe,match"]), "loop")

    def test_cli_status_not_occupying(self):
        self.assertIsNone(pf.classify([CLI, MAIN, "status"]))

    def test_cli_check_not_occupying(self):
        self.assertIsNone(pf.classify([CLI, MAIN, "check"]))

    def test_cli_match_not_occupying_by_default_but_opt_in(self):
        argv = [CLI, MAIN, "match"]
        self.assertIsNone(pf.classify(argv))
        self.assertEqual(pf.classify(argv, include_match=True), "match")

    def test_census_script_detected(self):
        self.assertEqual(pf.classify([CLI, CENSUS]), pf.CENSUS_SCRIPT)

    def test_census_script_abs_path(self):
        self.assertEqual(
            pf.classify(["/usr/bin/python3", "/repo/tools/census_struct_holes.py"]),
            pf.CENSUS_SCRIPT,
        )

    def test_unrelated_script(self):
        self.assertIsNone(pf.classify([CLI, "tools/check_class.py", "--all"]))


class PreflightTests(unittest.TestCase):
    def test_empty_process_list_clean_rc0(self):
        result = pf.preflight(source=_fake([]), self_pid=1)
        self.assertEqual(result.rc, 0)
        self.assertTrue(result.clean)
        report = pf.render_report(result)
        self.assertIn("OK 干净", report)

    def test_constructed_concurrency_rc2_lists_pid(self):
        rows = [
            (101, [CLI, MAIN, "status"]),  # 不占用
            (4242, [CLI, MAIN, "codegen", "all"]),
            (5353, [CLI, CENSUS]),
        ]
        result = pf.preflight(source=_fake(rows), self_pid=1)
        self.assertEqual(result.rc, 2)
        pids = [o.pid for o in result.occupants]
        self.assertEqual(pids, [4242, 5353])
        report = pf.render_report(result)
        self.assertIn("pid=4242", report)
        self.assertIn("pid=5353", report)
        self.assertIn("matched=codegen", report)
        self.assertIn("读数不可比（并发窗口）", report)

    def test_self_and_ancestors_excluded(self):
        rows = [(100, [CLI, MAIN, "loop"]), (200, [CLI, MAIN, "apply"])]
        # 让 100 是自身、2 是它的父进程：用 mock 覆盖 ancestors_of
        with mock.patch.object(pf, "ancestors_of", return_value={100, 2}):
            result = pf.preflight(source=_fake(rows), self_pid=100)
        self.assertEqual(result.rc, 2)
        self.assertEqual([o.pid for o in result.occupants], [200])

    def test_internal_error_rc1(self):
        def boom():
            raise RuntimeError("procfs exploded")

        result = pf.preflight(source=boom, self_pid=1)
        self.assertEqual(result.rc, 1)
        self.assertIn("procfs exploded", result.note)
        self.assertIn("自身错误", pf.render_report(result))

    def test_json_report_is_parseable(self):
        import json

        result = pf.preflight(source=_fake([(7, [CLI, MAIN, "export"])]), self_pid=1)
        data = json.loads(pf.render_report(result, as_json=True))
        self.assertEqual(data["rc"], 2)
        self.assertEqual(data["occupants"][0]["pid"], 7)
        self.assertEqual(data["verdict"], "concurrent")


class ReadingGuardTests(unittest.TestCase):
    def test_clean_reading_comparable(self):
        v = rg.guard_reading("match", "L1 196", source=_fake([]))
        self.assertEqual(v.rc, 0)
        self.assertEqual(v.verdict, "comparable")
        self.assertTrue(v.baseline_allowed)
        text = "\n".join(v.evidence_lines())
        self.assertIn('reading=match value="L1 196" verdict=comparable', text)
        self.assertIn("baseline_allowed=true", text)

    def test_concurrent_reading_not_comparable(self):
        rows = [(999, [CLI, MAIN, "probe", "all"])]
        v = rg.guard_reading("census", "hole_bytes 213151", source=_fake(rows))
        self.assertEqual(v.rc, 2)
        self.assertEqual(v.verdict, "not-comparable")
        self.assertFalse(v.baseline_allowed)
        text = "\n".join(v.evidence_lines())
        self.assertIn("verdict=not-comparable", text)
        self.assertIn("pid=999", text)
        self.assertIn("baseline_allowed=false", text)
        self.assertIn("不要写基线", text)

    def test_error_reading_not_comparable(self):
        def boom():
            raise OSError("no /proc")

        v = rg.guard_reading("match", "L1 1", source=boom)
        self.assertEqual(v.rc, 1)
        self.assertFalse(v.baseline_allowed)
        self.assertIn("自身错误", "\n".join(v.evidence_lines()))


class CliTests(unittest.TestCase):
    """入口返回码契约（用 --proc-root 指向空目录 = 干净）。"""

    def test_cli_clean_rc0(self):
        with mock.patch.object(pf, "read_processes", return_value=[]):
            self.assertEqual(pf.main([]), 0)

    def test_cli_concurrent_rc2(self):
        rows = [pf.ProcessInfo(pid=321, argv=[CLI, MAIN, "apply"], start_iso="mock")]
        with mock.patch.object(pf, "read_processes", return_value=rows):
            self.assertEqual(pf.main(["--json"]), 2)

    def test_cli_error_rc1(self):
        with mock.patch.object(pf, "read_processes", side_effect=RuntimeError("boom")):
            # main 内部 preflight 会把它折成 rc1
            self.assertEqual(pf.main([]), 1)

    def test_reading_guard_cli_clean_rc0(self):
        with mock.patch.object(pf, "read_processes", return_value=[]):
            self.assertEqual(rg.main(["--reading", "match", "--value", "L1 196"]), 0)

    def test_reading_guard_cli_concurrent_rc2(self):
        rows = [pf.ProcessInfo(pid=654, argv=[CLI, MAIN, "loop"], start_iso="mock")]
        with mock.patch.object(pf, "read_processes", return_value=rows):
            self.assertEqual(rg.main(["--reading", "match", "--value", "L1 196"]), 2)


if __name__ == "__main__":
    unittest.main(verbosity=2)
