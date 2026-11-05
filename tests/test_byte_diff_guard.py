"""byte_diff_explain 护栏域修（2026-11-05·病灶层：模块级 argv 守卫误伤 import）。

护栏本意（P2-4 审计）=挡「脚本误收 - 开头参数跑全流程写盘」——判在模块级 ⇒
任何带 -q/-v 的调用方（pytest/CLI 编排）一 import 即 exit(0)（asm_diff 接线实锤）。
修=守卫收 __main__ 域：脚本模式行为不变·import 面解放。
"""
import subprocess
import sys


def test_import_survives_dash_argv():
    r = subprocess.run(
        [sys.executable, '-c',
         "import sys; sys.argv[:]=['tool','-q'];"
         "import byte_diff_explain; print('imported-ok')"],
        capture_output=True, text=True, timeout=60,
        cwd='tools', env={'PATH': '/usr/bin:/bin:/usr/local/bin'})
    assert 'imported-ok' in r.stdout, \
        'import 带 -argv 必须存活（现=exit(0) 假绿截断·stderr=%s）' % r.stderr[:200]


def test_script_mode_guard_still_fires():
    """脚本模式带 -argv 仍必须被守（护栏原意不丢·不执行写盘）。"""
    r = subprocess.run(
        [sys.executable, 'byte_diff_explain.py', '--help'],
        capture_output=True, text=True, timeout=60,
        cwd='tools', env={'PATH': '/usr/bin:/bin:/usr/local/bin'})
    assert '不执行任何操作' in r.stdout, '脚本模式守卫必须仍在'
    assert 'partials explained' not in r.stdout, '守卫触发禁跑全流程'
