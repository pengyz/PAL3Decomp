#pragma once
// Auto-generated: UIRoleSelect

#include "PalScriptWaitObj.h"
#include "UIDialog.h"
#include "UIListBox.h"
#include "UIStaticFlex.h"

class UIRoleSelect : public UIDialog, public PalScriptWaitObj {
public:
    int m_sel; // +0x50
    int m_maxlen; // +0x54
    UIListBox m_list; // +0x58
    UIStaticFlex m_bk; // +0x560
    // total size: 0x620 (1568)

};
