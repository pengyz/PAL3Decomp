#include "UIWnd.h"
#pragma once
// Auto-generated: UITextArea

class UITextArea : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    char m_buf[12]; // +0x44
    BYTE m_bInvalidate; // +0x50
    char _tail_051[23]; // +0x51
    // total size: 0x68 (104)

    virtual void ShowWindow(); // 0x00445720
    virtual void Render(); // 0x00445500
    virtual int ProcessInput(); // 0x00445170
    virtual int Destroy(); // 0x00445920
    virtual UITextArea * _sdtor_13(UITextArea *Block, char a2); // 0x00444FF0
    int InitAfterClear(); // 0x00444F60
    void UpdateChildLayout(RECT *pRect, unsigned int nFlags); // 0x00445760
    void ReleaseAllTextures(); // 0x004B7AF0
};
