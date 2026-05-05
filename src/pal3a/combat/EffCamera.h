#ifndef PAL3A_EFFCAMERA_H
#define PAL3A_EFFCAMERA_H

#include "pal3a_types.h"

class CEffCamera {
public:
    char _data[48];

    void Render();
    unsigned long ProcInitTask(ulong dwParam);
    ~CEffCamera();
    void CreateTask(tagEffTaskParam * p);
    bool Create(tagEffObjType * pType);
    void Update(float fCurTime);
    unsigned long ProcCommonTask(ulong dwParam);
    char * GetEditorTaskDescription(int nIndex);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    CEffCamera();
    void Attach();
    void Destroy();
};

#endif // PAL3A_EFFCAMERA_H
