#include "PalScriptWaitObj.h"
#include "UIWnd.h"
#pragma once
// Auto-generated: UICaption

#include "gbengine/gbTexture.h"

class UICaption : public UIWnd, public PalScriptWaitObj {
public:
    char _gap_000[76]; // +0x0
    gbTexture * m_tex; // +0x4C
    int m_numline; // +0x50
    int m_lineheight; // +0x54
    int m_curline; // +0x58
    float m_linetime; // +0x5C
    // total size: 0x60 (96)

    void Destroy(); // 0x0043AB00
    void Destroy2(); // 0x0043A810
    virtual UICaption * _sdtor_5(UICaption *Block, char a2); // 0x0043B4B0
    void SetEnable(int szName, int bEnable); // 0x004427C0
    void DestroyPanel(); // 0x004461F0
    void sub_44BDA0(); // 0x0044BDA0
    UICaption * _sdtor_24(UICaption *Block, char a2); // 0x0044BE00
    void LayoutDefault(); // 0x00450320
};
