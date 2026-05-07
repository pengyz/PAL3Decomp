/**
 * gbengine.dll - gbBladeMgr
 * Blade trail (刀光/拖尾) effect manager implementation
 *
 * Addresses: 0x1000EC20 - 0x1000F19C
 */

#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbMesh.h"
#include <stdlib.h>
#include <string.h>

extern double g_CurrentTime;

// Blade trail constants
#define BLADE_MAX_ENTRIES   32
#define BLADE_MAX_FRAMES    40
#define BLADE_VERTEX_SIZE   16      // bytes per vertex (position + color)

// Static float constant: 0.1f (at 0x100f55d8 in original)
static const float s_fDefaultTimeScale = 0.1f;
// Static float constant: 100.0f (at 0x100f55e0 in original)
static const float s_f100 = 100.0f;

// ============================================================================
// 0x1000EC20 (146B) - gbBladeMgr::Init
// Called from gbSceneGraph constructor with gfxMgr pointer
// __thiscall, param_1 passed on stack (RET 0x4)
// ============================================================================
void gbBladeMgr::Init(void* gfxMgr) {
    int i, j;

    pGfxManager = gfxMgr;

    // Get blade render effect from the gfx manager's effect manager
    gbGfxManager* mgr = (gbGfxManager*)gfxMgr;
    pEffect = mgr->pEffectMgr->NewRenderEffect("gfx/script/blade.gbf", 0);

    globalTimeScale = 1.0f;
    lastTime = (float)g_CurrentTime;

    // Initialize all 32 blade entries
    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        entries[i].pGeomNode = NULL;
        entries[i].pVertexData = NULL;
        entries[i].timeScale = s_fDefaultTimeScale;
        entries[i].startTime = lastTime;
        entries[i].bladeTimeScale = 0.0f;
        entries[i].numVertices = 0;
        entries[i].numFrames = 0;

        // Clear timestamp buffer
        for (j = 0; j < BLADE_MAX_FRAMES; j++) {
            entries[i].timestamps[j] = 0.0f;
        }
    }
}

// ============================================================================
// 0x1000ED00 (118B) - gbBladeMgr::Reset
// Called from gbSceneGraph::ResetBladeMgr
// Frees all vertex data and reinitializes entries
// ============================================================================
void gbBladeMgr::Reset(void) {
    int i, j;

    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        if (entries[i].pGeomNode != NULL) {
            free(entries[i].pVertexData);
        }
        entries[i].pGeomNode = NULL;
        entries[i].pVertexData = NULL;
        entries[i].timeScale = s_fDefaultTimeScale;
        entries[i].startTime = lastTime;
        entries[i].bladeTimeScale = 0.0f;
        entries[i].numVertices = 0;
        entries[i].numFrames = 0;

        // Clear timestamp buffer
        for (j = 0; j < BLADE_MAX_FRAMES; j++) {
            entries[i].timestamps[j] = 0.0f;
        }
    }
}

// ============================================================================
// 0x1000ED80 (268B) - gbBladeMgr::Submit
// Called from gbGeomNode::AttachSelf to submit blade trail vertex data
// __thiscall with 3 stack params (RET 0xC)
// ============================================================================
void gbBladeMgr::Submit(void* vertexData, int numVerts, void* geomNode) {
    int i;
    gbBladeEntry* entry;

    // First, try to find existing entry for this geomNode
    i = 0;
    entry = entries;
    while (i < BLADE_MAX_ENTRIES) {
        if (entry->pGeomNode == geomNode) break;
        i++;
        entry = &entries[i];
    }

    // If not found, find a free slot
    if (i == BLADE_MAX_ENTRIES) {
        i = 0;
        entry = entries;
        while (i < BLADE_MAX_ENTRIES) {
            if (entry->pGeomNode == NULL) break;
            i++;
            entry = &entries[i];
        }
        if (i == BLADE_MAX_ENTRIES) {
            return;  // No free slots
        }
    }

    entry = &entries[i];

    // If slot was empty, allocate vertex buffer
    if (entries[i].pGeomNode == NULL) {
        entry->pGeomNode = geomNode;
        entry->pVertexData = malloc(numVerts * BLADE_VERTEX_SIZE * BLADE_MAX_FRAMES);
        entry->numFrames = 0;
        entry->numVertices = numVerts;
        entry->bladeTimeScale = 1.0f;
    }

    // If vertex count changed, free and clear
    if (entry->numVertices != numVerts) {
        free(entry->pVertexData);
        entry->pGeomNode = NULL;
        return;
    }

    // If there are existing frames, check if we can do a fast copy
    if (entry->numFrames != 0) {
        // Check if elapsed time since start is less than timeScale * 0.025
        float elapsed = entry->startTime - entry->timestamps[0];
        if (elapsed < entry->timeScale * 0.025f) {
            // Fast path: overwrite the latest frame at position [numFrames]
            int copySize = entry->numVertices * BLADE_VERTEX_SIZE;
            memcpy((char*)entry->pVertexData + copySize * entry->numFrames,
                   vertexData, copySize);
            entry->timestamps[0] = entry->startTime;
            return;
        }
    }

    // Normal path: push new frame into ring buffer (InsertFrame)
    {
        int nFrames = entry->numFrames;

        // Shift existing frames up by one slot (make room at position 1)
        if (nFrames > 1) {
            int frameIdx = nFrames - 1;
            while (frameIdx > 1) {
                if (nFrames < BLADE_MAX_FRAMES) {
                    int vertSize = entry->numVertices;
                    int srcOff = frameIdx * vertSize * BLADE_VERTEX_SIZE;
                    int dstOff = nFrames * vertSize * BLADE_VERTEX_SIZE;
                    memcpy((char*)entry->pVertexData + dstOff,
                           (char*)entry->pVertexData + srcOff,
                           vertSize * BLADE_VERTEX_SIZE);
                    entry->timestamps[nFrames] = entry->timestamps[nFrames - 1];
                }
                nFrames--;
                frameIdx--;
            }
        }

        // Copy new vertex data to frame slot [1]
        {
            int vertSize = entry->numVertices * BLADE_VERTEX_SIZE;
            memcpy((char*)entry->pVertexData + vertSize,
                   vertexData, vertSize);
        }

        // Store timestamp for the new frame
        entry->timestamps[1] = entry->startTime;

        // Also copy to frame slot [0]
        {
            int vertSize = entry->numVertices * BLADE_VERTEX_SIZE;
            memcpy(entry->pVertexData, vertexData, vertSize);
        }

        // Update frame count
        entry->timestamps[0] = entry->startTime;
        int newFrames = entry->numFrames + 1;
        if (newFrames < 2) {
            newFrames = 2;
        }
        if (newFrames > BLADE_MAX_FRAMES) {
            newFrames = BLADE_MAX_FRAMES;
        }
        entry->numFrames = newFrames;
    }
}

// ============================================================================
// 0x1000EE90 (52B) - gbBladeMgr::SetBladeTime
// Called from gbGeomNode::SetBladeTime
// __thiscall with 2 stack params (RET 0x8)
// ============================================================================
void gbBladeMgr::SetBladeTime(void* geomNode, float time) {
    int i;

    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        if (entries[i].pGeomNode == geomNode) {
            entries[i].timeScale = time;
            return;
        }
    }
}

// ============================================================================
// 0x1000EED0 (52B) - gbBladeMgr::SetBladeTimeScale
// Called from gbGeomNode::SetBladeTimeScale
// __thiscall with 2 stack params (RET 0x8)
// ============================================================================
void gbBladeMgr::SetBladeTimeScale(void* geomNode, float scale) {
    int i;

    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        if (entries[i].pGeomNode == geomNode) {
            entries[i].bladeTimeScale = scale;
            return;
        }
    }
}

// ============================================================================
// 0x1000EF60 (279B) - gbBladeMgr::Update
// Called from gbSceneGraph::End (was BladeMgr_Submit stub)
// Updates blade trail fade-out based on elapsed time
// ============================================================================
void gbBladeMgr::Update(void) {
    float deltaTime;
    int i, row, col;

    // Get delta time scaled by global time scale
    deltaTime = (float)((gbGfxManager*)pGfxManager)->GetDeltaTime() * globalTimeScale;
    lastTime = lastTime + deltaTime;

    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        gbBladeEntry* entry = &entries[i];

        // Update accumulated time for this entry
        float curTime = entry->startTime + deltaTime * entry->bladeTimeScale;
        entry->startTime = curTime;

        if (entry->pGeomNode == NULL) continue;

        // Check if blade trail has expired
        float elapsed = curTime - entry->timestamps[1];
        if (elapsed > entry->timeScale * s_f100) {
            // Trail expired: free vertex data and deactivate
            free(entry->pVertexData);
            entry->pGeomNode = NULL;
            continue;
        }

        // Update alpha fade for each frame's vertices
        if (entry->numFrames > 0) {
            for (row = 0; row < entry->numFrames; row++) {
                // Compute alpha based on time ratio
                float frameElapsed = curTime - entry->timestamps[1];
                int alpha = 100 - (int)(frameElapsed * s_f100 / entry->timeScale);
                if (alpha < 0) alpha = 0;
                else if (alpha > 100) alpha = 100;

                // Write alpha to each vertex in this frame
                for (col = 0; col < entry->numVertices; col++) {
                    int vertIdx = entry->numVertices * row + col;
                    // Each vertex is BLADE_VERTEX_SIZE bytes; alpha at byte offset 15 (ARGB high byte)
                    *((char*)entry->pVertexData + vertIdx * BLADE_VERTEX_SIZE + (BLADE_VERTEX_SIZE - 1)) = (char)alpha;
                }
            }
        }
    }
}

// ============================================================================
// 0x1000F1A0 (447B) - RenderBladeEntry (static helper)
// Builds triangle strip geometry from blade trail frames and renders
// ============================================================================
static void RenderBladeEntry(gbBladeEntry* entry, gbDynVertBuf* dynVB, gbRenderEffect* effect) {
    int numTris;
    int frame, vert;
    void* verts;

    int numFrames = entry->numFrames;
    int numVertices = entry->numVertices;

    // Number of triangles: (numFrames-1) * 6 * (numVertices-1)
    // Each quad between frames uses 6 vertices (2 triangles)
    numTris = (numFrames * 3 - 3) * (numVertices - 1);

    // Lock vertex buffer for writing
    verts = (void*)dynVB->Lock(numTris);

    if (verts == NULL) return;

    // Build triangle strips from blade frame data
    if (numFrames - 1 > 0) {
        for (frame = 0; frame < numFrames - 1; frame++) {
            if (numVertices - 1 <= 0) continue;

            for (vert = 0; vert < numVertices - 1; vert++) {
                char* src;
                char* dst = (char*)verts;

                // Triangle 1, vertex 0: frame[i], vert[j]
                src = (char*)entry->pVertexData + (numVertices * frame + vert) * BLADE_VERTEX_SIZE;
                memcpy(dst, src, BLADE_VERTEX_SIZE); dst += BLADE_VERTEX_SIZE;

                // Triangle 1, vertex 1: frame[i+1], vert[j+1]
                src = (char*)entry->pVertexData + (numVertices * (frame + 1) + vert + 1) * BLADE_VERTEX_SIZE;
                memcpy(dst, src, BLADE_VERTEX_SIZE); dst += BLADE_VERTEX_SIZE;

                // Triangle 1, vertex 2: frame[i+1], vert[j]
                src = (char*)entry->pVertexData + (numVertices * (frame + 1) + vert) * BLADE_VERTEX_SIZE;
                memcpy(dst, src, BLADE_VERTEX_SIZE); dst += BLADE_VERTEX_SIZE;

                // Triangle 2, vertex 0: frame[i], vert[j]
                src = (char*)entry->pVertexData + (numVertices * frame + vert) * BLADE_VERTEX_SIZE;
                memcpy(dst, src, BLADE_VERTEX_SIZE); dst += BLADE_VERTEX_SIZE;

                // Triangle 2, vertex 1: frame[i], vert[j+1]
                src = (char*)entry->pVertexData + (numVertices * frame + vert + 1) * BLADE_VERTEX_SIZE;
                memcpy(dst, src, BLADE_VERTEX_SIZE); dst += BLADE_VERTEX_SIZE;

                // Triangle 2, vertex 2: frame[i+1], vert[j+1]
                src = (char*)entry->pVertexData + (numVertices * (frame + 1) + vert + 1) * BLADE_VERTEX_SIZE;
                memcpy(dst, src, BLADE_VERTEX_SIZE); dst += BLADE_VERTEX_SIZE;

                verts = dst;
            }
        }
    }

    // Draw the triangle list (primType=1 = triangle list)
    dynVB->Draw(1, effect, NULL);
}

// ============================================================================
// 0x1000EF10 (77B) - gbBladeMgr::Render
// Called from gbSceneGraph::End
// Renders all active blade trails using dynamic vertex buffer
// ============================================================================
void gbBladeMgr::Render(void) {
    int i;

    // Get dynamic vertex buffer (FVF type 5)
    gbGfxManager* gfxMgr = (gbGfxManager*)pGfxManager;
    gbDynVertBuf* dynVB = gfxMgr->pVertPoolMgr->GetDynVertBuf(5);

    for (i = 0; i < BLADE_MAX_ENTRIES; i++) {
        if (entries[i].pGeomNode != NULL && entries[i].numFrames > 2) {
            RenderBladeEntry(&entries[i], dynVB, pEffect);
        }
    }
}

// ============================================================================
// 0x1000F080 (47B) - gbBladeMgr::GetLastBladePos
// Called from gbGeomNode::GetLastBladePos
// Returns the vertex data pointer for the entry matching geomNode
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
