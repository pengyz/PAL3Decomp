#pragma once
// Auto-generated: SkyBox

#include "gbengine/gbengine_types.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"

class SkyBox {
public:
    char _gap_000[4]; // +0x0
    gbColorQuad m_fogColor; // +0x4
    gbTexture * m_pTexture[6]; // +0x8
    char _gap_00C[20]; // +0xC
    gbVec3D m_vHalfSize; // +0x20
    char _gap_024[8]; // +0x24
    gbRenderEffect * m_pEffect; // +0x2C
    gbRenderEffect * m_pEffectNormal; // +0x30
    BYTE m_bValid; // +0x34
    char _tail_035[3]; // +0x35
    // total size: 0x38 (56)

};
