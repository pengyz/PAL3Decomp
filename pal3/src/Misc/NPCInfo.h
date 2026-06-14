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
    char _gap_042[2]; // +0x42
    float face; // +0x44
    BYTE onlayer; // +0x48
    char _gap_049[3]; // +0x49
    float x; // +0x4C
    float z; // +0x50
    BYTE initactive; // +0x54
    char _gap_055[3]; // +0x55
    ROLE_BEHAVIOUR initbeh; // +0x58
    UINT scriptid; // +0x5C
    float y; // +0x60
    char initact[16]; // +0x64
    UINT mid[3]; // +0x74
    BYTE mnum; // +0x80
    BYTE mrepeat; // +0x81
    char _gap_082[2]; // +0x82
    PolyLine path; // +0x84
    char _gap_088[192]; // +0x88
    UINT noturn; // +0x148
    UINT loopact; // +0x14C
    UINT speed; // +0x150
    UINT reserve[29]; // +0x154
    // total size: 0x1C8 (456)

};
