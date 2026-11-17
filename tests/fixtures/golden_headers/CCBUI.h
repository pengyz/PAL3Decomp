class UIWnd;

class tagRECT;

#pragma once
// Auto-generated: CCBUI
#include "pal3/ida_types.h"

#include "Misc/CCBUI_funcptr_t.h"
#include "UI/UIListBox.h"
#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbengine_types.h"
#include "Misc/tagUITask.h"

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
class UIWnd;

class CCBUI : public UIListBox {
public:
    UIStatic * m_pAttackSequenBack; // +0x48
    UIStatic * pPanel; // +0x4C
    UIStatic * m_pBattleFieldAttr[6]; // +0x50
    UIStatic * m_pAttackSequenFace[11]; // +0x68
    UIStatic * m_pRoleStatePanel[4]; // +0x94
    UIStatic * m_pRoleStateFace[5]; // +0xA4
    UIStatic * m_pRoleStateFaceName[5]; // +0xB8
    UIStatic * m_pRoleStateAttackInc[11]; // +0xCC
    UIStatic * m_pRoleStateAttackDec[11]; // +0xF8
    UIStatic * m_pRoleStateDefenceInc[11]; // +0x124
    UIStatic * m_pRoleStateDefenceDec[11]; // +0x150
    UIStatic * m_pRoleStateLuckInc[11]; // +0x17C
    UIStatic * m_pRoleStateLuckDec[11]; // +0x1A8
    UIStatic * m_pRoleStateSpeedInc[11]; // +0x1D4
    UIStatic * m_pRoleStateSpeedDec[11]; // +0x200
    UIStatic * m_pRoleStateStable[11]; // +0x22C
    UIStatic * m_pRoleStateBlank[11]; // +0x258
    UIStatic * m_pRoleStateForbid[11]; // +0x284
    UIStatic * m_pRoleStateSleep[11]; // +0x2B0
    UIStatic * m_pRoleStateChaos[11]; // +0x2DC
    UIStatic * m_pRoleStateMad[11]; // +0x308
    UIStatic * m_pRoleStateMirror[11]; // +0x334
    UIStatic * m_pRoleStateWall[11]; // +0x360
    UIStatic * m_pRoleStateBound[11]; // +0x38C
    UIStatic * m_pRoleStateHermit[11]; // +0x3B8
    UIStatic * m_pRoleStateImmunity[11]; // +0x3E4
    UIStatic * m_pWinPanel; // +0x410
    UIStatic * m_pLosePanel; // +0x414
    UIProgressBar * m_pRoleStateHP[4]; // +0x418
    UIProgressBar * m_pRoleStateGP[4]; // +0x428
    UIProgressBar * m_pRoleStateMP[4]; // +0x438
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
    CCBFiveNimbusWindow * m_pFiveNimbusWindow; // +0x4A8
    CCBSystem * m_pCBSystem; // +0x4AC
    CUtil * m_pUtil; // +0x4B0
    char _gap_4B4[4]; // +0x4B4
    tagUITask m_Task[19]; // +0x4B8
    char _gap_A10[32]; // +0xA10
    CCBUI_funcptr_t fp; // +0xA30
    char _tail_A40[24]; // +0xA40
    // total size: 0xA58 (2648)

    virtual ~CCBUI() {}

    virtual void ShowClipped(int nVal); // slot0 0x00445e70
    virtual void Render(); // slot1 0x0043ddf0
    virtual BOOL Update(CCBUI **deltatime); // slot2 0x00519660
    virtual void HideAll(); // slot3 0x00519510
    virtual int Create(int id, tagRECT *, UIWnd * parent); // slot4 0x00445b90
    virtual int OnMessage(int a2, unsigned int nVal, int nVal2); // slot6 0x005195e0

    void SetTooltip(const char *szText); // 0x00441040
    void SetRect(RECT *pRect); // 0x00441070
    int ShowEffect(int nY, int nWidth, int nHeight); // 0x00441380
    gbVFileSystem * LoadTextureSequence(gbVFileSystem *pPath, char bUseAtlas); // 0x004413c0
    int VirtualCall(int nVal1); // 0x004420b0
    void SetTargetPos(gbVec3D *pPos, gbVec3D *pDir); // 0x00442170
    void SetCurPlayer(int nPlayer); // 0x004421f0
    int SetRoleStatePointers(int nVal); // 0x00442200
    int SetSelection(int nItemIndex); // 0x00442230
    __int16 ForwardToPlayerMgr(_WORD *p_WORD); // 0x00459f30
    bool RollProbability(float fProb); // 0x00460a00
    int SetItemData(int nCol, int nRow, int nData, int nFlags); // 0x00469d00
    unsigned __int8 IsAddMode(); // 0x00469d40
    void CreatePanelUI(); // 0x004aa9c0
    void DestroyDynamic(int nVal); // 0x004ab2b0
    char IsActive(); // 0x004dc220
    char CountAttackSequences(); // 0x004dc610
    int StepFrame(); // 0x004e04c0
    char ResetAllSlots(); // 0x004e0690
    char UpdateDisplay(); // 0x004e0740
    char UpdateAnimation(); // 0x004e0820
    char UpdateState(); // 0x004e0980
    static int DlgProcEditorMain(CCBUI *a1, HWND hDlg, UINT uMsg, WORD wParam, LPARAM lParam); // 0x004e0a60
    int DlgProcEffect(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam); // 0x004e1160
    unsigned __int8 * PopulateSceneList(HWND hDlg); // 0x004e16f0
    unsigned __int8 * LoadSceneByIndex(int nVal); // 0x004e1870
    static int CombatDlgProcThunk(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam); // 0x004e1a10
    static int SettingsDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam); // 0x004e1f70
    static int HandleWindowMessage(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam); // 0x004e2430
    int DlgProcMain(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam); // 0x004e2490
    int CommandEditDialogProc(int *p_DWORD, HWND hDlg, int nVal, int nVal2, int nVal3); // 0x004e24c0
    LRESULT HandleRoleStateDialog(int nVal); // 0x004e2ae0
    char UpdateDebugStatus(); // 0x004e3780
    LRESULT InitUI(); // 0x004e3a20
    void InitUI_4E3D90(); // 0x004e3d90
    LRESULT PopulateCommandList(); // 0x004e4a80
    BOOL CloseCommandDialog(); // 0x004e4d50
    LRESULT ShowCommandDetails(); // 0x004e4d70
    int ApplyCommandEdit(); // 0x004e4f00
    int ShowSkillDetails(); // 0x004e5170
    static LRESULT SendWindowMessage(HWND hWnd, LPARAM lParam); // 0x004e53c0
    static LRESULT FormatCombatBuffer(HWND hWnd, int nVal); // 0x004e53e0
    int StartMagicThread(); // 0x004e5490
    LRESULT DlgProcEditor(HWND hDlg, int a3); // 0x004ea4a0
    static int DlgProcCameraEdit(CCBCamControl *a1, HWND hDlg, UINT uMsg, WORD wParam, LPARAM lParam); // 0x004ea5c0
    char DlgProcEffect_a6d0(HWND hDlg, int a3); // 0x004ea6d0
    char DlgProcInput(HWND hDlg, int a3); // 0x004eac10
    static INT_PTR DlgProcCameraConfigWrapper(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4); // 0x004eb230
    static int DlgProcCameraConfig(CCBCamControl *a1, HWND hDlg, UINT uMsg, WORD wParam, LPARAM lParam); // 0x004eb260
    void Method(int nVal); // 0x005160a0
    void InitResultPanels(); // 0x00516940
    char SetupAIWindow(); // 0x00516a30
    void Reset(); // 0x005177b0
    bool CreateCombatPanel(); // 0x00517b30
    bool CreateAttackSequen(); // 0x00517c10
    bool CreateBattleFieldAttr(); // 0x00517c80
    bool CreateControlWindow(); // 0x00517d60
    BOOL CreateItemWindow(); // 0x00517df0
    bool CreateParaWindow(); // 0x005181e0
    BOOL CreateMagicWindow(); // 0x005183c0
    bool CreateSkillWindow(char pData); // 0x005184c0
    int InitRoleDisplay(int a_128); // 0x005184e0
    bool CreateLineupWindow(int nVal, char pData); // 0x00518af0
    bool CreateProtectWindow(); // 0x00518b20
    bool CreateResultWindow(char pData); // 0x00518b30
    bool CreateFiveNimbus(char pData); // 0x00518d40
    int UpdateAnims(); // 0x00518e60
    void ShowBattleFieldAttr(int attr); // 0x00518fe0
    void ShowControlWindow(int bShow); // 0x00519080
    void ShowDialogWindow(); // 0x00519200
    void ShowAIWindow(int nRoleIndex); // 0x00519230
    bool IsResultWindowClosed(int nVal, int nVal2, int nVal3, int nVal4, int nVal5, int nVal6, int nVal7, const void *pData); // 0x00519260
    CCBUI(); // 0x00519310
    void Release(); // 0x00519380
    void ClearAttackSequence(); // 0x005193d0
    void CreateImbibeNimbus(int nCount); // 0x00519400
    void SetNimbusToNimbusControl(); // 0x005196c0
    void WriteNimbusToPlayerMgr(); // 0x00519a10
    bool CreateButton(int parent, int id, int rc, int picname, UIButton **a5); // 0x00519bd0
    void ChangeSpecStateLum(); // 0x0051a0f0
    BOOL LineMove(POINT *pStart, POINT *pEnd); // 0x0051a1d0
    unsigned int GravityDown(unsigned int formal); // 0x0051a2b0
    unsigned int ChangeNumTxt(); // 0x0051a340
    BOOL AddTask(tagUITask *pTask, int nParam); // 0x0051a430
    UIWnd * CreateButtons(CCBItemWindow *Block, char pData); // 0x0051b670
    void _CCBParabolaWindow(); // 0x0051b810
    void Update_B8C0(); // 0x0051b8c0
    void DestroyUIResources(); // 0x0051b920
    void ForwardShowClipped(int nFlags); // 0x0051b940
    void _todo_51B9C0(); // 0x0051b9c0
    void _todo_51BA40(); // 0x0051ba40
    void _todo_51BAC0(); // 0x0051bac0
    void InitShopUI(); // 0x00525540
    int * InitSkillUI(int nVal); // 0x005257b0
    void CCBUI_Render(); // 0x00526660
    int UpdateStatics(int deltatime, int haveinput); // 0x00526740
    void PlayResultSound(); // 0x005273d0
    void UpdateCaptions(); // 0x00527610
};
