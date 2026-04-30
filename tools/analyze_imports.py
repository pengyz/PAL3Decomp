#!/usr/bin/env python3
"""
PE Import Table Analyzer for PAL3.

Parses the import directory of PAL3.exe to:
1. List all imported DLLs and their functions
2. Identify DirectX version (D3D8 vs D3D9)
3. Detect game middleware (Bink, Miles, etc.)
4. Generate stub header files for third-party libraries

Usage:
    python analyze_imports.py                      # Analyze and print report
    python analyze_imports.py --generate-stubs     # Also generate stub headers
    python analyze_imports.py --output imports.json # Save to file
"""

import argparse
import json
import struct
import sys
from collections import defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_EXE = PROJECT_ROOT / "original" / "PAL3.exe"
INCLUDE_DIR = PROJECT_ROOT / "include"
THIRD_PARTY_DIR = PROJECT_ROOT / "src" / "third_party"
BUILD_DIR = PROJECT_ROOT / "build"


def read_pe_imports(exe_path):
    """Parse the PE import directory table."""
    imports = {}  # dll_name -> [func_names]

    with open(exe_path, 'rb') as f:
        # DOS header
        f.seek(0x3C)
        pe_offset = struct.unpack('<I', f.read(4))[0]

        # PE signature
        f.seek(pe_offset)
        if f.read(4) != b'PE\x00\x00':
            return imports

        # COFF header
        f.read(2)  # Machine
        num_sections = struct.unpack('<H', f.read(2))[0]
        f.read(12)
        opt_header_size = struct.unpack('<H', f.read(2))[0]
        f.read(2)

        opt_start = f.tell()

        # Optional header - PE32
        magic = struct.unpack('<H', f.read(2))[0]
        if magic != 0x10B:
            print("Not PE32 format (magic: 0x{:04X})".format(magic))
            return imports

        f.read(26)  # Skip to ImageBase
        image_base = struct.unpack('<I', f.read(4))[0]
        f.read(4)  # SectionAlignment
        f.read(4)  # FileAlignment
        f.read(16)  # OS/Image/Subsystem versions
        f.read(4)  # Win32VersionValue
        f.read(8)  # SizeOfImage, SizeOfHeaders
        f.read(4)  # CheckSum
        f.read(4)  # Subsystem + DllCharacteristics
        f.read(16)  # Stack/Heap sizes
        f.read(4)  # LoaderFlags
        num_data_dirs = struct.unpack('<I', f.read(4))[0]

        # Data directory entries
        data_dirs = []
        for i in range(min(num_data_dirs, 16)):
            rva = struct.unpack('<I', f.read(4))[0]
            size = struct.unpack('<I', f.read(4))[0]
            data_dirs.append((rva, size))

        # Import directory is entry 1
        if len(data_dirs) < 2 or data_dirs[1][0] == 0:
            return imports

        import_rva = data_dirs[1][0]
        import_size = data_dirs[1][1]

        # Read section headers to build RVA->file offset map
        f.seek(opt_start + opt_header_size)
        sections = []
        for i in range(num_sections):
            name = f.read(8).rstrip(b'\x00').decode('ascii', errors='ignore')
            virt_size = struct.unpack('<I', f.read(4))[0]
            virt_addr = struct.unpack('<I', f.read(4))[0]
            raw_size = struct.unpack('<I', f.read(4))[0]
            raw_ptr = struct.unpack('<I', f.read(4))[0]
            f.read(16)
            sections.append({
                'name': name,
                'virt_addr': virt_addr,
                'virt_size': virt_size,
                'raw_ptr': raw_ptr,
                'raw_size': raw_size,
            })

        def rva_to_offset(rva):
            for sec in sections:
                if sec['virt_addr'] <= rva < sec['virt_addr'] + sec['virt_size']:
                    return sec['raw_ptr'] + (rva - sec['virt_addr'])
            return None

        def read_string_at_rva(rva):
            offset = rva_to_offset(rva)
            if offset is None:
                return ""
            f.seek(offset)
            chars = []
            while True:
                b = f.read(1)
                if not b or b == b'\x00':
                    break
                chars.append(b.decode('ascii', errors='ignore'))
            return ''.join(chars)

        # Parse import directory entries
        import_offset = rva_to_offset(import_rva)
        if import_offset is None:
            return imports

        f.seek(import_offset)
        while True:
            # IMAGE_IMPORT_DESCRIPTOR: 5 DWORDs
            ilt_rva = struct.unpack('<I', f.read(4))[0]      # OriginalFirstThunk
            timestamp = struct.unpack('<I', f.read(4))[0]
            forwarder = struct.unpack('<I', f.read(4))[0]
            name_rva = struct.unpack('<I', f.read(4))[0]
            iat_rva = struct.unpack('<I', f.read(4))[0]      # FirstThunk

            # Null entry marks end
            if name_rva == 0:
                break

            dll_name = read_string_at_rva(name_rva)
            if not dll_name:
                continue

            # Parse Import Lookup Table
            func_names = []
            lookup_rva = ilt_rva if ilt_rva else iat_rva
            if lookup_rva == 0:
                imports[dll_name] = func_names
                continue

            lookup_offset = rva_to_offset(lookup_rva)
            if lookup_offset is None:
                imports[dll_name] = func_names
                continue

            save_pos = f.tell()
            f.seek(lookup_offset)

            while True:
                entry = struct.unpack('<I', f.read(4))[0]
                if entry == 0:
                    break

                if entry & 0x80000000:
                    # Import by ordinal
                    ordinal = entry & 0xFFFF
                    func_names.append("Ordinal_{}".format(ordinal))
                else:
                    # Import by name
                    hint_rva = entry
                    hint_offset = rva_to_offset(hint_rva)
                    if hint_offset:
                        cur = f.tell()
                        f.seek(hint_offset)
                        hint = struct.unpack('<H', f.read(2))[0]
                        name = read_string_at_rva(hint_rva + 2)
                        func_names.append(name)
                        f.seek(cur)

            f.seek(save_pos)
            imports[dll_name] = func_names

    return imports


# Library identification rules
LIBRARY_PROFILES = {
    'DirectX 8 (Direct3D)': {
        'dlls': ['d3d8.dll'],
        'stub_header': 'pal3_d3d8.h',
        'description': 'Direct3D 8 rendering API',
    },
    'DirectX 9 (Direct3D)': {
        'dlls': ['d3d9.dll'],
        'stub_header': 'pal3_d3d9.h',
        'description': 'Direct3D 9 rendering API',
    },
    'DirectX (D3DX)': {
        'dlls': ['d3dx8.dll', 'd3dx9.dll', 'd3dx8d.dll', 'd3dx9d.dll',
                 'd3dx9_24.dll', 'd3dx9_25.dll', 'd3dx9_26.dll'],
        'stub_header': 'pal3_d3dx.h',
        'description': 'D3DX utility library',
    },
    'DirectInput': {
        'dlls': ['dinput.dll', 'dinput8.dll'],
        'stub_header': 'pal3_dinput.h',
        'description': 'DirectInput for keyboard/mouse/gamepad',
    },
    'DirectSound': {
        'dlls': ['dsound.dll'],
        'stub_header': 'pal3_dsound.h',
        'description': 'DirectSound audio API',
    },
    'Bink Video': {
        'dlls': ['binkw32.dll', 'bink32.dll'],
        'stub_header': 'pal3_bink.h',
        'description': 'Bink Video codec (RAD Game Tools)',
    },
    'Miles Sound System': {
        'dlls': ['mss32.dll', 'mss16.dll'],
        'stub_header': 'pal3_miles.h',
        'description': 'Miles Sound System (RAD Game Tools)',
    },
    'Windows Media': {
        'dlls': ['wmvcore.dll'],
        'stub_header': None,
        'description': 'Windows Media Video',
    },
    'MSVC Runtime': {
        'dlls': ['msvcrt.dll', 'msvcr70.dll', 'msvcr71.dll', 'msvcr80.dll',
                 'msvcp60.dll', 'msvcp70.dll', 'msvcp71.dll'],
        'stub_header': None,
        'description': 'Microsoft C/C++ Runtime',
    },
}


def identify_libraries(imports):
    """Match imported DLLs against known library profiles."""
    detected = {}
    import_dlls_lower = {k.lower(): k for k in imports.keys()}

    for lib_name, profile in LIBRARY_PROFILES.items():
        for dll in profile['dlls']:
            if dll.lower() in import_dlls_lower:
                actual_name = import_dlls_lower[dll.lower()]
                detected[lib_name] = {
                    'dll': actual_name,
                    'functions': imports[actual_name],
                    'function_count': len(imports[actual_name]),
                    'description': profile['description'],
                    'stub_header': profile.get('stub_header'),
                }
                break

    # Identify MSVC version from CRT DLL
    crt_version = "unknown"
    for dll in import_dlls_lower:
        if 'msvcr71' in dll or 'msvcp71' in dll:
            crt_version = "MSVC 7.1 (VS2003)"
        elif 'msvcr70' in dll or 'msvcp70' in dll:
            crt_version = "MSVC 7.0 (VS2002)"
        elif 'msvcr80' in dll or 'msvcp80' in dll:
            crt_version = "MSVC 8.0 (VS2005)"
        elif dll == 'msvcrt.dll':
            crt_version = "MSVC 6.0 or system CRT"

    return detected, crt_version


# Stub header templates for known libraries
STUB_TEMPLATES = {
    'pal3_bink.h': '''/**
 * Bink Video Stub Header
 * Auto-generated from PAL3.exe import table
 *
 * These are declarations for Bink Video SDK functions imported by PAL3.
 * The actual Bink SDK is proprietary (RAD Game Tools).
 * These stubs allow compilation without the real SDK headers.
 */

#ifndef PAL3_BINK_H
#define PAL3_BINK_H

#include <windows.h>

typedef struct BINK BINK;
typedef struct BINK *HBINK;

typedef struct {{
    s32 Width;
    s32 Height;
    s32 FrameNum;
    s32 Frames;
    u32 FrameRate;
    u32 FrameRateDiv;
}} BINKSUMMARY;

/* Bink API functions used by PAL3: */
{func_decls}

#endif /* PAL3_BINK_H */
''',

    'pal3_miles.h': '''/**
 * Miles Sound System Stub Header
 * Auto-generated from PAL3.exe import table
 */

#ifndef PAL3_MILES_H
#define PAL3_MILES_H

#include <windows.h>

typedef void *HDIGDRIVER;
typedef void *HSAMPLE;
typedef void *HSTREAM;
typedef void *HPROVIDER;

/* Miles API functions used by PAL3: */
{func_decls}

#endif /* PAL3_MILES_H */
''',
}


def generate_stub_header(lib_name, lib_info):
    """Generate a stub header for a detected library."""
    stub_file = lib_info.get('stub_header')
    if not stub_file:
        return None

    functions = lib_info.get('functions', [])

    # Generate function declarations
    decl_lines = []
    for func_name in sorted(functions):
        if func_name.startswith('Ordinal_'):
            decl_lines.append("/* {} (ordinal import) */".format(func_name))
        else:
            # Generic declaration - user should refine with actual signatures
            decl_lines.append(
                "/* TODO: verify signature */\n"
                "/* {} */".format(func_name))

    func_decls = "\n".join(decl_lines) if decl_lines else "/* No named imports */"

    # Use template if available, otherwise generic
    if stub_file in STUB_TEMPLATES:
        content = STUB_TEMPLATES[stub_file].format(func_decls=func_decls)
    else:
        guard = stub_file.upper().replace('.', '_').replace('-', '_')
        content = """/**
 * {lib_name} Stub Header
 * Auto-generated from PAL3.exe import table
 *
 * {description}
 * Functions listed below are imported by the original binary.
 * Replace stubs with actual SDK headers when available.
 */

#ifndef {guard}
#define {guard}

#include <windows.h>

/* Imported functions: */
{func_decls}

#endif /* {guard} */
""".format(
            lib_name=lib_name,
            description=lib_info.get('description', ''),
            guard=guard,
            func_decls=func_decls,
        )

    return content


def print_report(imports, detected_libs, crt_version):
    """Print analysis report."""
    print()
    print("=" * 65)
    print("  PAL3.exe Import Table Analysis")
    print("=" * 65)
    print()

    total_funcs = sum(len(funcs) for funcs in imports.values())
    print("  Total DLLs imported:   {}".format(len(imports)))
    print("  Total functions:       {}".format(total_funcs))
    print("  CRT Version detected:  {}".format(crt_version))
    print()

    # Detected libraries
    if detected_libs:
        print("  Detected Libraries:")
        print("  " + "-" * 55)
        for lib_name, info in detected_libs.items():
            print("    {:<25s} via {:<15s} ({} funcs)".format(
                lib_name, info['dll'], info['function_count']))
        print()

    # Full import listing
    print("  Import Details:")
    print("  " + "-" * 55)
    for dll_name in sorted(imports.keys(), key=str.lower):
        funcs = imports[dll_name]
        ordinals = sum(1 for f in funcs if f.startswith('Ordinal_'))
        named = len(funcs) - ordinals

        print("\n  {} ({} named, {} ordinals)".format(
            dll_name, named, ordinals))
        for func in sorted(funcs):
            print("    - {}".format(func))

    print()
    print("=" * 65)


def main():
    parser = argparse.ArgumentParser(
        description="Analyze PAL3.exe import table"
    )
    parser.add_argument('--exe', default=str(ORIGINAL_EXE),
                        help='Path to PAL3.exe')
    parser.add_argument('--generate-stubs', '-g', action='store_true',
                        help='Generate stub header files')
    parser.add_argument('--output', '-o',
                        help='Save analysis to JSON')

    args = parser.parse_args()

    exe_path = Path(args.exe)
    if not exe_path.exists():
        print("ERROR: {} not found".format(exe_path))
        print("Place PAL3.exe in original/ directory")
        sys.exit(1)

    # Parse imports
    imports = read_pe_imports(str(exe_path))
    if not imports:
        print("ERROR: Could not parse import table")
        sys.exit(1)

    # Identify libraries
    detected_libs, crt_version = identify_libraries(imports)

    # Print report
    print_report(imports, detected_libs, crt_version)

    # Generate stubs
    if args.generate_stubs:
        INCLUDE_DIR.mkdir(parents=True, exist_ok=True)
        print("\nGenerating stub headers:")
        for lib_name, info in detected_libs.items():
            if info.get('stub_header'):
                content = generate_stub_header(lib_name, info)
                if content:
                    path = INCLUDE_DIR / info['stub_header']
                    path.write_text(content)
                    print("  Created: {}".format(path))

    # Save JSON
    if args.output:
        result = {
            'imports': {k: v for k, v in imports.items()},
            'detected_libraries': detected_libs,
            'crt_version': crt_version,
            'total_dlls': len(imports),
            'total_functions': sum(len(v) for v in imports.values()),
        }
        with open(args.output, 'w') as f:
            json.dump(result, f, indent=2)
        print("\nSaved to: {}".format(args.output))
    else:
        # Auto-save to build/
        BUILD_DIR.mkdir(parents=True, exist_ok=True)
        result = {
            'imports': {k: v for k, v in imports.items()},
            'detected_libraries': {k: {kk: vv for kk, vv in v.items()}
                                   for k, v in detected_libs.items()},
            'crt_version': crt_version,
        }
        out_path = BUILD_DIR / "imports_analysis.json"
        with open(out_path, 'w') as f:
            json.dump(result, f, indent=2)
        print("\nAnalysis saved to: {}".format(out_path))


if __name__ == '__main__':
    main()
