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
#include "UIFrameWnd.h"
#include "UIListBox.h"
#include "UIParticle.h"
#include "UIStatic.h"
#include "WuLing.h"
#include "_PURGE_INFO.h"

class StateUI;

class SwordUI : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    int m_ljsNum; // +0x168
    UIStatic m_ljsNumber; // +0x16C
    int m_purgeEquipNum; // +0x20C
    int m_purgeWeaponNum; // +0x210
    int m_avgWeaponWU; // +0x214
    int m_avgAdornWU; // +0x218
    int m_avgAdornFANG; // +0x21C
    int m_avgDefFANG; // +0x220
    int m_adornNum; // +0x224
    int m_defNum; // +0x228
    FightSkill m_WSkill[28]; // +0x22C
    int m_wskillNum; // +0x554C
    BYTE m_IsMsg; // +0x5550
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
    int FetchVal; // +0x5B9C
    int GuVal; // +0x5BA0
    StateUI * pStateUI; // +0x5BA4
    UIStatic m_FrameLine; // +0x5BA8
    UIStatic m_TimeMoney; // +0x5C48
    UIStatic stp_BarL; // +0x5CE8
    UIStatic stp_BarM; // +0x5D88
    UIStatic stp_BarR; // +0x5E28
    UIButton stp_State; // +0x5EC8
    UIButton stp_Magic; // +0x6020
    UIButton stp_Equip; // +0x6178
    UIButton stp_Prop; // +0x62D0
    UIButton stp_BattleArray; // +0x6428
    UIButton stp_System; // +0x6580
    UIButton stp_Exit; // +0x66D8
    UIStatic stp_Effect; // +0x6830
    tagRECT stp_Rect; // +0x68D0
    UIStatic m_GameTime; // +0x68E0
    UIStatic m_GameMoney; // +0x6980
    UIParticle m_btnPar[16][7]; // +0x6A20
    UIParticle m_btnPar2[16][7]; // +0x16D20
    tagRECT m_btnParRc[7]; // +0x27020
    BYTE _isParBtn[7]; // +0x27090
    int _curParEffect; // +0x27098
    UIStatic Sword_Name; // +0x2709C
    UIStatic Sword_Att; // +0x2713C
    UIStatic m_Ljs; // +0x271DC
    UIStatic m_WulingCtrl; // +0x2727C
    UI3DCtrl m_Sword; // +0x2731C
    UI3DCtrl m_ljs3D; // +0x27450
    UIStatic m_SwordFrame; // +0x27584
    UIStatic m_SwordRemarkBk; // +0x27624
    UIStatic m_SwordRemark; // +0x276C4
    UIButton m_Yjfx; // +0x27764
    tagRECT m_RemarkRc; // +0x278BC
    tagRECT m_SwordRemarkRc; // +0x278CC
    tagRECT m_NoteSwordRemarkRc; // +0x278DC
    WORD m_SwordDstX; // +0x278EC
    WORD m_SwordNoteX; // +0x278EE
    int m_bSwordRemarkOut; // +0x278F0
    UIButton mb_Positive[5]; // +0x278F4
    UIStatic ms_Positive[5]; // +0x27FAC
    UIButton mb_Lunar[5]; // +0x282CC
    UIStatic ms_Lunar[5]; // +0x28984
    UIStatic ms_Perfect[5]; // +0x28CA4
    BYTE m_CanCtrlBtn; // +0x28FC4
    UIButton mb_Test; // +0x28FC8
    UIParticle m_parSword[168]; // +0x29120
    tagRECT m_parSwordRc; // +0x415A0
    UIParticle m_parPurge[168]; // +0x415B0
    UIButton m_PositiveBtn; // +0x59A30
    UIButton m_LunarBtn; // +0x59B88
    tagRECT Purge_rectA[5]; // +0x59CE0
    tagRECT Purge_rectB[5]; // +0x59D30
    tagRECT dstRect[5]; // +0x59D80
    PurgeEffect m_PurgeEffect; // +0x59DD0
    TimeCtl m_effTime; // +0x59F7C
    BYTE m_bSwordMotion; // +0x59F88
    BYTE m_bSwordEff; // +0x59F89
    BYTE m_bSwordRot; // +0x59F8A
    BYTE m_bEff; // +0x59F8B
    int m_curpar; // +0x59F8C
    TimeCtl m_swdTime; // +0x59F90
    int m_Orthosize; // +0x59F9C
    int m_FinalOrthosize; // +0x59FA0
    _PURGE_INFO m_PURGEINFO[11]; // +0x59FA4
    UIFlexBar m_SmallBar; // +0x59FFC
    UIFlexBar m_BigBar; // +0x5A050
    UIButton m_Pushbtn[5]; // +0x5A0A4
    UIStatic m_equipFlag; // +0x5A75C
    UIStatic m_purgeFlag; // +0x5A7FC
    UIFlexBar m_ListTitle; // +0x5A89C
    UIStatic m_EquipTitle; // +0x5A8F0
    UIStatic m_PurgeTitle; // +0x5A990
    UIStatic m_ListTitlePurge; // +0x5AA30
    UIStatic m_ListFrame; // +0x5AAD0
    UIStatic m_ListFramePurge; // +0x5AB70
    UIStatic m_ListGrid[12]; // +0x5AC10
    UIStatic m_ListGridPurge[12]; // +0x5B390
    UIListBox m_WeaponList; // +0x5BB10
    UIListBox m_ClothList; // +0x5C018
    UIListBox m_HatList; // +0x5C520
    UIListBox m_ShoesList; // +0x5CA28
    UIListBox m_AdornList; // +0x5CF30
    UIListBox m_StuffList; // +0x5D438
    tagRECT m_StrRc; // +0x5D940
    UIStatic m_EquipStr; // +0x5D950
    UIStatic m_StuffStr; // +0x5D9F0
    UIStatic m_GuVal; // +0x5DA90
    tagRECT m_MsgRc; // +0x5DB30
    UIStatic m_PurgeMsg; // +0x5DB40
    UIFlexBar m_PurgeBottom; // +0x5DBE0
    tagRECT m_BtnRc; // +0x5DC34
    UIButton m_OK; // +0x5DC44
    UIButton m_Cancel; // +0x5DD9C
    UIButton m_SortEquipbyPrice; // +0x5DEF4
    UIButton m_SortEquipbyGu; // +0x5E04C
    UIButton m_SortStuffbyPrice; // +0x5E1A4
    UIButton m_SortStuffbyGu; // +0x5E2FC
    int m_SortState; // +0x5E454
    Inventory m_ItemArray; // +0x5E458
    MUIDialog m_Dlg; // +0x5E480
    MUIDialog m_Msg; // +0x5E9E8
    WuLing note_purgenum; // +0x5EF50
    BYTE m_bHasWeapon; // +0x5EF54
    BYTE m_isyjfx; // +0x0
    BYTE m_isPurged[5][2]; // +0x0
    BYTE m_isAllPurged[5]; // +0x0
    WuLing m_PurgeNum; // +0x0
    // total size: 0x5EF58 (388952)

};
