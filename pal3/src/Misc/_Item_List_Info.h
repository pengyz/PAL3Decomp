#include "UIFrameWnd.h"
#pragma once
// Auto-generated: _Item_List_Info

#include "UIButton.h"
#include "UIStatic.h"

class _Item;

class _Item_List_Info : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    UIStatic m_background; // +0x48
    char _gap_04C[156]; // +0x4C
    BYTE m_IsActive; // +0xE8
    char _gap_0E9[3]; // +0xE9
    _Item * m_pItem; // +0xEC
    UIButton m_BtnItem[12]; // +0xF0
    char _gap_120[4080]; // +0x120
    UIStatic ms_Title; // +0x1110
    char _gap_1114[156]; // +0x1114
    UIStatic ms_Info; // +0x11B0
    char _gap_11B4[156]; // +0x11B4
    UIStatic ms_Pic; // +0x1250
    char _gap_1254[156]; // +0x1254
    UIButton mb_Prev; // +0x12F0
    char _tail_12F4[932]; // +0x12F4
    // total size: 0x1698 (5784)

};
