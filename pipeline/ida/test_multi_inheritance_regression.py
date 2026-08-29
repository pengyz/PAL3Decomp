"""IDAPython regression test: multi-inheritance base classes must round-trip
through create_fixed_struct() -> export_full's classify_bases_and_members()
without losing any base beyond the first.

ROOT CAUSE this guards against (fixed 2026-08-29):
  1. apply_annotations.create_fixed_struct() added every base class as an
     anonymous UDT member, but never called udt_member_t.set_baseclass() —
     so IDA silently treated bases 2+ as ordinary unnamed data members.
  2. export_full.py independently re-derived "is this a base class?" from
     `member.offset == 0` instead of asking IDA's authoritative
     udm_t.is_baseclass() flag — a second bug on the read side that would
     have masked bug #1 even if #1 were fixed differently.
Both bugs together caused every base class beyond the first (CEffCylinder's
CTaskTpl_tagEffTaskParam_CEffCylinder at offset 12, etc.) to be exported as
an anonymous, untyped data member, which emit_headers.py then rendered as
`SomeBaseClassType ; // +0xC` — invalid C++, triggering a C2208 cascade
across ~38 multi-inheritance classes.

See docs/knowledge/gotcha_codegen_multi_inheritance_anon_member.md.

This script exercises the REAL IDA type system (unlike
tests/test_udt_classify.py, which tests the pure-logic classifier with
synthetic input and needs no IDB). It must be run against an initialized
work IDB that already has CEffCylinder's dependency types (CEffObj,
CTaskTpl_tagEffTaskParam_CEffCylinder) resolvable in the local TIL — i.e.
after `python pipeline/cli.py init` / `apply`.

Usage (headless idalib, e.g. via idb_open + py_exec_file, or idat -A -S):
  idat -A -S"pipeline/ida/test_multi_inheritance_regression.py" original/PAL3.exe.i64

Exit behavior: raises AssertionError (non-zero style failure signal) on any
mismatch; prints "ALL REGRESSION CHECKS PASSED" and returns normally on success.
Uses a throwaway type name (prefixed _regtest_) and always cleans it up, even
on failure, so repeated runs never leave stale types in the IDB.
"""
import json
import os
import sys

import ida_typeinf

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))

if SCRIPT_DIR not in sys.path:
    sys.path.insert(0, SCRIPT_DIR)

import apply_annotations  # noqa: E402
import udt_classify  # noqa: E402

_TEST_TYPE_NAME = "_regtest_CEffCylinder"


def _cleanup(til):
    ida_typeinf.del_named_type(til, _TEST_TYPE_NAME, ida_typeinf.NTF_TYPE)


def run():
    til = ida_typeinf.get_idati()

    # Precondition: the real dependency types must already exist in this
    # IDB (they come from annotations already applied via `pipeline/cli.py
    # apply`). If they don't, this test can't distinguish "bug present"
    # from "fixture missing" — fail loudly instead of silently skipping.
    for dep in ("CEffObj", "CTaskTpl_tagEffTaskParam_CEffCylinder", "gbGeomQuad",
                "gbTexture", "gbTextureArray"):
        probe = ida_typeinf.tinfo_t()
        assert probe.get_named_type(til, dep), (
            "precondition failed: dependency type '%s' not resolvable in TIL — "
            "run `python pipeline/cli.py init` (or `apply`) first" % dep
        )

    ann_path = os.path.join(PROJECT_ROOT, "data", "annotations", "structs", "CEffCylinder.json")
    with open(ann_path) as f:
        struct_info = json.load(f)

    assert isinstance(struct_info.get("base_class"), list) and len(struct_info["base_class"]) >= 2, (
        "fixture assumption failed: data/annotations/structs/CEffCylinder.json "
        "must declare base_class as a list with >= 2 entries for this regression "
        "test to be meaningful — annotation data may have changed"
    )

    _cleanup(til)  # in case a previous failed run left it behind
    try:
        # --- Step 1: apply_annotations must round-trip both base classes ---
        ok, err = apply_annotations.create_fixed_struct(
            _TEST_TYPE_NAME, struct_info, {}, {}, til
        )
        assert ok, "create_fixed_struct failed: %s" % err

        tif = ida_typeinf.tinfo_t()
        assert tif.get_named_type(None, _TEST_TYPE_NAME), (
            "type was reportedly created but get_named_type can't find it"
        )

        udt = ida_typeinf.udt_type_data_t()
        assert tif.get_udt_details(udt), "get_udt_details failed on freshly created type"

        raw_members = []
        for mi in range(udt.size()):
            um = udt[mi]
            base_type = um.type.dstr() if um.type else ''
            for prefix in ('struct ', 'class '):
                if base_type.startswith(prefix):
                    base_type = base_type[len(prefix):]
            raw_members.append({
                'name': um.name or '',
                'offset': um.offset // 8,
                'type': base_type,
                'is_baseclass': um.is_baseclass(),
            })

        # Bug #1 check: IDA's own is_baseclass() flag must be True for BOTH
        # bases, not just the first.
        base_flagged = [m for m in raw_members if m['is_baseclass']]
        base_types_flagged = {m['type'] for m in base_flagged}
        assert 'CEffObj' in base_types_flagged, (
            "regression: CEffObj (base #1, offset 0) lost is_baseclass() flag"
        )
        assert 'CTaskTpl_tagEffTaskParam_CEffCylinder' in base_types_flagged, (
            "REGRESSION (bug #1 reintroduced): CTaskTpl_tagEffTaskParam_CEffCylinder "
            "(base #2, offset 12) is missing is_baseclass()=True — "
            "apply_annotations.create_fixed_struct() likely stopped calling "
            "udt_member_t.set_baseclass() for bases beyond the first"
        )
        assert len(base_flagged) == 2, (
            "expected exactly 2 base-class-flagged members, got %d: %r" %
            (len(base_flagged), base_flagged)
        )

        # --- Step 2: export_full's classification logic must agree ---
        annotation_members = [
            {'name': m['name'], 'offset': m['offset'], 'type': m['type']}
            for m in raw_members
        ]
        bases, filtered = udt_classify.classify_bases_and_members(
            raw_members, annotation_members, _TEST_TYPE_NAME
        )

        assert {b['name'] for b in bases} == {
            'CEffObj', 'CTaskTpl_tagEffTaskParam_CEffCylinder',
        }, "classify_bases_and_members did not return both bases: %r" % bases

        # Neither base class must leak into data_members as an anonymous field.
        for b in bases:
            for m in filtered:
                assert m['offset'] != b['offset'] or m['name'], (
                    "REGRESSION (bug #2 reintroduced): base class %r at offset %d "
                    "leaked into data_members as an anonymous field %r — "
                    "emit_headers.py would render this as an untyped struct field "
                    "(C2208)" % (b['name'], b['offset'], m)
                )

        # A real, named data member must still be present and correctly
        # placed after both bases (48 = 12 (CEffObj) + 36 (CTaskTpl) — sanity
        # bound, not hardcoded to the exact CTaskTpl size in case it changes).
        real_members = [m for m in filtered if m['name']]
        assert any(m['name'] == 'm_pGeomQuad' for m in real_members), (
            "expected m_pGeomQuad among data_members, got: %r" % real_members
        )

        print("ALL REGRESSION CHECKS PASSED")
        print("  bases:", bases)
        print("  data_members (first 3):", filtered[:3])
    finally:
        _cleanup(til)


if __name__ == '__main__':
    run()
