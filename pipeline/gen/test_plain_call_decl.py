"""批 11 回退态测试（2026-09-29 零回归门：函数形声明合成全撤——C2668 幻影重载实证）。
教训：声明面合成与 free_functions/globals/macros 互连过深——review 静态面≠生产实效面。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
sys.path.insert(0, os.path.join(_GEN, 'stages'))
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestRolledBackBatch11(unittest.TestCase):
    def test_plain_call_not_collected(self):
        # 回退态：裸函数名不收集（批 11 全撤）
        from emit_cpp import collect_undefined_refs
        code = 'int F(void)\n{\n    return DllMain((void*)0x3E8, a, b);\n}\n'
        self.assertNotIn('DllMain', collect_undefined_refs(code))

    def test_no_phantom_decl(self):
        # 回退态：无 `int name(...)` 幻影声明（C2668 歧义重载源）
        from emit_cpp import generate_forward_decls
        code = 'int F(void)\n{\n    return DllMain((void*)0x3E8, a, b);\n}\n'
        out = generate_forward_decls(code)
        self.assertNotIn('int DllMain(...);', out)

    def test_nullsub_branch_intact(self):
        # 回退态：nullsub/atexit 分支原态（撤时误吞教训）
        from emit_cpp import generate_forward_decls
        code = 'int F(void) { return nullsub_5(1); }\n'
        out = generate_forward_decls(code)
        self.assertIn('void __cdecl nullsub_5(...);', out)


if __name__ == '__main__':
    unittest.main()
