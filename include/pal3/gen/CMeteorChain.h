#pragma once
// Auto-generated: CMeteorChain

class CEffMgr;
class gbTextureArray;
class tagMeteorNode;

class CMeteorChain {
public:
    CEffMgr * m_pEM; // +0x0
    gbGeomQuad * m_pGeomQuad; // +0x4
    unsigned char m_bHaveTexture; // +0x8
    gbTextureArray * m_pTextureArray; // +0xC
    int m_nNumOfNode; // +0x10
    tagMeteorNode * m_pFirstNode; // +0x14
    tagMeteorNode * m_pLastNode; // +0x18
    float m_fCurTime; // +0x1C
    float m_fLastTime; // +0x20
    unsigned long m_dwColor; // +0x24
    float m_fMaxLum; // +0x28
    float m_fLumDecSpeed; // +0x2C
    float m_fMaxWidth; // +0x30
    float m_fWidthDecSpeed; // +0x34
    // total size: 0x38 (56)

    CMeteorChain(); // 0x004CD0A0
    int Update(int a2, int a3, int a4, _DWORD *a5, int a6, int a7); // 0x004CD7E0
};
