#ifndef PAL3A_UINOTE_H
#define PAL3A_UINOTE_H

#include "pal3a_types.h"

class UINote {
public:
    char _data[268];

    ~UINote();
    void ShowWindow(int show);
    void Note(char * str);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void Create(UIWnd * pfather);
    int Update(float deltatime, int haveinput);
    UINote();
};

#endif // PAL3A_UINOTE_H
