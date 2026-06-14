#include "UIWnd.h"
#pragma once
// Auto-generated: UIDialog

class UIDialog : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    int m_bmodal; // +0x44
    // total size: 0x48 (72)

    void Create(int id, int x, int y, int parent, char *tex); // 0x004503D0
    void Show(); // 0x00450550
    int Init(); // 0x00450B30
    int * ResetState(); // 0x0052AEF0
};
