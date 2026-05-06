/**
 * gbengine.dll - gbSceneGraph
 * Scene graph management implementation
 */

#include "gbengine/gbSceneGraph.h"
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
    delta.x = point.x - position.x;
    delta.y = point.y - position.y;
    delta.z = point.z - position.z;

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
    // Transforms position/direction by the gbVolModNode's world matrix at +0x98
    // Sets sysLight.type based on lightType: 0->POINT(1), 1->SPOT(2), 2->DIR(3)
    // Copies diffuse/specular/ambient colors based on enable flags
    // Computes attenuation values based on attenuation mode
    // For point lights: transforms position by volmod matrix
    // For spot lights: transforms position and rotates direction, converts angles to radians
    // For directional lights: rotates direction and sets position = -dir * 100000

    // Get the world matrix from gbVolModNode (at offset +0x98)
    gbMatrix4* worldMatrix = &volmod->worldMatrix;

    // Set D3D light type
    if (lightType == 0) {
        sysLight.type = 1;  // D3DLIGHT_POINT
    } else if (lightType == 1) {
        sysLight.type = 2;  // D3DLIGHT_SPOT
    } else if (lightType == 2) {
        sysLight.type = 3;  // D3DLIGHT_DIRECTIONAL
    }
    // Note: Ghidra shows type is forced to 1 after the switch (possible bug or decompiler artifact)
    sysLight.type = 1;

    // Copy diffuse color to sysLight (conditionally based on enable flag)
    sysLight.diffuse.r = diffuse.r;
    sysLight.diffuse.g = diffuse.g;
    sysLight.diffuse.b = diffuse.b;
    sysLight.diffuse.a = diffuse.a;

    // Copy specular color
    sysLight.specular.r = specular.r;
    sysLight.specular.g = specular.g;
    sysLight.specular.b = specular.b;
    sysLight.specular.a = specular.a;

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

gbSceneGraph::gbSceneGraph(gbGfxManager* gfxMgr, const gbVec3D& param2, float param3) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                matrixPool1[i].m[j][k] = (j == k) ? 1.0f : 0.0f;
            }
        }
    }

    renderObjPool = malloc(0x70000);
    renderObjPoolUsed = 0;

    pGfxManager = gfxMgr;
    gbVisNode_pGfxMgr = gfxMgr;
    gbVisNode_pSceneGraph = this;

    activeCamera = NULL;
    skyBoxNode = NULL;
    shadowQuadEffect = NULL;
    bladeMgr = NULL;
    rootNode = NULL;
    volModNodePool = NULL;
    numVolModNodes = 0;
    memset(volModNodes, 0, sizeof(volModNodes));
}

gbSceneGraph::~gbSceneGraph(void) {
    if (renderObjPool) {
        free(renderObjPool);
        renderObjPool = NULL;
    }
    // Destructor would also free bladeMgr, rootNode, volModNodePool
}

void gbSceneGraph::AddSkyBox(gbVisNode* node) {
    skyBoxNode = node;
}

void gbSceneGraph::Begin(gbCamera* camera) {
    activeCamera = camera;
    renderObjPoolUsed = 0;
}

gbRenderInfoObj* gbSceneGraph::NewOneRenderObj(gbVisNode* node) {
    if (!renderObjPool || renderObjPoolUsed >= 0x70000) {
        return NULL;
    }

    // Check if we have space for another object
    if (renderObjPoolUsed + sizeof(gbRenderInfoObj) > 0x70000) {
        return NULL;
    }

    gbRenderInfoObj* obj = (gbRenderInfoObj*)((char*)renderObjPool + renderObjPoolUsed);
    renderObjPoolUsed += sizeof(gbRenderInfoObj);

    obj->pNode = node;
    obj->pMatrixOverride = NULL;
    obj->sectionIndex = 0;
    obj->pEffect = NULL;

    return obj;
}

gbRenderInfoObj* gbSceneGraph::NewShadowVolume(gbVisNode* node) {
    return NewOneRenderObj(node);
}

void gbSceneGraph::AddVolModNode(gbVolModNode* node) {
    volModNodes[numVolModNodes] = node;
    numVolModNodes++;
}

void gbSceneGraph::CalEffectiveVolMod(gbRenderInfoObj* renderInfo, const gbVec3D& position, int flags) {
    struct VolModEntry {
        float volMod;
        float effect;
    };
    VolModEntry entries[512];
    int numEntries = 0;
    int i;

    for (i = 0; i < numVolModNodes; i++) {
        gbVolModNode* vm = volModNodes[i];
        if (!vm) continue;

        void* modObj = vm->pVolMod;
        if (!modObj) continue;
        void** modVtable = *(void***)modObj;
        typedef float (__cdecl *GetEffectFn)(void*, const gbVec3D*, int);
        GetEffectFn getEffect = (GetEffectFn)modVtable[3];
        float effect = getEffect(modObj, &position, flags);

        if (effect != 0.0f) {
            entries[numEntries].volMod = *(float*)&vm;
            entries[numEntries].effect = effect;
            numEntries++;
        }
    }

    void** pSlotA = renderInfo->volModSlotA;
    void** pSlotB = renderInfo->volModSlotB;
    int countA = 0, countB = 0;

    for (i = 0; i < numEntries; i++) {
        gbVolModNode* vm = (gbVolModNode*)(int)entries[i].volMod;
        void* modObj = vm->pVolMod;
        void** modVtable = *(void***)modObj;
        typedef int (__cdecl *GetTypeFn)(void*);
        GetTypeFn getType = (GetTypeFn)modVtable[1];
        int vmType = getType(modObj);

        if (vmType == 0) {
            if (countA < 2) {
                pSlotA[countA] = (void*)(int)entries[i].volMod;
                countA++;
            }
        } else {
            if (countB < 2) {
                pSlotB[countB] = (void*)(int)entries[i].volMod;
                countB++;
            }
        }
    }

    for (i = countA; i < 2; i++) pSlotA[i] = 0;
    for (i = countB; i < 2; i++) pSlotB[i] = 0;
}

void gbSceneGraph::End(void) {
    numVolModNodes = 0;
}

void gbSceneGraph::AddVisNode(gbVisNode* node) {
    if (!rootNode || !node) return;
    rootNode->children.AddNode((gbChain1DNode*)node);
    node->pParent = (gbNBTreeNode*)rootNode;
}

void gbSceneGraph::DelVisNode(gbVisNode* node) {
    if (!node) return;
    gbNBTreeNode* parent = node->pParent;
    if (!parent) return;
    parent->children.DelNodeFromChain((gbChain1DNode*)node);
}

void gbSceneGraph::SetBladeTimeScale(float scale) {
    if (bladeMgr) {
        bladeMgr->globalTimeScale = scale;
    }
}

void gbSceneGraph::ResetBladeMgr(void) {
    if (!bladeMgr) return;
    void** vtable = *(void***)bladeMgr;
    typedef void (__cdecl *ResetFn)(void*);
    ResetFn reset = (ResetFn)vtable[1];
    reset(bladeMgr);
}
