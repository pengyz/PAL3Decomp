#!/usr/bin/env python3
"""Generate a correct mss32.lib import library with IMPORT_NAME type.

MSVC's LIB.EXE uses IMPORT_NAME_UNDECORATE for stdcall functions, which
strips the leading _ and @N from the import name. But Mss32.dll exports
functions WITH stdcall decoration (_AIL_xxx@N), so we need IMPORT_NAME
type (use symbol name as-is for DLL lookup).
"""
import struct
import subprocess
import re
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
DUMPBIN = r"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\bin\Hostx86\x86\dumpbin.exe"


def create_short_import(symbol_name, dll_name, hint=0, name_type=1):
    """Create a short import archive member.
    name_type: 0=IMPORT_ORDINAL, 1=IMPORT_NAME, 2=IMPORT_NAME_NOPREFIX, 3=IMPORT_NAME_UNDECORATE
    """
    type_field = 0 | (name_type << 2)  # IMPORT_CODE + name_type
    data = symbol_name.encode('ascii') + b'\x00' + dll_name.encode('ascii') + b'\x00'
    header = struct.pack('<HH', 0x0000, 0xFFFF)
    header += struct.pack('<HH', 0, 0x14C)
    header += struct.pack('<I', 0)
    header += struct.pack('<I', len(data))
    header += struct.pack('<H', hint)
    header += struct.pack('<H', type_field)
    return header + data


def ar_header(name, size):
    h = name.encode('ascii').ljust(16, b' ')
    h += b'0           '
    h += b'0     '
    h += b'0     '
    h += b'100666  '
    h += str(size).encode('ascii').ljust(10, b' ')
    h += b'\x60\x0a'
    assert len(h) == 60
    return h


def create_archive(members):
    """Create a COFF archive (.lib) with proper linker members."""
    AR_SIG = b'!<arch>\n'
    AR_HEADER_SIZE = 60

    # Collect symbols: each import member provides _name and __imp__name
    all_symbols = []
    for i, (name, data) in enumerate(members):
        sym_end = data[20:].index(b'\x00')
        sym_name = data[20:20+sym_end].decode('ascii')
        all_symbols.append((sym_name, i))
        all_symbols.append(('__imp_' + sym_name, i))

    num_syms = len(all_symbols)
    num_members = len(members)

    # Build first linker member data (big-endian offsets, placeholder)
    sym_names_blob = b''
    for sn, _ in all_symbols:
        sym_names_blob += sn.encode('ascii') + b'\x00'
    first_data_template = struct.pack('>I', num_syms) + b'\x00\x00\x00\x00' * num_syms + sym_names_blob
    if len(first_data_template) % 2:
        first_data_template += b'\n'

    # Build second linker member data (little-endian, placeholder)
    sorted_indices = sorted(range(num_syms), key=lambda i: all_symbols[i][0].lower())
    second_data_template = struct.pack('<I', num_members)
    second_data_template += b'\x00\x00\x00\x00' * num_members
    second_data_template += struct.pack('<I', num_syms)
    for si in sorted_indices:
        second_data_template += struct.pack('<H', all_symbols[si][1] + 1)
    for si in sorted_indices:
        second_data_template += all_symbols[si][0].encode('ascii') + b'\x00'
    if len(second_data_template) % 2:
        second_data_template += b'\n'

    # Calculate member offsets
    offset = len(AR_SIG)
    first_offset = offset
    offset += AR_HEADER_SIZE + len(first_data_template)
    second_offset = offset
    offset += AR_HEADER_SIZE + len(second_data_template)

    member_offsets = []
    for name, data in members:
        member_offsets.append(offset)
        padded = len(data) + (len(data) % 2)
        offset += AR_HEADER_SIZE + padded

    # Fix first linker member (big-endian offsets)
    first_data = struct.pack('>I', num_syms)
    for sym_name, mem_idx in all_symbols:
        first_data += struct.pack('>I', member_offsets[mem_idx])
    first_data += sym_names_blob
    if len(first_data) % 2:
        first_data += b'\n'

    # Fix second linker member (little-endian)
    second_data = struct.pack('<I', num_members)
    for mo in member_offsets:
        second_data += struct.pack('<I', mo)
    second_data += struct.pack('<I', num_syms)
    for si in sorted_indices:
        second_data += struct.pack('<H', all_symbols[si][1] + 1)
    for si in sorted_indices:
        second_data += all_symbols[si][0].encode('ascii') + b'\x00'
    if len(second_data) % 2:
        second_data += b'\n'

    # Assemble archive
    output = bytearray(AR_SIG)
    output += ar_header('/', len(first_data))
    output += first_data
    output += ar_header('/', len(second_data))
    output += second_data
    for name, data in members:
        padded_data = data + (b'\n' if len(data) % 2 else b'')
        output += ar_header(name, len(data))
        output += padded_data

    return bytes(output)


def main():
    mss_dll = Path(r"E:\Program Files (x86)\Steam\steamapps\common\PAL3\Mss32.dll")
    if not mss_dll.exists():
        mss_dll = PROJECT_ROOT / "original" / "Mss32.dll"

    output_lib = PROJECT_ROOT / "tools" / "vc6" / "Lib" / "mss32.lib"

    # Get exports from Mss32.dll
    result = subprocess.run([DUMPBIN, '/EXPORTS', str(mss_dll)],
                          capture_output=True, text=True)

    members = []
    for line in result.stdout.split('\n'):
        m = re.match(r'\s+(\d+)\s+([0-9A-Fa-f]+)\s+[0-9A-Fa-f]+\s+(_\w+@\d+)', line)
        if m:
            hint = int(m.group(2), 16)
            export_name = m.group(3)
            data = create_short_import(export_name, 'Mss32.dll', hint=hint, name_type=1)
            members.append((export_name[:15], data))

    lib_data = create_archive(members)
    with open(output_lib, 'wb') as f:
        f.write(lib_data)

    print(f"Created {output_lib}")
    print(f"  {len(members)} import entries, {len(lib_data)} bytes")


if __name__ == '__main__':
    main()
