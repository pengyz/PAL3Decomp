#pragma once
// Auto-generated: CTrail

class IDirect3DSurface9;

class CTrail {
public:
    float m_fTime; // +0x0
    unsigned char m_bSupport; // +0x4
    unsigned char m_bEnable; // +0x5
    gbCamera * m_pCam; // +0x8
    gbUIQuad m_ScreenQuad; // +0xC
    unsigned long m_dwRenderCounter; // +0x34
    unsigned long m_dwRT; // +0x38
    unsigned char m_bReady; // +0x3C
    gbTexture_D3D m_texRT[8]; // +0x40
    gbRenderEffect * m_eft; // +0x340
    IDirect3DSurface9 * m_OriginSurface; // +0x344
    // total size: 0x348 (840)

};
