#include "UIDialog.h"
#pragma once
// Auto-generated: UINote

#include "UIStaticFlex.h"
#include "gbengine/gbengine_internal.h"

class UINote : public UIDialog {
public:
    char _gap_000[72]; // +0x0
    UIStaticFlex m_static; // +0x48
    char _gap_04C[188]; // +0x4C
    float time; // +0x108
    // total size: 0x10C (268)

    void * Create(int id, int nVal, int nVal2, char *tex); // 0x004450A0
    void ReleaseResources(); // 0x004B7F00
    int GetEntryPtr(int nIndex); // 0x00528D30
    int RenderIfVisible(gbMatrixStack *pMatrixStack); // 0x0052AFC0
    void RenderWithStack(gbMatrixStack *pStack); // 0x0052AFF0
    int CallVtableMethod(double pData); // 0x0052B030
};
