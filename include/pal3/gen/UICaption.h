#pragma once
// Auto-generated: UICaption

#include "PalScriptWaitObj.h"
#include "UIWnd.h"

class UICaption : public UIWnd, public PalScriptWaitObj {
public:
    gbTexture * m_tex; // +0x4C
    int m_numline; // +0x50
    int m_lineheight; // +0x54
    int m_curline; // +0x58
    float m_linetime; // +0x5C
    gbTexture * m_tex2; // +0x60
    int m_numline2; // +0x64
    int m_curline2; // +0x68
    float m_linetime2; // +0x6C
    tagRECT m_rect2; // +0x70
    unsigned char m_bHas2; // +0x80
    unsigned char m_bDraw2; // +0x81
    // total size: 0x84 (132)

};
