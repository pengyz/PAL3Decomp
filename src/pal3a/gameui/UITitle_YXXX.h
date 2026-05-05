#ifndef PAL3A_UITITLE_YXXX_H
#define PAL3A_UITITLE_YXXX_H

#include "pal3a_types.h"

class UITitle_YXXX {
public:
    char _data[2616];

    int Update(float deltatime, int haveinput);
    void Create(UIWnd * pWnd);
    void UpdateElementShow();
    void Render();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    UITitle_YXXX();
    ~UITitle_YXXX();
};

class _Item {
public:
    char _data[48];

    ~_Item();
    _Item();
    void Load(char * filename);
    void ReadItem(TxtFile * fd, uchar restart);
};

#endif // PAL3A_UITITLE_YXXX_H
