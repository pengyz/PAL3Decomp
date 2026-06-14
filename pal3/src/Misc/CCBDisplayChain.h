#pragma once
// Auto-generated: CCBDisplayChain

#include "gbengine/gbengine_types.h"
#include "tagShowItem.h"

class CCBStage;
class CCBStageScene;
class tagRGBQUAD;

class CCBDisplayChain {
public:
    CCBStage * m_pStage; // +0x0
    CCBStageScene * m_pScene; // +0x4
    tagRGBQUAD m_DefaultColor; // +0x8
    gbColorQuad m_ScreenQuadColor; // +0xC
    int m_nItemNum; // +0x10
    tagShowItem m_ShowItem[64]; // +0x14
    char _gap_114[17664]; // +0x114
    BYTE m_byScreenQuadAlpha; // +0x4614
    char _tail_4615[3]; // +0x4615
    // total size: 0x4618 (17944)

};
