"""Test check_annotations.py nested_types validation rules."""
import sys, os, json, tempfile
sys.path.insert(0, 'pipeline')
from check_annotations import check

def _run_check(struct_data):
    """Helper: run check with a single custom struct."""
    with tempfile.TemporaryDirectory() as td:
        struct_file = os.path.join(td, "Test.json")
        with open(struct_file, 'w') as f:
            json.dump(struct_data, f)
        errors, warnings = check(struct_dir=td)
        return errors, warnings

def test_nested_struct_missing_kind():
    errs, _ = _run_check({
        "name": "Test", "nested_types": {"N": {"binary_size": 4}}
    })
    assert any("kind" in e for e in errs)

def test_nested_struct_missing_binary_size():
    errs, _ = _run_check({
        "name": "Test", "nested_types": {"N": {"kind": "struct"}}
    })
    assert any("binary_size" in e for e in errs)

def test_nested_enum_missing_values():
    errs, _ = _run_check({
        "name": "Test", "nested_types": {"E": {"kind": "enum"}}
    })
    assert any("values" in e for e in errs)

def test_nested_valid_struct():
    errs, _ = _run_check({
        "name": "Test", "nested_types": {"N": {"kind": "struct", "binary_size": 8}}
    })
    assert not errs

def test_nested_valid_enum():
    errs, _ = _run_check({
        "name": "Test", "nested_types": {"E": {"kind": "enum", "values": {"A": "0"}}}
    })
    assert not errs

def test_nested_valid_class():
    errs, _ = _run_check({
        "name": "Test", "nested_types": {"C": {"kind": "class", "binary_size": 4}}
    })
    assert not errs

def test_nested_invalid_kind():
    errs, _ = _run_check({
        "name": "Test", "nested_types": {"X": {"kind": "union"}}
    })
    assert any("kind" in e for e in errs)
