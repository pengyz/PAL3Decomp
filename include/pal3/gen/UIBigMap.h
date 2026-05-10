#pragma once
// Auto-generated: UIBigMap

#include "MUIDialog.h"
#include "TxtFile.h"
#include "UIAnimateCtrl.h"
#include "UIFrameWnd.h"
#include "UIStatic.h"
#include "_BIGMAP_ELEMENT.h"
#include "_MapElement.h"

class UIBigMap : public UIFrameWnd {
public:
    tagRECT screenrect; // +0x48
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    UIStatic ms_BigMap; // +0x168
    _MapElement m_Element[16]; // +0x208
    tagRECT m_spiritRect; // +0x1A88
    UIAnimateCtrl m_spirit; // +0x1A98
    float m_spiritPosX; // +0x1B3C
    float m_spiritPosY; // +0x1B40
    tagPOINT m_spiritPos; // +0x1B44
    tagPOINT m_movetopos; // +0x1B4C
    float m_movetoX; // +0x1B54
    float m_movetoY; // +0x1B58
    int m_spiritspeed; // +0x1B5C
    float m_speedFX; // +0x1B60
    float m_speedFY; // +0x1B64
    unsigned char m_bSpiritCanMove; // +0x1B68
    unsigned char m_isSpiritMoveTo; // +0x1B69
    float m_timescale; // +0x1B6C
    int m_stopdir; // +0x1B70
    _BIGMAP_ELEMENT m_curElement; // +0x1B74
    MUIDialog m_Answer; // +0x1B78
    MUIDialog m_Msg; // +0x20E0
    TxtFile scnname; // +0x2648
    unsigned char m_haveopen; // +0x2854
    unsigned char m_bupalpha; // +0x2855
    int m_alpha; // +0x2858
    int m_alphatime; // +0x285C
    // total size: 0x2860 (10336)

};
