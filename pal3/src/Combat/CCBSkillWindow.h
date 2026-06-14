#include "UIFrameWnd.h"
#pragma once
// Auto-generated: CCBSkillWindow

class CCBAIWindow;
class UIListBox;
class UIStatic;

class CCBSkillWindow : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    UIStatic * m_pBack; // +0x48
    UIStatic * m_pDescription; // +0x4C
    UIListBox * m_pSkillList[1]; // +0x50
    // total size: 0x54 (84)

    virtual ~CCBSkillWindow() {}

    virtual void Destroy(); // 0x0051BBE0
    virtual CCBAIWindow * ToggleSlots(int nVal); // 0x0051CA50
    virtual void Render(); // 0x0051CAA0
    virtual BOOL Update(int deltatime, int haveinput); // 0x0051C9F0
    virtual int Destroy_c880(); // 0x0051C880
    void _CCBSkillWindow(); // 0x0051BC00
    void Reset(); // 0x0051C2D0
    bool Create(int *pRect, int parent); // 0x0051C330
};
