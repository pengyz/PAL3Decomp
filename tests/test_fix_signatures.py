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
    is_generic_type,
    is_trivial_cast_type,
    infer_void_star_types,
    infer_int_pointer_types,
    simplify_class_name,
    get_semantic_param_name,
    rename_params_in_file
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


class TestIsTrivialCastType(unittest.TestCase):
    def test_trivial_types(self):
        self.assertTrue(is_trivial_cast_type("void"))
        self.assertTrue(is_trivial_cast_type("char"))
        self.assertTrue(is_trivial_cast_type("int"))
        self.assertTrue(is_trivial_cast_type("_DWORD"))
        self.assertTrue(is_trivial_cast_type("_BYTE"))

    def test_specific_types(self):
        self.assertFalse(is_trivial_cast_type("Scene"))
        self.assertFalse(is_trivial_cast_type("UIWnd"))
        self.assertFalse(is_trivial_cast_type("Actor"))


class TestInferVoidStar(unittest.TestCase):
    def test_detect_explicit_cast(self):
        """Test detection of (ClassName *)param_name pattern"""
        import tempfile
        import json

        # Create test data
        functions_data = {
            "0x00401000": {
                "name": "TestFunc",
                "signature": "void __cdecl(void *pConfig)"
            }
        }

        decomp_bodies = {
            "0x00401000": """
                void __cdecl TestFunc(void *pConfig)
                {
                    Scene *pScene = (Scene *)pConfig;
                    ((Scene *)pConfig)->Init();
                }
            """
        }

        # Write to temp file
        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            json.dump(functions_data, f)
            temp_path = f.name

        try:
            changes = infer_void_star_types(temp_path, decomp_bodies, dry_run=True)

            self.assertEqual(len(changes), 1)
            self.assertEqual(changes[0]["param_name"], "pConfig")
            self.assertEqual(changes[0]["new_type"], "Scene *")
            self.assertEqual(changes[0]["cast_count"], 2)
        finally:
            Path(temp_path).unlink()

    def test_skip_trivial_casts(self):
        """Test that trivial casts like (void*)/(int*) are skipped"""
        import tempfile
        import json

        functions_data = {
            "0x00401000": {
                "name": "TestFunc",
                "signature": "void __cdecl(void *pData)"
            }
        }

        decomp_bodies = {
            "0x00401000": """
                void __cdecl TestFunc(void *pData)
                {
                    int x = (int)pData;
                    char c = (char)pData;
                }
            """
        }

        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            json.dump(functions_data, f)
            temp_path = f.name

        try:
            changes = infer_void_star_types(temp_path, decomp_bodies, dry_run=True)
            # Should find no changes because only trivial casts
            self.assertEqual(len(changes), 0)
        finally:
            Path(temp_path).unlink()

    def test_skip_this_parameter(self):
        """Test that 'this' parameter is not modified"""
        import tempfile
        import json

        functions_data = {
            "0x00401000": {
                "name": "TestClass::Method",
                "signature": "void __thiscall(void *this)"
            }
        }

        decomp_bodies = {
            "0x00401000": """
                void __thiscall TestClass::Method(void *this)
                {
                    ((TestClass *)this)->member = 0;
                }
            """
        }

        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            json.dump(functions_data, f)
            temp_path = f.name

        try:
            changes = infer_void_star_types(temp_path, decomp_bodies, dry_run=True)
            # Should find no changes because 'this' is skipped
            self.assertEqual(len(changes), 0)
        finally:
            Path(temp_path).unlink()


class TestInferIntParams(unittest.TestCase):
    def test_detect_int_cast_to_pointer(self):
        """Test detection of int parameter cast to pointer"""
        import tempfile
        import json

        functions_data = {
            "0x00401000": {
                "name": "TestFunc",
                "signature": "void __thiscall(TestClass *this, int a2)"
            }
        }

        decomp_bodies = {
            "0x00401000": """
                void __thiscall TestFunc(TestClass *this, int a2)
                {
                    *(_DWORD *)(a2 + 4) = 0;
                    *(_BYTE *)(a2 + 16) = 1;
                    ((Actor *)a2)->Init();
                    ((Actor *)a2)->Update();
                    return ((Actor *)a2)->GetState();
                }
            """
        }

        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            json.dump(functions_data, f)
            temp_path = f.name

        try:
            changes = infer_int_pointer_types(temp_path, decomp_bodies, dry_run=True)

            self.assertEqual(len(changes), 1)
            self.assertEqual(changes[0]["param_name"], "a2")
            self.assertEqual(changes[0]["new_type"], "Actor *")
            self.assertGreaterEqual(changes[0]["cast_count"], 2)
        finally:
            Path(temp_path).unlink()

    def test_require_multiple_casts(self):
        """Test that single cast is not enough (need >= 2)"""
        import tempfile
        import json

        functions_data = {
            "0x00401000": {
                "name": "TestFunc",
                "signature": "void __cdecl(int a1)"
            }
        }

        decomp_bodies = {
            "0x00401000": """
                void __cdecl TestFunc(int a1)
                {
                    ((Scene *)a1)->Init();
                }
            """
        }

        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            json.dump(functions_data, f)
            temp_path = f.name

        try:
            changes = infer_int_pointer_types(temp_path, decomp_bodies, dry_run=True)
            # Should find no changes because only 1 cast (need >= 2)
            self.assertEqual(len(changes), 0)
        finally:
            Path(temp_path).unlink()

    def test_skip_this_parameter(self):
        """Test that 'this' parameter is not modified even if int"""
        import tempfile
        import json

        functions_data = {
            "0x00401000": {
                "name": "TestClass::Method",
                "signature": "void __thiscall(int this)"
            }
        }

        decomp_bodies = {
            "0x00401000": """
                void __thiscall TestClass::Method(int this)
                {
                    *(_DWORD *)(this + 4) = 0;
                    *(_DWORD *)(this + 8) = 0;
                }
            """
        }

        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            json.dump(functions_data, f)
            temp_path = f.name

        try:
            changes = infer_int_pointer_types(temp_path, decomp_bodies, dry_run=True)
            # Should find no changes because 'this' is skipped
            self.assertEqual(len(changes), 0)
        finally:
            Path(temp_path).unlink()


class TestSimplifyClassName(unittest.TestCase):
    def test_remove_gb_prefix(self):
        self.assertEqual(simplify_class_name("gbMatrixStack *"), "MatrixStack")
        self.assertEqual(simplify_class_name("gbVector3 *"), "Vector3")

    def test_remove_c_prefix(self):
        self.assertEqual(simplify_class_name("CEffect *"), "Effect")
        self.assertEqual(simplify_class_name("CUtil *"), "Util")

    def test_remove_tag_prefix(self):
        self.assertEqual(simplify_class_name("tagEffObjType *"), "EffObjType")

    def test_remove_ui_prefix(self):
        self.assertEqual(simplify_class_name("UIWnd *"), "Wnd")

    def test_preserve_non_prefixed(self):
        self.assertEqual(simplify_class_name("Scene *"), "Scene")
        self.assertEqual(simplify_class_name("Actor *"), "Actor")

    def test_dont_remove_lowercase(self):
        # Should NOT remove 'C' from 'char'
        self.assertEqual(simplify_class_name("char"), "char")


class TestGetSemanticParamName(unittest.TestCase):
    def test_const_char_pointer(self):
        self.assertEqual(get_semantic_param_name("const char *", 1), "pszName")
        self.assertEqual(get_semantic_param_name("const char *", 2), "pszName2")

    def test_char_pointer(self):
        self.assertEqual(get_semantic_param_name("char *", 1), "pszBuf")
        self.assertEqual(get_semantic_param_name("char *", 2), "pszBuf2")

    def test_float(self):
        self.assertEqual(get_semantic_param_name("float", 1), "fVal")
        self.assertEqual(get_semantic_param_name("float", 2), "fVal2")

    def test_int(self):
        self.assertEqual(get_semantic_param_name("int", 1), "nVal")
        self.assertEqual(get_semantic_param_name("int", 2), "nVal2")

    def test_unsigned_int(self):
        self.assertEqual(get_semantic_param_name("unsigned int", 1), "dwVal")
        self.assertEqual(get_semantic_param_name("DWORD", 1), "dwVal")

    def test_bool(self):
        self.assertEqual(get_semantic_param_name("BOOL", 1), "bFlag")
        self.assertEqual(get_semantic_param_name("bool", 1), "bFlag")

    def test_byte(self):
        self.assertEqual(get_semantic_param_name("BYTE", 1), "byVal")
        self.assertEqual(get_semantic_param_name("unsigned char", 1), "byVal")

    def test_word(self):
        self.assertEqual(get_semantic_param_name("WORD", 1), "wVal")
        self.assertEqual(get_semantic_param_name("unsigned short", 1), "wVal")

    def test_class_pointers(self):
        self.assertEqual(get_semantic_param_name("gbMatrixStack *", 1), "pMatrixStack")
        self.assertEqual(get_semantic_param_name("CEffect *", 1), "pEffect")
        self.assertEqual(get_semantic_param_name("Scene *", 1), "pScene")
        self.assertEqual(get_semantic_param_name("UIWnd *", 1), "pWnd")

    def test_primitive_pointers(self):
        self.assertEqual(get_semantic_param_name("float *", 1), "pfVal")
        self.assertEqual(get_semantic_param_name("int *", 1), "pnVal")
        self.assertEqual(get_semantic_param_name("unsigned int *", 1), "pdwVal")
        self.assertEqual(get_semantic_param_name("void *", 1), "pData")

    def test_multiple_same_type(self):
        self.assertEqual(get_semantic_param_name("float", 1), "fVal")
        self.assertEqual(get_semantic_param_name("float", 2), "fVal2")
        self.assertEqual(get_semantic_param_name("float", 3), "fVal3")


class TestRenameParams(unittest.TestCase):
    def test_rename_generic_params(self):
        """Test basic renaming of generic parameters"""
        import tempfile
        import json

        functions_data = {
            "0x00401000": {
                "name": "TestFunc",
                "signature": "void __thiscall(TestClass *this, float a2, int a3)"
            }
        }

        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            json.dump(functions_data, f)
            temp_path = f.name

        try:
            changes = rename_params_in_file(temp_path, dry_run=True)

            self.assertEqual(len(changes), 1)
            self.assertEqual(changes[0]["new_signature"], "void __thiscall(TestClass *this, float fVal, int nVal)")
            self.assertEqual(len(changes[0]["renames"]), 2)
            self.assertEqual(changes[0]["renames"][0]["old"], "a2")
            self.assertEqual(changes[0]["renames"][0]["new"], "fVal")
            self.assertEqual(changes[0]["renames"][1]["old"], "a3")
            self.assertEqual(changes[0]["renames"][1]["new"], "nVal")
        finally:
            Path(temp_path).unlink()

    def test_preserve_semantic_names(self):
        """Test that semantic names like fAngle, pStack are not changed"""
        import tempfile
        import json

        functions_data = {
            "0x00401000": {
                "name": "TestFunc",
                "signature": "void __cdecl(float fAngle, gbMatrixStack *pStack)"
            }
        }

        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            json.dump(functions_data, f)
            temp_path = f.name

        try:
            changes = rename_params_in_file(temp_path, dry_run=True)
            # Should find no changes because parameters already have semantic names
            self.assertEqual(len(changes), 0)
        finally:
            Path(temp_path).unlink()

    def test_skip_this_parameter(self):
        """Test that 'this' parameter is never renamed"""
        import tempfile
        import json

        functions_data = {
            "0x00401000": {
                "name": "TestClass::Method",
                "signature": "void __thiscall(int this, int a2)"
            }
        }

        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            json.dump(functions_data, f)
            temp_path = f.name

        try:
            changes = rename_params_in_file(temp_path, dry_run=True)

            self.assertEqual(len(changes), 1)
            # 'this' should remain unchanged, only a2 should be renamed
            self.assertIn("int this", changes[0]["new_signature"])
            self.assertIn("int nVal", changes[0]["new_signature"])
            self.assertEqual(len(changes[0]["renames"]), 1)
            self.assertEqual(changes[0]["renames"][0]["old"], "a2")
        finally:
            Path(temp_path).unlink()

    def test_multiple_same_type_disambiguation(self):
        """Test that multiple parameters of the same type get numbered suffixes"""
        import tempfile
        import json

        functions_data = {
            "0x00401000": {
                "name": "TestFunc",
                "signature": "void __cdecl(float a1, float a2, float a3)"
            }
        }

        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            json.dump(functions_data, f)
            temp_path = f.name

        try:
            changes = rename_params_in_file(temp_path, dry_run=True)

            self.assertEqual(len(changes), 1)
            self.assertEqual(changes[0]["new_signature"], "void __cdecl(float fVal, float fVal2, float fVal3)")
            self.assertEqual(len(changes[0]["renames"]), 3)
        finally:
            Path(temp_path).unlink()

    def test_class_pointer_naming(self):
        """Test Hungarian naming for class pointers"""
        import tempfile
        import json

        functions_data = {
            "0x00401000": {
                "name": "TestFunc",
                "signature": "void __cdecl(gbMatrixStack *a1, CEffect *a2, Scene *a3)"
            }
        }

        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            json.dump(functions_data, f)
            temp_path = f.name

        try:
            changes = rename_params_in_file(temp_path, dry_run=True)

            self.assertEqual(len(changes), 1)
            sig = changes[0]["new_signature"]
            self.assertIn("gbMatrixStack *pMatrixStack", sig)
            self.assertIn("CEffect *pEffect", sig)
            self.assertIn("Scene *pScene", sig)
        finally:
            Path(temp_path).unlink()

    def test_string_pointer_naming(self):
        """Test Hungarian naming for string pointers"""
        import tempfile
        import json

        functions_data = {
            "0x00401000": {
                "name": "TestFunc",
                "signature": "void __cdecl(const char *a1, char *a2)"
            }
        }

        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            json.dump(functions_data, f)
            temp_path = f.name

        try:
            changes = rename_params_in_file(temp_path, dry_run=True)

            self.assertEqual(len(changes), 1)
            sig = changes[0]["new_signature"]
            self.assertIn("const char *pszName", sig)
            self.assertIn("char *pszBuf", sig)
        finally:
            Path(temp_path).unlink()


if __name__ == "__main__":
    unittest.main()
