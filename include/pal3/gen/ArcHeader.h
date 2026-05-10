#pragma once
// Auto-generated: ArcHeader

#include "ArcBrief.h"

class ArcHeader {
public:
    char magic[4]; // +0x0
    BYTE ver; // +0x4
    DWORD reverse[16]; // +0x8
    ArcBrief brief; // +0x48
    DWORD localeOffset; // +0xA0
    DWORD playerOffset; // +0xA4
    DWORD scriptOffset; // +0xA8
    DWORD sceneOffset; // +0xAC
    DWORD soundOffset; // +0xB0
    DWORD miscOffset; // +0xB4
    DWORD mapOffset[2]; // +0xB8
    DWORD pastOffset; // +0xC0
    DWORD npcOffset; // +0xC4
    BYTE reverseOffset[20]; // +0xC8
    // total size: 0xE0 (224)

};
