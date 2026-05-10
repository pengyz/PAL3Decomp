#pragma once
// Auto-generated: ChoseCompose

#include "MUIDialog.h"
#include "PalScriptWaitObj.h"
#include "UIButton.h"
#include "UIFrameWnd.h"
#include "UIStatic.h"
#include "UIStaticFlex.h"

class ChoseCompose : public UIFrameWnd, public PalScriptWaitObj {
public:
    tagRECT rc; // +0x50
    int bkWndX; // +0x60
    int bkWndY; // +0x64
    int i; // +0x68
    int j; // +0x6C
    char buf[256]; // +0x70
    tagRECT bkRc; // +0x170
    unsigned long m_id; // +0x180
    unsigned char m_isExit; // +0x184
    UIStaticFlex m_bk; // +0x188
    UIStatic m_ComposeInfo; // +0x248
    UIButton m_RoleName[5]; // +0x2E8
    MUIDialog m_Msg; // +0x9A0
    unsigned char m_isCtrl[5]; // +0xF08
    unsigned char m_isActive; // +0xF0D
    unsigned char m_isExtented; // +0xF0E
    // total size: 0xF10 (3856)

};
