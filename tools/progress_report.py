#!/usr/bin/env python3
"""
PAL3 Decompilation Progress Tracker

Analyzes the decompilation progress by comparing:
- Implemented functions in src/
- Exported functions in asm/
- Matching rate with original binary
"""

import json
from pathlib import Path
from collections import defaultdict

def count_implemented_functions():
    """Count functions implemented in C++ source files."""
    implemented = defaultdict(list)

    for cpp_file in Path("src/topo").glob("*.cpp"):
        with open(cpp_file, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
            for i, line in enumerate(lines):
                if line.startswith("// 0x"):
                    # Extract address
                    parts = line.split()
                    if len(parts) >= 2:
                        addr = parts[1]
                        func_name = parts[2] if len(parts) > 2 else "unknown"
                        implemented[cpp_file.name].append({
                            'address': addr,
                            'name': func_name,
                            'line': i + 1
                        })

    return implemented

def count_exported_functions():
    """Count functions in Ghidra export JSON files."""
    exported = []

    for json_file in Path("asm/topo").glob("*.json"):
        try:
            with open(json_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
                exported.append({
                    'address': data.get('address', ''),
                    'name': data.get('name', ''),
                    'size': data.get('size_bytes', 0),
                    'file': json_file.name
                })
        except Exception as e:
            print(f"Warning: Failed to parse {json_file}: {e}")

    return exported

def find_stubs_and_todos():
    """Find stub implementations and TODO markers."""
    issues = []

    for cpp_file in Path("src/topo").glob("*.cpp"):
        with open(cpp_file, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
            for i, line in enumerate(lines):
                if any(marker in line.upper() for marker in ['TODO', 'STUB', 'FIXME', 'INCOMPLETE']):
                    issues.append({
                        'file': cpp_file.name,
                        'line': i + 1,
                        'text': line.strip()
                    })

    return issues

def main():
    print("=" * 70)
    print("PAL3 Decompilation Progress Report")
    print("=" * 70)

    implemented = count_implemented_functions()
    exported = count_exported_functions()
    issues = find_stubs_and_todos()

    total_impl = sum(len(funcs) for funcs in implemented.values())
    total_export = len(exported)

    print(f"\n[STATS] Overall Progress:")
    print(f"  Implemented:  {total_impl:3d} functions")
    print(f"  Total target: {total_export:3d} functions")
    print(f"  Progress:     {total_impl}/{total_export} ({100*total_impl//total_export if total_export > 0 else 0}%)")
    print(f"  Remaining:    {total_export - total_impl:3d} functions")

    print(f"\n[FILES] By Source File:")
    for file_name in sorted(implemented.keys()):
        funcs = implemented[file_name]
        print(f"  {file_name:<25} {len(funcs):3d} functions")

    if issues:
        print(f"\n[WARN] Incomplete Implementations ({len(issues)}):")
        for issue in issues[:10]:  # Show first 10
            print(f"  {issue['file']}:{issue['line']:4d}  {issue['text']}")
        if len(issues) > 10:
            print(f"  ... and {len(issues) - 10} more")

    print(f"\n[TODO] Next Steps:")
    print(f"  1. Implement remaining {total_export - total_impl} functions")
    print(f"  2. Resolve {len(issues)} TODOs/stubs")
    print(f"  3. Verify byte-matching with original binary")
    print(f"  4. Run: python tools/compare_function.py <address> <size>")

    print("\n" + "=" * 70)

if __name__ == "__main__":
    main()
