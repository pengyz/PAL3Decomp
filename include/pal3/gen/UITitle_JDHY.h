#pragma once
// Auto-generated: UITitle_JDHY

#include "MUIDialog.h"
#include "NOTE_STATE.h"
#include "Note_Item.h"
#include "UIButton.h"
#include "UIFrameWnd.h"
#include "UIPushButton.h"
#include "UIScrollBar.h"
#include "UIStatic.h"

class UICoverFrm;
class UILoadingFrm;

class UITitle_JDHY : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    char buf[256]; // +0x58
    UIStatic m_OutFrameT; // +0x158
    UIStatic m_OutFrameR; // +0x1F8
    UIStatic m_OutFrameL; // +0x298
    UIStatic m_OutFrameB; // +0x338
    UIStatic m_background; // +0x3D8
    UIButton m_exit; // +0x478
    unsigned char m_isItemShow[99]; // +0x5D0
    Note_Item m_NoteItem[99]; // +0x634
    UIStatic m_Title_JDHY; // +0x5A7E4
    UIStatic m_TopBar; // +0x5A884
    UIStatic m_BottomBar; // +0x5A924
    UIStatic m_BackBar; // +0x5A9C4
    UIStatic m_BackBar2; // +0x5AA64
    UIPushButton m_pbPage[10]; // +0x5AB04
    UIScrollBar m_Scroll; // +0x5B4DC
    int m_CurScrollPos; // +0x5B64C
    int m_ItemH; // +0x5B650
    int m_ItemW; // +0x5B654
    int m_firstItem; // +0x5B658
    int m_selItem; // +0x5B65C
    int m_getNote; // +0x5B660
    int m_loading; // +0x5B664
    float m_passtime; // +0x5B668
    UIButton m_LoadBtn; // +0x5B66C
    UIButton m_DeleteBtn; // +0x5B7C4
    NOTE_STATE m_noteState; // +0x5B91C
    MUIDialog m_YesNo; // +0x5B920
    MUIDialog m_MsgBox; // +0x5BE88
    int m_IsArcSave; // +0x5C3F0
    int m_IsReadFinishSave; // +0x5C3F4
    int m_nShowNoteNum; // +0x5C3F8
    UICoverFrm * m_pMgr; // +0x5C3FC
    UILoadingFrm * m_pLoadingFrm; // +0x5C400
    // total size: 0x5C404 (377860)

};
