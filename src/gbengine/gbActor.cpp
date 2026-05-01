/**
 * gbengine.dll - gbActor
 * Character model with skeletal animation
 */

#include "gbengine/gbengine_types.h"
#include <cstring>
#include <cstdlib>

// Forward declarations
class gbActor;
class gbActorDef;
class gbAnimNodeGroup;
class gbEffectMgr;
class gbGfxManager;
class gbRenderEffect;
class gbResManager;
class gbResource;
class gbTexture;
class gbVisNode;
class gbVFileSystem;

// Global variables
extern gbGfxManager* g_pGfxManager;
extern gbVFileSystem* g_pVFileSys;

// Message structure
struct gbNodeMsgObj {
    int type;
    int data1;
    void* data2;
};

// Render info structure
struct gbRenderInfoObj {
    void* data;
};

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


/* ======== gbVisNode (base class layout for inheritance) ======== */

class gbVisNode {
public:
    virtual ~gbVisNode();
    virtual void Update();
    virtual void Render(gbRenderInfoObj* renderInfo);
    void PushMessage(gbNodeMsgObj& msg);
    virtual void EnableShadow(int enable);
    virtual void GetBoundSphere(gbSphere* sphere);
    virtual int Attach(gbRenderEffect* effect);
    virtual void Reset(float time);

    gbVisNode();

protected:
    void* vftable;
    char data[0x54];
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

// Static variable for sun direction
static gbVec3D s_sunDirection = {0.0f, -1.0f, 0.0f};

// Constructor from gbActorDef
gbActor::gbActor(gbActorDef* actorDef) : gbVisNode() {
    m_pActorDef = actorDef;
    m_pActions = nullptr;
    m_numActions = 0;
    m_pExportNodeData = nullptr;
    m_maxExportNodes = 4;

    // Get export node count from actor definition
    char buffer1[1008];
    char buffer2[1012];
    m_numActions = actorDef->GetNumExportNodes(buffer1, buffer2, 256);

    // Allocate action state array
    if (m_numActions > 0) {
        m_pActions = (gbActionState*)malloc(m_numActions * sizeof(gbActionState));

        for (int i = 0; i < m_numActions; i++) {
            m_pActions[i].state = 0;
            m_pActions[i].actionIndex = *((int*)&buffer1[i * 4 - 0xC]);
            m_pActions[i].endFrame = *((int*)&buffer2[i * 4 + 4]);
            m_pActions[i].weight = 0.0f;
            m_pActions[i].currentFrame = 0;
            m_pActions[i].startFrame = 0;
            m_pActions[i].eventData = nullptr;
        }
    }

    // Allocate export node matrix data (4 nodes, each with 2 matrices)
    m_maxExportNodes = 4;
    size_t exportDataSize = m_maxExportNodes * (sizeof(gbMatrix4) * 2 + 0x24);
    m_pExportNodeData = malloc(exportDataSize);

    if (m_pExportNodeData) {
        memset(m_pExportNodeData, 0, exportDataSize);

        // Initialize matrices to identity
        gbMatrix4* matrices = (gbMatrix4*)((char*)m_pExportNodeData + 0x44);
        for (int i = 0; i < m_maxExportNodes; i++) {
            // Initialize two matrices per node
            gbMatrix4* m1 = &matrices[i * 2];
            gbMatrix4* m2 = &matrices[i * 2 + 1];

            for (int r = 0; r < 4; r++) {
                for (int c = 0; c < 4; c++) {
                    m1->m[r][c] = (r == c) ? 1.0f : 0.0f;
                    m2->m[r][c] = (r == c) ? 1.0f : 0.0f;
                }
            }
        }
    }

    UpdateExportNodes();
}

// Copy constructor
gbActor::gbActor(const gbActor& other) : gbVisNode() {
    m_pActorDef = other.m_pActorDef;
    m_numActions = other.m_numActions;
    m_maxExportNodes = other.m_maxExportNodes;

    if (m_numActions > 0) {
        m_pActions = (gbActionState*)malloc(m_numActions * sizeof(gbActionState));
        memcpy(m_pActions, other.m_pActions, m_numActions * sizeof(gbActionState));
    } else {
        m_pActions = nullptr;
    }

    if (other.m_pExportNodeData) {
        size_t size = m_maxExportNodes * (sizeof(gbMatrix4) * 2 + 0x24);
        m_pExportNodeData = malloc(size);
        memcpy(m_pExportNodeData, other.m_pExportNodeData, size);
    } else {
        m_pExportNodeData = nullptr;
    }
}

// Destructor
gbActor::~gbActor() {
    if (m_pActions) {
        free(m_pActions);
        m_pActions = nullptr;
    }
    if (m_pExportNodeData) {
        free(m_pExportNodeData);
        m_pExportNodeData = nullptr;
    }
}

// Update export node transforms
void gbActor::UpdateExportNodes() {
    if (!m_pActorDef || !m_pExportNodeData) return;

    // Update export node matrices from skeleton
    // This would normally update attachment point transforms
}

// Update animation state
void gbActor::Update() {
    gbVisNode::Update();

    if (!m_pActorDef) return;

    // Get delta time from graphics manager
    float deltaTime = 0.016f;  // Default 60fps
    float scaledDelta = deltaTime * 2.0f;  // Scale factor for frame advancement

    float maxWeight = -100.0f;
    int dominantFrame = 0;
    gbActionState* dominantAction = nullptr;

    // Update all active actions
    for (int i = 0; i < m_numActions; i++) {
        gbActionState* action = &m_pActions[i];

        if (action->state == 0) continue;  // Inactive

        // Update blend weights
        if (action->state == 1) {  // Fade in
            action->weight += scaledDelta;
            if (action->weight > 1.0f) {
                action->weight = 1.0f;
            }
        } else if (action->state == 2) {  // Fade out
            action->weight -= scaledDelta;
            if (action->weight < 0.0f) {
                action->state = 0;
                action->weight = 0.0f;
            }
        }

        // Track dominant action
        if (action->weight > maxWeight) {
            maxWeight = action->weight;
            dominantFrame = action->currentFrame;
            dominantAction = action;
        }

        // Advance frame
        int prevFrame = action->currentFrame;
        action->currentFrame += (int)scaledDelta;

        // Handle looping
        if (action->startFrame == action->endFrame) {
            action->currentFrame = action->startFrame;
        } else if (action->startFrame < action->endFrame) {
            if (action->currentFrame >= (int)action->endFrame) {
                // Loop or stop
                int loopFrame = action->endFrame - 4;
                if (loopFrame < (int)action->startFrame) {
                    loopFrame = action->startFrame;
                }
                action->currentFrame = loopFrame;

                // Send action complete message
                if (action->eventData) {
                    gbNodeMsgObj msg;
                    msg.type = 1;
                    msg.data1 = i;
                    msg.data2 = this;
                    PushMessage(msg);
                }
            }
        }
    }

    // Update skeletal pose
    if (m_pActorDef) {
        m_pActorDef->UpdateBones(this);
    }

    // Send message if dominant action changed
    if (dominantAction) {
        gbNodeMsgObj msg;
        msg.type = 1;
        msg.data1 = (int)dominantAction;
        msg.data2 = this;
        PushMessage(msg);
    }
}

// Render actor
void gbActor::Render(gbRenderInfoObj* renderInfo) {
    // Rendering would be handled by submitting draw calls to D3D9
    // This is a stub for now
}

// Render shadow volume
void gbActor::RenderShadowVolume(gbRenderInfoObj* renderInfo) {
    // Shadow volume rendering
}

// Attach render effect
int gbActor::Attach(gbRenderEffect* effect) {
    // Attach effect to actor
    return 1;
}

// Reset animation state
void gbActor::Reset(float time) {
    for (int i = 0; i < m_numActions; i++) {
        m_pActions[i].state = 0;
        m_pActions[i].weight = 0.0f;
        m_pActions[i].currentFrame = m_pActions[i].startFrame;
    }
}

// Go to action (simple)
void gbActor::GotoAction(char* actionName, int loop) {
    // Find action by name and activate it
}

// Go to action with time range
void gbActor::GotoAction(char* actionName, float startTime, float endTime) {
    // Set action with specific time range
}

// Go to action with three names (blend)
void gbActor::GotoAction(char* action1, char* action2, char* action3) {
    // Set up action blending
}

// Go to action with raw parameters
void gbActor::GotoAction(unsigned long p1, int p2, unsigned int p3, unsigned int p4, unsigned long p5) {
    // Direct action setup
}

// Lock action blend weight
void gbActor::LockAction(char* actionName, float weight) {
    // Lock action at specific weight
}

// Unlock action
void gbActor::UnlockAction(char* actionName) {
    // Unlock action
}

// Get action duration in milliseconds
unsigned int gbActor::GetActionDuration(char* actionName) {
    return 0;
}

// Get event time for action
unsigned int gbActor::GetEventTime(char* actionName, char* eventName) {
    return 0;
}

// Get transform matrix for named tag node
int gbActor::GetTagNodeTM(gbMatrix4* matrix, char* tagName) {
    return 0;
}

// Enable/disable shadow casting
void gbActor::EnableShadow(int enable) {
    // Enable/disable shadow
}

// Get bounding sphere
void gbActor::GetBoundSphere(gbSphere* sphere) {
    if (sphere) {
        sphere->center.x = 0.0f;
        sphere->center.y = 0.0f;
        sphere->center.z = 0.0f;
        sphere->radius = 1.0f;
    }
}

// Get collision AABB
gbAABBox* gbActor::GetCollideAABBox() {
    return nullptr;
}

// Get collision OBB
void gbActor::GetCollideOBB(gbOBBox& obb) {
    memset(&obb, 0, sizeof(obb));
}

// Get all export nodes
gbActorExpNode* gbActor::GetAllExpNode() {
    return (gbActorExpNode*)m_pExportNodeData;
}

// Get number of export nodes
int gbActor::GetNumExpNodes() {
    return m_maxExportNodes;
}

// Get mix info array
const gbMixActInfo* gbActor::GetMixInfo() {
    return nullptr;
}

// Get number of mix infos
int gbActor::GetNumMixInfo() {
    return 0;
}

// Set current material
void gbActor::SetCurMaterial(char* materialName) {
    // Set material by name
}

// Enable action material transition
void gbActor::EnableActionTransMtl(char* actionName, bool enable) {
    // Enable/disable material transition for action
}

// Set sun direction for lighting
void gbActor::SetSunDirection(gbVec3D* direction) {
    if (direction) {
        s_sunDirection = *direction;
    }
}


/* ======== gbResManager (base class stub) ======== */

class gbResManager {
public:
    void* _resmgr_data[3];

    gbResManager();
    ~gbResManager();

    gbResource* FindResByName(const char* name);
    void AddResource(gbResource* res);
};

/* ======== gbActorMgr ======== */

class gbActorMgr : public gbResManager {
public:
    gbActorMgr(gbGfxManager* gfxMgr);
    gbActorMgr(const gbActorMgr& other);
    ~gbActorMgr();

    gbActor* LoadActorFile(char* filename);
    void DestroyActor(gbActor* actor);

private:
    gbGfxManager* m_pGfxManager;
    gbRenderEffect* m_pSkinShadowEffect1;
    gbRenderEffect* m_pSkinShadowEffect2;
};

// Constructor
gbActorMgr::gbActorMgr(gbGfxManager* gfxMgr) {
    m_pGfxManager = gfxMgr;
    m_pSkinShadowEffect1 = nullptr;
    m_pSkinShadowEffect2 = nullptr;

    // Load shadow effects
    // m_pSkinShadowEffect1 = LoadEffect("gfxscript/skinshadow1.gbf");
    // m_pSkinShadowEffect2 = LoadEffect("gfxscript/skinshadow2.gbf");
}

// Copy constructor
gbActorMgr::gbActorMgr(const gbActorMgr& other) {
    m_pGfxManager = other.m_pGfxManager;
    m_pSkinShadowEffect1 = other.m_pSkinShadowEffect1;
    m_pSkinShadowEffect2 = other.m_pSkinShadowEffect2;
}

// Destructor
gbActorMgr::~gbActorMgr() {
    // Release shadow effects
}

// Load actor from file
gbActor* gbActorMgr::LoadActorFile(char* filename) {
    if (!filename) return nullptr;

    // Check if already loaded
    gbResource* res = nullptr;  // FindResByName(filename);

    if (!res) {
        // Determine file type (.mv3 or .mv2)
        const char* ext = strrchr(filename, '.');
        if (!ext) return nullptr;

        // Load actor definition file
        // Open file and read header
        char header[256];
        memset(header, 0, sizeof(header));

        // Create appropriate actor definition based on file type
        gbActorDef* actorDef = nullptr;

        if (strstr(header, ".MV3.")) {
            // MV3 format
            actorDef = (gbActorDef*)malloc(0x108);
        } else {
            // MV2 format
            actorDef = (gbActorDef*)malloc(0xE0);
        }

        if (actorDef) {
            actorDef->LoadFromFile(filename);
            // SetName and AddResource
            res = (gbResource*)actorDef;
        }
    }

    // Create actor instance
    if (res) {
        gbActor* actor = new gbActor((gbActorDef*)res);
        return actor;
    }

    return nullptr;
}

// Destroy actor
void gbActorMgr::DestroyActor(gbActor* actor) {
    if (actor) {
        delete actor;
    }
}
