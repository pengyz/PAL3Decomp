#pragma once
// Auto-generated: _CONTEXT

#include "_FLOATING_SAVE_AREA.h"

class _CONTEXT {
public:
    unsigned long ContextFlags; // +0x0
    unsigned long Dr0; // +0x4
    unsigned long Dr1; // +0x8
    unsigned long Dr2; // +0xC
    unsigned long Dr3; // +0x10
    unsigned long Dr6; // +0x14
    unsigned long Dr7; // +0x18
    _FLOATING_SAVE_AREA FloatSave; // +0x1C
    unsigned long SegGs; // +0x8C
    unsigned long SegFs; // +0x90
    unsigned long SegEs; // +0x94
    unsigned long SegDs; // +0x98
    unsigned long Edi; // +0x9C
    unsigned long Esi; // +0xA0
    unsigned long Ebx; // +0xA4
    unsigned long Edx; // +0xA8
    unsigned long Ecx; // +0xAC
    unsigned long Eax; // +0xB0
    unsigned long Ebp; // +0xB4
    unsigned long Eip; // +0xB8
    unsigned long SegCs; // +0xBC
    unsigned long EFlags; // +0xC0
    unsigned long Esp; // +0xC4
    unsigned long SegSs; // +0xC8
    unsigned char ExtendedRegisters[512]; // +0xCC
    // total size: 0x2CC (716)

};
