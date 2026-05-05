#ifndef PAL3A_EFFBINK_H
#define PAL3A_EFFBINK_H

#include "pal3a_types.h"

class CEffBink {
public:
    char _data[304];

    void Destroy();
    void Attach();
    ~CEffBink();
    unsigned long ProcInitTask(ulong dwParam);
    unsigned long ProcCommonTask(ulong dwParam);
    void Update(float fCurTime);
    bool Create(tagEffObjType * pType);
    void CreateTask(tagEffTaskParam * p);
    char * GetEditorTaskDescription(int nIndex);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    CEffBink();
    void Render();
};

#endif // PAL3A_EFFBINK_H
