#include "MeshFx.h"
#pragma once
// Auto-generated: MXSavePoint

#include "gbengine/gbGeomNode.h"
#include "gbengine/gbMesh.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"

class MXSavePoint : public MeshFx {
public:
    char _gap_000[92]; // +0x0
    float m_fTime; // +0x5C
    gbTextureArray m_aTex; // +0x60
    char _gap_064[64]; // +0x64
    gbTexture * m_pTex; // +0xA4
    gbRenderEffect * m_pEffect; // +0xA8
    gbGeomQuad m_trans; // +0xAC
    char _gap_0B0[64]; // +0xB0
    gbGeomQuad m_quads[12]; // +0xF0
    char _gap_120[768]; // +0x120
    gbGeomNode * m_stone; // +0x420
    // total size: 0x424 (1060)

};
