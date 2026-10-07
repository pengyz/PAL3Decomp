import pytest
pytestmark = pytest.mark.skip(reason='P2 progressive snapshot')
"""Test emit_headers.py handles :: nested types correctly."""
import sys, os, json
sys.path.insert(0, 'pipeline/gen')
sys.path.insert(0, 'pipeline/gen/stages')

# Mock the IDA structs file
import tempfile, json

# Save original IDA_STRUCTS_FILE and restore
from emit_headers import generate_header, IDA_STRUCTS_FILE

def test_nested_type_declaration():
    """generate_header emits nested type forward declaration inside parent."""
    cls_name = "TestParent"
    ida_struct = {"size": 16}
    result = generate_header(cls_name, ida_struct, methods=[],
                            nested_types=["Nested", "Stack"])
    assert "struct Nested;" in result, "Missing nested Nested forward decl"
    assert "struct Stack;" in result, "Missing nested Stack forward decl"
    # Nested types must be before the struct closing };
    struct_close = result.index("};")
    nested_pos = result.index("struct Nested")
    assert nested_pos < struct_close, \
        "Nested type should be before struct closing brace"

def test_no_nested_types():
    """Without nested_types, output unchanged."""
    cls_name = "Simple"
    result = generate_header(cls_name, {}, methods=[])
    assert "struct Nested;" not in result

if __name__ == '__main__':
    test_nested_type_declaration()
    test_no_nested_types()
    print("All tests passed!")

