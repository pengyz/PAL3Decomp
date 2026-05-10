#pragma once
// Auto-generated: gbVertexBubble

#include "gbChain1DNode.h"

class gbVertexBubble : public gbChain1DNode {
public:
    gbVertexPool * pPool; // +0x8
    int Start; // +0xC
    int BubSize; // +0x10
    int nVerts; // +0x14
    float * pXYZ; // +0x18
    float * pNormal; // +0x1C
    gbColorQuad * pColor1; // +0x20
    gbColorQuad * pColor2; // +0x24
    float * pUV[4]; // +0x28
    // total size: 0x38 (56)

};
