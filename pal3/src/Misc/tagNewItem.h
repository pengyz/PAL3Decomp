#pragma once
// Auto-generated: tagNewItem

class tagNewItem {
public:
    UINT dwItemID; // +0x0
    int (__thiscall *fnHP)(void *, unsigned int); // +0x4
    int (__thiscall *fnGP)(void *, unsigned int); // +0x8
    union { // +0xC
    int (__thiscall *fnMP)(void *, unsigned long); // +0xC
    float fMP; // +0xC
    };
    // total size: 0x10 (16)

};
