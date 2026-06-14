#pragma once
// Auto-generated: CTrail

#include "gbengine/gbCamera.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbMesh.h"

class IDirect3DSurface9;

class CTrail {
public:
    float m_fTime; // +0x0
    BYTE m_bSupport; // +0x4
    BYTE m_bEnable; // +0x5
    char _gap_006[2]; // +0x6
    gbCamera * m_pCam; // +0x8
    gbUIQuad m_ScreenQuad; // +0xC
    char _gap_010[36]; // +0x10
    UINT m_dwRenderCounter; // +0x34
    UINT m_dwRT; // +0x38
    BYTE m_bReady; // +0x3C
    char _gap_03D[3]; // +0x3D
    gbTexture_D3D m_texRT[8]; // +0x40
    char _gap_060[736]; // +0x60
    gbRenderEffect * m_eft; // +0x340
    IDirect3DSurface9 * m_OriginSurface; // +0x344
    // total size: 0x348 (840)

};
