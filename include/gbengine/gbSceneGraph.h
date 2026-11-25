#pragma once

#include "gbengine/gbengine_export.h"

#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_internal.h"
#include "gbengine/gbCamera.h"
#include "gbengine/gbRenderEffect.h"

// Forward declarations (defined after this header or circular deps)
class gbVisNode;
class gbVolModNode;
class gbDynVertBuf;
struct gbTextureArray;

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
    float Z;      // +0x04 [1]: Z coordinate (3D position component)
    int Param;           // +0x08 [2]: mesh section index
    gbRenderEffect* pEffect;    // +0x0C [3]: render effect to use
    void* pTexArray;        // +0x10 [4]: pointer to section texture array
    int Priority;         // +0x14 [5]: from node's renderPriority
    unsigned int Flags;               // +0x18 [6]: 1 if opaque, 0 if transparent
    unsigned int EffectFlag;   // +0x1C [7]: combined render flags
    gbMatrix4 worldMatrix;      // +0x20 [8..23]: world transform (64 bytes)
    void* volModSlotA[2];       // +0x60 [24..25]: volume modifier nodes (type A)
    void* volModSlotB[2];       // +0x68 [26..27]: volume modifier nodes (type B)
};

// ============================================================================
// gbLightObj - light object with virtual methods
// Members inherited from gbVolumeModifier
// ============================================================================
class gbAABBox;
class gbGfxManager;
/* [L-VAR 2026-11-11g] LIGHT_TYPE hoisted to global scope: decomp references
   LIGHT_SPOT unqualified at global scope (PAL3/RoleAtt/CScreenMode, 3 TUs);
   enums.json annotation has the family as global GBLIGHT_* constants. Enums
   have no storage -- hoisting is ABI-neutral, name-visible per decomp shape. */
enum LIGHT_TYPE {
    LIGHT_POINT = 1,
    LIGHT_SPOT = 2,
    LIGHT_DIRECTIONAL = 3
};

/* [2026-11-25] LGT_TYPE 家族退役: gbengine.dll 无此 mangle/til 枚举, enums.json
   亦无此键(521-523 历史行号早已退役)。Init 参数家族由二进制三证定谳为 LIGHT_TYPE:
   mangle W4LIGHT_TYPE@1 + IAT 导入调用(call ds:) + 语料渲染 LIGHT_SPOT(值2)。 
   2026-11-12 的 LGT_TYPE "矫正"撤销(依据=调用点值 0/1/2 全在 LGT 域——实为值 2
   同域歧义误读, 见 tools/probe_gbengine_light_20261125.py)。 */

class GBAPI gbLightObj : public gbVolumeModifier {
public:

    gbLightObj(void);
    gbLightObj(const gbLightObj& other);
    virtual ~gbLightObj(void);
    /* [2026-11-25 revert 2026-11-12 矫正] 参数家族=LIGHT_TYPE: mangle
       W4LIGHT_TYPE@1(二进制硬真值) + call ds: IAT 导入 + 5 调用点 raw push
       {0, ebp, 0, 2, 2}(值2=LIGHT_SPOT 渲染一致)。DLL 端 Init 体无 switch
       直存 this+8(值域无 DLL 约束)。 */
    void Init(enum LIGHT_TYPE type);
    void ComputeBoundSphere(void);
    virtual float GetEffectOnPoint(const gbVec3D& point, int useAttenuation);
    virtual void Compute(gbVolModNode* volmod);
    virtual int GetType(void);
    virtual const gbSphere* GetBoundSphere(void);
    gbLight* GetSysLight(void);
    gbLightObj& operator=(const gbLightObj& other);

    // PAL3-side methods (defined in pal3/src/Misc/gbLightObj.cpp — 非 dll 导出)
    BOOL IsIdle();  // 0x0042BEE0
    void GetAABBox(gbAABBox *p);  // 0x0042C6A0
    gbGfxManager * GetGfxManager(int nVal1);  // 0x0042C6E0
    int GetCGEntry(char a2);  // 0x0042C8D0
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
class GBAPI gbSceneGraph {
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
    unsigned char pnodebuf[2048];    // buffer for scene node data

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
