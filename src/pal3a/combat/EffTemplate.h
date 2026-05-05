#ifndef PAL3A_EFFTEMPLATE_H
#define PAL3A_EFFTEMPLATE_H

#include "pal3a_types.h"

class CEffTemplate {
public:
    char _data[48];

    unsigned long ProcCommonTask(ulong dwParam);
    void CreateTask(tagEffTaskParam * p);
    bool Create(tagEffObjType * pType);
    void Update(float fCurTime);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    char * GetEditorTaskDescription(int nIndex);
    void Render();
    ~CEffTemplate();
    void Attach();
    void Destroy();
    CEffTemplate();
    unsigned long ProcInitTask(ulong dwParam);
};

#endif // PAL3A_EFFTEMPLATE_H
