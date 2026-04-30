#!/usr/bin/env python3
"""
Batch Compare Configuration Generator.

Reads Ghidra-exported JSON files and decompiled source files,
then generates a batch_compare.json for compare.py --batch.

Usage:
    python gen_batch.py                          # All decompiled functions
    python gen_batch.py --module core             # Only core module
    python gen_batch.py --from-queue queue.json   # From prioritize.py output
    python gen_batch.py --output build/batch.json
"""

import argparse
import json
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ASM_DIR = PROJECT_ROOT / "asm"
SRC_DIR = PROJECT_ROOT / "src"
BUILD_DIR = PROJECT_ROOT / "build"


def find_source_for_function(func_name, func_address):
    """Find the decompiled source file for a function."""
    addr_str = func_address.replace('0x', '')

    # Search pattern: FUNCNAME_ADDRESS.c
    for src_file in SRC_DIR.rglob("*.c"):
        if addr_str in src_file.name:
            return str(src_file)
        if func_name in src_file.name:
            return str(src_file)

    # Search inside source files for the function
    for src_file in SRC_DIR.rglob("*.c"):
        try:
            content = src_file.read_text(encoding='utf-8', errors='ignore')
            if func_name in content or addr_str in content:
                return str(src_file)
        except IOError:
            continue

    return None


def generate_from_asm_dir(module_filter=None):
    """Generate batch config from asm/ JSON files that have corresponding source."""
    entries = []

    for json_file in sorted(ASM_DIR.glob("*.json")):
        if json_file.name.startswith('_'):
            continue

        try:
            with open(json_file) as f:
                data = json.load(f)
        except (json.JSONDecodeError, IOError):
            continue

        func_name = data.get('name', '')
        func_addr = data.get('address', '')
        func_size = data.get('size_bytes', 0)

        if not func_addr or not func_size:
            continue

        # Find source file
        source = find_source_for_function(func_name, func_addr)
        if not source:
            continue

        # Module filter
        if module_filter:
            if module_filter not in source:
                continue

        entries.append({
            'address': func_addr,
            'name': func_name,
            'size': func_size,
            'source_file': source,
        })

    return entries


def generate_from_queue(queue_path):
    """Generate batch config from a prioritize.py work queue."""
    with open(queue_path) as f:
        queue = json.load(f)

    entries = []
    for item in queue:
        source = find_source_for_function(item.get('name', ''), item.get('address', ''))
        if source:
            entries.append({
                'address': item['address'],
                'name': item.get('name', ''),
                'size': item.get('size_bytes', 256),
                'source_file': source,
            })

    return entries


def main():
    parser = argparse.ArgumentParser(
        description="Generate batch comparison configuration"
    )
    parser.add_argument('--module', '-m', help='Filter by module')
    parser.add_argument('--from-queue', '-q', help='Use prioritize.py queue file')
    parser.add_argument('--output', '-o',
                        default=str(BUILD_DIR / 'batch_compare.json'),
                        help='Output path')

    args = parser.parse_args()

    if args.from_queue:
        entries = generate_from_queue(args.from_queue)
    else:
        entries = generate_from_asm_dir(args.module)

    if not entries:
        print("No functions with decompiled source found.")
        print("Decompile some functions first with ai_decompile.py")
        sys.exit(0)

    batch = {'functions': entries}

    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    with open(args.output, 'w') as f:
        json.dump(batch, f, indent=2)

    print("Generated batch config: {} ({} functions)".format(args.output, len(entries)))
    for e in entries[:10]:
        print("  {} {} -> {}".format(e['address'], e['name'], e['source_file']))
    if len(entries) > 10:
        print("  ... ({} more)".format(len(entries) - 10))


if __name__ == '__main__':
    main()
