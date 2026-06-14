#pragma once
// Auto-generated: _Item

class _Item {
public:
    char title[16]; // +0x0
    char info[16]; // +0x10
    BYTE bHasChild; // +0x20
    char _gap_021[3]; // +0x21
    int nChildNum; // +0x24
    BYTE bIsPic; // +0x28
    char _gap_029[3]; // +0x29
    _Item ** ppChildren; // +0x2C
    // total size: 0x30 (48)

};
