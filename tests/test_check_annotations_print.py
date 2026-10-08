"""回归测试：check_annotations.py 的 vtable 回归错误必须被打印。

背景（2026-10-08 撞到）：
  `pipeline/check_annotations.py` 的 `__main__` 块在 `:778-779` 打印 errors，
  但 vtable 回归检查在 `:790-793` 才 `errors.append(...)` —— 在打印循环之后。
  ⇒ pre-commit 钩子报 "1 errors, 14 warnings — FAIL" 但**不显示是什么错误**，
     使 FAIL 不可诊断。

修复：把 vtable 检查移到打印循环之前。
"""
import os
import unittest


class TestCheckAnnotationsPrintsLateErrors(unittest.TestCase):
    def _main_block(self):
        path = os.path.join(os.path.dirname(__file__), '..',
                            'pipeline', 'check_annotations.py')
        with open(path, encoding='utf-8') as f:
            src = f.read()
        return src[src.index("if __name__ == '__main__':"):]

    def test_main_block_order_is_correct(self):
        """结构性断言：__main__ 块里 vtable 检查必须在打印循环之前。"""
        main_block = self._main_block()
        print_loop = main_block.index('for e in errors:')
        vtable_append = main_block.index('errors.append(')
        self.assertLess(vtable_append, print_loop,
                        'vtable 检查的 errors.append 必须在打印循环之前，'
                        '否则 late-appended error 只计数不显示')

    def test_all_errors_are_printed(self):
        """所有 errors（含 late-appended）都必须经过打印循环。

        通过结构断言：打印循环必须位于所有 errors.append 之后。
        """
        main_block = self._main_block()
        # 所有 errors.append 的位置
        append_positions = []
        idx = 0
        while True:
            try:
                idx = main_block.index('errors.append(', idx + 1)
            except ValueError:
                break
            append_positions.append(idx)
        self.assertTrue(append_positions, '__main__ 块应至少有一处 errors.append')
        print_loop = main_block.index('for e in errors:')
        for pos in append_positions:
            self.assertLess(pos, print_loop,
                            '所有 errors.append 都必须在打印循环之前')

    def test_summary_counts_match_printed(self):
        """摘要计数与打印的一致性：摘要必须在打印之后（否则计数含未打印项）。"""
        main_block = self._main_block()
        print_loop = main_block.index('for e in errors:')
        summary = main_block.index('len(errors)} errors')
        self.assertLess(print_loop, summary,
                        '摘要必须在打印循环之后')


if __name__ == '__main__':
    unittest.main()
