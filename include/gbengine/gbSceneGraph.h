#pragma once

#include "gbengine/gbengine_types.h"

// Forward declarations
class gbVisNode;
class gbGfxManager;
class gbCamera;
class gbRenderEffect;
class gbEffectMgr;
class gbVolModNode;
class gbBladeMgr;

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
// sizeof = 0x70 (deduced from usage patterns)
// ============================================================================
struct gbRenderInfoObj {
    gbVisNode* node;            // +0x00
    void* renderData;           // +0x04
    int flags;                  // +0x08
    float distance;             // +0x0C
    int _reserved10[4];         // +0x10
    gbMatrix4 worldMatrix;      // +0x20 (64 bytes)
    int volModSlotA[2];         // +0x60
    int volModSlotB[2];         // +0x68
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
