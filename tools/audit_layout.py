#!/usr/bin/env python3
"""
Layout validation tool for PAL3 annotation structs.

Detects structural issues that could break adjacent member layouts:
1. Size equality between annotation and IDA exported structs -- NOTE: this is a
   SAME-SOURCE comparison and carries NO information about whether the declared
   size is correct (see "NON-DISCRIMINATING CHECKS" below)
1b. Declared-size geometry (annotation-side, IDB-independent): a binary_size much
   larger than the largest declared member end is reported as a review signal
2. Member overlaps (member end > next member offset)
3. Offset out-of-bounds (member offset >= binary_size)
4. Array size inconsistencies (e.g., _BYTE[584] vs tagEffObj[2048])

NON-DISCRIMINATING CHECKS (why check 1 cannot be used as evidence)
------------------------------------------------------------------
`asm/pal3/ida_structs.json` is exported from the IDB, and the IDB UDTs were
written by `pipeline/ida/apply_annotations.py` from these very annotation files.
annotation -> apply -> IDB -> export is a single data path, so
`binary_size == ida_size` holds by construction (measured on this tree:
818/881 structs compared, 818 equal, 0 mismatch). A PASS therefore proves
nothing about size correctness. It is still reported, because a MISMATCH is
meaningful (stale IDB / a size `apply` could not express) -- and the fact that
it is same-source is printed in the report.
See `docs/specs/2026-09-15-cleanup-scan-architecture-rulings.md` ruling (b).

Exit codes:
    0  audit ran, no ERROR-level issues (warnings may exist)
    1  audit ran, ERROR-level layout issues found
    2  audit COULD NOT RUN: a prerequisite artifact is missing/unreadable
       (this is NOT a pass -- it used to be reported as WARN + exit 0)

Usage:
    python tools/audit_layout.py [--verbose] [--struct NAME]

Example:
    # Check all structs
    python tools/audit_layout.py

    # Check specific struct
    python tools/audit_layout.py --struct CEffMgr

    # Verbose output with details
    python tools/audit_layout.py --verbose
"""

import argparse
import json
import os
import re
import sys
from pathlib import Path

# Project root
PROJECT_ROOT = Path(__file__).parent.parent
ANN_DIR = PROJECT_ROOT / 'data' / 'annotations'
IDA_STRUCTS_PATH = PROJECT_ROOT / 'asm' / 'pal3' / 'ida_structs.json'

# Review thresholds for the IDB-independent declared-size geometry signal.
# Basis: docs/specs/2026-09-15-cleanup-scan-architecture-rulings.md ruling (b)
# uses exactly 3x / 50x on `binary_size vs max member offset`.
GEOMETRY_WARN_RATIO = 3.0
GEOMETRY_HIGH_RATIO = 50.0


class PrerequisiteError(Exception):
    """A required input artifact is missing or unreadable -> the audit cannot run."""


def load_annotations():
    """Load annotation structs from data/annotations/structs/

    Returns (structs, load_failures). A missing directory or an unparsable
    struct file is NOT silently skipped: the caller must not be able to print
    "no issues" after auditing only part of the tree.
    """
    structs = {}
    load_failures = []
    structs_dir = ANN_DIR / 'structs'
    if not structs_dir.exists():
        raise PrerequisiteError(
            "annotation structs directory not found: %s\n"
            "  This directory is tracked by git; a missing directory means the\n"
            "  working tree is incomplete." % structs_dir)

    for fname in sorted(structs_dir.glob('*.json')):
        try:
            with open(fname, 'r', encoding='utf-8') as f:
                sdata = json.load(f)
            sname = sdata.pop('name', fname.stem)
            structs[sname] = sdata
        except Exception as e:
            load_failures.append((str(fname), str(e)))

    return structs, load_failures


def load_ida_structs():
    """Load IDA exported structs from ida_structs.json.

    Missing / unreadable file raises PrerequisiteError: returning {} here used
    to feed an empty cross-check table into the audit, which silently disabled
    check 1 and check 2d and still exited 0 (false pass).
    """
    if not IDA_STRUCTS_PATH.exists():
        raise PrerequisiteError(
            "IDA structs export not found: %s\n"
            "  This is a PREREQUISITE ARTIFACT (asm/ is gitignored): regenerate it with\n"
            "      python pipeline/cli.py export\n"
            "  Without it the annotation<->IDB cross-checks cannot run at all, so this\n"
            "  tool refuses to report success." % IDA_STRUCTS_PATH)

    try:
        with open(IDA_STRUCTS_PATH, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except Exception as e:
        raise PrerequisiteError(
            "IDA structs export is unreadable: %s\n  %s\n"
            "  Regenerate it with: python pipeline/cli.py export" % (IDA_STRUCTS_PATH, e))

    if not data:
        raise PrerequisiteError(
            "IDA structs export is EMPTY: %s\n"
            "  Regenerate it with: python pipeline/cli.py export" % IDA_STRUCTS_PATH)
    return data


def estimate_type_size(type_str, all_structs):
    """
    Estimate the size of a type based on its string representation.
    Returns size in bytes, or 0 if unknown.
    """
    if not type_str:
        return 0

    # Handle inline union/struct (dict type) - MUST be first
    if isinstance(type_str, dict):
        # For inline types, estimate max extent
        members = type_str.get('union') or type_str.get('struct') or []
        max_end = 0
        for m in members:
            m_off = m.get('offset', 0)
            m_size = estimate_type_size(m.get('type', 'int'), all_structs)
            end = m_off + m_size
            if end > max_end:
                max_end = end
        return max_end

    # Now type_str should be a string
    if not isinstance(type_str, str):
        return 0

    # Handle arrays: extract base type and multipliers.
    # NOTE: arrays are resolved BEFORE the bare-pointer shortcut, otherwise
    # `char *[4]` / `gbPrintFont *[5]` are reported as a single 4-byte pointer
    # (measured: gbPrintFontMgr binary_size=20 is exactly 5*4, but the old
    # order made it look 5x oversized).
    array_match = re.findall(r'\[(\d+)\]', type_str)
    if array_match:
        base_type = re.sub(r'\[\d+\]', '', type_str).strip()
        base_size = estimate_type_size(base_type, all_structs)
        if base_size > 0:
            total = base_size
            for m in array_match:
                total *= int(m)
            return total
        return 0

    # Handle pointers
    if '*' in type_str:
        return 4  # 32-bit pointers

    # Basic types
    basic_types = {
        'char': 1, 'unsigned char': 1, 'BYTE': 1, '_BYTE': 1, 'bool': 1,
        'short': 2, 'unsigned short': 2, 'WORD': 2, '_WORD': 2,
        'int': 4, 'unsigned int': 4, 'long': 4, 'unsigned long': 4,
        'DWORD': 4, '_DWORD': 4, 'float': 4, 'BOOL': 4,
        'double': 8, '__int64': 8, 'LONGLONG': 8,
        'HRESULT': 4, 'HWND': 4, 'HANDLE': 4, 'UINT': 4, 'LONG': 4,
        'void *': 4, 'char *': 4,
    }

    # Clean type string
    clean_type = type_str.strip().replace('struct ', '').replace('class ', '').replace('const ', '')

    # Check basic types
    if clean_type in basic_types:
        return basic_types[clean_type]

    # Check pointer to type
    if clean_type.endswith('*'):
        return 4

    # Check array of type
    if '[' in clean_type:
        # Already handled above
        return 0

    # Check if it's a known struct
    if clean_type in all_structs:
        struct_info = all_structs[clean_type]
        return struct_info.get('binary_size', 0) or struct_info.get('pdb_size', 0) or 0

    # Check IDA structs
    # (Will be called separately with IDA structs loaded)

    return 0


def parse_offset(offset_str):
    """Parse offset string (decimal or hex) to integer"""
    try:
        if isinstance(offset_str, str):
            # Handle union variants like "12_1" - take base offset before underscore
            base = offset_str.split('_')[0]
            return int(base, 0)  # Auto-detect base (0x for hex)
        return int(offset_str)
    except (ValueError, TypeError):
        return None


def get_member_size(member, all_structs):
    """Get the size of a member, handling inline types and arrays"""
    mtype = member.get('type', 'int')
    return estimate_type_size(mtype, all_structs)


def audit_struct(sname, sdata, ida_structs, verbose=False):
    """
    Audit a single struct for layout issues.
    Returns list of issues: [(severity, message, details)]
    """
    issues = []

    # Get struct metadata
    binary_size = sdata.get('binary_size', 0) or sdata.get('pdb_size', 0)
    members = sdata.get('known_members', {})
    is_union = sdata.get('is_union', False)

    # Get IDA struct for comparison
    ida_struct = ida_structs.get(sname, {})
    ida_size = ida_struct.get('size', 0)
    ida_members = {m['offset']: m for m in ida_struct.get('data_members', [])}

    # Sort members by offset
    sorted_members = []
    for off_str, mdata in members.items():
        off = parse_offset(off_str)
        if off is not None:
            sorted_members.append((off, off_str, mdata))

    sorted_members.sort(key=lambda x: x[0])

    # Group by offset to detect union variants (multiple members at same offset)
    offset_groups = {}
    for off, off_str, mdata in sorted_members:
        offset_groups.setdefault(off, []).append((off_str, mdata))

    # Check 1: Binary size vs IDA size mismatch.
    # NON-DISCRIMINATING BY CONSTRUCTION: ida_size comes from an export of the
    # IDB, and the IDB UDT was written from this same annotation by
    # apply_annotations.py. A match is therefore expected and proves nothing;
    # only a MISMATCH is informative (stale IDB / size apply could not express).
    if binary_size and ida_size:
        if binary_size != ida_size:
            issues.append((
                'ERROR',
                f'binary_size mismatch: annotation={binary_size}, IDA={ida_size} '
                f'(same-source check: a mismatch means the IDB is STALE - annotations '
                f'were edited after the last apply/export)',
                {'annotation_size': binary_size, 'ida_size': ida_size,
                 'discriminating': True, 'interpretation': 'stale_idb_or_unexpressible_size'}
            ))

    # Check 2: Member-by-member validation
    for i, (off, off_str, mdata) in enumerate(sorted_members):
        mname = mdata.get('name', f'_unknown_{off}')
        mtype = mdata.get('type', 'int')
        source = mdata.get('source', '')

        # Skip padding/gap members
        if mname.startswith('_pad_') or mname.startswith('_gap_'):
            continue

        # Get member size
        msize = get_member_size(mdata, ida_structs)
        mend = off + msize

        # Check 2a: Offset out-of-bounds
        if binary_size and off >= binary_size:
            issues.append((
                'ERROR',
                f'Member {mname} at offset {off} >= binary_size {binary_size}',
                {'member': mname, 'offset': off, 'binary_size': binary_size}
            ))

        # Check 2b: Member end exceeds binary_size
        if binary_size and mend > binary_size:
            issues.append((
                'ERROR',
                f'Member {mname} ends at {mend} > binary_size {binary_size} (type={mtype}, size={msize})',
                {'member': mname, 'offset': off, 'end': mend, 'binary_size': binary_size, 'type': mtype, 'size': msize}
            ))

        # Check 2c: Overlap with next member
        # Skip if this offset has multiple members (union variants)
        if len(offset_groups.get(off, [])) <= 1:
            if i < len(sorted_members) - 1:
                next_off, next_off_str, next_mdata = sorted_members[i + 1]
                next_mname = next_mdata.get('name', f'_unknown_{next_off}')

                # Skip if next is padding/gap
                if not next_mname.startswith('_pad_') and not next_mname.startswith('_gap_'):
                    # Skip if next offset has multiple members (union variants)
                    if len(offset_groups.get(next_off, [])) <= 1:
                        # Skip if either member has "overlap" in source (intentional)
                        source1 = mdata.get('source', '')
                        source2 = next_mdata.get('source', '')
                        if 'overlap' in source1.lower() or 'overlap' in source2.lower():
                            continue

                        if mend > next_off:
                            issues.append((
                                'ERROR',
                                f'Member overlap: {mname}({mtype}, size={msize})@{off} ends@{mend} > next {next_mname}@{next_off}',
                                {
                                    'member1': mname, 'offset1': off, 'end1': mend,
                                    'member2': next_mname, 'offset2': next_off,
                                    'type1': mtype, 'size1': msize
                                }
                            ))

        # Check 2d: Type size mismatch with IDA
        if off in ida_members:
            ida_m = ida_members[off]
            ida_mtype = ida_m.get('type', '')

            # Compare sizes if both are known
            ida_msize = estimate_type_size(ida_mtype, ida_structs)
            if msize and ida_msize and msize != ida_msize:
                # Special case: pointer types can differ in syntax but same size
                if not (('*' in str(mtype) and '*' in str(ida_mtype)) or
                        ('*' in str(mtype) and 'char *' in str(ida_mtype)) or
                        ('char *' in str(mtype) and '*' in str(ida_mtype))):
                    issues.append((
                        'WARNING',
                        f'Type size mismatch at +{off}: annotation={mtype}({msize}b) vs IDA={ida_mtype}({ida_msize}b)',
                        {
                            'offset': off,
                            'ann_type': mtype, 'ann_size': msize,
                            'ida_type': ida_mtype, 'ida_size': ida_msize
                        }
                    ))

    # Check 3: Array size validation
    for off_str, mdata in members.items():
        mtype = mdata.get('type', '')
        mname = mdata.get('name', '')
        off = parse_offset(off_str)
        if off is None:
            continue

        # Check for array types
        if isinstance(mtype, str) and '[' in mtype:
            # Extract array info
            match = re.match(r'(.+?)\[(\d+)\]', mtype)
            if match:
                base_type = match.group(1).strip()
                array_size = int(match.group(2))
                base_size = estimate_type_size(base_type, ida_structs)

                if base_size > 0:
                    total_size = base_size * array_size
                    mend = off + total_size

                    # Check if this array overlaps with next member
                    # Skip if this offset has multiple members (union variants)
                    if len(offset_groups.get(off, [])) <= 1:
                        for next_off_str, next_mdata in members.items():
                            next_off = parse_offset(next_off_str)
                            if next_off is not None and next_off > off and next_off < mend:
                                next_mname = next_mdata.get('name', f'_unknown_{next_off}')
                                if not next_mname.startswith('_pad_') and not next_mname.startswith('_gap_'):
                                    # Skip if next offset has multiple members (union variants)
                                    if len(offset_groups.get(next_off, [])) <= 1:
                                        # Skip if either member has "overlap" in source (intentional)
                                        source1 = mdata.get('source', '')
                                        source2 = next_mdata.get('source', '')
                                        if 'overlap' in source1.lower() or 'overlap' in source2.lower():
                                            continue

                                        issues.append((
                                            'ERROR',
                                            f'Array {mname}({mtype}={total_size}b) at +{off} overlaps {next_mname}@{next_off}',
                                            {
                                                'array': mname, 'array_type': mtype, 'array_size': total_size,
                                                'overlapped': next_mname, 'overlapped_offset': next_off
                                            }
                                        ))

    # Check 4: Specific known issues
    # CEffMgr.m_EffTable: was incorrectly changed from _BYTE[584] to tagEffObj[2048]
    if sname == 'CEffMgr' and '2332' in members:
        eff_table = members['2332']
        eff_type = eff_table.get('type', '')
        if 'tagEffObj[2048]' in str(eff_type):
            issues.append((
                'ERROR',
                'CEffMgr.m_EffTable type tagEffObj[2048] is WRONG: should be _BYTE[584]',
                {
                    'member': 'm_EffTable',
                    'current_type': eff_type,
                    'expected_type': '_BYTE[584]',
                    'reason': 'tagEffObj[2048] = 40960b, would overlap m_nEff at +43292'
                }
            ))

    return issues


def size_check_scope(sname, sdata, ida_structs):
    """Classify the (annotation binary_size, IDA size) pair for coverage stats.

    Returns 'match' | 'mismatch' | None. Used only to report how many structs
    the same-source size comparison could look at; see the module docstring for
    why 'match' is not evidence.
    """
    binary_size = sdata.get('binary_size', 0) or sdata.get('pdb_size', 0)
    ida_size = (ida_structs.get(sname, {}) or {}).get('size', 0)
    if not binary_size or not ida_size:
        return None
    return 'match' if binary_size == ida_size else 'mismatch'


def declared_size_geometry(sname, sdata, all_structs):
    """IDB-independent geometry: binary_size vs largest DECLARED member end.

    Returns dict or None. This is a review signal only -- per ruling (b) a
    declared size with no real source is a suspected defect family, but a large
    ratio is not proof of a defect (a genuinely sparse struct with a big
    unannotated tail looks the same).

    Members whose size cannot be resolved (containers / unknown aliases) count
    as 1 byte so the measured end stays a LOWER BOUND -- the check must not fire
    just because the estimator is weak. A struct where NO member size could be
    resolved is skipped entirely (it would be estimator noise, not evidence).

    KNOWN BLIND SPOT (do not overstate this signal): a size that is inflated
    consistently with a nested by-value member is invisible here, because that
    member's (possibly inflated) size is added into max_member_end. Measured
    example: gbVFileSystem binary_size=917972 = 24 + sizeof(CPK=917948) ->
    ratio 1.0, never flagged. Catching that needs an independent size source.
    """
    bs = sdata.get('binary_size', 0) or sdata.get('pdb_size', 0)
    if not bs:
        return None
    members = sdata.get('known_members', {})
    max_end = 0
    resolved_members = 0
    for off_str, m in members.items():
        off = parse_offset(off_str)
        if off is None:
            continue
        msize = get_member_size(m, all_structs)
        if msize <= 0:
            # Unknown size (container type, unknown alias, ...): a member
            # DECLARED at `off` still proves the struct extends beyond `off`,
            # so use 1 byte as a conservative lower bound. Skipping such
            # members entirely would overstate the ratio (false positives:
            # `primitive` has a member at +72 -> 76 bytes is fine).
            msize = 1
        else:
            resolved_members += 1
        if off + msize > max_end:
            max_end = off + msize
    if max_end <= 0 or resolved_members == 0:
        # No member size could be resolved at all (e.g. Reoccupy = a single
        # std::vector member): the measured end is only "offset+1", which says
        # nothing. Refuse to emit a ratio instead of reporting estimator noise.
        return None
    return {'struct': sname, 'binary_size': bs, 'max_member_end': max_end,
            'ratio': round(bs / max_end, 1)}


def format_report(all_issues, verbose=False, size_scope=None, geometry=None):
    """Format the audit report

    size_scope: dict(match=, mismatch=, not_compared=) same-source size check coverage
    geometry: list of declared_size_geometry() dicts for oversized structs
    """
    size_scope = size_scope or {}
    geometry = geometry or []

    if not all_issues and not geometry:
        print("\n✅ No layout issues detected.")
        _print_evidence_limits(size_scope)
        return 0

    # Group by severity
    errors = [(sname, sev, msg, details) for sname, sev, msg, details in all_issues if sev == 'ERROR']
    warnings = [(sname, sev, msg, details) for sname, sev, msg, details in all_issues if sev == 'WARNING']

    print(f"\n{'='*80}")
    print(f"LAYOUT AUDIT REPORT")
    print(f"{'='*80}")
    print(f"Total issues: {len(all_issues)} ({len(errors)} errors, {len(warnings)} warnings)")

    if errors:
        print(f"\n{'─'*80}")
        print("ERRORS:")
        print(f"{'─'*80}")
        for sname, sev, msg, details in errors:
            print(f"  [{sname}] {msg}")
            if verbose:
                print(f"    Details: {json.dumps(details, indent=4)}")

    if warnings:
        print(f"\n{'─'*80}")
        print("WARNINGS:")
        print(f"{'─'*80}")
        for sname, sev, msg, details in warnings:
            print(f"  [{sname}] {msg}")
            if verbose:
                print(f"    Details: {json.dumps(details, indent=4)}")

    if geometry:
        over_warn = [g for g in geometry if g['ratio'] > GEOMETRY_WARN_RATIO]
        over_high = [g for g in geometry if g['ratio'] > GEOMETRY_HIGH_RATIO]
        print(f"\n{'─'*80}")
        print("IDB-INDEPENDENT SIZE GEOMETRY (review signal, not proof):")
        print(f"{'─'*80}")
        print(f"  binary_size > {GEOMETRY_WARN_RATIO:g}x largest declared member end: "
              f"{len(over_warn)} structs  (> {GEOMETRY_HIGH_RATIO:g}x: {len(over_high)})")
        for g in sorted(geometry, key=lambda x: -x['ratio'])[:20]:
            mark = 'HIGH' if g['ratio'] > GEOMETRY_HIGH_RATIO else 'warn'
            print(f"  [{mark}] {g['struct']}: binary_size={g['binary_size']} "
                  f"max_member_end={g['max_member_end']} ratio={g['ratio']}x")

    _print_evidence_limits(size_scope)

    print(f"\n{'='*80}")
    if errors:
        print(f"❌ FAILED: {len(errors)} errors detected")
        return 1
    else:
        print(f"⚠️ PASSED with {len(warnings)} warnings")
        return 0


def _print_evidence_limits(size_scope):
    """Print what these checks can and cannot establish (honesty section)."""
    if not size_scope:
        return
    print(f"\n{'─'*80}")
    print("NON-DISCRIMINATING CHECK (reported, never used as evidence):")
    print(f"{'─'*80}")
    print(f"  check 1 binary_size vs IDA size: compared={size_scope.get('compared', 0)} "
          f"match={size_scope.get('match', 0)} mismatch={size_scope.get('mismatch', 0)} "
          f"not_compared={size_scope.get('not_compared', 0)}")
    print("  Reason: the IDA export is produced from the IDB, and the IDB UDTs were written")
    print("  from these same annotations by pipeline/ida/apply_annotations.py")
    print("  (annotation -> apply -> IDB -> export is ONE data path). Equality is therefore")
    print("  expected by construction: a match says NOTHING about size correctness.")
    print("  A mismatch is still meaningful (stale IDB / size apply could not express).")
    print("  Sizes must be validated against an IDB-independent source (instruction-level")
    print("  reg+disp32 access bound, allocation point) -- see architecture ruling (b).")


def main():
    parser = argparse.ArgumentParser(description='Audit annotation struct layouts')
    parser.add_argument('--struct', help='Check specific struct only')
    parser.add_argument('--verbose', '-v', action='store_true', help='Verbose output')
    parser.add_argument('--json', action='store_true', help='Output as JSON')
    args = parser.parse_args()

    print("Loading annotations...")
    try:
        annotations, load_failures = load_annotations()
    except PrerequisiteError as e:
        return _prerequisite_failure(e)
    print(f"  Loaded {len(annotations)} structs")

    print("Loading IDA structs...")
    try:
        ida_structs = load_ida_structs()
    except PrerequisiteError as e:
        return _prerequisite_failure(e)
    print(f"  Loaded {len(ida_structs)} structs")

    if load_failures:
        print(f"\n[FATAL] {len(load_failures)} annotation struct file(s) could not be parsed:",
              file=sys.stderr)
        for path, err in load_failures[:20]:
            print(f"  {path}: {err}", file=sys.stderr)
        print("  The audit would silently cover less than the full tree -> refusing to report",
              file=sys.stderr)
        print("  a result. Fix or restore the listed files and re-run.", file=sys.stderr)
        return 2

    # Filter to specific struct if requested
    if args.struct:
        if args.struct not in annotations:
            print(f"ERROR: Struct '{args.struct}' not found in annotations")
            return 1
        structs_to_check = {args.struct: annotations[args.struct]}
    else:
        structs_to_check = annotations

    print(f"\nAuditing {len(structs_to_check)} structs...")
    all_issues = []
    size_scope = {'compared': 0, 'match': 0, 'mismatch': 0, 'not_compared': 0}
    geometry = []

    for sname, sdata in structs_to_check.items():
        issues = audit_struct(sname, sdata, ida_structs, verbose=args.verbose)
        if issues:
            all_issues.extend([(sname, sev, msg, details) for sev, msg, details in issues])

        verdict = size_check_scope(sname, sdata, ida_structs)
        if verdict is None:
            size_scope['not_compared'] += 1
        else:
            size_scope['compared'] += 1
            size_scope[verdict] += 1

        geo = declared_size_geometry(sname, sdata, annotations)
        if geo and geo['ratio'] > GEOMETRY_WARN_RATIO:
            geometry.append(geo)
            all_issues.append((sname, 'WARNING',
                               f"declared binary_size={geo['binary_size']} is {geo['ratio']}x the "
                               f"largest declared member end ({geo['max_member_end']}); no size "
                               f"source recorded -- review, do NOT auto-shrink to max member end",
                               dict(geo, check='declared_size_geometry',
                                    discriminating='partial (IDB-independent internal geometry, '
                                                   'blind to nested by-value inflation)')))

    print(f"  IDA cross-check coverage: {size_scope['compared']}/{len(structs_to_check)} structs "
          f"have an IDA entry with a size "
          f"(match={size_scope['match']}, mismatch={size_scope['mismatch']}, "
          f"not_compared={size_scope['not_compared']})")
    print(f"  Declared-size geometry: {len(geometry)} struct(s) above "
          f"{GEOMETRY_WARN_RATIO:g}x")

    if args.json:
        # JSON output
        output = {
            'total_issues': len(all_issues),
            'errors': len([i for i in all_issues if i[1] == 'ERROR']),
            'warnings': len([i for i in all_issues if i[1] == 'WARNING']),
            'non_discriminating': {
                'check': 'binary_size vs ida_size',
                'reason': 'same-source: annotation -> apply -> IDB -> export is one data path',
                'compared': size_scope['compared'],
                'match': size_scope['match'],
                'mismatch': size_scope['mismatch'],
                'not_compared': size_scope['not_compared'],
            },
            'declared_size_geometry': {
                'threshold_ratio': GEOMETRY_WARN_RATIO,
                'high_ratio': GEOMETRY_HIGH_RATIO,
                'count': len(geometry),
                'structs': sorted(geometry, key=lambda x: -x['ratio']),
            },
            'issues': [
                {
                    'struct': sname,
                    'severity': sev,
                    'message': msg,
                    'details': details
                }
                for sname, sev, msg, details in all_issues
            ]
        }
        print(json.dumps(output, indent=2))
        return 0 if output['errors'] == 0 else 1
    else:
        return format_report(all_issues, verbose=args.verbose,
                             size_scope=size_scope, geometry=geometry)


def _prerequisite_failure(err):
    """Loud, actionable failure for a missing/unreadable prerequisite artifact."""
    print("=" * 78, file=sys.stderr)
    print("AUDIT CANNOT RUN - prerequisite artifact missing or unreadable", file=sys.stderr)
    print("=" * 78, file=sys.stderr)
    print(str(err), file=sys.stderr)
    print("=" * 78, file=sys.stderr)
    print("This is NOT a pass: the checks that need this artifact were not run.",
          file=sys.stderr)
    return 2


if __name__ == '__main__':
    sys.exit(main())
