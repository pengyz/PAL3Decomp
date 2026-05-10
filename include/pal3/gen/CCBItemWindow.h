#pragma once
// Auto-generated: CCBItemWindow

#include "UIFrameWnd.h"

class UIListBox;
class UIPushButton;
class UIStatic;

class CCBItemWindow : public UIFrameWnd {
public:
    UIStatic * m_pBack; // +0x48
    UIStatic * m_pDescription; // +0x4C
    UIListBox * m_pItemList[3]; // +0x50
    UIPushButton * m_pButtonRecover; // +0x5C
    UIPushButton * m_pButtonAttack; // +0x60
    UIPushButton * m_pButtonTreasure; // +0x64
    int m_nActivePage; // +0x68
    // total size: 0x6C (108)

    CCBItemWindow(CCBItemWindow *Block, char a2); // 0x0051B160
    int Reset(); // 0x0051B1D0
    char Create(_DWORD *a2, int a3); // 0x0051B210
    int Destroy(); // 0x0051B4B0
    BOOL HandleInput(int a2, int a3); // 0x0051B570
    int OnMessage(int a2); // 0x0051B5D0
    _DWORD * Update(); // 0x0051B620
    UIWnd * CreateButtons(CCBItemWindow *Block, char a2); // 0x0051B670
};
