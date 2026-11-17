class UIWnd;

class tagRECT;

class CCBUI;

#pragma once
// Auto-generated: SaleUI
#include "pal3/ida_types.h"

#include "Misc/Inventory.h"
#include "Misc/MUIDialog.h"
#include "Misc/PlayerItem.h"
#include "Misc/Reoccupy.h"
#include "Misc/SaleUI_SortData.h"
#include "Misc/UI3DCtrl.h"
#include "Misc/UIAnimateCtrl.h"
#include "Misc/UIButton.h"
#include "Misc/UIFlexBar.h"
#include "UI/UIListBox.h"
#include "Misc/UIStatic.h"
#include "Misc/UIStaticRM.h"
#include "Misc/st_Manager.h"

class CCBUI;
class CCBUIPanel;

class SaleUI : public UIListBox {
public:
    int bkWidth; // +0x48
    int bkHeight; // +0x4C
    char buf[256]; // +0x50
    char remarkbuf[256]; // +0x150
    int m_SelNum; // +0x250
    st_Manager m_data; // +0x254
    char _gap_348[320]; // +0x348
    Inventory m_inventory; // +0x488
    Reoccupy m_reoccupy; // +0x4B0
    int dwWeaponWU; // +0x4C0
    char _gap_4C4[16880]; // +0x4C4
    SaleUI_SortData m_sort[299][5]; // +0x46B4
    char _gap_5E10[5980]; // +0x5E10
    int m_ListSelNum[299][5]; // +0x756C
    int m_Max[299][5]; // +0x8CC8
    int m_Sum[5]; // +0xA424
    BYTE _isCreatable; // +0xA438
    char _gap_A439[3]; // +0xA439
    PlayerItem m_SaleData[299][5]; // +0xA43C
    PlayerItem m_TempData[158]; // +0xEA50
    int m_bNGHS; // +0xF1B8
    int m_bWPXS; // +0xF1BC
    char _gap_F1C0[16036]; // +0xF1C0
    int m_NotesNull[299][5]; // +0x13064
    _BYTE m_IsEquip[299][5]; // +0x147C0
    _BYTE m_TempIsEquip[299][5]; // +0x14D97
    char _gap_1536E[2]; // +0x1536E
    int x; // +0x15370
    tagRECT rc; // +0x15374
    UIStatic m_Frame; // +0x15384
    char _gap_1541C[8]; // +0x1541C
    UIFlexBar m_FrameBar; // +0x15424
    UIStatic m_Flag; // +0x15478
    char _gap_15510[8]; // +0x15510
    UIStatic m_OutFrameT; // +0x15518
    char _gap_155B0[8]; // +0x155B0
    UIStatic m_OutFrameR; // +0x155B8
    char _gap_15650[8]; // +0x15650
    UIStatic m_OutFrameL; // +0x15658
    char _gap_156F0[8]; // +0x156F0
    UIStatic m_OutFrameB; // +0x156F8
    char _gap_15790[8]; // +0x15790
    UIButton mb_Exit; // +0x15798
    tagRECT m_ExitRc; // +0x158F0
    UIAnimateCtrl m_ani; // +0x15900
    UIStatic m_Role[5]; // +0x159A4
    char _gap_15C9C[40]; // +0x15C9C
    tagRECT m_RoleRc[5]; // +0x15CC4
    int RoleX; // +0x15D14
    int RoleY; // +0x15D18
    int HeadW; // +0x15D1C
    int HeadH; // +0x15D20
    _BYTE m_Is[5]; // +0x15D24
    char _gap_15D29[3]; // +0x15D29
    MUIDialog m_Msg; // +0x15D2C
    char _gap_16234[96]; // +0x16234
    UI3DCtrl m_3DObj; // +0x16294
    tagRECT m_FlagRc; // +0x163C8
    UIStatic m_TalkFrame; // +0x163D8
    char _gap_16470[8]; // +0x16470
    UIStatic m_Ready; // +0x16478
    char _gap_16510[8]; // +0x16510
    tagRECT m_ReadyRc; // +0x16518
    char m_entryTalk[256]; // +0x16528
    UIButton m_btn[5]; // +0x16628
    tagRECT m_TabRc; // +0x16CE0
    UIStatic m_ListSaleTitle; // +0x16CF0
    char _gap_16D88[8]; // +0x16D88
    tagRECT m_ListEquipTitleRc; // +0x16D90
    UIStaticRM m_Icon[5][5]; // +0x16DA0
    char _gap_17F34[200]; // +0x17F34
    UIStatic m_ListFrame; // +0x17FFC
    char _gap_18094[8]; // +0x18094
    UIStatic m_ScrollHB; // +0x1809C
    char _gap_18134[8]; // +0x18134
    UIStatic m_ListGrid[14]; // +0x1813C
    char _gap_1898C[112]; // +0x1898C
    tagRECT m_ListRc; // +0x189FC
    UIListBox ml_ResumeList; // +0x18A0C
    char _gap_18A54[1216]; // +0x18A54
    int ResumeNum; // +0x18F14
    UIListBox ml_TreasureList; // +0x18F18
    char _gap_18F60[1216]; // +0x18F60
    int TreasureNum; // +0x19420
    UIListBox ml_AttackList; // +0x19424
    char _gap_1946C[1216]; // +0x1946C
    int AttackNum; // +0x1992C
    char _tail_19930[1160]; // +0x19930
    // total size: 0x19DB8 (105912)

    virtual void ShowClipped(int nVal); // slot0 0x00445e70
    virtual void Render(); // slot1 0x0043ddf0
    virtual BOOL Update(CCBUI **deltatime); // slot2 0x0046b040
    virtual void HideAll(); // slot3 0x0043de40
    virtual int Create(int id, tagRECT *, UIWnd * parent); // slot4 0x00445b90
    virtual ~SaleUI();
    virtual int OnMessage(int a2, unsigned int nVal, int nVal2); // slot6 0x0046b4b0

    virtual int OnMessage_19(int nVal, unsigned int pszBuf, int nVal2); // 0x0046b4b0
    SaleUI(); // 0x0045a7b0
    unsigned __int8 LoadState(const void *arg0); // 0x0045b7a0
    int InitCombatUI(int nVal); // 0x0045b990
    int UpdateSkillPanel(); // 0x00460a90
    int DestroySubFrames(); // 0x004615f0
    void InitMode(int nVal); // 0x00461c50
    int SetValue(unsigned __int8 nValue); // 0x00461fd0
    int SetRange(unsigned __int8 nMax); // 0x00462080
    int SendInputToRole(unsigned __int8 pData); // 0x004620e0
    int SetSelectionFlags(int nFlags); // 0x00462120
    int GetValue(unsigned __int8 nIndex); // 0x00462220
    int CreatePanelElements(CCBUIPanel *arg0); // 0x004623a0
    int AddItem(); // 0x00469d50
    void SetupPlayerDisplay(int nVal); // 0x00469d90
    BOOL HandleInput(int nInputID, int nParam, int nFlags); // 0x00469eb0
    int ConsumeItems(); // 0x0046acd0
    char ToggleSlot0(unsigned __int8 pData); // 0x00471220
    char ToggleSlot1(unsigned __int8 pData); // 0x004712d0
    char ToggleSlot2(unsigned __int8 pData); // 0x00471380
    char ToggleSlot3(unsigned __int8 pData); // 0x00471430
    char ToggleSlot4(unsigned __int8 pData); // 0x004714e0
    int InitColumnWidths(); // 0x004ab5e0
    int InitUI(); // 0x00525120
    int ResetGridState(); // 0x005263c0
};
