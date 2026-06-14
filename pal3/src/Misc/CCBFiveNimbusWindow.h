#include "UIFrameWnd.h"
#pragma once
// Auto-generated: CCBFiveNimbusWindow

#include "OpenFNWindow.h"

class CCBItemWindow;
class CCBSkillWindow;
class UIButtonEX;

class CCBFiveNimbusWindow : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    UIButtonEX * pCtrlButton[5]; // +0x48
    char _gap_04C[16]; // +0x4C
    UIButtonEX * pMiddle; // +0x5C
    OpenFNWindow m_OpenWindow; // +0x60
    char _gap_064[8]; // +0x64
    int m_nimbus[5]; // +0x6C
    int m_state[5]; // +0x80
    int m_nimbusStep; // +0x94
    BYTE m_bShow; // +0x98
    BYTE m_bLock; // +0x99
    char _gap_09A[2]; // +0x9A
    int m_counter; // +0x9C
    // total size: 0xA0 (160)

    virtual int HandleInput(int a2, unsigned int nVal, int nVal2); // 0x00519FE0
    int * CreateScriptAndCamera(int id, int parent); // 0x00439740
    int SetFloatParam(float value); // 0x0043A070
    int CalcHitAngle(int nVal); // 0x0043FD20
    int UpdateDisplay(); // 0x00443AF0
    bool IsHitLeft(float fVal); // 0x00443BA0
    bool IsAboveThreshold(float fVal); // 0x00443BF0
    bool IsHitRight(float fVal); // 0x00443C20
    bool IsHitBottom(float fVal); // 0x00443C70
    void _CCBFiveNimbusWindow(); // 0x00519B60
    virtual void HandleInput(CCBItemWindow *thisa); // 0x0051B570
    virtual int OnMessage(CCBSkillWindow *thisa, unsigned int a3, unsigned int a2, unsigned int a5); // 0x0051C9B0
    char UpdateAnimation(int nVal); // 0x0052E2F0
    int fn_52F300(int nVal); // 0x0052F300
    int GetSlotA(int nVal); // 0x0052FBB0
    int GetSlotB(int nVal); // 0x0052FC30
    int ApplySelection(int nVal); // 0x00530BC0
};
