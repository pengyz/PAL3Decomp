#pragma once
// Auto-generated: ArcHeader

#include "ArcBrief.h"

class ArcHeader {
public:
    char magic[4]; // +0x0
    BYTE ver; // +0x4
    char _gap_005[3]; // +0x5
    UINT reverse[16]; // +0x8
    ArcBrief brief; // +0x48
    char _gap_04C[84]; // +0x4C
    UINT localeOffset; // +0xA0
    UINT playerOffset; // +0xA4
    UINT scriptOffset; // +0xA8
    UINT sceneOffset; // +0xAC
    UINT soundOffset; // +0xB0
    UINT miscOffset; // +0xB4
    UINT mapOffset[2]; // +0xB8
    UINT pastOffset; // +0xC0
    UINT npcOffset; // +0xC4
    _BYTE reverseOffset[20]; // +0xC8
    char _tail_0DC[4]; // +0xDC
    // total size: 0xE0 (224)

};
