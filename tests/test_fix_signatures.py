import pytest
import json
import sys
from pathlib import Path

project_root = Path(__file__).parent.parent
sys.path.insert(0, str(project_root / "tools"))

from fix_signatures import parse_signature, rebuild_signature, extract_class_from_function_name


class TestParseSignature:
    def test_simple_thiscall_with_int_this(self):
        sig = "char __thiscall(int this, float x)"
        parsed = parse_signature(sig)
        assert parsed["return_type"] == "char"
        assert parsed["convention"] == "__thiscall"
        assert len(parsed["params"]) == 2
        assert parsed["params"][0] == {"type": "int", "name": "this"}
        assert parsed["params"][1] == {"type": "float", "name": "x"}

    def test_thiscall_with_pointer_this(self):
        sig = "BOOL __thiscall(GRPinput *this)"
        parsed = parse_signature(sig)
        assert parsed["return_type"] == "BOOL"
        assert parsed["convention"] == "__thiscall"
        assert len(parsed["params"]) == 1
        assert parsed["params"][0] == {"type": "GRPinput *", "name": "this"}

    def test_stdcall_no_this(self):
        sig = "int __stdcall(int base, int count, int elemSize, int compareFunc)"
        parsed = parse_signature(sig)
        assert parsed["return_type"] == "int"
        assert parsed["convention"] == "__stdcall"
        assert len(parsed["params"]) == 4
        assert parsed["params"][0] == {"type": "int", "name": "base"}

    def test_no_params(self):
        sig = "int()"
        parsed = parse_signature(sig)
        assert parsed["return_type"] == "int"
        assert parsed["convention"] is None
        assert parsed["params"] == []

    def test_complex_return_type(self):
        sig = "gbVFileSystem *__thiscall(OpenSceneFile *this)"
        parsed = parse_signature(sig)
        assert parsed["return_type"] == "gbVFileSystem *"
        assert parsed["convention"] == "__thiscall"

    def test_double_pointer_param(self):
        sig = "gbVFileSystem *__thiscall(OpenNULLFile **this)"
        parsed = parse_signature(sig)
        assert parsed["params"][0] == {"type": "OpenNULLFile **", "name": "this"}

    def test_void_return(self):
        sig = "void __thiscall(int this, float a2)"
        parsed = parse_signature(sig)
        assert parsed["return_type"] == "void"


class TestRebuildSignature:
    def test_roundtrip_simple(self):
        sig = "char __thiscall(int this, float x)"
        parsed = parse_signature(sig)
        rebuilt = rebuild_signature(parsed)
        assert rebuilt == sig

    def test_roundtrip_no_convention(self):
        sig = "int()"
        parsed = parse_signature(sig)
        rebuilt = rebuild_signature(parsed)
        assert rebuilt == sig

    def test_modify_param_type(self):
        sig = "char __thiscall(int this, float x)"
        parsed = parse_signature(sig)
        parsed["params"][0]["type"] = "MyClass *"
        rebuilt = rebuild_signature(parsed)
        assert rebuilt == "char __thiscall(MyClass *this, float x)"

    def test_roundtrip_complex(self):
        sig = "gbVFileSystem *__thiscall(OpenSceneFile *this, char *String1)"
        parsed = parse_signature(sig)
        rebuilt = rebuild_signature(parsed)
        assert rebuilt == sig


class TestExtractClassName:
    def test_simple_class_method(self):
        name = "GRPinput::GetCursorPos"
        cls = extract_class_from_function_name(name)
        assert cls == "GRPinput"

    def test_constructor(self):
        name = "OpenSceneFile::OpenSceneFile"
        cls = extract_class_from_function_name(name)
        assert cls == "OpenSceneFile"

    def test_destructor(self):
        name = "OpenSceneFile::~OpenSceneFile"
        cls = extract_class_from_function_name(name)
        assert cls == "OpenSceneFile"

    def test_mangled_name(self):
        name = "?Method@ClassName@@QAEXH@Z"
        cls = extract_class_from_function_name(name)
        assert cls == "ClassName"

    def test_no_class(self):
        name = "ArraySort"
        cls = extract_class_from_function_name(name)
        assert cls is None

    def test_skip_template(self):
        name = "vector<int>::push_back"
        cls = extract_class_from_function_name(name)
        assert cls is None

    def test_skip_dollar_sign(self):
        name = "Class$Template::Method"
        cls = extract_class_from_function_name(name)
        assert cls is None


class TestFixThisType:
    @pytest.fixture
    def temp_functions_json(self, tmp_path):
        test_data = {
            "0x00401000": {
                "name": "MyClass::Method1",
                "signature": "int __thiscall(int this)"
            },
            "0x00401100": {
                "name": "MyClass::Method2",
                "signature": "void __thiscall(int this, float x)"
            },
            "0x00401200": {
                "name": "AlreadyFixed::Method",
                "signature": "int __thiscall(AlreadyFixed *this)"
            },
            "0x00401300": {
                "name": "NotThiscall",
                "signature": "int __stdcall(int a1)"
            },
            "0x00401400": {
                "name": "?MangledMethod@MangledClass@@QAEXH@Z",
                "signature": "void __thiscall(int this, int param)"
            },
            "0x00401500": {
                "name": "vector<int>::push",
                "signature": "void __thiscall(int this)"
            },
        }

        json_file = tmp_path / "functions.json"
        with open(json_file, 'w') as f:
            json.dump(test_data, f, indent=2)

        return json_file

    def test_dry_run_identifies_correct_functions(self, temp_functions_json):
        from fix_signatures import fix_this_type_in_file

        changes = fix_this_type_in_file(temp_functions_json, dry_run=True)

        assert len(changes) == 3

        addrs = [c["address"] for c in changes]
        assert "0x00401000" in addrs
        assert "0x00401100" in addrs
        assert "0x00401400" in addrs

        assert "0x00401200" not in addrs
        assert "0x00401300" not in addrs
        assert "0x00401500" not in addrs

    def test_apply_modifies_signatures(self, temp_functions_json):
        from fix_signatures import fix_this_type_in_file

        changes = fix_this_type_in_file(temp_functions_json, dry_run=False)

        with open(temp_functions_json) as f:
            data = json.load(f)

        assert data["0x00401000"]["signature"] == "int __thiscall(MyClass *this)"
        assert data["0x00401100"]["signature"] == "void __thiscall(MyClass *this, float x)"
        assert data["0x00401400"]["signature"] == "void __thiscall(MangledClass *this, int param)"

        assert data["0x00401200"]["signature"] == "int __thiscall(AlreadyFixed *this)"
        assert data["0x00401300"]["signature"] == "int __stdcall(int a1)"
        assert data["0x00401500"]["signature"] == "void __thiscall(int this)"
