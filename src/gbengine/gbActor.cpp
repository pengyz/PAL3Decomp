/**
 * gbengine.dll - gbActor
 * Character model with skeletal animation
 */

#include "gbengine/gbActor.h"
#include "gbengine/gbMisc.h"
#include "gbengine/gbGfxManager_impl.h"
#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbengine_internal.h"
#include <cstring>
#include <cstdlib>

#pragma warning(disable: 4234)

// Global variables
extern gbGfxManager* g_pGfxManager;
extern gbVFileSystem* g_pVFileSys;

// Animation frame rate conversion factor (seconds to frame ticks)
static const float ANIM_FRAME_RATE = 4800.0f;

// Static variable for sun direction
static gbVec3D s_sunDirection(0.0f, -1.0f, 0.0f);

// Constructor from gbActorDef
gbActor::gbActor(gbActorDef* actorDef) : gbVisNode() {
    m_pActorDef = actorDef;
    m_field_5C = 0;
    m_pActions = NULL;
    m_numActions = 0;
    m_pExportNodeData = NULL;
    m_numExportNodes = 0;
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
            m_pActions[i].actionCrc = *((unsigned int*)&buffer1[i * 4 - 0xC]);
            m_pActions[i].endFrame = *((int*)&buffer2[i * 4 + 4]);
            m_pActions[i].weight = 0.0f;
            m_pActions[i].currentFrame = 0;
            m_pActions[i].startFrame = 0;
            m_pActions[i].eventData = NULL;
        }
    }

    // Allocate export node data (4 nodes, each 0x84 bytes = sizeof(gbExpNodeData))
    m_maxExportNodes = 4;
    size_t exportDataSize = m_maxExportNodes * sizeof(gbExpNodeData);
    m_pExportNodeData = (gbExpNodeData*)malloc(exportDataSize);

    if (m_pExportNodeData) {
        memset(m_pExportNodeData, 0, exportDataSize);

        // Initialize matrices to identity (per Ghidra: calls gbMatrix4 constructor on each)
        for (int i = 0; i < m_maxExportNodes; i++) {
            m_pExportNodeData[i].localMatrix.LoadIdentity();
            m_pExportNodeData[i].worldMatrix.LoadIdentity();
        }
    }

    UpdateExportNodes();
}

// Copy constructor
gbActor::gbActor(const gbActor& other) : gbVisNode() {
    m_pActorDef = other.m_pActorDef;
    m_field_5C = other.m_field_5C;
    m_numActions = other.m_numActions;
    m_numExportNodes = other.m_numExportNodes;
    m_maxExportNodes = other.m_maxExportNodes;

    if (m_numActions > 0) {
        m_pActions = (gbActionState*)malloc(m_numActions * sizeof(gbActionState));
        memcpy(m_pActions, other.m_pActions, m_numActions * sizeof(gbActionState));
    } else {
        m_pActions = NULL;
    }

    if (other.m_pExportNodeData) {
        size_t size = m_maxExportNodes * sizeof(gbExpNodeData);
        m_pExportNodeData = (gbExpNodeData*)malloc(size);
        memcpy(m_pExportNodeData, other.m_pExportNodeData, size);
    } else {
        m_pExportNodeData = NULL;
    }
}

// Destructor
gbActor::~gbActor() {
    if (m_pActions) {
        free(m_pActions);
        m_pActions = NULL;
    }
    if (m_pExportNodeData) {
        free(m_pExportNodeData);
        m_pExportNodeData = NULL;
    }
}

// Update export node transforms - 0x10002cd0 (256 bytes)
void gbActor::UpdateExportNodes() {
    unsigned int crcBuffer[256];

    // Call actorDef vtable[11] (offset 44): get export node CRCs
    void** defVtable = *(void***)m_pActorDef;
    typedef int (__thiscall *GetExportCRCsFn)(void*, unsigned int*, int);
    GetExportCRCsFn getExportCRCs = (GetExportCRCsFn)defVtable[44 / 4];
    int numNodes = getExportCRCs(m_pActorDef, crcBuffer, 256);

    // Reallocate if count exceeds capacity
    if (numNodes > m_maxExportNodes) {
        if (m_pExportNodeData)
            operator delete(m_pExportNodeData);

        m_maxExportNodes = numNodes;
        char* mem = (char*)operator new(132 * numNodes);
        if (mem) {
            for (int i = 0; i < numNodes; i++) {
                gbMatrix4* local = (gbMatrix4*)(mem + i * 132 + 4);
                gbMatrix4* world = (gbMatrix4*)(mem + i * 132 + 68);
                local->LoadIdentity();
                world->LoadIdentity();
            }
        } else {
            mem = 0;
        }
        m_pExportNodeData = (gbExpNodeData*)mem;
    }

    // Fill CRC names and init matrices
    if (numNodes > 0) {
        for (int i = 0; i < numNodes; i++) {
            m_pExportNodeData[i].nameCrc = crcBuffer[i];
            m_pExportNodeData[i].localMatrix.LoadIdentity();
        }
    }

    m_numExportNodes = numNodes;
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
    gbActionState* dominantAction = NULL;

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
                    msg.data[0] = 1;
                    msg.data[1] = i;
                    msg.data[2] = (int)this;
                    PushMessage(msg);
                }
            }
        }
    }

    // Update skeletal pose
    if (m_pActorDef) {
        m_pActorDef->UpdateBones();
    }

    // Send message if dominant action changed
    if (dominantAction) {
        gbNodeMsgObj msg;
        msg.data[0] = 1;
        msg.data[1] = (int)dominantAction;
        msg.data[2] = (int)this;
        PushMessage(msg);
    }
}

void gbActor::Render(gbRenderInfoObj* renderInfo) {
    gbMatrixStack* matStack = gbVisNode::pGfxMgr->pMatrixStack[1];
    matStack->Push();
    matStack->LoadMatrix(&renderInfo->worldMatrix);
    m_pActorDef->RenderDef(this, renderInfo);
    matStack->Pop();
}

void gbActor::RenderShadowVolume(gbRenderInfoObj* renderInfo) {
    gbMatrixStack* matStack = gbVisNode::pGfxMgr->pMatrixStack[1];
    matStack->Push();
    matStack->LoadMatrix(&renderInfo->worldMatrix);
    m_pActorDef->RenderShadowVolumeDef(this, renderInfo);
    matStack->Pop();
}

// Attach render effect
int gbActor::Attach(gbRenderEffect* effect) {
    gbAABBox* aabb = m_pActorDef->GetCollideAABBox();
    if (gbVisNode::pGfxMgr->ClipBoundVolume(aabb)) {
        return 0;
    }
    m_pActorDef->AttachSelf(this, effect);
    if (enableShadow) {
        gbVisNode::pGfxMgr->pSceneGraph->NewShadowVolume((gbVisNode*)this);
    }
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
    GotoAction(gbCrc32Compute(actionName), loop, 1, 0, 0x6f766572);
}

// Go to action with time range (converts time to frame indices)
void gbActor::GotoAction(char* actionName, float startTime, float endTime) {
    GotoAction(gbCrc32Compute(actionName), 2, (unsigned int)(startTime * 4800.0f), (unsigned int)(endTime * 4800.0f), 0x6f766572);
}

// Go to action with three names (action + start marker + end marker)
void gbActor::GotoAction(char* action1, char* action2, char* action3) {
    if (!m_pActorDef) return;

    unsigned int crc = gbCrc32Compute(action1);

    // Find action index by CRC
    int actionIdx = 0;
    if (m_numActions > 0) {
        while (m_pActions[actionIdx].actionCrc != crc) {
            actionIdx++;
            if (actionIdx >= m_numActions) break;
        }
    }

    // Resolve start marker to frame number via actorDef vtable[0x44]
    unsigned int startFrame = 0;
    if (action2 != NULL) {
        void** defVtable = *(void***)m_pActorDef;
        typedef unsigned int (__thiscall *GetMarkerFn)(void*, unsigned int, int);
        GetMarkerFn getMarker = (GetMarkerFn)((void**)defVtable)[0x44 / 4];
        unsigned int crc2 = gbCrc32Compute(action2);
        startFrame = getMarker(m_pActorDef, crc2, actionIdx);
    }

    // Resolve end marker to frame number
    unsigned int endFrame;
    unsigned long transition;
    if (action3 != NULL) {
        unsigned int crc3 = gbCrc32Compute(action3);
        void** defVtable = *(void***)m_pActorDef;
        typedef unsigned int (__thiscall *GetMarkerFn)(void*, unsigned int, int);
        GetMarkerFn getMarker = (GetMarkerFn)((void**)defVtable)[0x44 / 4];
        endFrame = getMarker(m_pActorDef, crc3, actionIdx);
        if (endFrame != 0) {
            transition = endFrame;
            goto doGoto;
        }
        // Log warning if marker not found
        char* defName = m_pActorDef->pName;
        gbLogInfo((char*)"  Action msg not find actor:%s action:%s event:%s\n", defName, action1, action3);
    }

    // Fallback: get total duration via actorDef vtable[0x8]
    {
        void** defVtable = *(void***)m_pActorDef;
        typedef unsigned int (__thiscall *GetDurationFn)(void*, char*);
        GetDurationFn getDuration = (GetDurationFn)((void**)defVtable)[0x8 / 4];
        endFrame = getDuration(m_pActorDef, action1);
        transition = 0x6f766572;
    }

doGoto:
    GotoAction(crc, 2, startFrame, endFrame, transition);
}

// Go to action with raw parameters (core implementation)
void gbActor::GotoAction(unsigned long actionCrc, int loop, unsigned int startFrame, unsigned int endFrame, unsigned long transition) {
    if (!m_pActorDef) return;

    // Call actorDef vtable[0x38] - prepare for action change
    void** defVtable = *(void***)m_pActorDef;
    typedef void (__thiscall *PrepareFn)(void*);
    PrepareFn prepare = (PrepareFn)((void**)defVtable)[0x38 / 4];
    prepare(m_pActorDef);

    int actionIdx = 0;
    for (int i = 0; i < m_numActions; i++) {
        gbActionState* action = &m_pActions[i];

        if (action->actionCrc == actionCrc) {
            action->state = 1;
            action->weight = 1.0f;

            if (endFrame < startFrame) {
                action->currentFrame = 0;
            } else {
                action->currentFrame = startFrame;
            }
            action->startFrame = startFrame;
            action->endFrame = endFrame;
            action->transition = transition;
            action->loopFlag = 1;

            // Call actorDef vtable[0x48] - set active action
            typedef void (__thiscall *SetActiveFn)(void*, int);
            SetActiveFn setActive = (SetActiveFn)((void**)defVtable)[0x48 / 4];
            setActive(m_pActorDef, actionIdx);

            UpdateExportNodes();
        } else {
            action->state = 0;
            action->weight = 0.0f;
        }
        actionIdx++;
    }
}

// Lock action blend weight
void gbActor::LockAction(char* actionName, float weight) {
    unsigned int crc = gbCrc32Compute(actionName);
    for (int i = 0; i < m_numActions; i++) {
        if (m_pActions[i].actionCrc == crc) {
            m_pActions[i].state = 3;
            m_pActions[i].weight = weight;
            return;
        }
    }
}

// Unlock action (set to fade-out state)
void gbActor::UnlockAction(char* actionName) {
    unsigned int crc = gbCrc32Compute(actionName);
    for (int i = 0; i < m_numActions; i++) {
        if (m_pActions[i].actionCrc == crc) {
            m_pActions[i].state = 2;
            return;
        }
    }
}

// Get action duration - thunk to actorDef vtable[2] (offset 0x8)
unsigned int gbActor::GetActionDuration(char* actionName) {
    return m_pActorDef->GetActionDuration(actionName);
}

// Get event time for action - find action by CRC, then query actorDef
unsigned int gbActor::GetEventTime(char* actionName, char* eventName) {
    if (!m_pActorDef) return 0xFFFFFFFF;

    unsigned int actionCrc = gbCrc32Compute(actionName);
    unsigned int eventCrc = gbCrc32Compute(eventName);

    for (int i = 0; i < m_numActions; i++) {
        if (m_pActions[i].actionCrc == actionCrc) {
            void** defVtable = *(void***)m_pActorDef;
            typedef unsigned int (__thiscall *GetEventFn)(void*, unsigned int, int);
            GetEventFn getEvent = (GetEventFn)((void**)defVtable)[0x44 / 4];
            return getEvent(m_pActorDef, eventCrc, i);
        }
    }
    return 0xFFFFFFFF;
}

// Get transform matrix for named tag node (export node lookup)
int gbActor::GetTagNodeTM(gbMatrix4* matrix, char* tagName) {
    if (!m_pExportNodeData) return 0;

    unsigned int crc = gbCrc32Compute(tagName);
    int numNodes = m_maxExportNodes;

    for (int i = 0; i < numNodes; i++) {
        if (m_pExportNodeData[i].nameCrc == crc) {
            *matrix = m_pExportNodeData[i].localMatrix;
            return 1;
        }
    }
    return 0;
}

// Enable/disable shadow casting
void gbActor::EnableShadow(int enable) {
    gbVisNode::EnableShadow(enable);
    if (enable != 0) {
        m_pActorDef->UpdateBones();
    }
}

// Get bounding sphere - calls actorDef vtable[8] (offset 0x20) and copies
void gbActor::GetBoundSphere(gbSphere* sphere) {
    gbSphere* src = m_pActorDef->GetBoundSpherePtr();
    *(unsigned int*)((char*)sphere + 0) = *(unsigned int*)((char*)src + 0);
    *(unsigned int*)((char*)sphere + 4) = *(unsigned int*)((char*)src + 4);
    *(unsigned int*)((char*)sphere + 8) = *(unsigned int*)((char*)src + 8);
    *(unsigned int*)((char*)sphere + 12) = *(unsigned int*)((char*)src + 12);
}

// Get collision AABB - thunk: MOV ECX,[ECX+58]; MOV EAX,[ECX]; JMP [EAX+24]
gbAABBox* gbActor::GetCollideAABBox() {
    return m_pActorDef->GetCollideAABBox();
}

// Get collision OBB - thunk to actorDef vtable[7] (offset 0x1C)
void gbActor::GetCollideOBB(gbOBBox& obb) {
    m_pActorDef->GetCollideOBB(&obb, this);
}

// Get all export nodes (returns raw pointer to internal data)
gbActorExpNode* gbActor::GetAllExpNode() {
    return (gbActorExpNode*)(void*)m_pExportNodeData;
}

// Get number of export nodes - returns actual count at +0x6C
int gbActor::GetNumExpNodes() {
    return m_numExportNodes;
}

// Get mix info array - returns m_pActions reinterpreted
const gbMixActInfo* gbActor::GetMixInfo() {
    return (const gbMixActInfo*)m_pActions;
}

int gbActor::GetNumMixInfo() {
    return m_numActions;
}

// Set current material - thunk to actorDef vtable[15] (offset 0x3C)
void gbActor::SetCurMaterial(char* materialName) {
    m_pActorDef->SetCurMaterial(materialName);
}

// Enable action material transition - find action then delegate to actorDef vtable[0x4]
void gbActor::EnableActionTransMtl(char* actionName, bool enable) {
    if (!m_pActorDef) return;

    unsigned int crc = gbCrc32Compute(actionName);
    for (int i = 0; i < m_numActions; i++) {
        if (m_pActions[i].actionCrc == crc) {
            void** defVtable = *(void***)m_pActorDef;
            typedef void (__thiscall *EnableTransFn)(void*, int, bool);
            EnableTransFn enableTrans = (EnableTransFn)((void**)defVtable)[0x4 / 4];
            enableTrans(m_pActorDef, i, enable);
            return;
        }
    }
}

// Set sun direction for lighting
void gbActor::SetSunDirection(gbVec3D* direction) {
    int* dst = (int*)&s_sunDirection;
    int* src = (int*)direction;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    s_sunDirection.Normalize();
}

// 0x10005190 - operator= (163B)
gbActor& gbActor::operator=(const gbActor& other) {
    m_pActorDef = other.m_pActorDef;
    m_field_5C = other.m_field_5C;
    m_pActions = other.m_pActions;
    m_numActions = other.m_numActions;
    m_pExportNodeData = other.m_pExportNodeData;
    m_numExportNodes = other.m_numExportNodes;
    memcpy(&m_maxExportNodes, &other.m_maxExportNodes, 0x58u);
    return *this;
}


/* gbResManager definition is in gbengine_internal.h */

/* ======== gbActorMgr ======== */

class gbActorMgr : public gbResManager {
public:
    gbActorMgr(gbGfxManager* gfxMgr);
    gbActorMgr(const gbActorMgr& other);
    ~gbActorMgr();

    gbActorMgr& operator=(const gbActorMgr& other);

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
    m_pSkinShadowEffect1 = NULL;
    m_pSkinShadowEffect2 = NULL;

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
}

// operator=
gbActorMgr& gbActorMgr::operator=(const gbActorMgr& other) {
    if (this != &other) {
        m_pGfxManager = other.m_pGfxManager;
        m_pSkinShadowEffect1 = other.m_pSkinShadowEffect1;
        m_pSkinShadowEffect2 = other.m_pSkinShadowEffect2;
    }
    return *this;
}

// Load actor from file
gbActor* gbActorMgr::LoadActorFile(char* filename) {
    if (!filename) return NULL;

    // Check if already loaded
    gbResource* res = NULL;  // FindResByName(filename);

    if (!res) {
        // Determine file type (.mv3 or .mv2)
        const char* ext = strrchr(filename, '.');
        if (!ext) return NULL;

        // Load actor definition file
        // Open file and read header
        char header[256];
        memset(header, 0, sizeof(header));

        // Create appropriate actor definition based on file type
        gbActorDef* actorDef = NULL;

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

    return NULL;
}

// Destroy actor
void gbActorMgr::DestroyActor(gbActor* actor) {
    if (actor) {
        delete actor;
    }
}
