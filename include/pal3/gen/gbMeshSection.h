#pragma once
// Auto-generated: gbMeshSection

#include "gbTexFlipAnim.h"
#include "gbTextureArray.h"

class gbIndexBubble;

class gbMeshSection {
public:
    int BlendFlags; // +0x0
    int bBakedLight; // +0x4
    gbTextureArray TexArray; // +0x8
    gbMaterial Material; // +0x4C
    gbIndexBubble * pIndexBub; // +0x90
    unsigned int VertStart; // +0x94
    unsigned int VertEnd; // +0x98
    gbVec3D Point; // +0x9C
    gbRenderEffect * pCustomEffect; // +0xA8
    gbTexFlipAnim TexAnim; // +0xAC
    // total size: 0xBC (188)

};
