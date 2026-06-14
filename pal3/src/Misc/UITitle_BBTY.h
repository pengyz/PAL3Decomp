#include "UIFrameWnd.h"
#pragma once
// Auto-generated: UITitle_BBTY

#include "UIButton.h"
#include "UIButtonEXA.h"
#include "UIStatic.h"

class UITitle_BBTY : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    tagRECT rc; // +0x48
    char _gap_04C[12]; // +0x4C
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    UIStatic m_background; // +0x168
    char _gap_16C[156]; // +0x16C
    UIStatic m_remark; // +0x208
    char _gap_20C[156]; // +0x20C
    UIButtonEXA m_btn[3]; // +0x2A8
    char _gap_2B4[1116]; // +0x2B4
    UIButton m_exit; // +0x710
    char _gap_714[340]; // +0x714
    UIStatic m_Name; // +0x868
    char _gap_86C[156]; // +0x86C
    UIStatic m_Left; // +0x908
    char _gap_90C[156]; // +0x90C
    UIStatic m_Right; // +0x9A8
    char _gap_9AC[156]; // +0x9AC
    UIStatic m_FlagT; // +0xA48
    char _gap_A4C[156]; // +0xA4C
    UIStatic m_FlagB; // +0xAE8
    char _gap_AEC[156]; // +0xAEC
    UIButton m_Start; // +0xB88
    char _gap_B8C[340]; // +0xB8C
    UIButton m_Notes; // +0xCE0
    char _tail_CE4[1952]; // +0xCE4
    // total size: 0x1484 (5252)

    virtual ~UITitle_BBTY() {}

    virtual double UpdateFrame(double result, int arg0, int arg0a); // 0x004520A0
    virtual int OnMessage(int nVal, int nVal2, int nVal3); // 0x00452420
    int ctor_1CC0(); // 0x00451CC0
    void ctor(); // 0x00451DA0
    int CreateFromScript(); // 0x00451E50
    void SetRemarkTextures(int nVal); // 0x004524B0
};
