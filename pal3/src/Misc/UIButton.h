#include "UIWnd.h"
#pragma once
// Auto-generated: UIButton

#include "UIButton_UIBUTTON_STATE.h"
#include "UITextureArray.h"
#include "gbengine/gbTexture.h"

class _PlugInfo;

class UIButton : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    BYTE m_hasDBclk; // +0x44
    char _gap_045[3]; // +0x45
    float m_ratiow; // +0x48
    UIButton_UIBUTTON_STATE m_state; // +0x4C
    BYTE m_canctrl; // +0x50
    BYTE m_bLockUpdate; // +0x51
    char _gap_052[2]; // +0x52
    int m_offsetx; // +0x54
    float m_offsety; // +0x58
    BYTE m_bBigFont; // +0x5C
    char _gap_05D[3]; // +0x5D
    UITextureArray m_texarray; // +0x60
    char _gap_064[64]; // +0x64
    _PlugInfo * m_texarrayInfo[3]; // +0xA4
    char _gap_0A8[8]; // +0xA8
    gbTexture * m_disablepic; // +0xB0
    _PlugInfo * m_disablepicInfo; // +0xB4
    BYTE m_mouseoff; // +0xB8
    BYTE m_mouseon; // +0xB9
    char _gap_0BA[2]; // +0xBA
    int m_alignmode; // +0xBC
    char m_caption[128]; // +0xC0
    BYTE m_benable_snd; // +0x140
    char _tail_141[23]; // +0x141
    // total size: 0x158 (344)

    virtual ~UIButton() {}

    virtual void Render(); // 0x0043FF70
    virtual BOOL Update(int nDelta, int nVal2); // 0x00440560
    virtual void Destroy(); // 0x0043F9C0
    virtual int Create(int id, int *pRect, int parent); // 0x0043FF00
    int * ctor_17(); // 0x0043F7F0
    void _UIButton(); // 0x0043F970
};
