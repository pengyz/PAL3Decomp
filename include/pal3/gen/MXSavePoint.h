#pragma once
// Auto-generated: MXSavePoint

#include "MeshFx.h"

class gbTextureArray;

class MXSavePoint : public MeshFx {
public:
    float m_fTime; // +0x5C
    gbTextureArray m_aTex; // +0x60
    gbTexture * m_pTex; // +0xA4
    gbRenderEffect * m_pEffect; // +0xA8
    gbGeomQuad m_trans; // +0xAC
    gbGeomQuad m_quads[12]; // +0xF0
    gbGeomNode * m_stone; // +0x420
    // total size: 0x424 (1060)

};
