#pragma once
// Auto-generated: UISceneFace

#include "UIProgressBar.h"
#include "UIStatic.h"
#include "UIWnd.h"

class UISceneFace : public UIWnd {
public:
    UIProgressBar m_hp; // +0x44
    UIProgressBar m_mp; // +0x138
    UIStatic m_face[3]; // +0x22C
    UIStatic m_bk; // +0x40C
    float m_clicktime; // +0x4AC
    int m_onclick; // +0x4B0
    UIStatic m_state[4]; // +0x4B4
    // total size: 0x734 (1844)

};
