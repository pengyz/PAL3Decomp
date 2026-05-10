#pragma once
// Auto-generated: gbEffectMgr

class gbEffectMgr : public gbResManager {
public:
    gbGfxManager * m_pGfxMgr; // +0xC
    gbTexture * m_pWhiteTex; // +0x10
    gbTexture * m_pGrayTex; // +0x14
    gbRenderEffect * m_pDefEffect; // +0x18
    char m_AllHandle[2048]; // +0x1C (gbEffectMgr::HandleObj[64])
    int m_nHandle; // +0x81C
    gbRenderEffect * pCurEffect; // +0x820
    int bDoPassOutside; // +0x824
    // total size: 0x828 (2088)

};
