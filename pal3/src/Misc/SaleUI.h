#include "UIFrameWnd.h"
#pragma once
// Auto-generated: SaleUI

#include "BtnGroup.h"
#include "MUIDialog.h"
#include "PlayerItem.h"
#include "SaleUI_SortData.h"
#include "UI3DCtrl.h"
#include "UIAnimateCtrl.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIListBox.h"
#include "UIStatic.h"
#include "UIStaticRM.h"
#include "st_Manager.h"

class UIWnd;

class SaleUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    int bkWidth; // +0x48
    int bkHeight; // +0x4C
    char buf[256]; // +0x50
    char remarkbuf[256]; // +0x150
    int m_SelNum; // +0x250
    st_Manager m_data; // +0x254
    char _gap_258[17500]; // +0x258
    SaleUI_SortData m_sort[299][5]; // +0x46B4
    char _gap_5E10[5980]; // +0x5E10
    int m_ListSelNum[299][5]; // +0x756C
    int m_Max[299][5]; // +0x8CC8
    int m_Sum[5]; // +0xA424
    BYTE _isCreatable; // +0xA438
    char _gap_A439[3]; // +0xA439
    PlayerItem m_SaleData[299][5]; // +0xA43C
    char _gap_BB98[11960]; // +0xBB98
    PlayerItem m_TempData[299][5]; // +0xEA50
    char _gap_101AC[11960]; // +0x101AC
    int m_NotesNull[299][5]; // +0x13064
    _BYTE m_IsEquip[299][5]; // +0x147C0
    _BYTE m_TempIsEquip[299][5]; // +0x14D97
    char _gap_1536E[2]; // +0x1536E
    int x; // +0x15370
    tagRECT rc; // +0x15374
    char _gap_15378[12]; // +0x15378
    UIStatic m_Frame; // +0x15384
    char _gap_15388[156]; // +0x15388
    UIFlexBar m_FrameBar; // +0x15424
    char _gap_15428[80]; // +0x15428
    UIStatic m_Flag; // +0x15478
    char _gap_1547C[156]; // +0x1547C
    UIStatic m_OutFrameT; // +0x15518
    char _gap_1551C[156]; // +0x1551C
    UIStatic m_OutFrameR; // +0x155B8
    char _gap_155BC[156]; // +0x155BC
    UIStatic m_OutFrameL; // +0x15658
    char _gap_1565C[156]; // +0x1565C
    UIStatic m_OutFrameB; // +0x156F8
    char _gap_156FC[156]; // +0x156FC
    UIButton mb_Exit; // +0x15798
    char _gap_1579C[340]; // +0x1579C
    tagRECT m_ExitRc; // +0x158F0
    char _gap_158F4[12]; // +0x158F4
    UIAnimateCtrl m_ani; // +0x15900
    char _gap_15904[160]; // +0x15904
    UIStatic m_Role[5]; // +0x159A4
    char _gap_159B8[780]; // +0x159B8
    tagRECT m_RoleRc[5]; // +0x15CC4
    char _gap_15CD8[60]; // +0x15CD8
    int RoleX; // +0x15D14
    int RoleY; // +0x15D18
    int HeadW; // +0x15D1C
    int HeadH; // +0x15D20
    _BYTE m_Is[5]; // +0x15D24
    char _gap_15D29[3]; // +0x15D29
    MUIDialog m_Msg; // +0x15D2C
    char _gap_15D30[1380]; // +0x15D30
    UI3DCtrl m_3DObj; // +0x16294
    char _gap_16298[304]; // +0x16298
    tagRECT m_FlagRc; // +0x163C8
    char _gap_163CC[12]; // +0x163CC
    UIStatic m_TalkFrame; // +0x163D8
    char _gap_163DC[156]; // +0x163DC
    UIStatic m_Ready; // +0x16478
    char _gap_1647C[156]; // +0x1647C
    tagRECT m_ReadyRc; // +0x16518
    char _gap_1651C[12]; // +0x1651C
    char m_entryTalk[256]; // +0x16528
    UIButton m_btn[5]; // +0x16628
    char _gap_1663C[1700]; // +0x1663C
    tagRECT m_TabRc; // +0x16CE0
    char _gap_16CE4[12]; // +0x16CE4
    UIStatic m_ListSaleTitle; // +0x16CF0
    char _gap_16CF4[156]; // +0x16CF4
    tagRECT m_ListEquipTitleRc; // +0x16D90
    char _gap_16D94[12]; // +0x16D94
    UIStaticRM m_Icon[5][5]; // +0x16DA0
    char _gap_16E04[4600]; // +0x16E04
    UIStatic m_ListFrame; // +0x17FFC
    char _gap_18000[156]; // +0x18000
    UIStatic m_ScrollHB; // +0x1809C
    char _gap_180A0[156]; // +0x180A0
    UIStatic m_ListGrid[14]; // +0x1813C
    char _gap_18174[2184]; // +0x18174
    tagRECT m_ListRc; // +0x189FC
    char _gap_18A00[12]; // +0x18A00
    UIListBox ml_ResumeList; // +0x18A0C
    char _gap_18A10[1284]; // +0x18A10
    int ResumeNum; // +0x18F14
    UIListBox ml_TreasureList; // +0x18F18
    char _gap_18F1C[1284]; // +0x18F1C
    int TreasureNum; // +0x19420
    UIListBox ml_AttackList; // +0x19424
    char _gap_19428[1284]; // +0x19428
    int AttackNum; // +0x1992C
    UIListBox ml_SmeltList; // +0x19930
    char _gap_19934[1284]; // +0x19934
    int SmeltNum; // +0x19E38
    UIListBox ml_AncientList; // +0x19E3C
    char _gap_19E40[1284]; // +0x19E40
    int AncientNum; // +0x1A344
    UIListBox ml_EquipList; // +0x1A348
    char _gap_1A34C[1284]; // +0x1A34C
    int EquipNum; // +0x1A850
    int curPage; // +0x1A854
    int curNum; // +0x1A858
    BtnGroup m_btnGroup; // +0x1A85C
    char _gap_1A860[736]; // +0x1A860
    float m_ctrlTime; // +0x1AB40
    BYTE m_bCanUpdate1; // +0x1AB44
    BYTE m_bCanUpdate2; // +0x1AB45
    char _gap_1AB46[2]; // +0x1AB46
    UIButton m_Sortfunc; // +0x1AB48
    char _gap_1AB4C[340]; // +0x1AB4C
    UIButton m_Sortprice; // +0x1ACA0
    char _gap_1ACA4[340]; // +0x1ACA4
    int m_sortstate; // +0x1ADF8
    tagRECT m_ButtonRc; // +0x1ADFC
    char _gap_1AE00[12]; // +0x1AE00
    UIButton mb_OK; // +0x1AE0C
    char _gap_1AE10[340]; // +0x1AE10
    UIButton mb_Cancel; // +0x1AF64
    char _gap_1AF68[340]; // +0x1AF68
    UIStatic m_SaleRemarkBk; // +0x1B0BC
    char _gap_1B0C0[156]; // +0x1B0C0
    UIStatic m_SaleRemark; // +0x1B15C
    char _gap_1B160[156]; // +0x1B160
    UIStatic m_ItemFlag; // +0x1B1FC
    char _gap_1B200[156]; // +0x1B200
    tagRECT m_RemarkRc; // +0x1B29C
    char _gap_1B2A0[12]; // +0x1B2A0
    UIStatic m_SaleAtt; // +0x1B2AC
    char _tail_1B2B0[208]; // +0x1B2B0
    // total size: 0x1B380 (111488)

    virtual int ProcessCellAnimations(int deltatime, int haveinput); // 0x0046B040
    SaleUI(); // 0x0045A7B0
    int DestroySubFrames(); // 0x004615F0
    int Update(int deltatime, int haveinput); // 0x0046A8B0
    int ConsumeItems(); // 0x0046ACD0
    int InitColumnWidths(); // 0x004AB5E0
    int InitUI(); // 0x00525120
    int ResetGridState(); // 0x005263C0
    int OnMessage(int thisa, UIWnd *a2, char *nMsg, int wParam); // 0x00526A40
};
