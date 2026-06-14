#pragma once
// Auto-generated: NavFaceLayer

#include "gbengine/gbengine_types.h"

class LayerNode;
class NavFace;

class NavFaceLayer {
public:
    WORD numvert; // +0x0
    WORD numface; // +0x2
    gbVec3D * vertbuf; // +0x4
    NavFace * face; // +0x8
    LayerNode * node; // +0xC
    // total size: 0x10 (16)

    static int GetVertexNum(); // 0x00452540
    static struct gbVec3D * GetVertexBuf(); // 0x00452560
};
