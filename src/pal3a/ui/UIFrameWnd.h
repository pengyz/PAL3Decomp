#ifndef PAL3A_UIFRAMEWND_H
#define PAL3A_UIFRAMEWND_H

#include "pal3a_types.h"

class UIFrameWnd {
public:
    char _data[72];

    ~UIFrameWnd();
    void Render();
    void Create(uint id, tagRECT rect, char * bkpicname);
    void Destroy();
    UIFrameWnd();
};

#endif // PAL3A_UIFRAMEWND_H
