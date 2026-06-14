#pragma once
// Auto-generated: UIGroupCtrl

#include "gbengine/gbengine_types.h"
#include "gbengine/gbTexture.h"

class _PlugInfo;

class UIGroupCtrl {
public:
    tagRECT m_bkRc; // +0x0
    char _gap_004[12]; // +0x4
    BYTE m_isCreat; // +0x10
    char _gap_011[3]; // +0x11
    int m_ItemNum; // +0x14
    int m_lBTNSel; // +0x18
    int m_rBTNSel; // +0x1C
    int m_ItemW; // +0x20
    int m_ItemH; // +0x24
    tagRECT * pRect; // +0x28
    tagRECT * pKeepRect; // +0x2C
    gbColorQuad m_color; // +0x30
    float rollSpeed; // +0x34
    float speedstep; // +0x38
    int rollID; // +0x3C
    BYTE isCtrl; // +0x40
    char _gap_041[3]; // +0x41
    int m_PageState; // +0x44
    int m_showNum; // +0x48
    _BYTE * pEnable; // +0x4C
    gbTexture * m_pbk; // +0x50
    _PlugInfo * m_pbkInfo; // +0x54
    // total size: 0x58 (88)

};
