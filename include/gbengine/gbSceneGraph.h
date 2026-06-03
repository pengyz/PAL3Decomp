#pragma once

#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_internal.h"
#include "gbengine/gbCamera.h"
#include "gbengine/gbRenderEffect.h"

// Forward declarations (defined after this header or circular deps)
class gbVisNode;
class gbVolModNode;
class gbDynVertBuf;

// ============================================================================
// gbBladeMgr - blade trail effect manager
// sizeof(gbBladeMgr) = 0x1790
// Contains 32 blade entries (each 0xBC bytes) followed by global state
// ============================================================================

// gbBladeEntry - single blade trail instance
// sizeof = 0xBC = 188 bytes
// Each entry stores a ring buffer of vertex frames for one blade trail
struct gbBladeEntry {
    void* pGeomNode;            // +0x00: associated geom node pointer (used as lookup key)
    void* pVertexData;          // +0x04: malloc'd vertex buffer (numVertices * 0x10 * maxFrames)
    float timestamps[40];       // +0x08: per-frame timestamps (max 40 entries)
    float bladeTime;            // +0xA8: blade time duration threshold (init 0.1f)
    float curTime;              // +0xAC: accumulated current time for this slot
    float timeScale;            // +0xB0: per-blade time scale factor (init 1.0f when allocated)
    int numVertices;            // +0xB4: number of vertices per frame
    int numFrames;              // +0xB8: current number of frames stored (max 40)
    // sizeof = 0xBC
};

class gbBladeMgr {
public:
    gbBladeEntry entries[32];       // +0x0000 (32 * 0xBC = 0x1780)
    void* pGfxManager;              // +0x1780: pointer to gbGfxManager
    float curTime;                  // +0x1784: global accumulated time
    gbRenderEffect* pEffect;        // +0x1788: blade render effect
    float globalTimeScale;          // +0x178C: global time scale factor

    void Init(void* gfxMgr);
    void Reset(void);
    void Submit(void* vertexData, int numVertices, void* geomNode);
    void SetBladeTime(void* geomNode, float time);
    void SetBladeTimeScale(void* geomNode, float scale);
    void SetTimeScale(float scale);
    void Update(void);
    void Render(void);
    void* GetLastBladePos(void* geomNode);
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
// Members inherited from gbVolumeModifier
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
    void* renderObjPool;                      // +0x0000 [0]: malloc(0x70000) = 4096 gbRenderInfoObj
    int numRenderObjs;                        // +0x0004 [1]: current render obj count
    void* volModNodePool;                     // +0x0008 [2]: spatial structure
    gbVisNode* rootNode;                      // +0x000C [3]: root scene node
    gbRenderInfoObj shadowInfoPool[16];       // +0x0010: shadow volume render info slots (16×112=1792)
    int numShadowVolumes;                     // +0x0710 [452]: shadow volume count
    gbVolModNode* volModNodes[256];           // +0x0714 [453..]: volume modifier node pointers
    gbMatrix4 matrixPool[256];                // +0x0B14: 256 matrices (16384 bytes)
    int numVolModNodes;                       // +0x4B14 [4805]: volume modifier count
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
