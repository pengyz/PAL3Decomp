#ifndef PAL3A_UIPROGRESSBAR_H
#define PAL3A_UIPROGRESSBAR_H

#include "pal3a_types.h"

class UIProgressBar {
public:
    char _data[244];

    void SetRect(tagRECT * rc);
    ~UIProgressBar();
    int Update(float deltatime, int haveinput);
    void SetMaxVal(float val);
    void Create(uint id, tagRECT * rect, UIWnd * pfather, uchar bCalFrameRate);
    void SetDecorate(char * pic, uchar opt);
    void SetRadiusWidth(int radius);
    void Destroy();
    void SetRRadius(int radius);
    void SetTRadius(int radius);
    void SetProgress(float progress);
    void SetBk(char * bkPic, uchar opt);
    void SetMode(int mode);
    void SetLRadius(int radius);
    void SetBRadius(int radius);
    void SetForce(char * foPic, uchar opt);
    void CleanProgress();
    void SetProgressImmediate(float progress);
    UIProgressBar();
    void Render();
};

#endif // PAL3A_UIPROGRESSBAR_H
