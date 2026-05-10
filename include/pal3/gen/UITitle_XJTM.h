#pragma once
// Auto-generated: UITitle_XJTM

#include "UIButton.h"
#include "UIFrameWnd.h"
#include "UIStatic.h"
#include "_Item.h"

class UICoverFrm;

class UITitle_XJTM : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    UIStatic m_OutFrameT; // +0x60
    UIStatic m_OutFrameR; // +0x100
    UIStatic m_OutFrameL; // +0x1A0
    UIStatic m_OutFrameB; // +0x240
    UIStatic m_background; // +0x2E0
    UIStatic m_title; // +0x380
    UIButton m_exit; // +0x420
    unsigned char m_IsActive; // +0x578
    UICoverFrm * m_pMgr; // +0x57C
    _Item m_Item; // +0x580
    int m_SelFirstRow; // +0x5B0
    int m_SelSecondRow; // +0x5B4
    unsigned char m_SelFirstChanged; // +0x5B8
    unsigned char m_SelSecondChanged; // +0x5B9
    unsigned char m_SelZeroChanged; // +0x5BA
    UIStatic m_WordBk; // +0x5BC
    UIStatic m_BtnBk; // +0x65C
    UIButton m_BtnFirstRow[4]; // +0x6FC
    UIButton m_BtnSecondRow[5]; // +0xC5C
    UIStatic m_ItemInfo; // +0x1314
    UIStatic m_ItemPic; // +0x13B4
    // total size: 0x1454 (5204)

};
