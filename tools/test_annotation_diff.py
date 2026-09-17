"""`tools/annotation_diff.py` 的回归用例。

## 为什么写这个
该工具是 CLAUDE.md 的强制检查点（`apply` 后必须跑）。它曾经有一个**真实漏洞**：
`compare_struct` 只比较 `binary_size` 与 `known_members`，**`methods`（函数归属）
从不比较**。而归属迁移是本项目最主要的改动类型 —— 于是把
`UIWnd::GetWidth/GetHeight/GetPosition` 迁到 `UIProgressBar` 之后，工具仍报
「变更结构体数量: 0 / verdict: clean」，而 `git status` 明确显示两个文件已修改。
**一个报"clean"的门禁比没有门禁更危险。**

修法：白名单（`name`/`known_members`/`binary_size`）之外的**全部顶层字段**
逐字段比较，dict 字段再按键细化 —— 这样下一个新增字段不会再被静默忽略。

运行：`python3 -m unittest tools.test_annotation_diff -v`
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools.annotation_diff import (  # noqa: E402
    AnnotationDiffer, ChangeType, summarize_value,
)


def make_differ():
    """构造比较器；只调用纯函数式的 compare_* ，不碰 git / 磁盘。"""
    return AnnotationDiffer()


class TestCompareOtherFields(unittest.TestCase):
    def setUp(self):
        self.d = make_differ()
        self.base = {
            "name": "UIWnd",
            "binary_size": 68,
            "known_members": {"64": {"name": "m_bfocus", "type": "int"}},
            "methods": {
                "0x0043FDC0": {"name": "GetWidth", "signature": "void __thiscall(int)"},
                "0x00445B40": {"name": "_UIWnd"},
            },
        }

    def _types(self, changes):
        return sorted((c.change_type.value, c.field, c.offset) for c in changes)

    def test_method_removed_is_detected(self):
        """真实案例：从 UIWnd 移除一个方法，必须被检出。"""
        new = dict(self.base)
        new["methods"] = {"0x00445B40": {"name": "_UIWnd"}}
        ch = self.d.compare_other_fields(self.base, new)
        self.assertEqual(self._types(ch), [("field_removed", "methods", "0x0043FDC0")])
        self.assertIn("GetWidth", ch[0].old_value)

    def test_method_added_is_detected(self):
        """同一 VA 出现在另一个类里（迁移的另一半）。"""
        new = {"name": "UIProgressBar", "binary_size": 244, "known_members": {},
               "methods": {"0x0043FDC0": {"name": "GetWidth"}}}
        old = {"name": "UIProgressBar", "binary_size": 244, "known_members": {},
               "methods": {}}
        ch = self.d.compare_other_fields(old, new)
        self.assertEqual(self._types(ch), [("field_added", "methods", "0x0043FDC0")])

    def test_method_changed_is_detected(self):
        new = dict(self.base)
        new["methods"] = dict(self.base["methods"])
        new["methods"]["0x0043FDC0"] = {"name": "SetWidth",
                                        "signature": "void __thiscall(int)"}
        ch = self.d.compare_other_fields(self.base, new)
        self.assertEqual(self._types(ch), [("field_changed", "methods", "0x0043FDC0")])

    def test_base_class_change_is_detected(self):
        """`base_class` 变更同样曾经不可见。"""
        old = {"name": "X", "known_members": {}, "base_class": ["UIWnd"]}
        new = {"name": "X", "known_members": {}, "base_class": ["UIFrameWnd"]}
        ch = self.d.compare_other_fields(old, new)
        self.assertEqual(self._types(ch), [("field_changed", "base_class", "")])

    def test_vtables_change_is_detected(self):
        old = {"name": "X", "known_members": {}, "vtables": [{"addr": "0x1"}]}
        new = {"name": "X", "known_members": {}, "vtables": [{"addr": "0x2"}]}
        ch = self.d.compare_other_fields(old, new)
        self.assertEqual(len(ch), 1)
        self.assertEqual(ch[0].field, "vtables")

    def test_unknown_future_field_is_detected(self):
        """白名单之外的新字段也必须被检出（防下一个洞）。"""
        old = {"name": "X", "known_members": {}}
        new = {"name": "X", "known_members": {}, "_brand_new_field": 7}
        ch = self.d.compare_other_fields(old, new)
        self.assertEqual(self._types(ch), [("field_added", "_brand_new_field", "")])

    def test_detailed_fields_are_not_double_reported(self):
        """name / known_members / binary_size 由专门逻辑处理，这里不能再报一次。"""
        old = {"name": "A", "binary_size": 4, "known_members": {"0": {"name": "m"}}}
        new = {"name": "B", "binary_size": 8,
               "known_members": {"0": {"name": "m"}, "4": {"name": "n"}}}
        self.assertEqual(self.d.compare_other_fields(old, new), [])

    def test_identical_data_yields_no_changes(self):
        self.assertEqual(self.d.compare_other_fields(self.base, dict(self.base)), [])


class TestCompareStructIntegration(unittest.TestCase):
    """`compare_struct` 必须把 methods 变更合并进结果（回归的真正入口）。"""

    def test_compare_struct_reports_method_move(self):
        d = make_differ()
        old = {"name": "UIWnd", "binary_size": 68,
               "known_members": {"64": {"name": "m_bfocus", "type": "int"}},
               "methods": {"0x0043FDC0": {"name": "GetWidth"}}}
        new = {"name": "UIWnd", "binary_size": 68,
               "known_members": {"64": {"name": "m_bfocus", "type": "int"}},
               "methods": {}}
        diff = d.compare_struct(old, new)
        kinds = [c.change_type for c in diff.changes]
        self.assertIn(ChangeType.FIELD_REMOVED, kinds,
                      "methods 变更必须出现在 compare_struct 的结果里")

    def test_pure_method_change_makes_struct_dirty(self):
        """只有 methods 变化时，StructDiff 也必须非空（否则上层统计成 0）。"""
        d = make_differ()
        old = {"name": "X", "known_members": {}, "methods": {"0x1": {"name": "a"}}}
        new = {"name": "X", "known_members": {}, "methods": {"0x1": {"name": "b"}}}
        self.assertTrue(d.compare_struct(old, new).changes)


class TestSummarize(unittest.TestCase):
    def test_truncates_long_values(self):
        self.assertTrue(summarize_value({"a": "x" * 500}).endswith("..."))

    def test_short_value_intact(self):
        self.assertEqual(summarize_value({"a": 1}), '{"a": 1}')


if __name__ == '__main__':
    unittest.main()