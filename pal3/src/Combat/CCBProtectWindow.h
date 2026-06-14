#include "UIFrameWnd.h"
#pragma once
// Auto-generated: CCBProtectWindow

class UIButton;
class UIProgressBar;
class UIPushButton;
class UIStatic;

class CCBProtectWindow : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    UIStatic * m_pBack; // +0x48
    UIPushButton * m_pWHFace; // +0x4C
    UIPushButton * m_pWPXFace; // +0x50
    UIProgressBar * m_pWHLove; // +0x54
    UIProgressBar * m_pWPXLove; // +0x58
    UIButton * m_pOk; // +0x5C
    char _tail_060[80]; // +0x60
    // total size: 0xB0 (176)

    virtual ~CCBProtectWindow() {}

    virtual BOOL ShowAndNotify(int nVal, int nVal2); // 0x00518E30
    virtual CCBProtectWindow * _sdtor_19(CCBProtectWindow *Block, char a2); // 0x00516100
    virtual int ForwardOnMessage(int nVal, int nMsg, int wParam); // 0x0043D7A0
    char ValidateSlot(unsigned int dwVal); // 0x00449BE0
    CCBProtectWindow(); // 0x0051D6E0
    void _CCBProtectWindow(); // 0x0051D6F0
    void Reset(); // 0x0051D700
    virtual void Destroy(); // 0x0051DD80
    virtual int OnMessage(int nVal, int nVal2, int nVal3); // 0x0051F1B0
};
