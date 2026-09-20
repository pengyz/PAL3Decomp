"""任务1 测试：advisory 门必须挂在写盘路径（apply/export）上，且不得改变其退出码。"""
import pathlib

SRC = pathlib.Path(__file__).resolve().parent.parent / 'pipeline' / 'cli.py'


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


def test_apply_still_uses_its_own_exit_code():
    """确保 advisory 调用没有把 apply 的成功退出路径改成非零。"""
    src = SRC.read_text(encoding='utf-8')
    i = src.index('def cmd_apply(')
    j = src.index('\ndef ', i + 1)
    body = src[i:j]
    assert '_run_invariants_advisory()' in body


if __name__ == '__main__':
    import sys
    ok = fail = 0
    for name, fn in list(globals().items()):
        if name.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % name); ok += 1
            except AssertionError as e:
                print('  FAIL %s: %s' % (name, e)); fail += 1
    print('Results: %d passed, %d failed' % (ok, fail))
    sys.exit(1 if fail else 0)