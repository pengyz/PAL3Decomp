/**
 * gbengine.dll - gbGeomNode
 * Geometry node implementation
 * Verified against IDA Hex-Rays with struct applied (2026-05-06)
 */

#include "gbengine/gbGeomNode.h"
#include "gbengine/gbMesh.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbengine_internal.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma warning(disable: 4234)

/* ======== Constructor / Destructor ======== */

gbGeomNode::gbGeomNode(void) : gbVisNode() {
    worldTransform.LoadIdentity();
    staticTransform.LoadIdentity();

    pAnimTranslate = NULL;
    pAnimRotate = NULL;
    pAnimScale = NULL;
    scaleValue = 1.0f;
    hasAnimation = 0;
    animController = NULL;
    currentTime = 0.0;
    animMaxTime = 0.0f;
    animLoop = 0;
    loopPast = 0;
    mesh = NULL;
    bladeEnabled = 0;
    pLightmapData = NULL;
    numAttachPoints = 0;
    pAttachPointArray = NULL;
}

gbGeomNode::gbGeomNode(const gbGeomNode& other) : gbVisNode(other) {
    memcpy(&worldTransform, &other.worldTransform, sizeof(gbMatrix4));
    memcpy(&staticTransform, &other.staticTransform, 0x7C);
}

gbGeomNode& gbGeomNode::operator=(const gbGeomNode& other) {
    if (this != &other) {
        gbVisNode::operator=(other);
        memcpy(&worldTransform, &other.worldTransform, sizeof(gbMatrix4));
        memcpy(&staticTransform, &other.staticTransform, 0x7C);
    }
    return *this;
}

gbGeomNode::~gbGeomNode(void) {
    if (pLightmapData)
        operator delete(pLightmapData);
    if (mesh)
        mesh->Release();
    if (animController)
        operator delete(animController);
    if (pAnimTranslate) {
        delete pAnimTranslate;
    }
    if (pAnimScale) {
        delete pAnimScale;
    }
    if (pAnimRotate) {
        delete pAnimRotate;
    }
}

/* ======== File Loading (STUB) ======== */

int gbGeomNode::LoadFromFile(const char* filename, const char* texPath, void (__cdecl *progressCallback)(int, int)) {
    /* STUB - 1478 bytes, needs gbVFile system */
    return 0;
}

int gbGeomNode::LoadCVDFile(const char* filename) {
    /* STUB - 852 bytes */
    return 0;
}

void gbGeomNode::LoadCVDFromStream(gbVFile* file, float scale) {
    /* STUB */
}

void gbGeomNode::LoadCVDFromStream(gbVFile* file, float scale, gbGeomNode** outNodes, int& outCount) {
    /* STUB */
}

/* ======== Update ======== */

void gbGeomNode::Update(void) {
    float deltaTime = (float)(gbVisNode::pGfxMgr->GetDeltaTime()) * timeScale;

    if (animMaxTime > 0.0f) {
        double ct = currentTime;
        int frame = (int)(__int64)(ct / (double)animMaxTime);
        if (ct - (double)frame * (double)animMaxTime + deltaTime >= (double)animMaxTime) {
            gbNodeMsgObj msg;
            msg.data[0] = 1;
            msg.data[1] = 0x6F766572; // "over"
            msg.data[3] = (int)this;
            PushMessage(msg);
        }
    }

    currentTime = currentTime + deltaTime;

    if (animMaxTime > 0.0f) {
        if (currentTime >= (double)animMaxTime) {
            do {
                currentTime = currentTime - (double)animMaxTime;
                loopPast++;
            } while (currentTime >= (double)animMaxTime);
        }
        if (animLoop > 0 && loopPast >= animLoop)
            currentTime = (double)animMaxTime;
    }

    // Copy parent's world transform or load identity
    if (pParent)
        memcpy(&worldTransform, (char*)pParent + 88, 0x40u);
    else
        worldTransform.LoadIdentity();

    if (hasAnimation) {
        float time = (float)currentTime;
        gbVec3D result;

        if (pAnimTranslate) {
            pAnimTranslate->GetValue(&result, time);
            worldTransform.LeftTranslate(result);
        }

        worldTransform.LeftScale(scaleValue, scaleValue, scaleValue);

        if (pAnimScale) {
            gbQuaternion quat;
            pAnimScale->GetValue(&quat, time);
            quat.w = -quat.w;
            worldTransform.LeftMultiply(quat);
        }

        if (pAnimRotate) {
            gbQuaternion quat;
            pAnimRotate->GetValue(&quat, time);
            quat.w = -quat.w;
            worldTransform.LeftMultiply(quat);

            gbQuaternion quatInv = quat;
            quatInv.Inverse();
            worldTransform.LeftMultiply(quat);
            // IDA shows additional LeftScale + LeftMultiply(quatInv) here
            gbVisNode::Update();
            return;
        }
    } else {
        worldTransform.LeftMultiply(staticTransform);
    }

    gbVisNode::Update();
}

/* ======== Attach ======== */

void gbGeomNode::AttachSelf(gbRenderEffect* effect) {
    /* STUB - 754 bytes, needs full render pipeline */
}

int gbGeomNode::Attach(gbRenderEffect* effect) {
    // Call virtual AttachSelf (vtable offset 12 = slot 3)
    AttachSelf(effect);
    gbVisNode::Attach(effect);
    return 1;
}

/* ======== Render ======== */

void gbGeomNode::Render(gbRenderInfoObj* renderInfo) {
    int frame = 0;
    float curTime = (float)currentTime;

    if (animMaxTime != 0.0f)
        frame = (int)(__int64)(curTime / animMaxTime);

    if (visible) {
        if (mesh) {
            float localTime = (float)(curTime - (double)frame * (double)animMaxTime);
            if (localTime < 0.0f)
                localTime = 0.0f;
            mesh->SetCurTime(localTime);

            gbMatrixStack* matStack = (gbMatrixStack*)*(((DWORD*)gbVisNode::pGfxMgr) + 54);
            matStack->Push();
            matStack->LoadMatrix((gbMatrix4*)((char*)renderInfo + 32));

            // vtable[1] = DrawSubSet(int sectionIndex, gbRenderInfoObj*)
            typedef void (__thiscall *DrawSubSetFn)(void*, int, gbRenderInfoObj*);
            void** vtbl = *(void***)mesh;
            DrawSubSetFn fn = (DrawSubSetFn)vtbl[1];
            fn(mesh, ((int*)renderInfo)[2], renderInfo);

            matStack->Pop();
        }
    }
}

void gbGeomNode::RenderShadowVolume(gbRenderInfoObj* renderInfo) {
    int frame = 0;
    float curTime = (float)currentTime;

    if (animMaxTime != 0.0f)
        frame = (int)(__int64)(curTime / animMaxTime);

    if (visible) {
        if (mesh) {
            float localTime = (float)(curTime - (double)frame * (double)animMaxTime);
            if (localTime < 0.0f)
                localTime = 0.0f;
            mesh->SetCurTime(localTime);

            gbMatrixStack* matStack = (gbMatrixStack*)*(((DWORD*)gbVisNode::pGfxMgr) + 54);
            matStack->Push();
            matStack->LoadMatrix((gbMatrix4*)((char*)renderInfo + 32));

            // vtable[3] = RenderShadowVolume(gbVisNode*, gbRenderInfoObj*)
            typedef void (__thiscall *RenderShadowFn)(void*, gbGeomNode*, gbRenderInfoObj*);
            void** vtbl = *(void***)mesh;
            RenderShadowFn fn = (RenderShadowFn)vtbl[3];
            fn(mesh, this, renderInfo);

            matStack->Pop();
        }
    }
}

/* ======== Reset ======== */

void gbGeomNode::Reset(float time) {
    if (time >= 0.0f) {
        currentTime = (double)time;
    } else {
        double t = (double)animMaxTime * 0.99000001;
        currentTime = t;
        if (t < 0.0) {
            currentTime = 0.0;
            loopPast = 0;
            gbVisNode::Reset(time);
            return;
        }
    }
    loopPast = 0;
    gbVisNode::Reset(time);
}

/* ======== Bounding volumes ======== */

void gbGeomNode::GetBoundSphere(gbSphere* sphere) {
    if (mesh) {
        float* m = (float*)mesh;
        // mesh AABB: vMin at mesh+22*4=+0x58, vMax at mesh+25*4=+0x64
        float cx = (m[22] + m[25]) * 0.5f;
        float cy = (m[23] + m[26]) * 0.5f;
        float cz = (m[24] + m[27]) * 0.5f;
        float dx = m[25] - m[22];
        float dy = m[26] - m[23];
        float dz = m[27] - m[24];

        gbVec3D diag;
        diag.x = dx;
        diag.y = dy;
        diag.z = dz;
        sphere->radius = diag.Length() * 0.5f;

        gbVec3D center;
        center.x = cx;
        center.y = cy;
        center.z = cz;
        worldTransform.Transform(&center, &sphere->center);
    } else {
        sphere->radius = 0.0f;
        sphere->center.x = 0.0f;
        sphere->center.y = 0.0f;
        sphere->center.z = 0.0f;
    }
}

void gbGeomNode::SetAnimLoop(int loop) {
    animLoop = loop;
    loopPast = 0;
    for (int i = 0; i < children.nCount; i++) {
        gbGeomNode* child = (gbGeomNode*)children[i];
        child->SetAnimLoop(loop);
    }
}

void gbGeomNode::EnableShadow(int enable) {
    gbVisNode::EnableShadow(enable);
    if (enable) {
        // vtable[2] = ComputeShadowVolume()
        typedef void (__thiscall *ComputeShadowFn)(void*);
        void** vtbl = *(void***)mesh;
        ComputeShadowFn fn = (ComputeShadowFn)vtbl[2];
        fn(mesh);
    }
}

int gbGeomNode::GetAABBox(gbAABBox* box) {
    if (!mesh) return 0;

    // mesh AABB at mesh+88 = mesh+0x58 (same offset as worldTransform in node)
    // Actually mesh stores AABB at float offsets [22..27]
    memcpy(box, (char*)mesh + 88, 0x18u);
    return 1;
}

/* ======== Blade functions (delegates to sub-objects) ======== */

void gbGeomNode::SetBladeTime(float time) {
    /* Delegates to sub_1000EE90 - blade trail subsystem */
    // sub_1000EE90((int)this, time);
}

void gbGeomNode::SetBladeTimeScale(float scale) {
    /* Delegates to sub_1000EED0 - blade trail subsystem */
    // sub_1000EED0((int)this, scale);
}

gbVec3D* gbGeomNode::GetLastBladePos(gbGeomNode* node) {
    /* Delegates to sub_1000F080 - blade trail subsystem */
    // return (gbVec3D*)sub_1000F080(this);
    return NULL;
}

/* ======== Texture replacement ======== */

void gbGeomNode::ReplaceTexture(const char* textureName) {
    if (mesh) {
        mesh->ReplaceTexture(textureName);
    }

    gbGeomNode* child = (gbGeomNode*)children.pHead;
    children.pIterator = (gbChain1DNode*)child;
    while (child != NULL) {
        child->ReplaceTexture(textureName);
        child = (gbGeomNode*)((gbChain1DNode*)children.pIterator)->pNext;
        children.pIterator = (gbChain1DNode*)child;
    }
}

void gbGeomNode::ReplaceTexture(gbTexture* texture) {
    if (mesh) {
        mesh->ReplaceTexture(texture);
    }
}

/* ======== OBBox ======== */

gbOBBox* gbGeomNode::GetOBBox(gbOBBox* box) {
    memcpy(box, &worldTransform, sizeof(gbMatrix4));

    float* m = (float*)mesh;
    if (mesh) {
        // extent = vMax - vMin
        box->extent.x = m[25] - m[22];
        box->extent.y = m[26] - m[23];
        box->extent.z = m[27] - m[24];

        // center = (vMin + vMax) * 0.5
        gbVec3D center;
        center.x = (m[22] + m[25]) * 0.5f;
        center.y = (m[23] + m[26]) * 0.5f;
        center.z = (m[24] + m[27]) * 0.5f;
        box->matrix.LeftTranslate(center);
    } else {
        box->extent.x = 0.0f;
        box->extent.y = 0.0f;
        box->extent.z = 0.0f;
    }
    return box;
}

static int s_totalOBBoxNodes[256];

static void CollectMeshNodes(int* nodeArray, int* count, int node) {
    if (*(int*)(node + 264) != 0) {
        nodeArray[*count] = node;
        (*count)++;
    }
    int child = *(int*)(node + 0x0C);
    *(int*)(node + 0x18) = child;
    while (child != 0) {
        CollectMeshNodes(nodeArray, count, child);
        child = *(int*)(*(int*)(node + 0x18) + 4);
        *(int*)(node + 0x18) = child;
    }
}

gbOBBox* gbGeomNode::GetTotalOBBox(gbOBBox* box) {
    int nodeCount = 0;

    if (mesh) {
        s_totalOBBoxNodes[0] = (int)this;
        nodeCount = 1;
    }

    gbGeomNode* child = (gbGeomNode*)children.pHead;
    children.pIterator = (gbChain1DNode*)child;
    while (child != NULL) {
        CollectMeshNodes(s_totalOBBoxNodes, &nodeCount, (int)child);
        child = (gbGeomNode*)((gbChain1DNode*)children.pIterator)->pNext;
        children.pIterator = (gbChain1DNode*)child;
    }

    if (nodeCount == 0) {
        memcpy(box, &worldTransform, sizeof(gbMatrix4));
        float* m = (float*)mesh;
        if (mesh) {
            box->extent.x = m[25] - m[22];
            box->extent.y = m[26] - m[23];
            box->extent.z = m[27] - m[24];
            gbVec3D center;
            center.x = (m[22] + m[25]) * 0.5f;
            center.y = (m[23] + m[26]) * 0.5f;
            center.z = (m[24] + m[27]) * 0.5f;
            box->matrix.LeftTranslate(center);
        } else {
            box->extent.x = 0.0f;
            box->extent.y = 0.0f;
            box->extent.z = 0.0f;
        }
        return box;
    }

    if (nodeCount == 1) {
        int n = s_totalOBBoxNodes[0];
        memcpy(box, (void*)(n + 88), sizeof(gbMatrix4));
        float* m = (float*)*(int*)(n + 264);
        if (m) {
            box->extent.x = m[25] - m[22];
            box->extent.y = m[26] - m[23];
            box->extent.z = m[27] - m[24];
            gbVec3D center;
            center.x = (m[22] + m[25]) * 0.5f;
            center.y = (m[23] + m[26]) * 0.5f;
            center.z = (m[24] + m[27]) * 0.5f;
            box->matrix.LeftTranslate(center);
        } else {
            box->extent.x = 0.0f;
            box->extent.y = 0.0f;
            box->extent.z = 0.0f;
        }
        return box;
    }

    // Multiple nodes: compute combined AABB
    float minX = 3.4028235e+38f, minY = 3.4028235e+38f, minZ = 3.4028235e+38f;
    float maxX = -3.4028235e+38f, maxY = -3.4028235e+38f, maxZ = -3.4028235e+38f;
    gbAABBox tempBox;

    for (int i = 0; i < nodeCount; i++) {
        int n = s_totalOBBoxNodes[i];
        gbMatrix4* wt = (gbMatrix4*)(n + 88);
        memcpy(&tempBox, (void*)(*(int*)(n + 264) + 88), sizeof(gbAABBox));
        tempBox.Transform(wt);

        if (tempBox.vMin.x < minX) minX = tempBox.vMin.x;
        if (tempBox.vMin.y < minY) minY = tempBox.vMin.y;
        if (tempBox.vMin.z < minZ) minZ = tempBox.vMin.z;
        if (tempBox.vMax.x > maxX) maxX = tempBox.vMax.x;
        if (tempBox.vMax.y > maxY) maxY = tempBox.vMax.y;
        if (tempBox.vMax.z > maxZ) maxZ = tempBox.vMax.z;
    }

    box->extent.x = maxX - minX;
    box->extent.y = maxY - minY;
    box->extent.z = maxZ - minZ;
    box->matrix.LoadIdentity();
    box->matrix.m[3][0] = (maxX + minX) * 0.5f;
    box->matrix.m[3][1] = (maxY + minY) * 0.5f;
    box->matrix.m[3][2] = (maxZ + minZ) * 0.5f;
    return box;
}

/* ======== Simple accessors ======== */

void gbGeomNode::EnableBlade(int enable) {
    bladeEnabled = enable;
}

gbMatrix4* gbGeomNode::GetCacheToWorld() {
    return &worldTransform;
}

int gbGeomNode::GetLoopPast() {
    return loopPast;
}

gbBaseMesh* gbGeomNode::GetMesh() {
    return mesh;
}

float gbGeomNode::GetAnimMaxTime() {
    return animMaxTime;
}
