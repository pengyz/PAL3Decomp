#include "UIFrameWnd.h"
#pragma once
// Auto-generated: UITitle_QCYM

#include "UIButtonEXA.h"
#include "UIStatic.h"

class UITitle_QCYM : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    tagRECT rc; // +0x48
    char _gap_04C[12]; // +0x4C
    char buf[256]; // +0x58
    UIStatic m_OutFrameT; // +0x158
    char _gap_15C[156]; // +0x15C
    UIStatic m_OutFrameR; // +0x1F8
    char _gap_1FC[156]; // +0x1FC
    UIStatic m_OutFrameL; // +0x298
    char _gap_29C[156]; // +0x29C
    UIStatic m_OutFrameB; // +0x338
    char _gap_33C[156]; // +0x33C
    UIStatic m_background; // +0x3D8
    char _gap_3DC[156]; // +0x3DC
    UIStatic m_title; // +0x478
    char _gap_47C[156]; // +0x47C
    UIButtonEXA m_btn[30]; // +0x518
    char _tail_590[16252]; // +0x590
    // total size: 0x450C (17676)

    virtual int OnMsgSaveData(unsigned int uMsg, unsigned int wParam, int lParam); // 0x004568C0
    int HandleDeviceLostC(); // 0x00529BE0
};
