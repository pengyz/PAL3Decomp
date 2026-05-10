#pragma once
// Auto-generated: NPCInfo

#include "PolyLine.h"
#include "ROLE_BEHAVIOUR.h"

class NPCInfo {
public:
    BYTE id; // +0x0
    BYTE kind; // +0x1
    char name[32]; // +0x2
    char mtl[32]; // +0x22
    float face; // +0x44
    BYTE onlayer; // +0x48
    float x; // +0x4C
    float z; // +0x50
    BYTE initactive; // +0x54
    ROLE_BEHAVIOUR initbeh; // +0x58
    DWORD scriptid; // +0x5C
    float y; // +0x60
    char initact[16]; // +0x64
    DWORD mid[3]; // +0x74
    BYTE mnum; // +0x80
    BYTE mrepeat; // +0x81
    PolyLine path; // +0x84
    DWORD noturn; // +0x148
    DWORD loopact; // +0x14C
    DWORD speed; // +0x150
    DWORD reserve[29]; // +0x154
    // total size: 0x1C8 (456)

};
