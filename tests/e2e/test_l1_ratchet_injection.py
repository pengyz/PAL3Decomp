"""注入式负例：**L1 棘轮必须能被真实触发**（审计 P1-1）。

背景：`docs/specs/2026-09-15-plan-1to5-landing-design.md` §5 明文要求
"棘轮必须能被人为降低的 partial 触发（否则是死门禁）"，而此前
`grep -rn ratchet tests/` **零命中** —— 两条硬线都没有负例测试。

本用例的做法：
  1. 备份 `data/status/s4_baseline.json`；
  2. **注入**：把 `stats.match_L1` 抬到 真实值+1，制造"必然可触发的退化"；
  3. 跑真实的 `pipeline/cli.py match`；
  4. 断言两件事：
     a. 退出码非 0（棘轮必须报警）；
     b. 文件里的 `match_L1` 仍是**注入的那个"历史"值**（证明 `cmd_match`
        执行了"退化时把旧基线写回"，而不是让退化静默固化）；
  5. `finally` 无条件还原真实基线（避免污染仓库）。

**注意**：它会真跑一次完整 `match`（数分钟），这是 e2e 的固有成本；
默认由 `PAL3_E2E_INJECTION=1` 开启，避免拖慢日常套件 —— 但**它一旦运行就必须
能失败**（这正是"死门禁"要防的）。
"""
import json
import os
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent.parent
S4 = PROJECT_ROOT / "data" / "status" / "s4_baseline.json"

ENABLED = os.environ.get("PAL3_E2E_INJECTION") == "1"


def test_l1_ratchet_catches_injected_regression():
    if not ENABLED:
        print("[skip] 设 PAL3_E2E_INJECTION=1 才跑（它会真跑一次完整 match，数分钟）")
        return
    assert S4.exists(), "s4_baseline.json 不存在"
    backup = S4.read_text(encoding="utf-8")
    try:
        data = json.loads(backup)
        real_l1 = data["stats"]["match_L1"]
        injected = real_l1 + 1
        data["stats"]["match_L1"] = injected
        S4.write_text(json.dumps(data, ensure_ascii=False), encoding="utf-8")

        proc = subprocess.run([sys.executable, "pipeline/cli.py", "match"],
                              cwd=str(PROJECT_ROOT), capture_output=True, text=True)
        out = proc.stdout + proc.stderr
        assert proc.returncode != 0, (
            "L1 棘轮未能在注入的退化上报错 —— 门禁失效！\n" + out[-500:])
        assert "REGRESSION" in out or "ratchet" in out.lower(), out[-500:]

        after = json.loads(S4.read_text(encoding="utf-8"))["stats"]["match_L1"]
        assert after == injected, (
            "退化后基线被静默刷新（棘轮失忆）：期望写回注入值 %d，实得 %d"
            % (injected, after))
    finally:
        S4.write_text(backup, encoding="utf-8")


if __name__ == "__main__":
    try:
        test_l1_ratchet_catches_injected_regression()
        print("✅ L1 棘轮注入式负例：通过（棘轮能被触发且基线被写回）")
    except AssertionError as e:
        print("❌ 失败：%s" % e)
        sys.exit(1)
