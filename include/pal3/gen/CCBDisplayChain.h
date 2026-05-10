#pragma once
// Auto-generated: CCBDisplayChain

#include "tagRGBQUAD.h"
#include "tagShowItem.h"

class CCBStage;
class CCBStageScene;

class CCBDisplayChain {
public:
    CCBStage * m_pStage; // +0x0
    CCBStageScene * m_pScene; // +0x4
    tagRGBQUAD m_DefaultColor; // +0x8
    gbColorQuad m_ScreenQuadColor; // +0xC
    int m_nItemNum; // +0x10
    tagShowItem m_ShowItem[64]; // +0x14
    unsigned char m_byScreenQuadAlpha; // +0x4614
    // total size: 0x4618 (17944)

};
