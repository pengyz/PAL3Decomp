#pragma once
// Auto-generated: UIChatRest

#include "MUIDialog.h"
#include "RestScript.h"
#include "TimeCtl.h"
#include "UIButton.h"
#include "UIStatic.h"
#include "UITabBtn.h"
#include "UIWnd.h"

class Comp_DonateUI;
class PalScript;
class ScreenEffect;

class UIChatRest : public UIWnd {
public:
    tagPOINT m_pt; // +0x44
    tagRECT rc; // +0x4C
    tagRECT bkrc; // +0x5C
    int m_startX; // +0x6C
    int m_startY; // +0x70
    int mbWidth; // +0x74
    int mbHeight; // +0x78
    UIStatic m_FlagT; // +0x7C
    UIStatic m_FlagB; // +0x11C
    UIStatic m_FlagM[3]; // +0x1BC
    UIButton m_Chat; // +0x39C
    UIButton m_Rest; // +0x4F4
    UIButton m_Exit; // +0x64C
    UITabBtn m_TabBtn; // +0x7A4
    MUIDialog m_answerDlg; // +0x7BC
    BYTE m_bAnswer; // +0xD24
    ScreenEffect * eft; // +0xD28
    TimeCtl m_timewait; // +0xD2C
    BYTE m_isFadeOut; // +0xD38
    BYTE m_isFadeIn; // +0xD39
    MUIDialog m_noenoughmsg; // +0xD3C
    MUIDialog m_enough; // +0x12A4
    MUIDialog m_restover; // +0x180C
    UINT m_status; // +0x1D74
    BYTE m_isExit; // +0x1D78
    RestScript m_RestScript; // +0x1D7C
    int m_CANREST_ID; // +0x2590
    int m_CANNOTREST_ID; // +0x2594
    int m_RESTOVER_ID; // +0x2598
    PalScript * pRest; // +0x259C
    PalScript * pCantRest; // +0x25A0
    PalScript * pRestOver; // +0x25A4
    BYTE m_bActive; // +0x25A8
    Comp_DonateUI * pC_DUI; // +0x25AC
    BYTE m_bC_DUIOver; // +0x25B0
    UIStatic m_BK; // +0x25B4
    BYTE m_FadeOutAlpha; // +0x2654
    float m_age; // +0x2658
    float m_life; // +0x265C
    // total size: 0x2660 (9824)

};
