/**
 * gbengine.dll - gbMesh
 * Mesh classes for static and dynamic geometry
 */

#include "gbengine/gbMesh.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include <cstring>
#include <cstdlib>


/* ======== gbMeshSection ======== */

gbMeshSection::gbMeshSection() {
    m_vertexStart = 0;
    m_vertexCount = 0;
    m_faceStart = 0;
    m_faceCount = 0;
    m_materialIndex = 0;
}


/* ======== gbBaseMesh ======== */

// Static member initialization
int gbBaseMesh::Effect_RefCount = 0;
gbRenderEffect** gbBaseMesh::pShadowEffect = nullptr;
char* gbBaseMesh::TextureDir = nullptr;

// Constructor
gbBaseMesh::gbBaseMesh(gbGfxManager* gfxMgr) {
    m_refCount = 1;
    m_reserved1 = nullptr;
    m_reserved2 = nullptr;
    m_reserved3 = nullptr;
    m_reserved4 = nullptr;
    m_vertexBuffer = nullptr;
    m_indexBuffer = nullptr;
    m_sections = nullptr;
    m_numSections = 0;
    m_meshType = MESH_STATIC;
    m_currentTime = 0.0f;
    m_pGfxManager = gfxMgr;

    memset(m_reserved5, 0, sizeof(m_reserved5));
    memset(m_reserved6, 0, sizeof(m_reserved6));
    memset(&m_aabb, 0, sizeof(m_aabb));
    memset(m_objectName, 0, sizeof(m_objectName));
    memset(&m_memCache, 0, sizeof(m_memCache));

    // Initialize shadow effects on first mesh creation
    if (Effect_RefCount == 0) {
        // Load shadow effect shaders
    }
    Effect_RefCount++;
}

// Copy constructor
gbBaseMesh::gbBaseMesh(const gbBaseMesh& other) {
    m_refCount = 1;
    m_reserved1 = other.m_reserved1;
    m_reserved2 = other.m_reserved2;
    m_reserved3 = other.m_reserved3;
    m_reserved4 = other.m_reserved4;
    m_vertexBuffer = other.m_vertexBuffer;
    m_indexBuffer = other.m_indexBuffer;
    m_numSections = other.m_numSections;
    m_meshType = other.m_meshType;
    m_currentTime = other.m_currentTime;
    m_pGfxManager = other.m_pGfxManager;
    m_aabb = other.m_aabb;

    memcpy(m_reserved5, other.m_reserved5, sizeof(m_reserved5));
    memcpy(m_reserved6, other.m_reserved6, sizeof(m_reserved6));
    memcpy(m_objectName, other.m_objectName, sizeof(m_objectName));
    m_memCache = other.m_memCache;

    if (other.m_sections && m_numSections > 0) {
        m_sections = new gbMeshSection[m_numSections];
        memcpy(m_sections, other.m_sections, m_numSections * sizeof(gbMeshSection));
    } else {
        m_sections = nullptr;
    }

    Effect_RefCount++;
}

// Destructor
gbBaseMesh::~gbBaseMesh() {
    if (m_sections) {
        delete[] m_sections;
        m_sections = nullptr;
    }

    Effect_RefCount--;

    if (Effect_RefCount == 0) {
        pShadowEffect = nullptr;
    }
}

// Assignment operator
gbBaseMesh& gbBaseMesh::operator=(const gbBaseMesh& other) {
    if (this == &other) return *this;

    if (m_sections) {
        delete[] m_sections;
    }

    m_reserved1 = other.m_reserved1;
    m_reserved2 = other.m_reserved2;
    m_reserved3 = other.m_reserved3;
    m_reserved4 = other.m_reserved4;
    m_vertexBuffer = other.m_vertexBuffer;
    m_indexBuffer = other.m_indexBuffer;
    m_numSections = other.m_numSections;
    m_meshType = other.m_meshType;
    m_currentTime = other.m_currentTime;
    m_pGfxManager = other.m_pGfxManager;
    m_aabb = other.m_aabb;

    memcpy(m_reserved5, other.m_reserved5, sizeof(m_reserved5));
    memcpy(m_reserved6, other.m_reserved6, sizeof(m_reserved6));
    memcpy(m_objectName, other.m_objectName, sizeof(m_objectName));
    m_memCache = other.m_memCache;

    if (other.m_sections && m_numSections > 0) {
        m_sections = new gbMeshSection[m_numSections];
        memcpy(m_sections, other.m_sections, m_numSections * sizeof(gbMeshSection));
    } else {
        m_sections = nullptr;
    }

    return *this;
}

// Out-of-line accessors
gbMeshSection* gbBaseMesh::GetMeshSection(int index) {
    if (index < 0 || index >= m_numSections) return nullptr;
    return &m_sections[index];
}

int gbBaseMesh::GetNumSection() {
    return m_numSections;
}

int gbBaseMesh::GetNumFaces() {
    int totalFaces = 0;
    for (int i = 0; i < m_numSections; i++) {
        totalFaces += m_sections[i].m_faceCount;
    }
    return totalFaces;
}

unsigned int gbBaseMesh::GetFVF() {
    // Base class returns 0; derived classes (gbStaticMesh, etc.) override
    (void)0;
    return 0;
}

gbMeshType gbBaseMesh::GetMeshType() {
    return m_meshType;
}

gbAABBox* gbBaseMesh::GetAABBox() {
    return &m_aabb;
}

const char* gbBaseMesh::GetObjectName() {
    return m_objectName;
}

gbMeshMemCache* gbBaseMesh::GetMemoryCache() {
    return &m_memCache;
}

void gbBaseMesh::SetCurTime(float time) {
    m_currentTime = time;
}

void gbBaseMesh::SetTexture(int index, gbTexture* texture) {
    for (int i = 0; i < m_numSections; i++) {
        char* sectionBase = (char*)m_sections + i * 0xBC;
        gbTexture** texArray = *(gbTexture***)(sectionBase + 8);
        int maxTex = *(int*)(sectionBase + 0x48);

        if (index < maxTex && texArray[index] != NULL) {
            texArray[index]->refObj.Release();
        }

        // Increment new texture refcount and assign
        texture->refObj.RefCount++;
        texArray[index] = texture;

        // Update max texture count if needed
        if (*(int*)(sectionBase + 0x48) < index + 1) {
            *(int*)(sectionBase + 0x48) = index + 1;
        }
    }
}

void gbBaseMesh::ReplaceTexture(const char* textureName) {
    if (!m_sections) return;
    // Get texture via resource manager virtual call, load it, set as first section texture
    // gbResManager* resMgr = global texture resource manager
    // gbTexture* tex = resMgr->vtable[2](textureName);
    // tex->LoadTexture(1);
    // *(gbTexture**)((char*)m_sections + 8) = tex;
}

void gbBaseMesh::ReplaceTexture(gbTexture* texture) {
    // Stores texture as first texture of first section (offset +8 from section base)
    *(gbTexture**)((char*)m_sections + 8) = texture;
}

void gbBaseMesh::ComputeShadowVolume() {
    // Base class does nothing; gbStaticMesh overrides with full shadow volume computation
    (void)0;
}

void gbBaseMesh::RenderShadowVolume(gbVisNode* visNode, gbRenderInfoObj* renderInfo) {
    // Base class does nothing; derived classes override for shadow rendering
    (void)0;
}

void gbBaseMesh::SetMeshTexDir(char* dir) {
    TextureDir = dir;
}


/* ======== gbStaticMesh ======== */

// Static member initialization
char* gbStaticMesh::LightMapDir = nullptr;

gbStaticMesh::gbStaticMesh(gbGfxManager* gfxMgr) : gbBaseMesh(gfxMgr) {
    m_pVertBubble = nullptr;
    m_shadowVolumeVB = nullptr;
    m_shadowVolumeIB = nullptr;
    m_vertexBuffer = nullptr;
}

gbStaticMesh::gbStaticMesh(const gbStaticMesh& other) : gbBaseMesh(other) {
    m_pVertBubble = other.m_pVertBubble;
    m_shadowVolumeVB = other.m_shadowVolumeVB;
    m_shadowVolumeIB = other.m_shadowVolumeIB;
}

gbStaticMesh::~gbStaticMesh() {
    if (m_pVertBubble) {
        m_pVertBubble = nullptr;
    }
    if (m_shadowVolumeVB) {
        m_shadowVolumeVB = nullptr;
    }
    if (m_shadowVolumeIB) {
        m_shadowVolumeIB = nullptr;
    }
}

gbStaticMesh& gbStaticMesh::operator=(const gbStaticMesh& other) {
    if (this == &other) return *this;

    gbBaseMesh::operator=(other);

    m_pVertBubble = other.m_pVertBubble;
    m_shadowVolumeVB = other.m_shadowVolumeVB;
    m_shadowVolumeIB = other.m_shadowVolumeIB;

    return *this;
}

int gbStaticMesh::LoadFromStream(gbVFile* file, int flags, GeomNodeDesc* desc) {
    if (!file) return 0;

    struct MeshHeader {
        char signature[4];
        int version;
        int numVertices;
        int numFaces;
        int numSections;
        int fvf;
        gbAABBox bounds;
    };

    MeshHeader header;
    memset(&header, 0, sizeof(header));

    if (memcmp(header.signature, "MESH", 4) != 0) {
        return 0;
    }

    m_aabb = header.bounds;
    m_numSections = header.numSections;

    if (m_numSections > 0) {
        m_sections = new gbMeshSection[m_numSections];
    }

    return 1;
}

void gbStaticMesh::DrawSubSet(int index, gbRenderInfoObj* renderInfo) {
    if (index < 0 || index >= m_numSections) return;
}

// Internal shadow volume builder (0x10016c70)
// TODO: Implement full shadow volume mesh generation from positions and indices
static void BuildShadowVolumeData(void* params) {
    // Stub: the real implementation builds edge lists and extrudes shadow geometry
    // Output VB/IB pointers remain NULL until this is fully implemented
}

void gbStaticMesh::ComputeShadowVolume() {
    // Only compute if shadow volume VB hasn't been created yet
    if (m_shadowVolumeVB != NULL) return;
    if (m_pVertBubble == NULL) return;

    // Get vertex count from vertex bubble (at bubble offset +0x14 = countUsed)
    int numVerts = m_pVertBubble->countUsed;
    if (numVerts <= 0) return;

    // Allocate position array (numVerts * sizeof(gbVec3D) = numVerts * 12)
    gbVec3D* positions = (gbVec3D*)malloc(numVerts * sizeof(gbVec3D));
    if (!positions) return;

    // Lock vertex bubble and copy XYZ positions
    void* vertData = m_pVertBubble->Lock();
    if (vertData) {
        // Copy positions from interleaved vertex data
        // Each vertex has XYZ at the start, stride determined by vertex format
        char* srcPtr = (char*)vertData;
        for (int i = 0; i < numVerts; i++) {
            positions[i].x = *(float*)(srcPtr);
            positions[i].y = *(float*)(srcPtr + 4);
            positions[i].z = *(float*)(srcPtr + 8);
            m_pVertBubble->StepVertexPtr();
            // Advance source pointer by stride - use pPool->stride
            if (m_pVertBubble->pPool) {
                srcPtr += m_pVertBubble->pPool->stride;
            }
        }
        m_pVertBubble->Unlock();
    }

    // Count total indices across all sections
    int totalIndices = 0;
    for (int i = 0; i < m_numSections; i++) {
        char* sectionBase = (char*)m_sections + i * 0xBC;
        // Index bubble pointer at section offset +0x90
        gbIndexBubble* idxBubble = *(gbIndexBubble**)(sectionBase + 0x90);
        if (idxBubble) {
            totalIndices += idxBubble->count;
        }
    }

    // Allocate index buffer (unsigned short per index)
    unsigned short* indices = NULL;
    if (totalIndices > 0) {
        indices = (unsigned short*)malloc(totalIndices * sizeof(unsigned short));
        if (indices) {
            // Lock each index bubble and copy indices into flat array
            int offset = 0;
            for (int i = 0; i < m_numSections; i++) {
                char* sectionBase = (char*)m_sections + i * 0xBC;
                gbIndexBubble* idxBubble = *(gbIndexBubble**)(sectionBase + 0x90);
                if (idxBubble) {
                    unsigned short* srcIndices = idxBubble->Lock16();
                    if (srcIndices) {
                        memcpy(indices + offset, srcIndices, idxBubble->count * sizeof(unsigned short));
                        offset += idxBubble->count;
                    }
                    idxBubble->Unlock();
                }
            }
        }
    }

    // Build shadow volume creation param struct and call builder
    // The original passes a struct with positions, indices, counts, and output ptrs
    struct ShadowVolumeParams {
        gbVec3D* pPositions;
        int numVertices;
        unsigned short* pIndices;
        int numIndices;
        void** ppOutVB;
        void** ppOutIB;
    };

    ShadowVolumeParams params;
    params.pPositions = positions;
    params.numVertices = numVerts;
    params.pIndices = indices;
    params.numIndices = totalIndices;
    params.ppOutVB = &m_shadowVolumeVB;
    params.ppOutIB = &m_shadowVolumeIB;

    BuildShadowVolumeData(&params);

    // Free temporary arrays
    free(positions);
    if (indices) free(indices);
}

void gbStaticMesh::RenderShadowVolume(gbVisNode* visNode, gbRenderInfoObj* renderInfo) {
    if (!m_shadowVolumeVB || !m_shadowVolumeIB) return;
}

gbVertexBubble* gbStaticMesh::GetVertBubble() {
    return m_pVertBubble;
}


/* ======== gbDynVertBuf ======== */

// Static members
gbGfxManager* gbDynVertBuf::pGfxMgr = nullptr;
gbRenderEffect* gbDynVertBuf::pLineEffect = nullptr;

gbDynVertBuf::gbDynVertBuf(unsigned int fvfFlags, int maxVertices) {
    m_fvfFlags = fvfFlags;
    m_maxVertices = maxVertices;
    m_currentVertex = 0;
    m_vertexBuffer = nullptr;
    m_vertexStride = 0;
    m_pXYZ = nullptr;
    m_pNormal = nullptr;
    m_pColor1 = nullptr;
    m_pColor2 = nullptr;
    m_pUV = nullptr;
    m_vertNum = 0;
}

gbDynVertBuf::gbDynVertBuf(const gbDynVertBuf& other) {
    m_fvfFlags = other.m_fvfFlags;
    m_maxVertices = other.m_maxVertices;
    m_currentVertex = other.m_currentVertex;
    m_vertexBuffer = other.m_vertexBuffer;
    m_vertexStride = other.m_vertexStride;
    m_pXYZ = other.m_pXYZ;
    m_pNormal = other.m_pNormal;
    m_pColor1 = other.m_pColor1;
    m_pColor2 = other.m_pColor2;
    m_pUV = other.m_pUV;
    m_vertNum = other.m_vertNum;
}

gbDynVertBuf::~gbDynVertBuf() {
}

gbDynVertBuf& gbDynVertBuf::operator=(const gbDynVertBuf& other) {
    if (this != &other) {
        m_fvfFlags = other.m_fvfFlags;
        m_maxVertices = other.m_maxVertices;
        m_currentVertex = other.m_currentVertex;
        m_vertexBuffer = other.m_vertexBuffer;
        m_vertexStride = other.m_vertexStride;
        m_pXYZ = other.m_pXYZ;
        m_pNormal = other.m_pNormal;
        m_pColor1 = other.m_pColor1;
        m_pColor2 = other.m_pColor2;
        m_pUV = other.m_pUV;
        m_vertNum = other.m_vertNum;
    }
    return *this;
}

float* gbDynVertBuf::GetXYZ() {
    return m_pXYZ;
}

float* gbDynVertBuf::GetNormal() {
    return m_pNormal;
}

gbColorQuad* gbDynVertBuf::GetColor1() {
    return m_pColor1;
}

gbColorQuad* gbDynVertBuf::GetColor2() {
    return m_pColor2;
}

int gbDynVertBuf::GetVertNum() {
    return m_vertNum;
}

int gbDynVertBuf::GetVertexStride() {
    return m_vertexStride;
}

float* gbDynVertBuf::GetUV(int index) {
    return nullptr;
}

void gbDynVertBuf::StepVertexPtr() {
    m_currentVertex++;
    if (m_currentVertex >= m_maxVertices) {
        m_currentVertex = 0;
    }
}

float* gbDynVertBuf::Lock(int numVerts) {
    // Base implementation - derived classes override with actual D3D buffer lock
    (void)0;
    return NULL;
}

void gbDynVertBuf::Unlock() {
    // Base implementation - derived classes override
    (void)0;
}

void gbDynVertBuf::Draw(int primType, int numPrims, gbRenderEffect* effect) {
    // Base implementation - derived classes override with actual D3D draw call
    (void)0;
}

void gbDynVertBuf::RenderUIQuad(gbUIQuad* quadData, int numQuads, gbRenderEffect* effect, gbTextureArray* textures) {
    if (numQuads <= 0) return;

    // 6 vertices per quad (two triangles: TL, TR, BL | BL, TR, BR)
    float* pVerts = Lock(numQuads * 6);
    if (!pVerts) return;

    // Check FVF for XYZRHW (bit 0x100 in D3D FVF = D3DFVF_XYZRHW / transformed verts)
    int hasRHW = (m_fvfFlags & 0x100) != 0;

    for (int q = 0; q < numQuads; q++) {
        gbUIQuad* quad = &quadData[q];
        float x1 = quad->x1;
        float y1 = quad->y1;
        float x2 = quad->x2;
        float y2 = quad->y2;
        float u1 = quad->u1;
        float v1 = quad->v1;
        float u2 = quad->u2;
        float v2 = quad->v2;
        float z  = quad->z;
        unsigned int color = quad->color;

        if (hasRHW) {
            // 7 dwords per vertex: x, y, z, rhw, color, u, v
            // Vertex 0: top-left
            *pVerts++ = x1; *pVerts++ = y1; *pVerts++ = z; *pVerts++ = 1.0f;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u1; *pVerts++ = v1;
            // Vertex 1: top-right
            *pVerts++ = x2; *pVerts++ = y1; *pVerts++ = z; *pVerts++ = 1.0f;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u2; *pVerts++ = v1;
            // Vertex 2: bottom-left
            *pVerts++ = x1; *pVerts++ = y2; *pVerts++ = z; *pVerts++ = 1.0f;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u1; *pVerts++ = v2;
            // Vertex 3: bottom-left (second tri)
            *pVerts++ = x1; *pVerts++ = y2; *pVerts++ = z; *pVerts++ = 1.0f;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u1; *pVerts++ = v2;
            // Vertex 4: top-right
            *pVerts++ = x2; *pVerts++ = y1; *pVerts++ = z; *pVerts++ = 1.0f;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u2; *pVerts++ = v1;
            // Vertex 5: bottom-right
            *pVerts++ = x2; *pVerts++ = y2; *pVerts++ = z; *pVerts++ = 1.0f;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u2; *pVerts++ = v2;
        } else {
            // 6 dwords per vertex: x, y, z, color, u, v
            // Vertex 0: top-left
            *pVerts++ = x1; *pVerts++ = y1; *pVerts++ = z;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u1; *pVerts++ = v1;
            // Vertex 1: top-right
            *pVerts++ = x2; *pVerts++ = y1; *pVerts++ = z;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u2; *pVerts++ = v1;
            // Vertex 2: bottom-left
            *pVerts++ = x1; *pVerts++ = y2; *pVerts++ = z;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u1; *pVerts++ = v2;
            // Vertex 3: bottom-left (second tri)
            *pVerts++ = x1; *pVerts++ = y2; *pVerts++ = z;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u1; *pVerts++ = v2;
            // Vertex 4: top-right
            *pVerts++ = x2; *pVerts++ = y1; *pVerts++ = z;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u2; *pVerts++ = v1;
            // Vertex 5: bottom-right
            *pVerts++ = x2; *pVerts++ = y2; *pVerts++ = z;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u2; *pVerts++ = v2;
        }
    }

    // Draw as triangle list: numQuads * 2 triangles
    Draw(1, numQuads * 2, effect);
}

void gbDynVertBuf::RenderGeomQuad(gbGeomQuad* quadData, int numQuads, gbRenderEffect* effect, gbTextureArray* textures) {
    if (numQuads <= 0) return;

    // 6 vertices per quad (two triangles), 6 dwords per vertex (xyz + color + uv)
    float* pVerts = Lock(numQuads * 6);
    if (!pVerts) return;

    for (int q = 0; q < numQuads; q++) {
        gbGeomQuad* quad = &quadData[q];
        float u1 = quad->u1;
        float v1 = quad->v1;
        float u2 = quad->u2;
        float v2 = quad->v2;
        unsigned int color = quad->color;

        // Triangle 1: v0 (top-left), v1 (top-right), v2 (bottom-left)
        // Vertex 0: top-left
        *pVerts++ = quad->verts[0].x; *pVerts++ = quad->verts[0].y; *pVerts++ = quad->verts[0].z;
        *(unsigned int*)pVerts = color; pVerts++;
        *pVerts++ = u1; *pVerts++ = v1;
        // Vertex 1: top-right
        *pVerts++ = quad->verts[1].x; *pVerts++ = quad->verts[1].y; *pVerts++ = quad->verts[1].z;
        *(unsigned int*)pVerts = color; pVerts++;
        *pVerts++ = u2; *pVerts++ = v1;
        // Vertex 2: bottom-left
        *pVerts++ = quad->verts[2].x; *pVerts++ = quad->verts[2].y; *pVerts++ = quad->verts[2].z;
        *(unsigned int*)pVerts = color; pVerts++;
        *pVerts++ = u1; *pVerts++ = v2;

        // Triangle 2: v2 (bottom-left), v1 (top-right), v3 (bottom-right)
        // Vertex 3: bottom-left
        *pVerts++ = quad->verts[2].x; *pVerts++ = quad->verts[2].y; *pVerts++ = quad->verts[2].z;
        *(unsigned int*)pVerts = color; pVerts++;
        *pVerts++ = u1; *pVerts++ = v2;
        // Vertex 4: top-right
        *pVerts++ = quad->verts[1].x; *pVerts++ = quad->verts[1].y; *pVerts++ = quad->verts[1].z;
        *(unsigned int*)pVerts = color; pVerts++;
        *pVerts++ = u2; *pVerts++ = v1;
        // Vertex 5: bottom-right
        *pVerts++ = quad->verts[3].x; *pVerts++ = quad->verts[3].y; *pVerts++ = quad->verts[3].z;
        *(unsigned int*)pVerts = color; pVerts++;
        *pVerts++ = u2; *pVerts++ = v2;
    }

    // Draw as triangle list: numQuads * 2 triangles
    Draw(1, numQuads * 2, effect);
}

void gbDynVertBuf::RenderGeomQuadViaStrip(gbGeomQuad* quadData, int numQuads, gbRenderEffect* effect, gbTextureArray* textures) {
    RenderGeomQuadViaStrip(quadData, numQuads, effect, textures, 0);
}

void gbDynVertBuf::RenderGeomQuadViaStrip(gbGeomQuad* quadData, int numQuads, gbRenderEffect* effect, gbTextureArray* textures, unsigned long flags) {
    // Renders quads as a connected triangle strip
    // Each quad contributes 2 vertices to the strip, plus 2 for the final edge
    if (numQuads <= 0) return;

    int totalVerts = numQuads * 2 + 2;
    float* pVerts = Lock(totalVerts);
    if (!pVerts) return;

    // 6 dwords per vertex: xyz + color + uv
    for (int q = 0; q < numQuads; q++) {
        gbGeomQuad* quad = &quadData[q];
        unsigned int color = quad->color;
        float u1 = quad->u1;
        float v1 = quad->v1;
        float u2 = quad->u2;
        float v2 = quad->v2;

        if (q == 0) {
            // First quad: emit top-left and top-right vertices
            *pVerts++ = quad->verts[0].x; *pVerts++ = quad->verts[0].y; *pVerts++ = quad->verts[0].z;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u1; *pVerts++ = v1;

            *pVerts++ = quad->verts[1].x; *pVerts++ = quad->verts[1].y; *pVerts++ = quad->verts[1].z;
            *(unsigned int*)pVerts = color; pVerts++;
            *pVerts++ = u2; *pVerts++ = v1;
        }

        // Each quad emits its bottom-left and bottom-right vertices
        *pVerts++ = quad->verts[2].x; *pVerts++ = quad->verts[2].y; *pVerts++ = quad->verts[2].z;
        *(unsigned int*)pVerts = color; pVerts++;
        *pVerts++ = u1; *pVerts++ = v2;

        *pVerts++ = quad->verts[3].x; *pVerts++ = quad->verts[3].y; *pVerts++ = quad->verts[3].z;
        *(unsigned int*)pVerts = color; pVerts++;
        *pVerts++ = u2; *pVerts++ = v2;
    }

    // Draw as triangle strip
    Draw(3, totalVerts, effect);
}

void gbDynVertBuf::RenderLineStrip(gbColorQuad color, gbVec3D* points, int numPoints, gbRenderEffect* effect) {
    if (numPoints <= 0) return;

    // If no global line effect exists, create one via gbEffectMgr::NewTrivalEffect(3)
    if (pLineEffect == NULL && pGfxMgr != NULL) {
        pLineEffect = pGfxMgr->pEffectMgr->NewTrivalEffect(3);
    }

    // If no effect param passed, use the global line effect
    if (effect == NULL) {
        effect = pLineEffect;
    }

    // Lock buffer for numPoints vertices
    float* pVerts = Lock(numPoints);
    if (!pVerts) return;

    // Write vertices: for each point, write XYZ and color then step
    unsigned int colorVal = *(unsigned int*)&color;

    for (int i = 0; i < numPoints; i++) {
        // Write XYZ to current position pointer
        m_pXYZ[0] = points[i].x;
        m_pXYZ[1] = points[i].y;
        m_pXYZ[2] = points[i].z;
        // Write color
        *(unsigned int*)m_pColor1 = colorVal;
        // Advance internal vertex pointers
        StepVertexPtr();
    }

    // Draw as line strip: numPoints vertices
    Draw(5, numPoints, effect);
}
