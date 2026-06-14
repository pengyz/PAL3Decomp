#include "UIWnd.h"
#pragma once
// Auto-generated: UIAnimateCtrl

#include "UITextureArray.h"

class UIAnimateCtrl : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    float m_FPS; // +0x44
    float m_passtime; // +0x48
    UITextureArray m_texarray; // +0x4C
    char _gap_050[64]; // +0x50
    int m_curframe; // +0x90
    int m_numframe; // +0x94
    int m_looppassed; // +0x98
    int m_nLoop; // +0x9C
    int m_mode; // +0xA0
    // total size: 0xA4 (164)

    int GetRoleBySlot(unsigned int dwVal); // 0x00479260
};
