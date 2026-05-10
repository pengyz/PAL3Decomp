#pragma once
// Auto-generated: MXTransport

#include "MeshFx.h"
#include "ParticleEffect.h"
#include "gbTextureArray.h"
#include "gbVec2D.h"

class MXTransport : public MeshFx {
public:
    float m_fTime; // +0x5C
    gbTexture * m_pTransTex; // +0x60
    gbTextureArray m_aTex; // +0x64
    gbRenderEffect * m_pEffect; // +0xA8
    gbRenderEffect * m_pEffectA; // +0xAC
    gbGeomQuad m_quads[6]; // +0xB0
    gbGeomQuad m_quads2[6]; // +0x248
    gbGeomQuad m_trans; // +0x3E0
    gbVec2D m_height[4]; // +0x424
    int m_ok[4]; // +0x444
    ParticleEffect m_test; // +0x454
    // total size: 0x58DC0 (363968)

};
