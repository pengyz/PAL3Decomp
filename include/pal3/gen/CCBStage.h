#pragma once
// Auto-generated: CCBStage

#include "tagStageTask.h"

class Actor;
class CCBCamControl;
class CCBDisplayChain;
class CCBEditor;
class CCBRoleState;
class CCBStageCam;
class CCBStageEffect;
class CCBStageRole;
class CCBStageScene;
class CCBStageShadow;
class CCBSystem;

class CCBStage {
public:
    CCBSystem * m_pCBSystem; // +0x0
    CCBRoleState * m_pRoleState; // +0x4
    CCBEditor * m_pEditor; // +0x8
    CCBStageCam * m_pCam; // +0xC
    CCBCamControl * m_pCamControl; // +0x10
    CCBStageScene * m_pScene; // +0x14
    CCBStageRole * m_pRole[11]; // +0x18
    Actor * m_TempStorageNGH; // +0x44
    Actor * m_NGHVariance; // +0x48
    Actor * m_TempStorageWPX; // +0x4C
    Actor * m_WPXVariance; // +0x50
    CCBDisplayChain * m_pDisplayChain; // +0x54
    CCBStageShadow * m_pShadow; // +0x58
    CCBStageEffect * m_pEffect; // +0x5C
    int m_BFARole; // +0x60
    int m_BFARound; // +0x64
    tagPOINT m_ptMousePos; // +0x68
    int m_nSelectedRole; // +0x70
    unsigned char m_bRoleSelected[11]; // +0x74
    unsigned char m_bHideSceneAndRole; // +0x7F
    float m_fDamageNumPosY[11]; // +0x80
    float m_fMusicVolume; // +0xAC
    unsigned char m_bPaused; // +0xB0
    int m_nTask; // +0xB4
    int m_nCurTask; // +0xB8
    int m_nCurSubTask; // +0xBC
    tagStageTask m_Task[256]; // +0xC0
    unsigned long m_dwAniFlagOver; // +0xA48C0
    // total size: 0xA48C8 (673992)

    int InitRound(); // 0x004DFAA0
    int EndRound(); // 0x004DFED0
    char Reset(); // 0x004FBA70
    char Create(); // 0x004FBE50
    char Destroy(); // 0x004FBF90
    int Update(); // 0x004FC0A0
    int EditorUpdate(); // 0x004FC3A0
    void Render(); // 0x004FC6F0
    int GetRoleIndex(int a2, const void *a3, char a4); // 0x004FC700
    int GetRoleName(int a2, int a3, int a4, int a5, int a6, _DWORD *a7, int a8, int a9); // 0x004FC7D0
    char Procced(int a2); // 0x004FC8B0
    int IsDoTask(int a2); // 0x004FC980
    int EndTask(int a2); // 0x004FC9A0
    char * DelTask(int a2, _BYTE *a3, _DWORD *a4); // 0x004FC9C0
    char ForceDelTask(int a2); // 0x004FCA00
    void GetTask(); // 0x004FCA80
    char GetTaskID(int a2, int a3); // 0x004FCBD0
    char GetTaskState(int a2); // 0x004FCC10
    int IsTaskFinished(int a2); // 0x004FCD00
    // [IDA_USERPURGE] IsTaskValidButNotFinish; // 0x004FCD50
    int IsTaskExist(int a2); // 0x004FCDA0
    int DoTask(int a2); // 0x004FCDE0
    int StartSubTask(int a2); // 0x004FCE00
    int IsSubTaskFinished(int a2); // 0x004FCE70
    int IsAllSubTaskFinished(int a2); // 0x004FCFB0
    int IsTaskValid(int a2); // 0x004FD0B0
    int IsSubTaskValid(int a2); // 0x004FD1A0
    int IsIdle(int a2); // 0x004FD290
    int HasNormalAttackRole(int _24); // 0x004FD3D0
    int ClearRoleAllTask(int a2); // 0x004FD880
    int EndRoleAllTask(int a2); // 0x004FDA10
    int GetRoleTaskNum(int a2); // 0x004FDB10
    int SelectRole(int a2); // 0x004FDD90
    int ProcWait(int a2); // 0x004FDFC0
    int ProcShowFiveLineup(int a2); // 0x004FE290
    int ProcShowEnemyFiveLineup(); // 0x004FE540
    int ProcFiveLienupFadeIn(int a2); // 0x004FE550
    int ProcFiveLienupFadeOut(int a2); // 0x004FE600
    int ProcShowSneakAttackState(int _74); // 0x004FE660
    int HandleKeyCtrl(int a2); // 0x004FECE0
    int HandleKeyFriend(int a2); // 0x004FEE60
    int ProcShowName(int a2); // 0x004FEFB0
    int ProcShowItemName(int a2); // 0x004FF1B0
    int ProcShowDamage(int a2); // 0x004FF3D0
    int ProcShowCost(int a2); // 0x004FF5C0
    int ProcShowCombatDialog(int a2); // 0x004FF740
    int ProcGrabStageRole(int a2); // 0x004FF840
    int ResetAll(); // 0x00503020
    int UpdatePhysics(); // 0x00503CF0
    char ProcessTurn(); // 0x005045B0
    int CheckAllDone(); // 0x0050D440
    int ProcessCommand(); // 0x0050E0D0
};
