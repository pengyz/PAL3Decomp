#pragma once
// Auto-generated: PurgeEffect

#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"

class PurgeEffect {
public:
    gbTexture * pSrcTex; // +0x0
    gbImage2D pSrcImg; // +0x4
    char _gap_008[196]; // +0x8
    gbImage2D pDstImg; // +0xCC
    char _gap_0D0[196]; // +0xD0
    int m_ItemNum; // +0x194
    char EffItem[16]; // +0x198
    BYTE m_isUpdateMerge; // +0x1A8
    char _tail_1A9[3]; // +0x1A9
    // total size: 0x1AC (428)

};
