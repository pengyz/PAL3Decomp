#ifndef PAL3A_EFFTRACKGRID_H
#define PAL3A_EFFTRACKGRID_H

#include "pal3a_types.h"

class CEffTrackGrid {
public:
    char _data[4308];

    bool Create(tagEffObjType * pType);
    ~CEffTrackGrid();
    void Update(float fCurTime);
    void Render();
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    CEffTrackGrid();
    char * GetEditorTaskDescription(int nIndex);
};

#endif // PAL3A_EFFTRACKGRID_H
