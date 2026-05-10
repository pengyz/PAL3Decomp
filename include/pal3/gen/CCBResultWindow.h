#pragma once
// Auto-generated: CCBResultWindow

#include "UIFrameWnd.h"

class CCBUI;
class UIProgressBar;
class UIStatic;

class CCBResultWindow : public UIFrameWnd {
public:
    UIStatic * m_pBack; // +0x48
    UIStatic * m_pWind; // +0x4C
    UIStatic * m_pThunder; // +0x50
    UIStatic * m_pWater; // +0x54
    UIStatic * m_pFire; // +0x58
    UIStatic * m_pEarth; // +0x5C
    UIStatic * m_pDouble; // +0x60
    UIStatic * m_pEXP; // +0x64
    UIStatic * m_pLevel; // +0x68
    UIStatic * m_pFace[11]; // +0x6C
    UIStatic * m_pHGM; // +0x98
    UIProgressBar * m_pHP; // +0x9C
    UIProgressBar * m_pGP; // +0xA0
    UIProgressBar * m_pMP; // +0xA4
    CCBUI * m_pUI; // +0xA8
    int m_nIndex; // +0xAC
    unsigned char m_bClosed; // +0xB0
    // total size: 0xB4 (180)

    CCBResultWindow(int a2); // 0x0051F080
    ~CCBResultWindow(); // 0x0051F090
    int Reset(int a2, int a3); // 0x0051F0A0
};
