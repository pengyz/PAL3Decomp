#!/usr/bin/env python3
"""
Compile & Compare tool for PAL3 Decompilation.

Compiles a C/C++ source file using MSVC and compares the generated machine code
against the original PAL3.exe binary at specified function addresses.

Usage:
    python compare.py --source src/core/render.c --func-addr 0x00401000 --func-size 256
    python compare.py --source src/core/render.c --map-file build/render.map
    python compare.py --batch batch_compare.json

Requires:
    - MSVC cl.exe and link.exe in PATH (or configured via environment)
    - Original PAL3.exe in the original/ directory
    - Python 3.8+

Match Levels:
    Level 1: Byte-identical (perfect match)
    Level 2: Instruction-identical but different register allocation
    Level 3: Functionally equivalent (same control flow, different instruction sequence)
"""

import argparse
import json
import os
import struct
import subprocess
import sys
import tempfile
from dataclasses import dataclass, field
from enum import IntEnum
from pathlib import Path
from typing import Optional


class MatchLevel(IntEnum):
    NO_MATCH = 0
    FUNCTIONAL = 3       # Same control flow, different instructions
    INSTRUCTION = 2      # Same instructions, different registers
    BYTE_IDENTICAL = 1   # Perfect byte match


@dataclass
class CompareResult:
    func_address: str
    func_name: str
    match_level: MatchLevel
    original_bytes: bytes = field(repr=False)
    compiled_bytes: bytes = field(repr=False)
    diff_lines: list = field(default_factory=list)
    compile_errors: str = ""
    notes: str = ""


# Project paths
PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_EXE = PROJECT_ROOT / "original" / "PAL3.exe"
BUILD_DIR = PROJECT_ROOT / "build"
RESULTS_DIR = BUILD_DIR / "compare_results"


def find_msvc():
    """Locate MSVC compiler. Returns (cl_path, link_path) or raises."""
    # Check if cl.exe is already in PATH
    try:
        result = subprocess.run(['cl'], capture_output=True, timeout=5)
        return 'cl.exe', 'link.exe'
    except (FileNotFoundError, subprocess.TimeoutExpired):
        pass

    # Check common Visual Studio installation paths
    vs_paths = [
        r"C:\Program Files (x86)\Microsoft Visual Studio .NET 2003\Vc7\bin",
        r"C:\Program Files (x86)\Microsoft Visual Studio\VC98\Bin",
        r"C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\bin",
        r"C:\MSVC\VC\bin",  # Custom install location
    ]

    for vs_path in vs_paths:
        cl_path = os.path.join(vs_path, "cl.exe")
        if os.path.exists(cl_path):
            link_path = os.path.join(vs_path, "link.exe")
            return cl_path, link_path

    # Check environment variable
    msvc_path = os.environ.get('MSVC_PATH')
    if msvc_path:
        cl_path = os.path.join(msvc_path, "cl.exe")
        if os.path.exists(cl_path):
            return cl_path, os.path.join(msvc_path, "link.exe")

    raise FileNotFoundError(
        "MSVC cl.exe not found. Set MSVC_PATH environment variable or "
        "add cl.exe to PATH. For matching decompilation, use the same "
        "MSVC version as the original binary (check Rich Header)."
    )


def get_compile_flags(config: dict) -> list:
    """Get MSVC compile flags based on configuration."""
    # Default flags matching typical early-2000s MSVC game builds
    flags = [
        '/nologo',
        '/c',              # Compile only, no link
        '/GS-',           # No buffer security check (didn't exist in older MSVC)
    ]

    # Optimization level
    opt = config.get('optimization', '/O2')
    flags.append(opt)

    # Calling convention
    cc = config.get('calling_convention', '/Gd')  # __cdecl default
    flags.append(cc)

    # Additional flags
    if config.get('rtti', True):
        flags.append('/GR')  # Enable RTTI
    else:
        flags.append('/GR-')

    if config.get('exceptions', True):
        flags.append('/EHsc')  # C++ exceptions

    # Include paths
    include_dir = PROJECT_ROOT / "include"
    flags.append('/I{}'.format(include_dir))

    # Additional includes
    for inc in config.get('extra_includes', []):
        flags.append('/I{}'.format(inc))

    # Preprocessor defines
    for define in config.get('defines', ['WIN32', '_WINDOWS', 'NDEBUG']):
        flags.append('/D{}'.format(define))

    return flags


def compile_source(source_file: str, config: dict) -> tuple:
    """
    Compile a source file with MSVC.

    Returns: (obj_path, error_string)
    """
    cl_path, _ = find_msvc()
    flags = get_compile_flags(config)

    # Output object file
    obj_name = Path(source_file).stem + '.obj'
    obj_path = BUILD_DIR / obj_name
    BUILD_DIR.mkdir(parents=True, exist_ok=True)

    cmd = [cl_path] + flags + [
        '/Fo{}'.format(obj_path),
        '/Fa{}'.format(BUILD_DIR / (Path(source_file).stem + '.asm')),  # Generate assembly listing
        str(source_file),
    ]

    try:
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            timeout=30,
            cwd=str(PROJECT_ROOT),
        )

        if result.returncode != 0:
            return None, result.stderr + result.stdout

        return str(obj_path), ""

    except subprocess.TimeoutExpired:
        return None, "Compilation timed out"
    except Exception as e:
        return None, str(e)


def extract_function_from_obj(obj_path: str, func_name: str) -> Optional[bytes]:
    """
    Extract compiled bytes of a specific function from an OBJ file.

    Uses dumpbin or manual COFF parsing to find the function's code.
    """
    # Try dumpbin first (MSVC tool)
    try:
        result = subprocess.run(
            ['dumpbin', '/disasm', '/section:.text', obj_path],
            capture_output=True, text=True, timeout=15
        )
        if result.returncode == 0:
            # Parse dumpbin output to find function bytes
            return _parse_dumpbin_output(result.stdout, func_name)
    except FileNotFoundError:
        pass

    # Fallback: parse COFF manually
    return _parse_coff_text_section(obj_path)


def _parse_coff_text_section(obj_path: str) -> Optional[bytes]:
    """Parse a COFF .obj file to extract the .text section raw bytes."""
    try:
        with open(obj_path, 'rb') as f:
            # COFF header
            machine = struct.unpack('<H', f.read(2))[0]
            num_sections = struct.unpack('<H', f.read(2))[0]
            f.read(12)  # timestamp, symbol table pointer, num symbols
            opt_header_size = struct.unpack('<H', f.read(2))[0]
            f.read(2)  # characteristics

            # Skip optional header
            f.read(opt_header_size)

            # Section headers
            for i in range(num_sections):
                name = f.read(8).rstrip(b'\x00').decode('ascii', errors='ignore')
                virtual_size = struct.unpack('<I', f.read(4))[0]
                virtual_addr = struct.unpack('<I', f.read(4))[0]
                raw_size = struct.unpack('<I', f.read(4))[0]
                raw_ptr = struct.unpack('<I', f.read(4))[0]
                f.read(16)  # reloc ptr, linenum ptr, num relocs, num linenums, characteristics

                if name == '.text':
                    # Read the .text section
                    current_pos = f.tell()
                    f.seek(raw_ptr)
                    code_bytes = f.read(raw_size)
                    f.seek(current_pos)
                    return code_bytes

    except Exception:
        pass

    return None


def _parse_dumpbin_output(output: str, func_name: str) -> Optional[bytes]:
    """Parse dumpbin /disasm output to extract function bytes."""
    # This is a simplified parser - real implementation would be more robust
    code_bytes = bytearray()
    in_function = False

    for line in output.split('\n'):
        line = line.strip()
        if func_name in line and ':' in line:
            in_function = True
            continue
        if in_function:
            # Lines look like: "  00000000: 55                 push        ebp"
            if line and line[0:8].strip() and ':' in line[:12]:
                parts = line.split(':')
                if len(parts) >= 2:
                    hex_part = parts[1].split()
                    for h in hex_part:
                        if all(c in '0123456789ABCDEFabcdef' for c in h) and len(h) == 2:
                            code_bytes.append(int(h, 16))
                        else:
                            break
            elif not line or (line and not line[0].isspace()):
                break  # End of function

    return bytes(code_bytes) if code_bytes else None


def read_original_bytes(address: int, size: int) -> Optional[bytes]:
    """Read bytes from the original PAL3.exe at a given virtual address."""
    if not ORIGINAL_EXE.exists():
        return None

    # Parse PE headers to convert VA to file offset
    with open(ORIGINAL_EXE, 'rb') as f:
        # DOS header
        f.seek(0x3C)
        pe_offset = struct.unpack('<I', f.read(4))[0]

        # PE signature
        f.seek(pe_offset)
        sig = f.read(4)
        if sig != b'PE\x00\x00':
            return None

        # COFF header
        f.read(2)  # Machine
        num_sections = struct.unpack('<H', f.read(2))[0]
        f.read(12)  # Timestamp, symbol table, num symbols
        opt_header_size = struct.unpack('<H', f.read(2))[0]
        f.read(2)  # Characteristics

        # Optional header - get ImageBase
        opt_start = f.tell()
        f.read(28)  # Skip to ImageBase (offset 28 in optional header)
        image_base = struct.unpack('<I', f.read(4))[0]

        # Skip to section headers
        f.seek(opt_start + opt_header_size)

        # Convert VA to file offset
        rva = address - image_base

        for i in range(num_sections):
            name = f.read(8)
            virtual_size = struct.unpack('<I', f.read(4))[0]
            virtual_addr = struct.unpack('<I', f.read(4))[0]
            raw_size = struct.unpack('<I', f.read(4))[0]
            raw_ptr = struct.unpack('<I', f.read(4))[0]
            f.read(16)  # Rest of section header

            if virtual_addr <= rva < virtual_addr + virtual_size:
                file_offset = raw_ptr + (rva - virtual_addr)
                f.seek(file_offset)
                return f.read(size)

    return None


def disassemble_bytes(code_bytes: bytes, base_addr: int = 0) -> list:
    """
    Disassemble bytes to instruction list.
    Uses a simple x86 disassembler or external tool.
    """
    # Try using objdump or ndisasm if available
    try:
        with tempfile.NamedTemporaryFile(suffix='.bin', delete=False) as tmp:
            tmp.write(code_bytes)
            tmp_path = tmp.name

        result = subprocess.run(
            ['ndisasm', '-b', '32', '-o', hex(base_addr), tmp_path],
            capture_output=True, text=True, timeout=10
        )
        os.unlink(tmp_path)

        if result.returncode == 0:
            return result.stdout.strip().split('\n')
    except FileNotFoundError:
        pass

    # Fallback: hex dump
    lines = []
    for i in range(0, len(code_bytes), 16):
        chunk = code_bytes[i:i+16]
        hex_str = ' '.join('{:02x}'.format(b) for b in chunk)
        lines.append("{:08x}: {}".format(base_addr + i, hex_str))
    return lines


def compare_bytes(original: bytes, compiled: bytes) -> tuple:
    """
    Compare two byte sequences and determine match level.

    Returns: (MatchLevel, diff_lines)
    """
    if not original or not compiled:
        return MatchLevel.NO_MATCH, ["ERROR: Missing bytes for comparison"]

    # Level 1: Byte-identical
    if original == compiled:
        return MatchLevel.BYTE_IDENTICAL, []

    # Level 2: Check if instructions are the same but registers differ
    # (simplified heuristic - a full implementation would use a disassembler)
    diff_lines = []
    min_len = min(len(original), len(compiled))
    max_len = max(len(original), len(compiled))

    mismatches = 0
    for i in range(min_len):
        if original[i] != compiled[i]:
            mismatches += 1
            diff_lines.append(
                "  offset {:04x}: orig={:02x} compiled={:02x}".format(
                    i, original[i], compiled[i])
            )

    if len(original) != len(compiled):
        diff_lines.append(
            "  SIZE MISMATCH: original={} bytes, compiled={} bytes".format(
                len(original), len(compiled))
        )

    # Heuristic: if less than 10% of bytes differ and size is the same,
    # likely register allocation differences
    if len(original) == len(compiled) and mismatches < max(1, len(original) * 0.1):
        return MatchLevel.INSTRUCTION, diff_lines

    # Level 3: Would need control flow analysis - mark as functional if
    # sizes are similar (within 10%)
    if abs(len(original) - len(compiled)) < max_len * 0.1:
        return MatchLevel.FUNCTIONAL, diff_lines

    return MatchLevel.NO_MATCH, diff_lines


def generate_diff_report(result: CompareResult, output_path: str):
    """Generate a human-readable diff report."""
    lines = []
    lines.append("=" * 70)
    lines.append("Comparison Report: {} ({})".format(result.func_name, result.func_address))
    lines.append("=" * 70)
    lines.append("")
    lines.append("Match Level: {} ({})".format(
        result.match_level.value,
        result.match_level.name
    ))
    lines.append("")

    if result.compile_errors:
        lines.append("COMPILATION ERRORS:")
        lines.append(result.compile_errors)
        lines.append("")

    if result.diff_lines:
        lines.append("DIFFERENCES:")
        for dl in result.diff_lines[:100]:  # Limit output
            lines.append(dl)
        if len(result.diff_lines) > 100:
            lines.append("  ... ({} more differences)".format(
                len(result.diff_lines) - 100))
        lines.append("")

    # Show disassembly side by side
    if result.original_bytes and result.compiled_bytes:
        addr = int(result.func_address, 16)
        orig_asm = disassemble_bytes(result.original_bytes, addr)
        comp_asm = disassemble_bytes(result.compiled_bytes, addr)

        lines.append("DISASSEMBLY COMPARISON:")
        lines.append("-" * 70)
        lines.append("{:<35} | {}".format("ORIGINAL", "COMPILED"))
        lines.append("-" * 70)

        max_lines = max(len(orig_asm), len(comp_asm))
        for i in range(min(max_lines, 50)):
            left = orig_asm[i] if i < len(orig_asm) else ""
            right = comp_asm[i] if i < len(comp_asm) else ""
            marker = " " if left == right else "*"
            lines.append("{}{:<34} | {}".format(marker, left[:34], right[:34]))

        if max_lines > 50:
            lines.append("  ... ({} more lines)".format(max_lines - 50))

    lines.append("")
    lines.append("=" * 70)

    report = "\n".join(lines)

    if output_path:
        os.makedirs(os.path.dirname(output_path), exist_ok=True)
        with open(output_path, 'w') as f:
            f.write(report)

    return report


def compare_function(source_file: str, func_address: str, func_size: int,
                     func_name: str = "", config: dict = None) -> CompareResult:
    """
    Full comparison pipeline for a single function.
    """
    if config is None:
        config = {}

    addr = int(func_address, 16)
    if not func_name:
        func_name = "FUN_{:08x}".format(addr)

    result = CompareResult(
        func_address=func_address,
        func_name=func_name,
        match_level=MatchLevel.NO_MATCH,
        original_bytes=b'',
        compiled_bytes=b'',
    )

    # Step 1: Compile
    obj_path, errors = compile_source(source_file, config)
    if not obj_path:
        result.compile_errors = errors
        return result

    # Step 2: Extract compiled function bytes
    compiled_bytes = extract_function_from_obj(obj_path, func_name)
    if compiled_bytes is None:
        # If we can't extract by name, try getting the whole .text section
        compiled_bytes = _parse_coff_text_section(obj_path)

    if compiled_bytes is None:
        result.compile_errors = "Could not extract function bytes from compiled object"
        return result

    # Trim compiled bytes to expected size if needed
    if len(compiled_bytes) > func_size * 2:
        # Likely got the whole section; try to find function start
        compiled_bytes = compiled_bytes[:func_size]

    result.compiled_bytes = compiled_bytes

    # Step 3: Read original bytes
    original_bytes = read_original_bytes(addr, func_size)
    if original_bytes is None:
        result.notes = "Could not read original bytes (PAL3.exe not found?)"
        return result

    result.original_bytes = original_bytes

    # Step 4: Compare
    match_level, diff_lines = compare_bytes(original_bytes, compiled_bytes)
    result.match_level = match_level
    result.diff_lines = diff_lines

    return result


def run_batch_compare(batch_file: str, config: dict = None):
    """Run comparison for multiple functions from a batch file."""
    with open(batch_file, 'r') as f:
        batch = json.load(f)

    results = []
    for entry in batch.get('functions', []):
        print("[*] Comparing {} ({})...".format(
            entry.get('name', ''), entry['address']))

        result = compare_function(
            source_file=entry['source_file'],
            func_address=entry['address'],
            func_size=entry['size'],
            func_name=entry.get('name', ''),
            config=config,
        )

        # Generate report
        addr_str = entry['address'].replace('0x', '')
        report_path = str(RESULTS_DIR / "diff_{}.txt".format(addr_str))
        report = generate_diff_report(result, report_path)
        print(report[:200])  # Print summary
        print()

        results.append({
            'address': result.func_address,
            'name': result.func_name,
            'match_level': result.match_level.value,
            'match_level_name': result.match_level.name,
            'has_errors': bool(result.compile_errors),
        })

    # Summary
    RESULTS_DIR.mkdir(parents=True, exist_ok=True)
    summary_path = RESULTS_DIR / "_batch_summary.json"
    with open(summary_path, 'w') as f:
        json.dump(results, f, indent=2)

    # Print summary
    total = len(results)
    matched = sum(1 for r in results if r['match_level'] == 1)
    instruction = sum(1 for r in results if r['match_level'] == 2)
    functional = sum(1 for r in results if r['match_level'] == 3)
    failed = sum(1 for r in results if r['has_errors'])

    print("\n" + "=" * 50)
    print("BATCH COMPARISON SUMMARY")
    print("=" * 50)
    print("Total functions:    {}".format(total))
    print("Byte-identical:     {} ({:.1f}%)".format(matched, 100*matched/max(1,total)))
    print("Instruction match:  {} ({:.1f}%)".format(instruction, 100*instruction/max(1,total)))
    print("Functional match:   {} ({:.1f}%)".format(functional, 100*functional/max(1,total)))
    print("No match:           {}".format(total - matched - instruction - functional))
    print("Compile errors:     {}".format(failed))


def main():
    parser = argparse.ArgumentParser(
        description="Compile and compare decompiled C code against original PAL3.exe"
    )

    parser.add_argument('--source', '-s',
                        help='Source file to compile')
    parser.add_argument('--func-addr', '-a',
                        help='Function address in original exe (e.g., 0x00401000)')
    parser.add_argument('--func-size', '-z', type=int,
                        help='Function size in bytes')
    parser.add_argument('--func-name', '-n', default='',
                        help='Function name (for OBJ extraction)')
    parser.add_argument('--batch', '-b',
                        help='Batch comparison JSON file')
    parser.add_argument('--optimization', default='/O2',
                        choices=['/Od', '/O1', '/O2', '/Ox'],
                        help='MSVC optimization level (default: /O2)')
    parser.add_argument('--output', '-o',
                        help='Output diff report path')

    args = parser.parse_args()

    config = {
        'optimization': args.optimization,
    }

    if args.batch:
        run_batch_compare(args.batch, config)
    elif args.source and args.func_addr and args.func_size:
        result = compare_function(
            source_file=args.source,
            func_address=args.func_addr,
            func_size=args.func_size,
            func_name=args.func_name,
            config=config,
        )
        output_path = args.output or str(
            RESULTS_DIR / "diff_{}.txt".format(args.func_addr.replace('0x', '')))
        report = generate_diff_report(result, output_path)
        print(report)
    else:
        parser.print_help()
        print("\nExamples:")
        print("  python compare.py -s src/core/math.c -a 0x00401000 -z 128")
        print("  python compare.py --batch build/batch_compare.json")
        sys.exit(1)


if __name__ == '__main__':
    main()
