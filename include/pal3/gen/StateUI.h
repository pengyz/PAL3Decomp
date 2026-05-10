#pragma once
// Auto-generated: StateUI

#include "MUIDialog.h"
#include "UI3DCtrl.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIFrameWnd.h"
#include "UIParticle.h"
#include "UIStatic.h"
#include "s_RoleState.h"
#include "s_SpecialPropItem.h"

class JusticeBookUI;
class LineupUI;
class MagicUI;
class MainEquipUI;
class MainPropUI;
class SwordUI;
class SystemUI;
class TaskBookUI;

class StateUI : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    unsigned char m_IsMsg; // +0x168
    unsigned char m_Is[5]; // +0x169
    int m_CtrlRole; // +0x170
    unsigned char m_IsActive; // +0x174
    unsigned char m_IsCreateable; // +0x175
    UIStatic m_Frame; // +0x178
    UIStatic m_TimeMoney; // +0x218
    UIStatic m_OutFrameT; // +0x2B8
    UIStatic m_OutFrameR; // +0x358
    UIStatic m_OutFrameL; // +0x3F8
    UIStatic m_OutFrameB; // +0x498
    UIStatic stp_BarL; // +0x538
    UIFlexBar stp_BarM; // +0x5D8
    UIStatic stp_BarR; // +0x62C
    UIButton stp_State; // +0x6CC
    UIButton stp_Magic; // +0x824
    UIButton stp_Equip; // +0x97C
    UIButton stp_Prop; // +0xAD4
    UIButton stp_BattleArray; // +0xC2C
    UIButton stp_TaskBook; // +0xD84
    UIButton stp_System; // +0xEDC
    UIButton stp_Exit; // +0x1034
    UIStatic stp_Effect; // +0x118C
    tagRECT stp_Rect; // +0x122C
    UIStatic m_GameTime; // +0x123C
    UIStatic m_GameMoney; // +0x12DC
    UIParticle m_par[16][7]; // +0x137C
    UIParticle m_par2[16][7]; // +0x1167C
    tagRECT m_parRc[7]; // +0x2197C
    unsigned char _isParBtn[7]; // +0x219EC
    int _curParEffect; // +0x219F4
    tagRECT m_PortraitRc; // +0x219F8
    UIStatic m_Portrait; // +0x21A08
    UIStatic m_TeamState; // +0x21AA8
    UIStatic m_Time; // +0x21B48
    UIStatic m_Money; // +0x21BE8
    tagRECT m_TeamStateRc; // +0x21C88
    s_RoleState m_RoleState[5]; // +0x21C98
    UIStatic m_State[4]; // +0x269B4
    UIStatic m_Alignment; // +0x26C34
    tagRECT m_AlignmentRc; // +0x26CD4
    UIStatic m_Head[5]; // +0x26CE4
    tagRECT m_HeadRc[5]; // +0x27004
    UIStatic m_TopFrame; // +0x27054
    UIButton m_LeaveHere; // +0x270F4
    tagRECT m_LeaveRc; // +0x2724C
    UI3DCtrl m_3DObj; // +0x2725C
    MUIDialog m_DlgEx; // +0x27390
    LineupUI * p_LineupUI; // +0x278F8
    MagicUI * p_MagicUI; // +0x278FC
    MainEquipUI * p_mEquipUI; // +0x27900
    MainPropUI * p_mPropUI; // +0x27904
    SwordUI * p_SwordUI; // +0x27908
    JusticeBookUI * p_JusticeBookUI; // +0x2790C
    TaskBookUI * p_TaskBookUI; // +0x27910
    SystemUI * p_SystemUI; // +0x27914
    int m_curRender; // +0x27918
    unsigned char m_saveflag_note; // +0x2791C
    unsigned char m_isSeekSAVELOAD; // +0x2791D
    UIStatic m_test; // +0x27920
    gbTexture * pInterceptTex; // +0x279C0
    float sv; // +0x279C4
    float ev; // +0x279C8
    unsigned char mainuiopt; // +0x0
    unsigned char enable_save; // +0x0
    unsigned char m_isSword; // +0x0
    unsigned char m_isJusticeBook; // +0x0
    unsigned char m_isExit; // +0x279CC
    s_SpecialPropItem m_SpecialPropItem[5]; // +0x279D0
    // total size: 0x279F8 (162296)

    int Create(); // 0x004A4960
    void Init(); // 0x004A4A10
};
