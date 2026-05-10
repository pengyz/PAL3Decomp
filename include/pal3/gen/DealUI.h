#pragma once
// Auto-generated: DealUI

#include "UIButton.h"
#include "UIFrameWnd.h"
#include "UIStatic.h"
#include "UITabBtn.h"

class EquipUI;
class PropUI;
class SaleUI;

class DealUI : public UIFrameWnd {
public:
    tagPOINT m_pt; // +0x48
    tagRECT rc; // +0x50
    tagRECT bkrc; // +0x60
    int bkWndX; // +0x70
    int bkWndY; // +0x74
    int bkWidth; // +0x78
    int bkHeight; // +0x7C
    int mbWidth; // +0x80
    int mbHeight; // +0x84
    int m_startX; // +0x88
    int m_startY; // +0x8C
    int m_x; // +0x90
    int m_y; // +0x94
    unsigned char _isCreatable; // +0x98
    unsigned char m_Is[5]; // +0x99
    unsigned short m_ST; // +0x9E
    unsigned short m_ID; // +0xA0
    UIStatic m_FlagT; // +0xA4
    UIStatic m_FlagB; // +0x144
    UIStatic m_FlagM[5]; // +0x1E4
    UIButton mb_BuyEquip; // +0x504
    UIButton mb_BuyProp; // +0x65C
    UIButton mb_Sale; // +0x7B4
    UIButton mb_Talk; // +0x90C
    unsigned char m_IsExit; // +0xA64
    UIButton mb_Exit; // +0xA68
    UITabBtn m_TabBtn; // +0xBC0
    UIStatic m_BkWnd; // +0xBD8
    int m_curRender; // +0xC78
    EquipUI * pEquipUI; // +0xC7C
    PropUI * pPropUI; // +0xC80
    SaleUI * pSaleUI; // +0xC84
    gbTexture * pInterceptTex; // +0xC88
    float sv; // +0xC8C
    float ev; // +0xC90
    unsigned char m_opt; // +0xC94
    // total size: 0xC98 (3224)

};
