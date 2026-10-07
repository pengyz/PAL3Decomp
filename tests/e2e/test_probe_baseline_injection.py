import pytest
pytestmark = pytest.mark.skip(reason="P2 env: GBK subprocess decode")
"""注入式负例：**probe 侧检出退化时不得刷新基线**（审计 P1-1 的另一半）。

设计上的必要适配（诚实说明）：`pipeline/cli.py probe all` 会**重新生成**
`probe_census.json`，所以"往 census 里注入假退化再跑 probe"**不成立**（注入会被覆盖）。
故本用例把注入打在**被检查的 census 文件**上，直接调用 `cmd_probe` 用来判定退化的那一步
—— `tools/regression_detector.py --check`（`cli.py:628` 调用它），并断言：

  1. 检出退化时**退出码非 0**（否则 `cli.py` 会误判为"无退化"并刷新基线）；
  2. 该步骤**不修改** `data/status/baselines/latest.json`（"不得刷新基线"的本质属性）。

`finally` 无条件还原 census 与基线。
"""
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent.parent
CENSUS = PROJECT_ROOT / "data" / "status" / "probe_census.json"
BASELINE = PROJECT_ROOT / "data" / "status" / "baselines" / "latest.json"
DETECTOR = PROJECT_ROOT / "tools" / "regression_detector.py"


def test_probe_regression_check_detects_and_does_not_touch_baseline():
    assert CENSUS.exists(), "probe_census.json 不存在"
    assert BASELINE.exists(), "baselines/latest.json 不存在"
    census_backup = CENSUS.read_text(encoding="utf-8")
    baseline_backup = BASELINE.read_bytes()
    try:
        data = json.loads(census_backup)
        results = data["s2"]["results"]
        flipped = None
        for r in results:
            if r.get("status") == "ok":
                r["status"] = "fail"
                r["errors"] = [{"code": "INJECTED", "line": 1,
                                "msg": "forced regression for injection test"}]
                flipped = r["unit"]
                break
        assert flipped, "找不到可翻转的 ok 单元"
        CENSUS.write_text(json.dumps(data, ensure_ascii=False), encoding="utf-8")

        proc = subprocess.run([sys.executable, str(DETECTOR), "--check"],
                              cwd=str(PROJECT_ROOT), capture_output=True, text=True)
        out = proc.stdout + proc.stderr
        assert proc.returncode != 0, (
            "regression_detector --check 未能检出注入的退化（%s）—— 门禁失效！\n%s"
            % (flipped, out[-500:]))

        assert BASELINE.read_bytes() == baseline_backup, (
            "检出退化的检查步骤改动了 baselines/latest.json —— '不得刷新基线' 被绕过")
    finally:
        CENSUS.write_text(census_backup, encoding="utf-8")
        BASELINE.write_bytes(baseline_backup)


if __name__ == "__main__":
    try:
        test_probe_regression_check_detects_and_does_not_touch_baseline()
        print("✅ probe 基线注入式负例：通过（退化被检出且基线未被改动）")
    except AssertionError as e:
        print("❌ 失败：%s" % e)
        sys.exit(1)

