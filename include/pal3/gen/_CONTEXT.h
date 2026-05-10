#pragma once
// Auto-generated: _CONTEXT

#include "_FLOATING_SAVE_AREA.h"

class _CONTEXT {
public:
    DWORD ContextFlags; // +0x0
    DWORD Dr0; // +0x4
    DWORD Dr1; // +0x8
    DWORD Dr2; // +0xC
    DWORD Dr3; // +0x10
    DWORD Dr6; // +0x14
    DWORD Dr7; // +0x18
    _FLOATING_SAVE_AREA FloatSave; // +0x1C
    DWORD SegGs; // +0x8C
    DWORD SegFs; // +0x90
    DWORD SegEs; // +0x94
    DWORD SegDs; // +0x98
    DWORD Edi; // +0x9C
    DWORD Esi; // +0xA0
    DWORD Ebx; // +0xA4
    DWORD Edx; // +0xA8
    DWORD Ecx; // +0xAC
    DWORD Eax; // +0xB0
    DWORD Ebp; // +0xB4
    DWORD Eip; // +0xB8
    DWORD SegCs; // +0xBC
    DWORD EFlags; // +0xC0
    DWORD Esp; // +0xC4
    DWORD SegSs; // +0xC8
    BYTE ExtendedRegisters[512]; // +0xCC
    // total size: 0x2CC (716)

};
