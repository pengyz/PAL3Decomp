#pragma once
// Auto-generated: UICursor

#include "gbengine/gbengine_types.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"

class CameraCtrl;
class _PlugInfo;

class UICursor {
public:
    UINT m_dwID[3]; // +0x0
    CameraCtrl * m_active; // +0xC
    gbTexture * m_tex[3]; // +0x10
    char _gap_014[8]; // +0x14
    BYTE m_bShow; // +0x1C
    BYTE m_bSoftMode; // +0x1D
    char _tail_01E[2]; // +0x1E
    // total size: 0x20 (32)

    void Update(double fDelta); // 0x00535120
    static int UIRenderPar(int nX, int nY, int nW, int nH, gbColorQuad *pColor, gbTextureArray *pTex, _PlugInfo *pInfo); // 0x00541160
    void IRender(); // 0x00541CC0
};
