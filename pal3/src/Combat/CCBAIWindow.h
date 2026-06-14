#include "UIFrameWnd.h"
#pragma once
// Auto-generated: CCBAIWindow

class CCBControlWindow;
class CCBUI;
class UIButton;
class UIListBox;
class UIPushButton;
class UIStatic;

class CCBAIWindow : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    UIStatic * m_pBack; // +0x48
    UIStatic * m_pName[5]; // +0x4C
    char _gap_050[16]; // +0x50
    UIPushButton * m_pAttack; // +0x60
    UIPushButton * m_pItem; // +0x64
    UIPushButton * m_pSkill; // +0x68
    UIPushButton * m_pMagic; // +0x6C
    UIPushButton * m_pAffirmative; // +0x70
    UIPushButton * m_pAI; // +0x74
    UIButton * m_pOk; // +0x78
    int m_nIndex; // +0x7C
    char _tail_080[80]; // +0x80
    // total size: 0xD0 (208)

    void Reset(int *p_DWORD); // 0x0051CB60
    void Destroy(); // 0x0051CCE0
    char OnMessage(UIListBox **msg); // 0x0051CD90
    char Update(CCBUI **deltatime); // 0x0051CE40
    char ShowWindow(CCBControlWindow **show); // 0x0051CF00
};
