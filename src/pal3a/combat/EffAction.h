#ifndef PAL3A_EFFACTION_H
#define PAL3A_EFFACTION_H

#include "pal3a_types.h"

class CEffAction {
public:
    char _data[52];

    void Render();
    unsigned long ProcInitTask(ulong dwParam);
    void Update(float fCurTime);
    void PreLoadObjInTask(tagEffTaskParam * p);
    unsigned long ProcCommonTask(ulong dwParam);
    void CreateTask(tagEffTaskParam * p);
    bool Create(tagEffObjType * pType);
    ~CEffAction();
    char * GetEditorTaskDescription(int nIndex);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    void Destroy();
    CEffAction();
    void Attach();
};

#endif // PAL3A_EFFACTION_H
