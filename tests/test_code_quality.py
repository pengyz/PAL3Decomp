#!/usr/bin/env python3
"""[质量专项阶段 1] code_quality 纯函数单测（R15；fixture 文本，不碰真 pal3/src）。"""
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / 'tools'))

import code_quality as cq  # noqa: E402


def test_measure_basic_counts():
    src = ('void f() {\n'
           '  int v1 = *(_DWORD *)x;        // eax\n'
           '  v1 = (_DWORD)(y + 3);\n'
           '  v1 = this + 0x40;\n'
           '  // TODO: fix me\n'
           '}\n')
    m = cq.measure_text(src)
    assert m['lines'] == 6
    assert m['_raw']['casts'] >= 1
    assert m['_raw']['ptr_arith'] >= 2          # *(_DWORD*) 与 this+0x40
    assert m['_raw']['hr_names'] >= 1           # v1
    assert m['_raw']['reg_comments'] >= 1       # // eax
    assert m['todo_count'] == 1


def test_measure_masking_comments_strings():
    src = ('// (_DWORD) 假 cast 与 12345 假数字\n'
           'const char *s = "(_DWORD) 777";\n'
           'int a = 2;\n')
    m = cq.measure_text(src)
    assert m['_raw']['casts'] == 0       # 注释/串内不计
    assert m['_raw']['magic_nums'] == 1  # 仅代码位的 2（0/1 除外；串内 777 被掩）
    assert m['magic_num_per_kloc'] > 0


def test_unnamed_fn_rate():
    src = ('void sub_401000() {\n}\n'
           'void RealName() {\n}\n'
           'void _todo_004C6240() {\n}\n')
    m = cq.measure_text(src)
    assert m['_raw']['fndefs'] == 3
    assert m['_raw']['unnamed_fns'] == 2        # sub_401000 + _todo_004C6240（地址后缀形族）


def test_bucket_and_summarize():
    assert cq.bucket_of(100).startswith('小')
    assert cq.bucket_of(500).startswith('中')
    assert cq.bucket_of(2000).startswith('大')
    assert cq.bucket_of(9000).startswith('超大')
    units = [dict(cq.measure_text('int a = 2;\n'), unit='a.cpp', bucket='小(<200 行)'),
             dict(cq.measure_text('int b = 3;\nint c = 4;\n'), unit='b.cpp', bucket='小(<200 行)')]
    s = cq.summarize(units)
    assert s['units'] == 2 and s['total_lines'] == 3
    assert 'cast_per_kloc' in s['avg'] and 'todo_per_kloc' in s['avg']


def test_top_offenders_ordering():
    units = [dict(cq.measure_text('(_DWORD)a (_DWORD)b (_DWORD)c\n'), unit='hi.cpp'),
             dict(cq.measure_text('int a = 2;\n'), unit='lo.cpp')]
    rows = cq.top_offenders(units, 'cast_per_kloc', n=2)
    assert rows[0]['unit'] == 'hi.cpp' and rows[1]['unit'] == 'lo.cpp'


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
