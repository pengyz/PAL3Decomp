#pragma once
// Auto-generated: ARC_ArcHeader

#include "ARC_ArcBrief.h"

class ARC_ArcHeader {
public:
    char magic[4]; // +0x0
    BYTE ver; // +0x4
    DWORD reverse[16]; // +0x8
    ARC_ArcBrief brief; // +0x48
    DWORD localeOffset; // +0x98
    DWORD playerOffset; // +0x9C
    DWORD scriptOffset; // +0xA0
    DWORD sceneOffset; // +0xA4
    DWORD soundOffset; // +0xA8
    DWORD miscOffset; // +0xAC
    DWORD mapOffset[2]; // +0xB0
    DWORD pastOffset; // +0xB8
    DWORD npcOffset; // +0xBC
    DWORD reverseOffset[7]; // +0xC0
    // total size: 0xDC (220)

};
