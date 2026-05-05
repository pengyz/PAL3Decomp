#ifndef PAL3A_EFFMGR_H
#define PAL3A_EFFMGR_H

#include "pal3a_types.h"

class CEffMgr {
public:
    char _data[43312];

    bool LoadAllEffParam();
    bool Init();
    void StopRunningGroup(ulong dwRunningID);
    unsigned long RunEffGroup(int nGroup, float fx, float fy, float fz, ulong dwID);
    CEffMgr(gbGfxManager * pDisplay, gbCamera * pCam, CCBSystem * pCBSystem);
    ~CEffMgr();
    bool RegAllEff();
    void DelObjTask(int nGroup, int nObj, int nTask);
    void Attach();
    bool IsAllEffGroupStop();
    int GetEffClassIndex(ulong dwClassCRC);
    void DelAllIdleObj();
    void SetTimeScale(float fScale);
    bool SetEffObjTypeAtt(tagEffObjType * pType, int nEffObjTypeIndex);
    void StopAllEffGroup();
    bool IsEffGroupRunning(ulong dwRunningID);
    void DelObjType(int nType);
    void Update(float fCurTime);
    void DelObjInGroup(int nGroup, int nObj);
    void DelAllCreatedObj();
    bool SaveAllEffParam();
    unsigned long PreLoadEffGroup(int nGroup);
    void Render();
    void CopyObjType(int nType);
    int CreateEff(ulong dwTypeCRC, ulong dwRunID, float fx, float fy, float fz);
    int CreateEff(char * szEffTypeName, ulong dwRunID, float fx, float fy, float fz);
    int GetEffObjTypeIndex(ulong dwTypeCRC);
    void SwapObjInGroup(int nGroup, int nObj1, int nObj2);
    void CopyObjInGroup(int nGroup, int nObj, int nObjType);
};

#endif // PAL3A_EFFMGR_H
