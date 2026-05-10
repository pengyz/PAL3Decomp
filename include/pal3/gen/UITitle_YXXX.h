#pragma once
// Auto-generated: UITitle_YXXX

#include "UIButton.h"
#include "UIFrameWnd.h"
#include "UIStatic.h"
#include "_Item.h"

class UICoverFrm;

class UITitle_YXXX : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    UIStatic m_OutFrameT; // +0x58
    UIStatic m_OutFrameR; // +0xF8
    UIStatic m_OutFrameL; // +0x198
    UIStatic m_OutFrameB; // +0x238
    UIStatic m_background; // +0x2D8
    UIStatic m_title; // +0x378
    UIButton m_exit; // +0x418
    UIButton m_ZZRY; // +0x570
    UIButton m_XGWZ; // +0x6C8
    UIStatic m_WordBk; // +0x820
    UIStatic ms_Info; // +0x8C0
    UIStatic ms_Pic; // +0x960
    unsigned char m_bIsChanged; // +0xA00
    unsigned char m_IsActive; // +0xA01
    _Item m_Item; // +0xA04
    UICoverFrm * m_pMgr; // +0xA34
    // total size: 0xA38 (2616)

};
