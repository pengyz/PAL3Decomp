/**
 * gbengine.dll - gbBladeMgr
 * Blade trail effect manager implementation
 *
 * Addresses: 0x1000EC20 - 0x1000F19C
 * Verified against IDA disassembly (2026-05-08)
 */

#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbGfxManager_impl.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbMesh.h"
#include <stdlib.h>
#include <string.h>

extern double g_CurrentTime;

#define BLADE_MAX_ENTRIES   32
#define BLADE_MAX_FRAMES    40
#define BLADE_VERTEX_SIZE   16

static const float s_fDefaultBladeTime = 0.1f;
static const float s_fSubmitThreshold = 0.025f;
static const float s_f100 = 100.0f;

// ============================================================================
// 0x1000EC20 (146B) - gbBladeMgr::Init
// ============================================================================
void gbBladeMgr::Init(void* gfxMgr) {
    int i, j;

    pGfxManager = gfxMgr;

    gbGfxManager* mgr = (gbGfxManager*)gfxMgr;
    pEffect = mgr->pEffectMgr->NewRenderEffect("gfx/script/blade.gbf", 0);

    globalTimeScale = 1.0f;
    curTime = (float)g_CurrentTime;

    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        entries[i].pGeomNode = NULL;
        entries[i].pVertexData = NULL;
        entries[i].bladeTime = s_fDefaultBladeTime;
        entries[i].curTime = curTime;
        entries[i].timeScale = 0.0f;
        entries[i].numVertices = 0;
        entries[i].numFrames = 0;

        for (j = 0; j < BLADE_MAX_FRAMES; j++) {
            entries[i].timestamps[j] = 0.0f;
        }
    }
}

// ============================================================================
// 0x1000ED00 (118B) - gbBladeMgr::Reset
// ============================================================================
void gbBladeMgr::Reset(void) {
    int i, j;

    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        if (entries[i].pGeomNode != NULL) {
            free(entries[i].pVertexData);
        }
        entries[i].pGeomNode = NULL;
        entries[i].pVertexData = NULL;
        entries[i].bladeTime = s_fDefaultBladeTime;
        entries[i].curTime = curTime;
        entries[i].timeScale = 0.0f;
        entries[i].numVertices = 0;
        entries[i].numFrames = 0;

        for (j = 0; j < BLADE_MAX_FRAMES; j++) {
            entries[i].timestamps[j] = 0.0f;
        }
    }
}

// ============================================================================
// 0x1000F0B0 (239B) - InsertFrame (internal __thiscall on BladeEntry)
// Shifts frames right by one, inserts new data at frame[0] and frame[1]
// ============================================================================
static void BladeEntry_InsertFrame(gbBladeEntry* entry, void* vertexData, float time) {
    int numFrames = entry->numFrames;
    int frameSize = entry->numVertices * BLADE_VERTEX_SIZE;

    if (numFrames > 1) {
        int idx = numFrames;
        while (idx > 1) {
            if (idx < BLADE_MAX_FRAMES) {
                memcpy((char*)entry->pVertexData + idx * frameSize,
                       (char*)entry->pVertexData + (idx - 1) * frameSize,
                       frameSize);
                entry->timestamps[idx] = entry->timestamps[idx - 1];
            }
            idx--;
        }
    }

    memcpy((char*)entry->pVertexData + frameSize, vertexData, frameSize);
    entry->timestamps[1] = time;

    memcpy(entry->pVertexData, vertexData, frameSize);
    entry->timestamps[0] = time;

    numFrames = entry->numFrames + 1;
    if (numFrames < 2) numFrames = 2;
    if (numFrames > BLADE_MAX_FRAMES) numFrames = BLADE_MAX_FRAMES;
    entry->numFrames = numFrames;
}

// ============================================================================
// 0x1000ED80 (268B) - gbBladeMgr::Submit
// Called from gbGeomNode::AttachSelf
// ============================================================================
void gbBladeMgr::Submit(void* vertexData, int numVerts, void* geomNode) {
    int i;
    gbBladeEntry* entry;

    i = 0;
    entry = entries;
    do {
        if (entry->pGeomNode == geomNode) break;
        i++;
        entry++;
    } while (i < BLADE_MAX_ENTRIES);

    if (i == BLADE_MAX_ENTRIES) {
        i = 0;
        entry = entries;
        do {
            if (entry->pGeomNode == NULL) break;
            i++;
            entry++;
        } while (i < BLADE_MAX_ENTRIES);
        if (i == BLADE_MAX_ENTRIES) {
            return;
        }
    }

    entry = &entries[i];

    if (entry->pGeomNode == NULL) {
        entry->pGeomNode = geomNode;
        entry->pVertexData = malloc(numVerts * BLADE_VERTEX_SIZE * BLADE_MAX_FRAMES);
        entry->numFrames = 0;
        entry->numVertices = numVerts;
        entry->timeScale = 1.0f;
    }

    if (entry->numVertices != numVerts) {
        free(entry->pVertexData);
        entry->pGeomNode = NULL;
        return;
    }

    if (entry->numFrames != 0) {
        float elapsed = entry->curTime - entry->timestamps[1];
        if (elapsed < entry->bladeTime * s_fSubmitThreshold) {
            int frameSize = entry->numVertices * BLADE_VERTEX_SIZE;
            memcpy(entry->pVertexData, vertexData, frameSize);
            entry->timestamps[0] = entry->curTime;
            return;
        }
    }

    BladeEntry_InsertFrame(entry, vertexData, entry->curTime);
}

// ============================================================================
// 0x1000EE90 (52B) - gbBladeMgr::SetBladeTime
// ============================================================================
void gbBladeMgr::SetBladeTime(void* geomNode, float time) {
    int i;

    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        if (entries[i].pGeomNode == geomNode) {
            entries[i].bladeTime = time;
            return;
        }
    }
}

// ============================================================================
// 0x1000EED0 (52B) - gbBladeMgr::SetBladeTimeScale
// ============================================================================
void gbBladeMgr::SetBladeTimeScale(void* geomNode, float scale) {
    int i;

    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        if (entries[i].pGeomNode == geomNode) {
            entries[i].timeScale = scale;
            return;
        }
    }
}

// ============================================================================
// 0x1000EF60 (279B) - gbBladeMgr::Update
// Updates blade trail fade-out alpha per vertex
// ============================================================================
void gbBladeMgr::Update(void) {
    float deltaTime;
    int i, frame, vert;

    deltaTime = (float)((gbGfxManager*)pGfxManager)->GetDeltaTime() * globalTimeScale;
    curTime = curTime + deltaTime;

    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        gbBladeEntry* entry = &entries[i];

        float newTime = entry->curTime + deltaTime * entry->timeScale;
        entry->curTime = newTime;

        if (entry->pGeomNode == NULL) continue;

        if (newTime - entry->timestamps[0] > entry->bladeTime * s_f100) {
            free(entry->pVertexData);
            entry->pGeomNode = NULL;
            continue;
        }

        if (entry->numFrames > 0) {
            for (frame = 0; frame < entry->numFrames; frame++) {
                int alpha = 100 - (int)((newTime - entry->timestamps[frame]) * s_f100 / entry->bladeTime);
                if (alpha < 0) alpha = 0;
                else if (alpha > 100) alpha = 100;

                for (vert = 0; vert < entry->numVertices; vert++) {
                    int idx = entry->numVertices * frame + vert;
                    *((char*)entry->pVertexData + idx * BLADE_VERTEX_SIZE + 15) = (char)alpha;
                }
            }
        }
    }
}

// ============================================================================
// 0x1000EF10 (77B) - gbBladeMgr::Render
// ============================================================================
void gbBladeMgr::Render(void) {
    int i;

    gbGfxManager* gfxMgr = (gbGfxManager*)pGfxManager;
    gbDynVertBuf* dynVB = gfxMgr->pVertPoolMgr->GetDynVertBuf(5);

    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        if (entries[i].pGeomNode != NULL && entries[i].numFrames > 2) {
            // RenderBladeEntry is FUN_1000f1a0 (447B)
            // Builds triangle strips and renders via dynVB
            // TODO: implement full render (requires D3D vertex buffer details)
        }
    }
}

// ============================================================================
// 0x1000F080 (47B) - gbBladeMgr::GetLastBladePos
// ============================================================================
void* gbBladeMgr::GetLastBladePos(void* geomNode) {
    int i;

    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        if (entries[i].pGeomNode == geomNode) {
            return entries[i].pVertexData;
        }
    }
    return NULL;
}

// 0x10015660 (8B) - gbBladeMgr::SetTimeScale
void gbBladeMgr::SetTimeScale(float scale) {
    globalTimeScale = scale;
}
