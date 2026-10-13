"""[T51] R15 单测先行：drop_call_echo_arg 的方法隐式 this 回波剔除（T50 blocker）。

契约（F-echo-drop-this-gap）：
① 方法 def-head（`Cls::name(...)` 形）的隐式 this ∈ 回波形参集——
   this-strip 后 def-head 无 this，但调用形渲 `this` 回波须剔
② 非回波实参不动（真参不剔）
③ 幂等（二次套用不再变）
④ 注释/字面量内同名不误改（掩码语义）

⚠️ T50 教训：thunk 形实验净负当场回退——本批只闭合通路（工具层），
源形重建（thunk×3/尾调用×1）另批重试。
"""
import sys
import os
import unittest

_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
sys.path.insert(0, _ROOT)
sys.path.insert(0, os.path.join(_ROOT, 'pipeline', 'gen'))

from data import store            # noqa: E402
store.load()

from ast_transform import drop_call_echo_arg  # noqa: E402


SLOTS = {'compiler_init_005090A0': 0}


class TestDropCallEchoArg(unittest.TestCase):
    def test_method_this_echo_dropped(self):
        code = ('void CCBStageEffect::PreLoadEffGroup(CCBStageEffect *this)\n'
                '{\n  compiler_init_005090A0(this);\n}\n')
        out = drop_call_echo_arg(code, SLOTS)
        self.assertIn('compiler_init_005090A0()', out)
        self.assertNotIn('compiler_init_005090A0(this)', out)

    def test_non_echo_arg_untouched(self):
        code = ('void CCBStageEffect::PreLoadEffGroup(CCBStageEffect *this)\n'
                '{\n  compiler_init_005090A0(v7);\n}\n')
        out = drop_call_echo_arg(code, SLOTS)
        self.assertIn('compiler_init_005090A0(v7)', out)

    def test_idempotent(self):
        code = ('void CCBStageEffect::PreLoadEffGroup(CCBStageEffect *this)\n'
                '{\n  compiler_init_005090A0(this);\n}\n')
        once = drop_call_echo_arg(code, SLOTS)
        twice = drop_call_echo_arg(once, SLOTS)
        self.assertEqual(once, twice)

    def test_string_literal_not_rewritten(self):
        code = ('void CCBStageEffect::PreLoadEffGroup(CCBStageEffect *this)\n'
                '{\n  Log("compiler_init_005090A0(this)");\n'
                '  compiler_init_005090A0(this);\n}\n')
        out = drop_call_echo_arg(code, SLOTS)
        self.assertIn('Log("compiler_init_005090A0(this)")', out)
        self.assertNotIn('compiler_init_005090A0(this);', out)


if __name__ == '__main__':
    unittest.main()
