#pragma once
// Auto-generated: FLOATING_SAVE_AREA

class FLOATING_SAVE_AREA {
public:
    int ControlWord; // +0x0
    int StatusWord; // +0x4
    int TagWord; // +0x8
    int ErrorOffset; // +0xC
    int ErrorSelector; // +0x10
    int DataOffset; // +0x14
    int DataSelector; // +0x18
    int RegisterArea[80]; // +0x1C
    int Cr0NpxState; // +0x15C
    // total size: 0x160 (352)

};
