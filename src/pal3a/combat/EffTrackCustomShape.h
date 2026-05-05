#ifndef PAL3A_EFFTRACKCUSTOMSHAPE_H
#define PAL3A_EFFTRACKCUSTOMSHAPE_H

#include "pal3a_types.h"

class CEffTrackCustomShape {
public:
    char _data[200];

    bool Create(tagEffObjType * pType);
    void Update(float fCurTime);
    ~CEffTrackCustomShape();
    void Render();
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    char * GetEditorTaskDescription(int nIndex);
    CEffTrackCustomShape();
};

#endif // PAL3A_EFFTRACKCUSTOMSHAPE_H
