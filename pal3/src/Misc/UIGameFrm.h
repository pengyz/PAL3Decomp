#include "PalScriptWaitObj.h"
#include "UIWnd.h"
#pragma once
// Auto-generated: UIGameFrm

#include "UICaption.h"
#include "UIChatRest.h"
#include "UIEmote.h"
#include "UIHeadDialog.h"
#include "UINote.h"
#include "UIRoleDialog.h"
#include "UIRoleSelect.h"

class ScreenEffect;
class StateUI;
class UIFrameWnd;
class UISceneFrm;

class UIGameFrm : public UIWnd, public PalScriptWaitObj {
public:
    char _gap_000[76]; // +0x0
    UINT m_bigMapElement[16]; // +0x4C
    _BYTE m_newbigmap[16]; // +0x8C
    char _gap_09C[104]; // +0x9C
    UICaption m_cap; // +0x104
    char _gap_108[92]; // +0x108
    UINote m_note; // +0x164
    char _gap_168[264]; // +0x168
    UINT m_SmeltChatScript; // +0x270
    UINT m_HockShopScript; // +0x274
    UINT m_EncampFlag; // +0x278
    UINT m_ExitRow; // +0x27C
    BYTE m_SDTY; // +0x280
    BYTE m_APPR; // +0x281
    BYTE m_SKEE; // +0x282
    char _gap_283[1]; // +0x283
    UINT m_ExitSkee; // +0x284
    ScreenEffect * eft; // +0x288
    BYTE m_isFadeOut; // +0x28C
    BYTE m_overFade; // +0x28D
    char _gap_28E[2]; // +0x28E
    UIRoleSelect m_seldlg; // +0x290
    char _gap_294[1484]; // +0x294
    UIHeadDialog m_headdlg[5]; // +0x860
    char _gap_874[1740]; // +0x874
    UIRoleDialog m_roledlg; // +0xF40
    char _gap_F44[1104]; // +0xF44
    UIChatRest m_ChatRest; // +0x1394
    char _gap_1398[9512]; // +0x1398
    UINT m_ChatRestStatus; // +0x38C0
    UIFrameWnd * m_curfrm; // +0x38C4
    int m_curfrmid; // +0x38C8
    int m_lastfrmid; // +0x38CC
    UIEmote m_emote[6]; // +0x38D0
    char _gap_38E8[13608]; // +0x38E8
    UISceneFrm * m_scenefrm; // +0x6E10
    StateUI * m_sysfrm; // +0x6E14
    char _tail_6E18[4]; // +0x6E18
    // total size: 0x6E1C (28188)

    virtual ~UIGameFrm() {}

    int OnMessage(int nVal, int nVal2, int nVal3); // 0x004A6120
    int Destroy(); // 0x004A6600
};
