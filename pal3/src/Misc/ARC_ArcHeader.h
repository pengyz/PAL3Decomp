#pragma once
// Auto-generated: ARC_ArcHeader

#include "ARC_ArcBrief.h"

class ARC_ArcHeader {
public:
    char magic[4]; // +0x0
    BYTE ver; // +0x4
    char _gap_005[3]; // +0x5
    UINT reverse[16]; // +0x8
    ARC_ArcBrief brief; // +0x48
    char _gap_04C[76]; // +0x4C
    UINT localeOffset; // +0x98
    UINT playerOffset; // +0x9C
    UINT scriptOffset; // +0xA0
    UINT sceneOffset; // +0xA4
    UINT soundOffset; // +0xA8
    UINT miscOffset; // +0xAC
    UINT mapOffset[2]; // +0xB0
    UINT pastOffset; // +0xB8
    UINT npcOffset; // +0xBC
    UINT reverseOffset[7]; // +0xC0
    // total size: 0xDC (220)

};
