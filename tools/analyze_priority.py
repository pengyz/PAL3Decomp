#!/usr/bin/env python3
"""
Function Priority Analyzer

Analyzes JSON exports and generates prioritized implementation list
sorted by function size (small → large).
"""

import json
from pathlib import Path

def analyze_functions():
    """Scan all JSON files and extract function metadata."""
    functions = []

    for json_file in Path("asm/topo").glob("*.json"):
        try:
            with open(json_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
                functions.append({
                    'name': data.get('name', 'unknown'),
                    'address': data.get('address', '').upper(),
                    'size': data.get('size_bytes', 0),
                    'file': json_file.name
                })
        except Exception as e:
            print(f"Warning: Failed to parse {json_file}: {e}")

    return functions

def classify_by_size(functions):
    """Classify functions into size categories."""
    small = []   # < 50 bytes
    medium = []  # 50-150 bytes
    large = []   # > 150 bytes

    for func in functions:
        size = func['size']
        if size < 50:
            small.append(func)
        elif size < 150:
            medium.append(func)
        else:
            large.append(func)

    # Sort each category by size
    small.sort(key=lambda f: f['size'])
    medium.sort(key=lambda f: f['size'])
    large.sort(key=lambda f: f['size'])

    return small, medium, large

def main():
    print("=" * 70)
    print("Function Priority Analyzer")
    print("=" * 70)

    functions = analyze_functions()
    small, medium, large = classify_by_size(functions)

    print(f"\n[SUMMARY]")
    print(f"  Total functions: {len(functions)}")
    print(f"  Small (<50B):    {len(small)}")
    print(f"  Medium (50-150B): {len(medium)}")
    print(f"  Large (>150B):   {len(large)}")

    # Output prioritized list
    print(f"\n[BATCH 1: Small Functions (<50 bytes)] - {len(small)} functions")
    for i, func in enumerate(small[:20], 1):  # Show first 20
        print(f"  {i:3d}. {func['address']}  {func['size']:3d}B  {func['name']}")
    if len(small) > 20:
        print(f"  ... and {len(small) - 20} more")

    print(f"\n[BATCH 2: Medium Functions (50-150 bytes)] - {len(medium)} functions")
    for i, func in enumerate(medium[:20], 1):
        print(f"  {i:3d}. {func['address']}  {func['size']:3d}B  {func['name']}")
    if len(medium) > 20:
        print(f"  ... and {len(medium) - 20} more")

    print(f"\n[BATCH 3: Large Functions (>150 bytes)] - {len(large)} functions")
    for i, func in enumerate(large[:20], 1):
        print(f"  {i:3d}. {func['address']}  {func['size']:3d}B  {func['name']}")
    if len(large) > 20:
        print(f"  ... and {len(large) - 20} more")

    # Save to file
    with open("build/function_priority.txt", "w", encoding="utf-8") as f:
        f.write("BATCH 1: Small Functions (<50 bytes)\n")
        f.write("=" * 70 + "\n")
        for func in small:
            f.write(f"{func['address']},{func['size']},{func['name']},{func['file']}\n")

        f.write("\nBATCH 2: Medium Functions (50-150 bytes)\n")
        f.write("=" * 70 + "\n")
        for func in medium:
            f.write(f"{func['address']},{func['size']},{func['name']},{func['file']}\n")

        f.write("\nBATCH 3: Large Functions (>150 bytes)\n")
        f.write("=" * 70 + "\n")
        for func in large:
            f.write(f"{func['address']},{func['size']},{func['name']},{func['file']}\n")

    print(f"\n[OUTPUT] Saved to: build/function_priority.txt")
    print("=" * 70)

if __name__ == "__main__":
    main()
