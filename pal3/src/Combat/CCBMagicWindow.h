#include "UIFrameWnd.h"
#pragma once
// Auto-generated: CCBMagicWindow

class UIListBox;
class UIPushButton;
class UIStatic;

class CCBMagicWindow : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    UIStatic * m_pBack; // +0x48
    UIListBox * m_pMagicList[6]; // +0x4C
    char _gap_050[20]; // +0x50
    UIPushButton * m_pButtonWater; // +0x64
    UIPushButton * m_pButtonFire; // +0x68
    UIPushButton * m_pButtonThunder; // +0x6C
    UIPushButton * m_pButtonWind; // +0x70
    UIPushButton * m_pButtonEarth; // +0x74
    UIPushButton * m_pButtonDouble; // +0x78
    int m_nActivePage; // +0x7C
    char _gap_080[56]; // +0x80
    int m_nBtnX; // +0xB8
    char _gap_0BC[8]; // +0xBC
    int m_nBtnY; // +0xC4
    int m_nBtnState; // +0xC8
    char _tail_0CC[4]; // +0xCC
    // total size: 0xD0 (208)

    virtual ~CCBMagicWindow() {}

    virtual int OnMessage(int nVal, int nVal2, int nVal3); // 0x0051B860
    CCBMagicWindow(int nVal, int nVal2, int *p_DWORD); // 0x0051B9F0
    void _CCBMagicWindow(int nVal); // 0x0051BAB0
    void Reset(int nVal, int nVal2); // 0x0051BB00
    bool Create(int rc); // 0x0051BB40
    UIListBox * ForbidPage(); // 0x0051BB90
    int ClearMagicData(); // 0x0051BC50
    bool CreateButton(int *ppButton, int id); // 0x0051BC70
    virtual void Destroy(); // 0x0051C110
    virtual BOOL SetActivePage(int n, int nVal); // 0x0051C1B0
    UIListBox * GetActivePage(); // 0x0051C210
};
