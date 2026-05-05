#ifndef PAL3A_CBUI_H
#define PAL3A_CBUI_H

#include "pal3a_types.h"

class CCBAIWindow {
public:
    char _data[128];

    ~CCBAIWindow();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    CCBAIWindow();
    bool Create(tagRECT * rc, UIWnd * pFather);
    void ShowWindow(int show);
    void Reset();
    void Destroy();
    int Update(float deltatime, int haveinput);
};

class CCBControlWindow {
public:
    char _data[116];

    bool Create(tagRECT * rc, UIWnd * pFather);
    int Update(float deltatime, int haveinput);
    void HandleInput();
    void HandleEnable(int dir, int n);
    bool CreateButton(UIButton * * ppButton, uint id, tagRECT * rc, char * picname);
    void CreateButtons();
    void DefaultKey();
    ~CCBControlWindow();
    void MoveButtons();
    void KeyPressed();
    void Destroy();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    bool CanHandleMiddle();
    CCBControlWindow();
    void CheckKeyInput(int dir);
    void Reset();
};

class CCBFiveNimbusWindow {
public:
    char _data[160];

    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void ConsumeAllNimbus();
    CCBFiveNimbusWindow();
    void CheckNimbusState();
    ~CCBFiveNimbusWindow();
    void SetNimbusCtrlState(ECBFiveNimbus eNim, int iState);
    void DisableCtrl();
    void SetNimbusStep(int nNimbusStep);
    void SetNimbus(ECBFiveNimbus nimbus, int nimbusnum);
    void UpdateFNOpenWindow(float deltatime);
    int Update(float deltatime, int haveinput);
    void ConsumeNimbus(ECBFiveNimbus nimbus);
    void Destroy();
    void Reset();
    void ShowWindow(int show);
    int GetChangeRound();
    bool Create(tagRECT * rc, UIWnd * pFather);
    bool Init();
};

class CCBItemWindow {
public:
    char _data[108];

    int Update(float deltatime, int haveinput);
    void Reset();
    ~CCBItemWindow();
    bool CreateButton(UIPushButton * * ppButton, uint id, tagRECT * rc, char * picname);
    CCBItemWindow();
    bool Create(tagRECT * rc, UIWnd * pFather);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void SetActivePage(int n);
    void HandleInput();
    void Destroy();
    void CreateButtons();
};

class CCBLineupWindow {
public:
    char _data[124];

    int Update(float deltatime, int haveinput);
    ~CCBLineupWindow();
    void SetSelected(int nSelected);
    void Destroy();
    void Reset();
    int IsPtOnInitPos(tagPOINT pt);
    bool IsPtOnInitPos(int nPosIndex, tagPOINT pt);
    void ShowWindow(int show);
    bool Create(tagRECT * rc, UIWnd * pFather);
    void RefreshFacePos();
    int SetFaceLineup(int nFaceIndex, int nPosIndex);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    CCBLineupWindow();
    int IsFaceOnInitPos(int nFaceIndex);
    bool IsFaceOnInitPos(int nPosIndex, int nFaceIndex, int * nArea);
    void Render();
    int IsPtOnFace(tagPOINT pt);
    bool IsPtOnFace(int nFaceIndex, tagPOINT pt);
};

class CCBMagicWindow {
public:
    char _data[128];

    void Destroy();
    ~CCBMagicWindow();
    bool CreateButton(UIPushButton * * ppButton, uint id, tagRECT * rc, char * picname);
    void CreateButtons();
    void ForbidPage(ECBBattleFieldAttr eBFA);
    int Update(float deltatime, int haveinput);
    bool Create(tagRECT * rc, UIWnd * pFather);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    CCBMagicWindow();
    void HandleInput();
    void SetActivePage(int n);
    int GetActivePage();
    void Reset();
};

class CCBParabolaWindow {
public:
    char _data[84];

    CCBParabolaWindow();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void Destroy();
    ~CCBParabolaWindow();
    void Reset();
    int Update(float deltatime, int haveinput);
    bool Create(tagRECT * rc, UIWnd * pFather);
};

class CCBProtectWindow {
public:
    char _data[96];

    void Reset();
    void Destroy();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void ShowWindow(int show);
    ~CCBProtectWindow();
    CCBProtectWindow();
    bool Create(tagRECT * rc, UIWnd * pFather);
    int Update(float deltatime, int haveinput);
};

class CCBResultWindow {
public:
    char _data[180];

    int OnMessage(uint msg, ulong wparam, ulong lparam);
    ~CCBResultWindow();
    void Render();
    int Update(float deltatime, int haveinput);
    CCBResultWindow();
    void Destroy();
    void Reset();
    void ShowWindow(int show);
    bool Create(tagRECT * rc, UIWnd * pFather);
};

class CCBSkillWindow {
public:
    char _data[84];

    void Reset();
    ~CCBSkillWindow();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    bool Create(tagRECT * rc, UIWnd * pFather);
    int Update(float deltatime, int haveinput);
    CCBSkillWindow();
    void Destroy();
};

class CCBUI {
public:
    char _data[3552];

    tagRECT GetNimbusArea(tagRECT * __$ReturnUdt);
    bool CreateItemWindow();
    bool CreateMagicWindow();
    bool CreateAttackSequen();
    CCBUI(CCBSystem * pCBSystem);
    bool CreateBattleFieldAttr();
    void ClearFinishedTask();
    void Render();
    bool CreateStageControl();
    void ChangeSpecStateLum();
    gbColorQuad GetNimbusColor(gbColorQuad * __$ReturnUdt);
    unsigned long LineMove(ulong __formal);
    void ShowRoleStatePanel(uchar bVisible);
    bool Init();
    ~CCBUI();
    bool CreateLineupWindow();
    bool CreateObj();
    void AddResultWindowAni();
    bool CheckNimbusMove(tagPOINT pt, tagRECT area);
    void ShowControlWindow(uchar bShow);
    void ShowLineupWindow(uchar bVisible);
    void ShowBattleFieldAttr(ECBBattleFieldAttr attr, ECBForce force);
    void Destroy();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    unsigned long GravityDown(ulong __formal);
    bool AddTask(void * fp, ulong dwTaskID, float fExpectStartTime, float fExpectEndTime, tagUIParam * pParam);
    void SetNimbusToNimbusControl();
    bool CreateProtectWindow();
    void WriteNimbusToPlayerMgr();
    void ShowProtectWindow(uchar bVisible);
    void DoTask();
    bool CreateResultWindow();
    void ShowDialogWindow(uchar bVisible);
    bool Create();
    void ConfigImbibeNimbus(int index, ECBFiveNimbus nimbustype, tagPOINT pos, float accelerate);
    bool CreateControlWindow();
    bool CreateResultItem();
    void HideAll();
    bool CreateButton(UIButton * * ppButton, uint id, tagRECT * rc, char * picname);
    bool IsResultWindowClosed();
    bool DelTask(int nIndex);
    void ShowAIWindow(int nRoleIndex, uchar bVisible);
    bool CreateParaWindow();
    bool CreateRoleStatePanel();
    void ShowResultWindow(uchar bVisible);
    unsigned long ChangeNumTxt(ulong __formal);
    int Update(float deltatime, int haveinput);
    bool IsImbibeNimbusNotFinish();
    void DeleteUIObj(UIWnd * pUIWnd);
    void AddRightControlButtonAni();
    void Reset();
    bool CreateSkillWindow();
    bool CreateFiveNimbus();
    void CreateImbibeNimbus(int iNum);
    bool CreateAIWindow();
    bool CreateCombatPanel();
};

bool CreateObj(UIButtonEX * * ppObj);
bool CreateObj(UIProgressBar * * ppObj);
bool CreateObj(UIButton * * ppObj);
bool CreateObj(UIPushButton * * ppObj);
bool CreateObj(UIStatic * * ppObj);

#endif // PAL3A_CBUI_H
