"""批 C 放行条件②：R1/C′A 单测（复核点名——零覆盖实证）。含 stride 断言+回退突变杀点。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
sys.path.insert(0, os.path.join(_GEN, 'stages'))
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestR1CPrimeA(unittest.TestCase):
    def test_alias_arrow_rewritten(self):
        from stage5_fixup import _fix_register_this_alias
        s = 'void F() {\n    _ESI = this;\n    _ESI->m_x = 1;\n}\n'
        out = _fix_register_this_alias(s)
        self.assertIn('this->m_x', out)
        self.assertNotIn('_ESI = this;', out)      # 无残留用法时赋值删除

    def test_alias_bracket_keeps_assignment(self):
        # R1 收窄：`[` 形不动+赋值保留（F83/C′A 接管）——MatrixStack C2106 教训
        from stage5_fixup import _fix_register_this_alias
        s = 'void F() {\n    _ESI = this;\n    x = _ESI[1].m_y;\n}\n'
        out = _fix_register_this_alias(s)
        self.assertIn('_ESI = this;', out)          # 赋值保留
        self.assertIn('_ESI[1].m_y', out)           # `[` 形不动

    def test_typed_declaration_for_alias(self):
        # C′A：别名证 ⇒ `<Cls> *reg_X = this;`
        from stage5_fixup import _apply_text_substitutions
        class _Ctx:
            cls_name = 'RoleSystem'
            is_free_function = False
        s = 'void F() {\n    _ESI = this;\n    _ESI[1].m_y = 1;\n}\n'
        out = _apply_text_substitutions(s, _Ctx())
        self.assertIn('RoleSystem *reg_ESI = this;', out)

    def test_stride_identity_gate(self):
        # R3 位移恒等（复核阻断项）：[1] 缩放=sizeof(Cls)——断言声明型的 stride 语义
        from stage5_fixup import _apply_text_substitutions
        class _Ctx:
            cls_name = 'RoleSystem'
            is_free_function = False
        s = 'void F() {\n    _ESI = this;\n    _ESI[1].m_y = 1;\n}\n'
        out = _apply_text_substitutions(s, _Ctx())
        # [1] 前的基址必须是指针型（RoleSystem*）——sizeof(RoleSystem) 缩放
        self.assertIn('RoleSystem *reg_ESI', out)
        # 回退突变杀点：声明回 unsigned long ⇒ C2228（复核实证）
        self.assertNotIn('unsigned long reg_ESI', out)


if __name__ == '__main__':
    unittest.main()
