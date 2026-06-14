#include "UIWnd.h"
#pragma once
// Auto-generated: UIScrollBar

#include "UIFlexBar.h"
#include "UITextureArray.h"

class _PlugInfo;

class UIScrollBar : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    BYTE m_bPress; // +0x44
    BYTE m_bPressed; // +0x45
    char _gap_046[2]; // +0x46
    UIFlexBar m_bk; // +0x48
    char _gap_04C[80]; // +0x4C
    int m_btnH; // +0x9C
    int m_mouseat; // +0xA0
    int m_min; // +0xA4
    int m_max; // +0xA8
    int m_pos; // +0xAC
    float m_lastpos; // +0xB0
    float m_drawpos; // +0xB4
    float m_step; // +0xB8
    int m_pagesize; // +0xBC
    UITextureArray m_texarray; // +0xC0
    char _gap_0C4[64]; // +0xC4
    _PlugInfo * m_texarrayInfo[10]; // +0x104
    char _gap_108[36]; // +0x108
    float m_keytime; // +0x12C
    tagRECT m_btnrect[2]; // +0x130
    char _gap_138[24]; // +0x138
    int m_slideroffset; // +0x150
    int m_slidertboffset; // +0x154
    int m_sliderw; // +0x158
    int m_sliderh; // +0x15C
    // total size: 0x160 (352)

    void SetRange(float fValue); // 0x0043FCA0
};
