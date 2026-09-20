# tests/test_audit_element_sizes.py
"""任务2 测试：只读 ??_L/??_M 站点抽取器（fixture 元组顺序 + asm 缺失 exit 2 + "-"开头参数护栏）。

fixture 断言要点：`size` 必须来自字面量 `push`（不是从别处推得），
ctor/dtor 必须来自 `push offset sub_XXXX`（归一化为 `0xXXXX`）。
"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'tools'))
import audit_element_sizes as a

ASM = """
sub_408740      proc near
                push    offset sub_411CA0
                push    offset sub_411900
                push    5
                push    2200h
                push    offset unk_C05F60
                call    ??_L@YGXPAXIHP6EX0@Z1@Z
sub_408740      endp
"""

def test_parse_l_pushes_tuple():
    sites = a.parse_sites(ASM)
    assert len(sites) == 1
    s = sites[0]
    assert s['kind'] == 'ehl'
    assert s['size'] == 0x2200          # 来自 push 2200h 字面量
    assert s['count'] == 5
    assert s['ctor'] == '0x411900'
    assert s['dtor'] == '0x411CA0'

def test_missing_asm_returns_2(tmp_path, monkeypatch):
    monkeypatch.setattr(a, 'ASM_PATH', str(tmp_path / 'nope.asm'))
    assert a.main([]) == 2

def test_unknown_flag_is_rejected(monkeypatch):
    monkeypatch.setattr(sys, 'argv', ['audit_element_sizes.py', '--help'])
    assert a.main(['--help']) == 0   # 护栏：拒绝执行而非跑全流程


if __name__ == '__main__':
    import inspect, shutil, tempfile, pathlib

    class _MonkeyPatch:
        """够用的 monkeypatch 替身（pytest 未安装时直接跑本文件的兜底）。"""
        def __init__(self):
            self._undo = []

        def setattr(self, obj, name, value):
            self._undo.append((obj, name, getattr(obj, name)))
            setattr(obj, name, value)

        def undo(self):
            for obj, name, old in reversed(self._undo):
                setattr(obj, name, old)
            self._undo = []

    ok = fail = 0
    for name, fn in sorted(globals().items()):
        if name.startswith('test_') and callable(fn):
            params = inspect.signature(fn).parameters
            kwargs, tmpdir, mp = {}, None, _MonkeyPatch()
            if 'tmp_path' in params:
                tmpdir = tempfile.mkdtemp(prefix='aes_test_')
                kwargs['tmp_path'] = pathlib.Path(tmpdir)
            if 'monkeypatch' in params:
                kwargs['monkeypatch'] = mp
            try:
                fn(**kwargs)
                print('  PASS %s' % name)
                ok += 1
            except AssertionError as e:
                print('  FAIL %s: %s' % (name, e))
                fail += 1
            finally:
                mp.undo()
                if tmpdir:
                    shutil.rmtree(tmpdir, ignore_errors=True)
    print('Results: %d passed, %d failed' % (ok, fail))
    sys.exit(1 if fail else 0)