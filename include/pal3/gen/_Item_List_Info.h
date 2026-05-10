#pragma once
// Auto-generated: _Item_List_Info

#include "UIButton.h"
#include "UIFrameWnd.h"
#include "UIStatic.h"

class _Item;

class _Item_List_Info : public UIFrameWnd {
public:
    UIStatic m_background; // +0x48
    unsigned char m_IsActive; // +0xE8
    _Item * m_pItem; // +0xEC
    UIButton m_BtnItem[12]; // +0xF0
    UIStatic ms_Title; // +0x1110
    UIStatic ms_Info; // +0x11B0
    UIStatic ms_Pic; // +0x1250
    UIButton mb_Prev; // +0x12F0
    UIButton mb_Next; // +0x1448
    UIButton mb_Back; // +0x15A0
    int m_SelItemNum; // +0x16F8
    int m_SelFocusOn; // +0x16FC
    // total size: 0x1700 (5888)

};
