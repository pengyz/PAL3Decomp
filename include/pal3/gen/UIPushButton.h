#pragma once
// Auto-generated: UIPushButton

#include "UIWnd.h"
#include "gbFontType.h"

class _PlugInfo;

class UIPushButton : public UIWnd {
public:
    unsigned char m_isDown; // +0x44
    unsigned char m_isCtrl; // +0x45
    unsigned char m_mouseoff; // +0x46
    gbColorQuad m_fontcolor; // +0x48
    gbFontType m_fonttype; // +0x4C
    struct UIPUSHBUTTON_STATE {}; // nested type stub
    UIPUSHBUTTON_STATE m_state; // +0x50
    gbTexture * m_texarray[2]; // +0x54
    _PlugInfo * m_texarrayInfo[2]; // +0x5C
    unsigned char m_bOn; // +0x64
    gbTexture * m_onpic; // +0x68
    _PlugInfo * m_onpicInfo; // +0x6C
    gbTexture * m_disablepic; // +0x70
    _PlugInfo * m_disablepicInfo; // +0x74
    char m_caption[128]; // +0x78
    int m_TextTopOffset; // +0xF8
    // total size: 0xFC (252)

};
