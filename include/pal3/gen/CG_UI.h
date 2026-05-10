#pragma once
// Auto-generated: CG_UI

#include "MUIDialog.h"
#include "PtrArray.h"
#include "UIButton.h"
#include "UIFrameWnd.h"
#include "UIProgressBar.h"
#include "UISceneMap.h"
#include "UIStatic.h"
#include "UIStaticRM.h"
#include "st_Manager.h"

class CG_Entry;
class PropUI;

class CG_UI : public UIFrameWnd {
public:
    char buf[256]; // +0x48
    tagRECT m_ParentRc; // +0x148
    CG_Entry * m_pFather; // +0x158
    int m_SelType; // +0x15C
    int m_SelPropType; // +0x160
    int m_nResultValue; // +0x164
    int m_nWinState; // +0x168
    UIStatic m_OutFrameT; // +0x16C
    UIStatic m_OutFrameR; // +0x20C
    UIStatic m_OutFrameL; // +0x2AC
    UIStatic m_OutFrameB; // +0x34C
    UIStatic m_pTime; // +0x3EC
    UIStatic m_pMoney; // +0x48C
    UIStatic m_pTools; // +0x52C
    UIButton m_pItems[9]; // +0x5CC
    UIStatic m_pName; // +0x11E4
    UIStatic m_pPrice; // +0x1284
    UIStatic m_pHurt; // +0x1324
    UIStatic m_pInfo; // +0x13C4
    UIButton m_pBuy; // +0x1464
    UIButton m_pRun; // +0x15BC
    UIStatic m_pProp; // +0x1714
    UIButton m_pProps[5]; // +0x17B4
    UIStatic m_pPropsNum[5]; // +0x1E6C
    UIStatic m_pHP; // +0x218C
    UIProgressBar m_pBossHP; // +0x222C
    UIProgressBar m_pRoleHP; // +0x2320
    UIStatic m_pRoleFace; // +0x2414
    UIStatic m_pBossFace; // +0x24B4
    UIStatic m_pTimeBackground; // +0x2554
    UIStaticRM m_pTimeHunDigit; // +0x25F4
    UIStaticRM m_pTimeTenDigit; // +0x26B0
    UIStaticRM m_pTimeSinDigit; // +0x276C
    UIStatic m_pResult; // +0x2828
    MUIDialog m_pWinAnswer; // +0x28C8
    MUIDialog m_pLoseAnswer; // +0x2E30
    MUIDialog m_pNoMoneyMsg; // +0x3398
    MUIDialog m_pSurpassMsg; // +0x3900
    MUIDialog m_pAccountMsg; // +0x3E68
    MUIDialog m_pOverGameMsg; // +0x43D0
    MUIDialog m_pExitDlg; // +0x4938
    PtrArray m_ComboBuffer; // +0x4EA0
    UISceneMap m_SceneMap; // +0x4EB0
    UIButton m_Exit; // +0x5368
    unsigned char m_IsExit; // +0x54C0
    tagRECT m_InvalidRc0; // +0x54C4
    tagRECT m_InvalidRc1; // +0x54D4
    tagRECT m_InvalidRc2; // +0x54E4
    int m_nTimeSec; // +0x54F4
    int m_nBossHP; // +0x54F8
    float m_fBossHP; // +0x54FC
    int m_nRoleFullHP; // +0x5500
    int m_nRoleCurHP; // +0x5504
    float m_ComboHitLastTime; // +0x5508
    float m_ComboHitTime; // +0x550C
    int m_nComboHit; // +0x5510
    int m_nTotalComboHit; // +0x5514
    UIStatic m_pCombo; // +0x5518
    unsigned char m_mouseon[9]; // +0x55B8
    int m_nPropCost; // +0x55C4
    int m_nNoteMoney; // +0x55C8
    PropUI * m_pBuyUI; // +0x55CC
    unsigned char m_bRenderBuyUI; // +0x55D0
    st_Manager m_PropData; // +0x55D4
    unsigned char bUseKeyLocked; // +0x9A34
    unsigned int m_nPropNum[5]; // +0x9A38
    unsigned long m_dwCurPropID; // +0x9A4C
    // total size: 0x9A50 (39504)

};
