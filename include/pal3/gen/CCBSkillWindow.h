#pragma once
// Auto-generated: CCBSkillWindow

#include "UIFrameWnd.h"

class UIListBox;
class UIStatic;

class CCBSkillWindow : public UIFrameWnd {
public:
    UIStatic * m_pBack; // +0x48
    UIStatic * m_pDescription; // +0x4C
    UIListBox * m_pSkillList[1]; // +0x50
    // total size: 0x54 (84)

    CCBSkillWindow(UIWnd *Block, char a2); // 0x0051C260
    int Reset(); // 0x0051C2D0
    char Create(_DWORD *a2, int a3); // 0x0051C330
    int Destroy(); // 0x0051C880
    int OnMessage(int a2, int a3, int a4); // 0x0051C9B0
    BOOL Update(int a2, int a3); // 0x0051C9F0
};
