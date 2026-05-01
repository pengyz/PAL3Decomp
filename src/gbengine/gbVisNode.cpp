/**
 * gbengine.dll - gbVisNode
 * Scene node base class implementation
 */

#include "gbengine/gbVisNode.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

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
    (void)0;
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
    (void)0;
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
    (void)0;
}

// Render - virtual
void gbVisNode::Render(gbRenderInfoObj* renderInfo) {
    (void)0;
}

// RenderShadowVolume - virtual
void gbVisNode::RenderShadowVolume(gbRenderInfoObj* renderInfo) {
    (void)0;
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
    (void)0;
}

// EnableShadow - 0x10016830 (virtual)
void gbVisNode::EnableShadow(int enable) {
    // Ghidra: *(int*)(this + 0x40) = param_1
    // Offset 0x40 = cullNext field (reused as shadow enable flag in base class)
    cullNext = (gbVisNode*)(intptr_t)enable;
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

// GetTotalBoundSphere - 0x100168b0 (722B)
void gbVisNode::GetTotalBoundSphere(gbSphere* sphere) {
    GetBoundSphere(sphere);

    int childCount = *(int*)((char*)this + 0x14);
    for (int i = 0; i < childCount; i++) {
        gbChain1DNode* childNode = ((gbChain1D*)((char*)this + 0x0c))->operator[](i);
        if (!childNode) continue;

        gbSphere childSphere;
        childSphere.radius = 0.0f;
        childSphere.center.x = childSphere.center.y = childSphere.center.z = 0.0f;

        void** childVtable = *(void***)childNode;
        typedef void (__thiscall *GetBoundSphereFn)(void*, gbSphere*);
        GetBoundSphereFn getBound = (GetBoundSphereFn)childVtable[7];
        getBound(childNode, &childSphere);

        if (childSphere.radius == 0.0f) continue;

        if (sphere->radius == 0.0f) {
            *sphere = childSphere;
        } else {
            float dx = sphere->center.x - childSphere.center.x;
            float dy = sphere->center.y - childSphere.center.y;
            float dz = sphere->center.z - childSphere.center.z;
            float dist = sqrtf(dx * dx + dy * dy + dz * dz);

            if (dist == 0.0f) {
                if (sphere->radius < childSphere.radius) {
                    sphere->radius = childSphere.radius;
                }
            } else {
                float invDist = 1.0f / dist;
                dx *= invDist;
                dy *= invDist;
                dz *= invDist;

                float p1x = childSphere.center.x - dx * childSphere.radius;
                float p1y = childSphere.center.y - dy * childSphere.radius;
                float p1z = childSphere.center.z - dz * childSphere.radius;

                float p2x = sphere->center.x + dx * sphere->radius;
                float p2y = sphere->center.y + dy * sphere->radius;
                float p2z = sphere->center.z + dz * sphere->radius;

                float cx = (p1x + p2x) * 0.5f;
                float cy = (p1y + p2y) * 0.5f;
                float cz = (p1z + p2z) * 0.5f;

                sphere->center.x = cx;
                sphere->center.y = cy;
                sphere->center.z = cz;

                float ex = p2x - p1x;
                float ey = p2y - p1y;
                float ez = p2z - p1z;
                sphere->radius = sqrtf(ex * ex + ey * ey + ez * ez) * 0.5f;
            }
        }
    }
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


// ============================================================
// Additional export implementations
// ============================================================

#pragma optimize("", off)
#pragma auto_inline(off)

// Class definitions needed for moved functions
class gbVolModNode {
public:
    char _base_visnode[0x58];       // base class data (gbChain1DNode + gbNBTreeNode + gbVisNode)
    gbMatrix4 localMatrix;          // +0x58: local transform matrix
    gbMatrix4 worldMatrix;          // +0x98: world transform matrix
    void* pVolMod;                  // +0xD8: gbVolumeModifier pointer (ref-counted)

public:
    gbVolModNode(class gbVolModNode const & p0);
    gbVolModNode();
    virtual ~gbVolModNode();
    class gbVolModNode & operator=(class gbVolModNode const & p0);
    virtual int Attach(class gbRenderEffect * p0);
    virtual void GetBoundSphere(struct gbSphere * p0);
    class gbLightObj * GetLightObj();
    virtual void Render(struct gbRenderInfoObj * p0);
    void SetVolModObj(class gbVolumeModifier * p0);
};

class gbVolumeModifier {
public:
    char _stub_data[128];

public:
    gbVolumeModifier(class gbVolumeModifier const & p0);

public:
    gbVolumeModifier();

public:
    virtual ~gbVolumeModifier();

public:
    class gbVolumeModifier & operator=(class gbVolumeModifier const & p0);

};

// ---- gbVolModNode ----
gbVolModNode::gbVolModNode(class gbVolModNode const & p0) {
    // Copy constructor: memcpy entire object (per Ghidra at 0x10005700)
    memcpy(this, &p0, sizeof(gbVolModNode));
}

gbVolModNode::gbVolModNode() {
    // Default constructor per Ghidra at 0x10013040:
    // Base class gbVisNode constructed first (by compiler)
    // Initialize the two matrices and volume modifier pointer
    localMatrix.LoadIdentity();
    // worldMatrix is default-constructed by gbMatrix4 ctor
    pVolMod = 0;
}

class gbVolModNode & gbVolModNode::operator=(class gbVolModNode const & p0) {
    if (this != &p0) {
        memcpy(this, &p0, sizeof(gbVolModNode));
    }
    return *this;
}

int gbVolModNode::Attach(class gbRenderEffect * p0) {
    // From Ghidra (Attach at 0x10013190):
    // 1. Call base gbVisNode::Attach
    // 2. Copy localMatrix to worldMatrix
    // 3. Right-multiply worldMatrix by GfxMgr matrix stack top
    // 4. Notify volume modifier
    // 5. Add to scene graph vol mod list
    // 6. Return 1

    // Copy local to world matrix
    memcpy(&worldMatrix, &localMatrix, sizeof(gbMatrix4));

    // Notify the volume modifier (vtable[4] = SetNode)
    if (pVolMod != 0) {
        typedef void (__thiscall *SetNodeFn)(void*, void*);
        int** vt = (int**)pVolMod;
        SetNodeFn fn = (SetNodeFn)((*vt)[4]);
        fn(pVolMod, this);
    }

    return 1;
}

void gbVolModNode::GetBoundSphere(struct gbSphere * p0) {
    // From Ghidra (GetBoundSphere at 0x10013160):
    // Call pVolMod->vtable[2] to get bounding sphere data,
    // then transform center by localMatrix
    if (pVolMod != 0 && p0 != 0) {
        typedef void* (__thiscall *GetSphereFn)(void*);
        int** vt = (int**)pVolMod;
        GetSphereFn fn = (GetSphereFn)((*vt)[2]);
        int* sphereData = (int*)fn(pVolMod);
        if (sphereData) {
            // First dword is radius
            *(int*)&p0->radius = sphereData[0];
            // Transform center by localMatrix
            gbVec3D* srcCenter = (gbVec3D*)(sphereData + 1);
            localMatrix.Transform(srcCenter, &p0->center);
        }
    }
}

class gbLightObj * gbVolModNode::GetLightObj() {
    return (gbLightObj*)pVolMod;
}

void gbVolModNode::Render(struct gbRenderInfoObj * p0) {
    if (!pVolMod || !p0) return;
}

void gbVolModNode::SetVolModObj(class gbVolumeModifier * p0) {
    // From Ghidra (SetVolModObj at 0x10013140):
    // Increment refcount on new modifier, store pointer
    if (p0 != 0) {
        int* pRef = (int*)p0;
        pRef[1] += 1;  // Increment RefCount at offset +4
    }
    pVolMod = (void*)p0;
}

// ---- gbVolumeModifier ----
gbVolumeModifier::gbVolumeModifier(class gbVolumeModifier const & p0) { memcpy(this, &p0, sizeof(*this)); }

gbVolumeModifier::gbVolumeModifier() { memset(this, 0, sizeof(*this)); }

class gbVolumeModifier & gbVolumeModifier::operator=(class gbVolumeModifier const & p0) { if (this != &p0) memcpy(this, &p0, sizeof(*this)); return *this; }

