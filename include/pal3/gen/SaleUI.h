#pragma once
// Auto-generated: SaleUI

#include "BtnGroup.h"
#include "MUIDialog.h"
#include "PlayerItem.h"
#include "UI3DCtrl.h"
#include "UIAnimateCtrl.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIFrameWnd.h"
#include "UIListBox.h"
#include "UIStatic.h"
#include "UIStaticRM.h"
#include "UITabBtn.h"
#include "st_Manager.h"

class DealUI;
class HS_Entry;

class SaleUI : public UIFrameWnd {
public:
    int bkWidth; // +0x48
    int bkHeight; // +0x4C
    char buf[256]; // +0x50
    char remarkbuf[256]; // +0x150
    int m_SelNum; // +0x250
    st_Manager m_data; // +0x254
    char m_sort[11960]; // +0x46B4 (SaleUI::SortData[299][5])
    int m_ListSelNum[299][5]; // +0x756C
    int m_Max[299][5]; // +0x8CC8
    int m_Sum[5]; // +0xA424
    BYTE _isCreatable; // +0xA438
    PlayerItem m_SaleData[299][5]; // +0xA43C
    PlayerItem m_TempData[299][5]; // +0xEA50
    int m_NotesNull[299][5]; // +0x13064
    BYTE m_IsEquip[299][5]; // +0x147C0
    BYTE m_TempIsEquip[299][5]; // +0x14D97
    int x; // +0x15370
    tagRECT rc; // +0x15374
    UIStatic m_Frame; // +0x15384
    UIFlexBar m_FrameBar; // +0x15424
    UIStatic m_Flag; // +0x15478
    UIStatic m_OutFrameT; // +0x15518
    UIStatic m_OutFrameR; // +0x155B8
    UIStatic m_OutFrameL; // +0x15658
    UIStatic m_OutFrameB; // +0x156F8
    UIButton mb_Exit; // +0x15798
    tagRECT m_ExitRc; // +0x158F0
    UIAnimateCtrl m_ani; // +0x15900
    UIStatic m_Role[5]; // +0x159A4
    tagRECT m_RoleRc[5]; // +0x15CC4
    int RoleX; // +0x15D14
    int RoleY; // +0x15D18
    int HeadW; // +0x15D1C
    int HeadH; // +0x15D20
    BYTE m_Is[5]; // +0x15D24
    MUIDialog m_Msg; // +0x15D2C
    UI3DCtrl m_3DObj; // +0x16294
    tagRECT m_FlagRc; // +0x163C8
    UIStatic m_TalkFrame; // +0x163D8
    UIStatic m_Ready; // +0x16478
    tagRECT m_ReadyRc; // +0x16518
    char m_entryTalk[256]; // +0x16528
    UIButton m_btn[5]; // +0x16628
    tagRECT m_TabRc; // +0x16CE0
    UIStatic m_ListSaleTitle; // +0x16CF0
    tagRECT m_ListEquipTitleRc; // +0x16D90
    UIStaticRM m_Icon[5][5]; // +0x16DA0
    UIStatic m_ListFrame; // +0x17FFC
    UIStatic m_ScrollHB; // +0x1809C
    UIStatic m_ListGrid[14]; // +0x1813C
    tagRECT m_ListRc; // +0x189FC
    UIListBox ml_ResumeList; // +0x18A0C
    int ResumeNum; // +0x18F14
    UIListBox ml_TreasureList; // +0x18F18
    int TreasureNum; // +0x19420
    UIListBox ml_AttackList; // +0x19424
    int AttackNum; // +0x1992C
    UIListBox ml_SmeltList; // +0x19930
    int SmeltNum; // +0x19E38
    UIListBox ml_AncientList; // +0x19E3C
    int AncientNum; // +0x1A344
    UIListBox ml_EquipList; // +0x1A348
    int EquipNum; // +0x1A850
    int curPage; // +0x1A854
    int curNum; // +0x1A858
    BtnGroup m_btnGroup; // +0x1A85C
    float m_ctrlTime; // +0x1AB40
    BYTE m_bCanUpdate1; // +0x1AB44
    BYTE m_bCanUpdate2; // +0x1AB45
    UIButton m_Sortfunc; // +0x1AB48
    UIButton m_Sortprice; // +0x1ACA0
    int m_sortstate; // +0x1ADF8
    tagRECT m_ButtonRc; // +0x1ADFC
    UIButton mb_OK; // +0x1AE0C
    UIButton mb_Cancel; // +0x1AF64
    UIStatic m_SaleRemarkBk; // +0x1B0BC
    UIStatic m_SaleRemark; // +0x1B15C
    UIStatic m_ItemFlag; // +0x1B1FC
    tagRECT m_RemarkRc; // +0x1B29C
    UIStatic m_SaleAtt; // +0x1B2AC
    tagRECT m_SaleAttRc; // +0x1B34C
    UIStatic m_MoneyRemark; // +0x1B35C
    tagRECT m_MoneyRc; // +0x1B3FC
    UIStatic m_SumSale; // +0x1B40C
    tagRECT m_SumRc; // +0x1B4AC
    BYTE b_IsAdd; // +0x1B4BC
    BYTE b_IsSub; // +0x1B4BD
    int m_extmode; // +0x1B4C0
    DealUI * pDealUI; // +0x1B4C4
    HS_Entry * pEntryUI; // +0x1B4C8
    BYTE m_IsSale; // +0x1B4CC
    int m_curPage; // +0x1B4D0
    UITabBtn m_TabBtn; // +0x1B4D4
    BYTE m_opt; // +0x1B4EC
    // total size: 0x1B4F0 (111856)

};
