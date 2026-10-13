"""[T53/T51] R15 单测：drop_call_echo_arg 的方法隐式 this 回波剔除（F-echo-drop-this-gap）。

契约（T53 复核修正版）：
① 正形：带 `// attributes: thunk` 注记的 f(this) 剔（thunk 证据门）
② **负形**：无注记 f(this) **不剔**（UI3DModelNode/_Console 真实参保护）
③ 幂等（二次套用不再变）
④ 字面量撞码不误改（掩码语义）
⑤ 注释判定锚定行首注释形（字符串内同名不构成证据）

⚠️ T50/T51 教训：证据门收窄至 thunk 属性——无门首版 2 翻红当场抓回。
R11：改动 echo-drop 后**强制复跑本测**。
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

HEAD = 'void CCBStageEffect::PreLoadEffGroup(CCBStageEffect *this)\n{\n'


class TestDropCallEchoArg(unittest.TestCase):
    def test_thunk_marked_this_echo_dropped(self):
        code = (HEAD + '  // attributes: thunk\n'
                '  compiler_init_005090A0(this);\n}\n')
        out = drop_call_echo_arg(code, SLOTS)
        self.assertIn('compiler_init_005090A0()', out)
        self.assertNotIn('compiler_init_005090A0(this)', out)

    def test_unmarked_this_echo_not_dropped(self):
        # [T53②] 负形：无 thunk 注记 ⇒ 不剔（UI3DModelNode/_Console 真实参保护）
        code = (HEAD + '  compiler_init_005090A0(this);\n}\n')
        out = drop_call_echo_arg(code, SLOTS)
        self.assertIn('compiler_init_005090A0(this)', out)

    def test_non_echo_arg_untouched(self):
        code = (HEAD + '  // attributes: thunk\n'
                '  compiler_init_005090A0(v7);\n}\n')
        out = drop_call_echo_arg(code, SLOTS)
        self.assertIn('compiler_init_005090A0(v7)', out)

    def test_idempotent(self):
        code = (HEAD + '  // attributes: thunk\n'
                '  compiler_init_005090A0(this);\n}\n')
        once = drop_call_echo_arg(code, SLOTS)
        twice = drop_call_echo_arg(once, SLOTS)
        self.assertEqual(once, twice)

    def test_string_literal_not_rewritten(self):
        code = (HEAD + '  // attributes: thunk\n'
                '  Log("compiler_init_005090A0(this)");\n'
                '  compiler_init_005090A0(this);\n}\n')
        out = drop_call_echo_arg(code, SLOTS)
        self.assertIn('Log("compiler_init_005090A0(this)")', out)
        self.assertNotIn('compiler_init_005090A0(this);', out)

    def test_marker_in_string_not_counted(self):
        # [T53②] 行首锚定：字符串里的 "attributes: thunk" 不构成证据
        code = (HEAD + '  Log("attributes: thunk");\n'
                '  compiler_init_005090A0(this);\n}\n')
        out = drop_call_echo_arg(code, SLOTS)
        self.assertIn('compiler_init_005090A0(this)', out)


if __name__ == '__main__':
    unittest.main()
