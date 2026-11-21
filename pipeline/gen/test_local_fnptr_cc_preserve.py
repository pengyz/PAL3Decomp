"""体内局部函数指针声明的 CC 保护单测（20261121 stage1 变换#1 修复）。

根因: 变换#1 全树递归剥 ms_call_modifier，把体内局部 fnptr 声明器的 __stdcall
也剥掉 → `v7 = PtInRect` C2440（UIRoleSelectDialog Update 案）。
判别式: 定义行 CC = function_definition 直接子节点; 体内/形参 CC = 嵌套节点，语义必须保留。
"""
import os
import sys
import unittest

_GEN = os.path.dirname(os.path.abspath(__file__))
_ROOT = os.path.dirname(os.path.dirname(_GEN))
sys.path.insert(0, _ROOT)
sys.path.insert(0, _GEN)
sys.path.insert(0, os.path.join(_GEN, 'stages'))
os.environ.setdefault('PROJECT_ROOT', _ROOT)

from transform import make_context
import stage1_structural


class TestLocalFnptrCcPreserve(unittest.TestCase):
    CODE = (
        'BOOL UIRoleSelectDialog::Update(int a, int b)\n'
        '{\n'
        '  BOOL (__stdcall *v7)(const RECT *, POINT); // ebp\n'
        '  int (__stdcall *v8)(void *a1);\n'
        '  v7 = PtInRect;\n'
        '  return 0;\n'
        '}\n'
    )

    def _run(self, sig='BOOL __thiscall(int,int)'):
        return stage1_structural.run(self.CODE, make_context(
            'UIRoleSelectDialog', 'Update', sig=sig, is_free=False))

    def test_body_local_fnptr_stdcall_preserved(self):
        out = self._run()
        self.assertIn('BOOL (__stdcall *v7)', out)
        self.assertIn('int (__stdcall *v8)', out)

    def test_definition_line_cc_still_stripped(self):
        out = self._run()
        # 定义行(第一行)不允许再带 CC
        first = out.split('\n')[0]
        for cc in ('__thiscall', '__stdcall', '__cdecl', '__fastcall'):
            self.assertNotIn(cc, first)

    def test_fnptr_param_cc_preserved(self):
        code = (
            'void H(int (__stdcall *cb)(int))\n{\n  cb(1);\n}\n'
        )
        out = stage1_structural.run(code, make_context('', 'H', sig='', is_free=True))
        self.assertIn('int (__stdcall *cb)(int)', out)

    def test_dtor_path_unaffected(self):
        # ctor/dtor 走 step4 整前缀剥除，本不受影响——回归守卫
        code = (
            'UIRoleSelectDialog::~UIRoleSelectDialog()\n{\n'
            '  BOOL (__stdcall *v7)(const RECT *, POINT);\n'
            '  v7 = PtInRect;\n}\n'
        )
        out = stage1_structural.run(code, make_context(
            'UIRoleSelectDialog', '~UIRoleSelectDialog', sig='', is_free=False,
            flags=['dtor']))
        self.assertIn('(__stdcall *v7)', out)


if __name__ == '__main__':
    unittest.main()
