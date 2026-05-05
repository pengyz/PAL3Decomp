#ifndef PAL3A_UIDRAGBAR_H
#define PAL3A_UIDRAGBAR_H

#include "pal3a_types.h"

class UIDragBar {
public:
    char _data[272];

    void Render();
    UIDragBar();
    ~UIDragBar();
    void SetMode(int mode);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void SeekVal(float val);
    void SetDir(int dir);
    void Destroy();
    void SetBarForce(char * bkpic, uchar opt);
    void SetRadiusWidth(int radius);
    void Create(uint id, tagRECT * rect, UIWnd * pfather, char * drag_pic, uchar opt);
    void SetDragSize(int x, int y);
    void SetBarBk(char * bkpic, uchar opt);
    void Clear();
    void SetMaxVal(float val);
    int Update(float deltatime, int haveinput);
};

#endif // PAL3A_UIDRAGBAR_H
