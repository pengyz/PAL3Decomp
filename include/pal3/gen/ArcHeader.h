#pragma once
// Auto-generated: ArcHeader

#include "ArcBrief.h"

class ArcHeader {
public:
    char magic[4]; // +0x0
    unsigned char ver; // +0x4
    unsigned long reverse[16]; // +0x8
    ArcBrief brief; // +0x48
    unsigned long localeOffset; // +0xA0
    unsigned long playerOffset; // +0xA4
    unsigned long scriptOffset; // +0xA8
    unsigned long sceneOffset; // +0xAC
    unsigned long soundOffset; // +0xB0
    unsigned long miscOffset; // +0xB4
    unsigned long mapOffset[2]; // +0xB8
    unsigned long pastOffset; // +0xC0
    unsigned long npcOffset; // +0xC4
    unsigned char reverseOffset[20]; // +0xC8
    // total size: 0xE0 (224)

};
