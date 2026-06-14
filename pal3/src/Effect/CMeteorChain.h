#pragma once
// Auto-generated: CMeteorChain

#include "gbengine/gbMesh.h"
#include "gbengine/gbTexture.h"

class CEffMgr;
class tagMeteorNode;

class CMeteorChain {
public:
    CEffMgr * m_pEM; // +0x0
    gbGeomQuad * m_pGeomQuad; // +0x4
    BYTE m_bHaveTexture; // +0x8
    char _gap_009[3]; // +0x9
    gbTextureArray * m_pTextureArray; // +0xC
    int m_nNumOfNode; // +0x10
    tagMeteorNode * m_pFirstNode; // +0x14
    tagMeteorNode * m_pLastNode; // +0x18
    float m_fCurTime; // +0x1C
    float m_fLastTime; // +0x20
    UINT m_dwColor; // +0x24
    float m_fMaxLum; // +0x28
    float m_fLumDecSpeed; // +0x2C
    float m_fMaxWidth; // +0x30
    float m_fWidthDecSpeed; // +0x34
    // total size: 0x38 (56)

    CMeteorChain(); // 0x004CD0A0
    void Update(int fCurTime, int nVal, int nVal2, int *p_DWORD, int nVal3, int nVal4); // 0x004CD7E0
};
