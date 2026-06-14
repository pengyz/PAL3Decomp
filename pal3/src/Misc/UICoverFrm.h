#include "UIFrameWnd.h"
#pragma once
// Auto-generated: UICoverFrm

#include "Average.h"
#include "MENU_TYPE.h"
#include "UIButtonEX.h"
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
    char _gap_000[72]; // +0x0
    tagRECT rc; // +0x48
    char _gap_04C[12]; // +0x4C
    char buf[256]; // +0x58
    UIStatic m_background; // +0x158
    char _gap_15C[156]; // +0x15C
    UIPar_Star m_Star[13]; // +0x1F8
    char _gap_22C[1560]; // +0x22C
    UIPar_Meteor m_Meteor; // +0x844
    char _gap_848[272]; // +0x848
    _CLOUD m_cloud[10]; // +0x958
    char _gap_980[2120]; // +0x980
    _CLOUD m_midCloud[5]; // +0x11C8
    char _gap_11DC[1060]; // +0x11DC
    _CLOUD m_smlCloud[5]; // +0x1600
    char _gap_1614[1060]; // +0x1614
    _CLOUD m_testCloud[9]; // +0x1A38
    char _gap_1A5C[1908]; // +0x1A5C
    UIStatic m_mountainA; // +0x21D0
    char _gap_21D4[156]; // +0x21D4
    UIStatic m_mountainB; // +0x2270
    char _gap_2274[156]; // +0x2274
    UIStatic m_frame; // +0x2310
    char _gap_2314[156]; // +0x2314
    UIStatic m_Logo; // +0x23B0
    char _gap_23B4[156]; // +0x23B4
    BYTE m_isAlpha; // +0x2450
    char _gap_2451[3]; // +0x2451
    float m_alpha; // +0x2454
    UIStaticEXA m_tjA; // +0x2458
    char _gap_245C[196]; // +0x245C
    UIStaticEXA m_tjB; // +0x2520
    char _gap_2524[196]; // +0x2524
    UIButtonEX m_XDGS; // +0x25E8
    char _gap_25EC[388]; // +0x25EC
    UIButtonEX m_QCYM; // +0x2770
    char _gap_2774[388]; // +0x2774
    UIButtonEX m_XJTM; // +0x28F8
    char _gap_28FC[388]; // +0x28FC
    UIButtonEX m_LKYX; // +0x2A80
    char _gap_2A84[388]; // +0x2A84
    UIButtonEX m_YXXX; // +0x2C08
    char _gap_2C0C[388]; // +0x2C0C
    UIButtonEX m_JDHY; // +0x2D90
    char _gap_2D94[388]; // +0x2D94
    UIButtonEX * m_CtrlBtn[6]; // +0x2F18
    char _gap_2F1C[20]; // +0x2F1C
    int m_SelBtn; // +0x2F30
    BYTE m_ExitGame; // +0x2F34
    char _gap_2F35[3]; // +0x2F35
    UITitle_QCYM * pQCYM; // +0x2F38
    UITitle_JDHY * pJDHY; // +0x2F3C
    UITitle_YXXX * pYXXX; // +0x2F40
    UITitle_XJTM * pXJTM; // +0x2F44
    UITitle_ArcSave * pArcSave; // +0x2F48
    UILoadingFrm * pLoadingFrm; // +0x2F4C
    MENU_TYPE m_MenuType; // +0x2F50
    Average m_timeAverage; // +0x2F54
    char _gap_2F58[20]; // +0x2F58
    BYTE m_gotogame; // +0x2F6C
    char _gap_2F6D[3]; // +0x2F6D
    UINT m_flag; // +0x2F70
    UIStatic m_test; // +0x2F74
    char _tail_2F78[2800]; // +0x2F78
    // total size: 0x3A68 (14952)

    virtual ~UICoverFrm() {}

    virtual void Render(); // 0x0052C450
    virtual double UpdateStarAnimation(int edi0, double result, int result_4, int nVal); // 0x0052C480
    virtual int OnMessage(int nVal, char *pszBuf, int nVal2); // 0x0052CA10
    int SetDefaultValues(); // 0x0044C840
    char UpdateAnimation(float fVal); // 0x0044C8A0
    int SetCoverTexture(int nTexPtr); // 0x0044DB50
    int * FindActiveSlot(); // 0x0044FF20
    int UpdateClouds(int nVal, int nVal2); // 0x00527230
    int ResetStarFrames(int nVal); // 0x00527370
    int ctor(); // 0x0052BA10
    void ctor_BD50(); // 0x0052BD50
    int AnimateElements(); // 0x0052D5B0
    char LoadFromFile(char *pszFileName); // 0x0052D7C0
};
