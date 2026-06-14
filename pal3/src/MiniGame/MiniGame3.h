#pragma once
// Auto-generated: MiniGame3

#include "gbengine/gbengine_internal.h"

class MiniGame3 {
public:
    _BYTE _tail_000[4]; // +0x0
    // total size: 0x4 (4)

    void SetCameraActive(); // 0x00533FD0
    void Render(); // 0x00535320
    void PushPopStack(gbMatrixStack *pStack); // 0x00535970
    char LoadModels(const char *pszModel1, const char *pszModel2, const char *pszModel3); // 0x00535C30
    void RenderWithTransform(gbMatrixStack *pStack); // 0x00535F10
};
