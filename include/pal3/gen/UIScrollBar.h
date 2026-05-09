#pragma once
// Auto-generated: UIScrollBar

#include "UIFlexBar.h"
#include "UITextureArray.h"
#include "UIWnd.h"
#include "tagPOINT.h"
#include "tagRECT.h"

class _PlugInfo;

class UIScrollBar : public UIWnd {
public:
    unsigned char m_bPress; // +0x44
    unsigned char m_bPressed; // +0x45
    UIFlexBar m_bk; // +0x48
    int m_DragState; // +0x9C
    unsigned char m_bDrag; // +0xA0
    tagPOINT m_lastPt; // +0xA4
    int m_btnH; // +0xAC
    UIScrollBar::SB_AREA m_mouseat; // +0xB0
    int m_min; // +0xB4
    int m_max; // +0xB8
    int m_pos; // +0xBC
    float m_lastpos; // +0xC0
    float m_drawpos; // +0xC4
    float m_step; // +0xC8
    int m_pagesize; // +0xCC
    UITextureArray m_texarray; // +0xD0
    _PlugInfo * m_texarrayInfo[10]; // +0x114
    float m_keytime; // +0x13C
    tagRECT m_btnrect[2]; // +0x140
    int m_slideroffset; // +0x160
    int m_slidertboffset; // +0x164
    int m_sliderw; // +0x168
    int m_sliderh; // +0x16C
    // total size: 0x170 (368)

};
