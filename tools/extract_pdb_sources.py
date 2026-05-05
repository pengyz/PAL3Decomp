"""
Extract source file -> function mapping from PAL3A.PDB using DIA SDK.

Usage: python tools/extract_pdb_sources.py original/PAL3A.pdb > build/pdb_source_map.txt

Output format:
  source_file_path | function_name | rva
"""

import sys
import os

def try_dia_sdk():
    """Use Microsoft DIA SDK via COM to read PDB."""
    import comtypes
    import comtypes.client

    # Try to find msdia DLL
    msdia_paths = [
        r"C:\Program Files\Microsoft Visual Studio\2022\Community\DIA SDK\bin\amd64\msdia140.dll",
        r"C:\Program Files\Microsoft Visual Studio\2022\Professional\DIA SDK\bin\amd64\msdia140.dll",
        r"C:\Program Files\Microsoft Visual Studio\2022\Enterprise\DIA SDK\bin\amd64\msdia140.dll",
        r"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\DIA SDK\bin\msdia140.dll",
        r"C:\Program Files (x86)\Microsoft Visual Studio 14.0\DIA SDK\bin\msdia140.dll",
        r"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\DIA SDK\bin\amd64\msdia140.dll",
    ]

    # Try to create DIA source object
    try:
        # First try without explicit path (if already registered)
        dia = comtypes.client.CreateObject("DiaSource")
    except Exception:
        # Try registering msdia DLL
        for path in msdia_paths:
            if os.path.exists(path):
                print(f"# Found DIA SDK: {path}", file=sys.stderr)
                try:
                    os.system(f'regsvr32 /s "{path}"')
                    dia = comtypes.client.CreateObject("DiaSource")
                    break
                except Exception:
                    continue
        else:
            raise RuntimeError("Cannot find or register msdia140.dll. Install Visual Studio with C++ tools.")

    return dia


def extract_source_map_dia(pdb_path):
    """Extract source file to function mapping using DIA SDK."""
    import comtypes
    import comtypes.client
    from comtypes import GUID

    dia = try_dia_sdk()

    # Load PDB file
    dia.loadDataFromPdb(pdb_path)

    # Open session
    session = dia.openSession()

    # Get global scope
    global_scope = session.globalScope

    # Enumerate all functions (compilands -> functions -> source files)
    results = []

    # Iterate compilands (source file units)
    compilands = global_scope.findChildren(2, None, 0)  # SymTagCompiland = 2

    for i in range(compilands.count):
        compiland = compilands.Item(i)
        compiland_name = compiland.name if compiland.name else "unknown"

        # Get functions in this compiland
        functions = compiland.findChildren(5, None, 0)  # SymTagFunction = 5

        for j in range(functions.count):
            func = functions.Item(j)
            func_name = func.name if func.name else "unknown"
            rva = func.relativeVirtualAddress

            # Get source file for this function
            src_file = ""
            try:
                lines = session.findLinesByRVA(rva, 1)
                if lines.count > 0:
                    line = lines.Item(0)
                    src_file = line.sourceFile.fileName if line.sourceFile else ""
            except Exception:
                src_file = compiland_name

            if not src_file:
                src_file = compiland_name

            results.append((src_file, func_name, rva))

    return results


def try_raw_pdb_parse(pdb_path):
    """Fallback: parse PDB stream to extract source file names."""
    # PDB files have a "named stream" table and DBI stream with module info
    # This is a simplified parser for the DBI stream module list

    with open(pdb_path, 'rb') as f:
        magic = f.read(32)

        if b'Microsoft C/C++ MSF 7.00' not in magic:
            print("# Not a valid PDB 7.0 file", file=sys.stderr)
            return None

    # For PDB 7.0 format, read the stream directory
    # This is complex - let's just search for source file path patterns
    with open(pdb_path, 'rb') as f:
        data = f.read()

    # Look for source file paths (typically contain .cpp, .c, .h)
    # They're usually null-terminated strings in the DBI module info
    results = set()

    # Search for patterns like "x:\...\*.cpp" or relative paths
    i = 0
    while i < len(data) - 4:
        # Look for .cpp or .c file extensions followed by null byte
        if data[i:i+4] == b'.cpp' or data[i:i+2] == b'.c\x00':
            # Walk backwards to find start of string
            end = i + 4 if data[i:i+4] == b'.cpp' else i + 2
            # Find the null byte after extension
            while end < len(data) and data[end] != 0:
                end += 1

            start = i
            while start > 0 and data[start-1] != 0 and data[start-1] >= 32:
                start -= 1

            if end - start > 3 and end - start < 260:
                try:
                    path = data[start:end].decode('ascii', errors='ignore')
                    if ('\\' in path or '/' in path) and '.cpp' in path.lower() or '.c' == path[-2:].lower():
                        results.add(path)
                except:
                    pass
            i = end
        else:
            i += 1

    return sorted(results)


def main():
    if len(sys.argv) < 2:
        print("Usage: python extract_pdb_sources.py <path_to_pdb>", file=sys.stderr)
        sys.exit(1)

    pdb_path = os.path.abspath(sys.argv[1])

    if not os.path.exists(pdb_path):
        print(f"Error: PDB file not found: {pdb_path}", file=sys.stderr)
        sys.exit(1)

    print(f"# Analyzing: {pdb_path}", file=sys.stderr)
    print(f"# File size: {os.path.getsize(pdb_path)} bytes", file=sys.stderr)

    # Try DIA SDK first
    try:
        print("# Trying DIA SDK...", file=sys.stderr)
        results = extract_source_map_dia(pdb_path)
        print(f"# Found {len(results)} function entries", file=sys.stderr)

        # Group by source file
        from collections import defaultdict
        by_file = defaultdict(list)
        for src, func, rva in results:
            by_file[src].append((func, rva))

        # Output
        for src_file in sorted(by_file.keys()):
            funcs = by_file[src_file]
            print(f"\n=== {src_file} ({len(funcs)} functions) ===")
            for func_name, rva in sorted(funcs, key=lambda x: x[1]):
                print(f"  0x{rva:08X}  {func_name}")

        return
    except Exception as e:
        print(f"# DIA SDK failed: {e}", file=sys.stderr)

    # Fallback: raw string extraction
    print("# Falling back to raw PDB string extraction...", file=sys.stderr)
    paths = try_raw_pdb_parse(pdb_path)

    if paths:
        print(f"# Found {len(paths)} source file paths", file=sys.stderr)
        print("\n=== Source files found in PDB ===")
        for p in paths:
            print(f"  {p}")
    else:
        print("# Failed to extract source paths", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
