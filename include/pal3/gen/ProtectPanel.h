#pragma once
// Auto-generated: ProtectPanel

#include "UIFrameWnd.h"
#include "UIProgressBar.h"
#include "UIPushButton.h"
#include "UIStatic.h"

class ProtectPanel : public UIFrameWnd {
public:
    UIStatic m_BK; // +0x48
    UIPushButton m_WHFace; // +0xE8
    UIPushButton m_WPXFace; // +0x1E4
    UIProgressBar m_WHFavor; // +0x2E0
    UIProgressBar m_WPXFavor; // +0x3D4
    tagRECT m_WHFaceRc; // +0x4C8
    tagRECT m_WHFavorRc; // +0x4D8
    tagRECT m_WPXFaceRc; // +0x4E8
    tagRECT m_WPXFavorRc; // +0x4F8
    // total size: 0x508 (1288)

};
