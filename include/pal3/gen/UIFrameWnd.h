#pragma once
// Auto-generated: UIFrameWnd

#include "UIWnd.h"

class UIFrameWnd : public UIWnd {
public:
    gbTexture * m_pbktex; // +0x44
    // total size: 0x48 (72)

    UIFrameWnd(); // 0x004422E0
    void _UIFrameWnd(); // 0x00442390
    void OnMessage(); // 0x00442420
    int Render(); // 0x00442890
    int Update(int a2, int a3); // 0x00442AD0
    int SetPosition(int a2, int a3); // 0x00442C60
};
