#ifndef PAL3A_EFFTRACKCYLINDER_H
#define PAL3A_EFFTRACKCYLINDER_H

#include "pal3a_types.h"

class CEffTrackCylinder {
public:
    char _data[4320];

    bool Create(tagEffObjType * pType);
    ~CEffTrackCylinder();
    CEffTrackCylinder();
    void Update(float fCurTime);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    void Render();
    char * GetEditorTaskDescription(int nIndex);
};

#endif // PAL3A_EFFTRACKCYLINDER_H
