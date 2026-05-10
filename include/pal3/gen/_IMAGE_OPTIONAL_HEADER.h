#pragma once
// Auto-generated: _IMAGE_OPTIONAL_HEADER

#include "_IMAGE_DATA_DIRECTORY.h"

class _IMAGE_OPTIONAL_HEADER {
public:
    unsigned short Magic; // +0x0
    unsigned char MajorLinkerVersion; // +0x2
    unsigned char MinorLinkerVersion; // +0x3
    unsigned long SizeOfCode; // +0x4
    unsigned long SizeOfInitializedData; // +0x8
    unsigned long SizeOfUninitializedData; // +0xC
    unsigned long AddressOfEntryPoint; // +0x10
    unsigned long BaseOfCode; // +0x14
    unsigned long BaseOfData; // +0x18
    unsigned long ImageBase; // +0x1C
    unsigned long SectionAlignment; // +0x20
    unsigned long FileAlignment; // +0x24
    unsigned short MajorOperatingSystemVersion; // +0x28
    unsigned short MinorOperatingSystemVersion; // +0x2A
    unsigned short MajorImageVersion; // +0x2C
    unsigned short MinorImageVersion; // +0x2E
    unsigned short MajorSubsystemVersion; // +0x30
    unsigned short MinorSubsystemVersion; // +0x32
    unsigned long Win32VersionValue; // +0x34
    unsigned long SizeOfImage; // +0x38
    unsigned long SizeOfHeaders; // +0x3C
    unsigned long CheckSum; // +0x40
    unsigned short Subsystem; // +0x44
    unsigned short DllCharacteristics; // +0x46
    unsigned long SizeOfStackReserve; // +0x48
    unsigned long SizeOfStackCommit; // +0x4C
    unsigned long SizeOfHeapReserve; // +0x50
    unsigned long SizeOfHeapCommit; // +0x54
    unsigned long LoaderFlags; // +0x58
    unsigned long NumberOfRvaAndSizes; // +0x5C
    _IMAGE_DATA_DIRECTORY DataDirectory[16]; // +0x60
    // total size: 0xE0 (224)

};
