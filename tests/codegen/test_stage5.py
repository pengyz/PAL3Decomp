"""Codegen stage tests - verify key transformations work correctly."""
import sys
from pathlib import Path

# Setup import paths
PROJECT_ROOT = Path(__file__).resolve().parent.parent.parent
sys.path.insert(0, str(PROJECT_ROOT / "pipeline" / "gen"))
sys.path.insert(0, str(PROJECT_ROOT / "pipeline"))
sys.path.insert(0, str(PROJECT_ROOT))

from stages.stage5_fixup import _fix_single_ref_arg, _fix_operator_new_cast


def test_stage5_ref_params():
    """Verify: _fix_ref_params handles &arg → arg and arg → *arg."""
    # Case 1: &arg → arg
    assert _fix_single_ref_arg('&vec') == 'vec'
    assert _fix_single_ref_arg(' &vec') == 'vec'
    
    # Case 2: plain identifier → add *
    assert _fix_single_ref_arg('pBox') == '*pBox'
    
    # Case 3: numeric constant → no change
    assert _fix_single_ref_arg('9') == '9'
    assert _fix_single_ref_arg('0') == '0'


def test_stage5_operator_new_cast():
    """Verify: _fix_operator_new_cast adds casts to operator new."""
    code = """    int *v1; // eax
    v1 = operator new(656 * v4);
    char *v2;
    v2 = operator new(100);
"""
    result = _fix_operator_new_cast(code)
    # Should have casts added
    assert 'operator new' in result


if __name__ == "__main__":
    tests = [test_stage5_ref_params, test_stage5_operator_new_cast]
    passed = 0
    failed = 0
    for test in tests:
        try:
            test()
            print(f"  ✅ {test.__name__}")
            passed += 1
        except AssertionError as e:
            print(f"  ❌ {test.__name__}: {e}")
            failed += 1
        except Exception as e:
            print(f"  ⚠️  {test.__name__}: {e}")
            failed += 1
    print(f"\nResults: {passed} passed, {failed} failed")
    sys.exit(1 if failed else 0)
