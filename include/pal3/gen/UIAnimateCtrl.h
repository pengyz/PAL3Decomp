#pragma once
// Auto-generated: UIAnimateCtrl

#include "UITextureArray.h"
#include "UIWnd.h"

class UIAnimateCtrl : public UIWnd {
public:
    float m_FPS; // +0x44
    float m_passtime; // +0x48
    UITextureArray m_texarray; // +0x4C
    int m_curframe; // +0x90
    int m_numframe; // +0x94
    int m_looppassed; // +0x98
    int m_nLoop; // +0x9C
    int m_mode; // +0xA0
    // total size: 0xA4 (164)

};
