#include "UIFrameWnd.h"
#pragma once
// Auto-generated: StateUI

#include "MUIDialog.h"
#include "UI3DCtrl.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIParticle.h"
#include "UIStatic.h"
#include "gbengine/gbTexture.h"
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
class UIWnd;

class StateUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    BYTE m_isJusticeBook; // +0x48
    char _gap_049[207]; // +0x49
    BYTE m_IsMsg; // +0x118
    _BYTE m_Is[5]; // +0x119
    char _gap_11E[2]; // +0x11E
    int m_CtrlRole; // +0x120
    BYTE m_IsActive; // +0x124
    BYTE m_IsCreateable; // +0x125
    char _gap_126[2]; // +0x126
    UIStatic m_Frame; // +0x128
    char _gap_12C[148]; // +0x12C
    UIStatic m_TimeMoney; // +0x1C0
    char _gap_1C4[148]; // +0x1C4
    UIStatic m_OutFrameT; // +0x258
    char _gap_25C[148]; // +0x25C
    UIStatic m_OutFrameR; // +0x2F0
    char _gap_2F4[148]; // +0x2F4
    UIStatic m_OutFrameL; // +0x388
    char _gap_38C[148]; // +0x38C
    UIStatic m_OutFrameB; // +0x420
    char _gap_424[148]; // +0x424
    UIStatic stp_BarL; // +0x4B8
    char _gap_4BC[148]; // +0x4BC
    UIFlexBar stp_BarM; // +0x550
    char _gap_554[80]; // +0x554
    UIStatic stp_BarR; // +0x5A4
    char _gap_5A8[148]; // +0x5A8
    UIButton stp_State; // +0x63C
    char _gap_640[340]; // +0x640
    UIButton stp_Magic; // +0x794
    char _gap_798[340]; // +0x798
    UIButton stp_Equip; // +0x8EC
    char _gap_8F0[340]; // +0x8F0
    UIButton stp_Prop; // +0xA44
    char _gap_A48[340]; // +0xA48
    UIButton stp_BattleArray; // +0xB9C
    char _gap_BA0[340]; // +0xBA0
    UIButton stp_TaskBook; // +0xCF4
    char _gap_CF8[340]; // +0xCF8
    UIButton stp_System; // +0xE4C
    char _gap_E50[340]; // +0xE50
    UIButton stp_Exit; // +0xFA4
    char _gap_FA8[340]; // +0xFA8
    UIStatic stp_Effect; // +0x10FC
    char _gap_1100[148]; // +0x1100
    tagRECT stp_Rect; // +0x1194
    char _gap_1198[12]; // +0x1198
    UIStatic m_GameTime; // +0x11A4
    char _gap_11A8[148]; // +0x11A8
    UIStatic m_GameMoney; // +0x123C
    char _gap_1240[148]; // +0x1240
    UIParticle m_par[16][7]; // +0x12D4
    char _gap_1494[65856]; // +0x1494
    UIParticle m_par2[16][7]; // +0x115D4
    char _gap_11794[65856]; // +0x11794
    tagRECT m_parRc[7]; // +0x218D4
    char _gap_218F0[84]; // +0x218F0
    _BYTE _isParBtn[7]; // +0x21944
    char _gap_2194B[1]; // +0x2194B
    int _curParEffect; // +0x2194C
    tagRECT m_PortraitRc; // +0x21950
    char _gap_21954[12]; // +0x21954
    UIStatic m_Portrait; // +0x21960
    char _gap_21964[148]; // +0x21964
    UIStatic m_TeamState; // +0x219F8
    char _gap_219FC[148]; // +0x219FC
    UIStatic m_Time; // +0x21A90
    char _gap_21A94[148]; // +0x21A94
    UIStatic m_Money; // +0x21B28
    char _gap_21B2C[148]; // +0x21B2C
    tagRECT m_TeamStateRc; // +0x21BC0
    char _gap_21BC4[12]; // +0x21BC4
    s_RoleState m_RoleState[5]; // +0x21BD0
    char _gap_21BE4[19720]; // +0x21BE4
    UIStatic m_State[4]; // +0x268EC
    char _gap_268FC[592]; // +0x268FC
    UIStatic m_Alignment; // +0x26B4C
    char _gap_26B50[148]; // +0x26B50
    tagRECT m_AlignmentRc; // +0x26BE4
    char _gap_26BE8[12]; // +0x26BE8
    UIStatic m_Head[5]; // +0x26BF4
    char _gap_26C08[740]; // +0x26C08
    tagRECT m_HeadRc[5]; // +0x26EEC
    char _gap_26F00[60]; // +0x26F00
    UIStatic m_TopFrame; // +0x26F3C
    char _gap_26F40[148]; // +0x26F40
    UIButton m_LeaveHere; // +0x26FD4
    char _gap_26FD8[340]; // +0x26FD8
    tagRECT m_LeaveRc; // +0x2712C
    char _gap_27130[12]; // +0x27130
    UI3DCtrl m_3DObj; // +0x2713C
    char _gap_27140[304]; // +0x27140
    MUIDialog m_DlgEx; // +0x27270
    char _gap_27274[1380]; // +0x27274
    LineupUI * p_LineupUI; // +0x277D8
    MagicUI * p_MagicUI; // +0x277DC
    MainEquipUI * p_mEquipUI; // +0x277E0
    MainPropUI * p_mPropUI; // +0x277E4
    SwordUI * p_SwordUI; // +0x277E8
    JusticeBookUI * p_JusticeBookUI; // +0x277EC
    TaskBookUI * p_TaskBookUI; // +0x277F0
    SystemUI * p_SystemUI; // +0x277F4
    int m_curRender; // +0x277F8
    BYTE m_saveflag_note; // +0x277FC
    BYTE m_isSeekSAVELOAD; // +0x277FD
    char _gap_277FE[2]; // +0x277FE
    UIStatic m_test; // +0x27800
    char _gap_27804[148]; // +0x27804
    gbTexture * pInterceptTex; // +0x27898
    float sv; // +0x2789C
    float ev; // +0x278A0
    BYTE m_isExit; // +0x278A4
    char _gap_278A5[3]; // +0x278A5
    s_SpecialPropItem m_SpecialPropItem[5]; // +0x278A8
    char _tail_278BC[20]; // +0x278BC
    // total size: 0x278D0 (162000)

    virtual int OnRender(); // 0x00485DF0
    int LoadRoleList(); // 0x0047F390
    int ReleaseResource(); // 0x0047F410
    int CategorizeRoles(); // 0x0047F450
    int ShowPanels(int nVal, unsigned __int8 pData, UIWnd *bFlag); // 0x00480070
    int DispatchCmd(BOOL bFlag); // 0x00480450
    int AutoScrollParticles(int nVal); // 0x00482C90
    void ctor(); // 0x00483380
    int IteratePlayerAtts(); // 0x004845F0
    int UpdateVisibility(); // 0x00484660
    int SelectTab1(unsigned __int8 nTab); // 0x00484E90
    int SelectTab2(unsigned __int8 nTab); // 0x00484EB0
    int RefreshStatsDisplay(); // 0x00485980
    char * RefreshFromAtts(); // 0x00485CD0
    int SelectSubTab1(unsigned __int8 nTab); // 0x0048A310
    int SelectSubTab2(unsigned __int8 nTab); // 0x0048A330
    void UpdateRoleTooltip(int nVal); // 0x00492850
    void UpdateAttributeDisplay(int arg0, char *pszBuf, float id); // 0x00493420
    void UpdateScrollBars(); // 0x004940F0
    int ForwardToBigMap(char pData); // 0x004945E0
    int SelectBigMapTab2(char nTab); // 0x00494600
    int ShowPage(); // 0x004998E0
    void DisplayCaption(int nVal); // 0x0049A360
    int UpdateScrollValues(); // 0x0049AC70
    int SelectXJTMTab1(unsigned __int8 nTab); // 0x0049E860
    int SelectXJTMTab2(unsigned __int8 nTab); // 0x0049E880
    UIWnd * GetChildPtr(int index); // 0x004A2BD0
    UIWnd * FindChild(int id); // 0x004A2F90
    int InitLayout(); // 0x004A4960
    void CreateWidgets(); // 0x004A4A10
    int SaveData(); // 0x004B2470
};
