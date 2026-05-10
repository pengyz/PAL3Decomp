#pragma once
// Auto-generated: PurgeEffect

class PurgeEffect {
public:
    gbTexture * pSrcTex; // +0x0
    gbImage2D pSrcImg; // +0x4
    gbImage2D pDstImg; // +0xCC
    int m_ItemNum; // +0x194
    char EffItem[16]; // +0x198 (std::vector<EffectItem,std::allocator<EffectItem> >)
    BYTE m_isUpdateMerge; // +0x1A8
    // total size: 0x1AC (428)

};
