#ifndef PAL3A_EFFGBPARTICLE_H
#define PAL3A_EFFGBPARTICLE_H

#include "pal3a_types.h"

class CEffgbParticle {
public:
    char _data[80];

    void Destroy();
    void Attach();
    void SetTimeScale(float fTimeScale);
    char * GetEditorTaskDescription(int nIndex);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    void Update(float fCurTime);
    unsigned long ProcCommonTask(ulong dwParam);
    bool Create(tagEffObjType * pType);
    void CreateTask(tagEffTaskParam * p);
    ~CEffgbParticle();
    CEffgbParticle();
    void Render();
    unsigned long ProcInitTask(ulong dwParam);
};

#endif // PAL3A_EFFGBPARTICLE_H
