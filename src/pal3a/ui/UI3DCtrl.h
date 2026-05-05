#ifndef PAL3A_UI3DCTRL_H
#define PAL3A_UI3DCTRL_H

#include "pal3a_types.h"

class UI3DCtrl {
public:
    char _data[308];

    void SetOriginPt(int x, int y, int from_y);
    void SetOriginPt(int x, int y);
    gbRay GetMouseRay(gbRay * __$ReturnUdt);
    void Render();
    void SetOrthosize(float size);
    UI3DCtrl();
    bool IsOver(int id);
    void SetRotateMode(int mode, float target);
    int Update(float deltatime, int haveinput);
    ~UI3DCtrl();
    void SetRotate(float rotate);
    void Create(uint id, UIWnd * pfather);
    void Destroy();
};

class UI3DObj {
public:
    char _data[32];

    bool IsOver();
    void Destroy();
    UI3DObj();
    ~UI3DObj();
    void Load(char * filename, ACTION_KIND act);
};

#endif // PAL3A_UI3DCTRL_H
