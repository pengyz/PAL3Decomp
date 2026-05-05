#ifndef PAL3A_EFFQUAKE_H
#define PAL3A_EFFQUAKE_H

#include "pal3a_types.h"

class CEffQuake {
public:
    char _data[48];

    unsigned long ProcCommonTask(ulong dwParam);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    void Render();
    CEffQuake();
    ~CEffQuake();
    char * GetEditorTaskDescription(int nIndex);
    void CreateTask(tagEffTaskParam * p);
    void Destroy();
    unsigned long ProcInitTask(ulong dwParam);
    bool Create(tagEffObjType * pType);
    void Update(float fCurTime);
    void Attach();
};

#endif // PAL3A_EFFQUAKE_H
