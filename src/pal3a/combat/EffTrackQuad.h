#ifndef PAL3A_EFFTRACKQUAD_H
#define PAL3A_EFFTRACKQUAD_H

#include "pal3a_types.h"

class CEffTrackQuad {
public:
    char _data[4300];

    char * GetEditorTaskDescription(int nIndex);
    ~CEffTrackQuad();
    void Render();
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    CEffTrackQuad();
    void Update(float fCurTime);
    bool Create(tagEffObjType * pType);
};

#endif // PAL3A_EFFTRACKQUAD_H
