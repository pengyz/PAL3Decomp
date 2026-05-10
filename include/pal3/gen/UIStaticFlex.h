#pragma once
// Auto-generated: UIStaticFlex

#include "UITextureArray.h"
#include "UIWnd.h"
#include "gbFontType.h"

class UIStaticFlex : public UIWnd {
public:
    float DURATION; // +0x44
    struct allocator<char> > {}; // nested type stub
    allocator<char> > m_text; // +0x48
    tagRECT m_currect; // +0x58
    UITextureArray m_texs; // +0x68
    struct State {}; // nested type stub
    State m_state; // +0xAC
    float m_statetime; // +0xB0
    gbFontType m_fonttype; // +0xB4
    int m_tilesize; // +0xB8
    int m_openstyle; // +0xBC
    // total size: 0xC0 (192)

};
