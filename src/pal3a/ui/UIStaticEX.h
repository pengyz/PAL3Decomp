#ifndef PAL3A_UISTATICEX_H
#define PAL3A_UISTATICEX_H

#include "pal3a_types.h"

class UIMap {
public:
    char _data[152];

    bool CheckLeft(int left);
    bool MoveMapLeftUp(float deltatime);
    bool CheckRight(int right);
    bool CheckMoveRight(float deltatime);
    bool CheckMoveLeft(float deltatime);
    bool MoveMapRightDown(float deltatime);
    int Update(float deltatime, int haveinput);
    bool CheckMoveDown(float deltatime);
    bool MoveMapLeftDown(float deltatime);
    ~UIMap();
    bool CheckBottom(int bottom);
    void MovingMap(float deltatime, tagPOINT pt);
    void MovingMap(float deltatime);
    void SetPtInValidArea(tagPOINT pt);
    bool MoveMapRightUp(float deltatime);
    void Create(uint id, int MapWidth, int MapHeight, tagRECT ScreenRect, char * mapImageArray, UIWnd * pfather);
    bool CheckTop(int top);
    void RenderMap();
    bool MoveMapUp(float deltatime);
    bool CheckMoveUp(float deltatime);
    bool MoveMapRight(float deltatime);
    void Destroy();
    bool MoveMapLeft(float deltatime);
    void ResetMapPosition();
    bool MoveMapDown(float deltatime);
    UIMap();
    int CheckSubMapShow();
    void Render();
};

class UIStaticEX {
public:
    char _data[192];

    int Update(float deltatime, int haveinput);
    ~UIStaticEX();
    void Render();
    UIStaticEX();
};

class UIStaticEXA {
public:
    char _data[200];

    ~UIStaticEXA();
    void SetCenterPointInRect(int x, int y);
    UIStaticEXA();
    void Render();
};

class UIStaticFlip {
public:
    char _data[164];

    void Render();
    ~UIStaticFlip();
    UIStaticFlip();
};

class UIStaticRM {
public:
    char _data[188];

    void StopFlash();
    void Render();
    int Update(float deltatime, int haveinput);
    ~UIStaticRM();
    void BeginFlash();
    UIStaticRM();
};

#endif // PAL3A_UISTATICEX_H
