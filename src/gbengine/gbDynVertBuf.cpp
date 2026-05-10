/**
 * gbengine.dll - gbDynVertBuf
 * Dynamic vertex buffer for runtime geometry generation
 */

#include "gbengine/gbMesh.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include <string.h>
#include <stdlib.h>

// Static member
gbGfxManager* gbDynVertBuf::pGfxMgr = NULL;

float* gbDynVertBuf::GetNormal() {
    return m_pNormal;
}

float* gbDynVertBuf::Lock(int numVerts) {
    m_vertNum = numVerts;
    m_currentVertex = 0;
    return m_pXYZ;
}

// 0x1001C540 (16B) - Unlock vertex buffer (D3D mode only)
void gbDynVertBuf::Unlock() {
    if (m_field04 != 2) {
        ((IDirect3DVertexBuffer9*)m_vertexBuffer)->Unlock();
    }
}

void gbDynVertBuf::Draw(int primType, gbRenderEffect* effect, gbTextureArray* textures) {
}

// ConvertPrimitiveType - 0x1001C550 (53B)
static int ConvertPrimitiveType(int primType) {
    switch (primType) {
    case 1: return 4;  // -> D3DPT_TRIANGLELIST
    case 2: return 6;  // -> D3DPT_TRIANGLEFAN
    case 3: return 5;  // -> D3DPT_TRIANGLESTRIP
    case 4: return 2;  // -> D3DPT_LINELIST
    case 5: return 3;  // -> D3DPT_LINESTRIP
    default: return 1; // -> D3DPT_POINTLIST
    }
}

void gbDynVertBuf::RenderGeomQuad(gbGeomQuad* quads, int numQuads,
                                   gbRenderEffect* effect, gbTextureArray* textures) {
    // 6 vertices per quad (triangle list): V0, V1, V3, V3, V1, V2
    // Each vertex: xyz(3) + color(1) + uv(2) = 6 DWORDs
    float* pVerts = Lock(numQuads * 6);
    if (!pVerts) return;

    gbGeomQuad* q = quads;
    for (int i = 0; i < numQuads; i++, q++) {
        // Vertex 0: corner 0, uv=(u1, v1)
        pVerts[0] = q->vec[0].x; pVerts[1] = q->vec[0].y; pVerts[2] = q->vec[0].z;
        *(unsigned int*)&pVerts[3] = q->color;
        pVerts[4] = q->u1; pVerts[5] = q->v1;
        // Vertex 1: corner 1, uv=(u2, v1)
        pVerts[6] = q->vec[1].x; pVerts[7] = q->vec[1].y; pVerts[8] = q->vec[1].z;
        *(unsigned int*)&pVerts[9] = q->color;
        pVerts[10] = q->u2; pVerts[11] = q->v1;
        // Vertex 2: corner 3, uv=(u1, v2)
        pVerts[12] = q->vec[3].x; pVerts[13] = q->vec[3].y; pVerts[14] = q->vec[3].z;
        *(unsigned int*)&pVerts[15] = q->color;
        pVerts[16] = q->u1; pVerts[17] = q->v2;
        // Vertex 3: corner 3, uv=(u1, v2) (duplicate for 2nd triangle)
        pVerts[18] = q->vec[3].x; pVerts[19] = q->vec[3].y; pVerts[20] = q->vec[3].z;
        *(unsigned int*)&pVerts[21] = q->color;
        pVerts[22] = q->u1; pVerts[23] = q->v2;
        // Vertex 4: corner 1, uv=(u2, v1) (duplicate for 2nd triangle)
        pVerts[24] = q->vec[1].x; pVerts[25] = q->vec[1].y; pVerts[26] = q->vec[1].z;
        *(unsigned int*)&pVerts[27] = q->color;
        pVerts[28] = q->u2; pVerts[29] = q->v1;
        // Vertex 5: corner 2, uv=(u2, v2)
        pVerts[30] = q->vec[2].x; pVerts[31] = q->vec[2].y; pVerts[32] = q->vec[2].z;
        *(unsigned int*)&pVerts[33] = q->color;
        pVerts[34] = q->u2; pVerts[35] = q->v2;
        pVerts += 36;
    }
    Draw(1, effect, textures);
}

void gbDynVertBuf::RenderGeomQuadViaStrip(gbGeomQuad* quads, int numQuads,
                                           gbRenderEffect* effect, gbTextureArray* textures) {
    // Triangle strip: numQuads*2 vertices total
    // Each vertex: xyz(3) + color(1) + uv(2) = 6 DWORDs
    if (numQuads < 2) return;

    float* pVerts = Lock(numQuads * 2);
    if (!pVerts) return;

    // First quad: write 2 initial strip vertices (corners 0 and 3)
    pVerts[0] = quads[0].vec[0].x; pVerts[1] = quads[0].vec[0].y; pVerts[2] = quads[0].vec[0].z;
    *(unsigned int*)&pVerts[3] = quads[0].color;
    pVerts[4] = quads[0].su; pVerts[5] = quads[0].sv;
    pVerts[6] = quads[0].vec[3].x; pVerts[7] = quads[0].vec[3].y; pVerts[8] = quads[0].vec[3].z;
    *(unsigned int*)&pVerts[9] = quads[0].color;
    pVerts[10] = quads[0].su; pVerts[11] = quads[0].ev;
    pVerts += 12;

    // Remaining quads: 2 vertices each (corners from next quad)
    for (int i = 1; i < numQuads; i++) {
        pVerts[0] = quads[i].vec[0].x; pVerts[1] = quads[i].vec[0].y; pVerts[2] = quads[i].vec[0].z;
        *(unsigned int*)&pVerts[3] = quads[i].color;
        pVerts[4] = quads[i].eu; pVerts[5] = quads[i].sv;
        pVerts[6] = quads[i].vec[3].x; pVerts[7] = quads[i].vec[3].y; pVerts[8] = quads[i].vec[3].z;
        *(unsigned int*)&pVerts[9] = quads[i].color;
        pVerts[10] = quads[i].eu; pVerts[11] = quads[i].ev;
        pVerts += 12;
    }
    Draw(3, effect, textures);
}

void gbDynVertBuf::RenderGeomQuadViaStrip(gbGeomQuad* quads, int numQuads,
                                           gbRenderEffect* effect, gbTextureArray* textures,
                                           unsigned long flags) {
    if (numQuads <= 0) return;

    float* pVerts = Lock(numQuads * 2 + 2);
    if (!pVerts) return;

    gbGeomQuad* q = &quads[0];

    *(unsigned int*)&pVerts[3] = flags;
    pVerts[4] = q->u1; pVerts[5] = q->v1;
    pVerts[0] = q->vec[0].x; pVerts[1] = q->vec[0].y; pVerts[2] = q->vec[0].z;

    *(unsigned int*)&pVerts[9] = flags;
    pVerts[10] = q->u1; pVerts[11] = q->v2;
    pVerts[6] = q->vec[3].x; pVerts[7] = q->vec[3].y; pVerts[8] = q->vec[3].z;
    pVerts += 12;

    if (numQuads > 1) {
        int count = numQuads - 1;
        if (count > 0) {
            q++;
            do {
                pVerts[0] = q->vec[0].x; pVerts[1] = q->vec[0].y; pVerts[2] = q->vec[0].z;
                *(unsigned int*)&pVerts[3] = flags;
                pVerts[4] = q->u2; pVerts[5] = q->v1;

                *(unsigned int*)&pVerts[9] = flags;
                pVerts[10] = q->u2; pVerts[11] = q->v2;
                pVerts[6] = q->vec[3].x; pVerts[7] = q->vec[3].y; pVerts[8] = q->vec[3].z;
                pVerts += 12;
                q++;
                count--;
            } while (count != 0);
        }
    }

    *(unsigned int*)&pVerts[3] = flags;
    pVerts[4] = q->u1; pVerts[5] = q->v1;
    pVerts[0] = q->vec[1].x; pVerts[1] = q->vec[1].y; pVerts[2] = q->vec[1].z;

    *(unsigned int*)&pVerts[9] = flags;
    pVerts[10] = q->u1; pVerts[11] = q->v2;
    pVerts[6] = q->vec[2].x; pVerts[7] = q->vec[2].y; pVerts[8] = q->vec[2].z;

    Draw(3, effect, textures);
}

void gbDynVertBuf::RenderUIQuad(gbUIQuad* quads, int numQuads,
                                 gbRenderEffect* effect, gbTextureArray* textures) {
    if (m_fvfFlags & 0x100) {
        // XYZRHW path: 7 DWORDs per vertex (x, y, z, rhw, color, u, v)
        float* pVerts = Lock(numQuads * 6);
        if (!pVerts) return;

        gbUIQuad* q = quads;
        for (int i = 0; i < numQuads; i++, q++) {
            // Vertex 0: top-left
            pVerts[0] = q->x1; pVerts[1] = q->y1; pVerts[2] = q->z;
            pVerts[3] = 1.0f;
            *(unsigned int*)&pVerts[4] = q->color;
            pVerts[5] = q->u1; pVerts[6] = q->v1;
            // Vertex 1: top-right
            pVerts[7] = q->x2; pVerts[8] = q->y1; pVerts[9] = q->z;
            pVerts[10] = 1.0f;
            *(unsigned int*)&pVerts[11] = q->color;
            pVerts[12] = q->u2; pVerts[13] = q->v1;
            // Vertex 2: bottom-left
            pVerts[14] = q->x1; pVerts[15] = q->y2; pVerts[16] = q->z;
            pVerts[17] = 1.0f;
            *(unsigned int*)&pVerts[18] = q->color;
            pVerts[19] = q->u1; pVerts[20] = q->v2;
            // Vertex 3: bottom-left (duplicate for 2nd triangle)
            pVerts[21] = q->x1; pVerts[22] = q->y2; pVerts[23] = q->z;
            pVerts[24] = 1.0f;
            *(unsigned int*)&pVerts[25] = q->color;
            pVerts[26] = q->u1; pVerts[27] = q->v2;
            // Vertex 4: top-right (duplicate for 2nd triangle)
            pVerts[28] = q->x2; pVerts[29] = q->y1; pVerts[30] = q->z;
            pVerts[31] = 1.0f;
            *(unsigned int*)&pVerts[32] = q->color;
            pVerts[33] = q->u2; pVerts[34] = q->v1;
            // Vertex 5: bottom-right
            pVerts[35] = q->x2; pVerts[36] = q->y2; pVerts[37] = q->z;
            pVerts[38] = 1.0f;
            *(unsigned int*)&pVerts[39] = q->color;
            pVerts[40] = q->u2; pVerts[41] = q->v2;
            pVerts += 42;
        }
    } else {
        // XYZ path: 6 DWORDs per vertex (x, y, z, color, u, v)
        float* pVerts = Lock(numQuads * 6);
        if (!pVerts) return;

        gbUIQuad* q = quads;
        for (int i = 0; i < numQuads; i++, q++) {
            // Vertex 0: top-left
            pVerts[0] = q->x1; pVerts[1] = q->y1; pVerts[2] = q->z;
            *(unsigned int*)&pVerts[3] = q->color;
            pVerts[4] = q->u1; pVerts[5] = q->v1;
            // Vertex 1: top-right
            pVerts[6] = q->x2; pVerts[7] = q->y1; pVerts[8] = q->z;
            *(unsigned int*)&pVerts[9] = q->color;
            pVerts[10] = q->u2; pVerts[11] = q->v1;
            // Vertex 2: bottom-left
            pVerts[12] = q->x1; pVerts[13] = q->y2; pVerts[14] = q->z;
            *(unsigned int*)&pVerts[15] = q->color;
            pVerts[16] = q->u1; pVerts[17] = q->v2;
            // Vertex 3: bottom-left (duplicate for 2nd triangle)
            pVerts[18] = q->x1; pVerts[19] = q->y2; pVerts[20] = q->z;
            *(unsigned int*)&pVerts[21] = q->color;
            pVerts[22] = q->u1; pVerts[23] = q->v2;
            // Vertex 4: top-right (duplicate for 2nd triangle)
            pVerts[24] = q->x2; pVerts[25] = q->y1; pVerts[26] = q->z;
            *(unsigned int*)&pVerts[27] = q->color;
            pVerts[28] = q->u2; pVerts[29] = q->v1;
            // Vertex 5: bottom-right
            pVerts[30] = q->x2; pVerts[31] = q->y2; pVerts[32] = q->z;
            *(unsigned int*)&pVerts[33] = q->color;
            pVerts[34] = q->u2; pVerts[35] = q->v2;
            pVerts += 36;
        }
    }
    Draw(1, effect, textures);
}

void gbDynVertBuf::RenderLineStrip(gbColorQuad color, gbVec3D* points, int numPoints,
                                    gbRenderEffect* effect) {
    if (!pLineEffect) {
        pLineEffect = pGfxMgr->GetEffectMgr()->NewTrivalEffect(3);
    }
    if (!effect) {
        effect = pLineEffect;
    }

    float* pVerts = Lock(numPoints);
    if (!pVerts) return;

    if (numPoints > 0) {
        for (int i = 0; i < numPoints; i++) {
            m_pXYZ[0] = points[i].x;
            m_pXYZ[1] = points[i].y;
            m_pXYZ[2] = points[i].z;
            *(gbColorQuad*)m_pColor1 = color;
            StepVertexPtr();
        }
    }
    Draw(5, effect, NULL);
}
