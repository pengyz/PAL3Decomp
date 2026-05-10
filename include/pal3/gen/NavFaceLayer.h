#pragma once
// Auto-generated: NavFaceLayer

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

};
