#ifndef PAL3A_EFFCUSTOMSHAPE_H
#define PAL3A_EFFCUSTOMSHAPE_H

#include "pal3a_types.h"

class CEffCustomShape {
public:
    char _data[172];

    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    bool Create(tagEffObjType * pType);
    ~CEffCustomShape();
    void Destroy();
    CEffCustomShape();
    void Attach();
    void Update(float fCurTime);
    char * GetEditorTaskDescription(int nIndex);
    char * GetEditorObjDescription(int nIndex);
    void Render();
    unsigned long ProcCommonTask(ulong dwParam);
    unsigned long ProcInitTask(ulong dwParam);
    void CreateTask(tagEffTaskParam * p);
};

#endif // PAL3A_EFFCUSTOMSHAPE_H
