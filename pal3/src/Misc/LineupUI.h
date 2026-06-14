#include "UIFrameWnd.h"
#pragma once
// Auto-generated: LineupUI

#include "LINEUPINFO.h"
#include "LineupPlank.h"
#include "MUIDialog.h"
#include "Object3D.h"
#include "ProtectPanel.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIParticle.h"
#include "UIStatic.h"
#include "gbengine/gbengine_types.h"

class ObjectCamera;
class StateUI;

class LineupUI : public UIFrameWnd {
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
    char _gap_16E[2]; // +0x16E
    UIStatic m_Frame; // +0x170
    char _gap_174[156]; // +0x174
    UIStatic m_TimeMoney; // +0x210
    char _gap_214[156]; // +0x214
    UIStatic m_OutFrameT; // +0x2B0
    char _gap_2B4[156]; // +0x2B4
    UIStatic m_OutFrameR; // +0x350
    char _gap_354[156]; // +0x354
    UIStatic m_OutFrameL; // +0x3F0
    char _gap_3F4[156]; // +0x3F4
    UIStatic m_OutFrameB; // +0x490
    char _gap_494[156]; // +0x494
    UIStatic stp_BarL; // +0x530
    char _gap_534[156]; // +0x534
    UIFlexBar stp_BarM; // +0x5D0
    char _gap_5D4[80]; // +0x5D4
    UIStatic stp_BarR; // +0x624
    char _gap_628[156]; // +0x628
    UIButton stp_State; // +0x6C4
    char _gap_6C8[340]; // +0x6C8
    UIButton stp_Magic; // +0x81C
    char _gap_820[340]; // +0x820
    UIButton stp_Equip; // +0x974
    char _gap_978[340]; // +0x978
    UIButton stp_Prop; // +0xACC
    char _gap_AD0[340]; // +0xAD0
    UIButton stp_BattleArray; // +0xC24
    char _gap_C28[340]; // +0xC28
    UIButton stp_TaskBook; // +0xD7C
    char _gap_D80[340]; // +0xD80
    UIButton stp_System; // +0xED4
    char _gap_ED8[340]; // +0xED8
    UIButton stp_Exit; // +0x102C
    char _gap_1030[340]; // +0x1030
    UIStatic stp_Effect; // +0x1184
    char _gap_1188[156]; // +0x1188
    tagRECT stp_Rect; // +0x1224
    char _gap_1228[12]; // +0x1228
    UIStatic m_GameTime; // +0x1234
    char _gap_1238[156]; // +0x1238
    UIStatic m_GameMoney; // +0x12D4
    char _gap_12D8[156]; // +0x12D8
    MUIDialog m_DlgEx; // +0x1374
    char _gap_1378[1380]; // +0x1378
    UIStatic m_ZhenLie; // +0x18DC
    char _gap_18E0[156]; // +0x18E0
    UIParticle m_btnPar[16][7]; // +0x197C
    char _gap_1B3C[65856]; // +0x1B3C
    UIParticle m_btnPar2[16][7]; // +0x11C7C
    char _gap_11E3C[65856]; // +0x11E3C
    tagRECT m_btnParRc[7]; // +0x21F7C
    char _gap_21F98[84]; // +0x21F98
    _BYTE _isParBtn[7]; // +0x21FEC
    char _gap_21FF3[1]; // +0x21FF3
    int _curParEffect; // +0x21FF4
    LINEUPINFO m_LineupInfo[5]; // +0x21FF8
    char _gap_2200C[10]; // +0x2200C
    char m_Sequence[4]; // +0x22016
    char _gap_2201A[2]; // +0x2201A
    tagRECT roleRc; // +0x2201C
    char _gap_22020[12]; // +0x22020
    UIStatic m_RoleFrame; // +0x2202C
    char _gap_22030[156]; // +0x22030
    UIButton m_RoleBtn[5]; // +0x220CC
    char _gap_220E0[1700]; // +0x220E0
    int m_RoleBtnIndex[5]; // +0x22784
    UIStatic m_NoBody[5]; // +0x22798
    char _gap_227AC[780]; // +0x227AC
    UIStatic m_RoleLeader[5]; // +0x22AB8
    char _gap_22ACC[780]; // +0x22ACC
    tagRECT m_headRc[5]; // +0x22DD8
    char _gap_22DEC[60]; // +0x22DEC
    int m_headRole; // +0x22E28
    MUIDialog m_Msg; // +0x22E2C
    char _gap_22E30[1380]; // +0x22E30
    float m_objCamPitch; // +0x23394
    float m_objRotSpeed; // +0x23398
    ObjectCamera * m_pCamera; // +0x2339C
    float m_pointerHeight; // +0x233A0
    BYTE m_bPeek; // +0x233A4
    char _gap_233A5[3]; // +0x233A5
    int m_nPeek; // +0x233A8
    int m_nLastPeek; // +0x233AC
    BYTE m_isRotLineup; // +0x233B0
    char _gap_233B1[3]; // +0x233B1
    gbVec3D m_ObjPos[6]; // +0x233B4
    char _gap_233CC[48]; // +0x233CC
    Object3D m_LineupObj; // +0x233FC
    char _gap_23400[148]; // +0x23400
    Object3D m_3DRole[5]; // +0x23494
    char _gap_234A8[740]; // +0x234A8
    _BYTE m_IsRole[6]; // +0x2378C
    char _gap_23792[2]; // +0x23792
    int m_RoleId[6]; // +0x23794
    Object3D m_3DNone[6]; // +0x237AC
    char _gap_237C4[888]; // +0x237C4
    LineupPlank m_CtrlPlank[5]; // +0x23B3C
    char _gap_23B50[9940]; // +0x23B50
    ProtectPanel m_ProtectPanel; // +0x26224
    char _gap_26228[1284]; // +0x26228
    BYTE m_ProFlag; // +0x2672C
    char _gap_2672D[3]; // +0x2672D
    StateUI * pStateUI; // +0x26730
    char _tail_26734[13752]; // +0x26734
    // total size: 0x29CEC (171244)

    virtual ~LineupUI() {}

    virtual void RenderEffects(); // 0x0047F880
    virtual int CleanupAndForwardInput(); // 0x0047F970
    virtual int OnMessage(int nVal, char *pszBuf, int nVal2); // 0x00480600
    virtual int OnMsgHandleNav(unsigned int uMsg, unsigned int wParam, int lParam); // 0x00456500
    void _LineupUI(); // 0x00470F40
    int InitListView(); // 0x00471590
    int SetPageIndex(int nPage); // 0x00472A80
    void RefreshListData(); // 0x00472AA0
    int Render3DModels(); // 0x00473520
    int BuildEquipList(); // 0x004739F0
    int InitItemList(); // 0x00473B50
    void ProcessMouseInput(float fVal); // 0x00474AB0
    int UpdateAndForward(int nVal, int nVal2); // 0x00474C50
    int BuildListItems(); // 0x00474C80
    int RefreshDisplay(); // 0x00475FC0
    int PopulateList(); // 0x00476010
    int UpdateAllSlots(); // 0x004765D0
    int SetItemDisplay(); // 0x004765F0
    int SetItemColors(); // 0x00476ED0
    int RefreshDisplayEx(); // 0x004777B0
    int OnMessage(int msg, int wparam, int lparam); // 0x00477BB0
    char CountVisibleItems(int nVal); // 0x0047B0E0
    int ctor_E5C0(); // 0x0047E5C0
    void ctor(); // 0x0047E910
    int RebuildSystemPage(); // 0x004826A0
    int ShowPage(); // 0x00482BB0
    int Save(); // 0x00482ED0
    void * CreatePreviewScene(int nVal); // 0x00483650
    int GetSlotRect(int nVal, unsigned int dwVal); // 0x00484360
    int RebuildNavPage(); // 0x00484810
    static void LoadRoleData(); // 0x00488DE0
    int RebuildExitPage(); // 0x00491630
    int RebuildCaptionPage(); // 0x004993D0
    int RebuildFontPage(); // 0x004A26D0
    int * UpdateProtectPanel(int nVal); // 0x004B1920
    int RebuildMainPage(); // 0x004B3DA0
};
