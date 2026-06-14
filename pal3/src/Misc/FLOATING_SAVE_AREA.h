#pragma once
// Auto-generated: FLOATING_SAVE_AREA

class FLOATING_SAVE_AREA {
public:
    UINT ControlWord; // +0x0
    UINT StatusWord; // +0x4
    UINT TagWord; // +0x8
    UINT ErrorOffset; // +0xC
    UINT ErrorSelector; // +0x10
    UINT DataOffset; // +0x14
    UINT DataSelector; // +0x18
    char _gap_01C[80]; // +0x1C
    UINT Cr0NpxState; // +0x6C
    // total size: 0x70 (112)

};
