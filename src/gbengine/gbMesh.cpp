/**
 * gbengine.dll - gbMesh
 * Mesh classes for static and dynamic geometry
 */

#include "gbengine/gbMesh.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include <string.h>
#include <stdlib.h>


/* ======== gbMeshSection ======== */

gbMeshSection::gbMeshSection() {
    m_blendMode = 0;
    m_hasMultiTex = 0;
    memset(m_textures, 0, sizeof(m_textures));
    m_numTextures = 0;
    memset(m_material, 0, sizeof(m_material));
    m_pIndexBubble = NULL;
    m_vertStartCount = 0;
    m_faceStartCount = 0;
    m_boundCenter.x = 0.0f;
    m_boundCenter.y = 0.0f;
    m_boundCenter.z = 0.0f;
    m_overrideEffect = NULL;
    m_animTexArray = NULL;
    m_animTexSlot = 0;
    m_numAnimFrames = 0;
    m_animFrameInterval = 0;
}


/* ======== gbBaseMesh ======== */

// Static member initialization
int gbBaseMesh::Effect_RefCount = 0;
gbRenderEffect** gbBaseMesh::pShadowEffect = NULL;
char* gbBaseMesh::TextureDir = NULL;

// Constructor
gbBaseMesh::gbBaseMesh(gbGfxManager* gfxMgr) {
    m_refCount = 1;
    m_resName = NULL;
    m_resCrc = 0;
    m_resPrev = NULL;
    m_resNext = NULL;
    m_fvf = 0;
    memset(m_objectName, 0, sizeof(m_objectName));
    m_field2C = NULL;
    m_field30 = NULL;
    m_field34 = NULL;
    m_field38 = NULL;
    m_flags = 0;
    m_sections = NULL;
    m_numSections = 0;
    memset(&m_memCache, 0, sizeof(m_memCache));
    memset(&m_aabb, 0, sizeof(m_aabb));
    m_currentTime = 0.0f;
    m_pGfxManager = gfxMgr;

    if (Effect_RefCount == 0) {
        // pShadowEffect = gfxMgr->GetEffectMgr()->NewRenderEffect(...)
    }
    Effect_RefCount++;
}

// Copy constructor
gbBaseMesh::gbBaseMesh(const gbBaseMesh& other) {
    m_refCount = 1;
    m_resName = other.m_resName;
    m_resCrc = other.m_resCrc;
    m_resPrev = other.m_resPrev;
    m_resNext = other.m_resNext;
    m_fvf = other.m_fvf;
    memcpy(m_objectName, other.m_objectName, sizeof(m_objectName));
    m_field2C = other.m_field2C;
    m_field30 = other.m_field30;
    m_field34 = other.m_field34;
    m_field38 = other.m_field38;
    m_flags = other.m_flags;
    m_numSections = other.m_numSections;
    m_currentTime = other.m_currentTime;
    m_pGfxManager = other.m_pGfxManager;
    m_aabb = other.m_aabb;
    m_memCache = other.m_memCache;

    if (other.m_sections && m_numSections > 0) {
        m_sections = new gbMeshSection[m_numSections];
        memcpy(m_sections, other.m_sections, m_numSections * sizeof(gbMeshSection));
    } else {
        m_sections = NULL;
    }

    Effect_RefCount++;
}

// Destructor
gbBaseMesh::~gbBaseMesh() {
    if (m_sections) {
        delete[] m_sections;
        m_sections = NULL;
    }

    Effect_RefCount--;

    if (Effect_RefCount == 0) {
        pShadowEffect = NULL;
    }
}

// Assignment operator
gbBaseMesh& gbBaseMesh::operator=(const gbBaseMesh& other) {
    if (this == &other) return *this;

    if (m_sections) {
        delete[] m_sections;
    }

    m_resName = other.m_resName;
    m_resCrc = other.m_resCrc;
    m_resPrev = other.m_resPrev;
    m_resNext = other.m_resNext;
    m_fvf = other.m_fvf;
    memcpy(m_objectName, other.m_objectName, sizeof(m_objectName));
    m_field2C = other.m_field2C;
    m_field30 = other.m_field30;
    m_field34 = other.m_field34;
    m_field38 = other.m_field38;
    m_flags = other.m_flags;
    m_numSections = other.m_numSections;
    m_currentTime = other.m_currentTime;
    m_pGfxManager = other.m_pGfxManager;
    m_aabb = other.m_aabb;
    m_memCache = other.m_memCache;

    if (other.m_sections && m_numSections > 0) {
        m_sections = new gbMeshSection[m_numSections];
        memcpy(m_sections, other.m_sections, m_numSections * sizeof(gbMeshSection));
    } else {
        m_sections = NULL;
    }

    return *this;
}

// Out-of-line accessors
gbMeshSection* gbBaseMesh::GetMeshSection(int index) {
    if (index < 0 || index >= m_numSections) return NULL;
    return &m_sections[index];
}

int gbBaseMesh::GetNumSection() {
    return m_numSections;
}

int gbBaseMesh::GetNumFaces() {
    int totalFaces = 0;
    for (int i = 0; i < m_numSections; i++) {
        gbIndexBubble* ib = (gbIndexBubble*)m_sections[i].m_pIndexBubble;
        if (ib)
            totalFaces += ib->count / 3;
    }
    return totalFaces;
}

unsigned int gbBaseMesh::GetFVF() {
    return 0;
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
        gbMeshSection* section = &m_sections[i];

        if (index < section->m_numTextures && section->m_textures[index] != NULL) {
            // Release old texture
        }

        // Assign new texture
        section->m_textures[index] = texture;

        if (section->m_numTextures < index + 1) {
            section->m_numTextures = index + 1;
        }
    }
}

void gbBaseMesh::ReplaceTexture(const char* textureName) {
    if (!m_sections) return;
}

void gbBaseMesh::ReplaceTexture(gbTexture* texture) {
    if (m_sections)
        m_sections[0].m_textures[0] = texture;
}

void gbBaseMesh::ComputeShadowVolume() {
    (void)0;
}

void gbBaseMesh::SetMeshTexDir(char* dir) {
    TextureDir = dir;
}


/* ======== gbStaticMesh ======== */

// Static member initialization
char* gbStaticMesh::LightMapDir = NULL;

gbStaticMesh::gbStaticMesh(gbGfxManager* gfxMgr) : gbBaseMesh(gfxMgr) {
    m_pVertBubble = NULL;
    m_shadowVolumeVB = NULL;
    m_shadowVolumeIB = NULL;
    m_fvf = 0;
}

gbStaticMesh::gbStaticMesh(const gbStaticMesh& other) : gbBaseMesh(other) {
    m_pVertBubble = other.m_pVertBubble;
    m_shadowVolumeVB = other.m_shadowVolumeVB;
    m_shadowVolumeIB = other.m_shadowVolumeIB;
}

gbStaticMesh::~gbStaticMesh() {
    if (m_pVertBubble) {
        m_pVertBubble = NULL;
    }
    if (m_shadowVolumeVB) {
        m_shadowVolumeVB = NULL;
    }
    if (m_shadowVolumeIB) {
        m_shadowVolumeIB = NULL;
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
static void BuildShadowVolumeData(void* params) {
    if (!params) return;
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
        gbMeshSection* section = &m_sections[i];
        gbIndexBubble* idxBubble = (gbIndexBubble*)section->m_pIndexBubble;
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
                gbMeshSection* section = &m_sections[i];
                gbIndexBubble* idxBubble = (gbIndexBubble*)section->m_pIndexBubble;
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
gbRenderEffect* gbDynVertBuf::pLineEffect = NULL;

gbDynVertBuf::gbDynVertBuf(unsigned int fvfFlags, int maxVertices) {
    m_fvfFlags = fvfFlags;
    m_maxVertices = maxVertices;
    m_currentVertex = 0;
    m_vertexBuffer = NULL;
    m_vertexStride = 0;
    m_pXYZ = NULL;
    m_pNormal = NULL;
    m_pColor1 = NULL;
    m_pColor2 = NULL;
    memset(m_pUV, 0, sizeof(m_pUV));
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
    memcpy(m_pUV, other.m_pUV, sizeof(m_pUV));
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
        memcpy(m_pUV, other.m_pUV, sizeof(m_pUV));
        m_vertNum = other.m_vertNum;
    }
    return *this;
}

float* gbDynVertBuf::GetXYZ() {
    return m_pXYZ;
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
    return m_pUV[index];
}

void gbDynVertBuf::StepVertexPtr() {
    m_currentVertex++;
    if (m_currentVertex >= m_maxVertices) {
        m_currentVertex = 0;
    }
}

// gbDynVertBuf methods moved to gbDynVertBuf.cpp
