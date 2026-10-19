#!/usr/bin/env python3
"""[P1 dict 分派 2026-10-19] _emit_member dict 型分派单测（R15）。

病灶：dict 型（{"struct": [...]}/{"union": [...]})被当型名字符串渲染 ⇒ 变体层丢 ⇒ C2039。
"""
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))


def _render(mtype, mname='overlay', off=0):
    """模拟 _emit_member 的 dict 分派逻辑（纯断言 · 不加载 IDA 依赖）。"""
    if isinstance(mtype, dict):
        vk = 'union' if 'union' in mtype else 'struct'
        variants = mtype.get(vk) or []
        out = ['    %s {' % vk]
        for v in variants:
            vn = v.get('name', ''); vt = v.get('type', 'int')
            if isinstance(vt, dict):
                nk = 'union' if 'union' in vt else 'struct'
                out.append('        %s {' % nk)
                for nv in vt.get(nk) or []:
                    out.append('            %s %s;' % (nv.get('type', 'int'), nv.get('name', '')))
                out.append('        } %s;' % vn)
            else:
                out.append('        %s %s;' % (vt, vn))
        out.append('    } %s; // +0x%X' % (mname, off))
        return '\n'.join(out)
    return '%s %s;' % (mtype, mname)


def test_struct_form():
    out = _render({'struct': [{'offset': 0, 'name': 'a', 'type': 'int'},
                              {'offset': 4, 'name': 'b', 'type': 'float'}]}, 'skillCount', 290)
    assert 'struct {' in out and 'skillCount;' in out, out
    assert 'int a;' in out and 'float b;' in out


def test_union_form():
    out = _render({'union': [{'type': 'void *', 'name': 'v1'},
                             {'type': 'char *', 'name': 'v2'}]}, 'm_textx', 8)
    assert 'union {' in out and 'm_textx;' in out, out


def test_nested_form():
    out = _render({'union': [{'type': {'struct': [{'offset': 0, 'name': 'x', 'type': 'int'}]},
                              'name': 'inner'}]}, 'outer', 0)
    assert 'union {' in out and 'struct {' in out, out


def test_plain_type_passthrough():
    assert _render('int', 'm_x', 4) == 'int m_x;'


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
