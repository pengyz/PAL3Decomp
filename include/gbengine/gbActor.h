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

// Actor export node (attachment points)
struct gbActorExpNode {
    int flags;
    int nodeIndex;
    float weight;
    int startFrame;
    int endFrame;
    char name[32];
};

// Mix action info (animation blending)
struct gbMixActInfo {
    int fromAction;
    int toAction;
    int mixDuration;
};

// Actor action state
struct gbActionState {
    int state;          // 0=inactive, 1=fade-in, 2=fade-out
    int actionIndex;    // Current action
    float weight;       // Blend weight
    int currentFrame;   // Current frame
    int startFrame;     // Start frame
    int endFrame;       // End frame
    char* eventData;    // Event data
    int reserved[3];
};


/* ======== gbActorDef (resource) ======== */

class gbActorDef {
public:
    virtual ~gbActorDef() {}
    virtual void LoadFromFile(const char* filename) = 0;
    virtual int GetNumExportNodes(char* buffer1, char* buffer2, int maxNodes) = 0;
    virtual void UpdateBones(gbActor* actor) = 0;
    virtual int GetEventList(void* buffer, int fromFrame, int toFrame, void* eventData) = 0;

    void* vftable;
    char data[0x100];
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
    void* m_pExportNodeData;       // +0x68
    int m_maxExportNodes;          // +0x70 (usually 4)
    char m_reserved[8];
};
