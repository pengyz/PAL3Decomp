#pragma once
// Auto-generated: JusticeBookUI

#include "JB_STATE.h"
#include "JB_TYPE.h"
#include "UI3DCtrl.h"
#include "UIButton.h"
#include "UIFrameWnd.h"
#include "UIPushButton.h"
#include "UIStatic.h"

class JusticeBookUI : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    BYTE m_IsMsg; // +0x168
    BYTE m_IsActive; // +0x169
    BYTE m_IsExit; // +0x16A
    BYTE m_IsOpen; // +0x16B
    UIStatic m_BK; // +0x16C
    UIButton m_Exit; // +0x20C
    UIStatic m_OutFrameT; // +0x364
    UIStatic m_OutFrameR; // +0x404
    UIStatic m_OutFrameL; // +0x4A4
    UIStatic m_OutFrameB; // +0x544
    UI3DCtrl m_JusticeBook; // +0x5E4
    UI3DCtrl m_Monster; // +0x718
    UIStatic m_Name; // +0x84C
    UIStatic m_H; // +0x8EC
    UIStatic m_S; // +0x98C
    UIStatic m_Wuling[5]; // +0xA2C
    UIStatic m_Att[5]; // +0xD4C
    UIStatic m_Sorcery[4]; // +0x106C
    tagRECT m_SorceryRc[4]; // +0x12EC
    UIStatic m_Remark; // +0x132C
    UIStatic m_Number; // +0x13CC
    UIButton m_PgUp; // +0x146C
    UIButton m_PgDw; // +0x15C4
    UIPushButton m_tpGods; // +0x171C
    UIPushButton m_tpImmortal; // +0x1818
    UIPushButton m_tpGhost; // +0x1914
    UIPushButton m_tpDemon; // +0x1A10
    UIPushButton m_tpHuman; // +0x1B0C
    UIPushButton m_tpMagic; // +0x1C08
    UIPushButton m_tpGods_unopen; // +0x1D04
    UIPushButton m_tpImmortal_unopen; // +0x1E00
    UIPushButton m_tpGhost_unopen; // +0x1EFC
    UIPushButton m_tpDemon_unopen; // +0x1FF8
    UIPushButton m_tpHuman_unopen; // +0x20F4
    UIPushButton m_tpMagic_unopen; // +0x21F0
    DWORD * m_allMonsters; // +0x22EC
    int m_MonstersNum; // +0x22F0
    int m_tpNum[6]; // +0x22F4
    DWORD m_tpID[100][6]; // +0x230C
    JB_TYPE m_bookMark; // +0x2C6C
    JB_TYPE m_curMark; // +0x2C70
    int m_Page; // +0x2C74
    int m_curPage; // +0x2C78
    tagRECT l_bookMarkRc[6]; // +0x2C7C
    tagRECT r_bookMarkRc[6]; // +0x2CDC
    int bookMarkLR[6]; // +0x2D3C
    tagRECT m_OpenBookRc; // +0x2D54
    BYTE m_showElement; // +0x2D64
    BYTE m_isSetBookMark; // +0x2D65
    int m_isSetBookMarkLR; // +0x2D68
    JB_STATE m_bookState; // +0x2D6C
    gbColorQuad m_color; // +0x2D70
    float m_alpha; // +0x2D74
    BYTE m_isAlpha; // +0x2D78
    // total size: 0x2D7C (11644)

};
