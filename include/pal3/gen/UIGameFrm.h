#pragma once
// Auto-generated: UIGameFrm

#include "MUIDialog.h"
#include "PAL3_FRAME.h"
#include "PalScriptWaitObj.h"
#include "UIButton.h"
#include "UICaption.h"
#include "UIChatRest.h"
#include "UIEmote.h"
#include "UIHeadDialog.h"
#include "UINote.h"
#include "UIRoleDialog.h"
#include "UIRoleSelect.h"
#include "UIStatic.h"
#include "UIWnd.h"

class ScreenEffect;
class StateUI;
class UIFrameWnd;
class UISceneFrm;

class UIGameFrm : public UIWnd, public PalScriptWaitObj {
public:
    UINT m_bigMapElement[16]; // +0x4C
    BYTE m_newbigmap[16]; // +0x8C
    UICaption m_cap; // +0x9C
    UINote m_note; // +0x120
    DWORD m_SmeltChatScript; // +0x22C
    DWORD m_HockShopScript; // +0x230
    UINT m_EncampFlag; // +0x234
    DWORD m_ExitRow; // +0x238
    BYTE m_SDTY; // +0x23C
    BYTE m_APPR; // +0x23D
    BYTE m_SKEE; // +0x23E
    DWORD m_ExitSkee; // +0x240
    ScreenEffect * eft; // +0x244
    BYTE m_isFadeOut; // +0x248
    BYTE m_overFade; // +0x249
    UIRoleSelect m_seldlg; // +0x24C
    UIHeadDialog m_headdlg[5]; // +0x86C
    UIRoleDialog m_roledlg; // +0xF4C
    UIChatRest m_ChatRest; // +0x121C
    UINT m_ChatRestStatus; // +0x387C
    UIFrameWnd * m_curfrm; // +0x3880
    PAL3_FRAME m_curfrmid; // +0x3884
    PAL3_FRAME m_lastfrmid; // +0x3888
    UIEmote m_emote[6]; // +0x388C
    UISceneFrm * m_scenefrm; // +0x71BC
    StateUI * m_sysfrm; // +0x71C0
    UIStatic m_selemote_frame; // +0x71C4
    UIButton m_selemote_BTN1; // +0x7264
    UIButton m_selemote_BTN2; // +0x73BC
    int m_selemote_nSel; // +0x7514
    BYTE m_selemote_create; // +0x7518
    MUIDialog m_FinishSave; // +0x751C
    // total size: 0x7A84 (31364)

};
