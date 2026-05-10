#pragma once
// Auto-generated: UIRoleDialog

#include "PalScriptWaitObj.h"
#include "UIAnimateCtrl.h"
#include "UIDialog.h"
#include "UIStatic.h"
#include "UIStaticFlip.h"
#include "UITextArea.h"

class UIRoleDialog : public UIDialog, public PalScriptWaitObj {
public:
    UIStatic m_bk; // +0x50
    UIAnimateCtrl m_ani; // +0xF0
    UIStaticFlip m_face; // +0x194
    UITextArea m_static; // +0x238
    float m_fPosY; // +0x2A0
    float m_SfPosY; // +0x2A4
    unsigned char m_bReady; // +0x2A8
    int m_dlgh; // +0x2AC
    tagRECT m_bkRc; // +0x2B0
    int m_mode; // +0x2C0
    int m_leftright; // +0x2C4
    float m_time; // +0x2C8
    int m_sel; // +0x2CC
    // total size: 0x2D0 (720)

};
