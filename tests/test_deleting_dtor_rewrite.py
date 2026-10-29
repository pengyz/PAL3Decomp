"""删析构调用形转写（T4 批1）——R15 纯函数单测。运行: pytest tests/test_deleting_dtor_rewrite.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'pipeline/gen'))
from textutil import rewrite_deleting_dtor_calls as f


def test_flag0_explicit_dtor():
    src = '    (((UIRenderObj *)Instance))->UIRenderObj::_sdtor_call_dtor(0);'
    assert f(src) == '    (((UIRenderObj *)Instance))->~UIRenderObj();'


def test_flag1_delete():
    src = '          (((UIRenderObj *)v6))->UIRenderObj::_sdtor_call_dtor(1);'
    assert f(src) == '          delete (((UIRenderObj *)v6));'


def test_unqualified_untouched():
    src = '    x->_sdtor_call_dtor(1);'
    assert f(src) == src                       # 无类证据禁转（批2 挂账）


def test_idempotent():
    once = f('  ((A*)p))->A::_sdtor_call_dtor(1);')
    assert f(once) == once
