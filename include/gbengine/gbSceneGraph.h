#pragma once

#include "gbengine/gbengine_types.h"
#include "gbengine/gbCamera.h"
#include "gbengine/gbRenderEffect.h"

// Forward declarations (defined after this header or circular deps)
class gbVisNode;
class gbVolModNode;
// gbBladeMgr - blade trail effect manager
// Contains 32 blade entries (each 0xBC bytes) followed by global state
// Total entries array = 32 * 0xBC = 0x1780 bytes
struct gbBladeEntry {
    void* pGeomNode;        // +0x00: associated geom node pointer
    char _pad04[0xAC];      // +0x04..+0xAF
    float timeScale;        // +0xB0: per-blade time scale
    char _padB4[0x08];      // +0xB4..+0xBB
    // sizeof = 0xBC
};

class gbBladeMgr {
public:
    gbBladeEntry entries[32];   // +0x0000 (32 * 0xBC = 0x1780)
    char _pad1780[0x0C];        // +0x1780..+0x178B
    float globalTimeScale;      // +0x178C: global time scale factor
};

// ============================================================================
// gbLight - light parameters structure (maps to D3DLIGHT9)
// ============================================================================
struct gbLight {
    int type;
    gbColorFlt diffuse;
    gbColorFlt specular;
    gbColorFlt ambient;
    gbVec3D position;
    gbVec3D direction;
    float range;
    float falloff;
    float attenuation0;
    float attenuation1;
    float attenuation2;
    float theta;
    float phi;
};

// ============================================================================
// gbRenderInfoObj - render object info in scene graph pool
// sizeof = 0x70 = 112 bytes (verified: pool = malloc(0x70000) / 4096 objects)
// Layout verified via IDA: NewOneRenderObj, CalEffectiveVolMod, AttachSelf, Render
// ============================================================================
struct gbRenderInfoObj {
    gbVisNode* pNode;           // +0x00 [0]: owner node
    void* pMatrixOverride;      // +0x04 [1]: optional matrix override
    int sectionIndex;           // +0x08 [2]: mesh section index
    gbRenderEffect* pEffect;    // +0x0C [3]: render effect to use
    void* pTextureArray;        // +0x10 [4]: pointer to section texture array
    int renderPriority;         // +0x14 [5]: from node's renderPriority
    int isOpaque;               // +0x18 [6]: 1 if opaque, 0 if transparent
    unsigned int renderFlags;   // +0x1C [7]: combined render flags
    gbMatrix4 worldMatrix;      // +0x20 [8..23]: world transform (64 bytes)
    void* volModSlotA[2];       // +0x60 [24..25]: volume modifier nodes (type A)
    void* volModSlotB[2];       // +0x68 [26..27]: volume modifier nodes (type B)
};

// ============================================================================
// gbLightObj - light object with virtual methods
// ============================================================================
class gbLightObj {
public:
    enum LIGHT_TYPE {
        LIGHT_POINT = 1,
        LIGHT_SPOT = 2,
        LIGHT_DIRECTIONAL = 3
    };

    gbVec3D position;
    gbVec3D direction;
    gbColorFlt diffuse;
    gbColorFlt ambient;
    gbColorFlt specular;
    float range;
    float attenuation0;
    float attenuation1;
    float attenuation2;
    int lightType;
    int enabled;
    gbSphere boundingSphere;
    gbLight sysLight;

    gbLightObj(void);
    gbLightObj(const gbLightObj& other);
    virtual ~gbLightObj(void);
    void Init(enum LIGHT_TYPE type);
    void ComputeBoundSphere(void);
    virtual float GetEffectOnPoint(const gbVec3D& point, int useAttenuation);
    virtual void Compute(gbVolModNode* volmod);
    virtual int GetType(void);
    virtual const gbSphere* GetBoundSphere(void);
    gbLight* GetSysLight(void);
    gbLightObj& operator=(const gbLightObj& other);
};

// ============================================================================
// gbSceneGraph - main scene graph manager
// ============================================================================
class gbSceneGraph {
public:
    void* renderObjPool;                  // +0x00 - malloc(0x70000)
    int renderObjPoolUsed;                // +0x04
    void* volModNodePool;                 // +0x08
    gbVisNode* rootNode;                  // +0x0c
    gbMatrix4 matrixPool1[16];
    gbVolModNode* volModNodes[4352];      // volume modifier node array
    int numVolModNodes;                   // volume modifier count
    gbGfxManager* pGfxManager;
    gbVisNode* skyBoxNode;                // sky box node
    gbRenderEffect* shadowQuadEffect;
    gbCamera* activeCamera;
    gbBladeMgr* bladeMgr;

    gbSceneGraph(gbGfxManager* gfxMgr, const gbVec3D& param2, float param3);
    ~gbSceneGraph(void);
    void AddSkyBox(gbVisNode* node);
    void Begin(gbCamera* camera);
    gbRenderInfoObj* NewOneRenderObj(gbVisNode* node);
    gbRenderInfoObj* NewShadowVolume(gbVisNode* node);
    void AddVolModNode(gbVolModNode* node);
    void CalEffectiveVolMod(gbRenderInfoObj* renderInfo, const gbVec3D& position, int flags);
    void End(void);
    void AddVisNode(gbVisNode* node);
    void DelVisNode(gbVisNode* node);
    void SetBladeTimeScale(float scale);
    void ResetBladeMgr(void);
};
