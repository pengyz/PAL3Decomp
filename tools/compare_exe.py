#!/usr/bin/env python3
"""
PAL3.exe Binary Comparison Tool

Compare compiled PAL3.exe against original at specific function addresses.
Handles PE format parsing, RVA to file offset conversion, and byte-level comparison.

Usage:
    python compare_exe.py --address 0x00401000 --size 128
    python compare_exe.py --address 0x00401000 --size 128 --original original/PAL3.exe --compiled build/pal3_build/Release/PAL3.exe
    python compare_exe.py --batch functions.json
"""

import struct
import sys
import argparse
import json
from pathlib import Path
from typing import Optional, Tuple, List, Dict


def read_u16(data: bytes, offset: int) -> int:
    """Read 16-bit unsigned integer (little-endian)."""
    return struct.unpack_from('<H', data, offset)[0]


def read_u32(data: bytes, offset: int) -> int:
    """Read 32-bit unsigned integer (little-endian)."""
    return struct.unpack_from('<I', data, offset)[0]


def read_cstring(data: bytes, offset: int, max_len: int = 8) -> str:
    """Read null-terminated ASCII string."""
    end = data.find(b'\x00', offset, offset + max_len)
    if end == -1:
        end = offset + max_len
    return data[offset:end].decode('ascii', errors='replace')


class PEParser:
    """Simple PE file parser for extracting code sections."""

    def __init__(self, filepath: Path):
        self.filepath = filepath
        self.data = None
        self.image_base = 0
        self.sections = []
        self._load()

    def _load(self):
        """Load and parse PE file structure."""
        with open(self.filepath, 'rb') as f:
            self.data = f.read()

        # Verify DOS signature
        if self.data[:2] != b'MZ':
            raise ValueError(f"Not a valid PE file: {self.filepath}")

        # Get PE header offset
        pe_offset = read_u32(self.data, 0x3C)

        # Verify PE signature
        if self.data[pe_offset:pe_offset+4] != b'PE\x00\x00':
            raise ValueError(f"Invalid PE signature: {self.filepath}")

        # Parse COFF header
        coff_offset = pe_offset + 4
        machine = read_u16(self.data, coff_offset + 0)
        num_sections = read_u16(self.data, coff_offset + 2)
        opt_header_size = read_u16(self.data, coff_offset + 16)

        # Parse Optional header
        opt_offset = coff_offset + 20
        magic = read_u16(self.data, opt_offset)

        if magic == 0x010B:  # PE32
            self.image_base = read_u32(self.data, opt_offset + 28)
        elif magic == 0x020B:  # PE32+
            # PE32+ has different layout, but PAL3.exe should be PE32
            raise ValueError(f"PE32+ not supported: {self.filepath}")
        else:
            raise ValueError(f"Unknown PE magic: 0x{magic:04X}")

        # Parse section table
        section_offset = opt_offset + opt_header_size
        for i in range(num_sections):
            sec_base = section_offset + i * 40
            name = read_cstring(self.data, sec_base, 8).rstrip('\x00')
            vsize = read_u32(self.data, sec_base + 8)
            va = read_u32(self.data, sec_base + 12)
            raw_size = read_u32(self.data, sec_base + 16)
            raw_offset = read_u32(self.data, sec_base + 20)

            self.sections.append({
                'name': name,
                'va': va,
                'vsize': vsize,
                'raw_size': raw_size,
                'raw_offset': raw_offset
            })

    def rva_to_file_offset(self, rva: int) -> Optional[int]:
        """Convert RVA to file offset using section table."""
        for section in self.sections:
            if section['va'] <= rva < section['va'] + max(section['vsize'], section['raw_size']):
                return rva - section['va'] + section['raw_offset']
        return None

    def read_bytes_at_rva(self, rva: int, size: int) -> Optional[bytes]:
        """Read bytes from PE file at given RVA."""
        file_offset = self.rva_to_file_offset(rva)
        if file_offset is None:
            return None

        if file_offset + size > len(self.data):
            # Read what's available
            size = len(self.data) - file_offset

        return self.data[file_offset:file_offset + size]

    def read_bytes_at_address(self, address: int, size: int) -> Optional[bytes]:
        """Read bytes from PE file at given absolute address."""
        # Convert absolute address to RVA
        if address >= self.image_base:
            rva = address - self.image_base
        else:
            # Assume it's already an RVA
            rva = address

        return self.read_bytes_at_rva(rva, size)


def compare_bytes(original_bytes: bytes, compiled_bytes: bytes) -> Tuple[int, int]:
    """
    Compare two byte sequences.

    Returns:
        (matches, total) tuple
    """
    total = min(len(original_bytes), len(compiled_bytes))
    matches = sum(1 for i in range(total) if original_bytes[i] == compiled_bytes[i])
    return matches, total


def format_hex_diff(original_bytes: bytes, compiled_bytes: bytes, base_addr: int,
                     show_all: bool = False) -> str:
    """
    Format a hex diff showing differences between two byte sequences.

    Args:
        original_bytes: Original bytes
        compiled_bytes: Compiled bytes
        base_addr: Base address for display
        show_all: If True, show all bytes; if False, only show first 10 differences

    Returns:
        Formatted diff string
    """
    lines = []
    bytes_per_line = 16
    total = min(len(original_bytes), len(compiled_bytes))
    diff_count = 0
    max_diffs = 10 if not show_all else total

    for i in range(0, total, bytes_per_line):
        chunk_size = min(bytes_per_line, total - i)
        orig_chunk = original_bytes[i:i+chunk_size]
        comp_chunk = compiled_bytes[i:i+chunk_size]

        # Check if this line has differences
        has_diff = any(orig_chunk[j] != comp_chunk[j] for j in range(len(orig_chunk)))

        if has_diff or show_all:
            addr_str = f"{base_addr + i:08X}"

            # Format original bytes
            orig_hex = []
            for j, b in enumerate(orig_chunk):
                if j < len(comp_chunk) and b != comp_chunk[j]:
                    orig_hex.append(f"\033[91m{b:02X}\033[0m")  # Red for differences
                    diff_count += 1
                else:
                    orig_hex.append(f"{b:02X}")
            orig_line = ' '.join(orig_hex)

            # Format compiled bytes
            comp_hex = []
            for j, b in enumerate(comp_chunk):
                if j < len(orig_chunk) and b != orig_chunk[j]:
                    comp_hex.append(f"\033[92m{b:02X}\033[0m")  # Green for differences
                else:
                    comp_hex.append(f"{b:02X}")
            comp_line = ' '.join(comp_hex)

            lines.append(f"{addr_str}  O: {orig_line}")
            lines.append(f"{'':8}  C: {comp_line}")
            lines.append("")

            if not show_all and diff_count >= max_diffs * bytes_per_line:
                lines.append("... (showing first 10 difference locations)")
                break

    return '\n'.join(lines)


def compare_function(original_path: Path, compiled_path: Path,
                      address: int, size: int, verbose: bool = False) -> bool:
    """
    Compare a specific function between original and compiled executables.

    Args:
        original_path: Path to original PAL3.exe
        compiled_path: Path to compiled PAL3.exe
        address: Function address (RVA or absolute)
        size: Function size in bytes
        verbose: Show detailed hex diff

    Returns:
        True if perfect match, False otherwise
    """
    print(f"Comparing function at 0x{address:08X} ({size} bytes)")
    print("=" * 70)

    # Load PE files
    try:
        original_pe = PEParser(original_path)
        compiled_pe = PEParser(compiled_path)
    except Exception as e:
        print(f"Error loading PE files: {e}")
        return False

    # Read bytes
    original_bytes = original_pe.read_bytes_at_address(address, size)
    compiled_bytes = compiled_pe.read_bytes_at_address(address, size)

    if original_bytes is None:
        print(f"Error: Could not read bytes from original at 0x{address:08X}")
        return False

    if compiled_bytes is None:
        print(f"Error: Could not read bytes from compiled at 0x{address:08X}")
        return False

    # Compare
    matches, total = compare_bytes(original_bytes, compiled_bytes)
    match_rate = (matches / total * 100) if total > 0 else 0

    print(f"\nMatch rate: {matches}/{total} bytes ({match_rate:.1f}%)")

    if matches == total:
        print("\033[92m[OK] PERFECT MATCH!\033[0m")
        return True
    else:
        print(f"\033[91m[X] MISMATCH\033[0m ({total - matches} bytes differ)")

        if verbose:
            print("\nDetailed diff:")
            print(format_hex_diff(original_bytes, compiled_bytes, address, show_all=False))
        else:
            # Show first 5 differences
            print("\nFirst differences:")
            diff_count = 0
            for i in range(min(len(original_bytes), len(compiled_bytes))):
                if original_bytes[i] != compiled_bytes[i]:
                    print(f"  Offset +0x{i:04X}: "
                          f"original=0x{original_bytes[i]:02X} "
                          f"compiled=0x{compiled_bytes[i]:02X}")
                    diff_count += 1
                    if diff_count >= 5:
                        print(f"  ... ({total - matches} total differences)")
                        break

        return False


def batch_compare(original_path: Path, compiled_path: Path,
                   functions: List[Dict], verbose: bool = False) -> Tuple[int, int]:
    """
    Compare multiple functions from a batch list.

    Args:
        original_path: Path to original PAL3.exe
        compiled_path: Path to compiled PAL3.exe
        functions: List of dicts with 'address' and 'size' keys
        verbose: Show detailed output for each function

    Returns:
        (matched, total) tuple
    """
    matched = 0
    total = len(functions)

    print(f"Batch comparison: {total} functions")
    print("=" * 70)

    for i, func in enumerate(functions, 1):
        address = func.get('address', 0)
        size = func.get('size', 0)
        name = func.get('name', f'func_{i}')

        if isinstance(address, str):
            address = int(address, 16) if address.startswith('0x') else int(address)

        print(f"\n[{i}/{total}] {name} @ 0x{address:08X} ({size} bytes)")

        if compare_function(original_path, compiled_path, address, size, verbose=False):
            matched += 1

    print("\n" + "=" * 70)
    print(f"Batch results: {matched}/{total} functions matched ({100*matched//total if total > 0 else 0}%)")

    return matched, total


def main():
    parser = argparse.ArgumentParser(
        description='Compare compiled PAL3.exe against original at specific function addresses'
    )
    parser.add_argument('--original', type=str, default='original/PAL3.exe',
                        help='Path to original PAL3.exe')
    parser.add_argument('--compiled', type=str, default='build/pal3_build/Release/PAL3.exe',
                        help='Path to compiled PAL3.exe')
    parser.add_argument('--address', type=str,
                        help='Function address (hex with 0x prefix or decimal)')
    parser.add_argument('--size', type=int,
                        help='Function size in bytes')
    parser.add_argument('--batch', type=str,
                        help='JSON file with list of functions to compare')
    parser.add_argument('--verbose', '-v', action='store_true',
                        help='Show detailed hex diff')

    args = parser.parse_args()

    # Resolve paths relative to project root
    project_root = Path(__file__).parent.parent
    original_path = project_root / args.original
    compiled_path = project_root / args.compiled

    # Check files exist
    if not original_path.exists():
        print(f"Error: Original file not found: {original_path}")
        print("Please place PAL3.exe in the original/ directory")
        sys.exit(1)

    if not compiled_path.exists():
        print(f"Error: Compiled file not found: {compiled_path}")
        print("Please build first (e.g., cmake --build build --config Release)")
        sys.exit(1)

    # Batch mode
    if args.batch:
        batch_file = project_root / args.batch
        if not batch_file.exists():
            print(f"Error: Batch file not found: {batch_file}")
            sys.exit(1)

        with open(batch_file, 'r') as f:
            functions = json.load(f)

        matched, total = batch_compare(original_path, compiled_path, functions, args.verbose)
        sys.exit(0 if matched == total else 1)

    # Single function mode
    if not args.address or not args.size:
        print("Error: --address and --size required for single function mode")
        print("       or use --batch for multiple functions")
        parser.print_help()
        sys.exit(1)

    # Parse address
    address_str = args.address
    if address_str.startswith('0x') or address_str.startswith('0X'):
        address = int(address_str, 16)
    else:
        address = int(address_str)

    result = compare_function(original_path, compiled_path, address, args.size, args.verbose)
    sys.exit(0 if result else 1)


if __name__ == "__main__":
    main()
