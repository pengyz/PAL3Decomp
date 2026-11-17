class tagRECT;

class CCBUI;

#pragma once
// Auto-generated: UIWnd
#include "pal3/ida_types.h"

#include "Misc/PtrArray.h"
#include "gbengine/gbengine_types.h"

class CCBUI;

class UIWnd {
public:
    // vtable (7 methods, order matches binary layout)

    gbColorQuad m_fontcolor; // +0x4
    gbColorQuad m_wndcolor; // +0x8
    UINT m_id; // +0xC
    tagRECT m_rect; // +0x10
    UIWnd * m_pfather; // +0x20
    PtrArray m_childs; // +0x24
    int m_bcreateok; // +0x34
    int m_bvisible; // +0x38
    int m_benable; // +0x3C
    int m_bfocus; // +0x40
    // total size: 0x44 (68)

    virtual void ShowClipped(int nVal); // slot0 0x00445e70
    virtual void Render(); // slot1 0x00445cd0
    virtual BOOL Update(CCBUI **deltatime); // slot2 0x00445c60
    virtual void HideAll(); // slot3 0x00445c10
    virtual int Create(int id, tagRECT *, UIWnd * parent); // slot4 0x00445b90
    virtual ~UIWnd();
    virtual int OnMessage(int a2, unsigned int nVal, int nVal2); // slot6 0x00445d10

    UIWnd(); // 0x00445aa0
    int MoveToAbsolute(); // 0x00445d20
    int HitTest(int a2, int a3); // 0x00445d40
    int MoveWindow(); // 0x00445f20
    int SetRect(void *a2); // 0x00445fa0
    void DelegateRender(); // 0x00450390
    int GetState(); // 0x00451730
    void CleanupScript(); // 0x00457340
    static void SetRect_589c(tagRECT *a1); // 0x004d589c
    void BringWindowToTop(); // 0x004d5950
};
