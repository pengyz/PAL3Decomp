#include "UIFrameWnd.h"
#include "MUIDialogMgr.h"
#include "UIDialog.h"
#pragma once
// Auto-generated: MUIDialog

#include "UIStatic.h"

class MUIDialog : public UIDialog, public MUIDialogMgr, public UIFrameWnd {
public:
    char _gap_000[304]; // +0x0
    UIStatic m_static; // +0x130
    char _gap_134[156]; // +0x134
    UIStatic m_text; // +0x1D0
    char _gap_1D4[156]; // +0x1D4
    int m_btnW; // +0x270
    int m_btnH; // +0x274
    tagRECT m_btRc; // +0x278
    char _tail_27C[652]; // +0x27C
    // total size: 0x508 (1288)

    int GetPlayerAttField(int nVal, int nVal2); // 0x0049CEC0
    char InvokeCallback(); // 0x004A1620
    void SetSlotCaption(int a2); // 0x00527130
};
