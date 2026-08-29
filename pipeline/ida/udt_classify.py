"""Pure-logic UDT member classification for PAL3 decompilation pipeline.

Shared between export_full.py (production) and tests/ (TDD, no IDA runtime
required). Extracted so the "is this UDT member a base class?" decision can
be unit-tested without an IDB.

Background: multi-inheritance classes previously lost every base class
beyond the first because export_full.py inferred "is this a base class?"
from `offset == 0` instead of asking IDA's authoritative udm_t.is_baseclass()
flag. See docs/knowledge/gotcha_codegen_multi_inheritance_anon_member.md.
"""


def classify_bases_and_members(udt_members, annotation_members, type_name):
    """Split a UDT's raw member list into (bases, data_members).

    Args:
        udt_members: list of dicts, one per UDT member, each with:
            - name: str (empty string for anonymous members)
            - offset: int (byte offset)
            - type: str (dstr() with 'struct '/'class ' prefix already stripped)
            - is_baseclass: bool (IDA's udm_t.is_baseclass() value — the
              single source of truth; must NOT be re-derived from offset/name)
        annotation_members: the pre-existing {name, type, offset} member dicts
            (i.e. what export_full.py had already built as `members` before
            this function is called) — used to build the filtered data-member
            list in the same shape the rest of the pipeline expects.
        type_name: name of the struct/class being classified, so a
            self-referential base (offset 0, same type name — never valid,
            but seen defensively in some malformed inputs) is excluded.

    Returns:
        (bases, filtered_members) where:
        - bases: list of {'name': str, 'offset': int}, one per base class,
          in UDT member order (i.e. base declaration order == inheritance
          list order, which matters for codegen's `class X : public A, public B`).
        - filtered_members: annotation_members with any entries at a base
          class's offset removed, so a base class is never double-rendered
          as both an inheritance clause AND an anonymous data field.
    """
    bases = []
    for um in udt_members:
        if not um.get('is_baseclass'):
            continue
        base_type = um.get('type', '')
        if base_type and base_type != type_name:
            bases.append({'name': base_type, 'offset': um['offset']})

    base_offsets = {b['offset'] for b in bases}
    filtered = [
        m for m in annotation_members
        if (m.get('name', '') or m.get('offset', 0) not in base_offsets)
        and not any(
            x in m.get('name', '').lower()
            for x in ('baseclass', '__parent', '__vftable', '_vftable', 'vtbl')
        )
    ]
    return bases, filtered
