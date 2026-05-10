#pragma once
// Auto-generated: gbBaseMesh

#include "gbMeshMemCache.h"
#include "gbMeshType.h"
#include "gbResource.h"

class gbMeshSection;

class gbBaseMesh : public gbResource {
public:
    gbMeshType Type; // +0x18
    char ObjName[32]; // +0x1C
    unsigned int VertFVF; // +0x3C
    gbMeshSection * pSections; // +0x40
    int nSection; // +0x44
    gbMeshMemCache MemCache; // +0x48
    gbAABBox BoundBox; // +0x58
    float CurTime; // +0x70
    char TextureDir[256]; // +0x0
    gbRenderEffect * pShadowEffect[2]; // +0x0
    int Effect_RefCount; // +0x0
    gbGfxManager * pGfxMgr; // +0x74
    // total size: 0x78 (120)

};
