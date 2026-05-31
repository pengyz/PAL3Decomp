#pragma once
// Auto-generated: ComposeUI

#include "UIButton.h"
#include "UIFrameWnd.h"
#include "UIStatic.h"

class UIWnd;

class ComposeUI : public UIFrameWnd {
public:
    int m_CurRender; // +0x48
    unsigned char m_isCreatable; // +0x4C
    UIStatic m_TopFrame; // +0x50
    UIStatic m_BottomFrame; // +0xF0
    UIStatic m_MiddleFrame[3]; // +0x190
    UIButton m_Talk; // +0x370
    UIButton m_Compose; // +0x4C8
    UIButton m_Exit; // +0x620
    int m_SelBtn; // +0x778
    int m_RoleId; // +0x77C
    // total size: 0xF38 (3896)

    int RefreshRecipeList(int arg0); // 0x0047E030
    void ProcessFrame(int nVal); // 0x0047E190
    UIWnd * GetChildPtr(int index); // 0x004A2BD0
    UIWnd * FindChild(int id); // 0x004A2F90
    int ProcessChildItem(int arg0, int *p_DWORD); // 0x004A3730
};
