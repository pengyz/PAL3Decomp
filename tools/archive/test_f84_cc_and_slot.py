#!/usr/bin/env python3
"""[F84 扩展测试 2026-11-13] 调用约定词 + 槽位数组形态 A 态验证。

真实树形态样本(批量轮普查实证):
  T1 cc声明: void (__thiscall ***v5)(_DWORD, _DWORD); (**v5)(v5, 0);
  T2 槽数组: void ( ***v4)(_DWORD, _DWORD); (*v4[190])(v4 + 190, 0);
  T3 已绿形态回归: (**(void ( ***)(UIPushButton *, _DWORD))X)(x, (_DWORD)(0));
预期(A态/B2前): T1/T2 的实参无 cast(C2664 现场); T3 已有 cast。
"""
import sys, os, re
_P = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
for _p in (_P, os.path.join(_P, 'pipeline'), os.path.join(_P, 'pipeline', 'gen')):
    if _p not in sys.path:
        sys.path.insert(0, _p)

from stages.stage5_fixup import _build_var_types
from stages.transform import make_context

ctx = make_context('T', 'T', sig='', stub_registry=set())

CASES = [
    ("T1 cc声明",
     'void T1(void)\n{\n'
     '  void (__thiscall ***v5)(_DWORD, _DWORD); // esi\n'
     '  (**v5)(v5, 0);\n}\n',
     'v5'),
    ("T2 槽数组",
     'void T2(void)\n{\n'
     '  void ( ***v4)(_DWORD, _DWORD); // edi\n'
     '  (*v4[190])(v4 + 190, 0);\n}\n',
     'v4'),
]

for name, code, var in CASES:
    vt = _build_var_types(code, ctx)
    info = vt.get(var)
    print('%s: vt[%s]=%s' % (name, var, info))
    if info is None or info.get('kind') != 'fnptr':
        print('  => A态断言: NO MATCH(正则缺口证实)')
    else:
        print('  => 已匹配 params=%r' % info.get('params'))

# T3 已绿形态: F84 对 typed 形态的处理(回归保护)
from stages.stage5_fixup import _fix_line_dword_slots  # noqa
src_f84 = open(os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                            'pipeline', 'gen', 'stages', 'stage5_fixup.py'),
               encoding='utf-8').read()
assert "_k = code.find('(**'" in src_f84
print('\nT3: F84 扫描入口=code.find(\'(**\') — 槽位数组 (*v4[k]) 形态不在射程(证实)')
