#pragma once
// Auto-generated: SceneObjParam

#include "ObjectInfo.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbengine_types.h"

class Role;
class SceneObj;

class SceneObjParam {
public:
    gbVec3D tmpVEC[8]; // +0x0
    char _gap_020[64]; // +0x20
    SceneObj * mLinkObj; // +0x60
    Role * mRole; // +0x64
    ObjectInfo mInfo; // +0x68
    char _tail_06C[600]; // +0x6C
    // total size: 0x2C4 (708)

    int UpdateCameraAndRole(struct gbGfxManager *p); // 0x00533CB0
    int FlushCommands(); // 0x00533DA0
};
