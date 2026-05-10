#pragma once
// Auto-generated: UIRoleSelectDialog

#include "UIAnimateCtrl.h"
#include "UIDialog.h"
#include "UIListBox.h"
#include "UIStaticFlex.h"
#include "UIStaticFlip.h"
#include "UITextArea.h"

class UIRoleSelectDialog : public UIDialog {
public:
    int m_state; // +0x48
    UIStaticFlex m_bk; // +0x4C
    UIAnimateCtrl m_ani; // +0x10C
    UIStaticFlip m_face; // +0x1B0
    UITextArea m_static; // +0x254
    int m_texth; // +0x2BC
    UIListBox m_list; // +0x2C0
    int m_maxlen; // +0x7C8
    float m_last; // +0x7CC
    int m_sel; // +0x7D0
    int m_mode; // +0x7D4
    // total size: 0x7D8 (2008)

};
