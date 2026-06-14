#include "UIFrameWnd.h"
#pragma once
// Auto-generated: MainPropUI

#include "MUIDialog.h"
#include "UI3DCtrl.h"
#include "UIAnimate.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIListBox.h"
#include "UIParticle.h"
#include "UIPushButton.h"
#include "UIStatic.h"
#include "p_RoleState.h"

class StateUI;

class MainPropUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    tagRECT rc; // +0x48
    char _gap_04C[12]; // +0x4C
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    int s_x; // +0x68
    char buf[256]; // +0x6C
    char remarkbuf[256]; // +0x16C
    BYTE m_IsMsg; // +0x26C
    _BYTE m_Is[5]; // +0x26D
    char _gap_272[2]; // +0x272
    int m_CurSelRole; // +0x274
    int m_CurNeedRole; // +0x278
    BYTE m_IsActive; // +0x27C
    BYTE m_IsCreateable; // +0x27D
    char _gap_27E[2]; // +0x27E
    int curPage; // +0x280
    int curList; // +0x284
    int m_SelNum; // +0x288
    int m_UseNum; // +0x28C
    BYTE m_LockUse; // +0x290
    BYTE m_IsUsed; // +0x291
    BYTE m_IsCanUse; // +0x292
    BYTE m_IsAllUse; // +0x293
    StateUI * pStateUI; // +0x294
    UIStatic m_Frame; // +0x298
    char _gap_29C[156]; // +0x29C
    UIStatic m_TimeMoney; // +0x338
    char _gap_33C[156]; // +0x33C
    UIStatic m_TopFrame; // +0x3D8
    char _gap_3DC[156]; // +0x3DC
    UIStatic m_TopFrameWP; // +0x478
    char _gap_47C[156]; // +0x47C
    UIStatic m_OutFrameT; // +0x518
    char _gap_51C[156]; // +0x51C
    UIStatic m_OutFrameR; // +0x5B8
    char _gap_5BC[156]; // +0x5BC
    UIStatic m_OutFrameL; // +0x658
    char _gap_65C[156]; // +0x65C
    UIStatic m_OutFrameB; // +0x6F8
    char _gap_6FC[156]; // +0x6FC
    UIStatic stp_BarL; // +0x798
    char _gap_79C[156]; // +0x79C
    UIFlexBar stp_BarM; // +0x838
    char _gap_83C[80]; // +0x83C
    UIStatic stp_BarR; // +0x88C
    char _gap_890[156]; // +0x890
    UIButton stp_State; // +0x92C
    char _gap_930[340]; // +0x930
    UIButton stp_Magic; // +0xA84
    char _gap_A88[340]; // +0xA88
    UIButton stp_Equip; // +0xBDC
    char _gap_BE0[340]; // +0xBE0
    UIButton stp_Prop; // +0xD34
    char _gap_D38[340]; // +0xD38
    UIButton stp_BattleArray; // +0xE8C
    char _gap_E90[340]; // +0xE90
    UIButton stp_TaskBook; // +0xFE4
    char _gap_FE8[340]; // +0xFE8
    UIButton stp_System; // +0x113C
    char _gap_1140[340]; // +0x1140
    UIButton stp_Exit; // +0x1294
    char _gap_1298[340]; // +0x1298
    UIStatic stp_Effect; // +0x13EC
    char _gap_13F0[156]; // +0x13F0
    tagRECT stp_Rect; // +0x148C
    char _gap_1490[12]; // +0x1490
    UIStatic m_GameTime; // +0x149C
    char _gap_14A0[156]; // +0x14A0
    UIStatic m_GameMoney; // +0x153C
    char _gap_1540[156]; // +0x1540
    MUIDialog m_DlgEx; // +0x15DC
    char _gap_15E0[1380]; // +0x15E0
    UIParticle m_btnPar[16][7]; // +0x1B44
    char _gap_1D04[65856]; // +0x1D04
    UIParticle m_btnPar2[16][7]; // +0x11E44
    char _gap_12004[65856]; // +0x12004
    tagRECT m_btnParRc[7]; // +0x22144
    char _gap_22160[84]; // +0x22160
    _BYTE _isParBtn[7]; // +0x221B4
    char _gap_221BB[1]; // +0x221BB
    int _curParEffect; // +0x221BC
    MUIDialog m_Dlg; // +0x221C0
    char _gap_221C4[1380]; // +0x221C4
    p_RoleState m_Role[5]; // +0x22728
    char _gap_2273C[21440]; // +0x2273C
    UIStatic m_RemarkBk; // +0x27AFC
    char _gap_27B00[156]; // +0x27B00
    UIStatic m_Remark; // +0x27B9C
    char _gap_27BA0[156]; // +0x27BA0
    UIStatic m_RemarkVal; // +0x27C3C
    char _gap_27C40[156]; // +0x27C40
    tagRECT m_RemarkRc; // +0x27CDC
    char _gap_27CE0[12]; // +0x27CE0
    UIStatic m_typeWord; // +0x27CEC
    char _gap_27CF0[156]; // +0x27CF0
    UIStatic m_PageBk; // +0x27D8C
    char _gap_27D90[156]; // +0x27D90
    UIButton m_Ctrlbtn[5]; // +0x27E2C
    char _gap_27E40[1700]; // +0x27E40
    UIPushButton m_Pushbtn[5]; // +0x284E4
    char _gap_284F8[1240]; // +0x284F8
    UIStatic m_Title; // +0x289D0
    char _gap_289D4[156]; // +0x289D4
    UIStatic m_ListFrame; // +0x28A70
    char _gap_28A74[156]; // +0x28A74
    UIStatic m_ListGrid[14]; // +0x28B10
    char _gap_28B48[2184]; // +0x28B48
    UIStatic m_ScrollHB; // +0x293D0
    char _gap_293D4[156]; // +0x293D4
    UIListBox ml_Resume; // +0x29470
    char _gap_29474[1284]; // +0x29474
    UIListBox ml_Attack; // +0x29978
    char _gap_2997C[1284]; // +0x2997C
    UIListBox ml_Treasure; // +0x29E80
    char _gap_29E84[1284]; // +0x29E84
    UIListBox ml_Smelt; // +0x2A388
    char _gap_2A38C[1284]; // +0x2A38C
    UIListBox ml_Special; // +0x2A890
    char _gap_2A894[1284]; // +0x2A894
    UIAnimate m_Animate[5]; // +0x2AD98
    char _gap_2ADAC[240]; // +0x2ADAC
    tagRECT m_AnimateRc[5]; // +0x2AE9C
    char _gap_2AEB0[60]; // +0x2AEB0
    tagRECT m_SortRc; // +0x2AEEC
    char _gap_2AEF0[12]; // +0x2AEF0
    UIButton mb_SortDefault; // +0x2AEFC
    char _gap_2AF00[340]; // +0x2AF00
    UIButton mb_SortPrice; // +0x2B054
    char _gap_2B058[340]; // +0x2B058
    UIButton mb_SortUse; // +0x2B1AC
    char _gap_2B1B0[340]; // +0x2B1B0
    int m_SortState; // +0x2B304
    UI3DCtrl m_3DObj; // +0x2B308
    char _gap_2B30C[304]; // +0x2B30C
    UIParticle m_parSingle[12][5]; // +0x2B43C
    char _tail_2B52C[70524]; // +0x2B52C
    // total size: 0x3C8A8 (247976)

    int CreateCoverTemplate(); // 0x00487650
    void DisplayCaption(int nVal); // 0x00488660
    int CalcBarWidth(int nVal, float fVal); // 0x00489030
    int * InitNPCs(int nVal, int arg4, int nVal2); // 0x00489ED0
    int SetPage(unsigned __int8 nPageIdx); // 0x0048C4A0
    int FindValidSaveSlot(); // 0x0048CEE0
    void SetCaption(int nVal, int nVal2, int nVal3); // 0x0048CF10
    virtual char RenderWithEffects(); // 0x0048EB40
    int _MainPropUI(); // 0x004909F0
    int ShowPage(); // 0x00491B40
    void ShowSubPanels(int nVal); // 0x00492BB0
    int ProcessSlotCounter(int *pCounter); // 0x00497050
    int FindNextValid(int *pCounter); // 0x00497080
    char HandleKeyInput(); // 0x004970B0
};
