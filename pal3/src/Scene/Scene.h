#pragma once
// Auto-generated: Scene

#include "PtrArray.h"
#include "Role.h"
#include "SceneMapObj.h"
#include "SceneObj.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbGeomNode.h"
#include "gbengine/gbVisNode.h"

class Scene {
public:
    void * _vftable; // +0x0
    char * m_pDataBegin; // +0x4
    char * m_pDataEnd; // +0x8
    char * m_pCapacity[29]; // +0xC
    char _gap_010[112]; // +0x10
    int m_nReset; // +0x80
    gbGeomNode * m_geomnode; // +0x84
    gbVisNode * m_lights; // +0x88
    gbAABBox m_aabb; // +0x8C
    char _gap_090[20]; // +0x90
    PtrArray m_bbArray; // +0xA4
    char _gap_0A8[12]; // +0xA8
    SceneMapObj m_objmap[2]; // +0xB4
    char _gap_0BC[32]; // +0xBC
    int m_numobj; // +0xDC
    SceneObj m_obj[256]; // +0xE0
    char _gap_4E0[455680]; // +0x4E0
    int m_numnpc; // +0x6F8E0
    Role m_npc[72]; // +0x6F8E4
    char _tail_6FA04[642780]; // +0x6FA04
    // total size: 0x10C8E0 (1100000)

    void Render2(); // 0x0040C7D0
    int AddRoleEntry(const int * pRoleTriple); // 0x00410990
    double GetTileHeight(int nSceneIdx, int nX, int nY, int *pFlags); // 0x00421230
    static int GetNumObj(); // 0x00456FC0
};
