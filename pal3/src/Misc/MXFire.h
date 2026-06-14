#include "MeshFx.h"
#pragma once
// Auto-generated: MXFire

#include "gbengine/gbGeomNode.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"

class MXFire : public MeshFx {
public:
    char _gap_000[92]; // +0x0
    int m_nCurTex; // +0x5C
    float m_fTime; // +0x60
    gbRenderEffect * m_pEffect; // +0x64
    gbTexture * m_pTexs[16]; // +0x68
    char _gap_06C[60]; // +0x6C
    gbTextureArray m_ta; // +0xA8
    char _gap_0AC[64]; // +0xAC
    gbTexture * m_pFlare; // +0xEC
    gbGeomNode * m_candle; // +0xF0
    UINT m_type; // +0xF4
    // total size: 0xF8 (248)

};
