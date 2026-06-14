#include "UIFrameWnd.h"
#pragma once
// Auto-generated: CCBControlWindow

class UIButton;
class UIListBox;
class UIStatic;
class UIWnd;

class CCBControlWindow : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
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
    char _tail_074[80]; // +0x74
    // total size: 0xC4 (196)

    virtual void Render(CCBMagicWindow *thisa); // 0x0043DDF0
    virtual BOOL MoveButtons(int nVal, int nVal2); // 0x0051B0B0
    int Update(float, int); // 0x0051AFE0
    virtual UIWnd * HandleEnable(CCBControlWindow *Block, char dir); // 0x0051AC90
    virtual int OnMessage(int nVal, int a2, int a3); // 0x0051B030
    CCBControlWindow(); // 0x0051A700
    bool Create(tagRECT *rc, UIWnd *pFather, int nVal, int nVal2); // 0x0051AA20
    UIButton * HandleInput(UIButton *pButton); // 0x0051AB60
    void KeyPressed(); // 0x0051AC30
    UIListBox * DefaultKey(); // 0x0051AC40
    void _CCBControlWindow(); // 0x0051ACB0
    void CheckKeyInput(); // 0x0051AD00
    char OnMessage(int *pRect, int parent); // 0x0051AD10
    UIListBox * CreateButton(); // 0x0051B110
};
