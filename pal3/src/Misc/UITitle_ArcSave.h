#include "UIFrameWnd.h"
#pragma once
// Auto-generated: UITitle_ArcSave

#include "MUIDialog.h"

class PalScript;

class UITitle_ArcSave : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    MUIDialog m_YesNo; // +0x48
    char _tail_04C[4040]; // +0x4C
    // total size: 0x1014 (4116)

    virtual ~UITitle_ArcSave() {}

    virtual void Render(); // 0x0047C370
    virtual int ProcessPageAction(struct PalScript *p, int nVal); // 0x0047C3A0
    void Destroy(); // 0x0047BDF0
    virtual int OnMessage(int nVal, int nVal2, int nVal3); // 0x0047C430
    int ctor(); // 0x0047BBF0
    void ctor_BD20(); // 0x0047BD20
};
