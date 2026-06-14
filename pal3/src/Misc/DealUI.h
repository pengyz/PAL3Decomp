#include "UIFrameWnd.h"
#pragma once
// Auto-generated: DealUI

#include "UIButton.h"
#include "UIStatic.h"
#include "UITabBtn.h"
#include "gbengine/gbTexture.h"

class EquipUI;
class PropUI;
class SaleUI;

class DealUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    BYTE _isCreatable; // +0x48
    _BYTE m_Is[5]; // +0x49
    WORD m_ST; // +0x4E
    WORD m_ID; // +0x50
    char _gap_052[2]; // +0x52
    UIStatic m_FlagT; // +0x54
    char _gap_058[148]; // +0x58
    UIStatic m_FlagB; // +0xEC
    char _gap_0F0[148]; // +0xF0
    UIStatic m_FlagM[5]; // +0x184
    char _gap_198[740]; // +0x198
    UIButton mb_BuyEquip; // +0x47C
    char _gap_480[340]; // +0x480
    UIButton mb_BuyProp; // +0x5D4
    char _gap_5D8[340]; // +0x5D8
    UIButton mb_Sale; // +0x72C
    char _gap_730[340]; // +0x730
    UIButton mb_Talk; // +0x884
    char _gap_888[340]; // +0x888
    BYTE m_IsExit; // +0x9DC
    char _gap_9DD[3]; // +0x9DD
    UIButton mb_Exit; // +0x9E0
    char _gap_9E4[340]; // +0x9E4
    UITabBtn m_TabBtn; // +0xB38
    char _gap_B3C[20]; // +0xB3C
    UIStatic m_BkWnd; // +0xB50
    char _gap_B54[148]; // +0xB54
    int m_curRender; // +0xBE8
    EquipUI * pEquipUI; // +0xBEC
    PropUI * pPropUI; // +0xBF0
    SaleUI * pSaleUI; // +0xBF4
    gbTexture * pInterceptTex; // +0xBF8
    float sv; // +0xBFC
    float ev; // +0xC00
    BYTE m_opt; // +0xC04
    char _tail_C05[3]; // +0xC05
    // total size: 0xC08 (3080)

};
