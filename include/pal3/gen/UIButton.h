#pragma once
// Auto-generated: UIButton

#include "UITextureArray.h"
#include "UIWnd.h"

class _PlugInfo;

class UIButton : public UIWnd {
public:
    BYTE m_hasDBclk; // +0x44
    float m_ratiow; // +0x48
    float m_ratioh; // +0x4C
    tagRECT m_drawrc; // +0x50
    char m_state[4]; // +0x60 (UIButton::UIBUTTON_STATE)
    BYTE m_canctrl; // +0x64
    BYTE m_bLockUpdate; // +0x65
    int m_offsetx; // +0x68
    int m_offsety; // +0x6C
    BYTE m_bBigFont; // +0x70
    UITextureArray m_texarray; // +0x74
    _PlugInfo * m_texarrayInfo[3]; // +0xB8
    gbTexture * m_disablepic; // +0xC4
    _PlugInfo * m_disablepicInfo; // +0xC8
    BYTE m_mouseoff; // +0xCC
    BYTE m_mouseon; // +0xCD
    int m_alignmode; // +0xD0
    char m_caption[128]; // +0xD4
    BYTE m_benable_snd; // +0x154
    // total size: 0x158 (344)

};
