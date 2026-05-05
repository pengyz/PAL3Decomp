#ifndef PAL3A_UIANIMATE_H
#define PAL3A_UIANIMATE_H

#include "pal3a_types.h"

class UIAnimate {
public:
    char _data[52];

    void GotoPos(uchar bflag, uchar IsLoop, int speed, tagRECT dstRc, UIWnd * mp);
};

#endif // PAL3A_UIANIMATE_H
