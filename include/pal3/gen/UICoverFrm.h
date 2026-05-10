#pragma once
// Auto-generated: UICoverFrm

#include "Average.h"
#include "MENU_TYPE.h"
#include "MUIDialog.h"
#include "UIButtonEX.h"
#include "UIFrameWnd.h"
#include "UIPar_Meteor.h"
#include "UIPar_Star.h"
#include "UIStatic.h"
#include "UIStaticEXA.h"
#include "_CLOUD.h"

class UILoadingFrm;
class UITitle_ArcSave;
class UITitle_JDHY;
class UITitle_QCYM;
class UITitle_XJTM;
class UITitle_YXXX;

class UICoverFrm : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    char buf[256]; // +0x58
    UIStatic m_background; // +0x158
    UIPar_Star m_Star[13]; // +0x1F8
    UIPar_Meteor m_Meteor; // +0x844
    _CLOUD m_cloud[10]; // +0x958
    _CLOUD m_midCloud[5]; // +0x11C8
    _CLOUD m_smlCloud[5]; // +0x1600
    _CLOUD m_testCloud[9]; // +0x1A38
    UIStatic m_mountainA; // +0x21D0
    UIStatic m_mountainB; // +0x2270
    UIStatic m_frame; // +0x2310
    UIStatic m_Logo; // +0x23B0
    unsigned char m_isAlpha; // +0x2450
    float m_alpha; // +0x2454
    UIStaticEXA m_tjA; // +0x2458
    UIStaticEXA m_tjB; // +0x2520
    UIButtonEX m_XDGS; // +0x25E8
    UIButtonEX m_QCYM; // +0x2770
    UIButtonEX m_XJTM; // +0x28F8
    UIButtonEX m_LKYX; // +0x2A80
    UIButtonEX m_YXXX; // +0x2C08
    UIButtonEX m_JDHY; // +0x2D90
    UIButtonEX * m_CtrlBtn[6]; // +0x2F18
    int m_SelBtn; // +0x2F30
    unsigned char m_ExitGame; // +0x2F34
    UITitle_QCYM * pQCYM; // +0x2F38
    UITitle_JDHY * pJDHY; // +0x2F3C
    UITitle_YXXX * pYXXX; // +0x2F40
    UITitle_XJTM * pXJTM; // +0x2F44
    UITitle_ArcSave * pArcSave; // +0x2F48
    UILoadingFrm * pLoadingFrm; // +0x2F4C
    MENU_TYPE m_MenuType; // +0x2F50
    Average m_timeAverage; // +0x2F54
    unsigned char m_gotogame; // +0x2F6C
    unsigned int m_flag; // +0x2F70
    UIStatic m_test; // +0x2F74
    MUIDialog m_ArcDlg; // +0x3014
    MUIDialog m_Not1stDlg; // +0x357C
    unsigned char m_goingin; // +0x3AE4
    unsigned char m_ArcSaveSuc; // +0x3AE5
    unsigned char m_IsReadFinishSave; // +0x3AE6
    // total size: 0x3AE8 (15080)

};
