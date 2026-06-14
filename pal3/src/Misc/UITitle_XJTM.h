#include "UIFrameWnd.h"
#pragma once
// Auto-generated: UITitle_XJTM

#include "UIButton.h"
#include "UIStatic.h"
#include "_Item.h"

class UICoverFrm;

class UITitle_XJTM : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    tagRECT rc; // +0x48
    char _gap_04C[12]; // +0x4C
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    UIStatic m_OutFrameT; // +0x60
    char _gap_064[156]; // +0x64
    UIStatic m_OutFrameR; // +0x100
    char _gap_104[156]; // +0x104
    UIStatic m_OutFrameL; // +0x1A0
    char _gap_1A4[156]; // +0x1A4
    UIStatic m_OutFrameB; // +0x240
    char _gap_244[156]; // +0x244
    UIStatic m_background; // +0x2E0
    char _gap_2E4[156]; // +0x2E4
    UIStatic m_title; // +0x380
    char _gap_384[156]; // +0x384
    UIButton m_exit; // +0x420
    char _gap_424[340]; // +0x424
    BYTE m_IsActive; // +0x578
    char _gap_579[3]; // +0x579
    UICoverFrm * m_pMgr; // +0x57C
    _Item m_Item; // +0x580
    char _gap_584[44]; // +0x584
    int m_SelFirstRow; // +0x5B0
    int m_SelSecondRow; // +0x5B4
    BYTE m_SelFirstChanged; // +0x5B8
    BYTE m_SelSecondChanged; // +0x5B9
    BYTE m_SelZeroChanged; // +0x5BA
    char _gap_5BB[1]; // +0x5BB
    UIStatic m_WordBk; // +0x5BC
    char _gap_5C0[156]; // +0x5C0
    UIStatic m_BtnBk; // +0x65C
    char _gap_660[156]; // +0x660
    UIButton m_BtnFirstRow[4]; // +0x6FC
    char _gap_70C[1360]; // +0x70C
    UIButton m_BtnSecondRow[5]; // +0xC5C
    char _gap_C70[1700]; // +0xC70
    UIStatic m_ItemInfo; // +0x1314
    char _tail_1318[164]; // +0x1318
    // total size: 0x13BC (5052)

    int CreateSubWidgets(); // 0x0044CC60
    void DestroyStatics(); // 0x00486D20
    void DestroyFrames(); // 0x00486EF0
    int UpdateMonsterEntry(int nVal, int *pnVal); // 0x00487C40
    void LayoutGetRects(); // 0x004889E0
    int SetMonsterState(int nIndex, unsigned int dwParam); // 0x00488C70
    int UpdateNPCAnims2(int nVal, int nVal2); // 0x0048F360
    void DestroyStaticsEx(); // 0x00498C90
    void DestroyFramesEx(); // 0x00498E60
    int UpdateMonsterEntry2(int nVal, int *pnVal); // 0x004999D0
    int * Layout_49a6e0(int arg0, int *pnVal); // 0x0049A6E0
    int SetMonsterState2(int nIndex, unsigned int dwParam); // 0x0049A980
    int UpdateNPCAnims(int nVal, int nVal2); // 0x004A0330
};
