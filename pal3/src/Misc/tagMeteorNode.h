#pragma once
// Auto-generated: tagMeteorNode

#include "gbengine/gbengine_types.h"

class tagMeteorNode {
public:
    gbVec3D vecPos; // +0x0
    char _gap_004[8]; // +0x4
    float fLum; // +0xC
    float fWidth; // +0x10
    float fTime; // +0x14
    BYTE bVisible; // +0x18
    char _gap_019[3]; // +0x19
    tagMeteorNode * pLast; // +0x1C
    tagMeteorNode * pNext; // +0x20
    // total size: 0x24 (36)

};
