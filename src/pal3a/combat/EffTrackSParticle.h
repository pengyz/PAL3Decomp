#ifndef PAL3A_EFFTRACKSPARTICLE_H
#define PAL3A_EFFTRACKSPARTICLE_H

#include "pal3a_types.h"

class CEffTrackSParticle {
public:
    char _data[116];

    void Update(float fCurTime);
    bool Create(tagEffObjType * pType);
    ~CEffTrackSParticle();
    void Render();
    CEffTrackSParticle();
    char * GetEditorTaskDescription(int nIndex);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
};

#endif // PAL3A_EFFTRACKSPARTICLE_H
