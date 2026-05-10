#pragma once
// Auto-generated: _FLOATING_SAVE_AREA

class _FLOATING_SAVE_AREA {
public:
    DWORD ControlWord; // +0x0
    DWORD StatusWord; // +0x4
    DWORD TagWord; // +0x8
    DWORD ErrorOffset; // +0xC
    DWORD ErrorSelector; // +0x10
    DWORD DataOffset; // +0x14
    DWORD DataSelector; // +0x18
    BYTE RegisterArea[80]; // +0x1C
    DWORD Cr0NpxState; // +0x6C
    // total size: 0x70 (112)

};
