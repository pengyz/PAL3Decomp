#pragma once
// Auto-generated: MainEquipUI

#include "MUIDialog.h"
#include "PlayerItem_Type.h"
#include "RoleAtt.h"
#include "UI3DCtrl.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIFrameWnd.h"
#include "UIListBox.h"
#include "UIParticle.h"
#include "UIStatic.h"
#include "me_RoleState.h"

class StateUI;

class MainEquipUI : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    unsigned char m_IsMsg; // +0x168
    unsigned char m_Is[5]; // +0x169
    unsigned char m_IsActive; // +0x16E
    unsigned char m_IsCreateable; // +0x16F
    int m_SelNum; // +0x170
    int m_PutOnType; // +0x174
    PlayerItem_Type m_CurType; // +0x178
    StateUI * pStateUI; // +0x17C
    UIStatic m_Frame; // +0x180
    UIStatic m_TimeMoney; // +0x220
    UIStatic m_TopFrame; // +0x2C0
    UIStatic m_TopFrameZB; // +0x360
    UIStatic m_ScrollHB; // +0x400
    UIStatic m_OutFrameT; // +0x4A0
    UIStatic m_OutFrameR; // +0x540
    UIStatic m_OutFrameL; // +0x5E0
    UIStatic m_OutFrameB; // +0x680
    UIStatic stp_BarL; // +0x720
    UIFlexBar stp_BarM; // +0x7C0
    UIStatic stp_BarR; // +0x814
    UIButton stp_State; // +0x8B4
    UIButton stp_Magic; // +0xA0C
    UIButton stp_Equip; // +0xB64
    UIButton stp_Prop; // +0xCBC
    UIButton stp_BattleArray; // +0xE14
    UIButton stp_TaskBook; // +0xF6C
    UIButton stp_System; // +0x10C4
    UIButton stp_Exit; // +0x121C
    UIStatic stp_Effect; // +0x1374
    tagRECT stp_Rect; // +0x1414
    UIStatic m_GameTime; // +0x1424
    UIStatic m_GameMoney; // +0x14C4
    MUIDialog m_DlgEx; // +0x1564
    UIParticle m_btnPar[16][7]; // +0x1ACC
    UIParticle m_btnPar2[16][7]; // +0x11DCC
    tagRECT m_btnParRc[7]; // +0x220CC
    unsigned char _isParBtn[7]; // +0x2213C
    int _curParEffect; // +0x22144
    me_RoleState me_Role[5]; // +0x22148
    UIStatic m_WeaponName; // +0x2DEBC
    UIStatic m_ClothName; // +0x2DF5C
    UIStatic m_ShoesName; // +0x2DFFC
    UIStatic m_HatName; // +0x2E09C
    UIStatic m_Adorn1Name; // +0x2E13C
    UIStatic m_Adorn2Name; // +0x2E1DC
    UIStatic m_RemarkBk; // +0x2E27C
    UIStatic m_Remark; // +0x2E31C
    UIStatic m_RemarkVal; // +0x2E3BC
    UIStatic m_typeWord; // +0x2E45C
    tagRECT m_remarkRc; // +0x2E4FC
    RoleAtt m_role[5]; // +0x2E50C
    MUIDialog m_Dlg; // +0x2F5B0
    UIButton m_Ctrlbtn[5]; // +0x2FB18
    UIStatic m_ClothIcon; // +0x301D0
    UIStatic m_HatIcon; // +0x30270
    UIStatic m_ShoesIcon; // +0x30310
    UIStatic m_WeaponIcon; // +0x303B0
    UIStatic m_AdornIcon1; // +0x30450
    UIStatic m_AdornIcon2; // +0x304F0
    tagRECT m_SelRc; // +0x30590
    UIButton m_SelRole[5]; // +0x305A0
    int m_CurSelRole; // +0x30C58
    UIFlexBar m_ListTitle; // +0x30C5C
    UIStatic m_ListFrame; // +0x30CB0
    UIStatic m_ListGrid[14]; // +0x30D50
    UIStatic m_title; // +0x31610
    UIListBox ml_Equiplist; // +0x316B0
    int last_index; // +0x31BB8
    tagRECT m_SortRc; // +0x31BBC
    UIButton mb_SortDefault; // +0x31BCC
    UIButton mb_SortPrice; // +0x31D24
    UIButton mb_SortUse; // +0x31E7C
    int m_SortState; // +0x31FD4
    UI3DCtrl m_3DObj; // +0x31FD8
    // total size: 0x3210C (205068)

};
