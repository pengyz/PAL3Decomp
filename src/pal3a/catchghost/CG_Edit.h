#ifndef PAL3A_CG_EDIT_H
#define PAL3A_CG_EDIT_H

#include "pal3a_types.h"

class CG_Edit {
public:
    char _data[120];

    ~CG_Edit();
    SceneObj * GetLastObj();
    void DrawAreaByMousePoint(uchar bFill, uchar bNav);
    bool ShowTileRectNav(NavTileLayer * layer, tagRECT * rect);
    CG_Edit(CG_Entry * pFather);
    void Update(float deltatime);
    bool RectInRect(tagRECT * srcRc, tagRECT * dstRc);
    gbVec3D GetClickPoint(gbVec3D * __$ReturnUdt);
    void Init();
    void ConfirmAndAppend();
};

#endif // PAL3A_CG_EDIT_H
