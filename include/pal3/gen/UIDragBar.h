#pragma once
// Auto-generated: UIDragBar

#include "UIWnd.h"

class _PlugInfo;

class UIDragBar : public UIWnd {
public:
    UIWnd * p_Wnd; // +0x44
    unsigned int m_id; // +0x48
    tagRECT m_fatherRc; // +0x4C
    int m_SX; // +0x5C
    int m_SY; // +0x60
    int m_xOffSet; // +0x64
    unsigned char m_bDrag; // +0x68
    unsigned char m_bClick; // +0x69
    int m_DragState; // +0x6C
    tagPOINT m_lastPt; // +0x70
    tagRECT m_DragRc; // +0x78
    tagRECT m_bkRc; // +0x88
    tagRECT m_ProgressRc; // +0x98
    gbColorQuad m_DragColor; // +0xA8
    gbColorQuad m_bkColor; // +0xAC
    gbColorQuad m_foColor; // +0xB0
    gbTexture * m_DragTex[3]; // +0xB4
    _PlugInfo * m_DragTexInfo[3]; // +0xC0
    gbTexture * m_pbk; // +0xCC
    _PlugInfo * m_pbkInfo; // +0xD0
    gbTexture * m_ppic; // +0xD4
    _PlugInfo * m_ppicInfo; // +0xD8
    float m_progress; // +0xDC
    float m_Lenth; // +0xE0
    float m_MaxVal; // +0xE4
    float m_Val; // +0xE8
    float m_radius; // +0xEC
    float m_step; // +0xF0
    int m_dragRadius; // +0xF4
    float m_lradius; // +0xF8
    float m_rradius; // +0xFC
    float m_tradius; // +0x100
    float m_bradius; // +0x104
    int m_mode; // +0x108
    int m_dir; // +0x10C
    // total size: 0x110 (272)

};
