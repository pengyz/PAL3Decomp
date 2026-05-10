#pragma once
// Auto-generated: ComposeUI

#include "UIButton.h"
#include "UIFrameWnd.h"
#include "UIStatic.h"
#include "UITabBtn.h"

class Comp_DonateUI;

class ComposeUI : public UIFrameWnd {
public:
    int m_CurRender; // +0x48
    unsigned char m_isCreatable; // +0x4C
    UIStatic m_TopFrame; // +0x50
    UIStatic m_BottomFrame; // +0xF0
    UIStatic m_MiddleFrame[3]; // +0x190
    UIButton m_Talk; // +0x370
    UIButton m_Compose; // +0x4C8
    UIButton m_Exit; // +0x620
    int m_SelBtn; // +0x778
    int m_RoleId; // +0x77C
    char m_RoleLang[512][4]; // +0x780
    gbTexture * pInterceptTex; // +0xF80
    float sv; // +0xF84
    float ev; // +0xF88
    UITabBtn m_TabBtn; // +0xF8C
    Comp_DonateUI * pC_DUI; // +0xFA4
    // total size: 0xFA8 (4008)

};
