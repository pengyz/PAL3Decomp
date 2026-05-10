#pragma once
// Auto-generated: UIMap

#include "UIWnd.h"

class _SUBMAP;

class UIMap : public UIWnd {
public:
    int m_mapwidth; // +0x44
    int m_mapheight; // +0x48
    tagRECT m_screenArea; // +0x4C
    int m_screenWidth; // +0x5C
    int m_screenHeight; // +0x60
    int m_xMapNum; // +0x64
    int m_yMapNum; // +0x68
    int m_MapNum; // +0x6C
    _SUBMAP * m_pSubMap; // +0x70
    float m_moveSpeed; // +0x74
    BYTE m_isMoving; // +0x78
    float m_offsetx; // +0x7C
    float m_offsety; // +0x80
    float m_moveoffsetx; // +0x84
    float m_moveoffsety; // +0x88
    BYTE m_bCreate; // +0x8C
    float timescale; // +0x90
    BYTE m_bLock; // +0x94
    // total size: 0x98 (152)

};
