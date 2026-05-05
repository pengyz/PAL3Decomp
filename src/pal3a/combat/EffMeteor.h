#ifndef PAL3A_EFFMETEOR_H
#define PAL3A_EFFMETEOR_H

#include "pal3a_types.h"

class CEffMeteor {
public:
    char _data[4304];

    void CreateTask(tagEffTaskParam * p);
    void CreateGeom();
    void UpdateMeteor(float fDeltaTime, float fTime);
    bool Create(tagEffObjType * pType);
    char * GetEditorObjDescription(int nIndex);
    void Update(float fCurTime);
    unsigned long ProcCommonTask(ulong dwParam);
    void Render();
    void LoadTexture(char * pFileName);
    unsigned long ProcInitTask(ulong dwParam);
    void Attach();
    void Destroy();
    char * GetEditorTaskDescription(int nIndex);
    ~CEffMeteor();
    CEffMeteor();
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    void InitDefaultUVSet(int nFramePerRow, int nFramePerCol);
    void StartMeteor();
};

class CMeteorChain {
public:
    char _data[56];

    void AddNewNode(gbVec3D * pVec, float fCurTime);
    ~CMeteorChain();
    bool Create(CEffMgr * pEM, int nNumOfNode, uchar bTexture, gbTextureArray * t);
    void Update(float fCurTime);
    CMeteorChain();
    void GetFirstNodePos(gbVec3D * vecPos);
    void ClearAllNode();
    void Render();
};

#endif // PAL3A_EFFMETEOR_H
