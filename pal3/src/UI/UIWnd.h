#pragma once
// Auto-generated: UIWnd

#include "PtrArray.h"
#include "gbengine/gbengine_types.h"

class UIWnd {
public:
    // vtable (19 methods, order matches binary layout)

    char _gap_000[4]; // +0x0
    gbColorQuad m_fontcolor; // +0x4
    gbColorQuad m_wndcolor; // +0x8
    void * m_id; // +0xC
    tagRECT m_rect; // +0x10
    char _gap_014[12]; // +0x14
    UIWnd * m_pfather; // +0x20
    PtrArray m_childs; // +0x24
    char _gap_028[12]; // +0x28
    int m_bcreateok; // +0x34
    int m_bvisible; // +0x38
    int m_benable; // +0x3C
    int m_bfocus; // +0x40
    // total size: 0x44 (68)

    virtual ~UIWnd() {}

    virtual void Render(); // 0x00445CD0
    virtual void HideAll(); // 0x00445C10
    void Destroy(); // 0x0043BBB0
    void GetWidth(int nWidth); // 0x0043FDC0
    void GetHeight(int nHeight); // 0x0043FDD0
    void GetPosition(int pPos); // 0x0043FDE0
    virtual int LayoutAndRender(); // 0x004433D0
    void _UIWnd(); // 0x00445B40
    int MoveWindow(void); // 0x00445F20
    void RenderText(); // 0x0044A7F0
    void DelegateRender(); // 0x00450390
    void RenderContent(); // 0x00450440
    virtual UIWnd * _sdtor_27(UIWnd *Block, char a2); // 0x00450E90
    virtual UIWnd * _sdtor_28(UIWnd *Block, char a2); // 0x004518E0
    void CleanupScript(); // 0x00457340
    static void SetRect(tagRECT *); // 0x004D589C
    static void BringWindowToTop(); // 0x004D5950
    int sub_525080(); // 0x00525080
};
