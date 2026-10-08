import importlib.util
import json
import os
import sys
import tempfile
import unittest
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


class OwnerFieldTests(unittest.TestCase):
    @staticmethod
    def _load_apply_annotations():
        saved_modules = {name: sys.modules.get(name) for name in IDA_MODULES}
        for name in IDA_MODULES:
            sys.modules[name] = MagicMock()
        try:
            spec = importlib.util.spec_from_file_location(
                "test_apply_annotations", MODULE_PATH
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

    def _load_for_methods(self, first_method, owner_method):
        module = self._load_apply_annotations()
        with tempfile.TemporaryDirectory() as annotations_dir:
            structs_dir = os.path.join(annotations_dir, "structs")
            os.makedirs(structs_dir)
            with open(os.path.join(annotations_dir, "functions.json"), "w", encoding="utf-8") as stream:
                json.dump({}, stream)
            with open(os.path.join(annotations_dir, "globals.json"), "w", encoding="utf-8") as stream:
                json.dump({}, stream)
            with open(os.path.join(structs_dir, "AFirst.json"), "w", encoding="utf-8") as stream:
                json.dump({"methods": {"0x00400000": first_method}}, stream)
            with open(os.path.join(structs_dir, "BOwner.json"), "w", encoding="utf-8") as stream:
                json.dump({"methods": {"0x00400000": owner_method}}, stream)

            module.ANNOTATIONS_DIR = annotations_dir
            annotations = module.load_annotations()

        return annotations["functions"]["0x00400000"]["class"]

    def test_owner_annotation_overrides_first_declaration(self):
        function_class = self._load_for_methods(
            {"name": "Method"},
            {"name": "Method", "owner": "BOwner"},
        )
        self.assertEqual(function_class, "BOwner")

    def test_missing_owner_preserves_first_declaration(self):
        function_class = self._load_for_methods(
            {"name": "Method"},
            {"name": "Method"},
        )
        self.assertEqual(function_class, "AFirst")


if __name__ == "__main__":
    unittest.main()
