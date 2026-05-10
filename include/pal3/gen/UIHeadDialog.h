#pragma once
// Auto-generated: UIHeadDialog

#include "PalScriptWaitObj.h"
#include "UIDialog.h"

class Role;

class UIHeadDialog : public UIDialog, public PalScriptWaitObj {
public:
    Role * m_role; // +0x50
    int m_width; // +0x54
    int m_height; // +0x58
    gbTexture * m_bktex; // +0x5C
    char m_text[256]; // +0x60
    // total size: 0x160 (352)

};
