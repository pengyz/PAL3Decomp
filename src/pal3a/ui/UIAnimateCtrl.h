#ifndef PAL3A_UIANIMATECTRL_H
#define PAL3A_UIANIMATECTRL_H

#include "pal3a_types.h"

class UIAnimateCtrl {
public:
    char _data[164];

    UIAnimateCtrl();
    void Open(char * animatename);
    ~UIAnimateCtrl();
    void Reset();
    int Update(float deltatime, int haveinput);
    void SetFPS(float FPS);
    void Render();
    void Open2(char * filename, int numfrm);
    void SetLoop(int nLoop);
    void Destroy();
};

#endif // PAL3A_UIANIMATECTRL_H
