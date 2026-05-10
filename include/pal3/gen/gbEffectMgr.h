#pragma once
// Auto-generated: gbEffectMgr

class gbEffectMgr : public gbResManager {
public:
    gbGfxManager * m_pGfxMgr; // +0xC
    gbTexture * m_pWhiteTex; // +0x10
    gbTexture * m_pGrayTex; // +0x14
    gbRenderEffect * m_pDefEffect; // +0x18
    struct HandleObj {}; // nested type stub
    HandleObj m_AllHandle[64]; // +0x1C
    int m_nHandle; // +0x81C
    gbRenderEffect * pCurEffect; // +0x820
    int bDoPassOutside; // +0x824
    // total size: 0x828 (2088)

};
