#!/usr/bin/env python3
"""Compile Regression Detection Tool for PAL3 Decompilation Pipeline.

Compares current compilation results with a stored baseline to detect regressions.

Usage:
    python3 tools/compile_regression.py [--update-baseline]
"""

import json
import sys
from pathlib import Path
from datetime import datetime

# F52-bis（第 133 轮）：本脚本正文用 emoji（✅/⚠️/🎉）报结论，而 cmd/pwsh 的默认
# stdout 编码是 GBK ⇒ `UnicodeEncodeError` 直接让**门禁自己崩掉**
# （第 132/133 轮实测：报告已经算完并打印，最后一行 `✅ No regressions detected`
#   抛异常 → 退出码 1，被 `cli.py` 当成"有退化"）。门禁工具的结论行必须能打印出来。
for _s in (sys.stdout, sys.stderr):
    try:
        _s.reconfigure(encoding='utf-8', errors='replace')
    except Exception:
        pass

PROJECT_ROOT = Path(__file__).parent.parent
PROBE_FILE = PROJECT_ROOT / "data" / "status" / "probe_census.json"
BASELINE_FILE = PROJECT_ROOT / "data" / "status" / "compile_baseline.json"


def load_current():
    """Load current compilation results."""
    if not PROBE_FILE.exists():
        print(f"Error: {PROBE_FILE} not found. Run probe_compile.py first.")
        sys.exit(1)
    with open(PROBE_FILE, encoding='utf-8') as f:
        return json.load(f)


def load_baseline():
    """Load baseline results."""
    if not BASELINE_FILE.exists():
        return None
    with open(BASELINE_FILE) as f:
        return json.load(f)


def save_baseline(data):
    """Save current results as baseline."""
    baseline = {
        "timestamp": datetime.now().isoformat(),
        "s2": data["s2"],
        "s1": data["s1"],
        "ok_files": [r["unit"] for r in data["s2"]["results"] if r.get("status") == "ok"],
    }
    with open(BASELINE_FILE, "w") as f:
        json.dump(baseline, f, indent=2)
    print(f"Baseline saved to {BASELINE_FILE}")
    return baseline


def compare(current, baseline):
    """Compare current results with baseline."""
    curr_ok = {r["unit"] for r in current["s2"]["results"] if r.get("status") == "ok"}
    base_ok = set(baseline.get("ok_files", []))

    # Regressions: files that were ok but now fail
    regressions = sorted(base_ok - curr_ok)
    # Improvements: files that were fail but now ok
    improvements = sorted(curr_ok - base_ok)

    return regressions, improvements


def main():
    import argparse
    parser = argparse.ArgumentParser(description="Detect compilation regressions")
    parser.add_argument("--update-baseline", action="store_true", help="Update baseline with current results")
    args = parser.parse_args()

    current = load_current()

    if args.update_baseline:
        save_baseline(current)
        return

    baseline = load_baseline()
    if baseline is None:
        print("No baseline found. Run with --update-baseline to create one.")
        print(f"Current S2: {current['s2']['ok']}/{current['s2']['total']}")
        return

    regressions, improvements = compare(current, baseline)

    print(f"Compile Regression Report")
    print(f"{'='*50}")
    print(f"Baseline: {baseline.get('timestamp', 'unknown')}")
    print(f"Baseline S2: {len(baseline.get('ok_files', []))}/204")
    print(f"Current S2: {current['s2']['ok']}/{current['s2']['total']}")
    print()

    if regressions:
        print(f"⚠️  REGRESSIONS ({len(regressions)} files):")
        for f in regressions:
            print(f"  - {f}")
    else:
        print("✅ No regressions detected")

    if improvements:
        print(f"\n🎉 IMPROVEMENTS ({len(improvements)} files):")
        for f in improvements:
            print(f"  + {f}")

    print()
    diff = current['s2']['ok'] - len(baseline.get('ok_files', []))
    if diff > 0:
        print(f"Net change: +{diff} files")
    elif diff < 0:
        print(f"Net change: {diff} files")
    else:
        print("Net change: 0 files")

    # Exit code: 1 if regressions, 0 otherwise
    if regressions:
        sys.exit(1)


if __name__ == "__main__":
    main()
