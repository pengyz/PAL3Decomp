#pragma once
// Auto-generated: UITitle_BBTY

#include "MUIDialog.h"
#include "UIButton.h"
#include "UIButtonEXA.h"
#include "UIFrameWnd.h"
#include "UIStatic.h"
#include "_better_note.h"

class UICoverFrm;

class UITitle_BBTY : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    UIStatic m_background; // +0x168
    UIStatic m_remark; // +0x208
    UIButtonEXA m_btn[3]; // +0x2A8
    UIButton m_exit; // +0x710
    UIStatic m_Name; // +0x868
    UIStatic m_Left; // +0x908
    UIStatic m_Right; // +0x9A8
    UIStatic m_FlagT; // +0xA48
    UIStatic m_FlagB; // +0xAE8
    UIButton m_Start; // +0xB88
    UIButton m_Notes; // +0xCE0
    UIButton m_Exit; // +0xE38
    MUIDialog m_Msg; // +0xF90
    _better_note m_appr_note; // +0x14F8
    UINT m_gamestate; // +0x1500
    BYTE m_isgoto; // +0x1504
    UICoverFrm * m_pMgr; // +0x1508
    // total size: 0x150C (5388)

};
