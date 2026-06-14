#include "UIFrameWnd.h"
#pragma once
// Auto-generated: MainEquipUI

#include "MUIDialog.h"
#include "PlayerItem_Type.h"
#include "RoleAtt.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIListBox.h"
#include "UIParticle.h"
#include "UIStatic.h"
#include "me_RoleState.h"

class OpenNULLFile;
class StateUI;

class MainEquipUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    tagRECT rc; // +0x48
    char _gap_04C[12]; // +0x4C
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    BYTE m_IsMsg; // +0x168
    _BYTE m_Is[5]; // +0x169
    BYTE m_IsActive; // +0x16E
    BYTE m_IsCreateable; // +0x16F
    int m_SelNum; // +0x170
    int m_PutOnType; // +0x174
    PlayerItem_Type m_CurType; // +0x178
    StateUI * pStateUI; // +0x17C
    UIStatic m_Frame; // +0x180
    char _gap_184[156]; // +0x184
    UIStatic m_TimeMoney; // +0x220
    char _gap_224[156]; // +0x224
    UIStatic m_TopFrame; // +0x2C0
    char _gap_2C4[156]; // +0x2C4
    UIStatic m_TopFrameZB; // +0x360
    char _gap_364[156]; // +0x364
    UIStatic m_ScrollHB; // +0x400
    char _gap_404[156]; // +0x404
    UIStatic m_OutFrameT; // +0x4A0
    char _gap_4A4[156]; // +0x4A4
    UIStatic m_OutFrameR; // +0x540
    char _gap_544[156]; // +0x544
    UIStatic m_OutFrameL; // +0x5E0
    char _gap_5E4[156]; // +0x5E4
    UIStatic m_OutFrameB; // +0x680
    char _gap_684[156]; // +0x684
    UIStatic stp_BarL; // +0x720
    char _gap_724[156]; // +0x724
    UIFlexBar stp_BarM; // +0x7C0
    char _gap_7C4[80]; // +0x7C4
    UIStatic stp_BarR; // +0x814
    char _gap_818[156]; // +0x818
    UIButton stp_State; // +0x8B4
    char _gap_8B8[340]; // +0x8B8
    UIButton stp_Magic; // +0xA0C
    char _gap_A10[340]; // +0xA10
    UIButton stp_Equip; // +0xB64
    char _gap_B68[340]; // +0xB68
    UIButton stp_Prop; // +0xCBC
    char _gap_CC0[340]; // +0xCC0
    UIButton stp_BattleArray; // +0xE14
    char _gap_E18[340]; // +0xE18
    UIButton stp_TaskBook; // +0xF6C
    char _gap_F70[340]; // +0xF70
    UIButton stp_System; // +0x10C4
    char _gap_10C8[340]; // +0x10C8
    UIButton stp_Exit; // +0x121C
    char _gap_1220[340]; // +0x1220
    UIStatic stp_Effect; // +0x1374
    char _gap_1378[156]; // +0x1378
    tagRECT stp_Rect; // +0x1414
    char _gap_1418[12]; // +0x1418
    UIStatic m_GameTime; // +0x1424
    char _gap_1428[156]; // +0x1428
    UIStatic m_GameMoney; // +0x14C4
    char _gap_14C8[156]; // +0x14C8
    MUIDialog m_DlgEx; // +0x1564
    char _gap_1568[1380]; // +0x1568
    UIParticle m_btnPar[16][7]; // +0x1ACC
    char _gap_1C8C[65856]; // +0x1C8C
    UIParticle m_btnPar2[16][7]; // +0x11DCC
    char _gap_11F8C[65856]; // +0x11F8C
    tagRECT m_btnParRc[7]; // +0x220CC
    char _gap_220E8[84]; // +0x220E8
    _BYTE _isParBtn[7]; // +0x2213C
    char _gap_22143[1]; // +0x22143
    int _curParEffect; // +0x22144
    me_RoleState me_Role[5]; // +0x22148
    char _gap_2215C[48480]; // +0x2215C
    UIStatic m_WeaponName; // +0x2DEBC
    char _gap_2DEC0[156]; // +0x2DEC0
    UIStatic m_ClothName; // +0x2DF5C
    char _gap_2DF60[156]; // +0x2DF60
    UIStatic m_ShoesName; // +0x2DFFC
    char _gap_2E000[156]; // +0x2E000
    UIStatic m_HatName; // +0x2E09C
    char _gap_2E0A0[156]; // +0x2E0A0
    UIStatic m_Adorn1Name; // +0x2E13C
    char _gap_2E140[156]; // +0x2E140
    UIStatic m_Adorn2Name; // +0x2E1DC
    char _gap_2E1E0[156]; // +0x2E1E0
    UIStatic m_RemarkBk; // +0x2E27C
    char _gap_2E280[156]; // +0x2E280
    UIStatic m_Remark; // +0x2E31C
    char _gap_2E320[156]; // +0x2E320
    UIStatic m_RemarkVal; // +0x2E3BC
    char _gap_2E3C0[156]; // +0x2E3C0
    UIStatic m_typeWord; // +0x2E45C
    char _gap_2E460[156]; // +0x2E460
    tagRECT m_remarkRc; // +0x2E4FC
    char _gap_2E500[12]; // +0x2E500
    RoleAtt m_role[5]; // +0x2E50C
    char _gap_2E520[4240]; // +0x2E520
    MUIDialog m_Dlg; // +0x2F5B0
    char _gap_2F5B4[1380]; // +0x2F5B4
    UIButton m_Ctrlbtn[5]; // +0x2FB18
    char _gap_2FB2C[1700]; // +0x2FB2C
    UIStatic m_ClothIcon; // +0x301D0
    char _gap_301D4[156]; // +0x301D4
    UIStatic m_HatIcon; // +0x30270
    char _gap_30274[156]; // +0x30274
    UIStatic m_ShoesIcon; // +0x30310
    char _gap_30314[156]; // +0x30314
    UIStatic m_WeaponIcon; // +0x303B0
    char _gap_303B4[156]; // +0x303B4
    UIStatic m_AdornIcon1; // +0x30450
    char _gap_30454[156]; // +0x30454
    UIStatic m_AdornIcon2; // +0x304F0
    char _gap_304F4[156]; // +0x304F4
    tagRECT m_SelRc; // +0x30590
    char _gap_30594[12]; // +0x30594
    UIButton m_SelRole[5]; // +0x305A0
    char _gap_305B4[1700]; // +0x305B4
    int m_CurSelRole; // +0x30C58
    UIFlexBar m_ListTitle; // +0x30C5C
    char _gap_30C60[80]; // +0x30C60
    UIStatic m_ListFrame; // +0x30CB0
    char _gap_30CB4[156]; // +0x30CB4
    UIStatic m_ListGrid[14]; // +0x30D50
    char _gap_30D88[2184]; // +0x30D88
    UIStatic m_title; // +0x31610
    char _gap_31614[156]; // +0x31614
    UIListBox ml_Equiplist; // +0x316B0
    char _gap_316B4[1284]; // +0x316B4
    int last_index; // +0x31BB8
    tagRECT m_SortRc; // +0x31BBC
    char _gap_31BC0[12]; // +0x31BC0
    UIButton mb_SortDefault; // +0x31BCC
    char _tail_31BD0[892]; // +0x31BD0
    // total size: 0x31F4C (204620)

    virtual ~MainEquipUI() {}

    virtual void Render(); // 0x0047B200
    virtual BOOL Render3DModel(); // 0x0047B3B0
    virtual int OnMessage(int nVal, int nVal2, int nVal3); // 0x0047B6C0
    int ctor_9300(); // 0x00479300
    void ctor(); // 0x00479680
    int InitMainEquipUI(int arg0); // 0x00479890
    void ValidateRoles(); // 0x0047A580
    int UpdateLayout(); // 0x0047AAB0
    int UpdateCompareLayout(); // 0x0047ADF0
    void FormatItemPath(int nVal); // 0x0047B140
    int ClearState(); // 0x0047EC00
    int CreateUI(); // 0x0047ECB0
    int * UpdateFadeAlpha(float fVal); // 0x00480530
    OpenNULLFile * LoadFromFile(OpenNULLFile *pFile, int nVal); // 0x004819A0
    unsigned __int8 SetAdornVisible(unsigned __int8 pData); // 0x00481BA0
    void SelectWithSound(int nVal); // 0x00481CB0
    void ShowPanelsWithSound(int nVal, int nVal2); // 0x00481EB0
    void RenderEquipDetails(int arg0); // 0x00482140
    int CountVisibleStats(); // 0x004844A0
    void UpdateTooltip(int nVal); // 0x004930E0
    void ShowWithCursor(int nVal); // 0x0049AEA0
    void SetupRoleList(int arg0, char arg4); // 0x0049B2E0
    void SetSlotLabel(int nVal, int nVal2, int nVal3); // 0x0049C9F0
    void ResetControls(); // 0x0049E670
    int CreateFromData(int *pBuffer); // 0x0049E8E0
    void * CreateListPanel(int nVal, int FC); // 0x0049F2E0
    int _MainEquipUI(); // 0x004A2450
    int HandleDeviceLostB(); // 0x004A4780
    int Render_4a4820(); // 0x004A4820
    int ShowPage(); // 0x004A4ED0
    BOOL SetEquipSlotData(); // 0x004A4FC0
    BOOL HandleMessage(); // 0x004A5010
    int RenderThrottled(); // 0x004A5930
    int LayoutHandleNav(); // 0x004A5A80
    int UpdateCaptions(); // 0x004A5B30
};
