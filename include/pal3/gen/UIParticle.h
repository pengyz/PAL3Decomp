#pragma once
// Auto-generated: UIParticle

#include "UIPar_TimeCtrl.h"
#include "UIStatic.h"
#include "gbColorQuad.h"
#include "tagRECT.h"

class gbTexture;

class UIParticle {
public:
    tagRECT m_viewRect; // +0x0
    int view_radiusX; // +0x10
    int view_radiusY; // +0x14
    int par_radiusX; // +0x18
    int par_radiusY; // +0x1C
    int _W; // +0x20
    int _H; // +0x24
    unsigned char m_bGetBottom; // +0x28
    unsigned char m_bBounceX; // +0x29
    float m_HelixAngle; // +0x2C
    float m_tempx; // +0x30
    float m_tempy; // +0x34
    float m_helix_rx; // +0x38
    float m_helix_ry; // +0x3C
    unsigned char m_isDiffuse; // +0x40
    float m_posx; // +0x44
    float m_posy; // +0x48
    int m_FlareTime; // +0x4C
    unsigned char m_isSubA; // +0x50
    gbColorQuad m_rainbowColor; // +0x54
    unsigned char m_bGetTop; // +0x58
    float m_riseY; // +0x5C
    int m_xflag; // +0x60
    int m_state; // +0x64
    unsigned char m_iscolorfade; // +0x68
    UIPar_TimeCtrl m_time; // +0x6C
    unsigned long m_sec; // +0x78
    gbColorQuad m_color; // +0x7C
    unsigned char _isActive; // +0x80
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
    int _sizeX; // +0x244
    int _sizeY; // +0x248
    float _speed; // +0x24C
    // total size: 0x250 (592)

};
