#include "UIWnd.h"
#pragma once
// Auto-generated: UIMap

class _SUBMAP;

class UIMap : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    int m_mapwidth; // +0x44
    int m_screenWidth; // +0x48
    int m_screenHeight; // +0x4C
    int m_xMapNum; // +0x50
    int m_yMapNum; // +0x54
    int m_MapNum; // +0x58
    _SUBMAP * m_pSubMap; // +0x5C
    float m_moveSpeed; // +0x60
    BYTE m_isMoving; // +0x64
    char _gap_065[3]; // +0x65
    float m_offsetx; // +0x68
    float m_offsety; // +0x6C
    float m_moveoffsetx; // +0x70
    float m_moveoffsety; // +0x74
    BYTE m_bCreate; // +0x78
    char _gap_079[3]; // +0x79
    float timescale; // +0x7C
    BYTE m_bLock; // +0x80
    char _tail_081[23]; // +0x81
    // total size: 0x98 (152)

    virtual ~UIMap() {}

    virtual void Render(); // 0x004414F0
    virtual BOOL ProcessHitTest(int nVal, int nVal2); // 0x00441730
    void Destroy(); // 0x004414D0
    virtual int OnMessage(int nVal, int nVal2, int nVal3); // 0x004420C0
    virtual char * Create(int id, void *pRect, int parent, char *pszTexPath, int nVal, char bAtlas); // 0x004412C0
    int * ctor(); // 0x004410F0
    void ctor_11D0(); // 0x004411D0
};
