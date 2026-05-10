#pragma once
// Auto-generated: UIStaticFlex

#include "UITextureArray.h"
#include "UIWnd.h"
#include "gbFontType.h"

class UIStaticFlex : public UIWnd {
public:
    float DURATION; // +0x44
    char m_text[16]; // +0x48 (std::basic_string<char,std::char_traits<char>,std::allocator<char> >)
    tagRECT m_currect; // +0x58
    UITextureArray m_texs; // +0x68
    char m_state[4]; // +0xAC (UIStaticFlex::State)
    float m_statetime; // +0xB0
    gbFontType m_fonttype; // +0xB4
    int m_tilesize; // +0xB8
    int m_openstyle; // +0xBC
    // total size: 0xC0 (192)

};
