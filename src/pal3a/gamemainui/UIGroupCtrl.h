#ifndef PAL3A_UIGROUPCTRL_H
#define PAL3A_UIGROUPCTRL_H

#include "pal3a_types.h"

class UIGroupCtrl {
public:
    char _data[88];

    void PageUp();
    bool RectInRect(tagRECT * srcRc, tagRECT * dstRc);
    void Create(tagRECT bkRc, int ItemNum, int ItemW, int ItemH, char * bkpic, uchar opt);
    ~UIGroupCtrl();
    bool RectOverLapBTM(tagRECT * srcRc, tagRECT * dstRc);
    void Update();
    UIGroupCtrl();
    void Reset();
    bool RectOverLapTOP(tagRECT * srcRc, tagRECT * dstRc);
    void Render();
    void PageDown();
};

#endif // PAL3A_UIGROUPCTRL_H
