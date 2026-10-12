"""[T5-F5] owner 机制告警的最小自测（R11：改工具必须跑其测试）。

T4 复核 F5 实证的两个可靠性缺口，本测试锁定「只报不改行为」契约：
  ①双认领无 owner ⇒ 打印告警，行为仍是「先声明者胜」（functions.json 优先）
  ②多 struct 争 owner ⇒ 打印告警，行为仍是 last-wins（文件序后者胜）

注入面：apply_annotations.load_annotations 的纯数据路径（IDA 模块 mock 掉）。
"""
import importlib.util
import io
import json
import os
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from unittest.mock import MagicMock


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MODULE_PATH = os.path.join(ROOT, "pipeline", "ida", "apply_annotations.py")
IDA_MODULES = (
    "ida_auto",
    "ida_bytes",
    "ida_funcs",
    "ida_hexrays",
    "ida_name",
    "ida_typeinf",
    "idautils",
    "idc",
)


def _load_apply_annotations():
    saved_modules = {name: sys.modules.get(name) for name in IDA_MODULES}
    for name in IDA_MODULES:
        sys.modules[name] = MagicMock()
    try:
        spec = importlib.util.spec_from_file_location(
            "test_owner_warnings_apply_annotations", MODULE_PATH
        )
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        return module
    finally:
        for name, module in saved_modules.items():
            if module is None:
                sys.modules.pop(name, None)
            else:
                sys.modules[name] = module


class OwnerWarningTests(unittest.TestCase):
    def _run_load(self, structs, functions=None):
        """在临时 annotations 目录上跑 load_annotations，返回 (annotations, stdout)。"""
        module = _load_apply_annotations()
        with tempfile.TemporaryDirectory() as annotations_dir:
            structs_dir = os.path.join(annotations_dir, "structs")
            os.makedirs(structs_dir)
            with open(os.path.join(annotations_dir, "functions.json"), "w", encoding="utf-8") as f:
                json.dump(functions or {}, f)
            with open(os.path.join(annotations_dir, "globals.json"), "w", encoding="utf-8") as f:
                json.dump({}, f)
            for fname, sdata in structs.items():
                with open(os.path.join(structs_dir, fname), "w", encoding="utf-8") as f:
                    json.dump(sdata, f)
            module.ANNOTATIONS_DIR = annotations_dir
            buf = io.StringIO()
            with redirect_stdout(buf):
                annotations = module.load_annotations()
            return annotations, buf.getvalue()

    def test_dual_claim_without_owner_warns_and_behavior_unchanged(self):
        """①双认领无 owner：告警 + 先声明者胜（AFirst.json 先于 BSecond.json）。"""
        method = {"name": "Foo", "signature": "void __thiscall()"}
        annotations, out = self._run_load({
            "AFirst.json": {"methods": {"0x00400000": dict(method)}},
            "BSecond.json": {"methods": {"0x00400000": dict(method, name="Bar")}},
        })
        self.assertIn("双认领", out)
        self.assertIn("0x00400000", out)
        # 行为不变：无 owner 时先声明者胜
        self.assertEqual(annotations["functions"]["0x00400000"]["class"], "AFirst")
        self.assertEqual(annotations["functions"]["0x00400000"]["name"], "Foo")

    def test_functions_json_plus_struct_claim_warns(self):
        """①变体：functions.json 与 struct 同址且均无 owner ⇒ 同样计入双认领。"""
        annotations, out = self._run_load(
            {"AFirst.json": {"methods": {"0x00400000": {"name": "Foo"}}}},
            functions={"0x00400000": {"name": "Old"}},
        )
        self.assertIn("双认领", out)
        # 行为不变：addr 已在 functions.json 且无 owner ⇒ functions.json 条目保留
        self.assertEqual(annotations["functions"]["0x00400000"]["name"], "Old")

    def test_multi_owner_conflict_warns_and_last_wins(self):
        """②多 struct 争 owner：告警 + last-wins（BSecond.json 文件序在后）。"""
        annotations, out = self._run_load({
            "AFirst.json": {"methods": {
                "0x00400000": {"name": "Foo", "owner": "AFirst", "signature": "void __thiscall()"}}},
            "BSecond.json": {"methods": {
                "0x00400000": {"name": "Bar", "owner": "BSecond", "signature": "void __thiscall()"}}},
        })
        self.assertIn("争 owner", out)
        self.assertIn("AFirst", out)
        self.assertIn("BSecond", out)
        # 行为不变：last-wins
        self.assertEqual(annotations["functions"]["0x00400000"]["class"], "BSecond")

    def test_single_owner_no_warning(self):
        """合法单 owner：不告警（不产生噪声）。"""
        annotations, out = self._run_load({
            "AFirst.json": {"methods": {
                "0x00400000": {"name": "Foo", "owner": "AFirst", "signature": "void __thiscall()"}}},
            "BSecond.json": {"methods": {
                "0x00400000": {"name": "Bar", "signature": "void __thiscall()"}}},
        })
        self.assertNotIn("双认领", out)
        self.assertNotIn("争 owner", out)
        # 行为不变：owner 仍然赢（t7 先例）
        self.assertEqual(annotations["functions"]["0x00400000"]["class"], "AFirst")


if __name__ == "__main__":
    unittest.main()
