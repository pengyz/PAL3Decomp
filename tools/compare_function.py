#!/usr/bin/env python3
"""
Compare a specific function between original and decompiled binaries.

Usage: python compare_function.py <function_address> [size]
"""

import sys
import struct
from pathlib import Path

def read_bytes(file_path, address, size):
    """Read bytes from PE file at RVA address."""
    try:
        with open(file_path, 'rb') as f:
            # For DLL, address is RVA, need to convert to file offset
            # Simplified: assume .text section starts at 0x1000 (RVA) and 0x400 (file offset)
            # This is typical for MSVC DLLs
            if address >= 0x10000000:
                # Handle full address with image base
                address -= 0x10000000

            # Simple RVA to file offset (works for .text section)
            # .text RVA usually starts at 0x1000, file offset at 0x400
            file_offset = address - 0x1000 + 0x400

            f.seek(file_offset)
            data = f.read(size)
            return data
    except Exception as e:
        print(f"Error reading {file_path}: {e}")
        return None

def format_hex(data, bytes_per_line=16):
    """Format bytes as hex dump."""
    lines = []
    for i in range(0, len(data), bytes_per_line):
        chunk = data[i:i+bytes_per_line]
        hex_part = ' '.join(f'{b:02x}' for b in chunk)
        ascii_part = ''.join(chr(b) if 32 <= b < 127 else '.' for b in chunk)
        lines.append(f"{i:04x}  {hex_part:<48}  {ascii_part}")
    return '\n'.join(lines)

def compare_functions(original_dll, compiled_dll, address, size):
    """Compare function bytes between original and compiled DLL."""
    print(f"Comparing function at 0x{address:08x} ({size} bytes)")
    print("=" * 70)

    original_bytes = read_bytes(original_dll, address, size)
    compiled_bytes = read_bytes(compiled_dll, address, size)

    if original_bytes is None or compiled_bytes is None:
        print("Failed to read one or both files")
        return False

    if len(original_bytes) < size:
        print(f"Warning: Original DLL only has {len(original_bytes)} bytes")
        size = len(original_bytes)

    if len(compiled_bytes) < size:
        print(f"Warning: Compiled DLL only has {len(compiled_bytes)} bytes")
        size = len(compiled_bytes)

    # Compare
    matches = sum(1 for i in range(min(size, len(original_bytes), len(compiled_bytes)))
                  if original_bytes[i] == compiled_bytes[i])

    match_rate = (matches / size * 100) if size > 0 else 0

    print(f"\nMatch rate: {matches}/{size} bytes ({match_rate:.1f}%)")

    if matches == size:
        print("✓ PERFECT MATCH!")
        return True

    # Show first difference
    print("\nFirst differences:")
    diff_count = 0
    for i in range(min(size, len(original_bytes), len(compiled_bytes))):
        if original_bytes[i] != compiled_bytes[i]:
            print(f"  Offset +0x{i:04x}: "
                  f"original=0x{original_bytes[i]:02x} "
                  f"compiled=0x{compiled_bytes[i]:02x}")
            diff_count += 1
            if diff_count >= 10:
                print(f"  ... ({size - matches} total differences)")
                break

    return False

def main():
    if len(sys.argv) < 2:
        print("Usage: python compare_function.py <address_hex> [size_bytes]")
        print("Example: python compare_function.py 0x10001110 12")
        sys.exit(1)

    # Parse address
    addr_str = sys.argv[1]
    if addr_str.startswith('0x'):
        address = int(addr_str, 16)
    else:
        address = int(addr_str)

    # Parse size
    size = int(sys.argv[2]) if len(sys.argv) > 2 else 64

    # Find DLL files
    project_root = Path(__file__).parent.parent
    original_dll = project_root / "original" / "topo.dll"
    compiled_dll = project_root / "build" / "verify" / "topo.dll"

    if not original_dll.exists():
        print(f"Original DLL not found: {original_dll}")
        print("Please place the original topo.dll in original/ directory")
        sys.exit(1)

    if not compiled_dll.exists():
        print(f"Compiled DLL not found: {compiled_dll}")
        print("Please build first: ./run_verify.bat")
        sys.exit(1)

    result = compare_functions(original_dll, compiled_dll, address, size)
    sys.exit(0 if result else 1)

if __name__ == "__main__":
    main()
