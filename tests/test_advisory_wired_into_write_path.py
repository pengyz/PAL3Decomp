"""任务1 测试：advisory 门必须挂在写盘路径（apply/export）上，且不得改变其退出码。

2026-09-21 F3（评审后续项·测试补强）：
原文件 3 个测试**全部**是源码子串检查 ⇒ 评审者实测变异
（把调用改成 `sys.exit(_run_invariants_advisory())`，真违反接口条款）后 3/3 仍 PASS，
零判别力 ✗。现将**冗余的第 3 个**测试替换为**进程内 monkeypatch 行为级测试**：
真正调用 cmd_apply/cmd_export（stub 掉 IDA 与 subprocess），断言
  1) 不抛 SystemExit（advisory 不得改变写盘路径的退出码）；
  2) advisory 各被调用**恰 1 次**，且 argv 含 `--advisory`。
无需 IDA/IDB ✓（_check_ida/_run_ida/subprocess.run 全部替身）。

变异负例（证明本测试真能抓住那个变异）：
  cp pipeline/cli.py /tmp/cli_mut_apply.py
  sed -i 's/^    _run_invariants_advisory()   #/    sys.exit(_run_invariants_advisory())  #/' /tmp/cli_mut_apply.py
  PAL3_ADVISORY_TEST_CLI=/tmp/cli_mut_apply.py python3 tests/test_advisory_wired_into_write_path.py
⇒ 行为级测试必须 FAIL（副本放 /tmp，**不得**在仓库内改 cli.py 或建符号链接）。
"""
import importlib.util
import os
import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from pipeline import cli  # noqa: E402

SRC = ROOT / 'pipeline' / 'cli.py'

# 变异演示用：指向 cli.py 的**副本**（默认不设 ⇒ 测仓库内真文件）。
CLI_PATH_ENV = 'PAL3_ADVISORY_TEST_CLI'


def _cli_under_test():
    """返回被测 cli 模块；设了 CLI_PATH_ENV 时从该副本加载（变异负例用）。"""
    path = os.environ.get(CLI_PATH_ENV)
    if not path:
        return cli
    spec = importlib.util.spec_from_file_location('cli_under_test', path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    # 副本在 /tmp ⇒ 其 _PROJECT_DIR 会算成 '/'，advisory 会因"工具不存在"提前返回而
    # 掩盖真实变异。把路径常量对齐到仓库（变异的对象是**调用点**，不是路径）。
    mod._PROJECT_DIR = cli._PROJECT_DIR
    mod._PIPELINE_DIR = cli._PIPELINE_DIR
    return mod


class _StubPath:
    """cfg.idb_work / cfg.decomp_dir 的替身：exists() 恒真，避免走 sys.exit(1) 分支。"""

    def __init__(self, name):
        self.name = name

    def exists(self):
        return True

    def __str__(self):
        return '/stub/' + self.name


class _StubCfg:
    def __init__(self):
        self.idb_work = _StubPath('PAL3.exe.i64')
        self.decomp_dir = _StubPath('decomp')


class _Completed:
    def __init__(self, returncode):
        self.returncode = returncode


_MISSING = object()


class _MiniPatch:
    """pytest 未安装/未注入时的兜底 monkeypatch（接口与 pytest 的 setattr/undo 一致）。"""

    def __init__(self):
        self._undo = []

    def setattr(self, target, name, value):
        old = getattr(target, name, _MISSING)
        self._undo.append((target, name, old))
        setattr(target, name, value)

    def undo(self):
        for target, name, old in reversed(self._undo):
            if old is _MISSING:
                try:
                    delattr(target, name)
                except AttributeError:
                    pass
            else:
                setattr(target, name, old)
        self._undo = []


def _exercise(cli_mod, command, mp):
    """在替身环境下真调 cmd_apply/cmd_export，返回 (SytemExit 或 None, advisory 调用列表)。

    **关键**：advisory 调用返回 rc=1（故意）—— 若调用方丢弃返回值则无 SystemExit；
    若它写成 sys.exit(...) 则此处必然捕获到 SystemExit。
    """
    calls = []

    def fake_run(cmd, *a, **kw):
        argv = [str(x) for x in cmd] if isinstance(cmd, (list, tuple)) else [str(cmd)]
        is_adv = (any(x.endswith('codegen_invariants.py') for x in argv)
                  and '--advisory' in argv)
        calls.append({'argv': argv, 'advisory': is_adv})
        return _Completed(1 if is_adv else 0)      # advisory: rc=1 但不得外泄为退出码

    mp.setattr(cli_mod, '_check_ida', lambda *a, **kw: None)
    mp.setattr(cli_mod, '_run_ida', lambda *a, **kw: True)
    mp.setattr(cli_mod, 'cfg', _StubCfg())
    mp.setattr(cli_mod.subprocess, 'run', fake_run)

    raised = None
    try:
        if command == 'apply':
            cli_mod.cmd_apply()
        else:
            cli_mod.cmd_export()
    except SystemExit as e:
        raised = e
    finally:
        mp.undo()

    return raised, [c for c in calls if c['advisory']]


def _assert_write_path_is_advisory_only(command, monkeypatch):
    mp = monkeypatch if monkeypatch is not None else _MiniPatch()
    raised, advisories = _exercise(_cli_under_test(), command, mp)
    assert raised is None, (
        'cmd_%s 抛了 SystemExit(%r)：advisory 不得改变写盘路径的退出码 '
        '（advisory 自身 rc=1 也必须被丢弃）' % (command, getattr(raised, 'code', raised)))
    assert len(advisories) == 1, (
        'cmd_%s 应恰好 advisory 调用 1 次，实测 %d 次' % (command, len(advisories)))
    assert '--advisory' in advisories[0]['argv'], (
        'cmd_%s 的 advisory 调用 argv 缺 --advisory：%r' % (command, advisories[0]['argv']))


def test_apply_is_advisory_only_and_calls_advisory_once(monkeypatch=None):
    _assert_write_path_is_advisory_only('apply', monkeypatch)


def test_export_is_advisory_only_and_calls_advisory_once(monkeypatch=None):
    _assert_write_path_is_advisory_only('export', monkeypatch)


# ---------------------------------------------------------------------------
# 以下两个是**非判别层**的廉价不变量（源码形态），保留作快速文档化检查；
# 真正能抓住 `sys.exit(...)` 变异的是上面两个行为级测试 ✓。
# ---------------------------------------------------------------------------
def test_apply_and_export_call_invariants_advisory():
    src = SRC.read_text(encoding='utf-8')
    for fn in ('def cmd_apply(', 'def cmd_export('):
        i = src.index(fn)
        j = src.index('\ndef ', i + 1)
        body = src[i:j]
        assert '_run_invariants_advisory' in body, '%s 未接 advisory 门' % fn


def test_helper_does_not_exit_by_itself():
    src = SRC.read_text(encoding='utf-8')
    i = src.index('def _run_invariants_advisory(')
    j = src.index('\ndef ', i + 1)
    body = src[i:j]
    assert 'sys.exit' not in body, 'helper 不得自行退出（否则会改变 apply/export 退出码）'


if __name__ == '__main__':
    ok = fail = 0
    for name, fn in list(globals().items()):
        if name.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % name); ok += 1
            except AssertionError as e:
                print('  FAIL %s: %s' % (name, e)); fail += 1
    print('Results: %d passed, %d failed' % (ok, fail))
    sys.exit(1 if fail else 0)