#pragma once
// Auto-generated: IMAGE_OPTIONAL_HEADER32

#include "_IMAGE_DATA_DIRECTORY.h"

class IMAGE_OPTIONAL_HEADER32 {
public:
    int Magic; // +0x0
    int MajorLinkerVersion; // +0x4
    int MinorLinkerVersion; // +0x8
    int SizeOfCode; // +0xC
    int SizeOfInitializedData; // +0x10
    int SizeOfUninitializedData; // +0x14
    int AddressOfEntryPoint; // +0x18
    int BaseOfCode; // +0x1C
    int BaseOfData; // +0x20
    int ImageBase; // +0x24
    int SectionAlignment; // +0x28
    int FileAlignment; // +0x2C
    int MajorOperatingSystemVersion; // +0x30
    int MinorOperatingSystemVersion; // +0x34
    int MajorImageVersion; // +0x38
    int MinorImageVersion; // +0x3C
    int MajorSubsystemVersion; // +0x40
    int MinorSubsystemVersion; // +0x44
    int Win32VersionValue; // +0x48
    int SizeOfImage; // +0x4C
    int SizeOfHeaders; // +0x50
    int CheckSum; // +0x54
    int Subsystem; // +0x58
    int DllCharacteristics; // +0x5C
    int SizeOfStackReserve; // +0x60
    int SizeOfStackCommit; // +0x64
    int SizeOfHeapReserve; // +0x68
    int SizeOfHeapCommit; // +0x6C
    int LoaderFlags; // +0x70
    int NumberOfRvaAndSizes; // +0x74
    _IMAGE_DATA_DIRECTORY DataDirectory[16]; // +0x78
    // total size: 0xF8 (248)

};
