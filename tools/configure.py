#!/usr/bin/env python3
"""
Configuration and setup script for PAL3 decompilation project.

This script helps set up the development environment and verify
that all required tools are available.

Usage:
    python configure.py check       # Check environment
    python configure.py init        # Initialize project (first time)
    python configure.py pe-info     # Analyze PAL3.exe PE headers
"""

import argparse
import json
import os
import struct
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
BUILD_DIR = PROJECT_ROOT / "build"
CONFIG_FILE = BUILD_DIR / "project_config.json"

# 添加 tools 目录到模块搜索路径
sys.path.insert(0, str(Path(__file__).parent))
from project_config import get_exe_path, require_exe_path


def check_tool(name, cmd, expected_in_output=""):
    """Check if a tool is available."""
    try:
        result = subprocess.run(
            cmd, capture_output=True, text=True, timeout=10)
        output = result.stdout + result.stderr
        if expected_in_output:
            found = expected_in_output.lower() in output.lower()
        else:
            found = result.returncode == 0
        return found, output[:200]
    except FileNotFoundError:
        return False, "Not found in PATH"
    except subprocess.TimeoutExpired:
        return False, "Timed out"
    except Exception as e:
        return False, str(e)


def check_environment():
    """Check all required tools and files."""
    print("PAL3 Decompilation - Environment Check")
    print("=" * 50)
    print()

    all_ok = True

    # Required tools
    tools = [
        ("Python 3.8+", ['python', '--version'], "3."),
        ("MSVC (cl.exe)", ['cl'], "Microsoft"),
        ("Ghidra (analyzeHeadless)", ['analyzeHeadless', '--help'], ""),
        ("Git", ['git', '--version'], "git version"),
    ]

    # Optional tools
    optional_tools = [
        ("ndisasm (NASM)", ['ndisasm', '--version'], ""),
        ("dumpbin (MSVC)", ['dumpbin', '/headers', '/nologo'], ""),
        ("anthropic (Python)", ['python', '-c', 'import anthropic; print("OK")'], "OK"),
    ]

    print("Required Tools:")
    print("-" * 50)
    for name, cmd, expected in tools:
        found, info = check_tool(name, cmd, expected)
        status = "OK" if found else "MISSING"
        icon = "+" if found else "!"
        print("  [{}] {:<30s} {}".format(icon, name, status))
        if not found:
            all_ok = False
            print("      {}".format(info[:60]))

    print()
    print("Optional Tools:")
    print("-" * 50)
    for name, cmd, expected in optional_tools:
        found, info = check_tool(name, cmd, expected)
        status = "OK" if found else "not found"
        icon = "+" if found else "-"
        print("  [{}] {:<30s} {}".format(icon, name, status))

    print()
    print("Project Files:")
    print("-" * 50)

    # Check original exe
    exe_path = get_exe_path()
    if exe_path is None:
        # 向后兼容
        fallback = PROJECT_ROOT / "original" / "PAL3.exe"
        if fallback.exists():
            exe_path = fallback
    if exe_path and exe_path.exists():
        size = exe_path.stat().st_size
        print("  [+] PAL3.exe found ({:,} bytes)".format(size))
        print("      {}".format(exe_path))
    else:
        print("  [!] PAL3.exe NOT FOUND")
        print("      配置方法: 编辑 local_config.json 设置 game_dir")
        all_ok = False

    # Check directory structure
    expected_dirs = ['src/core', 'src/game', 'src/script', 'include', 'tools', 'asm']
    for d in expected_dirs:
        path = PROJECT_ROOT / d
        if path.exists():
            print("  [+] {}/".format(d))
        else:
            print("  [-] {}/ (will create)".format(d))

    print()
    if all_ok:
        print("Environment OK. Ready to start decompilation.")
    else:
        print("Some requirements are missing. See above for details.")

    return all_ok


def parse_rich_header(exe_path: str) -> dict:
    """Parse the PE Rich Header to identify compiler/linker versions."""
    info = {
        'compiler_versions': [],
        'linker_version': '',
        'build_tools': [],
    }

    try:
        with open(exe_path, 'rb') as f:
            data = f.read(0x400)  # Rich header is in first 1KB

        # Find "Rich" signature
        rich_offset = data.find(b'Rich')
        if rich_offset < 0:
            info['notes'] = "No Rich header found (may be stripped)"
            return info

        # XOR key is the DWORD after "Rich"
        xor_key = struct.unpack_from('<I', data, rich_offset + 4)[0]

        # Find "DanS" signature (start of Rich header, encrypted)
        dans_encrypted = struct.pack('<I', 0x536E6144 ^ xor_key)  # "DanS" XORed
        dans_offset = data.find(dans_encrypted)
        if dans_offset < 0:
            info['notes'] = "Could not find DanS signature"
            return info

        # Decrypt and parse entries
        # Each entry is 8 bytes: [comp_id (2) + build_num (2)] [count (4)]
        entries_start = dans_offset + 16  # Skip DanS + 3 padding DWORDs
        entries_end = rich_offset

        # Known MSVC compiler IDs
        compiler_ids = {
            0x00: "Unknown/Import",
            0x01: "Import",
            0x02: "Linker",
            0x04: "MSVC 6.0 (C)",
            0x05: "MSVC 6.0 (C++)",
            0x06: "MSVC 6.0 (Linker)",
            0x0A: "MSVC 7.0 (C)",
            0x0B: "MSVC 7.0 (C++)",
            0x0C: "MSVC 7.0 (MASM)",
            0x0D: "MSVC 7.0 (Linker)",
            0x0E: "MSVC 7.0 (Resource)",
            0x0F: "MSVC 7.1 (C)",         # VS2003
            0x10: "MSVC 7.1 (C++)",        # VS2003
            0x11: "MSVC 7.1 (MASM)",       # VS2003
            0x12: "MSVC 7.1 (Linker)",     # VS2003
            0x13: "MSVC 7.1 (Resource)",   # VS2003
            0x14: "MSVC 8.0 (C)",          # VS2005
            0x15: "MSVC 8.0 (C++)",        # VS2005
            0x19: "MSVC 9.0 (C)",          # VS2008
            0x1A: "MSVC 9.0 (C++)",        # VS2008
        }

        for offset in range(entries_start, entries_end, 8):
            if offset + 8 > len(data):
                break

            dword1 = struct.unpack_from('<I', data, offset)[0] ^ xor_key
            dword2 = struct.unpack_from('<I', data, offset + 4)[0] ^ xor_key

            comp_id = (dword1 >> 16) & 0xFFFF
            build_num = dword1 & 0xFFFF
            count = dword2

            if comp_id == 0 and build_num == 0:
                continue

            tool_name = compiler_ids.get(comp_id, "Tool ID 0x{:02X}".format(comp_id))
            entry = {
                'tool_id': comp_id,
                'tool_name': tool_name,
                'build_number': build_num,
                'count': count,
            }
            info['build_tools'].append(entry)

            # Identify main compiler
            if comp_id in (0x04, 0x05, 0x0A, 0x0B, 0x0F, 0x10, 0x14, 0x15, 0x19, 0x1A):
                info['compiler_versions'].append(tool_name)

    except Exception as e:
        info['error'] = str(e)

    return info


def parse_pe_info(exe_path: str) -> dict:
    """Parse basic PE information from the executable."""
    info = {
        'image_base': 0,
        'entry_point': 0,
        'sections': [],
        'imports': [],
        'linker_version': '',
        'text_size': 0,
    }

    try:
        with open(exe_path, 'rb') as f:
            # DOS header
            f.seek(0x3C)
            pe_offset = struct.unpack('<I', f.read(4))[0]

            # PE signature
            f.seek(pe_offset)
            sig = f.read(4)
            if sig != b'PE\x00\x00':
                info['error'] = "Not a valid PE file"
                return info

            # COFF header
            machine = struct.unpack('<H', f.read(2))[0]
            num_sections = struct.unpack('<H', f.read(2))[0]
            timestamp = struct.unpack('<I', f.read(4))[0]
            f.read(4)  # PointerToSymbolTable
            f.read(4)  # NumberOfSymbols
            opt_header_size = struct.unpack('<H', f.read(2))[0]
            characteristics = struct.unpack('<H', f.read(2))[0]

            info['machine'] = "i386" if machine == 0x14c else "x86_64" if machine == 0x8664 else hex(machine)
            info['timestamp'] = timestamp

            # Optional header
            opt_magic = struct.unpack('<H', f.read(2))[0]
            linker_major = struct.unpack('<B', f.read(1))[0]
            linker_minor = struct.unpack('<B', f.read(1))[0]
            info['linker_version'] = "{}.{}".format(linker_major, linker_minor)

            size_of_code = struct.unpack('<I', f.read(4))[0]
            f.read(8)  # SizeOfInitializedData, SizeOfUninitializedData
            entry_point = struct.unpack('<I', f.read(4))[0]
            f.read(4)  # BaseOfCode

            if opt_magic == 0x10b:  # PE32
                f.read(4)  # BaseOfData
                image_base = struct.unpack('<I', f.read(4))[0]
            else:
                image_base = struct.unpack('<Q', f.read(8))[0]

            info['image_base'] = "0x{:08X}".format(image_base)
            info['entry_point'] = "0x{:08X}".format(image_base + entry_point)
            info['size_of_code'] = size_of_code

            # Skip to section headers
            f.seek(pe_offset + 24 + opt_header_size)

            # Read sections
            for i in range(num_sections):
                name = f.read(8).rstrip(b'\x00').decode('ascii', errors='ignore')
                virtual_size = struct.unpack('<I', f.read(4))[0]
                virtual_addr = struct.unpack('<I', f.read(4))[0]
                raw_size = struct.unpack('<I', f.read(4))[0]
                raw_ptr = struct.unpack('<I', f.read(4))[0]
                f.read(12)  # Relocations, linenums
                flags = struct.unpack('<I', f.read(4))[0]

                section = {
                    'name': name,
                    'virtual_size': virtual_size,
                    'virtual_address': "0x{:08X}".format(image_base + virtual_addr),
                    'raw_size': raw_size,
                    'flags': "0x{:08X}".format(flags),
                }
                info['sections'].append(section)

                if name == '.text':
                    info['text_size'] = virtual_size

    except Exception as e:
        info['error'] = str(e)

    return info


def analyze_exe():
    """Analyze PAL3.exe and display information."""
    exe_path = get_exe_path()
    if exe_path is None:
        # 向后兼容：也检查 original/ 目录
        fallback = PROJECT_ROOT / "original" / "PAL3.exe"
        if fallback.exists():
            exe_path = fallback
        else:
            exe_path = require_exe_path()  # 会打印错误并退出

    print("Analyzing {}...".format(exe_path))
    print("=" * 60)

    # PE info
    pe_info = parse_pe_info(str(exe_path))
    print("\nPE Header Information:")
    print("-" * 40)
    print("  Machine:       {}".format(pe_info.get('machine', '?')))
    print("  Image Base:    {}".format(pe_info.get('image_base', '?')))
    print("  Entry Point:   {}".format(pe_info.get('entry_point', '?')))
    print("  Linker:        {}".format(pe_info.get('linker_version', '?')))
    print("  Code Size:     {:,} bytes".format(pe_info.get('size_of_code', 0)))

    print("\nSections:")
    print("  {:<10s} {:>12s} {:>14s} {:>12s}".format(
        "Name", "VirtSize", "VirtAddr", "RawSize"))
    for sec in pe_info.get('sections', []):
        print("  {:<10s} {:>12,d} {:>14s} {:>12,d}".format(
            sec['name'], sec['virtual_size'],
            sec['virtual_address'], sec['raw_size']))

    # Rich header
    print("\nRich Header (Compiler Detection):")
    print("-" * 40)
    rich_info = parse_rich_header(str(exe_path))

    if rich_info.get('error'):
        print("  Error: {}".format(rich_info['error']))
    elif rich_info.get('notes'):
        print("  {}".format(rich_info['notes']))
    else:
        for entry in rich_info.get('build_tools', []):
            print("  {:35s} build {:5d}  (x{})".format(
                entry['tool_name'], entry['build_number'], entry['count']))

        if rich_info.get('compiler_versions'):
            print("\n  Detected compiler(s): {}".format(
                ", ".join(set(rich_info['compiler_versions']))))

    # Save results
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    results = {
        'pe_info': pe_info,
        'rich_header': rich_info,
        'file_size': exe_path.stat().st_size,
    }
    results_path = BUILD_DIR / "exe_analysis.json"
    with open(results_path, 'w') as f:
        json.dump(results, f, indent=2, default=str)
    print("\nFull analysis saved to: {}".format(results_path))

    # Update project config
    config_path = CONFIG_FILE
    config = {}
    if config_path.exists():
        with open(config_path) as f:
            config = json.load(f)
    config['text_section_size'] = pe_info.get('text_size', 0)
    config['image_base'] = pe_info.get('image_base', '')
    config['entry_point'] = pe_info.get('entry_point', '')
    config['linker_version'] = pe_info.get('linker_version', '')
    with open(config_path, 'w') as f:
        json.dump(config, f, indent=2)


def init_project():
    """Initialize project for first-time setup."""
    print("Initializing PAL3 decompilation project...")
    print()

    # Create directories
    dirs = [
        'original', 'src/core', 'src/game', 'src/script', 'src/third_party',
        'include', 'tools', 'asm', 'build', 'docs'
    ]
    for d in dirs:
        path = PROJECT_ROOT / d
        path.mkdir(parents=True, exist_ok=True)
        print("  Created: {}/".format(d))

    # Create placeholder files
    placeholder_files = {
        'src/core/.gitkeep': '',
        'src/game/.gitkeep': '',
        'src/script/.gitkeep': '',
        'src/third_party/.gitkeep': '',
        'include/.gitkeep': '',
        'asm/.gitkeep': '',
    }
    for path, content in placeholder_files.items():
        filepath = PROJECT_ROOT / path
        if not filepath.exists():
            filepath.write_text(content)

    print()
    print("Next steps:")
    print("  1. Place PAL3.exe in original/")
    print("  2. Run: python tools/configure.py pe-info")
    print("  3. Set up Ghidra project and import PAL3.exe")
    print("  4. Run: analyzeHeadless ... -postScript ghidra_export.py --list-only")
    print("  5. Start decompiling with: python tools/ai_decompile.py process -f <json>")


def main():
    parser = argparse.ArgumentParser(
        description="PAL3 Decompilation Project Configuration"
    )
    subparsers = parser.add_subparsers(dest='command')

    subparsers.add_parser('check', help='Check environment and tools')
    subparsers.add_parser('init', help='Initialize project (first time)')
    subparsers.add_parser('pe-info', help='Analyze PAL3.exe PE headers')

    args = parser.parse_args()

    if args.command == 'check':
        check_environment()
    elif args.command == 'init':
        init_project()
    elif args.command == 'pe-info':
        analyze_exe()
    else:
        parser.print_help()
        print("\nQuick start:")
        print("  python configure.py init      # First time setup")
        print("  python configure.py check     # Verify environment")
        print("  python configure.py pe-info   # Analyze PAL3.exe")


if __name__ == '__main__':
    main()
