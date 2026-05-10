#pragma once
// Auto-generated: MXFire

#include "MeshFx.h"

class gbTextureArray;

class MXFire : public MeshFx {
public:
    int m_nCurTex; // +0x5C
    float m_fTime; // +0x60
    gbRenderEffect * m_pEffect; // +0x64
    gbTexture * m_pTexs[16]; // +0x68
    gbTextureArray m_ta; // +0xA8
    gbTexture * m_pFlare; // +0xEC
    gbGeomNode * m_candle; // +0xF0
    unsigned long m_type; // +0xF4
    // total size: 0xF8 (248)

};
