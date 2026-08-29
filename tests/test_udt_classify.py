"""Tests for pipeline/ida/udt_classify.py.

Root cause under test: export_full.py used to infer "is this UDT member a
base class?" from `offset == 0`, which only holds for the FIRST base class
in a multi-inheritance struct. Any additional base sits at a non-zero
offset and was silently misclassified as an anonymous data member —
emit_headers.py then rendered it as an untyped struct field, producing the
C2208 "no members defined using this type" cascade across ~38 classes
(CEff* task templates, Role/UICaption/MUIDialog/SceneObj, etc.).

See docs/knowledge/gotcha_codegen_multi_inheritance_anon_member.md.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "pipeline" / "ida"))

from udt_classify import classify_bases_and_members


def _member(name, offset, type_, is_baseclass):
    return {'name': name, 'offset': offset, 'type': type_, 'is_baseclass': is_baseclass}


def test_single_base_at_offset_zero():
    """Baseline: single inheritance still works (offset 0, is_baseclass=True)."""
    udt_members = [
        _member('', 0, 'CEffObj', True),
        _member('m_pGeomQuad', 48, 'gbGeomQuad *', False),
    ]
    annotation_members = [
        {'name': '', 'offset': 0, 'type': 'CEffObj'},
        {'name': 'm_pGeomQuad', 'offset': 48, 'type': 'gbGeomQuad *'},
    ]
    bases, filtered = classify_bases_and_members(udt_members, annotation_members, 'CEffCylinder')

    assert bases == [{'name': 'CEffObj', 'offset': 0}]
    assert filtered == [{'name': 'm_pGeomQuad', 'offset': 48, 'type': 'gbGeomQuad *'}]


def test_second_base_at_nonzero_offset_is_classified_as_base():
    """Regression test for the exact CEffCylinder bug.

    A second base class (CTaskTpl_..., at offset 12, i.e. non-zero) must be
    classified as a base, not silently kept as an anonymous data member —
    which is what an `offset == 0` heuristic would do (and did, before the fix).
    """
    udt_members = [
        _member('', 0, 'CEffObj', True),
        _member('', 12, 'CTaskTpl_tagEffTaskParam_CEffCylinder', True),
        _member('m_pGeomQuad', 48, 'gbGeomQuad *', False),
        _member('m_pTexture', 52, 'gbTexture *', False),
    ]
    annotation_members = [
        {'name': '', 'offset': 0, 'type': 'CEffObj'},
        {'name': '', 'offset': 12, 'type': 'CTaskTpl_tagEffTaskParam_CEffCylinder'},
        {'name': 'm_pGeomQuad', 'offset': 48, 'type': 'gbGeomQuad *'},
        {'name': 'm_pTexture', 'offset': 52, 'type': 'gbTexture *'},
    ]
    bases, filtered = classify_bases_and_members(udt_members, annotation_members, 'CEffCylinder')

    assert bases == [
        {'name': 'CEffObj', 'offset': 0},
        {'name': 'CTaskTpl_tagEffTaskParam_CEffCylinder', 'offset': 12},
    ]
    # Both base classes must be gone from data_members — neither should ever
    # reach emit_headers.py as an anonymous/untyped field.
    assert filtered == [
        {'name': 'm_pGeomQuad', 'offset': 48, 'type': 'gbGeomQuad *'},
        {'name': 'm_pTexture', 'offset': 52, 'type': 'gbTexture *'},
    ]


def test_anonymous_inline_union_at_nonzero_offset_is_not_a_base():
    """An anonymous member at a non-zero offset that IDA does NOT flag as a
    base class (is_baseclass=False) is an inline union/struct member, and
    must stay in data_members — this is the case the old `offset == 0`
    heuristic was trying (incorrectly) to approximate.
    """
    udt_members = [
        _member('', 0, 'CEffObj', True),
        _member('', 28, '_inline_C2DSpark_tagSpark_', False),
    ]
    annotation_members = [
        {'name': '', 'offset': 0, 'type': 'CEffObj'},
        {'name': '', 'offset': 28, 'type': '_inline_C2DSpark_tagSpark_'},
    ]
    bases, filtered = classify_bases_and_members(udt_members, annotation_members, 'C2DSpark_tagSpark')

    assert bases == [{'name': 'CEffObj', 'offset': 0}]
    assert filtered == [{'name': '', 'offset': 28, 'type': '_inline_C2DSpark_tagSpark_'}]


def test_three_base_classes_all_nonzero_except_first():
    """Three-way multi-inheritance: every base must be detected regardless
    of position, not just the first two."""
    udt_members = [
        _member('', 0, 'Object', True),
        _member('', 4, 'PalScriptWaitObj', True),
        _member('', 12, 'GlowObj', True),
        _member('m_nState', 64, 'int', False),
    ]
    annotation_members = [
        {'name': '', 'offset': 0, 'type': 'Object'},
        {'name': '', 'offset': 4, 'type': 'PalScriptWaitObj'},
        {'name': '', 'offset': 12, 'type': 'GlowObj'},
        {'name': 'm_nState', 'offset': 64, 'type': 'int'},
    ]
    bases, filtered = classify_bases_and_members(udt_members, annotation_members, 'Role')

    assert [b['name'] for b in bases] == ['Object', 'PalScriptWaitObj', 'GlowObj']
    assert filtered == [{'name': 'm_nState', 'offset': 64, 'type': 'int'}]


def test_name_based_baseclass_heuristic_is_not_used():
    """A member literally named '__parent' or containing 'baseclass' must
    NOT be treated as a base class unless IDA's is_baseclass() says so —
    the old code had a name-based fallback for this that is no longer
    needed (0 real matches found when audited against the live IDB) and
    would incorrectly promote an ordinary field to a base class by name
    coincidence alone.
    """
    udt_members = [
        _member('__parent', 0, 'int', False),
    ]
    annotation_members = [
        {'name': '__parent', 'offset': 0, 'type': 'int'},
    ]
    bases, filtered = classify_bases_and_members(udt_members, annotation_members, 'Foo')

    assert bases == []
    # Still filtered out of data_members (that part of the old behavior is
    # intentionally preserved as a defensive filter), but NOT promoted to `bases`.
    assert filtered == []


def test_self_referential_base_is_excluded():
    """A base class whose type name equals the struct's own name is never
    valid and must be excluded (defensive; guards against malformed input)."""
    udt_members = [
        _member('', 0, 'Foo', True),
    ]
    annotation_members = [
        {'name': '', 'offset': 0, 'type': 'Foo'},
    ]
    bases, filtered = classify_bases_and_members(udt_members, annotation_members, 'Foo')

    assert bases == []


def test_no_bases_passthrough():
    """A struct with no base classes at all: everything stays a data member."""
    udt_members = [
        _member('m_x', 0, 'int', False),
        _member('m_y', 4, 'float', False),
    ]
    annotation_members = [
        {'name': 'm_x', 'offset': 0, 'type': 'int'},
        {'name': 'm_y', 'offset': 4, 'type': 'float'},
    ]
    bases, filtered = classify_bases_and_members(udt_members, annotation_members, 'Vec2')

    assert bases == []
    assert filtered == annotation_members
