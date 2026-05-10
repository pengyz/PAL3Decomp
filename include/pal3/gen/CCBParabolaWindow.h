#pragma once
// Auto-generated: CCBParabolaWindow

#include "UIFrameWnd.h"

class UIListBox;
class UIStatic;

class CCBParabolaWindow : public UIFrameWnd {
public:
    UIStatic * m_pBack; // +0x48
    UIStatic * m_pDescription; // +0x4C
    UIListBox * m_pItemList; // +0x50
    // total size: 0x54 (84)

    int Reset(int a2, int a3, int a4); // 0x0051B860
    int Destroy(); // 0x0051B920
    bool OnMessage(int a2, int a3, int a4); // 0x0051B950
    int Update(int a2, int a3); // 0x0051B9A0
};
