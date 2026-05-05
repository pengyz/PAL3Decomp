#ifndef PAL3A_UIBUTTON_H
#define PAL3A_UIBUTTON_H

#include "pal3a_types.h"

class UIButton {
public:
    char _data[344];

    void SetOnPic(char * picname, uchar opt);
    void SetCaption(char * txt);
    ~UIButton();
    void SetBk(char * picname, uchar opt);
    void Destroy();
    void SetDownPic(char * picname, uchar opt);
    void Render();
    void SetNormalPic(char * picname, uchar opt);
    void Create(uint id, tagRECT * rect, UIWnd * pfather, char * picname, uchar dbclk, uchar opt, uchar bCalFrameRate);
    int Update(float deltatime, int haveinput);
    void SetDisablePic(char * picname, uchar opt);
    UIButton();
};

class UIButtonEX {
public:
    char _data[392];

    unsigned char GetChannel(int cur, int x, int y, int channel);
    void Create(uint id, tagRECT * rect, UIWnd * pfather, char * picname, uchar opt, uchar bCalFrameRate);
    int Update(float deltatime, int haveinput);
    void GetOPTLibData(char * libName, int x, int y, int w, int h, int cur);
};

class UIButtonEXA {
public:
    char _data[376];

    ~UIButtonEXA();
    void Create(uint id, tagRECT * rect, UIWnd * pfather, char * picname, uchar opt);
    int Update(float deltatime, int haveinput);
    void Render();
    unsigned char GetChannel(int x, int y, int channel);
    UIButtonEXA();
    void SetBk(char * picname, uchar opt);
    void GetOPTLibData(char * libName, int x, int y, int w, int h);
};

#endif // PAL3A_UIBUTTON_H
