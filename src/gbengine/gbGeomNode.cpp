/**
 * gbengine.dll - gbGeomNode
 * Geometry node implementation
 */

#include "gbengine/gbGeomNode.h"
#include "gbengine/gbMesh.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma warning(disable: 4234)

/* ======== gbGeomNode method implementations ======== */

gbGeomNode::gbGeomNode(void) {
    // Call base class constructor (gbVisNode at 0x10016590)
    // Base class is 0x58 bytes

    // Initialize matrices (constructors at 0x10025110)
    memset(&localTransform, 0, sizeof(gbMatrix4));
    memset(&worldTransform, 0, sizeof(gbMatrix4));

    // Set vtable pointer (0x100f5588)
    // vtable = (void*)0x100f5588;

    // Load identity matrices (LoadIdentity at 0x10025640)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            localTransform.m[i][j] = (i == j) ? 1.0f : 0.0f;
            worldTransform.m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }

    // Initialize remaining fields (from decompilation)
    mesh = NULL;                    // +0xd8
    animController = NULL;          // +0xdc
    materialData = NULL;            // +0xe0
    animTime = 1.0f;                // +0xe4 = 0x3f800000
    bladeEffect = NULL;             // +0xe8
    shadowData = NULL;              // +0xec
    shadowEnabled = 0;              // +0xf0
    bladeEnabled = 0;               // +0xf4
    textureOverride = NULL;         // +0xf8
    animLoop = 0;                   // +0xfc
    loopPast = 0;                   // +0x100
    boundingBox = NULL;             // +0x104
    bladeTime = 0.0f;               // +0x108
    bladeTimeScale = 0.0f;          // +0x10c
    lastBladePos = NULL;            // +0x110
}

gbGeomNode::gbGeomNode(const gbGeomNode& other) {
    // Copy base class members (gbVisNode portion)
    // This is a shallow copy of the inheritance hierarchy

    // Copy matrices
    memcpy(&localTransform, &other.localTransform, sizeof(gbMatrix4));
    memcpy(&worldTransform, &other.worldTransform, sizeof(gbMatrix4));

    // Copy all other fields
    mesh = other.mesh;
    animController = other.animController;
    materialData = other.materialData;
    animTime = other.animTime;
    bladeEffect = other.bladeEffect;
    shadowData = other.shadowData;
    shadowEnabled = other.shadowEnabled;
    bladeEnabled = other.bladeEnabled;
    textureOverride = other.textureOverride;
    animLoop = other.animLoop;
    loopPast = other.loopPast;
    boundingBox = other.boundingBox;
    bladeTime = other.bladeTime;
    bladeTimeScale = other.bladeTimeScale;
    lastBladePos = other.lastBladePos;

    // Set vtable
    // vtable = (void*)0x100f5588;
}

gbGeomNode& gbGeomNode::operator=(const gbGeomNode& other) {
    if (this != &other) {
        // Same as copy constructor but for existing object
        memcpy(&localTransform, &other.localTransform, sizeof(gbMatrix4));
        memcpy(&worldTransform, &other.worldTransform, sizeof(gbMatrix4));

        mesh = other.mesh;
        animController = other.animController;
        materialData = other.materialData;
        animTime = other.animTime;
        bladeEffect = other.bladeEffect;
        shadowData = other.shadowData;
        shadowEnabled = other.shadowEnabled;
        bladeEnabled = other.bladeEnabled;
        textureOverride = other.textureOverride;
        animLoop = other.animLoop;
        loopPast = other.loopPast;
        boundingBox = other.boundingBox;
        bladeTime = other.bladeTime;
        bladeTimeScale = other.bladeTimeScale;
        lastBladePos = other.lastBladePos;
    }
    return *this;
}

gbGeomNode::~gbGeomNode(void) {
    // Clean up mesh and other resources
    if (mesh) {
        // mesh->Release() or delete
    }
    if (bladeEffect) {
        // Release blade effect
    }
    if (shadowData) {
        // Release shadow data
    }
    if (lastBladePos) {
        delete lastBladePos;
        lastBladePos = NULL;
    }
}

int gbGeomNode::LoadFromFile(const char* filename, const char* texPath, void (__cdecl *progressCallback)(int, int)) {
    /* STUB */
    if (!filename) return 0;
    return LoadCVDFile(filename);
}

int gbGeomNode::LoadCVDFile(const char* filename) {
    /* STUB */
    if (!filename) return 0;
    // Open file via virtual file system and delegate to stream loader
    return 0;
}

void gbGeomNode::LoadCVDFromStream(gbVFile* file, float scale) {
    /* STUB */
    if (!file) return;
}

void gbGeomNode::LoadCVDFromStream(gbVFile* file, float scale, gbGeomNode** outNodes, int& outCount) {
    /* STUB */
    if (outNodes) *outNodes = NULL;
    outCount = 0;
}

void gbGeomNode::Update(void) {
    /* STUB */
    // Update animation state
    if (animController) {
        // Update animation time
        // Update bone transforms
        // Update blade effects if enabled
    }

    // Update world transform from local transform and parent
    // Update bounding volumes

    // Call base class Update
    // gbVisNode::Update();
}

void gbGeomNode::AttachSelf(gbRenderEffect* effect) {
    if (!effect || !mesh) return;

    int numSections = mesh->GetNumSection();
    for (int i = 0; i < numSections; i++) {
        gbMeshSection* section = mesh->GetMeshSection(i);
        if (!section) continue;
    }
}

int gbGeomNode::Attach(gbRenderEffect* effect) {
    if (!effect) return 0;

    // Attach this node and all children to the render effect
    AttachSelf(effect);

    // Recursively attach children
    // return childCount;
    return 1;
}

void gbGeomNode::Render(gbRenderInfoObj* renderInfo) {
    if (!renderInfo || !mesh) return;

    int numSections = mesh->GetNumSection();
    for (int i = 0; i < numSections; i++) {
        // Call virtual DrawSubSet on the mesh for each section
        void** meshVtable = *(void***)mesh;
        typedef void (__thiscall *DrawSubSetFn)(void*, int, gbRenderInfoObj*);
        DrawSubSetFn drawSubSet = (DrawSubSetFn)meshVtable[3];
        drawSubSet(mesh, i, renderInfo);
    }
}

void gbGeomNode::RenderShadowVolume(gbRenderInfoObj* renderInfo) {
    if (!renderInfo || !shadowEnabled || !shadowData) return;

    void** meshVtable = *(void***)mesh;
    typedef void (__thiscall *RenderShadowFn)(void*, gbVisNode*, gbRenderInfoObj*);
    RenderShadowFn renderShadow = (RenderShadowFn)meshVtable[5];
    renderShadow(mesh, (gbVisNode*)this, renderInfo);
}

void gbGeomNode::Reset(float time) {
    // Reset animation to specified time
    animTime = time;
    loopPast = 0;

    if (animController) {
        // Reset animation controller to time
    }

    // Call base class Reset
    // gbVisNode::Reset(time);
}

void gbGeomNode::GetBoundSphere(gbSphere* sphere) {
    if (!sphere) return;

    if (!mesh) {
        sphere->radius = 0.0f;
        sphere->center.x = sphere->center.y = sphere->center.z = 0.0f;
        return;
    }

    gbAABBox* aabb = mesh->GetAABBox();
    float cx = (aabb->vMin.x + aabb->vMax.x) * 0.5f;
    float cy = (aabb->vMin.y + aabb->vMax.y) * 0.5f;
    float cz = (aabb->vMin.z + aabb->vMax.z) * 0.5f;
    float dx = aabb->vMax.x - aabb->vMin.x;
    float dy = aabb->vMax.y - aabb->vMin.y;
    float dz = aabb->vMax.z - aabb->vMin.z;
    float radius = sqrtf(dx * dx + dy * dy + dz * dz) * 0.5f;

    sphere->center.x = worldTransform.m[0][0] * cx + worldTransform.m[1][0] * cy + worldTransform.m[2][0] * cz + worldTransform.m[3][0];
    sphere->center.y = worldTransform.m[0][1] * cx + worldTransform.m[1][1] * cy + worldTransform.m[2][1] * cz + worldTransform.m[3][1];
    sphere->center.z = worldTransform.m[0][2] * cx + worldTransform.m[1][2] * cy + worldTransform.m[2][2] * cz + worldTransform.m[3][2];
    sphere->radius = radius;
}

void gbGeomNode::SetAnimLoop(int loop) {
    animLoop = loop;
}

void gbGeomNode::EnableShadow(int enable) {
    shadowEnabled = enable;
}

int gbGeomNode::GetAABBox(gbAABBox* box) {
    if (!mesh) return 0;

    gbAABBox* meshBox = mesh->GetAABBox();
    memcpy(box, meshBox, sizeof(gbAABBox));
    return 1;
}

void gbGeomNode::SetBladeTime(float time) {
    bladeTime = time;
}

void gbGeomNode::SetBladeTimeScale(float scale) {
    bladeTimeScale = scale;
}

gbVec3D* gbGeomNode::GetLastBladePos(gbGeomNode* node) {
    if (bladeEffect && lastBladePos) {
        return lastBladePos;
    }
    return NULL;
}

void gbGeomNode::ReplaceTexture(const char* textureName) {
    if (mesh) {
        mesh->ReplaceTexture(textureName);
    }

    gbGeomNode* child = (gbGeomNode*)children.pHead;
    children.pIterator = (gbNBTreeNode*)child;
    while (child != NULL) {
        child->ReplaceTexture(textureName);
        child = (gbGeomNode*)children.pIterator->pNext;
        children.pIterator = (gbNBTreeNode*)child;
    }
}

void gbGeomNode::ReplaceTexture(gbTexture* texture) {
    if (mesh) {
        mesh->ReplaceTexture(texture);
    }
}

gbOBBox* gbGeomNode::GetOBBox(gbOBBox* box) {
    if (!box) return NULL;

    memcpy(&box->matrix, &worldTransform, sizeof(gbMatrix4));

    if (mesh) {
        gbAABBox* aabb = mesh->GetAABBox();
        box->extent.x = aabb->vMax.x - aabb->vMin.x;
        box->extent.y = aabb->vMax.y - aabb->vMin.y;
        box->extent.z = aabb->vMax.z - aabb->vMin.z;

        gbVec3D center;
        center.x = (aabb->vMin.x + aabb->vMax.x) * 0.5f;
        center.y = (aabb->vMin.y + aabb->vMax.y) * 0.5f;
        center.z = (aabb->vMin.z + aabb->vMax.z) * 0.5f;
        box->matrix.LeftTranslate(center);
    } else {
        box->extent.x = 0.0f;
        box->extent.y = 0.0f;
        box->extent.z = 0.0f;
    }
    return box;
}

static gbGeomNode* s_totalOBBoxNodes[256];

static void CollectMeshNodes(gbGeomNode** nodeArray, unsigned int* count, gbGeomNode* node) {
    if (node->GetMesh() != NULL) {
        nodeArray[*count] = node;
        (*count)++;
    }
    gbGeomNode* child = (gbGeomNode*)node->children.pHead;
    node->children.pIterator = (gbNBTreeNode*)child;
    while (child != NULL) {
        CollectMeshNodes(nodeArray, count, child);
        child = (gbGeomNode*)node->children.pIterator->pNext;
        node->children.pIterator = (gbNBTreeNode*)child;
    }
}

gbOBBox* gbGeomNode::GetTotalOBBox(gbOBBox* box) {
    if (!box) return NULL;

    unsigned int nodeCount = 0;
    if (mesh) {
        s_totalOBBoxNodes[0] = this;
        nodeCount = 1;
    }

    gbGeomNode* child = (gbGeomNode*)children.pHead;
    children.pIterator = (gbNBTreeNode*)child;
    while (child != NULL) {
        CollectMeshNodes(s_totalOBBoxNodes, &nodeCount, child);
        child = (gbGeomNode*)children.pIterator->pNext;
        children.pIterator = (gbNBTreeNode*)child;
    }

    if (nodeCount == 0) {
        memcpy(&box->matrix, &worldTransform, sizeof(gbMatrix4));
        if (mesh) {
            gbAABBox* aabb = mesh->GetAABBox();
            box->extent.x = aabb->vMax.x - aabb->vMin.x;
            box->extent.y = aabb->vMax.y - aabb->vMin.y;
            box->extent.z = aabb->vMax.z - aabb->vMin.z;
            gbVec3D center;
            center.x = (aabb->vMin.x + aabb->vMax.x) * 0.5f;
            center.y = (aabb->vMin.y + aabb->vMax.y) * 0.5f;
            center.z = (aabb->vMin.z + aabb->vMax.z) * 0.5f;
            box->matrix.LeftTranslate(center);
        } else {
            box->extent.x = 0.0f;
            box->extent.y = 0.0f;
            box->extent.z = 0.0f;
        }
        return box;
    }

    if (nodeCount == 1) {
        gbGeomNode* n = s_totalOBBoxNodes[0];
        memcpy(&box->matrix, &n->worldTransform, sizeof(gbMatrix4));
        if (n->mesh) {
            gbAABBox* aabb = n->mesh->GetAABBox();
            box->extent.x = aabb->vMax.x - aabb->vMin.x;
            box->extent.y = aabb->vMax.y - aabb->vMin.y;
            box->extent.z = aabb->vMax.z - aabb->vMin.z;
            gbVec3D center;
            center.x = (aabb->vMin.x + aabb->vMax.x) * 0.5f;
            center.y = (aabb->vMin.y + aabb->vMax.y) * 0.5f;
            center.z = (aabb->vMin.z + aabb->vMax.z) * 0.5f;
            box->matrix.LeftTranslate(center);
        } else {
            box->extent.x = 0.0f;
            box->extent.y = 0.0f;
            box->extent.z = 0.0f;
        }
        return box;
    }

    float minX = 3.4028235e+38f, minY = 3.4028235e+38f, minZ = 3.4028235e+38f;
    float maxX = -3.4028235e+38f, maxY = -3.4028235e+38f, maxZ = -3.4028235e+38f;
    gbAABBox tempBox;

    for (unsigned int i = 0; i < nodeCount; i++) {
        gbGeomNode* n = s_totalOBBoxNodes[i];
        gbAABBox* aabb = n->mesh->GetAABBox();
        memcpy(&tempBox, aabb, sizeof(gbAABBox));
        tempBox.Transform(&n->worldTransform);

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
    if (animController) {
        return animController->maxTime;
    }
    return 0.0f;
}
