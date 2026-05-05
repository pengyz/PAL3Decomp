#ifndef PAL3A_UICOVERFRM_H
#define PAL3A_UICOVERFRM_H

#include "pal3a_types.h"

class UICoverFrm {
public:
    char _data[15080];

    void GotoGame(uint flag);
    void UpdateTestCloud(float deltatime);
    void BeginGame();
    void ResetSingleTestCloud(int i);
    void ResetTestCloud();
    void Destroy();
    void CreateTestCloud();
    void ResetSingleSmlCloud(int i);
    void ResetSingleMidCloud(int i);
    ~UICoverFrm();
    void CreateCloud();
    void CreateMidCloud();
    void Create();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void AdjustCloud();
    void AdjustMidCloud();
    void CreateBk800();
    void UpdateCloud(float deltatime);
    void ResetSmlCloud();
    int Update(float deltatime, int haveinput);
    void CreateBk1024();
    void ResetCloud();
    void SwitchMenu(MENU_TYPE type, ulong lparam);
    UICoverFrm();
    void Render();
    void ResetMidCloud();
    void AdjustSmlCloud();
    void UpdateLogoAlpha(float deltatime);
    void CreateSmlCloud();
    void ResetSingleCloud(int i);
};

#endif // PAL3A_UICOVERFRM_H
