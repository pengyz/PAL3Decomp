/**
 * gbengine.dll - gbGeomNode
 * Geometry node implementation
 * Verified against IDA Hex-Rays with struct applied (2026-05-06)
 */

#include "gbengine/gbGeomNode.h"
#include "gbengine/gbMesh.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbengine_internal.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma warning(disable: 4234)

/* ======== Skinned Mesh Internal Structures ======== */

// Blend section for skinned mesh vertices (sizeof = 0x24 = 36 bytes)
// Used by FindMeshSection to sort blend weights/indices
struct gbBlendSection {
    int field_00;                   // +0x00
    int field_04;                   // +0x04
    int field_08;                   // +0x08
    unsigned char boneIndices[8];   // +0x0C: bone indices (sorted by weight)
    unsigned char boneWeights[8];   // +0x14: bone weights (sorted descending)
    int numInfluences;              // +0x1C: number of active bone influences
    int field_20;                   // +0x20
};

// Skinned mesh blend data container
// this+0x08 = numSections, this+0x18 = pSections (pointer to gbBlendSection array)
class gbSkinBlendData {
public:
    int field_00;                   // +0x00
    int field_04;                   // +0x04
    int numSections;                // +0x08
    int field_0C;                   // +0x0C
    int field_10;                   // +0x10
    int field_14;                   // +0x14
    gbBlendSection* pSections;      // +0x18

    void FindMeshSection(int targetCount);
};

// Animation keyframe (sizeof = 0x20 = 32 bytes)
struct gbAnimKeyFrame {
    int time;                       // +0x00: time in ticks (float seconds * 4800)
    gbVec3D position;               // +0x04: position
    gbQuaternion rotation;          // +0x10: rotation quaternion
};

// Bone animation data element (sizeof = 0x50 = 80 bytes)
// Used by ClearAnimData, FreeAnimData, LoadAnimKeys, InterpolateAnim
class gbBoneAnimData {
public:
    int boneIndex;                  // +0x00: bone index (or parent reference)
    char name[64];                  // +0x04: bone name string
    int field_44;                   // +0x44: unknown field
    int numKeys;                    // +0x48: number of keyframes
    gbAnimKeyFrame* pKeys;          // +0x4C: pointer to keyframe array

    gbBoneAnimData();               // constructor (ClearAnimData)
    ~gbBoneAnimData();              // destructor (FreeAnimData)
    void LoadAnimKeys(gbVFile* file);
    void InterpolateAnim(unsigned int time, float* outPos, gbQuaternion* outQuat);
};

// WDS Bone node (sizeof = 0x13C = 316 bytes)
// Used by LoadFromStream and UpdateTransform for skeleton hierarchy
struct gbWDSBone {
    int nodeType;                   // +0x00: node type (checked against 1 in UpdateTransform)
    char name[64];                  // +0x04: node name (variable length read)
    float posX, posY, posZ;         // +0x44: rest position
    float rotX, rotY, rotZ, rotW;   // +0x50: rest rotation (w=1.0 init)
    char field_60[36];              // +0x60: extra data (0x24 bytes read from file)
    int field_84;                   // +0x84: unknown
    gbMatrix4 localMatrix;          // +0x88: local matrix (identity init)
    int boneIndex;                  // +0xC8: index in matrix buffer (-1 init)
    int parentBoneIndex;            // +0xCC: parent bone index (-1 init)
    int numChildren;                // +0xD0: number of children
    gbWDSBone** children;           // +0xD4: child bone pointer array
    int contextPtr;                 // +0xD8: parent context pointer
    float workPosX, workPosY, workPosZ; // +0xDC: working position (interpolated)
    float workQuatX, workQuatY, workQuatZ, workQuatW; // +0xE8: working quaternion
    float blendFactor;              // +0xF8: blend/time factor (0.0 = use rest pose)
    gbMatrix4 worldMatrix;          // +0xFC: world matrix (identity init)

    gbWDSBone();
    void LoadFromStream(gbVFile* file, int context);
    void UpdateTransform(int matrixBuffer, int param2);
};

// Time conversion constant for animation (float -> ticks)
static const float ANIM_TICKS_PER_SECOND = 4800.0f;

/* ======== FindMeshSection ======== */

// 0x10006E70 (218B)
// Sorts blend weights/indices in descending order and pads to target count
void gbSkinBlendData::FindMeshSection(int targetCount)
{
    int sectionIdx = 0;

    if (numSections > 0)
    {
        int offset = 0;
        do
        {
            gbBlendSection* sec = (gbBlendSection*)((char*)pSections + offset);
            int count = sec->numInfluences;
            unsigned char* indices = sec->boneIndices;
            unsigned char* weights = sec->boneWeights;

            // Bubble sort by weight (descending)
            if (count - 1 > 0)
            {
                unsigned char* wPtr = weights;
                while (1)
                {
                    int j = (int)(wPtr - weights) + 1;
                    if (j < count)
                    {
                        do
                        {
                            unsigned char w = *wPtr;
                            unsigned char wj = weights[j];
                            if (w < wj)
                            {
                                *wPtr = wj;
                                weights[j] = w;
                                unsigned char idx = indices[(int)(wPtr - weights)];
                                indices[(int)(wPtr - weights)] = indices[j];
                                indices[j] = idx;
                            }
                            ++j;
                        } while (j < sec->numInfluences);
                    }
                    count = sec->numInfluences;
                    ++wPtr;
                    if ((int)(wPtr - weights) >= count - 1)
                        break;
                }
            }

            int curCount = sec->numInfluences;
            if (!curCount)
            {
                indices[0] = 0;
                weights[0] = 0;
            }
            for (; curCount < targetCount; ++curCount)
            {
                indices[curCount] = indices[0];
                weights[curCount] = 0;
            }
            sec->numInfluences = targetCount;

            sectionIdx++;
            offset += 36;
        } while (sectionIdx < numSections);
    }
}

/* ======== gbWDSBone Constructor ======== */

inline gbWDSBone::gbWDSBone() :
    posX(0.0f), posY(0.0f), posZ(0.0f),
    rotX(0.0f), rotY(0.0f), rotZ(0.0f), rotW(1.0f),
    // localMatrix auto-constructed here in declaration order
    boneIndex(-1), parentBoneIndex(-1),
    children(NULL), contextPtr(0),
    workPosX(0.0f), workPosY(0.0f), workPosZ(0.0f),
    workQuatX(0.0f), workQuatY(0.0f), workQuatZ(0.0f), workQuatW(1.0f)
    // worldMatrix auto-constructed here in declaration order
{
}

/* ======== LoadFromStream (WDS Bone) ======== */

// 0x10006FB0 (529B)
// Loads bone hierarchy from file stream
void gbWDSBone::LoadFromStream(gbVFile* file, int context)
{
    gbVFile* v3;
    int v9;

    v3 = file;
    g_pVFileSys->Read(&nodeType, 4u, v3);
    g_pVFileSys->Read(&file, 4u, v3);
    g_pVFileSys->Read((char*)this + 4, (size_t)file, v3);
    *((char*)this + (int)file + 4) = 0;
    g_pVFileSys->Read(&posX, 0x0Cu, v3);
    g_pVFileSys->Read(&rotX, 0x10u, v3);
    g_pVFileSys->Read(field_60, 0x24u, v3);
    g_pVFileSys->Read(&field_84, 4u, v3);
    g_pVFileSys->Read(&localMatrix, 0x40u, v3);
    g_pVFileSys->Read(&boneIndex, 4u, v3);
    g_pVFileSys->Read(&parentBoneIndex, 4u, v3);
    g_pVFileSys->Read(&numChildren, 4u, v3);
    contextPtr = context;
    children = (gbWDSBone**)operator new(4 * numChildren);

    context = 0;
    if (numChildren > 0)
    {
        do
        {
            gbWDSBone* child = new gbWDSBone();
            v9 = context;
            children[context] = child;
            children[v9]->LoadFromStream(v3, (int)this);
            context = v9 + 1;
        } while (context < numChildren);
    }
}

/* ======== UpdateTransform (WDS Bone) ======== */

// 0x100071D0 (315B)
// Computes bone world transforms recursively
void gbWDSBone::UpdateTransform(int matrixBuffer, int param2)
{
    if (boneIndex >= 0)
    {
        if (blendFactor == 0.0f)
        {
            workPosX = posX;
            workPosY = posY;
            workPosZ = posZ;
            workQuatX = rotX;
            workQuatY = rotY;
            workQuatZ = rotZ;
            workQuatW = rotW;
        }

        workQuatW = -workQuatW;

        // Compute offset into matrix buffer: matrixBuffer + 4 + boneIndex * 132
        gbMatrix4* boneWorldMat = (gbMatrix4*)(matrixBuffer + 4 + boneIndex * 132);

        if (nodeType == 1)
        {
            ((gbQuaternion*)&workQuatX)->GetMatrix(boneWorldMat);
            boneWorldMat->RightTranslate(*(gbVec3D*)&workPosX);
        }
        else
        {
            ((gbQuaternion*)&workQuatX)->GetMatrix(boneWorldMat);
            boneWorldMat->RightTranslate(*(gbVec3D*)&workPosX);
        }

        if (parentBoneIndex >= 0)
        {
            gbMatrix4* parentMat = (gbMatrix4*)(matrixBuffer + 4 + parentBoneIndex * 132);
            boneWorldMat->RightMultiply(*parentMat);
        }

        // Copy local matrix to second slot: matrixBuffer + 0x44 + boneIndex * 132
        gbMatrix4* boneLocalSlot = (gbMatrix4*)(matrixBuffer + 0x44 + boneIndex * 132);
        *boneLocalSlot = localMatrix;
        boneLocalSlot->RightMultiply(*(const gbMatrix4*)(matrixBuffer + 4 + boneIndex * 132));
    }

    int i = 0;
    if (numChildren > 0)
    {
        do
        {
            children[i]->UpdateTransform(matrixBuffer, param2);
            i++;
        } while (i < numChildren);
    }
}

/* ======== ClearAnimData ======== */

// 0x10007310 (10B)
// Constructor callback for gbBoneAnimData - clears keyframe pointer
gbBoneAnimData::gbBoneAnimData()
{
    pKeys = NULL;
}

/* ======== FreeAnimData ======== */

// 0x10007320 (15B)
// Destructor callback for gbBoneAnimData - frees keyframe array
gbBoneAnimData::~gbBoneAnimData()
{
    if (pKeys)
        operator delete(pKeys);
}

/* ======== LoadAnimKeys ======== */

// 0x10007330 (308B)
// Loads animation keyframe data from file into bone anim element
void gbBoneAnimData::LoadAnimKeys(gbVFile* file)
{
    int nameLen;
    float timeFloat;
    char discardBuf[36]; // 0x24 bytes discarded per keyframe (extra transform data)

    g_pVFileSys->Read(this, 4u, file);
    g_pVFileSys->Read(&nameLen, 4u, file);
    g_pVFileSys->Read((char*)this + 4, (unsigned int)nameLen, file);
    g_pVFileSys->Read((char*)this + 0x48, 4u, file);
    g_pVFileSys->Read((char*)this + 0x44, 4u, file);

    int nKeys = numKeys;
    gbAnimKeyFrame* keys = (gbAnimKeyFrame*)operator new(nKeys << 5);
    int offset = 0;

    if (keys)
    {
        if (nKeys - 1 >= 0)
        {
            int* ptr = (int*)((char*)keys + 12);
            int count = nKeys;
            do
            {
                ptr[-2] = 0;
                ptr[-1] = 0;
                *ptr = 0;
                ptr[3] = 0;
                ptr[2] = 0;
                ptr[1] = 0;
                ptr[4] = 0x3F800000;
                ptr += 8;
                --count;
            } while (count);
        }
    }
    else
    {
        keys = NULL;
    }

    pKeys = keys;
    int result = numKeys;
    int i = 0;
    if (result > 0)
    {
        do
        {
            g_pVFileSys->Read(&timeFloat, 4u, file);
            *(int*)((char*)pKeys + offset) = (int)(__int64)(timeFloat * ANIM_TICKS_PER_SECOND);
            g_pVFileSys->Read((void*)((char*)pKeys + offset + 4), 0x0Cu, file);
            g_pVFileSys->Read((void*)((char*)pKeys + offset + 16), 0x10u, file);
            g_pVFileSys->Read(discardBuf, 0x24u, file);
            result = numKeys;
            ++i;
            offset += 32;
        } while (i < result);
    }
}

/* ======== InterpolateAnim ======== */

// 0x10007470 (300B)
// Interpolates animation keyframes - finds time range, lerps position, slerps quaternion
void gbBoneAnimData::InterpolateAnim(unsigned int time, float* outPos, gbQuaternion* outQuat)
{
    int nKeys = numKeys;
    int idx = 0;

    if (nKeys <= 0)
        goto lastFrame;

    {
        unsigned int* keyPtr = (unsigned int*)pKeys;
        unsigned int* iter = keyPtr;
        do
        {
            if (time < *iter)
                break;
            ++idx;
            iter += 8;  // stride 32 bytes = 8 DWORDs
        } while (idx < nKeys);

        if (idx && idx < nKeys)
        {
            int byteOffset = 32 * idx;
            unsigned int nextTime = keyPtr[idx * 8];
            unsigned int prevTime = keyPtr[idx * 8 - 8];
            float t = (float)((double)(unsigned int)(nextTime - time) / (double)(unsigned int)(nextTime - prevTime));
            float oneMinusT = 1.0f - t;

            outPos[0] = oneMinusT * *(float*)&keyPtr[idx * 8 + 1] + t * *(float*)&keyPtr[idx * 8 - 7];
            outPos[1] = oneMinusT * *(float*)((char*)pKeys + byteOffset + 8) + t * *(float*)((char*)pKeys + byteOffset - 24);
            outPos[2] = oneMinusT * *(float*)((char*)pKeys + byteOffset + 12) + t * *(float*)((char*)pKeys + byteOffset - 20);

            outQuat->Slerp(
                (gbQuaternion*)((char*)pKeys + byteOffset + 16),
                (gbQuaternion*)((char*)pKeys + byteOffset - 16),
                t);
            return;
        }
    }

lastFrame:
    {
        int lastOffset = nKeys * 32 - 28;
        char* base = (char*)pKeys;
        outPos[0] = *(float*)(base + lastOffset);
        outPos[1] = *(float*)(base + lastOffset + 4);
        outPos[2] = *(float*)(base + lastOffset + 8);

        int* quatSrc = (int*)((char*)pKeys + numKeys * 32 - 16);
        *(int*)&outQuat->x = quatSrc[0];
        *(int*)&outQuat->y = quatSrc[1];
        *(int*)&outQuat->z = quatSrc[2];
        *(int*)&outQuat->w = quatSrc[3];
    }
}

/* ======== Constructor / Destructor ======== */

gbGeomNode::gbGeomNode(void) : gbVisNode() {
    worldTransform.LoadIdentity();
    staticTransform.LoadIdentity();

    *(int*)((char*)this + 0xF0) = 0;
    animController = NULL;
    PosCtrl = NULL;
    pAnimRotate = NULL;
    pAnimScale = NULL;
    hasAnimation = 0;
    *(int*)((char*)this + 0xF4) = 0;
    animMaxTime = 0.0f;
    animLoop = 0;
    loopPast = 0;
    mesh = NULL;
    bBlade = 0;
    pLightmapData = NULL;
    scaleValue = 1.0f;
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
    if (PosCtrl) {
        delete PosCtrl;
    }
    if (pAnimScale) {
        delete pAnimScale;
    }
    if (pAnimRotate) {
        delete pAnimRotate;
    }
}

// Attach point data (48 bytes per entry in pAttachPointArray)
struct gbAttachPointData {
    char _pad[32];          // +0x00
    gbVec3D position;       // +0x20 (offset 32)
    int colorIndex;         // +0x2C (offset 44)
};

/* ======== File Loading ======== */

#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbMisc.h"

static GeomNodeDesc* s_nodeDescPool = NULL;
static int s_nodeDescPoolSize = 256;
static int s_nodeDescCount = 0;
static int s_nodeDescInitialized = 0;

static int s_cvdMeshCounter = 0;

static void s_nodeDescCleanup() {
    if (s_nodeDescPool) {
        free(s_nodeDescPool);
        s_nodeDescPool = NULL;
    }
}

int gbGeomNode::LoadFromFile(const char* filename, const char* texPath, void (__cdecl *progressCallback)(int, int)) {
    char* ext = strrchr((char*)filename, '.');
    if (gbstricmp(ext, ".pol")) {
        if (!gbstricmp(ext, ".cvd"))
            return LoadCVDFile(filename);
        if (!gbstricmp(ext, ".wds")) {
            gbVFile* file = g_pVFileSys->OpenFile(filename, 0x201u);
            // WDS loading (skinned mesh) - simplified
            g_pVFileSys->CloseFile(file);
        }
        return 0;
    }

    // .pol file loading
    gbVFile* file = g_pVFileSys->OpenFile(filename, 0x201u);
    if (!file) {
        gbLogInfo("---gbGeomNode::LoadFromFile file not find,filename=%s", (char*)filename);
        return 0;
    }

    char magic[8];
    g_pVFileSys->Read(magic, 4u, file);
    magic[4] = 0;
    if (strcmp(magic, "poly")) {
        gbLogInfo("---gbGeomNode::LoadFromFile file version refused,filename=%s", (char*)filename);
        return 0;
    }

    int version;
    int numMeshes;
    g_pVFileSys->Read(&version, 4u, file);
    g_pVFileSys->Read(&numMeshes, 4u, file);

    // Initialize node description pool
    if (!s_nodeDescInitialized) {
        s_nodeDescInitialized = 1;
        s_nodeDescPoolSize = 256;
        s_nodeDescPool = (GeomNodeDesc*)malloc(sizeof(GeomNodeDesc) * 256);
        s_nodeDescCount = 0;
        atexit(s_nodeDescCleanup);
    }

    s_nodeDescCount = 0;
    int poolNeeded = numMeshes ? numMeshes : 16;
    if (poolNeeded > s_nodeDescPoolSize) {
        s_nodeDescPoolSize = poolNeeded;
        GeomNodeDesc* newPool = (GeomNodeDesc*)malloc(sizeof(GeomNodeDesc) * poolNeeded);
        if (s_nodeDescCount)
            memcpy(newPool, s_nodeDescPool, sizeof(GeomNodeDesc) * s_nodeDescCount);
        if (s_nodeDescPool)
            free(s_nodeDescPool);
        s_nodeDescPool = newPool;
    }
    s_nodeDescCount = numMeshes;
    g_pVFileSys->Read(s_nodeDescPool, sizeof(GeomNodeDesc) * numMeshes, file);

    // Read attach points (version > 100)
    if (version > 100) {
        g_pVFileSys->Read(&numAttachPoints, 4u, file);
        if (numAttachPoints) {
            gbAttachPointData* attachData = (gbAttachPointData*)operator new(sizeof(gbAttachPointData) * numAttachPoints);
            if (attachData) {
                for (int i = numAttachPoints - 1; i >= 0; i--) {
                    attachData[i].position.x = 0.0f;
                    attachData[i].position.y = 0.0f;
                    attachData[i].position.z = 0.0f;
                }
            }
            pAttachPointArray = attachData;

            for (int i = 0; i < numAttachPoints; i++) {
                gbAttachPointData* ap = &((gbAttachPointData*)pAttachPointArray)[i];
                gbMatrix4 mat;
                g_pVFileSys->Read(ap->_pad, 0x20u, file);
                g_pVFileSys->Read(&mat, 0x40u, file);
                int dummy;
                g_pVFileSys->Read(&dummy, 4u, file);
                gbVec3D origin;
                origin.x = 0.0f; origin.y = 0.0f; origin.z = 0.0f;
                mat.Transform(&origin, &ap->position);
                int nameLen;
                g_pVFileSys->Read(&nameLen, 4u, file);
                if (nameLen) {
                    char nameBuf[1024];
                    g_pVFileSys->Read(nameBuf, nameLen, file);
                    nameBuf[nameLen] = 0;
                    int r, g, b;
                    sscanf(nameBuf, "%d%d%d", &r, &g, &b);
                    ap->colorIndex = b | ((g | ((r | 0xFFFFFF00) << 8)) << 8);
                } else {
                    ap->colorIndex = -1;
                }
            }
        } else {
            pAttachPointArray = NULL;
        }
    }

    // Set lightmap directory
    if (texPath) {
        strcpy((char*)&gbStaticMesh::LightMapDir, texPath);
    } else {
        *(char*)&gbStaticMesh::LightMapDir = 0;
    }

    if (numMeshes == 1) {
        // Single mesh - load directly into this node
        gbStaticMesh* newMesh = (gbStaticMesh*)gbVisNode::pGfxMgr->NewMesh((char*)filename, MESH_STATIC);
        mesh = newMesh;
        if (!newMesh->LoadFromStream(file, version, s_nodeDescPool))
            return 0;
        if (progressCallback)
            progressCallback(1, 1);
    } else {
        // Multiple meshes - create child nodes
        for (int i = 0; i < numMeshes; i++) {
            gbGeomNode* child = new gbGeomNode();
            char nameBuf[256];
            sprintf(nameBuf, "%s_%d", filename, i);
            gbStaticMesh* childMesh = (gbStaticMesh*)gbVisNode::pGfxMgr->NewMesh(nameBuf, MESH_STATIC);
            child->mesh = childMesh;
            if (!childMesh->LoadFromStream(file, version, &s_nodeDescPool[i]))
                return 0;
            children.AddNodeOnTail(child);
            child->pParent = this;
            if (progressCallback)
                progressCallback(numMeshes, i);
        }
    }

    g_pVFileSys->CloseFile(file);
    return 1;
}

int gbGeomNode::LoadCVDFile(const char* filename) {
    s_cvdMeshCounter = 0;
    gbVFile* file = g_pVFileSys->OpenFile(filename, 0x201u);
    if (!file)
        return 0;

    char magic[8];
    g_pVFileSys->Read(magic, 4u, file);
    magic[4] = 0;

    float scale;
    if (!strcmp(magic, "cvdf"))
        scale = 0.40000001f;
    else if (!strcmp(magic, "cvds"))
        scale = 0.5f;
    else
        scale = 0.5f;

    // Check for .ani animation file
    char aniPath[256];
    char titleBuf[256];
    ((gbVFile1*)file)->GetDir(aniPath, 256);
    strcat(aniPath, ((gbVFile1*)file)->GetTitle(titleBuf, 256));
    strcat(aniPath, ".ani");

    if (g_pVFileSys->FileExistNum(aniPath)) {
        // Load animation controller (0x88 bytes allocation)
        // Clear posMatrix rows 1-2 partial (offset 0x50 in struct, 6 ints)
        animController = (gbAnimNodeGroup*)operator new(0x88u);
        if (animController) {
            memset(&animController->posMatrix.m[1][3], 0, 6 * sizeof(int));
        }
        // sub_1000E760(aniPath) - load animation
    } else {
        animController = NULL;
    }

    // Set initial rotation
    staticTransform.SetAxisAngle(0, -1.5707963f);

    int numNodes;
    gbGeomNode* nodeList[1024];
    int nodeCount = 0;
    g_pVFileSys->Read(&numNodes, 4u, file);

    int i;
    for (i = 0; i < numNodes; i++) {
        gbGeomNode* child = new gbGeomNode();
        child->LoadCVDFromStream(file, scale);
        nodeList[nodeCount++] = child;

        int numChildren;
        g_pVFileSys->Read(&numChildren, 4u, file);
        for (int j = 0; j < numChildren; j++) {
            LoadCVDFromStream(file, scale, nodeList, nodeCount);
        }
    }

    // Add all nodes as children
    for (i = 0; i < nodeCount; i++) {
        children.AddNodeOnTail(nodeList[i]);
        nodeList[i]->pParent = this;
        if (nodeList[i]->animMaxTime > animMaxTime)
            animMaxTime = nodeList[i]->animMaxTime;
    }

    g_pVFileSys->CloseFile(file);
    return 1;
}

void gbGeomNode::LoadCVDFromStream(gbVFile* file, float scale) {
    char hasAnim;
    g_pVFileSys->Read(&hasAnim, 1u, file);
    if (!hasAnim)
        return;

    hasAnimation = 1;

    // Create translation curve (vtable at off_100F55F0)
    PosCtrl = (gbAnimCurve*)operator new(0x14u);
    // sub_1000FAB0(file) - read translation keyframes

    // Create scale curve (vtable at off_100F55EC)
    pAnimScale = (gbAnimCurve*)operator new(0x14u);
    // sub_1000FAB0(file) - read scale keyframes

    // Create rotation curve (vtable at off_100F55E8)
    pAnimRotate = (gbAnimCurve*)operator new(0x14u);
    // sub_1000FB60(file) - read rotation keyframes

    // Read scale value
    g_pVFileSys->Read(&scaleValue, 4u, file);

    // Create mesh
    char nameBuf[300];
    sprintf(nameBuf, "%s+%d", file->fullPath, s_cvdMeshCounter);
    mesh = (gbStaticMesh*)gbVisNode::pGfxMgr->NewMesh(nameBuf, (gbMeshType)1);
    ++s_cvdMeshCounter;

    // sub_10011C60(file, scale) - read mesh data with scale

    // Compute max animation time
    // animMaxTime = max of all curve durations

    // Read and discard transform matrix
    gbMatrix4 tempMat;
    g_pVFileSys->Read(&tempMat, 0x40u, file);
}

void gbGeomNode::LoadCVDFromStream(gbVFile* file, float scale, gbGeomNode** outNodes, int& outCount) {
    gbGeomNode* node = new gbGeomNode();
    node->LoadCVDFromStream(file, scale);
    outNodes[outCount++] = node;

    int numChildren;
    g_pVFileSys->Read(&numChildren, 4u, file);
    for (int i = 0; i < numChildren; i++) {
        LoadCVDFromStream(file, scale, outNodes, outCount);
    }
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
        memcpy(&worldTransform, &((gbGeomNode*)pParent)->worldTransform, sizeof(gbMatrix4));
    else
        worldTransform.LoadIdentity();

    if (hasAnimation) {
        float time = (float)currentTime;
        gbVec3D result;

        if (PosCtrl) {
            PosCtrl->GetValue(&result, time);
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

// Blade attach point transform buffer (static, 256 entries × 4 vec3s)
struct gbBladeAttachPoint {
    gbVec3D position;
    int colorIndex;
};
static gbBladeAttachPoint s_bladeTransforms[256];
static int s_bladeInitialized = 0;

extern double g_CurrentTime;

static void __cdecl gbBladeSystem_Submit(gbBladeAttachPoint* transforms, int count, gbGeomNode* node) {
    gbVisNode::pSceneGraph->bladeMgr->Submit(transforms, count, node);
}

void gbGeomNode::AttachSelf(gbRenderEffect* effect) {
    if (!mesh)
        return;

    gbVec3D renderPos;
    renderPos.x = 0.0f;
    renderPos.y = 0.0f;
    renderPos.z = 0.0f;
    int sectionIndex = 0;
    gbMatrix4 localMatrix;
    localMatrix.LoadIdentity();

    gbMatrixStack* matStack = gbVisNode::pGfxMgr->pMatrixStack[1];
    matStack->Push();
    matStack->MultMatrix(&worldTransform);

    if (gbVisNode::pGfxMgr->ClipBoundVolume(&mesh->m_aabb)) {
        matStack->Pop();
        return;
    }

    // Blade attach point processing
    if (bBlade && pAttachPointArray) {
        if (!s_bladeInitialized) {
            s_bladeInitialized = 1;
            memset(s_bladeTransforms, 0, sizeof(s_bladeTransforms));
        }

        const gbMatrix4& worldMat = gbVisNode::pGfxMgr->GetWorldMatrix();
        int ap = 0;
        if (numAttachPoints > 0) {
            gbBladeAttachPoint* dst = s_bladeTransforms;
            gbAttachPointData* src = (gbAttachPointData*)pAttachPointArray;
            do {
                worldMat.Transform(&src->position, &dst->position);
                dst->colorIndex = src->colorIndex;
                ++ap;
                ++dst;
                ++src;
            } while (ap < numAttachPoints);
        }
        gbBladeSystem_Submit(s_bladeTransforms, numAttachPoints, this);
    }

    // Section iteration - submit render objects
    int numSec = mesh->m_numSections;
    sectionIndex = 0;
    if (numSec > 0) {
        gbMeshSection* sec = mesh->m_sections;
        do {
            gbRenderInfoObj* renderObj = gbVisNode::pSceneGraph->NewOneRenderObj(this);
            gbMatrix4* topMat = matStack->GetTop();
            topMat->Transform(&sec->m_boundCenter, &renderPos);
            gbVisNode::pSceneGraph->CalEffectiveVolMod(renderObj, renderPos, sec->m_hasMultiTex);

            unsigned int flags = 1;
            if (mesh->m_vertFVF & 4)
                flags = 1025;
            if (sec->m_hasMultiTex)
                flags |= 2u;

            float blendVal;
            if (sec->m_blendMode == 1 || gbVisNode::GetBlend(blendVal)) {
                flags |= 0x40u;
            } else if (sec->m_blendMode == 2) {
                flags |= 0x80u;
            } else if (sec->m_blendMode == 3) {
                flags |= 0x100u;
            }

            if ((flags & 0x400) == 0) {
                if (renderObj->volModSlotA[0])
                    flags |= 4u;
                if (renderObj->volModSlotA[1] && (flags & 2) == 0)
                    flags |= 8u;
            }

            int gfxMode = gbVisNode::pGfxMgr->FogParam.enable;
            if (gfxMode == 2) {
                flags |= 0x20u;
            } else if (gfxMode == 1) {
                flags |= 0x10u;
            }

            renderObj->Param = sectionIndex;
            renderObj->Flags = (sec->m_blendMode == 0) ? 1 : 0;

            // Animated texture frame selection
            if (sec->m_numAnimFrames) {
                int frameIdx = (int)(__int64)(g_CurrentTime * 1000.0) / sec->m_animFrameInterval % sec->m_numAnimFrames;
                sec->m_textures[sec->m_animTexSlot] = *(gbTexture**)((char*)sec->m_animTexArray + 4 * frameIdx);
            }

            renderObj->EffectFlag = flags;
            renderObj->pTexArray = &sec->m_textures[0];
            renderObj->Z = (localMatrix.m[3][3] != 0.0f) ? (void*)&localMatrix : NULL;

            if (sec->m_overrideEffect)
                renderObj->pEffect = (gbRenderEffect*)sec->m_overrideEffect;
            else
                renderObj->pEffect = gbVisNode::pGfxMgr->GetEffectMgr()->GetRenderEffect(flags);

            numSec = mesh->m_numSections;
            ++sectionIndex;
            ++sec;
        } while (sectionIndex < numSec);
    }

    // Shadow volume submission
    if (cullNext)
        gbVisNode::pSceneGraph->NewShadowVolume(this);

    matStack->Pop();
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

            gbMatrixStack* matStack = gbVisNode::pGfxMgr->pMatrixStack[1];
            matStack->Push();
            matStack->LoadMatrix(&renderInfo->worldMatrix);

            mesh->DrawSubSetBase(renderInfo->Param, renderInfo);

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

            gbMatrixStack* matStack = gbVisNode::pGfxMgr->pMatrixStack[1];
            matStack->Push();
            matStack->LoadMatrix(&renderInfo->worldMatrix);

            mesh->RenderShadowVolume(this, renderInfo);

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
        gbAABBox* aabb = &mesh->m_aabb;
        float cx = (aabb->vMin.x + aabb->vMax.x) * 0.5f;
        float cy = (aabb->vMin.y + aabb->vMax.y) * 0.5f;
        float cz = (aabb->vMin.z + aabb->vMax.z) * 0.5f;
        float dx = aabb->vMax.x - aabb->vMin.x;
        float dy = aabb->vMax.y - aabb->vMin.y;
        float dz = aabb->vMax.z - aabb->vMin.z;

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
    for (int i = 0; i < children.m_numNode; i++) {
        gbGeomNode* child = (gbGeomNode*)children[i];
        child->SetAnimLoop(loop);
    }
}

void gbGeomNode::EnableShadow(int enable) {
    gbVisNode::EnableShadow(enable);
    if (enable) {
        mesh->ComputeShadowVolume();
    }
}

int gbGeomNode::GetAABBox(gbAABBox* box) {
    if (!mesh) return 0;

    memcpy(box, &mesh->m_aabb, sizeof(gbAABBox));
    return 1;
}

/* ======== Blade functions (delegates to blade manager) ======== */

// 0x100117e0 (26B)
void gbGeomNode::SetBladeTime(float time) {
    gbVisNode::pSceneGraph->bladeMgr->SetBladeTime(this, time);
}

// 0x10011800 (26B)
void gbGeomNode::SetBladeTimeScale(float scale) {
    gbVisNode::pSceneGraph->bladeMgr->SetBladeTimeScale(this, scale);
}

// 0x10011820 (23B)
gbVec3D* gbGeomNode::GetLastBladePos(gbGeomNode* node) {
    return (gbVec3D*)gbVisNode::pSceneGraph->bladeMgr->GetLastBladePos(this);
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

    if (mesh) {
        gbAABBox* aabb = &mesh->m_aabb;
        // extent = vMax - vMin
        box->xlen = aabb->vMax.x - aabb->vMin.x;
        box->ylen = aabb->vMax.y - aabb->vMin.y;
        box->zlen = aabb->vMax.z - aabb->vMin.z;

        // center = (vMin + vMax) * 0.5
        gbVec3D center;
        center.x = (aabb->vMin.x + aabb->vMax.x) * 0.5f;
        center.y = (aabb->vMin.y + aabb->vMax.y) * 0.5f;
        center.z = (aabb->vMin.z + aabb->vMax.z) * 0.5f;
        box->trans.LeftTranslate(center);
    } else {
        box->xlen = 0.0f;
        box->ylen = 0.0f;
        box->zlen = 0.0f;
    }
    return box;
}

static int s_totalOBBoxNodes[256];

static void CollectMeshNodes(int* nodeArray, int* count, gbGeomNode* node) {
    if (node->mesh != NULL) {
        nodeArray[*count] = (int)node;
        (*count)++;
    }
    gbChain1DNode* child = node->children.pHead;
    node->children.pIterator = child;
    while (child != NULL) {
        CollectMeshNodes(nodeArray, count, (gbGeomNode*)child);
        child = node->children.pIterator->pNext;
        node->children.pIterator = child;
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
        CollectMeshNodes(s_totalOBBoxNodes, &nodeCount, child);
        child = (gbGeomNode*)((gbChain1DNode*)children.pIterator)->pNext;
        children.pIterator = (gbChain1DNode*)child;
    }

    if (nodeCount == 0) {
        memcpy(box, &worldTransform, sizeof(gbMatrix4));
        if (mesh) {
            gbAABBox* aabb = &mesh->m_aabb;
            box->xlen = aabb->vMax.x - aabb->vMin.x;
            box->ylen = aabb->vMax.y - aabb->vMin.y;
            box->zlen = aabb->vMax.z - aabb->vMin.z;
            gbVec3D center;
            center.x = (aabb->vMin.x + aabb->vMax.x) * 0.5f;
            center.y = (aabb->vMin.y + aabb->vMax.y) * 0.5f;
            center.z = (aabb->vMin.z + aabb->vMax.z) * 0.5f;
            box->trans.LeftTranslate(center);
        } else {
            box->xlen = 0.0f;
            box->ylen = 0.0f;
            box->zlen = 0.0f;
        }
        return box;
    }

    if (nodeCount == 1) {
        gbGeomNode* n = (gbGeomNode*)s_totalOBBoxNodes[0];
        memcpy(box, &n->worldTransform, sizeof(gbMatrix4));
        if (n->mesh) {
            gbAABBox* aabb = &n->mesh->m_aabb;
            box->xlen = aabb->vMax.x - aabb->vMin.x;
            box->ylen = aabb->vMax.y - aabb->vMin.y;
            box->zlen = aabb->vMax.z - aabb->vMin.z;
            gbVec3D center;
            center.x = (aabb->vMin.x + aabb->vMax.x) * 0.5f;
            center.y = (aabb->vMin.y + aabb->vMax.y) * 0.5f;
            center.z = (aabb->vMin.z + aabb->vMax.z) * 0.5f;
            box->trans.LeftTranslate(center);
        } else {
            box->xlen = 0.0f;
            box->ylen = 0.0f;
            box->zlen = 0.0f;
        }
        return box;
    }

    // Multiple nodes: compute combined AABB
    float minX = 3.4028235e+38f, minY = 3.4028235e+38f, minZ = 3.4028235e+38f;
    float maxX = -3.4028235e+38f, maxY = -3.4028235e+38f, maxZ = -3.4028235e+38f;
    gbAABBox tempBox;

    for (int i = 0; i < nodeCount; i++) {
        gbGeomNode* n = (gbGeomNode*)s_totalOBBoxNodes[i];
        gbMatrix4* wt = &n->worldTransform;
        memcpy(&tempBox, &n->mesh->m_aabb, sizeof(gbAABBox));
        tempBox.Transform(wt);

        if (tempBox.vMin.x < minX) minX = tempBox.vMin.x;
        if (tempBox.vMin.y < minY) minY = tempBox.vMin.y;
        if (tempBox.vMin.z < minZ) minZ = tempBox.vMin.z;
        if (tempBox.vMax.x > maxX) maxX = tempBox.vMax.x;
        if (tempBox.vMax.y > maxY) maxY = tempBox.vMax.y;
        if (tempBox.vMax.z > maxZ) maxZ = tempBox.vMax.z;
    }

    box->xlen = maxX - minX;
    box->ylen = maxY - minY;
    box->zlen = maxZ - minZ;
    box->trans.LoadIdentity();
    box->trans.m[3][0] = (maxX + minX) * 0.5f;
    box->trans.m[3][1] = (maxY + minY) * 0.5f;
    box->trans.m[3][2] = (maxZ + minZ) * 0.5f;
    return box;
}

/* ======== Simple accessors ======== */

void gbGeomNode::EnableBlade(int enable) {
    bBlade = enable;
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
