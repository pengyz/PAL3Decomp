"""SingletonThunk 胶水剥离（T5·(i)）——R15 纯函数。
合成物胶水（atexit 注册+立即调用）由编译器随全局对象定义再生，禁手写。
运行: pytest tests/test_singleton_glue_strip.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'pipeline/gen'))
from textutil import strip_singleton_thunk_glue as f


def test_atexit_form():
    src = '    atexit(SingletonThunk_004B6D70);\n    keep();\n'
    assert f(src) == '    keep();\n'


def test_call_with_this():
    src = '  SingletonThunk_00431D90(this);\n  atexit(SingletonThunk_00431DB0);\n'
    assert f(src) == ''


def test_unrelated_untouched():
    src = '  SingletonHelper_real();\n  x = 1;\n'
    assert f(src) == src


def test_idempotent():
    once = f('  atexit(SingletonThunk_00431E70);\n')
    assert f(once) == once
