#!/usr/bin/env python3
"""
Layout validation tool for PAL3 annotation structs.

Detects structural issues that could break adjacent member layouts:
1. Type size mismatches between annotation and IDA exported structs
2. Member overlaps (member end > next member offset)
3. Offset out-of-bounds (member offset >= binary_size)
4. Array size inconsistencies (e.g., _BYTE[584] vs tagEffObj[2048])

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


def load_annotations():
    """Load annotation structs from data/annotations/structs/"""
    structs = {}
    structs_dir = ANN_DIR / 'structs'
    if not structs_dir.exists():
        return structs

    for fname in structs_dir.glob('*.json'):
        try:
            with open(fname, 'r', encoding='utf-8') as f:
                sdata = json.load(f)
            sname = sdata.pop('name', fname.stem)
            structs[sname] = sdata
        except Exception as e:
            print(f"WARN: Failed to load {fname}: {e}", file=sys.stderr)

    return structs


def load_ida_structs():
    """Load IDA exported structs from ida_structs.json"""
    if not IDA_STRUCTS_PATH.exists():
        print(f"WARN: IDA structs not found at {IDA_STRUCTS_PATH}", file=sys.stderr)
        return {}

    try:
        with open(IDA_STRUCTS_PATH, 'r', encoding='utf-8') as f:
            return json.load(f)
    except Exception as e:
        print(f"ERROR: Failed to load {IDA_STRUCTS_PATH}: {e}", file=sys.stderr)
        return {}


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

    # Handle pointers
    if '*' in type_str:
        return 4  # 32-bit pointers

    # Handle arrays: extract base type and multipliers
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

    # Check 1: Binary size vs IDA size mismatch
    if binary_size and ida_size and binary_size != ida_size:
        issues.append((
            'ERROR',
            f'binary_size mismatch: annotation={binary_size}, IDA={ida_size}',
            {'annotation_size': binary_size, 'ida_size': ida_size}
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


def format_report(all_issues, verbose=False):
    """Format the audit report"""
    if not all_issues:
        print("\n✅ No layout issues detected.")
        return

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

    print(f"\n{'='*80}")
    if errors:
        print(f"❌ FAILED: {len(errors)} errors detected")
        return 1
    else:
        print(f"⚠️ PASSED with {len(warnings)} warnings")
        return 0


def main():
    parser = argparse.ArgumentParser(description='Audit annotation struct layouts')
    parser.add_argument('--struct', help='Check specific struct only')
    parser.add_argument('--verbose', '-v', action='store_true', help='Verbose output')
    parser.add_argument('--json', action='store_true', help='Output as JSON')
    args = parser.parse_args()

    print("Loading annotations...")
    annotations = load_annotations()
    print(f"  Loaded {len(annotations)} structs")

    print("Loading IDA structs...")
    ida_structs = load_ida_structs()
    print(f"  Loaded {len(ida_structs)} structs")

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

    for sname, sdata in structs_to_check.items():
        issues = audit_struct(sname, sdata, ida_structs, verbose=args.verbose)
        if issues:
            all_issues.extend([(sname, sev, msg, details) for sev, msg, details in issues])

    if args.json:
        # JSON output
        output = {
            'total_issues': len(all_issues),
            'errors': len([i for i in all_issues if i[1] == 'ERROR']),
            'warnings': len([i for i in all_issues if i[1] == 'WARNING']),
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
        return format_report(all_issues, verbose=args.verbose)


if __name__ == '__main__':
    sys.exit(main())
