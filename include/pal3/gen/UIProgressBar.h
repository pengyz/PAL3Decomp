#pragma once
// Auto-generated: UIProgressBar

#include "PGR_MODE.h"
#include "UIWnd.h"

class _PlugInfo;

class UIProgressBar : public UIWnd {
public:
    int m_mode; // +0x44
    int m_dir; // +0x48
    tagRECT m_ProgressRc; // +0x4C
    tagRECT m_decorateRc; // +0x5C
    float m_progress; // +0x6C
    float m_speed; // +0x70
    float m_SetProgress; // +0x74
    float m_Lenth; // +0x78
    float m_MaxVal; // +0x7C
    float m_stepval; // +0x80
    float m_radius; // +0x84
    float m_lradius; // +0x88
    float m_rradius; // +0x8C
    float m_tradius; // +0x90
    float m_bradius; // +0x94
    float m_step; // +0x98
    float m_Val; // +0x9C
    unsigned char m_IsGetit; // +0xA0
    gbColorQuad m_bkColor; // +0xA4
    gbColorQuad m_foColor; // +0xA8
    gbTexture * m_pbk; // +0xAC
    _PlugInfo * m_pbkInfo; // +0xB0
    gbTexture * m_ppic; // +0xB4
    _PlugInfo * m_ppicInfo; // +0xB8
    gbTexture * m_pdecorate; // +0xBC
    _PlugInfo * m_pdecorateInfo; // +0xC0
    int m_decorateW; // +0xC4
    int m_decorateH; // +0xC8
    int m_decorateOffsetX; // +0xCC
    int m_decorateOffsetY; // +0xD0
    PGR_MODE m_pgrmode; // +0xD4
    gbColorQuad m_color; // +0xD8
    int m_dstAlpha; // +0xDC
    int m_alpha; // +0xE0
    int m_minAlpha; // +0xE4
    float m_fadespeed; // +0xE8
    unsigned char m_isAdd; // +0xEC
    unsigned char m_isFlash; // +0xED
    unsigned char m_stop; // +0xEE
    int m_warningval; // +0xF0
    // total size: 0xF4 (244)

};
