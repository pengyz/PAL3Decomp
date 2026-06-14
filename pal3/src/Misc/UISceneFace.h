#include "UIWnd.h"
#pragma once
// Auto-generated: UISceneFace

#include "UIProgressBar.h"
#include "UIStatic.h"

class UISceneFace : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    UIProgressBar m_hp; // +0x44
    char _gap_048[240]; // +0x48
    UIProgressBar m_mp; // +0x138
    char _gap_13C[240]; // +0x13C
    UIStatic m_face[3]; // +0x22C
    char _gap_238[444]; // +0x238
    UIStatic m_bk; // +0x3F4
    char _gap_3F8[148]; // +0x3F8
    float m_clicktime; // +0x48C
    int m_onclick; // +0x490
    UIStatic m_state[4]; // +0x494
    char _tail_4A4[592]; // +0x4A4
    // total size: 0x6F4 (1780)

    int SetFaceVisible(int nVal, unsigned int dwVal); // 0x0052D010
    int ResetAllSlots(); // 0x0052D0D0
    int UpdateFacePosition(); // 0x0052D0F0
};
