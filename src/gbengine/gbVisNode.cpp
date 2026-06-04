/**
 * gbengine.dll - gbVisNode
 * Scene node base class implementation
 */

#include "gbengine/gbVisNode.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_internal.h"
#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbGfxManager.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

#pragma warning(disable: 4234)

// Static members
gbGfxManager* gbVisNode::pGfxMgr = NULL;
gbSceneGraph* gbVisNode::pSceneGraph = NULL;

// Constructor - 0x10016590
gbVisNode::gbVisNode() {
    pParent = NULL;

    msgOverflow = 1;
    msgUnused = 0;
    msgCapacity = 8;
    msgBuffer = (gbNodeMsgObj*)operator new(128);
    msgReadIndex = 0;
    msgWriteIndex = 0;
    renderPriority = 0;
    enableShadow = 0;
    field_44 = 0;
    cullPrev = NULL;
    cullNext = NULL;
    renderPriority = 0;

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
    children.pIterator = other.children.pIterator;

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
    enableShadow = other.enableShadow;
    field_44 = other.field_44;
    cullPrev = other.cullPrev;
    cullNext = other.cullNext;
    blendValue = other.blendValue;
    blendMode = other.blendMode;
}

// Destructor - 0x100049c0
gbVisNode::~gbVisNode() {
    operator delete(msgBuffer);
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

// Attach - 0x100166f0
int gbVisNode::Attach(gbRenderEffect* effect) {
    int result;
    gbVisNode* child;

    result = 0;
    child = (gbVisNode*)children.pHead;
    children.pIterator = (gbNBTreeNode*)child;
    if (child) {
        do {
            if (child->Attach(effect))
                result = 1;
            child = (gbVisNode*)children.pIterator->pNext;
            children.pIterator = (gbNBTreeNode*)child;
        } while (child);
    }
    return result;
}

// Update - 0x10016730 (virtual)
void gbVisNode::Update() {
    gbVisNode* child = (gbVisNode*)children.pHead;
    children.pIterator = (gbNBTreeNode*)child;

    while (child != NULL) {
        child->Update();
        child = (gbVisNode*)children.pIterator->pNext;
        children.pIterator = (gbNBTreeNode*)child;
    }
}

// Reset - 0x10016760 (42B) - Iterate children, call Reset on each
void gbVisNode::Reset(float time) {
    gbVisNode* child = (gbVisNode*)children.pHead;
    children.pIterator = (gbNBTreeNode*)child;

    while (child) {
        child->Reset(time);
        child = (gbVisNode*)children.pIterator->pNext;
        children.pIterator = (gbNBTreeNode*)child;
    }
}

// ShowNode - 0x10016790
void gbVisNode::ShowNode(int show) {
    visible = show;

    // Recursively apply to children
    gbVisNode* child = (gbVisNode*)children.pHead;
    children.pIterator = (gbNBTreeNode*)child;

    while (child != NULL) {
        child->ShowNode(show);
        child = (gbVisNode*)children.pIterator->pNext;
        children.pIterator = (gbNBTreeNode*)child;
    }
}

// SetTimeScale - 0x100167c0
void gbVisNode::SetTimeScale(float scale) {
    timeScale = scale;

    gbVisNode* child = (gbVisNode*)children.pHead;
    for (children.pIterator = (gbChain1DNode*)child; child; children.pIterator = (gbChain1DNode*)child) {
        child->SetTimeScale(scale);
        child = (gbVisNode*)children.pIterator->pNext;
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

    gbVisNode* child = (gbVisNode*)children.pHead;
    children.pIterator = (gbNBTreeNode*)child;

    while (child != NULL) {
        child->SetRenderPriority(priority);
        child = (gbVisNode*)children.pIterator->pNext;
        children.pIterator = (gbNBTreeNode*)child;
    }
}

// GetCullNext
gbVisNode* gbVisNode::GetCullNext() {
    return cullNext;
}

// GetCullPrev
gbVisNode* gbVisNode::GetCullPrev() {
    return cullPrev;
}

// GetBoundSphere - 0x10016820 (virtual, base implementation)
void gbVisNode::GetBoundSphere(gbSphere* sphere) {
    sphere->radius = 0.0f;
}

// EnableShadow - 0x10016830 (virtual)
void gbVisNode::EnableShadow(int enable) {
    enableShadow = enable;
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
    children.pIterator = (gbNBTreeNode*)child;

    while (child != NULL) {
        child->SetBlendRecursive(mode, value);
        child = (gbVisNode*)children.pIterator->pNext;
        children.pIterator = (gbNBTreeNode*)child;
    }
}

// GetTotalBoundSphere - 0x100168b0 (722B)
void gbVisNode::GetTotalBoundSphere(gbSphere* sphere) {
    GetBoundSphere(sphere);

    int childCount = children.m_numNode;
    for (int i = 0; i < childCount; i++) {
        gbChain1DNode* childNode = children[i];
        if (!childNode) continue;

        gbSphere childSphere;
        childSphere.radius = 0.0f;
        childSphere.center.x = childSphere.center.y = childSphere.center.z = 0.0f;

        ((gbVisNode*)childNode)->GetBoundSphere(&childSphere);

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
    gbSphere sphere;
    sphere.center.x = 0.0f;
    sphere.center.y = 0.0f;
    sphere.center.z = 0.0f;
    GetBoundSphere(&sphere);
    if (sphere.radius == 0.0f)
        return 0;
    float r = sphere.radius;
    box->vMin.x = sphere.center.x - r;
    box->vMin.y = sphere.center.y - r;
    box->vMin.z = sphere.center.z - r;
    box->vMax.x = sphere.center.x + r;
    box->vMax.y = sphere.center.y + r;
    box->vMax.z = sphere.center.z + r;
    return 1;
}

// operator= - 0x10004af0 (121B)
gbVisNode& gbVisNode::operator=(const gbVisNode& other) {
    pNext = other.pNext;
    pParent = other.pParent;
    children = other.children;
    children.pIterator = other.children.pIterator;
    msgBuffer = other.msgBuffer;
    msgCapacity = other.msgCapacity;
    memcpy(&msgUnused, &other.msgUnused, 0x3Cu);
    return *this;
}


// ============================================================
// Additional export implementations (gbVolModNode, gbVolumeModifier)
// Class definitions in gbengine_internal.h
// ============================================================

#pragma auto_inline(off)

// ---- gbVolModNode ----
gbVolModNode::gbVolModNode(class gbVolModNode const & p0) {
    memcpy(this, &p0, sizeof(gbVolModNode));
}

gbVolModNode::gbVolModNode() {
    localMatrix.LoadIdentity();
    pVolMod = 0;
}

// 0x100057c0 - gbVolModNode::operator= (168B)
class gbVolModNode & gbVolModNode::operator=(class gbVolModNode const & p0) {
    int* dst = (int*)_base_visnode;
    const int* src = (const int*)p0._base_visnode;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    memcpy(&_base_visnode[24], &p0._base_visnode[24], 0x3Cu);
    localMatrix = p0.localMatrix;
    worldMatrix = p0.worldMatrix;
    pVolMod = p0.pVolMod;
    return *this;
}

int gbVolModNode::Attach(class gbRenderEffect * p0) {
    // Call base class gbVisNode::Attach
    ((gbVisNode*)this)->gbVisNode::Attach(p0);

    // worldMatrix = localMatrix
    worldMatrix = localMatrix;

    // RightMultiply by world matrix stack top
    gbMatrix4* top = gbVisNode::pGfxMgr->pMatrixStack[1]->GetTop();
    worldMatrix.RightMultiply(*top);

    // Notify volume modifier
    pVolMod->Compute(this);

    // Register with scene graph
    gbVisNode::pSceneGraph->AddVolModNode(this);
    return 1;
}

class gbLightObj * gbVolModNode::GetLightObj() {
    return (gbLightObj*)pVolMod;
}

void gbVolModNode::Render(struct gbRenderInfoObj * p0) {
}

// ---- gbVolumeModifier ----
gbVolumeModifier::gbVolumeModifier(class gbVolumeModifier const & p0) { memcpy(this, &p0, sizeof(*this)); }

gbVolumeModifier::gbVolumeModifier() {
    memset(this, 0, sizeof(*this));
}

gbVolumeModifier::~gbVolumeModifier() {
}

float gbVolumeModifier::GetEffectOnPoint(const gbVec3D& point, int useAttenuation) {
    return 0.0f;
}

void gbVolumeModifier::Compute(gbVolModNode* volmod) {
}

int gbVolumeModifier::GetType(void) {
    return m_LightType;
}

const gbSphere* gbVolumeModifier::GetBoundSphere(void) {
    return &m_BoundSphere;
}

class gbVolumeModifier & gbVolumeModifier::operator=(class gbVolumeModifier const & p0) { if (this != &p0) memcpy(this, &p0, sizeof(*this)); return *this; }


