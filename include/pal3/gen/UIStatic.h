#pragma once
// Auto-generated: UIStatic

#include "UIWnd.h"
#include "gbFontType.h"

class _PlugInfo;

class UIStatic : public UIWnd {
public:
    int m_bordersize; // +0x44
    int m_align; // +0x48
    gbTexture * pDebugTex; // +0x0
    float m_ratiow; // +0x4C
    float m_ratioh; // +0x50
    int m_textx; // +0x54
    int m_texty; // +0x58
    gbFontType m_fonttype; // +0x5C
    char m_text[16]; // +0x60 (std::basic_string<char,std::char_traits<char>,std::allocator<char> >)
    gbTexture * m_pbk; // +0x70
    _PlugInfo * m_pbkInfo; // +0x74
    gbTexture * m_ppic; // +0x78
    _PlugInfo * m_ppicInfo; // +0x7C
    gbTexture * m_disablepic; // +0x80
    _PlugInfo * m_disablepicInfo; // +0x84
    gbTexture * m_pbk2; // +0x88
    BYTE m_mouseoff; // +0x8C
    int m_FVF; // +0x90
    int m_nTextW; // +0x94
    BYTE m_PureColor; // +0x98
    int m_richtext; // +0x9C
    // total size: 0xA0 (160)

    UIStatic(); // 0x00440740
    int OnMessage(); // 0x00440BA0
    BOOL Update(int a2, int a3); // 0x00440DD0
    int Render(); // 0x00440F30
};
