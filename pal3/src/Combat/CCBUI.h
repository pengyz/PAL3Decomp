#include "UIFrameWnd.h"
#pragma once
// Auto-generated: CCBUI

#include "CCBUI_funcptr_t.h"
#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbengine_types.h"
#include "tagUITask.h"

class CCBAIWindow;
class CCBCamControl;
class CCBControlWindow;
class CCBFiveNimbusWindow;
class CCBItemWindow;
class CCBLineupWindow;
class CCBMagicWindow;
class CCBParabolaWindow;
class CCBProtectWindow;
class CCBResultWindow;
class CCBSkillWindow;
class CCBSystem;
class CUtil;
class UIButton;
class UIProgressBar;
class UIStatic;
class UIStaticCB;

class CCBUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    UIStatic * m_pAttackSequenBack; // +0x48
    UIStatic * pPanel; // +0x4C
    UIStatic * m_pBattleFieldAttr[6]; // +0x50
    char _gap_054[20]; // +0x54
    UIStatic * m_pAttackSequenFace[11]; // +0x68
    char _gap_06C[40]; // +0x6C
    UIStatic * m_pRoleStatePanel[4]; // +0x94
    char _gap_098[12]; // +0x98
    UIStatic * m_pRoleStateFace[5]; // +0xA4
    char _gap_0A8[16]; // +0xA8
    UIStatic * m_pRoleStateFaceName[5]; // +0xB8
    char _gap_0BC[16]; // +0xBC
    UIStatic * m_pRoleStateAttackInc[11]; // +0xCC
    char _gap_0D0[40]; // +0xD0
    UIStatic * m_pRoleStateAttackDec[11]; // +0xF8
    char _gap_0FC[40]; // +0xFC
    UIStatic * m_pRoleStateDefenceInc[11]; // +0x124
    char _gap_128[40]; // +0x128
    UIStatic * m_pRoleStateDefenceDec[11]; // +0x150
    char _gap_154[40]; // +0x154
    UIStatic * m_pRoleStateLuckInc[11]; // +0x17C
    char _gap_180[40]; // +0x180
    UIStatic * m_pRoleStateLuckDec[11]; // +0x1A8
    char _gap_1AC[40]; // +0x1AC
    UIStatic * m_pRoleStateSpeedInc[11]; // +0x1D4
    char _gap_1D8[40]; // +0x1D8
    UIStatic * m_pRoleStateSpeedDec[11]; // +0x200
    char _gap_204[40]; // +0x204
    UIStatic * m_pRoleStateStable[11]; // +0x22C
    char _gap_230[40]; // +0x230
    UIStatic * m_pRoleStateBlank[11]; // +0x258
    char _gap_25C[40]; // +0x25C
    UIStatic * m_pRoleStateForbid[11]; // +0x284
    char _gap_288[40]; // +0x288
    UIStatic * m_pRoleStateSleep[11]; // +0x2B0
    char _gap_2B4[40]; // +0x2B4
    UIStatic * m_pRoleStateChaos[11]; // +0x2DC
    char _gap_2E0[40]; // +0x2E0
    UIStatic * m_pRoleStateMad[11]; // +0x308
    char _gap_30C[40]; // +0x30C
    UIStatic * m_pRoleStateMirror[11]; // +0x334
    char _gap_338[40]; // +0x338
    UIStatic * m_pRoleStateWall[11]; // +0x360
    char _gap_364[40]; // +0x364
    UIStatic * m_pRoleStateBound[11]; // +0x38C
    char _gap_390[40]; // +0x390
    UIStatic * m_pRoleStateHermit[11]; // +0x3B8
    char _gap_3BC[40]; // +0x3BC
    UIStatic * m_pRoleStateImmunity[11]; // +0x3E4
    char _gap_3E8[40]; // +0x3E8
    UIStatic * m_pWinPanel; // +0x410
    UIStatic * m_pLosePanel; // +0x414
    UIProgressBar * m_pRoleStateHP[4]; // +0x418
    char _gap_41C[12]; // +0x41C
    UIProgressBar * m_pRoleStateGP[4]; // +0x428
    char _gap_42C[12]; // +0x42C
    UIProgressBar * m_pRoleStateMP[4]; // +0x438
    char _gap_43C[12]; // +0x43C
    UIProgressBar * m_pRoleStateSword; // +0x448
    UIStaticCB * m_pTrickName; // +0x44C
    UIStaticCB * m_pTrickName2; // +0x450
    UIStatic * m_pDialogBack; // +0x454
    UIStatic * m_pResultLevelup; // +0x458
    UIStatic * m_pResultWindLvup; // +0x45C
    UIStatic * m_pResultThunderLvup; // +0x460
    UIStatic * m_pResultWaterLvup; // +0x464
    UIStatic * m_pResultFireLvup; // +0x468
    UIStatic * m_pResultEarthLvup; // +0x46C
    UIStatic * m_pResultDoubleLvup; // +0x470
    UIStatic * m_pResultGetItem; // +0x474
    CCBControlWindow * m_pMain; // +0x478
    CCBItemWindow * m_pItemWindow; // +0x47C
    CCBParabolaWindow * m_pParabolaWindow; // +0x480
    CCBMagicWindow * m_pMagicWindow; // +0x484
    CCBSkillWindow * m_pSkillWindow; // +0x488
    CCBAIWindow * m_pAIWindow; // +0x48C
    CCBLineupWindow * m_pLineupWindow; // +0x490
    CCBProtectWindow * m_pProtectWindow; // +0x494
    CCBResultWindow * m_pResultWindow[4]; // +0x498
    char _gap_49C[12]; // +0x49C
    CCBFiveNimbusWindow * m_pFiveNimbusWindow; // +0x4A8
    CCBSystem * m_pCBSystem; // +0x4AC
    CUtil * m_pUtil; // +0x4B0
    char _gap_4B4[4]; // +0x4B4
    tagUITask m_Task[19]; // +0x4B8
    char _gap_504[1324]; // +0x504
    CCBUI_funcptr_t fp; // +0xA30
    char _tail_A34[36]; // +0xA34
    // total size: 0xA58 (2648)

    virtual ~CCBUI() {}

    void SetTooltip(const char *szText); // 0x00441040
    void SetRect(RECT *pRect); // 0x00441070
    int ShowEffect(int nY, int nWidth, int nHeight); // 0x00441380
    gbVFileSystem * LoadTextureSequence(gbVFileSystem *pPath, char bUseAtlas); // 0x004413C0
    int VirtualCall(); // 0x004420B0
    void SetTargetPos(gbVec3D *pPos, gbVec3D *pDir); // 0x00442170
    void SetCurPlayer(int nPlayer); // 0x004421F0
    int SetRoleStatePointers(int nVal); // 0x00442200
    int SetSelection(int nItemIndex); // 0x00442230
    __int16 ForwardToPlayerMgr(_WORD *p_WORD); // 0x00459F30
    bool RollProbability(float fProb); // 0x00460A00
    int SetItemData(int nCol, int nRow, int nData, int nFlags); // 0x00469D00
    unsigned __int8 fn_469D40(); // 0x00469D40
    void AddItem(void *pData, int nCol, int nRow, int nFlags); // 0x00469D50
    void CreatePanelUI(); // 0x004AA9C0
    void DestroyDynamic(int nVal); // 0x004AB2B0
    char IsActive(); // 0x004DC220
    int UpdatePanel(BOOL bRefresh); // 0x004DC250
    char CountAttackSequences(); // 0x004DC610
    int StepFrame(); // 0x004E04C0
    char ResetAllSlots(); // 0x004E0690
    char UpdateDisplay(); // 0x004E0740
    char UpdateAnimation(); // 0x004E0820
    char UpdateState(); // 0x004E0980
    static int DlgProcEditorMain(CCBUI *a1, HWND hDlg, UINT uMsg, WORD wParam, LPARAM lParam); // 0x004E0A60
    int CloseDialog(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam); // 0x004E10E0
    int DlgProcEffect(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam); // 0x004E1160
    unsigned __int8 * PopulateSceneList(HWND hDlg); // 0x004E16F0
    unsigned __int8 * LoadSceneByIndex(int nVal); // 0x004E1870
    static int CombatDlgProcThunk(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam); // 0x004E1A10
    int SettingsDialogProc(HWND hDlg, unsigned int dwVal, WPARAM pData, LPARAM a5); // 0x004E1F70
    int HandleWindowMessage(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam); // 0x004E2430
    int DlgProcMain(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam); // 0x004E2490
    int CommandEditDialogProc(int *p_DWORD, HWND hDlg, int nVal, int nVal2, int nVal3); // 0x004E24C0
    LRESULT HandleRoleStateDialog(int nVal); // 0x004E2AE0
    char UpdateDebugStatus(); // 0x004E3780
    LRESULT InitUI_4E3A20(); // 0x004E3A20
    void InitUI_4E3D90(); // 0x004E3D90
    LRESULT PopulateCommandList(); // 0x004E4A80
    BOOL CloseCommandDialog(); // 0x004E4D50
    LRESULT ShowCommandDetails(); // 0x004E4D70
    int ApplyCommandEdit(); // 0x004E4F00
    int ShowSkillDetails(); // 0x004E5170
    static LRESULT SendWindowMessage(HWND hWnd, LPARAM lParam); // 0x004E53C0
    static LRESULT FormatCombatBuffer(HWND hWnd, int nVal); // 0x004E53E0
    int StartMagicThread(); // 0x004E5490
    LRESULT _nearby_4ea4a0(void *hDlg, HWND arg4, int a3); // 0x004EA4A0
    static int DlgProcCameraEdit(CCBCamControl *a1, HWND hDlg, UINT uMsg, WORD wParam, LPARAM lParam); // 0x004EA5C0
    char _nearby_4ea6d0(HWND hDlg, int a3); // 0x004EA6D0
    char _nearby_4eac10(HWND hDlg, int a3); // 0x004EAC10
    static INT_PTR _nearby_4eb230(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4); // 0x004EB230
    static int DlgProcCameraConfig(CCBCamControl *a1, HWND hDlg, UINT uMsg, WORD wParam, LPARAM lParam); // 0x004EB260
    int * ctor(int nVal); // 0x005160A0
    virtual void Destroy(); // 0x005164D0
    void InitResultPanels(); // 0x00516940
    char SetupAIWindow(); // 0x00516A30
    void _CCBUI(); // 0x00517650
    void Reset(); // 0x005177B0
    bool CreateCombatPanel(); // 0x00517B30
    bool CreateAttackSequen(); // 0x00517C10
    bool CreateBattleFieldAttr(); // 0x00517C80
    bool CreateControlWindow(); // 0x00517D60
    BOOL CreateItemWindow(); // 0x00517DF0
    bool CreateParaWindow(); // 0x005181E0
    BOOL CreateMagicWindow(); // 0x005183C0
    bool CreateSkillWindow(char pData); // 0x005184C0
    int InitRoleDisplay(int a_128); // 0x005184E0
    bool CreateLineupWindow(int nVal, char pData); // 0x00518AF0
    bool CreateProtectWindow(); // 0x00518B20
    bool CreateResultWindow(char pData); // 0x00518B30
    bool CreateFiveNimbus(char pData); // 0x00518D40
    void HideAll(); // 0x00518E60
    void ShowBattleFieldAttr(int attr); // 0x00518FE0
    void ShowControlWindow(int bShow); // 0x00519080
    void ShowDialogWindow(); // 0x00519200
    void ShowAIWindow(int nRoleIndex); // 0x00519230
    bool IsResultWindowClosed(int nVal, int nVal2, int nVal3, int nVal4, int nVal5, int nVal6, int nVal7, const void *pData); // 0x00519260
    int * ctor(); // 0x00519310
    void Release(); // 0x00519380
    void ClearAttackSequence(); // 0x005193D0
    void CreateImbibeNimbus(int nCount); // 0x00519400
    virtual int OnMessage(int pt, unsigned int area, int nVal); // 0x005195E0
    void SetNimbusToNimbusControl(); // 0x005196C0
    void WriteNimbusToPlayerMgr(); // 0x00519A10
    virtual CCBUI * GetNimbusColor(int nNimbusType); // 0x00519B40
    void Render(); // 0x00519BB0
    char CreateButton(int a2, int a3, int a4, int a5, tagRECT *pRect, int parent); // 0x00519BD0
    virtual void Destroy_9f50(); // 0x00519F50
    virtual BOOL AddResultWindowAni(int nVal, int nVal2); // 0x0051A090
    void ChangeSpecStateLum(); // 0x0051A0F0
    BOOL LineMove(POINT *pStart, POINT *pEnd); // 0x0051A1D0
    unsigned int GravityDown(unsigned int formal); // 0x0051A2B0
    unsigned int ChangeNumTxt(); // 0x0051A340
    virtual void DoTask(); // 0x0051A390
    BOOL AddTask(tagUITask *pTask, int nParam); // 0x0051A430
    virtual int Destroy_a880(); // 0x0051A880
    virtual BOOL CheckMagicKeyPress(int nVal, int nVal2); // 0x0051AB00
    void InitShopUI(); // 0x00525540
    int * InitSkillUI(int nVal); // 0x005257B0
    int Update(int deltatime, int haveinput); // 0x00526740
    void PlayResultSound(); // 0x005273D0
    void UpdateCaptions(); // 0x00527610
};
