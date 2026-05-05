#ifndef PAL3A_EFFMODEL_H
#define PAL3A_EFFMODEL_H

#include "pal3a_types.h"

class CEffModel {
public:
    char _data[104];

    char * GetEditorTaskDescription(int nIndex);
    void SetTimeScale(float fScale);
    void CreateTask(tagEffTaskParam * p);
    void DestroyModel();
    void Destroy();
    ~CEffModel();
    CEffModel();
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    unsigned long ProcCommonTask(ulong dwParam);
    void Render();
    void Update(float fCurTime);
    void Attach();
    bool LoadModel(char * pFileName);
    bool Create(tagEffObjType * pType);
    unsigned long ProcInitTask(ulong dwParam);
};

#endif // PAL3A_EFFMODEL_H
