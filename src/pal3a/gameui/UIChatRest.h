#ifndef PAL3A_UICHATREST_H
#define PAL3A_UICHATREST_H

#include "pal3a_types.h"

class RestScript {
public:
    char _data[2068];

    ~RestScript();
    int GetKeyVal(char** srcKey, char * cmpKey);
    RestScript();
    void GetRestScript(char * FileName);
};

class UIChatRest {
public:
    char _data[9824];

    void Render();
    void Create(UIWnd * pfather);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void HideUI(uchar bHide, uchar bAll);
    int Update(float deltatime, int haveinput);
    void AdjustElement();
    UIChatRest();
    void Show(char * ScriptFileName, int v1, int v2, int v3);
    void Exit();
    ~UIChatRest();
    void Destroy();
};

#endif // PAL3A_UICHATREST_H
