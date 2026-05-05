#ifndef PAL3A_EFFTIME_H
#define PAL3A_EFFTIME_H

#include "pal3a_types.h"

class CEffTime {
public:
    char _data[48];

    void Render();
    char * GetEditorTaskDescription(int nIndex);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    void Update(float fCurTime);
    void CreateTask(tagEffTaskParam * p);
    bool Create(tagEffObjType * pType);
    unsigned long ProcCommonTask(ulong dwParam);
    unsigned long ProcInitTask(ulong dwParam);
    void Destroy();
    void Attach();
    CEffTime();
    ~CEffTime();
};

#endif // PAL3A_EFFTIME_H
