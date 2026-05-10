#pragma once
// Auto-generated: UISceneMap

#include "UIButton.h"
#include "UIStatic.h"
#include "UIStaticEX.h"
#include "UIStaticFlex.h"
#include "UITextureArray.h"
#include "UIWnd.h"

class UISceneMap : public UIWnd {
public:
    unsigned char m_bLeft; // +0x44
    unsigned char m_bPlayer; // +0x45
    float m_lastZ; // +0x48
    gbVec3D m_lastLookAt; // +0x4C
    UIButton m_probe; // +0x58
    UIStatic m_base; // +0x1B0
    UIStatic m_addin; // +0x250
    UIStaticEX m_compass; // +0x2F0
    UIStaticFlex m_mapbk; // +0x3B0
    UITextureArray m_icons; // +0x470
    int m_state; // +0x4B4
    // total size: 0x4B8 (1208)

};
