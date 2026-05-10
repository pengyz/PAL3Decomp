#pragma once
// Auto-generated: Comp_DonateUI

#include "Comp_Donate_Detail.h"
#include "LineupComp.h"
#include "MUIDialog.h"
#include "UIButton.h"
#include "UIFrameWnd.h"
#include "UIRoleDialog.h"
#include "UIRoleSelect.h"
#include "UIStatic.h"

class Comp_DonateUI : public UIFrameWnd {
public:
    int m_RoleId; // +0x48
    Comp_Donate_Detail m_CompDonate[10]; // +0x4C
    int m_keynum; // +0x164
    int m_curitem; // +0x168
    struct CDState {}; // nested type stub
    CDState m_state[10]; // +0x16C
    char m_lang[256][16][5]; // +0x194
    UIStatic m_OutFrameT; // +0x5194
    UIStatic m_OutFrameR; // +0x5234
    UIStatic m_OutFrameL; // +0x52D4
    UIStatic m_OutFrameB; // +0x5374
    UIStatic m_TopFrame; // +0x5414
    UIButton m_ExitBtn; // +0x54B4
    UIButton m_Btn[10]; // +0x560C
    UIStatic m_BtnStatic[10]; // +0x637C
    int m_mouseon; // +0x69BC
    UIRoleDialog m_RoleDlg; // +0x69C0
    UIRoleSelect m_SelectDlg; // +0x6C90
    unsigned char m_IfSel; // +0x72B0
    unsigned char m_IfGetSel; // +0x72B1
    tagRECT m_RoleDlgRc; // +0x72B4
    int m_AddIntimacyDonate[5]; // +0x72C4
    int m_AddIntimacyComp[5]; // +0x72D8
    char m_RoleLang[512][4][5]; // +0x72EC
    int m_SelBtn; // +0x9AEC
    MUIDialog m_Msg; // +0x9AF0
    MUIDialog m_ActiveDlg; // +0xA058
    MUIDialog m_ExitDlg; // +0xA5C0
    unsigned char m_IsActive; // +0xAB28
    unsigned char m_IsOver; // +0xAB29
    LineupComp m_LineupComp; // +0xAB2C
    UIStatic m_BK; // +0xB308
    // total size: 0xB3A8 (45992)

};
