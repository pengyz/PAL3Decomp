#include "SceneMap.h"
#pragma once
// Auto-generated: SceneMapPlayer

#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"

class NavTileLayer;

class SceneMapPlayer : public SceneMap {
public:
    char _gap_000[16]; // +0x0
    int m_nLayerIndex; // +0x10
    tagPOINT m_playerpt; // +0x14
    char _gap_018[4]; // +0x18
    tagRECT m_playerfov; // +0x1C
    char _gap_020[12]; // +0x20
    int m_maxwidth; // +0x2C
    int m_maxheight; // +0x30
    gbTexture * m_tex; // +0x34
    gbImage2D m_img; // +0x38
    char _gap_03C[196]; // +0x3C
    NavTileLayer * m_layer; // +0x100
    BYTE m_bBuild; // +0x104
    char m_szName[128]; // +0x105
    char _tail_185[3]; // +0x185
    // total size: 0x188 (392)

    virtual void Reset(); // 0x004208A0
    void ClearName(); // 0x004220F0
};
