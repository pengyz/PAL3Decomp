#pragma once
// Auto-generated: CCBControlWindow

#include "UIFrameWnd.h"

class UIButton;
class UIStatic;

class CCBControlWindow : public UIFrameWnd {
public:
    UIStatic * m_pBack; // +0x48
    UIButton * m_pButtonAttack; // +0x4C
    UIButton * m_pButtonSkill; // +0x50
    UIButton * m_pButtonMagic; // +0x54
    UIButton * m_pButtonItem; // +0x58
    UIButton * m_pButtonDefence; // +0x5C
    UIButton * m_pButtonLineup; // +0x60
    UIButton * m_pButtonAI; // +0x64
    UIButton * m_pButtonFlee; // +0x68
    UIButton * m_pButtonProtect; // +0x6C
    int m_CurCtrl; // +0x70
    // total size: 0x74 (116)

    CCBControlWindow(); // 0x0051A700
    ~CCBControlWindow(); // 0x0051A880
    int Reset(int a2, unsigned int a3, int a4); // 0x0051A930
    char Create(_DWORD *a2, int a3, int a4, int a5); // 0x0051AA20
    int HandleInput(int a2); // 0x0051AB60
    int KeyPressed(); // 0x0051AC30
    _DWORD * DefaultKey(); // 0x0051AC40
    UIWnd * HandleEnable(CCBControlWindow *Block, char a2); // 0x0051AC90
    int CheckKeyInput(); // 0x0051AD00
    char OnMessage(_DWORD *pRect, int parent); // 0x0051AD10
    int Update(); // 0x0051AFE0
    BOOL MoveButtons(int a2, int a3); // 0x0051B0B0
    _DWORD * CreateButton(); // 0x0051B110
};
