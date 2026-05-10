#pragma once
// Auto-generated: UITitle_QCYM

#include "UIButton.h"
#include "UIButtonEXA.h"
#include "UIFrameWnd.h"
#include "UIStatic.h"

class UICoverFrm;

class UITitle_QCYM : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    char buf[256]; // +0x58
    UIStatic m_OutFrameT; // +0x158
    UIStatic m_OutFrameR; // +0x1F8
    UIStatic m_OutFrameL; // +0x298
    UIStatic m_OutFrameB; // +0x338
    UIStatic m_background; // +0x3D8
    UIStatic m_title; // +0x478
    UIButtonEXA m_btn[30]; // +0x518
    UIStatic m_NoMovieBK[30]; // +0x3128
    UIButton m_exit; // +0x43E8
    UIStatic m_info; // +0x4540
    UIStatic m_infoBK; // +0x45E0
    unsigned char m_isPlayMovie; // +0x4680
    unsigned char m_isJustOver; // +0x4681
    float m_fpasstime; // +0x4684
    UICoverFrm * m_pMgr; // +0x4688
    // total size: 0x468C (18060)

};
