"""Test check_annotations.py nested_types validation rules."""
import sys, os, json, tempfile
sys.path.insert(0, 'pipeline')
from check_annotations import check

def _run_check(struct_data):
    """Helper: run check with a single custom struct.

    [R70 修测试隔离 2026-10-22] check() 会加载真实 functions.json（含无关错误）
    ⇒ 只过滤出与本 struct 相关的错误（Test/N/E），避免混入全仓错误。
    """
    with tempfile.TemporaryDirectory() as td:
        struct_file = os.path.join(td, "Test.json")
        with open(struct_file, 'w') as f:
            json.dump(struct_data, f)
        errors, warnings = check(struct_dir=td)
        # 过滤：只看与本测试 struct 相关的错误（Test/N/E）
        def _relevant(e):
            e = str(e)
            return ('Test' in e or 'nested' in e.lower()
                    or "N'" in e or "E'" in e
                    or 'kind' in e or 'binary_size' in e or 'values' in e)
        errors = [e for e in errors if _relevant(e)]
        warnings = [w for w in warnings if _relevant(str(w))]
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
