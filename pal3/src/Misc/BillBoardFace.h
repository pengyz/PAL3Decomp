#pragma once
// Auto-generated: BillBoardFace

#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"

class BillBoardFace {
public:
    gbTextureArray m_texarray; // +0x0
    char _gap_004[64]; // +0x4
    int m_curtex; // +0x44
    int m_id; // +0x48
    gbVec3D m_pos; // +0x4C
    char _gap_050[8]; // +0x50
    gbRenderEffect * m_effect; // +0x58
    // total size: 0x5C (92)

};
