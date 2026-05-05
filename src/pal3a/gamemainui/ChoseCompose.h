#ifndef PAL3A_CHOSECOMPOSE_H
#define PAL3A_CHOSECOMPOSE_H

#include "pal3a_types.h"

class ChoseCompose {
public:
    char _data[3856];

    void SetSpecifyCompose(int Role);
    ~ChoseCompose();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void Render();
    void SpecifyCompose(ulong id);
    ChoseCompose();
    int Update(float deltatime, int haveinput);
    void Create();
};

#endif // PAL3A_CHOSECOMPOSE_H
