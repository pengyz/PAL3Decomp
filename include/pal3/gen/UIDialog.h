#pragma once
// Auto-generated: UIDialog

#include "UIWnd.h"

class UIDialog : public UIWnd {
public:
    int m_bmodal; // +0x44
    // total size: 0x48 (72)

    void Create(int id, int x, int y, int parent, char *tex); // 0x004503D0
    void Show(); // 0x00450550
    int Init(); // 0x00450B30
};
