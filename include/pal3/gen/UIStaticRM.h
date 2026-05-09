#pragma once
// Auto-generated: UIStaticRM

#include "UIS_RM_Mode.h"
#include "UIStatic.h"
#include "gbColorQuad.h"

class UIStaticRM : public UIStatic {
public:
    gbColorQuad m_color; // +0xA0
    int m_dstAlpha; // +0xA4
    int m_alpha; // +0xA8
    int m_minAlpha; // +0xAC
    float m_fadespeed; // +0xB0
    unsigned char m_isAdd; // +0xB4
    unsigned char m_isFlash; // +0xB5
    unsigned char m_stop; // +0xB6
    UIS_RM_Mode m_mode; // +0xB8
    // total size: 0xBC (188)

};
