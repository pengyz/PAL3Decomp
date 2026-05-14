"""
Analyze IDA-named globals in generated source files to find those that fall
inside known annotated global structs.

For example, if g_SceneMgr is at 0x00C04390 with type SceneMgr (size 54116),
then dword_C04394 at 0x00C04394 is actually g_SceneMgr + 0x4 (SceneMgr.m_pSceneRoot).

Usage:
    python tools/analyze_global_overlaps.py
"""

import json
import os
import re
import sys
from pathlib import Path

# Project root
PROJECT_ROOT = Path(__file__).resolve().parent.parent
GLOBALS_JSON = PROJECT_ROOT / "pipeline" / "data" / "annotations" / "globals.json"
STRUCTS_DIR = PROJECT_ROOT / "pipeline" / "data" / "annotations" / "structs"
SRC_DIR = PROJECT_ROOT / "src" / "pal3"

# IDA default name patterns: prefix_HEXADDR
IDA_GLOBAL_RE = re.compile(r'\b(stru|dword|byte|word|off|unk|flt)_([0-9A-Fa-f]{4,8})\b')

# Primitive/simple types that don't occupy a large struct range
PRIMITIVE_TYPES = {
    'int', 'unsigned int', 'long', 'unsigned long',
    'short', 'unsigned short', 'char', 'unsigned char',
    'float', 'double', 'void *', 'HWND', 'HINSTANCE', 'HCURSOR',
    'UINT', 'LPARAM', 'LPCSTR', 'const char *', 'const int',
    'const LPCSTR', 'const CHAR[]', 'const char[]', 'const WCHAR',
}


def is_struct_type(type_str: str) -> bool:
    """Check if a type string represents a struct (not a primitive or small array)."""
    # Strip const
    t = type_str.strip()
    if t.startswith('const '):
        t = t[6:].strip()

    # Pointers are not struct instances (they're just 4 bytes)
    if t.endswith('*'):
        return False

    # Check against known primitives
    if t in PRIMITIVE_TYPES:
        return False

    # Small char/int arrays (like char[3], char[4], CHAR[8]) - skip if small
    array_match = re.match(r'(char|CHAR|unsigned char|int|float)\[(\d+)\]', t)
    if array_match:
        count = int(array_match.group(2))
        # Only consider large arrays as "struct-like" (> 32 bytes)
        elem_size = 4 if array_match.group(1) in ('int', 'float') else 1
        if count * elem_size <= 32:
            return False

    # void *[N] arrays
    if re.match(r'void \*\[\d+\]', t):
        return False

    return True


def get_struct_size(type_str: str) -> int | None:
    """Get the size of a struct type from its annotation file."""
    # Extract base type name (strip array suffix, const, etc.)
    t = type_str.strip()
    if t.startswith('const '):
        t = t[6:].strip()

    # Handle array types like "char[256]" or "ScriptCounter[10]"
    array_match = re.match(r'(.+?)\[(\d+)\]$', t)
    array_count = 1
    if array_match:
        t = array_match.group(1).strip()
        array_count = int(array_match.group(2))

    # For primitive arrays, compute size directly
    primitive_sizes = {
        'char': 1, 'CHAR': 1, 'unsigned char': 1,
        'short': 2, 'unsigned short': 2,
        'int': 4, 'unsigned int': 4, 'long': 4, 'unsigned long': 4,
        'float': 4, 'double': 8,
    }
    if t in primitive_sizes:
        return primitive_sizes[t] * array_count

    # Look up struct file
    struct_file = STRUCTS_DIR / f"{t}.json"
    if not struct_file.exists():
        return None

    try:
        with open(struct_file, 'r', encoding='utf-8') as f:
            struct_data = json.load(f)
    except (json.JSONDecodeError, UnicodeDecodeError):
        return None

    # Try gen_size, binary_size, pdb_size (in order of preference)
    size = struct_data.get('gen_size') or struct_data.get('binary_size')
    if size and size > 1:  # pdb_size=1 is a placeholder
        return size * array_count

    pdb_size = struct_data.get('pdb_size')
    if pdb_size and pdb_size > 1:
        return pdb_size * array_count

    # Fallback: estimate from highest known_member offset
    members = struct_data.get('known_members', {})
    if members:
        max_offset = max(int(k) for k in members.keys())
        # Rough estimate: highest offset + 16 (conservative)
        estimated = max_offset + 16
        return estimated * array_count

    return None


def get_member_at_offset(type_str: str, offset: int) -> str | None:
    """Try to find the member name at a given offset within a struct."""
    t = type_str.strip()
    if t.startswith('const '):
        t = t[6:].strip()

    # Handle array types
    array_match = re.match(r'(.+?)\[(\d+)\]$', t)
    elem_size = None
    if array_match:
        base_type = array_match.group(1).strip()
        array_count = int(array_match.group(2))
        # Get element size
        struct_file = STRUCTS_DIR / f"{base_type}.json"
        if struct_file.exists():
            try:
                with open(struct_file, 'r', encoding='utf-8') as f:
                    struct_data = json.load(f)
                elem_size = struct_data.get('gen_size') or struct_data.get('binary_size')
            except (json.JSONDecodeError, UnicodeDecodeError):
                pass
        if elem_size:
            elem_index = offset // elem_size
            elem_offset = offset % elem_size
            member = _lookup_member(base_type, elem_offset)
            if member:
                return f"[{elem_index}].{member}"
            return f"[{elem_index}]+0x{elem_offset:X}"
        t = base_type
    else:
        t = t

    member = _lookup_member(t, offset)
    return member


def _lookup_member(type_name: str, offset: int) -> str | None:
    """Look up a member at a specific offset in a struct."""
    struct_file = STRUCTS_DIR / f"{type_name}.json"
    if not struct_file.exists():
        return None

    try:
        with open(struct_file, 'r', encoding='utf-8') as f:
            struct_data = json.load(f)
    except (json.JSONDecodeError, UnicodeDecodeError):
        return None

    members = struct_data.get('known_members', {})

    # Exact match
    if str(offset) in members:
        return members[str(offset)].get('name', f'offset_0x{offset:X}')

    # Find closest member before this offset
    offsets = sorted(int(k) for k in members.keys())
    prev_offset = None
    for o in offsets:
        if o <= offset:
            prev_offset = o
        else:
            break

    if prev_offset is not None:
        member_info = members[str(prev_offset)]
        member_name = member_info.get('name', f'offset_0x{prev_offset:X}')
        sub_offset = offset - prev_offset
        if sub_offset == 0:
            return member_name
        return f"{member_name}+0x{sub_offset:X}"

    return None


def scan_source_files() -> dict[str, set[str]]:
    """Scan source files for IDA-named globals, return {file: set of global names}."""
    ida_globals = {}  # name -> set of files it appears in
    all_names = set()

    for root, dirs, files in os.walk(SRC_DIR):
        for fname in files:
            if not fname.endswith('.cpp') and not fname.endswith('.h'):
                continue
            fpath = os.path.join(root, fname)
            try:
                with open(fpath, 'r', encoding='utf-8') as f:
                    content = f.read()
            except UnicodeDecodeError:
                try:
                    with open(fpath, 'r', encoding='gbk') as f:
                        content = f.read()
                except:
                    continue

            matches = IDA_GLOBAL_RE.findall(content)
            for prefix, hex_addr in matches:
                name = f"{prefix}_{hex_addr}"
                all_names.add(name)

    return all_names


def main():
    # 1. Load annotated globals
    with open(GLOBALS_JSON, 'r', encoding='utf-8') as f:
        globals_data = json.load(f)

    # 2. Build address ranges for struct-type globals
    struct_ranges = []  # (start_addr, end_addr, name, type_str, size)

    for addr_str, info in globals_data.items():
        addr = int(addr_str, 16)
        type_str = info['type']
        name = info['name']

        if not is_struct_type(type_str):
            continue

        size = get_struct_size(type_str)
        if size is None or size <= 4:
            continue

        struct_ranges.append((addr, addr + size, name, type_str, size))

    # Sort by address
    struct_ranges.sort(key=lambda x: x[0])

    print(f"=== Global Struct Overlap Analysis ===")
    print(f"")
    print(f"Annotated globals total: {len(globals_data)}")
    print(f"Struct-type globals with known sizes: {len(struct_ranges)}")
    print(f"")

    # Print the struct ranges we found
    print(f"--- Known Global Struct Ranges ---")
    for start, end, name, type_str, size in struct_ranges:
        print(f"  0x{start:08X} - 0x{end:08X}  {name} ({type_str}, {size} bytes)")
    print(f"")

    # 3. Scan source files for IDA-named globals
    ida_globals = scan_source_files()
    print(f"Total unique IDA-named globals in source: {len(ida_globals)}")
    print(f"")

    # 4. Check which IDA globals fall within struct ranges
    overlaps = []  # (ida_name, ida_addr, parent_name, parent_type, offset)

    for ida_name in ida_globals:
        match = IDA_GLOBAL_RE.match(ida_name)
        if not match:
            continue
        prefix, hex_addr = match.groups()
        ida_addr = int(hex_addr, 16)

        # Binary search would be optimal, but linear is fine for ~400 ranges
        for start, end, parent_name, parent_type, size in struct_ranges:
            if start < ida_addr < end:  # Strict < on start (exclude exact match = same global)
                offset = ida_addr - start
                overlaps.append((ida_name, ida_addr, parent_name, parent_type, offset, start))
                break

    # Sort overlaps by parent global, then offset
    overlaps.sort(key=lambda x: (x[5], x[4]))

    print(f"IDA globals overlapping with known struct globals: {len(overlaps)}")
    print(f"")

    # 5. Report top examples
    print(f"--- Top Overlapping Globals (sorted by parent) ---")
    print(f"")

    # Group by parent
    by_parent = {}
    for ida_name, ida_addr, parent_name, parent_type, offset, parent_addr in overlaps:
        if parent_name not in by_parent:
            by_parent[parent_name] = []
        by_parent[parent_name].append((ida_name, ida_addr, offset))

    # Print all parents with their overlaps
    for parent_name in sorted(by_parent.keys(), key=lambda k: len(by_parent[k]), reverse=True):
        items = by_parent[parent_name]
        parent_info = None
        for start, end, name, type_str, size in struct_ranges:
            if name == parent_name:
                parent_info = (start, type_str, size)
                break

        if parent_info is None:
            continue

        parent_addr, parent_type, parent_size = parent_info
        print(f"  {parent_name} @ 0x{parent_addr:08X} ({parent_type}, {parent_size} bytes) -- {len(items)} overlaps:")

        for ida_name, ida_addr, offset in sorted(items, key=lambda x: x[2]):
            member = get_member_at_offset(parent_type, offset)
            member_str = f" ({parent_type}.{member})" if member else ""
            print(f"    {ida_name} => {parent_name} + 0x{offset:X}{member_str}")

        print()

    # Top 20 examples (flat list for quick reference)
    print(f"--- Top 20 Examples (flat) ---")
    print(f"")
    # Sort by parent size descending (larger structs are more interesting)
    all_overlaps_sorted = sorted(overlaps, key=lambda x: (-get_struct_size(
        next((t for s, e, n, t, sz in struct_ranges if n == x[2]), '')) or 0, x[4]))
    for i, (ida_name, ida_addr, parent_name, parent_type, offset, parent_addr) in enumerate(all_overlaps_sorted[:20]):
        member = get_member_at_offset(parent_type, offset)
        member_str = f" ({parent_type}.{member})" if member else ""
        print(f"  {ida_name} => {parent_name} + 0x{offset:X}{member_str}")
    print()

    # Summary
    print(f"")
    print(f"=== Summary ===")
    print(f"Total IDA-named globals in source:          {len(ida_globals)}")
    print(f"Overlapping with known global structs:      {len(overlaps)}")
    print(f"Percentage:                                 {100*len(overlaps)/max(len(ida_globals),1):.1f}%")
    print(f"Distinct parent globals affected:           {len(by_parent)}")
    print(f"")
    print(f"These IDA globals are likely member accesses of the parent struct")
    print(f"and could be replaced with proper member access expressions.")


if __name__ == '__main__':
    main()
