#pragma once
// Auto-generated: CCBMagicWindow

#include "UIFrameWnd.h"

class UIListBox;
class UIPushButton;
class UIStatic;

class CCBMagicWindow : public UIFrameWnd {
public:
    UIStatic * m_pBack; // +0x48
    UIListBox * m_pMagicList[6]; // +0x4C
    UIPushButton * m_pButtonWater; // +0x64
    UIPushButton * m_pButtonFire; // +0x68
    UIPushButton * m_pButtonThunder; // +0x6C
    UIPushButton * m_pButtonWind; // +0x70
    UIPushButton * m_pButtonEarth; // +0x74
    UIPushButton * m_pButtonDouble; // +0x78
    int m_nActivePage; // +0x7C
    // total size: 0x80 (128)

    CCBMagicWindow(int a2, int a3, _DWORD *a4); // 0x0051B9F0
    ~CCBMagicWindow(); // 0x0051BAB0
    int Reset(int a2, int a3); // 0x0051BB00
    int Create(int a2); // 0x0051BB40
    _DWORD * ForbidPage(); // 0x0051BB90
    UIWnd * Destroy(CCBMagicWindow *Block, char a2); // 0x0051BBE0
    int OnMessage(); // 0x0051BC50
    char CreateButton(_DWORD *a2, int a3); // 0x0051BC70
    int Update(); // 0x0051C110
    BOOL SetActivePage(int a2, int a3); // 0x0051C1B0
    _DWORD * GetActivePage(); // 0x0051C210
};
