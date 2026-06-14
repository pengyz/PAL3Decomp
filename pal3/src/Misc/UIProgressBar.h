#include "UIWnd.h"
#pragma once
// Auto-generated: UIProgressBar

#include "PGR_MODE.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbTexture.h"

class _PlugInfo;

class UIProgressBar : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    int m_mode; // +0x44
    tagRECT m_decorateRc; // +0x48
    char _gap_04C[12]; // +0x4C
    int m_progress; // +0x58
    int m_speed; // +0x5C
    int m_SetProgress; // +0x60
    int m_Lenth; // +0x64
    float m_MaxVal; // +0x68
    float m_stepval; // +0x6C
    int m_radius; // +0x70
    int m_lradius; // +0x74
    int m_rradius; // +0x78
    float m_tradius; // +0x7C
    float m_bradius; // +0x80
    int m_step; // +0x84
    float m_Val; // +0x88
    BYTE m_IsGetit; // +0x8C
    char _gap_08D[3]; // +0x8D
    gbColorQuad m_bkColor; // +0x90
    gbColorQuad m_foColor; // +0x94
    gbTexture * m_pbk; // +0x98
    _PlugInfo * m_pbkInfo; // +0x9C
    gbTexture * m_ppic; // +0xA0
    _PlugInfo * m_ppicInfo; // +0xA4
    gbTexture * m_pdecorate; // +0xA8
    _PlugInfo * m_pdecorateInfo; // +0xAC
    int m_decorateW; // +0xB0
    int m_decorateH; // +0xB4
    int m_decorateOffsetX; // +0xB8
    int m_decorateOffsetY; // +0xBC
    PGR_MODE m_pgrmode; // +0xC0
    gbColorQuad m_color; // +0xC4
    int m_dstAlpha; // +0xC8
    int m_alpha; // +0xCC
    int m_minAlpha; // +0xD0
    float m_fadespeed; // +0xD4
    BYTE m_isAdd; // +0xD8
    BYTE m_isFlash; // +0xD9
    BYTE m_stop; // +0xDA
    char _gap_0DB[1]; // +0xDB
    int m_warningval; // +0xDC
    char _tail_0E0[20]; // +0xE0
    // total size: 0xF4 (244)

    virtual void Render(); // 0x00439410
    virtual BOOL CheckRayHitRole(int nVal, int nVal2); // 0x00439A20
    virtual void Destroy(); // 0x00439810
    int * ctor(); // 0x00439030
    void FindChildByName(float fValue); // 0x0043FDF0
    static void SetRadiusWidth(int); // 0x004C6831
};
