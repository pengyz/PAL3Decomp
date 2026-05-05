#ifndef PAL3A_EFFSPARTICAL_H
#define PAL3A_EFFSPARTICAL_H

#include "pal3a_types.h"

class CEffSParticle {
public:
    char _data[100];

    void Render();
    unsigned long ProcCommonTask(ulong dwParam);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    ~CEffSParticle();
    void CreateTask(tagEffTaskParam * p);
    void SetTimeScale(float fTimeScale);
    char * GetEditorTaskDescription(int nIndex);
    void Destroy();
    unsigned long ProcInitTask(ulong dwParam);
    bool Create(tagEffObjType * pType);
    void Update(float fCurTime);
    CEffSParticle();
    void Attach();
};

#endif // PAL3A_EFFSPARTICAL_H
