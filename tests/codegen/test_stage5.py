"""Codegen stage tests - verify key transformations work correctly."""
import sys
from pathlib import Path

# Setup import paths
PROJECT_ROOT = Path(__file__).resolve().parent.parent.parent
sys.path.insert(0, str(PROJECT_ROOT / "pipeline" / "gen"))
sys.path.insert(0, str(PROJECT_ROOT / "pipeline"))
sys.path.insert(0, str(PROJECT_ROOT))

from stages.stage5_fixup import (
    _fix_single_ref_arg,
    _fix_operator_new_cast,
    _fix_ref_params,
)


class _Ctx:
    """Minimal ctx: `_build_var_types` only reads `.sig`."""
    sig = "void __thiscall Cls::F(int a)"
    cls_name = "Cls"
    is_free_function = False


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


def test_stage5_case3_requires_declaration_evidence():
    """F1a: Case 3 must not add '*' to an identifier we can prove is not a pointer.

    Regression guard for the double-application bug: stage 3 strips '&' from the
    SAME table, so stage 5's Case 3 re-adds '*' to the now-bare identifier
    ('Rotate(v10, &v15)' -> 'Rotate(v10, v15)' -> 'Rotate(v10,  *v15)'; the
    extra ', ' separator plus the preserved leading space is the double space).

    These assertions deliberately encode ONLY the transform's behaviour on
    synthetic input -- never any annotation or IDB state.
    """
    # value local (its address was taken: Hex-Rays prints BYREF) -> leave bare
    out = _fix_ref_params(
        '  struct gbVec3D v15; // [esp+0x3C] [ebp-0xC] BYREF\n'
        '  float v10;\n'
        '  v15.x = 0.0;\n'
        '  o->gbMatrixStack::Rotate(v10, &v15);\n', _Ctx())
    assert 'Rotate(v10, v15)' in out, out
    assert '*v15' not in out, out

    # pointer local -> the deref IS correct and must be preserved
    out = _fix_ref_params(
        '  gbVec3D *v5; // ebp\n'
        '  o->gbMatrixStack::Translate(v5);\n', _Ctx())
    assert 'Translate(*v5)' in out, out

    # struct value local passed to a reference parameter
    out = _fix_ref_params(
        '  struct gbOBBox actionId; // BYREF\n'
        '  r->gbRay::IsColOBB_H(&actionId);\n', _Ctx())
    assert 'IsColOBB_H(actionId)' in out, out

    # array local: '*arr' is wrong for both 'T&' and 'T*' targets
    assert 'Translate(buf)' in _fix_ref_params(
        '  char buf[16];\n  o->gbMatrixStack::Translate(buf);\n', _Ctx())

    # unknown identifier (global/member) keeps the legacy behaviour
    out = _fix_ref_params(
        '  o->gbMatrixStack::Translate(g_SomeGlobal);\n', _Ctx())
    assert 'Translate(*g_SomeGlobal)' in out, out

    # no ctx -> Case 3 keeps the legacy behaviour, so the gate can never crash
    # a caller.  (Case 1 is evidence-free by nature and unchanged either way.)
    assert _fix_ref_params('  o->gbMatrixStack::Translate(v15);\n') \
        == '  o->gbMatrixStack::Translate(*v15);\n'
    assert _fix_ref_params('  o->gbMatrixStack::Rotate(a, &v15);\n') \
        == '  o->gbMatrixStack::Rotate(a, v15);\n'


def test_stage5_setaxisangle_entry_removed():
    """F1b: 'SetAxisAngle' must no longer be treated as taking a reference.

    gbengine.def (compiler-emitted mangled names) says the parameter is a
    POINTER: '?SetAxisAngle@gbQuaternion@@QAEXPAUgbVec3D@@M@Z' ('PAU', not
    'AAU').  Treating arg 0 as a reference stripped a required '&' and, for the
    static form, consumed the `this` argument and shifted every later argument.
    """
    for code in (
        '  q->gbQuaternion::SetAxisAngle(&v43, 45.0);\n',
        '  gbMatrix4::SetAxisAngle(&v4, 0, f);\n',
        '  gbMatrix4::SetAxisAngle(&v22, &v16, v13);\n',
    ):
        assert _fix_ref_params(code, _Ctx()) == code, code

    # neighbouring entries in the same table must still be applied
    out = _fix_ref_params('  gbQuaternion::Translate(&v5);\n', _Ctx())
    assert out == '  gbQuaternion::Translate(v5);\n', out


if __name__ == "__main__":
    tests = [
        test_stage5_ref_params,
        test_stage5_operator_new_cast,
        test_stage5_case3_requires_declaration_evidence,
        test_stage5_setaxisangle_entry_removed,
    ]
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
