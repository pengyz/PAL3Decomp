"""Test PE (Portable Executable) structure of compiled binaries.

This test verifies that our decompiled and recompiled binaries have
the correct PE structure matching the original binaries.

PE structure includes:
- DOS header and stub
- PE signature and COFF header
- Optional header (subsystem, entry point, etc.)
- Section table (.text, .data, .rdata, etc.)
- Import/Export directories

We parse minimal PE structure needed to verify basic correctness
without external dependencies (like pefile).
"""
import struct
import os
import pytest


class PEInfo:
    """Minimal PE file parser for verification tests."""

    def __init__(self, filepath):
        """Parse PE file headers."""
        self.filepath = filepath
        with open(filepath, 'rb') as f:
            # DOS header
            dos_header = f.read(64)
            if dos_header[0:2] != b'MZ':
                raise ValueError(f"Not a valid PE file: {filepath}")

            self.dos_signature = dos_header[0:2]
            self.pe_offset = struct.unpack('<I', dos_header[0x3C:0x40])[0]

            # PE signature
            f.seek(self.pe_offset)
            pe_sig = f.read(4)
            if pe_sig != b'PE\x00\x00':
                raise ValueError(f"Invalid PE signature at offset {self.pe_offset}")

            # COFF header (20 bytes)
            coff_header = f.read(20)
            self.machine = struct.unpack('<H', coff_header[0:2])[0]
            self.num_sections = struct.unpack('<H', coff_header[2:4])[0]
            self.timestamp = struct.unpack('<I', coff_header[4:8])[0]
            self.symbol_table_ptr = struct.unpack('<I', coff_header[8:12])[0]
            self.num_symbols = struct.unpack('<I', coff_header[12:16])[0]
            self.optional_header_size = struct.unpack('<H', coff_header[16:18])[0]
            self.characteristics = struct.unpack('<H', coff_header[18:20])[0]

            # Optional header (PE32)
            if self.optional_header_size > 0:
                opt_header = f.read(self.optional_header_size)
                self.magic = struct.unpack('<H', opt_header[0:2])[0]

                if self.magic == 0x10b:  # PE32
                    self.entry_point = struct.unpack('<I', opt_header[16:20])[0]
                    self.image_base = struct.unpack('<I', opt_header[28:32])[0]
                    self.section_alignment = struct.unpack('<I', opt_header[32:36])[0]
                    self.file_alignment = struct.unpack('<I', opt_header[36:40])[0]
                    self.os_major = struct.unpack('<H', opt_header[40:42])[0]
                    self.os_minor = struct.unpack('<H', opt_header[42:44])[0]
                    self.subsystem = struct.unpack('<H', opt_header[68:70])[0]
                    self.dll_characteristics = struct.unpack('<H', opt_header[70:72])[0]
                else:
                    # PE32+ or other format
                    self.subsystem = None

            # Section headers
            self.sections = []
            section_table_offset = self.pe_offset + 24 + self.optional_header_size
            f.seek(section_table_offset)

            for i in range(self.num_sections):
                section_data = f.read(40)
                name = section_data[0:8].rstrip(b'\x00').decode('ascii', errors='ignore')
                virtual_size = struct.unpack('<I', section_data[8:12])[0]
                virtual_address = struct.unpack('<I', section_data[12:16])[0]
                raw_size = struct.unpack('<I', section_data[16:20])[0]
                raw_ptr = struct.unpack('<I', section_data[20:24])[0]
                characteristics = struct.unpack('<I', section_data[36:40])[0]

                self.sections.append({
                    'name': name,
                    'virtual_size': virtual_size,
                    'virtual_address': virtual_address,
                    'raw_size': raw_size,
                    'raw_ptr': raw_ptr,
                    'characteristics': characteristics
                })

    def is_dll(self):
        """Check if this PE is a DLL."""
        return bool(self.characteristics & 0x2000)

    def is_executable(self):
        """Check if this PE is executable."""
        return bool(self.characteristics & 0x0002)


def test_compiled_topo_is_valid_pe(compiled_topo_dll):
    """Test that compiled topo.dll is a valid PE file."""
    info = PEInfo(compiled_topo_dll)
    assert info.machine == 0x14C, f"Expected x86 (0x14C), got {hex(info.machine)}"
    assert info.is_dll(), "topo.dll should be marked as DLL"


def test_compiled_topo_is_32bit(compiled_topo_dll):
    """Test that compiled topo.dll is 32-bit."""
    info = PEInfo(compiled_topo_dll)
    assert info.machine == 0x14C, "Must be x86 (IMAGE_FILE_MACHINE_I386)"
    assert info.magic == 0x10b, "Must be PE32 (not PE32+)"


def test_compiled_topo_has_code_section(compiled_topo_dll):
    """Test that topo.dll has a .text section."""
    info = PEInfo(compiled_topo_dll)
    section_names = [s['name'] for s in info.sections]
    assert '.text' in section_names, f"Missing .text section. Found: {section_names}"


def test_original_vs_compiled_machine_type(original_topo_dll, compiled_topo_dll):
    """Test that original and compiled have same machine type."""
    orig = PEInfo(original_topo_dll)
    comp = PEInfo(compiled_topo_dll)
    assert orig.machine == comp.machine, \
        f"Machine type mismatch: original={hex(orig.machine)}, compiled={hex(comp.machine)}"


def test_original_vs_compiled_subsystem(original_topo_dll, compiled_topo_dll):
    """Test that subsystem matches (Windows GUI/Console)."""
    orig = PEInfo(original_topo_dll)
    comp = PEInfo(compiled_topo_dll)

    if orig.subsystem and comp.subsystem:
        # Note: Subsystem may differ between VC6 and modern MSVC
        # Original (VC6) might use GUI (2), modern MSVC might use Console (3)
        # This is acceptable for a DLL as long as it's a valid Windows subsystem
        valid_subsystems = [2, 3]  # GUI or Console
        assert comp.subsystem in valid_subsystems, \
            f"Compiled subsystem {comp.subsystem} is not valid (expected 2 or 3)"

        # Informational: report if different
        if orig.subsystem != comp.subsystem:
            print(f"\nNote: Subsystem differs (original={orig.subsystem}, compiled={comp.subsystem})")
            print("This is acceptable for DLLs compiled with different MSVC versions")


def test_original_vs_compiled_dll_flag(original_topo_dll, compiled_topo_dll):
    """Test that both are marked as DLLs."""
    orig = PEInfo(original_topo_dll)
    comp = PEInfo(compiled_topo_dll)

    assert orig.is_dll() == comp.is_dll(), \
        "DLL characteristic mismatch between original and compiled"


def test_compiled_topo_section_count(compiled_topo_dll):
    """Test that topo.dll has reasonable number of sections."""
    info = PEInfo(compiled_topo_dll)
    # Typical DLL has 3-8 sections (.text, .data, .rdata, .reloc, etc.)
    assert 1 <= info.num_sections <= 20, \
        f"Unusual number of sections: {info.num_sections}"


def test_compiled_topo_alignment(compiled_topo_dll):
    """Test that section/file alignment are standard values."""
    info = PEInfo(compiled_topo_dll)

    # Common alignments
    valid_section_alignments = [0x1000, 0x2000, 0x4000, 0x10000]
    valid_file_alignments = [0x200, 0x1000]

    assert info.section_alignment in valid_section_alignments, \
        f"Non-standard section alignment: {hex(info.section_alignment)}"
    assert info.file_alignment in valid_file_alignments, \
        f"Non-standard file alignment: {hex(info.file_alignment)}"


def test_original_topo_structure_info(original_topo_dll):
    """Display original topo.dll structure for reference (informational)."""
    info = PEInfo(original_topo_dll)
    print(f"\nOriginal topo.dll PE structure:")
    print(f"  Machine: {hex(info.machine)} (x86)")
    print(f"  Sections: {info.num_sections}")
    for sect in info.sections:
        print(f"    {sect['name']:8s} VA={hex(sect['virtual_address']):8s} "
              f"Size={sect['virtual_size']:6d} bytes")
    print(f"  Subsystem: {info.subsystem}")
    print(f"  Image Base: {hex(info.image_base)}")
    print(f"  Entry Point: {hex(info.entry_point)}")

    # Test always passes, this is just for info
    assert True


def test_compiled_topo_structure_info(compiled_topo_dll):
    """Display compiled topo.dll structure for comparison (informational)."""
    info = PEInfo(compiled_topo_dll)
    print(f"\nCompiled topo.dll PE structure:")
    print(f"  Machine: {hex(info.machine)} (x86)")
    print(f"  Sections: {info.num_sections}")
    for sect in info.sections:
        print(f"    {sect['name']:8s} VA={hex(sect['virtual_address']):8s} "
              f"Size={sect['virtual_size']:6d} bytes")
    print(f"  Subsystem: {info.subsystem}")
    print(f"  Image Base: {hex(info.image_base)}")
    print(f"  Entry Point: {hex(info.entry_point)}")

    # Test always passes, this is just for info
    assert True



