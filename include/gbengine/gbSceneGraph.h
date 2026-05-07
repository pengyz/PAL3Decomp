#pragma once

#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_internal.h"
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
class gbLightObj : public gbVolumeModifier {
public:
    enum LIGHT_TYPE {
        LIGHT_POINT = 1,
        LIGHT_SPOT = 2,
        LIGHT_DIRECTIONAL = 3
    };

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
// sizeof(gbSceneGraph) ~ 19248 bytes (0x4B30)
// Layout verified via IDA constructor and method offsets:
//   [0]     renderObjPool (gbRenderInfoObj array, malloc(0x70000))
//   [1]     numRenderObjs (count of render objects in pool)
//   [2]     volModNodePool (spatial partitioning structure)
//   [3]     rootNode (gbVisNode)
//   [4..] renderInfos: 16 entries × 112 bytes (gbRenderInfoObj-like)
//   then:  matrixPool: 256 × gbMatrix4 (64 bytes each)
//   [4805]  numVolModNodes
//   [4806]  pGfxManager
//   [4807]  skyBoxNode
//   [4808]  shadowQuadEffect
//   [4809]  activeCamera
//   [4810]  bladeMgr
//   +19244  bSceneActive (byte flag)
class gbSceneGraph {
public:
    void* renderObjPool;                      // +0x00 [0]: malloc(0x70000)
    int numRenderObjs;                        // +0x04 [1]: current render obj count
    void* volModNodePool;                     // +0x08 [2]: spatial structure
    gbVisNode* rootNode;                      // +0x0C [3]: root scene node
    char renderInfoPool[16 * 112];            // +0x10 [4..]: 16 render info slots (1792 bytes)
    gbMatrix4 matrixPool[256];                // +0x710: 256 matrices (16384 bytes)
    gbVolModNode* volModNodes[449];           // +0x4710: vol mod node pointers
    int numVolModNodes;                       // +0x4B14 [4805]
    gbGfxManager* pGfxManager;                // +0x4B18 [4806]
    gbVisNode* skyBoxNode;                    // +0x4B1C [4807]
    gbRenderEffect* shadowQuadEffect;         // +0x4B20 [4808]
    gbCamera* activeCamera;                   // +0x4B24 [4809]
    gbBladeMgr* bladeMgr;                     // +0x4B28 [4810]
    unsigned char bSceneActive;               // +0x4B2C: scene rendering flag
    char _pad[3];

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
