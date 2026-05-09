#pragma once
// Auto-generated: UIWnd

#include "PtrArray.h"
#include "gbColorQuad.h"
#include "tagRECT.h"

class UIWnd {
public:
    gbColorQuad m_fontcolor; // +0x4
    gbColorQuad m_wndcolor; // +0x8
    unsigned int m_id; // +0xC
    tagRECT m_rect; // +0x10
    UIWnd * m_pfather; // +0x20
    PtrArray m_childs; // +0x24
    int m_bcreateok; // +0x34
    int m_bvisible; // +0x38
    int m_benable; // +0x3C
    int m_bfocus; // +0x40
    // total size: 0x44 (68)

    int Reset(); // 0x00445920
    int SetState(int state); // 0x00445930
    int Create(int id, void *pRect, int parent); // 0x00445B90
    int SetVisible(int bVisible); // 0x00445DB0
    int GetChild(int id); // 0x00446010
};
