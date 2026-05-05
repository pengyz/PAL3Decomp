#ifndef PAL3A_UITITLE_ARCSAVE_H
#define PAL3A_UITITLE_ARCSAVE_H

#include "pal3a_types.h"

class UITitle_ArcSave {
public:
    char _data[4228];

    void Create(UIWnd * father);
    ~UITitle_ArcSave();
    int Update(float deltatime, int haveinput);
    void Render();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    UITitle_ArcSave();
};

#endif // PAL3A_UITITLE_ARCSAVE_H
