#ifndef PAL3A_UIANIMATECTRLEX_H
#define PAL3A_UIANIMATECTRLEX_H

#include "pal3a_types.h"

class UIAnimateCtrlEX {
public:
    char _data[204];

    void SetBk(char * texname);
    ~UIAnimateCtrlEX();
    void Render();
    int Update(float deltatime, int haveinput);
    UIAnimateCtrlEX();
};

#endif // PAL3A_UIANIMATECTRLEX_H
