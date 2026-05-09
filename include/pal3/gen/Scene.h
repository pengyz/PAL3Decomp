#pragma once
// Auto-generated: Scene

#include "NavigationInfo.h"
#include "PtrArray.h"
#include "Role.h"
#include "SceneInfo.h"
#include "SceneMapObj.h"
#include "SceneObj.h"
#include "gbAABBox.h"

class gbGeomNode;
class gbVisNode;

class Scene {
public:
    SceneInfo m_info; // +0x0
    gbGeomNode * m_geomnode; // +0x84
    gbVisNode * m_lights; // +0x88
    gbAABBox m_aabb; // +0x8C
    PtrArray m_bbArray; // +0xA4
    SceneMapObj m_objmap[2]; // +0xB4
    int m_numobj; // +0xDC
    SceneObj m_obj[256]; // +0xE0
    int m_numnpc; // +0x6F8E0
    Role m_npc[72]; // +0x6F8E4
    NavigationInfo m_nav; // +0x10AF24
    gbGeomNode * m_cvd; // +0x10B090
    NavigationInfo m_CamCollide; // +0x10B094
    unsigned char m_bHasNavCollide; // +0x10B200
    int m_bLoad; // +0x10B204
    int m_battached; // +0x10B208
    unsigned char m_lastobj; // +0x10B20C
    int m_bStar; // +0x10B210
    // total size: 0x10B214 (1094164)

    int LoadConfig(void *pConfig); // 0x00410990
};
