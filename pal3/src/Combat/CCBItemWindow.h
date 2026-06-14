#include "UIFrameWnd.h"
#pragma once
// Auto-generated: CCBItemWindow

class UIListBox;
class UIPushButton;
class UIStatic;
class UIWnd;

class CCBItemWindow : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    UIStatic * m_pBack; // +0x48
    UIStatic * m_pDescription; // +0x4C
    UIListBox * m_pItemList[3]; // +0x50
    char _gap_054[8]; // +0x54
    UIPushButton * m_pButtonRecover; // +0x5C
    UIPushButton * m_pButtonAttack; // +0x60
    UIPushButton * m_pButtonTreasure; // +0x64
    int m_nActivePage; // +0x68
    char _tail_06C[80]; // +0x6C
    // total size: 0xBC (188)

    virtual ~CCBItemWindow() {}

    virtual int HandleMessage(int nVal, unsigned int nMsg, int wParam); // 0x0051A930
    CCBItemWindow(); // 0x004461B0
    char * SetItemName(char *pszName); // 0x00450650
    void _CCBItemWindow(); // 0x0051A3B0
    void Reset(); // 0x0051B1D0
    bool Create(int *pRect, int parent); // 0x0051B210
    virtual void Destroy(CCBItemWindow *thisa); // 0x0051B4B0
    virtual int OnMessage(CCBItemWindow *thisa, unsigned int a2, unsigned int a4, unsigned int a5); // 0x0051B5D0
    UIListBox * Update(); // 0x0051B620
    UIWnd * CreateButtons(CCBItemWindow *Block, char pData); // 0x0051B670
};
