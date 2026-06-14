#include "UIWnd.h"
#pragma once
// Auto-generated: UISceneMap

#include "UIButton.h"
#include "UIStatic.h"
#include "UIStaticEX.h"
#include "UIStaticFlex.h"
#include "UITextureArray.h"
#include "gbengine/gbVFileSystem.h"

class UISceneMap : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    UIButton m_probe; // +0x44
    char _gap_048[340]; // +0x48
    UIStatic m_base; // +0x19C
    char _gap_1A0[148]; // +0x1A0
    UIStaticEX m_compass; // +0x234
    char _gap_238[180]; // +0x238
    UIStaticFlex m_mapbk; // +0x2EC
    char _gap_2F0[188]; // +0x2F0
    UITextureArray m_icons; // +0x3AC
    char _gap_3B0[64]; // +0x3B0
    int m_state; // +0x3F0
    // total size: 0x3F4 (1012)

    virtual ~UISceneMap() {}

    virtual void Render(); // 0x00450230
    virtual double Update(float fVal, int nVal); // 0x004501A0
    char sub_443CA0(int thisa, float fVal); // 0x00443CA0
    unsigned int ValidateInput(unsigned int dwVal); // 0x00449F70
    int ctor(); // 0x0044FFE0
    void ctor_90(); // 0x00450090
    UISceneMap(); // 0x00450DC0
    int LoadCompass(const char *arg0, int nVal); // 0x00451200
    int RenderWithUpdate(); // 0x0046F2C0
    int ShowPage(); // 0x004B42F0
    void Destructor(); // 0x004B47E0
    int fn_523E60(); // 0x00523E60
    void Render_527cd0(); // 0x00527CD0
    void Render_529c80(); // 0x00529C80
    int SetCurrentMapID(int nVal); // 0x0052FBA0
    struct gbVFileSystem * LoadOverlayTexture(double thisa, int nVal); // 0x00535930
    int SetColorIfValid(int nVal); // 0x00535960
    int SetFieldIfValid(int nVal); // 0x00535E50
};
