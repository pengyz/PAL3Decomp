#pragma once
// Auto-generated: UIParticle

#include "UIPar_TimeCtrl.h"
#include "UIStatic.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbTexture.h"

class UIParticle {
public:
    tagRECT m_viewRect; // +0x0
    char _gap_004[12]; // +0x4
    int view_radiusX; // +0x10
    int view_radiusY; // +0x14
    int par_radiusX; // +0x18
    int par_radiusY; // +0x1C
    int _W; // +0x20
    int _H; // +0x24
    BYTE m_bGetBottom; // +0x28
    BYTE m_bBounceX; // +0x29
    char _gap_02A[2]; // +0x2A
    float m_HelixAngle; // +0x2C
    float m_tempx; // +0x30
    float m_tempy; // +0x34
    float m_helix_rx; // +0x38
    float m_helix_ry; // +0x3C
    BYTE m_isDiffuse; // +0x40
    char _gap_041[3]; // +0x41
    float m_posx; // +0x44
    float m_posy; // +0x48
    int m_FlareTime; // +0x4C
    BYTE m_isSubA; // +0x50
    char _gap_051[3]; // +0x51
    gbColorQuad m_rainbowColor; // +0x54
    BYTE m_bGetTop; // +0x58
    char _gap_059[3]; // +0x59
    float m_riseY; // +0x5C
    int m_xflag; // +0x60
    int m_state; // +0x64
    BYTE m_iscolorfade; // +0x68
    char _gap_069[3]; // +0x69
    UIPar_TimeCtrl m_time; // +0x6C
    char _gap_070[8]; // +0x70
    UINT m_sec; // +0x78
    gbColorQuad m_color; // +0x7C
    BYTE _isActive; // +0x80
    char _gap_081[3]; // +0x81
    float _fade; // +0x84
    float _x; // +0x88
    float _y; // +0x8C
    float _xi; // +0x90
    float _yi; // +0x94
    float _xg; // +0x98
    float _yg; // +0x9C
    char _texName[256]; // +0xA0
    gbTexture * _ptex; // +0x1A0
    UIStatic _element; // +0x1A4
    char _gap_1A8[148]; // +0x1A8
    int _sizeX; // +0x23C
    int _sizeY; // +0x240
    float _speed; // +0x244
    // total size: 0x248 (584)

    static int * CountActiveParticles(int *p_DWORD); // 0x00529400
};
