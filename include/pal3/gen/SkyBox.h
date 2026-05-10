#pragma once
// Auto-generated: SkyBox

class SkyBox {
public:
    gbColorQuad m_fogColor; // +0x4
    gbTexture * m_pTexture[6]; // +0x8
    gbVec3D m_vHalfSize; // +0x20
    gbRenderEffect * m_pEffect; // +0x2C
    gbRenderEffect * m_pEffectNormal; // +0x30
    BYTE m_bValid; // +0x34
    // total size: 0x38 (56)

};
