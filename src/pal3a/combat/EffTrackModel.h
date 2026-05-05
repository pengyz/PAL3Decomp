#ifndef PAL3A_EFFTRACKMODEL_H
#define PAL3A_EFFTRACKMODEL_H

#include "pal3a_types.h"

class CEffTrackModel {
public:
    char _data[132];

    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    char * GetEditorTaskDescription(int nIndex);
    void Attach();
    ~CEffTrackModel();
    CEffTrackModel();
    bool Create(tagEffObjType * pType);
    void Update(float fCurTime);
};

#endif // PAL3A_EFFTRACKMODEL_H
