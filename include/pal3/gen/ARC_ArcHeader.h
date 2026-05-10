#pragma once
// Auto-generated: ARC_ArcHeader

#include "ARC_ArcBrief.h"

class ARC_ArcHeader {
public:
    char magic[4]; // +0x0
    unsigned char ver; // +0x4
    unsigned long reverse[16]; // +0x8
    ARC_ArcBrief brief; // +0x48
    unsigned long localeOffset; // +0x98
    unsigned long playerOffset; // +0x9C
    unsigned long scriptOffset; // +0xA0
    unsigned long sceneOffset; // +0xA4
    unsigned long soundOffset; // +0xA8
    unsigned long miscOffset; // +0xAC
    unsigned long mapOffset[2]; // +0xB0
    unsigned long pastOffset; // +0xB8
    unsigned long npcOffset; // +0xBC
    unsigned long reverseOffset[7]; // +0xC0
    // total size: 0xDC (220)

};
