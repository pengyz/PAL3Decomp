#include "UIWnd.h"
#pragma once
// Auto-generated: UIChatRest

#include "MUIDialog.h"
#include "RestScript.h"
#include "TimeCtl.h"
#include "UIButton.h"
#include "UIStatic.h"
#include "UITabBtn.h"

class Comp_DonateUI;
class PalScript;
class ScreenEffect;

class UIChatRest : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    tagPOINT m_pt; // +0x44
    char _gap_048[4]; // +0x48
    tagRECT bkrc; // +0x4C
    char _gap_050[12]; // +0x50
    int m_startX; // +0x5C
    int m_startY; // +0x60
    int mbWidth; // +0x64
    int mbHeight; // +0x68
    UIStatic m_FlagT; // +0x6C
    char _gap_070[148]; // +0x70
    UIStatic m_FlagB; // +0x104
    char _gap_108[148]; // +0x108
    UIStatic m_FlagM[3]; // +0x19C
    char _gap_1A8[444]; // +0x1A8
    UIButton m_Chat; // +0x364
    char _gap_368[340]; // +0x368
    UIButton m_Rest; // +0x4BC
    char _gap_4C0[340]; // +0x4C0
    UIButton m_Exit; // +0x614
    char _gap_618[340]; // +0x618
    UITabBtn m_TabBtn; // +0x76C
    char _gap_770[20]; // +0x770
    MUIDialog m_answerDlg; // +0x784
    char _gap_788[1284]; // +0x788
    BYTE m_bAnswer; // +0xC8C
    char _gap_C8D[3]; // +0xC8D
    ScreenEffect * eft; // +0xC90
    TimeCtl m_timewait; // +0xC94
    char _gap_C98[8]; // +0xC98
    BYTE m_isFadeOut; // +0xCA0
    BYTE m_isFadeIn; // +0xCA1
    MUIDialog m_noenoughmsg; // +0xCA2
    char _gap_CA6[1284]; // +0xCA6
    MUIDialog m_enough; // +0x11AA
    char _gap_11AE[1284]; // +0x11AE
    MUIDialog m_restover; // +0x16B2
    char _gap_16B6[1286]; // +0x16B6
    UINT m_status; // +0x1BBC
    BYTE m_isExit; // +0x1BC0
    RestScript m_RestScript; // +0x1BC1
    char _gap_1BC5[2067]; // +0x1BC5
    int m_CANREST_ID; // +0x23D8
    int m_CANNOTREST_ID; // +0x23DC
    int m_RESTOVER_ID; // +0x23E0
    PalScript * pRest; // +0x23E4
    PalScript * pCantRest; // +0x23E8
    PalScript * pRestOver; // +0x23EC
    BYTE m_bActive; // +0x23F0
    char _gap_23F1[3]; // +0x23F1
    Comp_DonateUI * pC_DUI; // +0x23F4
    BYTE m_bC_DUIOver; // +0x23F8
    UIStatic m_BK; // +0x23F9
    char _gap_23FD[148]; // +0x23FD
    BYTE m_FadeOutAlpha; // +0x2491
    char _gap_2492[2]; // +0x2492
    float m_age; // +0x2494
    float m_life; // +0x2498
    // total size: 0x249C (9372)

};
