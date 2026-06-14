#include "UIWnd.h"
#pragma once
// Auto-generated: UIFrameWnd

#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"

class UIFrameWnd : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    gbTexture * m_pbktex; // +0x44
    // total size: 0x48 (72)

    virtual ~UIFrameWnd() {}

    virtual void RenderWithTexture(); // 0x00442E90
    virtual BOOL Update_2ff0(int nVal, int nVal2); // 0x00442FF0
    virtual void Destroy(); // 0x00442420
    virtual void Render(); // 0x00443950
    virtual BOOL UpdateIfVisible(int nVal, int nVal2); // 0x00443970
    virtual void Destroy_38f0(); // 0x004438F0
    virtual int sub_443530(void *Block, char a3); // 0x00443530
    virtual gbVFileSystem * LoadFrameResources(); // 0x004435A0
    UIFrameWnd(); // 0x0043BB70
    virtual BOOL Update_bbc0(int nVal, int nVal2); // 0x0043BBC0
    void _UIFrameWnd(); // 0x00442390
    gbVFileSystem * SetTextureByID(int nTexID); // 0x00442540
    void SetTextureByName(LPCSTR lpTexName, char bCalcUV); // 0x004425D0
    int CalculateLayout(); // 0x00442890
    virtual BOOL Update(int nVal, int nVal2); // 0x00442AD0
    void SetPosition(int nVal, int nVal2); // 0x00442C60
    int SetFrameParam(int nVal); // 0x00442C80
    UIFrameWnd * _sdtor_8(UIFrameWnd *Block, char a2); // 0x00442D20
    void _UIFrameWnd_ovl_2d40(); // 0x00442D40
    void ctor(); // 0x00442E80
    virtual int sub_4431B0(void *Block, char a3); // 0x004431B0
    void DestroyCallingCtor(); // 0x004431D0
    virtual int sub_4433A0(void *Block, char a3); // 0x004433A0
    void _dtor_thunk(); // 0x004433C0
    void * InitSharedPanel(); // 0x004434C0
    void _UIFrameWnd_ovl(); // 0x00443550
    virtual int sub_444AA0(void *Block, char a3); // 0x00444AA0
    void _UIFrameWnd_Full(); // 0x00444AC0
    virtual int RenderAll(); // 0x00444AD0
    virtual BOOL ProcessInput(int nVal, int nVal2); // 0x00444D30
    BOOL IsOnScreen(int nVal, int nVal2); // 0x00450560
    int OnPaintUpdate(); // 0x0045A220
    BOOL ProcessTimer(BOOL bEnable, BOOL bReset, int nInterval, int nParam); // 0x00478880
    bool RollProbability(float fProb); // 0x0048CFB0
};
