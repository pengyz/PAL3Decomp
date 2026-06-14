#include "UIFrameWnd.h"
#pragma once
// Auto-generated: CG_UI

#include "MUIDialog.h"
#include "PtrArray.h"
#include "UIButton.h"
#include "UIProgressBar.h"
#include "UISceneMap.h"
#include "UIStatic.h"
#include "UIStaticRM.h"

class CG_Entry;
class PropUI;

class CG_UI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    char buf[256]; // +0x48
    tagRECT m_ParentRc; // +0x148
    char _gap_14C[12]; // +0x14C
    CG_Entry * m_pFather; // +0x158
    int m_SelType; // +0x15C
    int m_SelPropType; // +0x160
    int m_nResultValue; // +0x164
    int m_nWinState; // +0x168
    UIStatic m_OutFrameT; // +0x16C
    char _gap_170[156]; // +0x170
    UIStatic m_OutFrameR; // +0x20C
    char _gap_210[156]; // +0x210
    UIStatic m_OutFrameL; // +0x2AC
    char _gap_2B0[156]; // +0x2B0
    UIStatic m_OutFrameB; // +0x34C
    char _gap_350[156]; // +0x350
    UIStatic m_pTime; // +0x3EC
    char _gap_3F0[156]; // +0x3F0
    UIStatic m_pMoney; // +0x48C
    char _gap_490[156]; // +0x490
    UIStatic m_pTools; // +0x52C
    char _gap_530[156]; // +0x530
    UIButton m_pItems[9]; // +0x5CC
    char _gap_5F0[3060]; // +0x5F0
    UIStatic m_pName; // +0x11E4
    char _gap_11E8[156]; // +0x11E8
    UIStatic m_pPrice; // +0x1284
    char _gap_1288[156]; // +0x1288
    UIStatic m_pHurt; // +0x1324
    char _gap_1328[156]; // +0x1328
    UIStatic m_pInfo; // +0x13C4
    char _gap_13C8[156]; // +0x13C8
    UIButton m_pBuy; // +0x1464
    char _gap_1468[340]; // +0x1468
    UIButton m_pRun; // +0x15BC
    char _gap_15C0[340]; // +0x15C0
    UIStatic m_pProp; // +0x1714
    char _gap_1718[156]; // +0x1718
    UIButton m_pProps[5]; // +0x17B4
    char _gap_17C8[1700]; // +0x17C8
    UIStatic m_pPropsNum[5]; // +0x1E6C
    char _gap_1E80[780]; // +0x1E80
    UIStatic m_pHP; // +0x218C
    char _gap_2190[156]; // +0x2190
    UIProgressBar m_pBossHP; // +0x222C
    char _gap_2230[240]; // +0x2230
    UIProgressBar m_pRoleHP; // +0x2320
    char _gap_2324[240]; // +0x2324
    UIStatic m_pRoleFace; // +0x2414
    char _gap_2418[156]; // +0x2418
    UIStatic m_pBossFace; // +0x24B4
    char _gap_24B8[156]; // +0x24B8
    UIStatic m_pTimeBackground; // +0x2554
    char _gap_2558[156]; // +0x2558
    UIStaticRM m_pTimeHunDigit; // +0x25F4
    char _gap_25F8[184]; // +0x25F8
    UIStaticRM m_pTimeTenDigit; // +0x26B0
    char _gap_26B4[184]; // +0x26B4
    UIStaticRM m_pTimeSinDigit; // +0x276C
    char _gap_2770[184]; // +0x2770
    UIStatic m_pResult; // +0x2828
    char _gap_282C[156]; // +0x282C
    MUIDialog m_pWinAnswer; // +0x28C8
    char _gap_28CC[1380]; // +0x28CC
    MUIDialog m_pLoseAnswer; // +0x2E30
    char _gap_2E34[1380]; // +0x2E34
    MUIDialog m_pNoMoneyMsg; // +0x3398
    char _gap_339C[1380]; // +0x339C
    MUIDialog m_pSurpassMsg; // +0x3900
    char _gap_3904[1380]; // +0x3904
    MUIDialog m_pAccountMsg; // +0x3E68
    char _gap_3E6C[1380]; // +0x3E6C
    MUIDialog m_pOverGameMsg; // +0x43D0
    char _gap_43D4[1380]; // +0x43D4
    MUIDialog m_pExitDlg; // +0x4938
    char _gap_493C[1380]; // +0x493C
    PtrArray m_ComboBuffer; // +0x4EA0
    char _gap_4EA4[12]; // +0x4EA4
    UISceneMap m_SceneMap; // +0x4EB0
    char _gap_4EB4[1204]; // +0x4EB4
    UIButton m_Exit; // +0x5368
    char _gap_536C[340]; // +0x536C
    BYTE m_IsExit; // +0x54C0
    char _gap_54C1[3]; // +0x54C1
    tagRECT m_InvalidRc0; // +0x54C4
    char _gap_54C8[12]; // +0x54C8
    tagRECT m_InvalidRc1; // +0x54D4
    char _gap_54D8[12]; // +0x54D8
    tagRECT m_InvalidRc2; // +0x54E4
    char _gap_54E8[12]; // +0x54E8
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
    char _gap_551C[156]; // +0x551C
    _BYTE m_mouseon[9]; // +0x55B8
    char _gap_55C1[3]; // +0x55C1
    int m_nPropCost; // +0x55C4
    int m_nNoteMoney; // +0x55C8
    PropUI * m_pBuyUI; // +0x55CC
    BYTE m_bRenderBuyUI; // +0x55D0
    char _tail_55D1[17271]; // +0x55D1
    // total size: 0x9948 (39240)

};
