"""
Extract module/compiland information from PAL3A.PDB (PDB 2.0 JG format).
Searches for .obj file paths and nearby source file paths to determine
the original source file organization of gbengine.dll.
"""
import sys
import struct

def extract_obj_paths(data):
    """Find all .obj file references in the PDB."""
    results = set()
    idx = 0
    while True:
        idx = data.find(b'.obj', idx)
        if idx == -1:
            break
        start = idx
        while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
            start -= 1
        end = idx + 4
        s = data[start:end].decode('ascii', errors='ignore')
        if len(s) > 5 and ('\\' in s or '/' in s or ':' in s):
            results.add(s)
        idx += 1
    return sorted(results)


def extract_cpp_paths(data):
    """Find all .cpp/.c source file references."""
    results = set()
    for ext in [b'.cpp', b'.cxx', b'.c\x00']:
        idx = 0
        while True:
            idx = data.find(ext, idx)
            if idx == -1:
                break
            start = idx
            while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
                start -= 1
            end = idx + len(ext)
            if ext == b'.c\x00':
                end -= 1  # don't include null
            else:
                while end < len(data) and 32 <= data[end] < 127:
                    end += 1
            s = data[start:end].decode('ascii', errors='ignore')
            if len(s) > 4 and ('\\' in s or '/' in s):
                # Filter out strings that are clearly not file paths
                if not s.endswith('.cs') and not s.endswith('.com'):
                    results.add(s)
            idx += 1
    return sorted(results)


def find_gbengine_modules(data):
    """Search specifically for gbEngine9 related paths."""
    results = []
    # Search for gbEngine9 string occurrences
    idx = 0
    while True:
        idx = data.find(b'gbEngine9', idx)
        if idx == -1:
            break
        # Expand to find the full path
        start = idx
        while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
            start -= 1
        end = idx + 9
        while end < len(data) and 32 <= data[end] < 127:
            end += 1
        s = data[start:end].decode('ascii', errors='ignore')
        if len(s) > 10:
            results.append(s)
        idx += 1
    return results


def find_module_info_records(data):
    """
    Try to locate DBI stream module info records.
    In PDB 2.0, module info contains pairs of null-terminated strings:
    - Object file name (e.g., Release\\gbCamera.obj)
    - Source file name (used as module name)
    """
    # Look for patterns where .obj path is followed by .cpp path
    # (typical DBI module info record layout)
    pairs = []
    idx = 0
    while True:
        idx = data.find(b'.obj\x00', idx)
        if idx == -1:
            break
        # Get the obj path
        start = idx
        while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
            start -= 1
        obj_path = data[start:idx+4].decode('ascii', errors='ignore')

        # Look for a source file path nearby (within 260 bytes after the null)
        search_start = idx + 5
        search_end = min(search_start + 520, len(data))
        region = data[search_start:search_end]

        # Find .cpp or .c in the region
        for ext in [b'.cpp', b'.c\x00']:
            pos = region.find(ext)
            if pos != -1:
                src_start = pos
                while src_start > 0 and region[src_start-1] != 0 and 32 <= region[src_start-1] < 127:
                    src_start -= 1
                src_end = pos + (4 if ext == b'.cpp' else 2)
                src_path = region[src_start:src_end].decode('ascii', errors='ignore')
                if len(src_path) > 4 and ('\\' in src_path or '/' in src_path):
                    pairs.append((obj_path, src_path))
                break

        idx += 1
    return pairs


def main():
    pdb_path = 'original/PAL3A.pdb'
    print(f"Reading {pdb_path}...", file=sys.stderr)

    with open(pdb_path, 'rb') as f:
        data = f.read()

    print(f"PDB size: {len(data)} bytes", file=sys.stderr)
    print(f"Header: {data[:40]}", file=sys.stderr)

    # Extract gbEngine9 specific paths
    print("\n=== gbEngine9 paths ===")
    gb_paths = find_gbengine_modules(data)
    for p in sorted(set(gb_paths)):
        print(f"  {p}")
    print(f"\nTotal gbEngine9 references: {len(gb_paths)}", file=sys.stderr)

    # Extract .obj paths
    print("\n=== .obj file paths ===")
    obj_paths = extract_obj_paths(data)
    gb_objs = [p for p in obj_paths if 'gbEngine9' in p or 'gbengine' in p.lower()]
    print(f"  gbEngine9-related .obj files: {len(gb_objs)}")
    for p in gb_objs:
        print(f"    {p}")

    if not gb_objs:
        print("\n  All .obj paths found:")
        for p in obj_paths[:50]:
            print(f"    {p}")
        if len(obj_paths) > 50:
            print(f"    ... ({len(obj_paths)} total)")

    # Extract source file paths
    print("\n=== Source file paths (.cpp/.c) ===")
    src_paths = extract_cpp_paths(data)
    gb_srcs = [p for p in src_paths if 'gbEngine9' in p or 'gbengine' in p.lower()]
    print(f"  gbEngine9-related source files: {len(gb_srcs)}")
    for p in gb_srcs:
        print(f"    {p}")

    if not gb_srcs:
        print("\n  All source paths (first 50):")
        for p in src_paths[:50]:
            print(f"    {p}")
        if len(src_paths) > 50:
            print(f"    ... ({len(src_paths)} total)")

    # Try to find module info pairs
    print("\n=== Module info pairs (obj -> src) ===")
    pairs = find_module_info_records(data)
    gb_pairs = [(o, s) for o, s in pairs if 'gbEngine9' in o or 'gbEngine9' in s or 'gb' in o.lower()]
    print(f"  gbEngine9-related pairs: {len(gb_pairs)}")
    for obj, src in gb_pairs[:100]:
        print(f"    {obj} -> {src}")

    if not gb_pairs:
        print(f"\n  All pairs (first 30):")
        for obj, src in pairs[:30]:
            print(f"    {obj} -> {src}")


if __name__ == "__main__":
    main()
