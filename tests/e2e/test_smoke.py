"""End-to-end smoke test for PAL3 decompilation pipeline."""
import json
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent.parent
PROBE_FILE = PROJECT_ROOT / "data" / "status" / "probe_census.json"
BASELINE_FILE = PROJECT_ROOT / "data" / "status" / "compile_baseline.json"
LAYOUT_TOOL = PROJECT_ROOT / "tools" / "audit_layout.py"
REGRESSION_TOOL = PROJECT_ROOT / "tools" / "compile_regression.py"
CLASSIFIER_TOOL = PROJECT_ROOT / "tools" / "error_classifier.py"

MIN_S2 = 58  # Minimum acceptable S2 count


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
    """Verify S2 compilation >= baseline."""
    if not PROBE_FILE.exists():
        return False, "probe_census.json not found"
    with open(PROBE_FILE) as f:
        data = json.load(f)
    s2_ok = data.get("s2", {}).get("ok", 0)
    if s2_ok < MIN_S2:
        return False, f"S2 {s2_ok} < {MIN_S2}"
    return True, f"S2: {s2_ok}/204"


def test_layout_audit():
    """Verify no layout issues."""
    ok, output = run_cmd(["python3", str(LAYOUT_TOOL)], timeout=30)
    if "No layout issues" in output:
        return True, "No layout issues"
    return False, f"Layout issues found: {output[:200]}"


def test_compile_regression():
    """Verify no regressions vs baseline."""
    if not BASELINE_FILE.exists():
        return True, "No baseline (skipped)"
    ok, output = run_cmd(["python3", str(REGRESSION_TOOL)], timeout=120)
    if "No regressions" in output:
        return True, "No regressions"
    return False, f"Regressions: {output[:200]}"


def test_error_classifier():
    """Verify error classifier runs successfully."""
    ok, output = run_cmd(["python3", str(CLASSIFIER_TOOL)], timeout=30)
    if "Total failed files:" in output:
        return True, "Classifier OK"
    return False, f"Classifier failed: {output[:200]}"


def main():
    tests = [
        ("probe_compile", test_probe_compile),
        ("layout_audit", test_layout_audit),
        ("compile_regression", test_compile_regression),
        ("error_classifier", test_error_classifier),
    ]

    print("E2E Smoke Test")
    print("=" * 50)
    passed = 0
    failed = 0
    for name, test_fn in tests:
        ok, msg = test_fn()
        status = "✅" if ok else "❌"
        print(f"  {status} {name}: {msg}")
        if ok:
            passed += 1
        else:
            failed += 1

    print(f"\nResults: {passed} passed, {failed} failed")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
