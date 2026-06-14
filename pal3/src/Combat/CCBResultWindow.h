#include "UIFrameWnd.h"
#pragma once
// Auto-generated: CCBResultWindow

class CCBUI;
class UIProgressBar;
class UIStatic;

class CCBResultWindow : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
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
    char _gap_070[40]; // +0x70
    UIStatic * m_pHGM; // +0x98
    UIProgressBar * m_pHP; // +0x9C
    UIProgressBar * m_pGP; // +0xA0
    UIProgressBar * m_pMP; // +0xA4
    CCBUI * m_pUI; // +0xA8
    int m_nIndex; // +0xAC
    BYTE m_bClosed; // +0xB0
    char _tail_0B1[3]; // +0xB1
    // total size: 0xB4 (180)

    virtual BOOL IsImbibeNimbusNotFinish(int nVal, int nVal2); // 0x00519660
    virtual void ShowLineupWindow(BOOL bShow); // 0x00519360
    void _CCBResultWindow(); // 0x0043BE30
    void ctor(); // 0x00442E10
    void Create(); // 0x00443190
    CCBResultWindow(); // 0x00444A20
    int StartAnim(); // 0x00444D10
    void SetDirty(); // 0x00444D20
    int FindChildByID(int nID); // 0x00515CE0
    virtual void Reset(); // 0x0051F0A0
};
