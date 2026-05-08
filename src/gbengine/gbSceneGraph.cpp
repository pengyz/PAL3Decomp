/**
 * gbengine.dll - gbSceneGraph
 * Scene graph management implementation
 */

#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbVisNode.h"
#include "gbengine/gbChain.h"
#include "gbengine/gbengine_internal.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Static globals referenced in decompilation
gbGfxManager* gbVisNode_pGfxMgr = NULL;
gbSceneGraph* gbVisNode_pSceneGraph = NULL;


/* ======== gbLightObj method implementations ======== */

float gbLightObj::GetEffectOnPoint(const gbVec3D& point, int useAttenuation) {
    if (!enabled) return 0.0f;

    gbVec3D delta;
    delta.x = point.x - sysLight.position.x;
    delta.y = point.y - sysLight.position.y;
    delta.z = point.z - sysLight.position.z;

    float distSq = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
    float dist = sqrtf(distSq);

    if (dist > range) return 0.0f;

    if (useAttenuation) {
        float atten = attenuation0 + attenuation1 * dist + attenuation2 * distSq;
        if (atten > 0.0f) {
            return 1.0f / atten;
        }
    }

    return 1.0f;
}

void gbLightObj::Compute(gbVolModNode* volmod) {
    // 0x10013350 (581B) - Computes D3DLIGHT9 sysLight from light parameters
    // Transforms position/direction by the gbVolModNode's world matrix
    // Sets sysLight.type based on lightType: 0->POINT(1), 1->SPOT(2), 2->DIR(3)

    gbMatrix4* worldMatrix = &volmod->worldMatrix;

    // Set D3D light type
    if (lightType == 0) {
        sysLight.type = 1;  // D3DLIGHT_POINT
    } else if (lightType == 1) {
        sysLight.type = 2;  // D3DLIGHT_SPOT
    } else if (lightType == 2) {
        sysLight.type = 3;  // D3DLIGHT_DIRECTIONAL
    }
    sysLight.type = 1;

    // Copy diffuse color to sysLight
    sysLight.diffuse.r = diffuse.r;
    sysLight.diffuse.g = diffuse.g;
    sysLight.diffuse.b = diffuse.b;
    sysLight.diffuse.a = diffuse.a;

    // Specular defaults (no separate specular field in gbVolumeModifier)
    sysLight.specular.r = diffuse.r;
    sysLight.specular.g = diffuse.g;
    sysLight.specular.b = diffuse.b;
    sysLight.specular.a = diffuse.a;

    // Copy ambient color
    sysLight.ambient.r = ambient.r;
    sysLight.ambient.g = ambient.g;
    sysLight.ambient.b = ambient.b;
    sysLight.ambient.a = ambient.a;

    // Set range and falloff
    sysLight.range = range;
    sysLight.falloff = 1.0f;

    // Compute attenuation values
    sysLight.attenuation0 = 1.0f;
    sysLight.attenuation1 = 0.0f;
    sysLight.attenuation2 = 0.0f;

    // Transform position/direction based on light type
    gbVec3D localPos;
    localPos.x = 0.0f; localPos.y = 0.0f; localPos.z = 0.0f;
    gbVec3D localDir;
    localDir.x = 0.0f; localDir.y = -1.0f; localDir.z = 0.0f;

    if (lightType == 0) {
        // Point light: transform position
        worldMatrix->Transform(&localPos, &sysLight.position);
    } else if (lightType == 1) {
        // Spot light: transform position and rotate direction
        worldMatrix->Transform(&localPos, &sysLight.position);
        worldMatrix->Rotate(&localDir, &sysLight.direction);
    } else {
        // Directional light: rotate direction, set position far away
        worldMatrix->Rotate(&localDir, &sysLight.direction);
        sysLight.range = 200000.0f;
        sysLight.position.x = sysLight.direction.x * -100000.0f;
        sysLight.position.y = sysLight.direction.y * -100000.0f;
        sysLight.position.z = sysLight.direction.z * -100000.0f;
    }
}


/* ======== gbSceneGraph method implementations ======== */

// 0x10014b10 (322B) - Constructor
gbSceneGraph::gbSceneGraph(gbGfxManager* gfxMgr, const gbVec3D& param2, float param3) {
    int i;

    // Initialize shadow info pool matrices (16 entries at +0x10, each 112 bytes)
    for (i = 0; i < 16; i++) {
        shadowInfoPool[i].worldMatrix.LoadIdentity();
    }

    // Initialize matrix pool (256 identity matrices at +0xB14)
    for (i = 0; i < 256; i++) {
        matrixPool[i].LoadIdentity();
    }

    // Allocate render object pool (0x70000 bytes = 4096 objects × 112 bytes)
    renderObjPool = malloc(0x70000);
    numRenderObjs = 0;

    pGfxManager = gfxMgr;
    gbVisNode::pGfxMgr = gfxMgr;
    gbVisNode::pSceneGraph = this;

    skyBoxNode = NULL;
    activeCamera = NULL;

    // Create shadow quad effect
    shadowQuadEffect = gfxMgr->GetEffectMgr()->NewRenderEffect("gfx/script/shadow.gbf", 0);

    // Create blade manager
    bladeMgr = new gbBladeMgr;
    bladeMgr->Init(gfxMgr);

    // Create root scene node
    gbVisNode* root = new gbVisNode();
    rootNode = root;

    // Create spatial partitioning for volume modifiers
    volModNodePool = NULL; // TODO: actual spatial structure (sub_100145A0)

    numVolModNodes = 0;
    numShadowVolumes = 0;
    bSceneActive = 1;
}

// 0x10014c60 - Destructor
extern void sub_10014650(void* pool);
extern void sub_1000ECC0(void* bladeMgr);

gbSceneGraph::~gbSceneGraph(void) {
    if (volModNodePool) {
        sub_10014650(volModNodePool);
        operator delete(volModNodePool);
    }
    if (rootNode) {
        delete rootNode;
    }
    if (bladeMgr) {
        sub_1000ECC0(bladeMgr);
        operator delete(bladeMgr);
    }
    ((gbRefObject*)shadowQuadEffect)->Release();
    skyBoxNode = NULL;
    free(renderObjPool);
}

// 0x10014cd0 (13B) - Set sky box node
void gbSceneGraph::AddSkyBox(gbVisNode* node) {
    skyBoxNode = node;
}

// 0x10014ce0 (37B) - Begin scene rendering
void gbSceneGraph::Begin(gbCamera* camera) {
    bSceneActive = 1;
    activeCamera = camera;
    numRenderObjs = 0;
    numVolModNodes = 0;
    numShadowVolumes = 0;
}

// 0x10014d10 (83B) - Allocate a render object from pool
gbRenderInfoObj* gbSceneGraph::NewOneRenderObj(gbVisNode* node) {
    gbRenderInfoObj* obj = &((gbRenderInfoObj*)renderObjPool)[numRenderObjs];
    obj->pNode = node;
    obj->renderPriority = node->renderPriority;
    memcpy(&obj->worldMatrix, pGfxManager->pMatrixStack[1]->GetTop(), sizeof(gbMatrix4));
    numRenderObjs++;
    return obj;
}

// 0x10014d70 (25B) - Get next shadow volume slot from pool
gbRenderInfoObj* gbSceneGraph::NewShadowVolume(gbVisNode* node) {
    return &shadowInfoPool[numShadowVolumes];
}

// 0x10014d90 (33B) - Add volume modifier node
void gbSceneGraph::AddVolModNode(gbVolModNode* node) {
    volModNodes[numVolModNodes++] = node;
}

// 0x10014dc0 (322B) - Calculate effective volume modifiers for a point
void gbSceneGraph::CalEffectiveVolMod(gbRenderInfoObj* renderInfo, const gbVec3D& position, int flags) {
    struct VolModEntry {
        gbVolModNode* node;
        float effect;
    };
    VolModEntry entries[256];
    int numEntries = 0;
    int i;

    for (i = 0; i < numVolModNodes; i++) {
        gbVolModNode* vm = volModNodes[i];
        gbVolumeModifier* modObj = vm->pVolMod;
        float effect = modObj->GetEffectOnPoint(position, flags);

        if (effect != 0.0f) {
            entries[numEntries].node = vm;
            entries[numEntries].effect = effect;
            numEntries++;
        }
    }

    // Sort by effect strength (descending)
    // qsort(entries, numEntries, sizeof(VolModEntry), CompareFunction);

    int countA = 0, countB = 0;

    for (i = 0; i < numEntries; i++) {
        gbVolModNode* vm = entries[i].node;
        gbVolumeModifier* modObj = vm->pVolMod;

        if (modObj->GetType()) {
            // Directional lights go to slot B
            if (countB < 2) {
                renderInfo->volModSlotB[countB] = vm;
                countB++;
            }
        } else {
            // Point/spot lights go to slot A
            if (countA < 2) {
                renderInfo->volModSlotA[countA] = vm;
                countA++;
            }
        }
    }

    // Clear unused slots
    if (countA < 2) memset(&renderInfo->volModSlotA[countA], 0, (2 - countA) * sizeof(void*));
    if (countB < 2) memset(&renderInfo->volModSlotB[countB], 0, (2 - countB) * sizeof(void*));
}

// 0x100154C0 - Global for qsort compare function (dword_1013BCE4)
static void* s_pRenderObjPool;

// Compare function for qsort: sort render objects by effect pointer
// so that objects with the same effect are batched together
static int __cdecl RenderObjCompare(const void* a, const void* b) {
    int idxA = *(const int*)a;
    int idxB = *(const int*)b;
    gbRenderInfoObj* pool = (gbRenderInfoObj*)s_pRenderObjPool;
    // Sort by: isOpaque (opaque first), then by effect pointer
    int opaqueA = pool[idxA].isOpaque & 1;
    int opaqueB = pool[idxB].isOpaque & 1;
    if (opaqueA != opaqueB)
        return opaqueB - opaqueA;  // opaque (1) before transparent (0)
    // Within same opacity class, sort by effect pointer for batching
    if (pool[idxA].pEffect < pool[idxB].pEffect) return -1;
    if (pool[idxA].pEffect > pool[idxB].pEffect) return 1;
    return 0;
}

// 0x10014a90 (63B) - Recursively add node and all descendants without clip testing
// Called when a node is fully inside the frustum
static void CollectAllNodes(int* outArray, int* pCount, int node)
{
    int* children;
    int i;

    outArray[*pCount] = node;
    *pCount = *pCount + 1;
    children = (int*)(node + 0x20);
    i = 8;
    do {
        if (*children != 0) {
            CollectAllNodes(outArray, pCount, *children);
        }
        children = children + 1;
        i = i - 1;
    } while (i != 0);
}

// 0x100149c0 (195B) - Recursive frustum culling traversal of spatial octree
// Tests node against camera frustum and recurses into children
static void CollectVisibleNodesRecursive(int* outArray, int* pCount, gbCamera* camera, int node, unsigned int clipMask)
{
    float extent;
    float extentVec[3];
    unsigned int clipResult;
    int* children;
    int i;

    extent = *(float*)(node + 0x18) + *(float*)(node + 0x14);
    extentVec[0] = extent;
    extentVec[1] = extent;
    extentVec[2] = extent;
    clipResult = camera->ClipAABBox((gbVec3D*)(node + 8), (gbVec3D*)extentVec, clipMask);
    if (clipResult & 0x80000000) {
        return;
    }
    if (clipResult == 0x3f) {
        // Fully inside frustum - add this node and all children without further testing
        outArray[*pCount] = node;
        *pCount = *pCount + 1;
        children = (int*)(node + 0x20);
        i = 8;
        do {
            if (*children != 0) {
                CollectAllNodes(outArray, pCount, *children);
            }
            children = children + 1;
            i = i - 1;
        } while (i != 0);
        return;
    }
    // Partially visible - add this node and recurse children with updated clip mask
    i = *pCount;
    outArray[i] = node;
    *pCount = *pCount + 1;
    children = (int*)(node + 0x20);
    i = 8;
    do {
        if (*children != 0) {
            CollectVisibleNodesRecursive(outArray, pCount, camera, *children, clipResult);
        }
        children = children + 1;
        i = i - 1;
    } while (i != 0);
}

// 0x10014990 (44B) - Collect visible nodes from camera frustum
// __thiscall on spatial partition structure (ECX = volModNodePool)
// Returns count of visible root-level nodes written to outArray
static int CollectVisibleNodes(int* outArray, gbCamera* camera, void* spatialRoot)
{
    int count = 0;
    int rootNode = *(int*)spatialRoot;
    CollectVisibleNodesRecursive(outArray, &count, camera, rootNode, 0);
    return count;
}


// 0x10014f40 (1403B) - End scene rendering (render all objects)
void gbSceneGraph::End(void) {
    int sortIndices[4096];
    int visibleNodes[4096];
    int i, numVisible, numOpaque;
    gbRenderEffect* curEffect;
    gbRenderEffect* nextEffect;
    int numPasses;
    int pass;
    int batchStart;
    gbMatrixStack* worldStack;
    gbMatrixStack* viewStack;

    // Phase 1: Traverse scene and submit visible nodes
    if (bSceneActive) {
        if (activeCamera) {
            numVisible = CollectVisibleNodes(visibleNodes, activeCamera, volModNodePool);
            if (numVisible > 0) {
                for (i = 0; i < numVisible; i++) {
                    gbVisNode* node = (gbVisNode*)visibleNodes[i];
                    // Walk children linked list, calling Attach(NULL) on each
                    gbVisNode* child = (gbVisNode*)*(int*)((char*)node + 64);
                    while (child) {
                        child->Attach(NULL);
                        child = (gbVisNode*)*(int*)((char*)child + 76);
                    }
                }
            }
        }
        // Submit sky box if present
        if (skyBoxNode) {
            skyBoxNode->Attach(NULL);
        }
    }

    // Phase 2: Build sort index array
    int numObjs = numRenderObjs;
    for (i = 0; i < numObjs; i++) {
        sortIndices[i] = i;
    }

    // Sort render objects for batching (opaque first, then by effect)
    s_pRenderObjPool = renderObjPool;
    qsort(sortIndices, numObjs, sizeof(int), RenderObjCompare);

    // Push world matrix stack
    worldStack = pGfxManager->pMatrixStack[1];
    worldStack->Push();

    // Find split point between opaque and transparent objects
    numOpaque = numObjs;
    for (i = 0; i < numObjs; i++) {
        gbRenderInfoObj* obj = &((gbRenderInfoObj*)renderObjPool)[sortIndices[i]];
        if ((obj->isOpaque & 1) == 0) {
            numOpaque = i;
            break;
        }
    }

    // Phase 3: Render opaque objects (sorted by effect for batching)
    pGfxManager->pEffectMgr->m_nFrameCounter = 1;

    if (numOpaque > 0) {
        curEffect = ((gbRenderInfoObj*)renderObjPool)[sortIndices[0]].pEffect;
        batchStart = 0;

        for (i = 0; i < numOpaque; i++) {
            nextEffect = ((gbRenderInfoObj*)renderObjPool)[sortIndices[i]].pEffect;
            if (nextEffect != curEffect) {
                // Flush batch for current effect
                numPasses = curEffect->Begin();
                for (pass = 0; pass < numPasses; pass++) {
                    curEffect->Pass(pass);
                    for (int j = batchStart; j < i; j++) {
                        int idx = sortIndices[j];
                        gbRenderInfoObj* info = &((gbRenderInfoObj*)renderObjPool)[idx];
                        info->pNode->Render(info);
                    }
                }
                curEffect->End();
                batchStart = i;
                curEffect = nextEffect;
            }
        }

        // Flush final opaque batch
        numPasses = curEffect->Begin();
        for (pass = 0; pass < numPasses; pass++) {
            curEffect->Pass(pass);
            for (int j = batchStart; j < numOpaque; j++) {
                int idx = sortIndices[j];
                gbRenderInfoObj* info = &((gbRenderInfoObj*)renderObjPool)[idx];
                info->pNode->Render(info);
            }
        }
        curEffect->End();
    }

    pGfxManager->pEffectMgr->m_nFrameCounter = 0;

    // Phase 4: Render transparent objects (same batching logic)
    pGfxManager->pEffectMgr->m_nFrameCounter = 1;

    if (numObjs > numOpaque) {
        curEffect = ((gbRenderInfoObj*)renderObjPool)[sortIndices[numOpaque]].pEffect;
        batchStart = numOpaque;

        for (i = numOpaque; i < numObjs; i++) {
            nextEffect = ((gbRenderInfoObj*)renderObjPool)[sortIndices[i]].pEffect;
            if (nextEffect != curEffect) {
                numPasses = curEffect->Begin();
                for (pass = 0; pass < numPasses; pass++) {
                    curEffect->Pass(pass);
                    for (int j = batchStart; j < i; j++) {
                        int idx = sortIndices[j];
                        gbRenderInfoObj* info = &((gbRenderInfoObj*)renderObjPool)[idx];
                        info->pNode->Render(info);
                    }
                }
                curEffect->End();
                batchStart = i;
                curEffect = nextEffect;
            }
        }

        // Flush final transparent batch
        numPasses = curEffect->Begin();
        for (pass = 0; pass < numPasses; pass++) {
            curEffect->Pass(pass);
            for (int j = batchStart; j < numObjs; j++) {
                int idx = sortIndices[j];
                gbRenderInfoObj* info = &((gbRenderInfoObj*)renderObjPool)[idx];
                info->pNode->Render(info);
            }
        }
        curEffect->End();
    }

    pGfxManager->pEffectMgr->m_nFrameCounter = 0;

    // Phase 5: Render blade trails
    bladeMgr->Update();
    bladeMgr->Render();

    // Phase 6: Render shadow volumes
    if (numShadowVolumes > 0) {
        gbRenderInfoObj* shadowInfo = shadowInfoPool;
        for (i = 0; i < numShadowVolumes; i++) {
            shadowInfo->pNode->RenderShadowVolume(shadowInfo);
            shadowInfo++;
        }
    }

    // Phase 7: Render shadow quad overlay (if any shadow volumes were rendered)
    if (numShadowVolumes) {
        viewStack = pGfxManager->pMatrixStack[0];
        gbUIQuad quad;
        gbTextureArray texArr;

        worldStack->Push();
        worldStack->LoadIdentity();
        viewStack->Push();
        viewStack->LoadIdentity();

        gbDynVertBuf* dynVB = pGfxManager->pVertPoolMgr->GetDynVertBuf(0x15);

        quad.x1 = -1.0f;
        quad.y1 = -1.0f;
        quad.x2 = 1.0f;
        quad.y2 = 1.0f;
        quad.u1 = 0.0f;
        quad.v1 = 0.0f;
        quad.u2 = 0.0f;
        quad.v2 = 0.0f;
        quad.z = 0.0f;
        quad.color = 0x50000000;

        memset(&texArr, 0, sizeof(texArr));

        dynVB->RenderUIQuad(&quad, 1, shadowQuadEffect, &texArr);

        worldStack->Pop();
        viewStack->Pop();
    }

    // Pop world matrix stack
    worldStack->Pop();

    // Reset scene state
    bSceneActive = 1;
    activeCamera = NULL;
    numRenderObjs = 0;
    numVolModNodes = 0;
    numShadowVolumes = 0;
}

// 0x100155a0 - Add a visible node to scene
void gbSceneGraph::AddVisNode(gbVisNode* node) {
    if (!rootNode || !node) return;
    rootNode->children.AddNode((gbChain1DNode*)node);
    node->pParent = (gbNBTreeNode*)rootNode;
}

// 0x100155d0 - Remove a visible node from scene
void gbSceneGraph::DelVisNode(gbVisNode* node) {
    if (!node) return;
    gbNBTreeNode* parent = node->pParent;
    if (!parent) return;
    parent->children.DelNodeFromChain((gbChain1DNode*)node);
}

// 0x10015600 (22B) - Set blade time scale
void gbSceneGraph::SetBladeTimeScale(float scale) {
    bladeMgr->globalTimeScale = scale;
}

// 0x10015620 (11B) - Reset blade manager
void gbSceneGraph::ResetBladeMgr(void) {
    bladeMgr->Reset();
}

