#include "UIFrameWnd.h"
#pragma once
// Auto-generated: UITitle_JDHY

#include "NOTE_STATE.h"
#include "Note_Item.h"
#include "UIButton.h"
#include "UIPushButton.h"
#include "UIScrollBar.h"
#include "UIStatic.h"

class UITitle_JDHY : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    tagRECT rc; // +0x48
    char _gap_04C[12]; // +0x4C
    char buf[256]; // +0x58
    UIStatic m_OutFrameT; // +0x158
    char _gap_15C[156]; // +0x15C
    UIStatic m_OutFrameR; // +0x1F8
    char _gap_1FC[156]; // +0x1FC
    UIStatic m_OutFrameL; // +0x298
    char _gap_29C[156]; // +0x29C
    UIStatic m_OutFrameB; // +0x338
    char _gap_33C[156]; // +0x33C
    UIStatic m_background; // +0x3D8
    char _gap_3DC[156]; // +0x3DC
    UIButton m_exit; // +0x478
    char _gap_47C[340]; // +0x47C
    _BYTE m_isItemShow[99]; // +0x5D0
    char _gap_633[1]; // +0x633
    Note_Item m_NoteItem[99]; // +0x634
    char _gap_7C0[368676]; // +0x7C0
    UIStatic m_Title_JDHY; // +0x5A7E4
    char _gap_5A7E8[156]; // +0x5A7E8
    UIStatic m_TopBar; // +0x5A884
    char _gap_5A888[156]; // +0x5A888
    UIStatic m_BottomBar; // +0x5A924
    char _gap_5A928[156]; // +0x5A928
    UIStatic m_BackBar; // +0x5A9C4
    char _gap_5A9C8[156]; // +0x5A9C8
    UIStatic m_BackBar2; // +0x5AA64
    char _gap_5AA68[156]; // +0x5AA68
    UIPushButton m_pbPage[10]; // +0x5AB04
    char _gap_5AB2C[2480]; // +0x5AB2C
    UIScrollBar m_Scroll; // +0x5B4DC
    char _gap_5B4E0[364]; // +0x5B4E0
    int m_CurScrollPos; // +0x5B64C
    int m_ItemH; // +0x5B650
    int m_ItemW; // +0x5B654
    int m_firstItem; // +0x5B658
    int m_selItem; // +0x5B65C
    int m_getNote; // +0x5B660
    int m_loading; // +0x5B664
    float m_passtime; // +0x5B668
    UIButton m_LoadBtn; // +0x5B66C
    char _gap_5B670[340]; // +0x5B670
    UIButton m_DeleteBtn; // +0x5B7C4
    char _gap_5B7C8[340]; // +0x5B7C8
    NOTE_STATE m_noteState; // +0x5B91C
    char _tail_5B920[2628]; // +0x5B920
    // total size: 0x5C364 (377700)

    virtual void RenderSlotEffects(); // 0x004B2C70
    virtual int ForwardHitTest(); // 0x004B3100
    virtual int OnMessage(); // 0x004B3470
    void LayoutCalcRects(); // 0x0045E9F0
    int HandleDeviceLostA(); // 0x0047C1C0
    int DestroyPages(); // 0x004B01D0
    int _UITitle_JDHY(); // 0x004B0540
    int PopulateContent(); // 0x004B0820
    int ResetAndRefresh(); // 0x004B1580
    int InitNoteItems(); // 0x004B15F0
    int ResetNoteState(); // 0x004B1C00
    int UpdateButtonStates(); // 0x004B1C50
    int ScrollDown(); // 0x004B1EA0
    int ScrollUp(); // 0x004B1FB0
    int HandleInput(); // 0x004B20C0
    FILE * SaveData(double Data, int nVal); // 0x004B2750
    char SaveData(int Data); // 0x004B2920
    int HandleNavigation(); // 0x004B2D20
    int UpdateTextPosition(); // 0x004B3270
};
