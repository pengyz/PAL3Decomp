#!/usr/bin/env python3
"""Classify PAL3 functions and generate decompilation priority queue.

Usage:
    python tools/classify_functions.py [--input asm/pal3/pal3_functions.json] [--output asm/pal3/priority_queue.json]
    python tools/classify_functions.py --stats
    python tools/classify_functions.py --demo
"""

import json
import os
import sys
import argparse
import re

# Known CRT function name patterns
CRT_PATTERNS = [
    r'^_?malloc$', r'^_?free$', r'^_?realloc$', r'^_?calloc$',
    r'^_?printf', r'^_?sprintf', r'^_?fprintf', r'^_?sscanf',
    r'^_?strlen$', r'^_?strcpy', r'^_?strcat', r'^_?strcmp', r'^_?strncpy',
    r'^_?memcpy$', r'^_?memset$', r'^_?memmove$', r'^_?memcmp$',
    r'^__?CxxThrowException', r'^__?EH_', r'^___?CxxFrame',
    r'^_?_purecall', r'^__?security_check',
    r'^_?atexit', r'^_?exit$', r'^__?initterm',
    r'^_?operator new', r'^_?operator delete',
    r'^__?alloca', r'^__?chkstk',
    r'^_?setjmp', r'^_?longjmp',
    r'^_RTC_', r'^__security_',
    r'^_?fopen', r'^_?fclose', r'^_?fread', r'^_?fwrite', r'^_?fseek',
    r'^_?atoi', r'^_?atof', r'^_?strtol', r'^_?strtod',
    r'^_?sin$', r'^_?cos$', r'^_?tan$', r'^_?sqrt$', r'^_?pow$',
    r'^_?abs$', r'^_?fabs$', r'^_?floor$', r'^_?ceil$',
    r'^_?time$', r'^_?clock$',
    r'^_?rand$', r'^_?srand$',
    r'^__?CRT', r'^__?init', r'^__onexit',
]

# D3DX / DirectX patterns
D3DX_PATTERNS = [
    r'^D3DX', r'^Direct3D', r'^D3D',
    r'^_D3DX', r'^_Direct3D',
]

# Ghidra default name pattern (not yet identified)
GHIDRA_DEFAULT = r'^FUN_[0-9a-fA-F]+$'

def classify_function(func_info):
    """Classify a function based on its name, size, and characteristics.

    Returns:
        tuple: (category, priority) where priority 1 is highest, 5 is lowest
    """
    name = func_info.get('name', '')
    size = func_info.get('size', 0)
    is_thunk = func_info.get('is_thunk', False)

    if is_thunk:
        return 'thunk', 5

    # Check CRT patterns
    for pattern in CRT_PATTERNS:
        if re.match(pattern, name):
            return 'crt', 5

    # Check D3DX patterns
    for pattern in D3DX_PATTERNS:
        if re.match(pattern, name):
            return 'd3dx', 5

    # If name matches Ghidra default (FUN_XXXXXXXX), it's unidentified game logic
    if re.match(GHIDRA_DEFAULT, name):
        # Prioritize by size
        if size < 100:
            return 'game_logic_small', 1
        elif size < 500:
            return 'game_logic_medium', 2
        else:
            return 'game_logic_large', 3

    # Named function (has custom name from analysis) - likely important
    if size < 100:
        return 'game_logic_small', 1
    elif size < 500:
        return 'game_logic_medium', 2
    else:
        return 'game_logic_large', 3

def generate_demo_data():
    """Generate sample data for testing without Ghidra export."""
    return {
        'total_functions': 20,
        'functions': [
            # Small game logic (priority 1)
            {'name': 'FUN_00401000', 'address': '0x00401000', 'size': 45, 'is_thunk': False},
            {'name': 'FUN_00401030', 'address': '0x00401030', 'size': 78, 'is_thunk': False},
            {'name': 'InitPlayer', 'address': '0x00401100', 'size': 92, 'is_thunk': False},

            # Medium game logic (priority 2)
            {'name': 'FUN_00402000', 'address': '0x00402000', 'size': 256, 'is_thunk': False},
            {'name': 'FUN_00402200', 'address': '0x00402200', 'size': 324, 'is_thunk': False},
            {'name': 'LoadScene', 'address': '0x00402500', 'size': 412, 'is_thunk': False},

            # Large game logic (priority 3)
            {'name': 'FUN_00403000', 'address': '0x00403000', 'size': 856, 'is_thunk': False},
            {'name': 'BattleSystem', 'address': '0x00403500', 'size': 1024, 'is_thunk': False},
            {'name': 'FUN_00404000', 'address': '0x00404000', 'size': 2048, 'is_thunk': False},

            # CRT functions (priority 5)
            {'name': '_malloc', 'address': '0x00405000', 'size': 64, 'is_thunk': False},
            {'name': '_free', 'address': '0x00405040', 'size': 48, 'is_thunk': False},
            {'name': 'sprintf', 'address': '0x00405080', 'size': 128, 'is_thunk': False},
            {'name': '_memcpy', 'address': '0x00405100', 'size': 32, 'is_thunk': False},

            # D3DX functions (priority 5)
            {'name': 'D3DXCreateTexture', 'address': '0x00406000', 'size': 156, 'is_thunk': False},
            {'name': 'D3DXMatrixMultiply', 'address': '0x00406100', 'size': 84, 'is_thunk': False},

            # Thunks (priority 5)
            {'name': 'jmp_sub_401000', 'address': '0x00407000', 'size': 5, 'is_thunk': True},
            {'name': 'jmp_sub_402000', 'address': '0x00407010', 'size': 5, 'is_thunk': True},

            # More game logic
            {'name': 'UpdateNPC', 'address': '0x00408000', 'size': 234, 'is_thunk': False},
            {'name': 'FUN_00408200', 'address': '0x00408200', 'size': 67, 'is_thunk': False},
            {'name': 'RenderUI', 'address': '0x00408300', 'size': 512, 'is_thunk': False},
        ]
    }

def main():
    parser = argparse.ArgumentParser(description='Classify PAL3 functions')
    parser.add_argument('--input', default='asm/pal3/pal3_functions.json',
                       help='Input function list JSON')
    parser.add_argument('--output', default='asm/pal3/priority_queue.json',
                       help='Output priority queue JSON')
    parser.add_argument('--stats', action='store_true',
                       help='Show statistics only')
    parser.add_argument('--demo', action='store_true',
                       help='Run with demo data (for testing without Ghidra export)')
    args = parser.parse_args()

    # Load or generate function list
    if args.demo:
        print("=== DEMO MODE: Using sample data ===\n")
        data = generate_demo_data()
    else:
        if not os.path.exists(args.input):
            print(f"Error: Input file not found: {args.input}")
            print("Run Ghidra export first (Task 1 + Task 2)")
            print("Or use --demo flag to test with sample data")
            sys.exit(1)

        with open(args.input) as f:
            data = json.load(f)

    functions = data.get('functions', [])
    print(f"Loaded {len(functions)} functions")

    # Classify each function
    classified = []
    stats = {}

    for func in functions:
        category, priority = classify_function(func)
        stats[category] = stats.get(category, 0) + 1
        classified.append({
            **func,
            'category': category,
            'priority': priority,
        })

    # Sort by priority (1=highest) then by size (smaller first)
    classified.sort(key=lambda f: (f['priority'], f.get('size', 0)))

    # Output
    if args.stats:
        print("\n=== Classification Statistics ===")
        for cat in sorted(stats.keys()):
            count = stats[cat]
            print(f"  {cat}: {count}")
        print(f"  TOTAL: {len(classified)}")

        print("\n=== Priority Breakdown ===")
        for p in range(1, 6):
            count = sum(1 for f in classified if f['priority'] == p)
            if count > 0:
                print(f"  Priority {p}: {count} functions")

        print("\n=== Top 10 Priority Functions ===")
        for i, func in enumerate(classified[:10], 1):
            print(f"  {i}. [{func['category']}] {func['name']} - {func['size']} bytes (priority {func['priority']})")
    else:
        output = {
            'total_functions': len(classified),
            'statistics': stats,
            'priority_queue': classified
        }

        if not args.demo:
            os.makedirs(os.path.dirname(args.output) or '.', exist_ok=True)
            with open(args.output, 'w') as f:
                json.dump(output, f, indent=2)
            print(f"Priority queue saved to: {args.output}")
        else:
            print("\nPriority queue (sample):")
            print(json.dumps(output, indent=2)[:1000] + "...")

        print(f"\n=== Statistics ===")
        for cat in sorted(stats.keys()):
            count = stats[cat]
            print(f"  {cat}: {count}")

        print(f"\n=== Priority Breakdown ===")
        for p in range(1, 6):
            count = sum(1 for f in classified if f['priority'] == p)
            if count > 0:
                print(f"  Priority {p}: {count} functions")

if __name__ == '__main__':
    main()
