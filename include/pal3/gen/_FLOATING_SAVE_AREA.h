#pragma once
// Auto-generated: _FLOATING_SAVE_AREA

class _FLOATING_SAVE_AREA {
public:
    unsigned long ControlWord; // +0x0
    unsigned long StatusWord; // +0x4
    unsigned long TagWord; // +0x8
    unsigned long ErrorOffset; // +0xC
    unsigned long ErrorSelector; // +0x10
    unsigned long DataOffset; // +0x14
    unsigned long DataSelector; // +0x18
    unsigned char RegisterArea[80]; // +0x1C
    unsigned long Cr0NpxState; // +0x6C
    // total size: 0x70 (112)

};
