#include "UIFrameWnd.h"
#pragma once
// Auto-generated: JusticeBookUI

#include "JB_TYPE.h"
#include "UI3DCtrl.h"
#include "UIButton.h"
#include "UIPushButton.h"
#include "UIStatic.h"

class JusticeBookUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    tagRECT rc; // +0x48
    char _gap_04C[12]; // +0x4C
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
    char _gap_170[156]; // +0x170
    UIButton m_Exit; // +0x20C
    char _gap_210[340]; // +0x210
    UIStatic m_OutFrameT; // +0x364
    char _gap_368[156]; // +0x368
    UIStatic m_OutFrameR; // +0x404
    char _gap_408[156]; // +0x408
    UIStatic m_OutFrameL; // +0x4A4
    char _gap_4A8[156]; // +0x4A8
    UIStatic m_OutFrameB; // +0x544
    char _gap_548[156]; // +0x548
    UI3DCtrl m_JusticeBook; // +0x5E4
    char _gap_5E8[304]; // +0x5E8
    UI3DCtrl m_Monster; // +0x718
    char _gap_71C[304]; // +0x71C
    UIStatic m_Name; // +0x84C
    char _gap_850[156]; // +0x850
    UIStatic m_H; // +0x8EC
    char _gap_8F0[156]; // +0x8F0
    UIStatic m_S; // +0x98C
    char _gap_990[156]; // +0x990
    UIStatic m_Wuling[5]; // +0xA2C
    char _gap_A40[780]; // +0xA40
    UIStatic m_Att[5]; // +0xD4C
    char _gap_D60[780]; // +0xD60
    UIStatic m_Sorcery[4]; // +0x106C
    char _gap_107C[624]; // +0x107C
    tagRECT m_SorceryRc[4]; // +0x12EC
    char _gap_12FC[48]; // +0x12FC
    UIStatic m_Remark; // +0x132C
    char _gap_1330[156]; // +0x1330
    UIStatic m_Number; // +0x13CC
    char _gap_13D0[156]; // +0x13D0
    UIButton m_PgUp; // +0x146C
    char _gap_1470[340]; // +0x1470
    UIButton m_PgDw; // +0x15C4
    char _gap_15C8[340]; // +0x15C8
    UIPushButton m_tpGods; // +0x171C
    char _gap_1720[248]; // +0x1720
    UIPushButton m_tpImmortal; // +0x1818
    char _gap_181C[248]; // +0x181C
    UIPushButton m_tpGhost; // +0x1914
    char _gap_1918[248]; // +0x1918
    UIPushButton m_tpDemon; // +0x1A10
    char _gap_1A14[248]; // +0x1A14
    UIPushButton m_tpHuman; // +0x1B0C
    char _gap_1B10[248]; // +0x1B10
    UIPushButton m_tpMagic; // +0x1C08
    char _gap_1C0C[248]; // +0x1C0C
    UIPushButton m_tpGods_unopen; // +0x1D04
    char _gap_1D08[248]; // +0x1D08
    UIPushButton m_tpImmortal_unopen; // +0x1E00
    char _gap_1E04[248]; // +0x1E04
    UIPushButton m_tpGhost_unopen; // +0x1EFC
    char _gap_1F00[248]; // +0x1F00
    UIPushButton m_tpDemon_unopen; // +0x1FF8
    char _gap_1FFC[248]; // +0x1FFC
    UIPushButton m_tpHuman_unopen; // +0x20F4
    char _gap_20F8[248]; // +0x20F8
    UIPushButton m_tpMagic_unopen; // +0x21F0
    char _gap_21F4[248]; // +0x21F4
    UINT * m_allMonsters; // +0x22EC
    int m_MonstersNum; // +0x22F0
    int m_tpNum[6]; // +0x22F4
    UINT m_tpID[100][6]; // +0x230C
    JB_TYPE m_bookMark; // +0x2C6C
    JB_TYPE m_curMark; // +0x2C70
    int m_Page; // +0x2C74
    char _tail_2C78[20]; // +0x2C78
    // total size: 0x2C8C (11404)

    virtual ~JusticeBookUI() {}

    virtual void Render(); // 0x00528ED0
    virtual int ProcessInput(int nVal, int nVal2); // 0x00528F50
    virtual int OnMessage(int nVal, char *pszBuf, int nVal2); // 0x00529120
    char UpdateFadeAnim(float fDelta); // 0x0044DA30
    int ctor(); // 0x005282E0
    void ctor_84E0(); // 0x005284E0
};
