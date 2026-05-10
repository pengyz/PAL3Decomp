#pragma once
// Auto-generated: CCBUI

#include "UIFrameWnd.h"
#include "tagUITask.h"

class CCBAIWindow;
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
class UIProgressBar;
class UIStatic;
class UIStaticCB;
class tagImbibeNimbus;

class CCBUI : public UIFrameWnd {
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
    tagUITask m_Task[32]; // +0x4B8
    unsigned char m_bShowResult; // +0xDB8
    void * * m_fp; // +0xDC0
    int m_nTask; // +0xDD0
    int m_nCurTask; // +0xDD4
    int mImbibeNimbusNum; // +0xDD8
    tagImbibeNimbus * m_pImbibeNimbus; // +0xDDC
    // total size: 0xDE0 (3552)

    int GetState(); // 0x004DC560
    int SetParam(int a2, int a3); // 0x004DC5C0
    int Update(); // 0x004E04C0
    char UpdateInput(); // 0x004E0690
    char UpdateDisplay(); // 0x004E0740
    char UpdateAnimation(); // 0x004E0820
    char UpdateState(); // 0x004E0980
    ~CCBUI(); // 0x00517650
    char Reset(); // 0x005177B0
    char CreateCombatPanel(); // 0x00517B30
    char CreateAttackSequen(); // 0x00517C10
    char CreateBattleFieldAttr(); // 0x00517C80
    char CreateControlWindow(); // 0x00517D60
    char CreateItemWindow(); // 0x00517DF0
    char CreateParaWindow(); // 0x005181E0
    // [IDA_COMPLEX_RET] original: int (__thiscall ***__thiscall(_DWORD *this))(_DWORD, _DWORD)
    int ( CreateMagicWindow(_DWORD); // 0x005183C0
    int CreateSkillWindow(char a2); // 0x005184C0
    int CreateLineupWindow(int a2, char a3); // 0x00518AF0
    char CreateProtectWindow(); // 0x00518B20
    char CreateResultWindow(char a2); // 0x00518B30
    int CreateFiveNimbus(char a2); // 0x00518D40
    int HideAll(); // 0x00518E60
    int ShowBattleFieldAttr(int a2); // 0x00518FE0
    int ShowControlWindow(int a2); // 0x00519080
    int ShowDialogWindow(); // 0x00519200
    char ShowAIWindow(int a2); // 0x00519230
    char IsResultWindowClosed(int a2, int a3, int a4, int a5, int a6, int a7, int a8, const void *a9); // 0x00519260
    UIWnd * ShowLineupWindow(CCBUI *Block, char a2); // 0x00519360
    int OnMessage(); // 0x005193D0
    char CreateImbibeNimbus(_DWORD *pRect, int parent); // 0x00519400
    int ConfigImbibeNimbus(); // 0x00519510
    int CheckNimbusMove(int a2, unsigned int a3, int a4); // 0x005195E0
    BOOL IsImbibeNimbusNotFinish(int a2, int a3); // 0x00519660
    struct gbVFileSystem * SetNimbusToNimbusControl(); // 0x005196C0
    char WriteNimbusToPlayerMgr(_DWORD *a2, int a3, int a4, int a5); // 0x00519A10
    UIWnd * GetNimbusColor(CCBUI *Block, char a2); // 0x00519B40
    int Render(); // 0x00519BB0
    // [IDA_USERPURGE] CreateButton; // 0x00519BD0
    int DeleteUIObj(); // 0x00519F50
    int AddRightControlButtonAni(int a2, unsigned int a3, int a4); // 0x00519FE0
    BOOL AddResultWindowAni(int a2, int a3); // 0x0051A090
    int ChangeSpecStateLum(); // 0x0051A0F0
    char LineMove(_DWORD *a2, int a3, int a4, int a5); // 0x0051A1D0
    int GravityDown(int a2); // 0x0051A2B0
    _DWORD * ChangeNumTxt(); // 0x0051A340
    UIWnd * DoTask(CCBUI *Block, char a2); // 0x0051A390
    char AddTask(_DWORD *a2, int a3); // 0x0051A430
};
