#pragma once
// Auto-generated: MainPropUI

#include "MUIDialog.h"
#include "UI3DCtrl.h"
#include "UIAnimate.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIFrameWnd.h"
#include "UIListBox.h"
#include "UIParticle.h"
#include "UIPushButton.h"
#include "UIStatic.h"
#include "p_RoleState.h"

class StateUI;

class MainPropUI : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    int s_x; // +0x68
    char buf[256]; // +0x6C
    char remarkbuf[256]; // +0x16C
    unsigned char m_IsMsg; // +0x26C
    unsigned char m_Is[5]; // +0x26D
    int m_CurSelRole; // +0x274
    int m_CurNeedRole; // +0x278
    unsigned char m_IsActive; // +0x27C
    unsigned char m_IsCreateable; // +0x27D
    int curPage; // +0x280
    int curList; // +0x284
    int m_SelNum; // +0x288
    int m_UseNum; // +0x28C
    unsigned char m_LockUse; // +0x290
    unsigned char m_IsUsed; // +0x291
    unsigned char m_IsCanUse; // +0x292
    unsigned char m_IsAllUse; // +0x293
    StateUI * pStateUI; // +0x294
    UIStatic m_Frame; // +0x298
    UIStatic m_TimeMoney; // +0x338
    UIStatic m_TopFrame; // +0x3D8
    UIStatic m_TopFrameWP; // +0x478
    UIStatic m_OutFrameT; // +0x518
    UIStatic m_OutFrameR; // +0x5B8
    UIStatic m_OutFrameL; // +0x658
    UIStatic m_OutFrameB; // +0x6F8
    UIStatic stp_BarL; // +0x798
    UIFlexBar stp_BarM; // +0x838
    UIStatic stp_BarR; // +0x88C
    UIButton stp_State; // +0x92C
    UIButton stp_Magic; // +0xA84
    UIButton stp_Equip; // +0xBDC
    UIButton stp_Prop; // +0xD34
    UIButton stp_BattleArray; // +0xE8C
    UIButton stp_TaskBook; // +0xFE4
    UIButton stp_System; // +0x113C
    UIButton stp_Exit; // +0x1294
    UIStatic stp_Effect; // +0x13EC
    tagRECT stp_Rect; // +0x148C
    UIStatic m_GameTime; // +0x149C
    UIStatic m_GameMoney; // +0x153C
    MUIDialog m_DlgEx; // +0x15DC
    UIParticle m_btnPar[16][7]; // +0x1B44
    UIParticle m_btnPar2[16][7]; // +0x11E44
    tagRECT m_btnParRc[7]; // +0x22144
    unsigned char _isParBtn[7]; // +0x221B4
    int _curParEffect; // +0x221BC
    MUIDialog m_Dlg; // +0x221C0
    p_RoleState m_Role[5]; // +0x22728
    UIStatic m_RemarkBk; // +0x27AFC
    UIStatic m_Remark; // +0x27B9C
    UIStatic m_RemarkVal; // +0x27C3C
    tagRECT m_RemarkRc; // +0x27CDC
    UIStatic m_typeWord; // +0x27CEC
    UIStatic m_PageBk; // +0x27D8C
    UIButton m_Ctrlbtn[5]; // +0x27E2C
    UIPushButton m_Pushbtn[5]; // +0x284E4
    UIStatic m_Title; // +0x289D0
    UIStatic m_ListFrame; // +0x28A70
    UIStatic m_ListGrid[14]; // +0x28B10
    UIStatic m_ScrollHB; // +0x293D0
    UIListBox ml_Resume; // +0x29470
    UIListBox ml_Attack; // +0x29978
    UIListBox ml_Treasure; // +0x29E80
    UIListBox ml_Smelt; // +0x2A388
    UIListBox ml_Special; // +0x2A890
    UIAnimate m_Animate[5]; // +0x2AD98
    tagRECT m_AnimateRc[5]; // +0x2AE9C
    tagRECT m_SortRc; // +0x2AEEC
    UIButton mb_SortDefault; // +0x2AEFC
    UIButton mb_SortPrice; // +0x2B054
    UIButton mb_SortUse; // +0x2B1AC
    int m_SortState; // +0x2B304
    UI3DCtrl m_3DObj; // +0x2B308
    UIParticle m_parSingle[12][5]; // +0x2B43C
    UIParticle m_parDouble[12][5]; // +0x33EFC
    tagRECT m_parRc[5]; // +0x3C9BC
    int m_nUsedID; // +0x3CA0C
    // total size: 0x3CA10 (248336)

};
