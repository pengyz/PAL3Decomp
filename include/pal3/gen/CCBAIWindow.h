#pragma once
// Auto-generated: CCBAIWindow

#include "UIFrameWnd.h"

class UIButton;
class UIPushButton;
class UIStatic;

class CCBAIWindow : public UIFrameWnd {
public:
    UIStatic * m_pBack; // +0x48
    UIStatic * m_pName[5]; // +0x4C
    UIPushButton * m_pAttack; // +0x60
    UIPushButton * m_pItem; // +0x64
    UIPushButton * m_pSkill; // +0x68
    UIPushButton * m_pMagic; // +0x6C
    UIPushButton * m_pAffirmative; // +0x70
    UIPushButton * m_pAI; // +0x74
    UIButton * m_pOk; // +0x78
    int m_nIndex; // +0x7C
    // total size: 0x80 (128)

    int SetText(int a2, int a3); // 0x004DFE00
    CCBAIWindow(int a2); // 0x0051CA50
    ~CCBAIWindow(); // 0x0051CAA0
    static char Reset(_DWORD *a1); // 0x0051CB60
    static char Destroy(_DWORD *a1); // 0x0051CCE0
    static char OnMessage(UIListBox **a1); // 0x0051CD90
    static char Update(_DWORD *a1); // 0x0051CE40
    static char ShowWindow(_DWORD *a1); // 0x0051CF00
};
