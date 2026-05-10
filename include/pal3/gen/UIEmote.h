#pragma once
// Auto-generated: UIEmote

#include "PalScriptWaitObj.h"
#include "UIAnimateCtrl.h"
#include "UIEMOTE.h"
#include "UIWnd.h"

class Role;

class UIEmote : public UIWnd, public PalScriptWaitObj {
public:
    UIEMOTE m_cur; // +0x4C
    UIAnimateCtrl m_ani[14]; // +0x50
    Role * m_role; // +0x948
    int m_loopcount; // +0x94C
    int m_nLoop[14]; // +0x950
    // total size: 0x988 (2440)

};
