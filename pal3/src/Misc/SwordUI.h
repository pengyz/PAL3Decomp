#include "UIFrameWnd.h"
#pragma once
// Auto-generated: SwordUI

#include "FightSkill.h"
#include "Inventory.h"
#include "MUIDialog.h"
#include "PurgeEffect.h"
#include "S_Distribute.h"
#include "TimeCtl.h"
#include "UI3DCtrl.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIListBox.h"
#include "UIParticle.h"
#include "UIStatic.h"
#include "WuLing.h"
#include "_PURGE_INFO.h"
#include "gbengine/gbTexture.h"

class StateUI;

class SwordUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    WuLing m_PurgeNum; // +0x48
    char _gap_04C[12]; // +0x4C
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    int m_ljsNum; // +0x168
    UIStatic m_ljsNumber; // +0x16C
    char _gap_170[156]; // +0x170
    int m_purgeEquipNum; // +0x20C
    int m_purgeWeaponNum; // +0x210
    int m_avgWeaponWU; // +0x214
    int m_avgAdornWU; // +0x218
    int m_avgAdornFANG; // +0x21C
    int m_avgDefFANG; // +0x220
    int m_adornNum; // +0x224
    int m_defNum; // +0x228
    FightSkill m_WSkill[28]; // +0x22C
    char _gap_29C[21168]; // +0x29C
    int m_wskillNum; // +0x554C
    BYTE m_IsMsg; // +0x5550
    char _gap_5551[3]; // +0x5551
    int m_CtrlRole; // +0x5554
    BYTE m_IsActive; // +0x5558
    BYTE m_IsCreateable; // +0x5559
    BYTE m_IsLunar; // +0x555A
    BYTE m_is3dLunar; // +0x555B
    int m_SelNum; // +0x555C
    int m_CurPage; // +0x5560
    float m_angle; // +0x5564
    float rot; // +0x5568
    S_Distribute m_Distribute[99]; // +0x556C
    char _gap_56F8[1188]; // +0x56F8
    int FetchVal; // +0x5B9C
    int GuVal; // +0x5BA0
    StateUI * pStateUI; // +0x5BA4
    UIStatic m_FrameLine; // +0x5BA8
    char _gap_5BAC[156]; // +0x5BAC
    UIStatic m_TimeMoney; // +0x5C48
    char _gap_5C4C[156]; // +0x5C4C
    UIStatic stp_BarL; // +0x5CE8
    char _gap_5CEC[156]; // +0x5CEC
    UIStatic stp_BarM; // +0x5D88
    char _gap_5D8C[156]; // +0x5D8C
    UIStatic stp_BarR; // +0x5E28
    char _gap_5E2C[156]; // +0x5E2C
    UIButton stp_State; // +0x5EC8
    char _gap_5ECC[340]; // +0x5ECC
    UIButton stp_Magic; // +0x6020
    char _gap_6024[340]; // +0x6024
    UIButton stp_Equip; // +0x6178
    char _gap_617C[340]; // +0x617C
    UIButton stp_Prop; // +0x62D0
    char _gap_62D4[340]; // +0x62D4
    UIButton stp_BattleArray; // +0x6428
    char _gap_642C[340]; // +0x642C
    UIButton stp_System; // +0x6580
    char _gap_6584[340]; // +0x6584
    UIButton stp_Exit; // +0x66D8
    char _gap_66DC[340]; // +0x66DC
    UIStatic stp_Effect; // +0x6830
    char _gap_6834[156]; // +0x6834
    tagRECT stp_Rect; // +0x68D0
    char _gap_68D4[12]; // +0x68D4
    UIStatic m_GameTime; // +0x68E0
    char _gap_68E4[156]; // +0x68E4
    UIStatic m_GameMoney; // +0x6980
    char _gap_6984[156]; // +0x6984
    UIParticle m_btnPar[16][7]; // +0x6A20
    char _gap_6BE0[65856]; // +0x6BE0
    UIParticle m_btnPar2[16][7]; // +0x16D20
    char _gap_16EE0[65856]; // +0x16EE0
    tagRECT m_btnParRc[7]; // +0x27020
    char _gap_2703C[84]; // +0x2703C
    _BYTE _isParBtn[7]; // +0x27090
    char _gap_27097[1]; // +0x27097
    int _curParEffect; // +0x27098
    UIStatic Sword_Name; // +0x2709C
    char _gap_270A0[156]; // +0x270A0
    UIStatic Sword_Att; // +0x2713C
    char _gap_27140[156]; // +0x27140
    UIStatic m_Ljs; // +0x271DC
    char _gap_271E0[156]; // +0x271E0
    UIStatic m_WulingCtrl; // +0x2727C
    char _gap_27280[156]; // +0x27280
    UI3DCtrl m_Sword; // +0x2731C
    char _gap_27320[304]; // +0x27320
    UI3DCtrl m_ljs3D; // +0x27450
    char _gap_27454[304]; // +0x27454
    UIStatic m_SwordFrame; // +0x27584
    char _gap_27588[156]; // +0x27588
    UIStatic m_SwordRemarkBk; // +0x27624
    char _gap_27628[156]; // +0x27628
    UIStatic m_SwordRemark; // +0x276C4
    char _gap_276C8[156]; // +0x276C8
    UIButton m_Yjfx; // +0x27764
    char _gap_27768[340]; // +0x27768
    tagRECT m_RemarkRc; // +0x278BC
    char _gap_278C0[12]; // +0x278C0
    tagRECT m_SwordRemarkRc; // +0x278CC
    char _gap_278D0[12]; // +0x278D0
    tagRECT m_NoteSwordRemarkRc; // +0x278DC
    char _gap_278E0[12]; // +0x278E0
    WORD m_SwordDstX; // +0x278EC
    WORD m_SwordNoteX; // +0x278EE
    int m_bSwordRemarkOut; // +0x278F0
    UIButton mb_Positive[5]; // +0x278F4
    char _gap_27908[1700]; // +0x27908
    UIStatic ms_Positive[5]; // +0x27FAC
    char _gap_27FC0[780]; // +0x27FC0
    UIButton mb_Lunar[5]; // +0x282CC
    char _gap_282E0[1700]; // +0x282E0
    UIStatic ms_Lunar[5]; // +0x28984
    char _gap_28998[780]; // +0x28998
    UIStatic ms_Perfect[5]; // +0x28CA4
    char _gap_28CB8[780]; // +0x28CB8
    BYTE m_CanCtrlBtn; // +0x28FC4
    char _gap_28FC5[3]; // +0x28FC5
    UIButton mb_Test; // +0x28FC8
    char _gap_28FCC[340]; // +0x28FCC
    UIParticle m_parSword[168]; // +0x29120
    char _gap_293C0[98784]; // +0x293C0
    tagRECT m_parSwordRc; // +0x415A0
    char _gap_415A4[12]; // +0x415A4
    UIParticle m_parPurge[168]; // +0x415B0
    char _gap_41850[98784]; // +0x41850
    UIButton m_PositiveBtn; // +0x59A30
    char _gap_59A34[340]; // +0x59A34
    UIButton m_LunarBtn; // +0x59B88
    char _gap_59B8C[340]; // +0x59B8C
    tagRECT Purge_rectA[5]; // +0x59CE0
    char _gap_59CF4[60]; // +0x59CF4
    tagRECT Purge_rectB[5]; // +0x59D30
    char _gap_59D44[60]; // +0x59D44
    tagRECT dstRect[5]; // +0x59D80
    char _gap_59D94[60]; // +0x59D94
    PurgeEffect m_PurgeEffect; // +0x59DD0
    char _gap_59DD4[424]; // +0x59DD4
    TimeCtl m_effTime; // +0x59F7C
    char _gap_59F80[8]; // +0x59F80
    BYTE m_bSwordMotion; // +0x59F88
    BYTE m_bSwordEff; // +0x59F89
    BYTE m_bSwordRot; // +0x59F8A
    BYTE m_bEff; // +0x59F8B
    int m_curpar; // +0x59F8C
    TimeCtl m_swdTime; // +0x59F90
    char _gap_59F94[8]; // +0x59F94
    int m_Orthosize; // +0x59F9C
    int m_FinalOrthosize; // +0x59FA0
    _PURGE_INFO m_PURGEINFO[11]; // +0x59FA4
    char _gap_59FD0[44]; // +0x59FD0
    UIFlexBar m_SmallBar; // +0x59FFC
    char _gap_5A000[80]; // +0x5A000
    UIFlexBar m_BigBar; // +0x5A050
    char _gap_5A054[80]; // +0x5A054
    UIButton m_Pushbtn[5]; // +0x5A0A4
    char _gap_5A0B8[1700]; // +0x5A0B8
    UIStatic m_equipFlag; // +0x5A75C
    char _gap_5A760[156]; // +0x5A760
    UIStatic m_purgeFlag; // +0x5A7FC
    char _gap_5A800[156]; // +0x5A800
    UIFlexBar m_ListTitle; // +0x5A89C
    char _gap_5A8A0[80]; // +0x5A8A0
    UIStatic m_EquipTitle; // +0x5A8F0
    char _gap_5A8F4[156]; // +0x5A8F4
    UIStatic m_PurgeTitle; // +0x5A990
    char _gap_5A994[156]; // +0x5A994
    UIStatic m_ListTitlePurge; // +0x5AA30
    char _gap_5AA34[156]; // +0x5AA34
    UIStatic m_ListFrame; // +0x5AAD0
    char _gap_5AAD4[156]; // +0x5AAD4
    UIStatic m_ListFramePurge; // +0x5AB70
    char _gap_5AB74[156]; // +0x5AB74
    UIStatic m_ListGrid[12]; // +0x5AC10
    char _gap_5AC40[1872]; // +0x5AC40
    UIStatic m_ListGridPurge[12]; // +0x5B390
    char _gap_5B3C0[1872]; // +0x5B3C0
    UIListBox m_WeaponList; // +0x5BB10
    char _gap_5BB14[1284]; // +0x5BB14
    UIListBox m_ClothList; // +0x5C018
    char _gap_5C01C[1284]; // +0x5C01C
    UIListBox m_HatList; // +0x5C520
    char _gap_5C524[1284]; // +0x5C524
    UIListBox m_ShoesList; // +0x5CA28
    char _gap_5CA2C[1284]; // +0x5CA2C
    UIListBox m_AdornList; // +0x5CF30
    char _gap_5CF34[1284]; // +0x5CF34
    UIListBox m_StuffList; // +0x5D438
    char _gap_5D43C[1284]; // +0x5D43C
    tagRECT m_StrRc; // +0x5D940
    char _gap_5D944[12]; // +0x5D944
    UIStatic m_EquipStr; // +0x5D950
    char _gap_5D954[156]; // +0x5D954
    UIStatic m_StuffStr; // +0x5D9F0
    char _gap_5D9F4[156]; // +0x5D9F4
    UIStatic m_GuVal; // +0x5DA90
    char _gap_5DA94[156]; // +0x5DA94
    tagRECT m_MsgRc; // +0x5DB30
    char _gap_5DB34[12]; // +0x5DB34
    UIStatic m_PurgeMsg; // +0x5DB40
    char _gap_5DB44[156]; // +0x5DB44
    UIFlexBar m_PurgeBottom; // +0x5DBE0
    char _gap_5DBE4[80]; // +0x5DBE4
    tagRECT m_BtnRc; // +0x5DC34
    char _gap_5DC38[12]; // +0x5DC38
    UIButton m_OK; // +0x5DC44
    char _gap_5DC48[340]; // +0x5DC48
    UIButton m_Cancel; // +0x5DD9C
    char _gap_5DDA0[340]; // +0x5DDA0
    UIButton m_SortEquipbyPrice; // +0x5DEF4
    char _gap_5DEF8[340]; // +0x5DEF8
    UIButton m_SortEquipbyGu; // +0x5E04C
    char _gap_5E050[340]; // +0x5E050
    UIButton m_SortStuffbyPrice; // +0x5E1A4
    char _gap_5E1A8[340]; // +0x5E1A8
    UIButton m_SortStuffbyGu; // +0x5E2FC
    char _gap_5E300[340]; // +0x5E300
    int m_SortState; // +0x5E454
    Inventory m_ItemArray; // +0x5E458
    char _gap_5E45C[36]; // +0x5E45C
    MUIDialog m_Dlg; // +0x5E480
    char _gap_5E484[1380]; // +0x5E484
    MUIDialog m_Msg; // +0x5E9E8
    char _gap_5E9EC[1380]; // +0x5E9EC
    WuLing note_purgenum; // +0x5EF50
    BYTE m_bHasWeapon; // +0x5EF54
    char _tail_5EF55[3]; // +0x5EF55
    // total size: 0x5EF58 (388952)

    gbTexture * RenderSword(); // 0x004AAD90
};
