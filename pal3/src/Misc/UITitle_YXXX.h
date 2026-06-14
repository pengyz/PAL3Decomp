#include "UIFrameWnd.h"
#pragma once
// Auto-generated: UITitle_YXXX

#include "UIButton.h"
#include "UIStatic.h"

class UITitle_YXXX : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    tagRECT rc; // +0x48
    char _gap_04C[12]; // +0x4C
    UIStatic m_OutFrameT; // +0x58
    char _gap_05C[156]; // +0x5C
    UIStatic m_OutFrameR; // +0xF8
    char _gap_0FC[156]; // +0xFC
    UIStatic m_OutFrameL; // +0x198
    char _gap_19C[156]; // +0x19C
    UIStatic m_OutFrameB; // +0x238
    char _gap_23C[156]; // +0x23C
    UIStatic m_background; // +0x2D8
    char _gap_2DC[156]; // +0x2DC
    UIStatic m_title; // +0x378
    char _gap_37C[156]; // +0x37C
    UIButton m_exit; // +0x418
    char _gap_41C[340]; // +0x41C
    UIButton m_ZZRY; // +0x570
    char _gap_574[340]; // +0x574
    UIButton m_XGWZ; // +0x6C8
    char _gap_6CC[340]; // +0x6CC
    UIStatic m_WordBk; // +0x820
    char _tail_824[388]; // +0x824
    // total size: 0x9A8 (2472)

    virtual ~UITitle_YXXX() {}

    virtual int Update(int nVal, int nVal2); // 0x0047E3E0
    virtual int HandleMsgDLL(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved); // 0x0047E4E0
    int LayoutWidgets(); // 0x00459970
    void Create(); // 0x0047DCA0
    void _UITitle_YXXX(); // 0x0047DD90
    void Init(); // 0x0047DE40
    int * CreateTitle(char *pszBuf, unsigned int dwVal, int nVal); // 0x004AF770
};
