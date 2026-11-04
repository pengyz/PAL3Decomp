"""B 转换证明 Task 9：门禁接线（task-9-brief Step 1，TDD 红→绿）。

gate.sh=mutation+fixture+matrix 三证串跑；pre-commit 触发面=转换器/证明器 9 件
（spec §2 勘误补：hook 实路径=.git/hooks/pre-commit 本地钩）。
环境注记：daemon 互斥持库+端口 8432（gate 本身不需要 daemon——三证全离线）。
"""
import pathlib
import subprocess

_ROOT = pathlib.Path(__file__).resolve().parent.parent
_GATE = _ROOT / 'ghidra_track' / 'gate.sh'
_HOOK = _ROOT / '.git' / 'hooks' / 'pre-commit'


def test_gate_green():
    r = subprocess.run(['bash', str(_GATE)], cwd=str(_ROOT),
                       capture_output=True, text=True, timeout=600)
    assert r.returncode == 0, 'gate 绿跑必须 exit 0: %s' % (r.stdout + r.stderr)[-500:]


def test_gate_propagates_red(tmp_path):
    bad = tmp_path / 'bad_test.py'
    bad.write_text('def test_always_fails():\n    assert False, "注入红"\n')
    r = subprocess.run(['bash', str(_GATE)], cwd=str(_ROOT),
                       capture_output=True, text=True, timeout=600,
                       env={'GATE_TEST_PATH': str(bad),
                            'PATH': '/usr/bin:/bin:/usr/local/bin'})
    assert r.returncode != 0, 'gate 必须传播测试红（exit 1）'


def test_hook_wired_with_trigger():
    assert _HOOK.exists(), 'pre-commit 钩必须在（仓内既有钩）'
    txt = _HOOK.read_text()
    assert 'gate.sh' in txt, '钩未接 gate.sh'
    assert 'ghidra_track' in txt and 'import_annotation' in txt, '触发面正则缺席'
    # 触发面真命中（钩内同款 grep 对样本）
    hit = subprocess.run(
        "grep -qE '^ghidra_track/(import_annotation|gen_plan|plan_to_changeset|"
        "import_standard|verify_core|verify_b_import|fixture_proof|mutation_proof|"
        "proof_matrix)\\.py$' <<< 'ghidra_track/gen_plan.py'",
        shell=True, executable='/bin/bash')
    assert hit.returncode == 0, '触发面正则必须命中 gen_plan.py'
    miss = subprocess.run(
        "grep -qE '^ghidra_track/(import_annotation|gen_plan)\\.py$' <<< 'pal3/src/UI/StateUI.cpp'",
        shell=True, executable='/bin/bash')
    assert miss.returncode != 0, '非触发面文件不得命中（防全量拦）'
