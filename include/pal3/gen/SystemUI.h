#pragma once
// Auto-generated: SystemUI

#include "MUIDialog.h"
#include "NOTE_STATE.h"
#include "Note_Item.h"
#include "UIButton.h"
#include "UIDragBar.h"
#include "UIFlexBar.h"
#include "UIFrameWnd.h"
#include "UIParticle.h"
#include "UIPushButton.h"
#include "UIScrollBar.h"
#include "UIStatic.h"

class StateUI;

class SystemUI : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    unsigned char m_IsMsg; // +0x168
    StateUI * pStateUI; // +0x16C
    UIStatic m_Frame; // +0x170
    UIStatic m_TimeMoney; // +0x210
    UIStatic m_OutFrameT; // +0x2B0
    UIStatic m_OutFrameR; // +0x350
    UIStatic m_OutFrameL; // +0x3F0
    UIStatic m_OutFrameB; // +0x490
    UIStatic stp_BarL; // +0x530
    UIFlexBar stp_BarM; // +0x5D0
    UIStatic stp_BarR; // +0x624
    UIButton stp_State; // +0x6C4
    UIButton stp_Magic; // +0x81C
    UIButton stp_Equip; // +0x974
    UIButton stp_Prop; // +0xACC
    UIButton stp_BattleArray; // +0xC24
    UIButton stp_TaskBook; // +0xD7C
    UIButton stp_System; // +0xED4
    UIButton stp_Exit; // +0x102C
    UIStatic stp_Effect; // +0x1184
    tagRECT stp_Rect; // +0x1224
    UIStatic m_GameTime; // +0x1234
    UIStatic m_GameMoney; // +0x12D4
    UIParticle m_par[16][7]; // +0x1374
    UIParticle m_par2[16][7]; // +0x11674
    tagRECT m_parRc[7]; // +0x21974
    unsigned char _isParBtn[7]; // +0x219E4
    int _curParEffect; // +0x219EC
    UIStatic m_TopBar; // +0x219F0
    UIStatic m_BottomBar; // +0x21A90
    UIButton m_ExitGame; // +0x21B30
    UIButton m_SaveBtn; // +0x21C88
    UIButton m_LoadBtn; // +0x21DE0
    UIButton m_DeleteBtn; // +0x21F38
    UIPushButton m_pbPage[10]; // +0x22090
    unsigned char m_isItemShow[99]; // +0x22A68
    Note_Item m_NoteItem[99]; // +0x22ACC
    UIScrollBar m_Scroll; // +0x7CC7C
    int m_CurScrollPos; // +0x7CDEC
    UIStatic m_BackBar; // +0x7CDF0
    UIStatic m_BackBar2; // +0x7CE90
    UIDragBar m_MusicBar; // +0x7CF30
    UIDragBar m_MusicEffectBar; // +0x7D040
    UIStatic m_MusicText; // +0x7D150
    UIStatic m_MusicEffectText; // +0x7D1F0
    int m_ItemH; // +0x7D290
    int m_ItemW; // +0x7D294
    int m_firstItem; // +0x7D298
    int m_selItem; // +0x7D29C
    int m_getNote; // +0x7D2A0
    NOTE_STATE m_noteState; // +0x7D2A4
    int m_loading; // +0x7D2A8
    float m_passtime; // +0x7D2AC
    unsigned char m_isExit; // +0x7D2B0
    MUIDialog m_MsgBox; // +0x7D2B4
    MUIDialog m_DlgEx; // +0x7D81C
    MUIDialog m_YesNo_Btn; // +0x7DD84
    int m_bFinishSave; // +0x7E2EC
    int m_nShowNoteNum; // +0x7E2F0
    // total size: 0x7E2F4 (516852)

};
