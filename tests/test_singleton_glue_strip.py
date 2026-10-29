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


def test_d2_semantic_pair_not_stripped():
    """D2 守卫：Site2/3 手工单例对（0x431E70/EC0）禁剥——半剥离=真初始化丢失。"""
    src = '  SingletonThunk_00431E70(this);\n  atexit(ConditionalCleanup);\n'
    assert f(src) == src


def test_d2b_pseudo_arg_stripped_pair_statement_kept():
    """D2b：Site2/3 语句保留（D2）+ 伪参剥离（B9 零栈参字节形）。"""
    from textutil import strip_singleton_thunk_args as g
    src = '  SingletonThunk_00431E70(this);\n  atexit(ConditionalCleanup);\n'
    assert g(src) == '  SingletonThunk_00431E70();\n  atexit(ConditionalCleanup);\n'
