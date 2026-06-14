#include "UIWnd.h"
#pragma once
// Auto-generated: UIDragBar

#include "gbengine/gbengine_types.h"
#include "gbengine/gbTexture.h"

class UIWnd;
class _PlugInfo;

class UIDragBar : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    UIWnd * p_Wnd; // +0x44
    int m_SX; // +0x48
    int m_SY; // +0x4C
    int m_xOffSet; // +0x50
    BYTE m_bDrag; // +0x54
    BYTE m_bClick; // +0x55
    char _gap_056[2]; // +0x56
    int m_DragState; // +0x58
    tagPOINT m_lastPt; // +0x5C
    char _gap_060[4]; // +0x60
    tagRECT m_DragRc; // +0x64
    char _gap_068[12]; // +0x68
    tagRECT m_bkRc; // +0x74
    char _gap_078[12]; // +0x78
    tagRECT m_ProgressRc; // +0x84
    char _gap_088[12]; // +0x88
    gbColorQuad m_DragColor; // +0x94
    gbColorQuad m_bkColor; // +0x98
    gbColorQuad m_foColor; // +0x9C
    gbTexture * m_DragTex[3]; // +0xA0
    char _gap_0A4[8]; // +0xA4
    _PlugInfo * m_DragTexInfo[3]; // +0xAC
    char _gap_0B0[8]; // +0xB0
    gbTexture * m_pbk; // +0xB8
    _PlugInfo * m_pbkInfo; // +0xBC
    gbTexture * m_ppic; // +0xC0
    _PlugInfo * m_ppicInfo; // +0xC4
    float m_progress; // +0xC8
    float m_Lenth; // +0xCC
    float m_MaxVal; // +0xD0
    float m_Val; // +0xD4
    float m_radius; // +0xD8
    float m_step; // +0xDC
    int m_dragRadius; // +0xE0
    float m_lradius; // +0xE4
    float m_rradius; // +0xE8
    float m_tradius; // +0xEC
    float m_bradius; // +0xF0
    int m_mode; // +0xF4
    int m_dir; // +0xF8
    char _tail_0FC[20]; // +0xFC
    // total size: 0x110 (272)

};
