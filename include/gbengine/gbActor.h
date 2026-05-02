#pragma once

#include "gbengine/gbVisNode.h"

// Forward declarations
class gbActor;
class gbActorDef;
class gbActorMgr;
class gbAnimNodeGroup;
class gbGfxManager;
class gbRenderEffect;
class gbResManager;
class gbResource;
class gbTexture;
class gbVFileSystem;

// Actor export node (attachment points) - external query result
struct gbActorExpNode {
    int flags;
    int nodeIndex;
    float weight;
    int startFrame;
    int endFrame;
    char name[32];
};

// Internal export node data (sizeof = 0x84)
// Allocated as array of 4 (total 0x210 bytes)
struct gbExpNodeData {
    unsigned int nameCrc;   // +0x00: CRC32 of node name (used for lookup)
    gbMatrix4 localMatrix;  // +0x04: local transform (64 bytes)
    gbMatrix4 worldMatrix;  // +0x44: world transform (64 bytes)
    // sizeof = 0x84
};

// Mix action info (animation blending)
struct gbMixActInfo {
    int fromAction;
    int toAction;
    int mixDuration;
};

// Actor action state (stride = 0x24 = 36 bytes)
struct gbActionState {
    int state;                  // +0x00: 0=inactive, 1=active, 2=fade-out, 3=locked
    unsigned int actionCrc;     // +0x04: CRC32 of action name
    float weight;               // +0x08: blend weight
    unsigned int currentFrame;  // +0x0C
    unsigned int startFrame;    // +0x10
    unsigned int endFrame;      // +0x14
    void* eventData;            // +0x18: event notification flag/data
    int loopFlag;               // +0x1C
    unsigned long transition;   // +0x20
};


/* ======== gbActorDef (resource) ======== */
// gbActorDef layout from Ghidra + gbResource base analysis:
//   +0x00: vtable (virtual class)
//   +0x04: RefCount
//   +0x08: pName (char*) — from gbResource::SetName
//   +0x0C: NameCrc32
//   +0x10: IsLoaded
//   +0x14: pMgr (gbResManager*)
//   +0x9C: numMixInfo (int)
// Two concrete subclasses: non-MV3 (sizeof=0xE0), MV3 (sizeof=0x108)

class gbActorDef {
public:
    virtual ~gbActorDef() {}
    virtual void LoadFromFile(const char* filename) = 0;
    virtual int GetNumExportNodes(char* buffer1, char* buffer2, int maxNodes) = 0;
    virtual void UpdateBones(gbActor* actor) = 0;
    virtual int GetEventList(void* buffer, int fromFrame, int toFrame, void* eventData) = 0;

    int RefCount;               // +0x04
    char* pName;                // +0x08: resource name (set via gbResource::SetName)
    unsigned int NameCrc32;     // +0x0C
    int IsLoaded;               // +0x10
    void* pMgr;                 // +0x14: gbResManager*
    char _pad18[0x84];          // +0x18..+0x9B
    int numMixInfo;             // +0x9C: number of mix action entries
};


/* ======== gbActor ======== */

class gbActor : public gbVisNode {
public:
    gbActor(gbActorDef* actorDef);
    gbActor(const gbActor& other);
    virtual ~gbActor();

    virtual void Update();
    virtual void Render(gbRenderInfoObj* renderInfo);
    virtual void RenderShadowVolume(gbRenderInfoObj* renderInfo);
    virtual int Attach(gbRenderEffect* effect);
    virtual void Reset(float time);
    virtual void EnableShadow(int enable);
    virtual void GetBoundSphere(gbSphere* sphere);

    // Action control
    void GotoAction(char* actionName, int loop);
    void GotoAction(char* actionName, float startTime, float endTime);
    void GotoAction(char* action1, char* action2, char* action3);
    void GotoAction(unsigned long p1, int p2, unsigned int p3, unsigned int p4, unsigned long p5);
    void LockAction(char* actionName, float weight);
    void UnlockAction(char* actionName);

    // Query methods
    unsigned int GetActionDuration(char* actionName);
    unsigned int GetEventTime(char* actionName, char* eventName);
    int GetTagNodeTM(gbMatrix4* matrix, char* tagName);
    gbActorExpNode* GetAllExpNode();
    int GetNumExpNodes();
    const gbMixActInfo* GetMixInfo();
    int GetNumMixInfo();
    gbAABBox* GetCollideAABBox();
    void GetCollideOBB(gbOBBox& obb);

    // Material/texture control
    void SetCurMaterial(char* materialName);
    void EnableActionTransMtl(char* actionName, bool enable);

    gbActor& operator=(const gbActor& other);

    // Static methods
    static void SetSunDirection(gbVec3D* direction);

private:
    void UpdateExportNodes();

    gbActorDef* m_pActorDef;       // +0x58
    gbActionState* m_pActions;     // +0x60
    int m_numActions;              // +0x64
    gbExpNodeData* m_pExportNodeData; // +0x68
    int m_maxExportNodes;          // +0x70 (usually 4)
    char m_reserved[8];
};
