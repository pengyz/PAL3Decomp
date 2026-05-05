#ifndef PAL3A_UICAPTION_H
#define PAL3A_UICAPTION_H

#include "pal3a_types.h"

class UICaption {
public:
    char _data[132];

    void Caption(char * texfile, int numline);
    void Caption2(char * texfile, int numline);
    int Update(float deltatime, int haveinput);
    void DrawLine(int line, uchar alpha);
    ~UICaption();
    int IsWaiting();
    void DrawLine2(int line, uchar alpha);
    void Destroy();
    void Destroy2();
    void Render();
    UICaption();
};

#endif // PAL3A_UICAPTION_H
