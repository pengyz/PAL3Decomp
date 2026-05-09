#pragma once
// Auto-generated: CCBProtectWindow

#include "UIFrameWnd.h"

class UIButton;
class UIProgressBar;
class UIPushButton;
class UIStatic;

class CCBProtectWindow : public UIFrameWnd {
public:
    UIStatic * m_pBack; // +0x48
    UIPushButton * m_pWHFace; // +0x4C
    UIPushButton * m_pWPXFace; // +0x50
    UIProgressBar * m_pWHLove; // +0x54
    UIProgressBar * m_pWPXLove; // +0x58
    UIButton * m_pOk; // +0x5C
    // total size: 0x60 (96)

    CCBProtectWindow(); // 0x0051D6E0
    ~CCBProtectWindow(); // 0x0051D6F0
    static void Reset(); // 0x0051D700
    int Create(); // 0x0051D710
    stdiobuf * Destroy(stdiobuf *Block, char a2); // 0x0051DD80
    void ShowWindow(); // 0x0051DDA0
    int Update(int a2); // 0x0051F070
};
