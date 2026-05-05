#ifndef PAL3A_CBSTAGECAM_H
#define PAL3A_CBSTAGECAM_H

#include "pal3a_types.h"

class CCBCamControl {
public:
    char _data[430256];

    void DoCircleMoveSpeedUnknow();
    void KeepCurCam(tagCam * pCam);
    void ShowCircleSet();
    void Update();
    ~CCBCamControl();
    void Reset();
    void DoLineMove();
    bool Create();
    CCBCamControl(CCBStage * pStage, CCBStageCam * pCam);
    bool StartList(int nListIndex, int nTaskIndex);
    bool StartList(int nListIndex);
    void DoCircleMoveTargetUnknow();
    void StopList();
    void SetCircle(gbVec3D * pvecCenter, gbVec3D * pvecEnd);
    void ResetListFlag(int nListIndex);
    void HandleInput();
    void UpdateCircleSet();
    bool Destroy();
    void DoLineMoveTargetUnknow();
    void DoLineMoveTimeUnknow();
    void DoList();
    void DoCircleMoveTimeUnknow();
    bool LoadPointer();
    void DoCircleMove();
    void DoMechanicsMove();
    bool IsPointerUnderMouse(gbVec3D * pvecPointerPos);
    bool Init();
    void DoLineMoveSpeedUnknow();
};

class CCBStageCam {
public:
    char _data[6272];

    int AddCurCamToEditor();
    void SaveEditorCam();
    void DelEditorCam(int nCamIndex);
    void ClearFinishedTask();
    unsigned long ProcCamMove(ulong __formal);
    bool DelTask(int nIndex);
    ~CCBStageCam();
    void SetCamPos(tagCam * pCamParam);
    CCBStageCam(CCBStage * pStage, gbGfxManager * pGfxMgr);
    bool SwitchEditorCamPos(int nStartPos, int nEndPos, float fExpectTime);
    void DoTask();
    void SetCamPosToEditor(int nParamIndex);
    void LoadEditorCam();
    bool Create();
    bool Init();
    void Update();
    bool IsCamValid(tagCam * pCam);
    bool Destroy();
    bool IsEditorCamValid(int nCamIndex);
    void Reset();
    bool AddTask(void * fp, ulong dwTaskID, float fExpectTime, tagCam * pStartPos, tagCam * pEndPos);
};

class CCCTData {
public:
    char _data[430000];

    bool IsTaskValid(int nTaskIndex, int nListIndex);
    void Reset();
    bool Save();
    bool SwapTask(int nListIndex, int nTaskIndex1, int nTaskIndex2);
    bool DelTaskInList(int nListIndex, int nTaskIndex);
    bool Destroy();
    bool Init();
    bool Load();
    int GetTaskNumInList(int nListIndex);
    bool AddTaskToList(int nListIndex, tagCCT * pCCT);
    ~CCCTData();
    bool ClearList(int nListIndex);
    CCCTData();
    bool InsertTaskToList(int nListIndex, int nTaskIndex, tagCCT * pCCT);
    bool Create();
    int GetFreeSpaceInPool();
};

#endif // PAL3A_CBSTAGECAM_H
