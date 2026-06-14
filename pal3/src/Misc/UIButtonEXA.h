#include "UIButton.h"
#pragma once
// Auto-generated: UIButtonEXA

#include "_btnOPTDATA.h"
#include "gbengine/gbengine_types.h"

class UIButtonEXA : public UIButton {
public:
    char _gap_000[344]; // +0x0
    _btnOPTDATA m_optData; // +0x158
    char _gap_15C[12]; // +0x15C
    int m_EnableMode; // +0x168
    gbColorQuad m_color; // +0x16C
    gbColorQuad m_enablecolor; // +0x170
    gbColorQuad m_surecolor; // +0x174
    // total size: 0x178 (376)

};
