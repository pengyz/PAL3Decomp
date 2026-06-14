#include "UIWnd.h"
#pragma once
// Auto-generated: UIStaticFlex

#include "UIStaticFlex_State.h"
#include "UITextureArray.h"
#include "gbengine/gbPrintFont.h"

class UIStaticFlex : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    tagRECT m_currect; // +0x44
    char _gap_048[12]; // +0x48
    UITextureArray m_texs; // +0x54
    char _gap_058[64]; // +0x58
    UIStaticFlex_State m_state; // +0x98
    float m_statetime; // +0x9C
    gbFontType m_fonttype; // +0xA0
    int m_tilesize; // +0xA4
    int m_openstyle; // +0xA8
    char _tail_0AC[20]; // +0xAC
    // total size: 0xC0 (192)

};
