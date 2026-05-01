#!/usr/bin/env python3
"""
Apply PAL3patch known symbols to Ghidra exported function JSONs.

This script:
1. Extracts all known symbols from PAL3patch source (pal3.h + hook addresses)
2. Matches them against Ghidra exported function files
3. Renames FUN_xxxxx functions to their real names
4. Saves the symbol database to build/pal3_known_symbols.json

Usage:
    python tools/apply_symbols.py [--dry-run]
"""

import re
import os
import json
import sys

PAL3PATCH_HEADER = "extra/PAL3patch/src/PAL3patch/include/PAL3patch/pal3.h"
PAL3PATCH_SRC_DIR = "extra/PAL3patch/src/PAL3patch/src"
GHIDRA_FUNC_DIR = "asm/pal3/functions"
OUTPUT_SYMBOLS = "build/pal3_known_symbols.json"


def extract_symbols():
    """Extract all known symbols from PAL3patch."""
    symbols = {}

    with open(PAL3PATCH_HEADER, 'r', encoding='utf-8') as f:
        content = f.read()

    # TOPTR function pointers
    for m in re.finditer(
        r'#define\s+(\w+)\s+\(\(([^)]+)\)\s*TOPTR\((0x[0-9A-Fa-f]+)\)\)', content
    ):
        name, sig, addr = m.groups()
        symbols[addr.lower()] = {
            'name': name, 'type': 'function',
            'signature': sig.strip(), 'source': 'pal3.h'
        }

    # Global variables
    for m in re.finditer(
        r'#define\s+(\w+)\s+\(\*\(([^)]+)\s*\*\)\s*TOPTR\((0x[0-9A-Fa-f]+)\)\)', content
    ):
        name, type_, addr = m.groups()
        symbols[addr.lower()] = {
            'name': name, 'type': 'global',
            'datatype': type_.strip(), 'source': 'pal3.h'
        }

    # Thiscall methods
    for m in re.finditer(
        r'#define\s+(\w+)\([^)]*\)\s+THISCALL_WRAPPER\(MAKE_THISCALL_FUNCPTR\((0x[0-9A-Fa-f]+)',
        content
    ):
        name, addr = m.groups()
        symbols[addr.lower()] = {
            'name': name, 'type': 'method', 'source': 'pal3.h'
        }

    # Hook addresses from source files
    hook_patterns = [
        (r'INIT_WRAPPER_CALL\((\w+),\s*\{\s*(0x[0-9A-Fa-f]+)', 'call_site'),
        (r'make_call6?\((0x[0-9A-Fa-f]+),\s*(\w+)', 'patch_site'),
        (r'make_jmp\((0x[0-9A-Fa-f]+),\s*(\w+)', 'patch_site'),
    ]

    if os.path.isdir(PAL3PATCH_SRC_DIR):
        for fname in os.listdir(PAL3PATCH_SRC_DIR):
            if not fname.endswith('.c'):
                continue
            path = os.path.join(PAL3PATCH_SRC_DIR, fname)
            with open(path, 'r', encoding='utf-8', errors='ignore') as fp:
                for line in fp:
                    for pattern, sym_type in hook_patterns:
                        for m in re.finditer(pattern, line):
                            if sym_type == 'call_site':
                                wrapper, addr = m.groups()
                                key = addr.lower()
                                if key not in symbols:
                                    symbols[key] = {
                                        'name': f'call_site_{wrapper}',
                                        'type': sym_type, 'source': fname
                                    }
                            else:
                                addr, target = m.groups()
                                key = addr.lower()
                                if key not in symbols:
                                    symbols[key] = {
                                        'name': f'patched_by_{target}',
                                        'type': sym_type, 'source': fname
                                    }

    return symbols


def apply_to_ghidra(symbols, dry_run=False):
    """Apply symbol names to Ghidra exported JSON files."""
    if not os.path.isdir(GHIDRA_FUNC_DIR):
        print(f"Ghidra export dir not found: {GHIDRA_FUNC_DIR}")
        return 0

    renamed = 0
    for fname in os.listdir(GHIDRA_FUNC_DIR):
        if not fname.endswith('.json'):
            continue
        path = os.path.join(GHIDRA_FUNC_DIR, fname)
        with open(path, 'r') as fp:
            data = json.load(fp)

        addr = data.get('address', '').lower()
        if addr in symbols:
            sym = symbols[addr]
            old_name = data.get('name', '')
            new_name = sym['name']

            if old_name.startswith('FUN_') or old_name.startswith('thunk_FUN'):
                if not dry_run:
                    data['name'] = new_name
                    data['pal3patch_info'] = sym
                    with open(path, 'w') as fp:
                        json.dump(data, fp, indent=2, ensure_ascii=False)
                print(f"  {addr}: {old_name} -> {new_name}")
                renamed += 1

    return renamed


def main():
    dry_run = '--dry-run' in sys.argv

    print("Extracting symbols from PAL3patch...")
    symbols = extract_symbols()

    funcs = sum(1 for s in symbols.values() if s['type'] == 'function')
    methods = sum(1 for s in symbols.values() if s['type'] == 'method')
    globals_ = sum(1 for s in symbols.values() if s['type'] == 'global')
    other = len(symbols) - funcs - methods - globals_

    print(f"  Functions: {funcs}")
    print(f"  Methods:   {methods}")
    print(f"  Globals:   {globals_}")
    print(f"  Other:     {other}")
    print(f"  Total:     {len(symbols)}")
    print()

    # Save symbol database
    if not dry_run:
        os.makedirs(os.path.dirname(OUTPUT_SYMBOLS), exist_ok=True)
        output = {
            'description': 'Known symbols from PAL3patch reverse engineering',
            'source': f'{PAL3PATCH_HEADER} + {PAL3PATCH_SRC_DIR}/*.c',
            'symbols': symbols
        }
        with open(OUTPUT_SYMBOLS, 'w', encoding='utf-8') as f:
            json.dump(output, f, indent=2, ensure_ascii=False)
        print(f"Saved symbol database: {OUTPUT_SYMBOLS}")

    # Apply to Ghidra exports
    print()
    print(f"Applying to Ghidra exports {'(DRY RUN)' if dry_run else ''}...")
    renamed = apply_to_ghidra(symbols, dry_run)
    print(f"\nRenamed {renamed} functions")


if __name__ == "__main__":
    main()
