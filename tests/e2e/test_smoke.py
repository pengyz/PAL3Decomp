"""End-to-end smoke test for PAL3 decompilation pipeline.

2026-09-20 修复（审计 P0-1）：本文件原先的 4 个 `test_*` 全部用
`return True/False, msg` 返回结果，**没有任何断言** —— 在 pytest 下，
`test_*` 函数只要不抛异常就算 PASS（返回非 None 仅触发
`PytestReturnNotNoneWarning`），所以这些用例**恒通过**，是典型的"死门禁"；
而 `MIN_S2 = 58` 也早已过期（实际值 75）。

现在：
  * 每个 `test_*` 用 **assert**，pytest 下能真正失败；
  * `MIN_S2` 默认取**编译基线的记录值**（棘轮语义：不得低于基线），
    可用环境变量 `PAL3_MIN_S2` 覆盖；
  * `python tests/e2e/test_smoke.py` 仍可直接运行（`main()` 捕获取证失败并汇总）。
"""
import json
import os
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent.parent
PROBE_FILE = PROJECT_ROOT / "data" / "status" / "probe_census.json"
BASELINE_FILE = PROJECT_ROOT / "data" / "status" / "compile_baseline.json"
LAYOUT_TOOL = PROJECT_ROOT / "tools" / "audit_layout.py"
REGRESSION_TOOL = PROJECT_ROOT / "tools" / "compile_regression.py"
CLASSIFIER_TOOL = PROJECT_ROOT / "tools" / "error_classifier.py"


def _min_s2():
    """S2 下限：优先环境变量，否则取编译基线的记录值（棘轮），最后退回 0。

    绝不硬编码过期的常量 —— 旧的 `MIN_S2 = 58` 远低于真实值 75，形同虚设。
    """
    env = os.environ.get("PAL3_MIN_S2")
    if env and env.isdigit():
        return int(env)
    try:
        with open(BASELINE_FILE, encoding="utf-8") as f:
            return int(json.load(f).get("s2", {}).get("ok", 0))
    except Exception:
        return 0


def run_cmd(cmd, timeout=300):
    """Run a command and return (success, output)."""
    try:
        result = subprocess.run(
            cmd, capture_output=True, text=True,
            timeout=timeout, cwd=PROJECT_ROOT
        )
        return result.returncode == 0, result.stdout + result.stderr
    except subprocess.TimeoutExpired:
        return False, f"Timeout after {timeout}s"
    except Exception as e:
        return False, str(e)


def test_probe_compile():
    """S2 编译通过数不得低于基线（棘轮）。"""
    assert PROBE_FILE.exists(), "probe_census.json not found"
    with open(PROBE_FILE, encoding="utf-8") as f:
        data = json.load(f)
    s2_ok = data.get("s2", {}).get("ok", 0)
    total = data.get("s2", {}).get("total", 0)
    floor = _min_s2()
    assert s2_ok >= floor, f"S2 {s2_ok}/{total} < 下限 {floor}"


def test_layout_audit():
    """layout 审计必须成功执行（其自身已标注部分检查无判别力，见工具头注）。"""
    ok, output = run_cmd(["python3", str(LAYOUT_TOOL)], timeout=120)
    assert ok, f"audit_layout.py 执行失败: {output[:300]}"


def test_compile_regression():
    """相对编译基线不得有退化。

    判据用**工具退出码**（regression_detector 检出退化时非零），
    不用字符串匹配 —— 该工具在"有改善"时输出 `🎉 IMPROVEMENTS`、
    在"无变化"时输出 `No regressions`，只匹配后者会误报。
    """
    if not BASELINE_FILE.exists():
        return  # 无基线 ⇒ 跳过（不算失败）
    ok, output = run_cmd(["python3", str(REGRESSION_TOOL)], timeout=180)
    assert ok, f"检出退化（regression_detector 退出码非 0）: {output[-300:]}"


def test_error_classifier():
    """error_classifier 必须能跑出汇总（工具自身健全，此前只是未接线）。"""
    ok, output = run_cmd(["python3", str(CLASSIFIER_TOOL)], timeout=60)
    assert ok and "Total failed files:" in output, f"classifier 失败: {output[:300]}"


TESTS = [
    ("probe_compile", test_probe_compile),
    ("layout_audit", test_layout_audit),
    ("compile_regression", test_compile_regression),
    ("error_classifier", test_error_classifier),
]


def main():
    print("E2E Smoke Test")
    print("=" * 50)
    passed = failed = 0
    for name, fn in TESTS:
        try:
            fn()
            print(f"  ✅ {name}")
            passed += 1
        except AssertionError as e:
            print(f"  ❌ {name}: {e}")
            failed += 1
        except Exception as e:
            print(f"  ⚠️  {name}: {type(e).__name__}: {e}")
            failed += 1
    print(f"\nResults: {passed} passed, {failed} failed  (S2 下限 = {_min_s2()})")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
