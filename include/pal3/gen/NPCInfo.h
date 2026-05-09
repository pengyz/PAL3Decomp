#pragma once
// Auto-generated: NPCInfo

#include "PolyLine.h"
#include "ROLE_BEHAVIOUR.h"

class NPCInfo {
public:
    unsigned char id; // +0x0
    unsigned char kind; // +0x1
    char name[32]; // +0x2
    char mtl[32]; // +0x22
    float face; // +0x44
    unsigned char onlayer; // +0x48
    float x; // +0x4C
    float z; // +0x50
    unsigned char initactive; // +0x54
    ROLE_BEHAVIOUR initbeh; // +0x58
    unsigned long scriptid; // +0x5C
    float y; // +0x60
    char initact[16]; // +0x64
    unsigned long mid[3]; // +0x74
    unsigned char mnum; // +0x80
    unsigned char mrepeat; // +0x81
    PolyLine path; // +0x84
    unsigned long noturn; // +0x148
    unsigned long loopact; // +0x14C
    unsigned long speed; // +0x150
    unsigned long reserve[29]; // +0x154
    // total size: 0x1C8 (456)

};
