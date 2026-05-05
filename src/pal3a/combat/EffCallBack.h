#ifndef PAL3A_EFFCALLBACK_H
#define PAL3A_EFFCALLBACK_H

#include "pal3a_types.h"

class CEffCallBack {
public:
    char _data[64];

    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    char * GetEditorTaskDescription(int nIndex);
    void Render();
    ~CEffCallBack();
    unsigned long ProcCommonTask(ulong dwParam);
    void Update(float fCurTime);
    bool Create(tagEffObjType * pType);
    void CreateTask(tagEffTaskParam * p);
    unsigned long ProcInitTask(ulong dwParam);
    void PreLoadObjInTask(tagEffTaskParam * p);
    void Attach();
    CEffCallBack();
    void Destroy();
};

#endif // PAL3A_EFFCALLBACK_H
