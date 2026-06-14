#include "MeshFx.h"
#pragma once
// Auto-generated: MXTransport

#include "ParticleEffect.h"
#include "gbengine/gbMesh.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"

class MXTransport : public MeshFx {
public:
    char _gap_000[92]; // +0x0
    float m_fTime; // +0x5C
    gbTexture * m_pTransTex; // +0x60
    gbTextureArray m_aTex; // +0x64
    char _gap_068[64]; // +0x68
    gbRenderEffect * m_pEffect; // +0xA8
    gbRenderEffect * m_pEffectA; // +0xAC
    gbGeomQuad m_quads[6]; // +0xB0
    char _gap_0C8[384]; // +0xC8
    gbGeomQuad m_quads2[6]; // +0x248
    char _gap_260[384]; // +0x260
    gbGeomQuad m_trans; // +0x3E0
    char _gap_3E4[64]; // +0x3E4
    gbVec2D m_height[4]; // +0x424
    char _gap_434[16]; // +0x434
    int m_ok[4]; // +0x444
    ParticleEffect m_test; // +0x454
    char _tail_458[362856]; // +0x458
    // total size: 0x58DC0 (363968)

};
