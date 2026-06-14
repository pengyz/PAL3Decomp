#include "PalScriptWaitObj.h"
#include "UIDialog.h"
#pragma once
// Auto-generated: UIRoleSelect

#include "UIListBox.h"
#include "UIStaticFlex.h"

class UIRoleSelect : public UIDialog, public PalScriptWaitObj {
public:
    char _gap_000[80]; // +0x0
    int m_sel; // +0x50
    int m_maxlen; // +0x54
    UIListBox m_list; // +0x58
    char _gap_05C[1204]; // +0x5C
    UIStaticFlex m_bk; // +0x510
    char _tail_514[188]; // +0x514
    // total size: 0x5D0 (1488)

    int SetByte(char value); // 0x004A1530
    int SetFieldLeft(int nVal); // 0x00524960
};
