#include "UIWnd.h"
#pragma once
// Auto-generated: UITabCtrl

#include "UITextureArray.h"

class UITabCtrl : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    int m_itemwidth; // +0x44
    UITextureArray m_texarray; // +0x48
    char _gap_04C[64]; // +0x4C
    int m_numpage; // +0x8C
    int m_onpage; // +0x90
    // total size: 0x94 (148)

    int SetItemParam(int nIndex); // 0x0046D0A0
    int InitAnimParams(); // 0x00532A80
    void Render(); // 0x00532B40
};
