"""End-to-end smoke test for PAL3 decompilation pipeline.

2026-09-20 淇锛堝璁?P0-1锛夛細鏈枃浠跺師鍏堢殑 4 涓?`test_*` 鍏ㄩ儴鐢?
`return True/False, msg` 杩斿洖缁撴灉锛?*娌℃湁浠讳綍鏂█** 鈥斺€?鍦?pytest 涓嬶紝
`test_*` 鍑芥暟鍙涓嶆姏寮傚父灏辩畻 PASS锛堣繑鍥為潪 None 浠呰Е鍙?
`PytestReturnNotNoneWarning`锛夛紝鎵€浠ヨ繖浜涚敤渚?*鎭掗€氳繃**锛屾槸鍏稿瀷鐨?姝婚棬绂?锛?
鑰?`MIN_S2 = 58` 涔熸棭宸茶繃鏈燂紙瀹為檯鍊?75锛夈€?

鐜板湪锛?
  * 姣忎釜 `test_*` 鐢?**assert**锛宲ytest 涓嬭兘鐪熸澶辫触锛?
  * `MIN_S2` 榛樿鍙?*缂栬瘧鍩虹嚎鐨勮褰曞€?*锛堟杞涔夛細涓嶅緱浣庝簬鍩虹嚎锛夛紝
    鍙敤鐜鍙橀噺 `PAL3_MIN_S2` 瑕嗙洊锛?
  * `python tests/e2e/test_smoke.py` 浠嶅彲鐩存帴杩愯锛坄main()` 鎹曡幏鍙栬瘉澶辫触骞舵眹鎬伙級銆?
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
    """S2 涓嬮檺锛氫紭鍏堢幆澧冨彉閲忥紝鍚﹀垯鍙栫紪璇戝熀绾跨殑璁板綍鍊硷紙妫樿疆锛夛紝鏈€鍚庨€€鍥?0銆?

    缁濅笉纭紪鐮佽繃鏈熺殑甯搁噺 鈥斺€?鏃х殑 `MIN_S2 = 58` 杩滀綆浜庣湡瀹炲€?75锛屽舰鍚岃櫄璁俱€?
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
    """S2 缂栬瘧閫氳繃鏁颁笉寰椾綆浜庡熀绾匡紙妫樿疆锛夈€?""
    assert PROBE_FILE.exists(), "probe_census.json not found"
    with open(PROBE_FILE, encoding="utf-8") as f:
        data = json.load(f)
    s2_ok = data.get("s2", {}).get("ok", 0)
    total = data.get("s2", {}).get("total", 0)
    floor = _min_s2()
    assert s2_ok >= floor, f"S2 {s2_ok}/{total} < 涓嬮檺 {floor}"


def test_layout_audit():
    """layout 瀹¤蹇呴』鎴愬姛鎵ц锛堝叾鑷韩宸叉爣娉ㄩ儴鍒嗘鏌ユ棤鍒ゅ埆鍔涳紝瑙佸伐鍏峰ご娉級銆?""
    ok, output = run_cmd(["sys.executable", str(LAYOUT_TOOL)], timeout=120)
    assert ok, f"audit_layout.py 鎵ц澶辫触: {output[:300]}"


def test_compile_regression():
    """鐩稿缂栬瘧鍩虹嚎涓嶅緱鏈夐€€鍖栥€?

    鍒ゆ嵁鐢?*宸ュ叿閫€鍑虹爜**锛坮egression_detector 妫€鍑洪€€鍖栨椂闈為浂锛夛紝
    涓嶇敤瀛楃涓插尮閰?鈥斺€?璇ュ伐鍏峰湪"鏈夋敼鍠?鏃惰緭鍑?`馃帀 IMPROVEMENTS`銆?
    鍦?鏃犲彉鍖?鏃惰緭鍑?`No regressions`锛屽彧鍖归厤鍚庤€呬細璇姤銆?
    """
    if not BASELINE_FILE.exists():
        return  # 鏃犲熀绾?鈬?璺宠繃锛堜笉绠楀け璐ワ級
    ok, output = run_cmd(["sys.executable", str(REGRESSION_TOOL)], timeout=180)
    assert ok, f"妫€鍑洪€€鍖栵紙regression_detector 閫€鍑虹爜闈?0锛? {output[-300:]}"


def test_error_classifier():
    """error_classifier 蹇呴』鑳借窇鍑烘眹鎬伙紙宸ュ叿鑷韩鍋ュ叏锛屾鍓嶅彧鏄湭鎺ョ嚎锛夈€?""
    ok, output = run_cmd(["sys.executable", str(CLASSIFIER_TOOL)], timeout=60)
    assert ok and "Total failed files:" in output, f"classifier 澶辫触: {output[:300]}"


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
            print(f"  鉁?{name}")
            passed += 1
        except AssertionError as e:
            print(f"  鉂?{name}: {e}")
            failed += 1
        except Exception as e:
            print(f"  鈿狅笍  {name}: {type(e).__name__}: {e}")
            failed += 1
    print(f"\nResults: {passed} passed, {failed} failed  (S2 涓嬮檺 = {_min_s2()})")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())

