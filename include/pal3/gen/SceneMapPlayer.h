#pragma once
// Auto-generated: SceneMapPlayer

#include "SceneMap.h"

class NavTileLayer;

class SceneMapPlayer : public SceneMap {
public:
    int m_nLayerIndex; // +0x10
    tagPOINT m_playerpt; // +0x14
    tagRECT m_playerfov; // +0x1C
    int m_maxwidth; // +0x2C
    int m_maxheight; // +0x30
    gbTexture * m_tex; // +0x34
    gbImage2D m_img; // +0x38
    NavTileLayer * m_layer; // +0x100
    unsigned char m_bBuild; // +0x104
    char m_szName[128]; // +0x105
    // total size: 0x188 (392)

};
