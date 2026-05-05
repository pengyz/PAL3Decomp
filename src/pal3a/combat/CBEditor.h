#ifndef PAL3A_CBEDITOR_H
#define PAL3A_CBEDITOR_H

#include "pal3a_types.h"

class CCBEditor {
public:
    char _data[9624];

    int DynBalanceEditorDialogProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void TurnFightInfoToSelectFighter();
    void LoadScene(int nSceneIndex);
    void InitSpecStateCfg();
    int BalanceEditorDialogProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void CheckBalanceEditor();
    void TurnSelectFighterToFightInfo();
    void AddCCT();
    bool IsItemNew(ulong dwItemID, int * nIndex);
    void RefreshEffEditorObjList(HWND * hDlg);
    void SetBalanceEditorRoleList(int nRoleIndex);
    void InitNewItemCfg();
    void SetBalanceEditorMoneyEditor();
    void Reset();
    bool IsCheck(HWND * hWnd);
    void RefreshEffEditorTaskList(HWND * hDlg);
    int EditorDialogProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void Update();
    void GetTextFmt(HWND * hWnd, ulong * pDW, float * pF);
    void CreateSelectFighterBox();
    bool IsOurWindow(HWND * hWnd);
    void ChangeItemValue();
    void SetText(HWND * hWnd, ulong dw);
    void SetText(HWND * hWnd, char * pStr);
    void SetText(HWND * hWnd, int n);
    void SetText(HWND * hWnd, float f);
    void LoadNewItem();
    ~CCBEditor();
    void CloseAllGameDisplay();
    int CamEditorDialogProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void InitCamEditorDlg(HWND * hDlg);
    int GetItemGP(ulong dwItemID);
    void DefaultItem();
    void RefreshEffEditorObjTypeList(HWND * hDlg);
    void CCTValueActive();
    int SelectFighterProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void RefreshLinkEditorLinkerData(HWND * hDlg);
    int GetItemMP(ulong dwItemID);
    int SceneEditorProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void SaveNewItemCfg();
    void FillCCTValue();
    bool Create();
    bool SaveEffObjType(HWND * hDlg, int nEffObjType);
    int GetItemHP(ulong dwItemID);
    void RefreshEffEditorGroupList(HWND * hDlg);
    void RefreshSelectFighterBox();
    int DynSceneEditorProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    bool CheckCCTValue();
    char * GetText(HWND * hWnd);
    float GetTextf(HWND * hWnd);
    int GetTextn(HWND * hWnd);
    void SetCurSelectItem();
    void SaveSpecStateCfg();
    void InitSelectFighterBox();
    int DynEffObjTypeProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void RefreshCCTWindow();
    void RefreshLinkEditorAllTrickList(HWND * hDlg);
    unsigned long GetTextdw(HWND * hWnd);
    bool Destroy();
    void InitEffEditorDlg(HWND * hDlg);
    void RefreshEffEditorObjDescription(HWND * hDlg, int nClassIndex);
    void CheckAIState();
    int FightSkillCfgProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void RemoveItem();
    int LinkEditorDialogProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void AutoDetectRange(HWND * hDlg);
    void InitCBSceneList(HWND * hDlg);
    void UpdateEffEditorTaskData(HWND * hDlg);
    void ActiveRoleData();
    int DynNewItemProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void AddItem();
    void Check(HWND * hWnd, uchar bCheck);
    void SaveNewItem();
    void SetTimeScale(float f);
    void InitFightSkillCfg();
    void CheckCamEditor();
    int DynCamEditorDialogProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    int DynEffEditorDialogProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    int DynLinkEditorDialogProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void SaveFightSkillCfg();
    void CheckSceneEditParam();
    void ActiveRoleLevel();
    int EffObjTypeProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void RefreshEffEditorTaskDescription(HWND * hDlg);
    void InitLinkEditorDlg(HWND * hDlg);
    int EditorBoxProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    int GetInTeamRoleNum();
    unsigned long GetTextCrc(HWND * hWnd);
    int DynEditorBoxProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    CCBEditor(CCBSystem * pCBSystem);
    void RefreshEffEditorTaskData(HWND * hDlg);
    int NewItemProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void LoadEffObjType(HWND * hDlg, int nEffObjType);
    int SpecStateCfgProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void Render();
    void SetRoleDataPanel();
    void UpdateLinkEditorLinkerData(HWND * hDlg);
    int EffEditorDialogProc(HWND * hDlg, uint msg, uint wParam, long lParam);
    void RefreshCCTListWindow();
    void RefreshLinkEditorEffGroupList(HWND * hDlg);
    bool Init();
    void InitBalanceEditorRoleList();
};

bool FILEMODULE(char * filename, uchar isopen);

#endif // PAL3A_CBEDITOR_H
