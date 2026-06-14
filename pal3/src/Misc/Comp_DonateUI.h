#include "UIFrameWnd.h"
#pragma once
// Auto-generated: Comp_DonateUI

#include "Comp_Donate_Detail.h"
#include "LineupComp.h"
#include "MUIDialog.h"
#include "UIButton.h"
#include "UIRoleDialog.h"
#include "UIRoleSelect.h"
#include "UIStatic.h"

class Comp_DonateUI : public UIFrameWnd {
public:


    enum CDState {
        CD_NONE = 0,
        CD_HASKEY = 1,
        CD_DONATED = 2,
        CD_NOSOURCE = 3,
        CD_NOINTIMACY = 4,
        CD_CANCOMPOSE = 5,
        CD_COMPOSED = 6,
        CD_NUM = 7,
    };
    char _gap_000[72]; // +0x0
    int m_RoleId; // +0x48
    Comp_Donate_Detail m_CompDonate[10]; // +0x4C
    char _gap_074[240]; // +0x74
    int m_keynum; // +0x164
    int m_curitem; // +0x168
    CDState m_state[10]; // +0x16C
    char m_lang[256][16][5]; // +0x194
    UIStatic m_OutFrameT; // +0x5194
    char _gap_5198[156]; // +0x5198
    UIStatic m_OutFrameR; // +0x5234
    char _gap_5238[156]; // +0x5238
    UIStatic m_OutFrameL; // +0x52D4
    char _gap_52D8[156]; // +0x52D8
    UIStatic m_OutFrameB; // +0x5374
    char _gap_5378[156]; // +0x5378
    UIStatic m_TopFrame; // +0x5414
    char _gap_5418[156]; // +0x5418
    UIButton m_ExitBtn; // +0x54B4
    char _gap_54B8[340]; // +0x54B8
    UIButton m_Btn[10]; // +0x560C
    char _gap_5634[3400]; // +0x5634
    UIStatic m_BtnStatic[10]; // +0x637C
    char _gap_63A4[1560]; // +0x63A4
    int m_mouseon; // +0x69BC
    UIRoleDialog m_RoleDlg; // +0x69C0
    char _gap_69C4[716]; // +0x69C4
    UIRoleSelect m_SelectDlg; // +0x6C90
    char _gap_6C94[1564]; // +0x6C94
    BYTE m_IfSel; // +0x72B0
    BYTE m_IfGetSel; // +0x72B1
    char _gap_72B2[2]; // +0x72B2
    tagRECT m_RoleDlgRc; // +0x72B4
    char _gap_72B8[12]; // +0x72B8
    int m_AddIntimacyDonate[5]; // +0x72C4
    int m_AddIntimacyComp[5]; // +0x72D8
    char m_RoleLang[512][4][5]; // +0x72EC
    int m_SelBtn; // +0x9AEC
    MUIDialog m_Msg; // +0x9AF0
    char _gap_9AF4[1380]; // +0x9AF4
    MUIDialog m_ActiveDlg; // +0xA058
    char _gap_A05C[1380]; // +0xA05C
    MUIDialog m_ExitDlg; // +0xA5C0
    char _gap_A5C4[1380]; // +0xA5C4
    BYTE m_IsActive; // +0xAB28
    BYTE m_IsOver; // +0xAB29
    char _gap_AB2A[2]; // +0xAB2A
    LineupComp m_LineupComp; // +0xAB2C
    char _gap_AB30[2008]; // +0xAB30
    UIStatic m_BK; // +0xB308
    char _tail_B30C[356]; // +0xB30C
    // total size: 0xB470 (46192)

    BOOL ProcessInput(); // 0x004A6030
};
