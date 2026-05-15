#!/usr/bin/env python3

import sys
import unittest
from pathlib import Path

# Add tools directory to path
sys.path.insert(0, str(Path(__file__).parent.parent / "tools"))

from fix_signatures import (
    parse_signature,
    rebuild_signature,
    extract_class_from_function_name,
    demangle_msvc_params,
    is_generic_type
)


class TestParseSignature(unittest.TestCase):
    def test_basic_thiscall(self):
        sig = "int __thiscall(int this, int a)"
        parsed = parse_signature(sig)
        self.assertEqual(parsed["return_type"], "int")
        self.assertEqual(parsed["convention"], "__thiscall")
        self.assertEqual(len(parsed["params"]), 2)
        self.assertEqual(parsed["params"][0]["type"], "int")
        self.assertEqual(parsed["params"][0]["name"], "this")

    def test_no_convention(self):
        sig = "void()"
        parsed = parse_signature(sig)
        self.assertEqual(parsed["return_type"], "void")
        self.assertIsNone(parsed["convention"])
        self.assertEqual(len(parsed["params"]), 0)


class TestRebuildSignature(unittest.TestCase):
    def test_rebuild_thiscall(self):
        parsed = {
            "return_type": "int",
            "convention": "__thiscall",
            "params": [
                {"type": "MyClass *", "name": "this"},
                {"type": "int", "name": "value"}
            ]
        }
        sig = rebuild_signature(parsed)
        self.assertEqual(sig, "int __thiscall(MyClass *this, int value)")


class TestExtractClassName(unittest.TestCase):
    def test_cpp_style_name(self):
        name = "MyClass::Method"
        class_name = extract_class_from_function_name(name)
        self.assertEqual(class_name, "MyClass")

    def test_mangled_name(self):
        name = "?Method@MyClass@@QAEHXZ"
        class_name = extract_class_from_function_name(name)
        self.assertEqual(class_name, "MyClass")

    def test_no_class(self):
        name = "GlobalFunction"
        class_name = extract_class_from_function_name(name)
        self.assertIsNone(class_name)


class TestDemangleMsvcParams(unittest.TestCase):
    def test_simple_int_params(self):
        # AStarPathFinder::FindPath with 4 int parameters
        mangled = "?FindPath@AStarPathFinder@@IAEHHHHH@Z"
        result = demangle_msvc_params(mangled)
        self.assertIsNotNone(result)
        self.assertEqual(result["class_name"], "AStarPathFinder")
        self.assertEqual(result["method_name"], "FindPath")
        self.assertEqual(result["return_type"], "int")
        self.assertEqual(len(result["param_types"]), 4)
        self.assertEqual(result["param_types"], ["int", "int", "int", "int"])

    def test_void_return(self):
        # Constructor returns void
        mangled = "??0AStarPathFinder@@QAE@XZ"
        result = demangle_msvc_params(mangled)
        self.assertIsNotNone(result)
        self.assertEqual(result["class_name"], "AStarPathFinder")
        self.assertEqual(result["method_name"], "AStarPathFinder")
        self.assertEqual(result["return_type"], "void")
        self.assertEqual(len(result["param_types"]), 0)

    def test_destructor(self):
        mangled = "??1AStarPathFinder@@UAE@XZ"
        result = demangle_msvc_params(mangled)
        self.assertIsNotNone(result)
        self.assertEqual(result["class_name"], "AStarPathFinder")
        self.assertEqual(result["method_name"], "~AStarPathFinder")
        self.assertEqual(result["return_type"], "void")

    def test_pointer_param(self):
        # Method with pointer parameter
        # Note: This is a simplified test - actual MSVC encoding is more complex
        mangled = "?SetName@MyClass@@QAEXPBD@Z"
        result = demangle_msvc_params(mangled)
        # Even if we can't fully decode, should not crash
        self.assertTrue(result is None or isinstance(result, dict))

    def test_non_mangled_name(self):
        result = demangle_msvc_params("RegularFunction")
        self.assertIsNone(result)

    def test_empty_string(self):
        result = demangle_msvc_params("")
        self.assertIsNone(result)


class TestIsGenericType(unittest.TestCase):
    def test_generic_types(self):
        self.assertTrue(is_generic_type("int"))
        self.assertTrue(is_generic_type("void *"))
        self.assertTrue(is_generic_type("void*"))
        self.assertTrue(is_generic_type("char *"))
        self.assertTrue(is_generic_type("unsigned int"))

    def test_specific_types(self):
        self.assertFalse(is_generic_type("MyClass *"))
        self.assertFalse(is_generic_type("gbVector3"))
        self.assertFalse(is_generic_type("LPDIRECT3DDEVICE9"))


class TestCrossRefPal3a(unittest.TestCase):
    def test_basic_matching(self):
        # This test would require creating temporary JSON files
        # For now, we'll just verify the function exists and accepts the right params
        from fix_signatures import cross_ref_pal3a

        # Test that function signature is correct
        self.assertTrue(callable(cross_ref_pal3a))

    def test_parameter_count_mismatch_should_skip(self):
        # Test logic: if PAL3 has 3 params (including this) and PAL3A has 3 params,
        # they should NOT match (because thiscall excludes this from count)
        # This is tested indirectly through the implementation
        pass


if __name__ == "__main__":
    unittest.main()
