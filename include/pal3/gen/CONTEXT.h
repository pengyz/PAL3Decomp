#pragma once
// Auto-generated: CONTEXT

#include "_FLOATING_SAVE_AREA.h"

class CONTEXT {
public:
    int ContextFlags; // +0x0
    int Dr0; // +0x4
    int Dr1; // +0x8
    int Dr2; // +0xC
    int Dr3; // +0x10
    int Dr6; // +0x14
    int Dr7; // +0x18
    _FLOATING_SAVE_AREA FloatSave; // +0x1C
    int SegGs; // +0x17C
    int SegFs; // +0x180
    int SegEs; // +0x184
    int SegDs; // +0x188
    int Edi; // +0x18C
    int Esi; // +0x190
    int Ebx; // +0x194
    int Edx; // +0x198
    int Ecx; // +0x19C
    int Eax; // +0x1A0
    int Ebp; // +0x1A4
    int Eip; // +0x1A8
    int SegCs; // +0x1AC
    int EFlags; // +0x1B0
    int Esp; // +0x1B4
    int SegSs; // +0x1B8
    int ExtendedRegisters[512]; // +0x1BC
    // total size: 0x9BC (2492)

};
