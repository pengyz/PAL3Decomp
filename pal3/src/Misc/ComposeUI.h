#include "UIFrameWnd.h"
#pragma once
// Auto-generated: ComposeUI

#include "UIButton.h"
#include "UIStatic.h"

class ComposeUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    int m_CurRender; // +0x48
    BYTE m_isCreatable; // +0x4C
    char _gap_04D[3]; // +0x4D
    UIStatic m_TopFrame; // +0x50
    char _gap_054[156]; // +0x54
    UIStatic m_BottomFrame; // +0xF0
    char _gap_0F4[156]; // +0xF4
    UIStatic m_MiddleFrame[3]; // +0x190
    char _gap_19C[468]; // +0x19C
    UIButton m_Talk; // +0x370
    char _gap_374[340]; // +0x374
    UIButton m_Compose; // +0x4C8
    char _gap_4CC[340]; // +0x4CC
    UIButton m_Exit; // +0x620
    char _gap_624[340]; // +0x624
    int m_SelBtn; // +0x778
    char _tail_77C[1980]; // +0x77C
    // total size: 0xF38 (3896)

    int RefreshRecipeList(int arg0); // 0x0047E030
    void ProcessFrame(int nVal); // 0x0047E190
    int ProcessChildItem(int arg0, int *p_DWORD); // 0x004A3730
};
