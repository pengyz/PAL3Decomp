#ifndef PAL3A_UIEMOTE_H
#define PAL3A_UIEMOTE_H

#include "pal3a_types.h"

class UIEmote {
public:
    char _data[2440];

    int Update(float deltatime, int haveinput);
    ~UIEmote();
    void Active(Role * role, UIEMOTE em);
    void Create(UIWnd * pfather);
    int IsWaiting();
    UIEmote();
    void ComputePos();
    void HideEmote();
};

#endif // PAL3A_UIEMOTE_H
