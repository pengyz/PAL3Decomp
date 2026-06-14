#include "PalScriptWaitObj.h"
#include "UIFrameWnd.h"
#pragma once
// Auto-generated: ChoseCompose

#include "UIButton.h"
#include "UIStatic.h"
#include "UIStaticFlex.h"

class ChoseCompose : public UIFrameWnd, public PalScriptWaitObj {
public:
    char _gap_000[80]; // +0x0
    tagRECT rc; // +0x50
    char _gap_054[12]; // +0x54
    int bkWndX; // +0x60
    int bkWndY; // +0x64
    int i; // +0x68
    int j; // +0x6C
    char buf[256]; // +0x70
    tagRECT bkRc; // +0x170
    char _gap_174[12]; // +0x174
    UINT m_id; // +0x180
    BYTE m_isExit; // +0x184
    char _gap_185[3]; // +0x185
    UIStaticFlex m_bk; // +0x188
    char _gap_18C[188]; // +0x18C
    UIStatic m_ComposeInfo; // +0x248
    char _gap_24C[156]; // +0x24C
    UIButton m_RoleName[5]; // +0x2E8
    char _tail_2FC[3006]; // +0x2FC
    // total size: 0xEBA (3770)

    void Init(int nVal); // 0x0044C970
    void DestroyScene(); // 0x004549A0
    void _ChoseCompose(); // 0x00454AA0
    int LayoutItems(int arg0, int nVal, int nVal2, int nVal3, int nVal4); // 0x00455570
    void Method_4A2170(); // 0x004A2170
    void DestroySubWindows(); // 0x004A22E0
    int LayoutItem(int arg0, int nVal, int nVal2, int nVal3, int nVal4); // 0x004B19E0
};
