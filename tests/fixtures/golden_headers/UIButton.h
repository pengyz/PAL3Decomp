class UIWnd;

class tagRECT;

class CCBUI;

#pragma once
// Auto-generated: UIButton
#include "pal3/ida_types.h"

#include "Misc/UIButton_UIBUTTON_STATE.h"
#include "Misc/UITextureArray.h"
#include "UI/UIWnd.h"
#include "gbengine/gbTexture.h"

class CCBUI;
class _PlugInfo;

class UIButton : public UIWnd {
public:
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
    _PlugInfo * m_texarrayInfo[3]; // +0xA4
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

    virtual void ShowClipped(int nVal); // slot0 0x00445e70
    virtual void Render(); // slot1 0x0043ff70
    virtual BOOL Update(CCBUI **deltatime); // slot2 0x00440560
    virtual void HideAll(); // slot3 0x0043f9c0
    virtual int Create(int, tagRECT *, UIWnd *); // slot4 0x0043ff00
    virtual ~UIButton();
    virtual int OnMessage(int a2, unsigned int nVal, int nVal2); // slot6 0x00445d10

    int * ctor(); // 0x0043f7f0
};
