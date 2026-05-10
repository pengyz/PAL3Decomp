#pragma once
// Auto-generated: _IMAGE_OPTIONAL_HEADER

#include "_IMAGE_DATA_DIRECTORY.h"

class _IMAGE_OPTIONAL_HEADER {
public:
    WORD Magic; // +0x0
    BYTE MajorLinkerVersion; // +0x2
    BYTE MinorLinkerVersion; // +0x3
    DWORD SizeOfCode; // +0x4
    DWORD SizeOfInitializedData; // +0x8
    DWORD SizeOfUninitializedData; // +0xC
    DWORD AddressOfEntryPoint; // +0x10
    DWORD BaseOfCode; // +0x14
    DWORD BaseOfData; // +0x18
    DWORD ImageBase; // +0x1C
    DWORD SectionAlignment; // +0x20
    DWORD FileAlignment; // +0x24
    WORD MajorOperatingSystemVersion; // +0x28
    WORD MinorOperatingSystemVersion; // +0x2A
    WORD MajorImageVersion; // +0x2C
    WORD MinorImageVersion; // +0x2E
    WORD MajorSubsystemVersion; // +0x30
    WORD MinorSubsystemVersion; // +0x32
    DWORD Win32VersionValue; // +0x34
    DWORD SizeOfImage; // +0x38
    DWORD SizeOfHeaders; // +0x3C
    DWORD CheckSum; // +0x40
    WORD Subsystem; // +0x44
    WORD DllCharacteristics; // +0x46
    DWORD SizeOfStackReserve; // +0x48
    DWORD SizeOfStackCommit; // +0x4C
    DWORD SizeOfHeapReserve; // +0x50
    DWORD SizeOfHeapCommit; // +0x54
    DWORD LoaderFlags; // +0x58
    DWORD NumberOfRvaAndSizes; // +0x5C
    _IMAGE_DATA_DIRECTORY DataDirectory[16]; // +0x60
    // total size: 0xE0 (224)

};
