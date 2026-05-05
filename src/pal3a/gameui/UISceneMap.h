#ifndef PAL3A_UISCENEMAP_H
#define PAL3A_UISCENEMAP_H

#include "pal3a_types.h"

class UISceneMap {
public:
    char _data[1208];

    ~UISceneMap();
    void CloseMap();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void Create(uint id, UIWnd * pfather, uchar left);
    void SetRect(tagPOINT pt);
    int Update(float deltatime, int haveinput);
    void DrawMap(tagRECT * rect, int mapindex);
    void Render();
    UISceneMap();
};

#endif // PAL3A_UISCENEMAP_H
