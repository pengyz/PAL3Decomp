/**
 * gbengine.dll - gbVisNode
 * Scene node base class implementation
 */

#include "gbengine/gbengine_types.h"
#include "gbengine/gbChain.h"
#include <string.h>
#include <stdlib.h>

// Forward declarations
class gbVisNode;
class gbRenderEffect;
class gbGfxManager;
class gbSceneGraph;


// Structs
struct gbRenderInfoObj;

struct gbNodeMsgObj {
    int data[4];  // 16 bytes message object
};

enum NodeBlend {
    BLEND_NONE = 0,
    BLEND_ALPHA = 1,
    BLEND_ADD = 2
};

/* ======== gbVisNode ======== */

class gbVisNode : public gbNBTreeNode {
public:
    gbNodeMsgObj* msgBuffer;     // +0x1c - message queue buffer
    int msgCapacity;             // +0x20 - message queue capacity (default 8)
    int msgUnused;               // +0x24 - unused field
    int msgOverflow;             // +0x28 - overflow flag
    int msgReadIndex;            // +0x2c - read index
    int msgWriteIndex;           // +0x30 - write index
    int renderPriority;          // +0x34
    float timeScale;             // +0x38 - time scale (default 1.0)
    int visible;                 // +0x3c - visibility flag (default 1)
    gbVisNode* cullNext;         // +0x40 - cull list next
    gbVisNode* cullPrev;         // +0x44 - cull list prev
    void* unknown48;             // +0x48
    void* unknown4c;             // +0x4c
    float blendValue;            // +0x50 - blend value
    NodeBlend blendMode;         // +0x54 - blend mode

    // Static members
    static gbGfxManager* pGfxMgr;
    static gbSceneGraph* pSceneGraph;

    gbVisNode();
    gbVisNode(const gbVisNode& other);
    virtual ~gbVisNode();

    void PushMessage(gbNodeMsgObj& msg);
    int PopMessage(gbNodeMsgObj& msg);
    virtual int Attach(gbRenderEffect* effect);
    virtual void AttachSelf(gbRenderEffect* effect);
    virtual void Render(gbRenderInfoObj* renderInfo);
    virtual void RenderShadowVolume(gbRenderInfoObj* renderInfo);
    virtual void Update();
    virtual void Reset(float time);
    void ShowNode(int show);
    void SetTimeScale(float scale);
    float GetTimeScale();
    int IsNodeShow();
    int GetRenderPriority();
    void SetRenderPriority(int priority);
    gbVisNode* GetCullNext();
    gbVisNode* GetCullPrev();
    virtual void GetBoundSphere(gbSphere* sphere);
    virtual void EnableShadow(int enable);
    void SetBlend(NodeBlend mode, float value);
    NodeBlend GetBlend(float& outValue);
    void SetBlendRecursive(NodeBlend mode, float value);
    void GetTotalBoundSphere(gbSphere* sphere);
    virtual int GetAABBox(gbAABBox* box);

    gbVisNode& operator=(const gbVisNode& other);
};

// Static members
gbGfxManager* gbVisNode::pGfxMgr = NULL;
gbSceneGraph* gbVisNode::pSceneGraph = NULL;

// Constructor - 0x10016590
gbVisNode::gbVisNode() {
    // Base class gbChain1DNode constructor called first (vtable set)
    // Then gbNBTreeNode fields initialized
    pParent = NULL;

    // Initialize gbChain1D for children
    children.pHead = NULL;
    children.pTail = NULL;
    children.nCount = 0;
    children.pIterator = NULL;

    // gbVisNode fields
    msgOverflow = 1;
    msgUnused = 0;
    msgCapacity = 8;
    msgBuffer = (gbNodeMsgObj*)operator new(128);  // 8 * 16 bytes
    msgReadIndex = 0;
    msgWriteIndex = 0;
    renderPriority = 0;
    cullNext = NULL;
    cullPrev = NULL;
    unknown4c = NULL;
    unknown48 = NULL;
    renderPriority = 0;

    // vtable updated to gbVisNode
    timeScale = 1.0f;
    visible = 1;
}

// Copy constructor - 0x10004a60
gbVisNode::gbVisNode(const gbVisNode& other) : gbNBTreeNode() {
    // Copy gbChain1DNode fields
    pNext = other.pNext;

    // Copy gbNBTreeNode fields
    pParent = other.pParent;
    children = other.children;
    pChildIterator = other.pChildIterator;

    // Copy gbVisNode fields
    // Copy 6 dwords starting at +0x1c
    msgBuffer = other.msgBuffer;
    msgCapacity = other.msgCapacity;
    msgUnused = other.msgUnused;
    msgOverflow = other.msgOverflow;
    msgReadIndex = other.msgReadIndex;
    msgWriteIndex = other.msgWriteIndex;

    renderPriority = other.renderPriority;
    timeScale = other.timeScale;
    visible = other.visible;
    cullNext = other.cullNext;
    cullPrev = other.cullPrev;
    unknown48 = other.unknown48;
    unknown4c = other.unknown4c;
    blendValue = other.blendValue;
    blendMode = other.blendMode;
}

// Destructor - 0x100049c0
gbVisNode::~gbVisNode() {
    // vtable set to gbVisNode

    // Free message buffer
    operator delete(msgBuffer);

    // vtable set to gbNBTreeNode

    // Destroy children chain
    // gbChain1D destructor called

    // gbChain1DNode destructor called
}

// PushMessage - 0x10016640
void gbVisNode::PushMessage(gbNodeMsgObj& msg) {
    int writeIdx = msgWriteIndex;
    int nextWrite = writeIdx + 1;

    if (nextWrite == msgCapacity) {
        nextWrite = 0;
    }

    int readIdx = msgReadIndex;

    if (nextWrite == readIdx) {
        if (msgOverflow != 0) {
            return;  // Queue full, drop message
        }

        // Advance read index if not at write
        if (readIdx != writeIdx) {
            readIdx++;
            if (readIdx == msgCapacity) {
                readIdx = 0;
            }
            msgReadIndex = readIdx;
        }
    }

    // Copy message to buffer
    gbNodeMsgObj* slot = &msgBuffer[writeIdx];
    slot->data[0] = msg.data[0];
    slot->data[1] = msg.data[1];
    slot->data[2] = msg.data[2];
    slot->data[3] = msg.data[3];

    msgWriteIndex = nextWrite;
}

// PopMessage - 0x100166a0
int gbVisNode::PopMessage(gbNodeMsgObj& msg) {
    if (msgReadIndex == msgWriteIndex) {
        return 0;  // Queue empty
    }

    // Copy message from buffer
    gbNodeMsgObj* slot = &msgBuffer[msgReadIndex];
    msg.data[0] = slot->data[0];
    msg.data[1] = slot->data[1];
    msg.data[2] = slot->data[2];
    msg.data[3] = slot->data[3];

    // Advance read index
    int nextRead = msgReadIndex + 1;
    if (nextRead == msgCapacity) {
        nextRead = 0;
    }
    msgReadIndex = nextRead;

    return 1;
}

// Attach - 0x100166f0 (virtual, base implementation does nothing)
int gbVisNode::Attach(gbRenderEffect* effect) {
    return 0;
}

// Update - 0x10016730 (virtual)
void gbVisNode::Update() {
    // Iterate through children and call Update on each
    gbVisNode* child = (gbVisNode*)children.pHead;
    pChildIterator = (gbNBTreeNode*)child;

    while (child != NULL) {
        // Call virtual Update through vtable
        void** vtable = *(void***)child;
        typedef void (__thiscall *UpdateFunc)(gbVisNode*);
        UpdateFunc updateFunc = (UpdateFunc)vtable[5];  // Update is at vtable+0x14
        updateFunc(child);

        child = (gbVisNode*)pChildIterator->pNext;
        pChildIterator = (gbNBTreeNode*)child;
    }
}

// Reset - 0x10016760 (virtual, base implementation does nothing)
void gbVisNode::Reset(float time) {
    // Base implementation is empty
}

// ShowNode - 0x10016790
void gbVisNode::ShowNode(int show) {
    visible = show;

    // Recursively apply to children
    gbVisNode* child = (gbVisNode*)children.pHead;
    pChildIterator = (gbNBTreeNode*)child;

    while (child != NULL) {
        child->ShowNode(show);
        child = (gbVisNode*)pChildIterator->pNext;
        pChildIterator = (gbNBTreeNode*)child;
    }
}

// SetTimeScale - 0x100167c0
void gbVisNode::SetTimeScale(float scale) {
    timeScale = scale;

    // Recursively apply to children
    gbVisNode* child = (gbVisNode*)children.pHead;
    pChildIterator = (gbNBTreeNode*)child;

    while (child != NULL) {
        child->SetTimeScale(scale);
        child = (gbVisNode*)pChildIterator->pNext;
        pChildIterator = (gbNBTreeNode*)child;
    }
}

// AttachSelf - virtual
void gbVisNode::AttachSelf(gbRenderEffect* effect) {
    // Base implementation does nothing
}

// Render - virtual
void gbVisNode::Render(gbRenderInfoObj* renderInfo) {
    // Base implementation does nothing
}

// RenderShadowVolume - virtual
void gbVisNode::RenderShadowVolume(gbRenderInfoObj* renderInfo) {
    // Base implementation does nothing
}

// GetTimeScale
float gbVisNode::GetTimeScale() {
    return timeScale;
}

// IsNodeShow
int gbVisNode::IsNodeShow() {
    return visible;
}

// GetRenderPriority
int gbVisNode::GetRenderPriority() {
    return renderPriority;
}

// SetRenderPriority - 0x100167f0
void gbVisNode::SetRenderPriority(int priority) {
    renderPriority = priority;
}

// GetCullNext
gbVisNode* gbVisNode::GetCullNext() {
    return cullNext;
}

// GetCullPrev
gbVisNode* gbVisNode::GetCullPrev() {
    return cullPrev;
}

// GetBoundSphere - 0x10016820 (virtual, base implementation does nothing)
void gbVisNode::GetBoundSphere(gbSphere* sphere) {
    // Base implementation does nothing
}

// EnableShadow - 0x10016830 (virtual, base implementation does nothing)
void gbVisNode::EnableShadow(int enable) {
    // Base implementation does nothing
}

// SetBlend - 0x10016840
void gbVisNode::SetBlend(NodeBlend mode, float value) {
    blendMode = mode;
    blendValue = value;
}

// GetBlend - 0x10016860
NodeBlend gbVisNode::GetBlend(float& outValue) {
    outValue = blendValue;
    return blendMode;
}

// SetBlendRecursive - 0x10016870
void gbVisNode::SetBlendRecursive(NodeBlend mode, float value) {
    SetBlend(mode, value);

    // Recursively apply to children
    gbVisNode* child = (gbVisNode*)children.pHead;
    pChildIterator = (gbNBTreeNode*)child;

    while (child != NULL) {
        child->SetBlendRecursive(mode, value);
        child = (gbVisNode*)pChildIterator->pNext;
        pChildIterator = (gbNBTreeNode*)child;
    }
}

// GetTotalBoundSphere - 0x100168b0
void gbVisNode::GetTotalBoundSphere(gbSphere* sphere) {
    // Complex implementation - stub for now
    // This calculates the bounding sphere encompassing this node and all children
}

// GetAABBox - 0x10016b90 (virtual)
int gbVisNode::GetAABBox(gbAABBox* box) {
    return 0;  // Base implementation returns 0
}

// operator= - 0x10004af0
gbVisNode& gbVisNode::operator=(const gbVisNode& other) {
    if (this != &other) {
        // Copy all fields
        pNext = other.pNext;
        pParent = other.pParent;
        children = other.children;
        pChildIterator = other.pChildIterator;
        msgBuffer = other.msgBuffer;
        msgCapacity = other.msgCapacity;
        msgUnused = other.msgUnused;
        msgOverflow = other.msgOverflow;
        msgReadIndex = other.msgReadIndex;
        msgWriteIndex = other.msgWriteIndex;
        renderPriority = other.renderPriority;
        timeScale = other.timeScale;
        visible = other.visible;
        cullNext = other.cullNext;
        cullPrev = other.cullPrev;
        unknown48 = other.unknown48;
        unknown4c = other.unknown4c;
        blendValue = other.blendValue;
        blendMode = other.blendMode;
    }
    return *this;
}
