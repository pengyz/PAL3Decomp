#ifndef PAL3A_HEADMSG_H
#define PAL3A_HEADMSG_H

#include "pal3a_types.h"

class HeadMsg {
public:
    char _data[68];

    ~HeadMsg();
    void SetY(int y);
    void Update(float fDeltaTIme);
    void Hide();
    void Render();
    HeadMsg();
    void NewMsg(char * str, int type, Role * pRole);
};

#endif // PAL3A_HEADMSG_H
