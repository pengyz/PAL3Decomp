/**
 * gbengine.dll - gbMesh
 * Mesh classes for static and dynamic geometry
 */

#include "gbengine/gbMesh.h"
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
}

void gbBaseMesh::ReplaceTexture(const char* textureName) {
}

void gbBaseMesh::ReplaceTexture(gbTexture* texture) {
}

void gbBaseMesh::ComputeShadowVolume() {
}

void gbBaseMesh::RenderShadowVolume(gbVisNode* visNode, gbRenderInfoObj* renderInfo) {
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

void gbStaticMesh::ComputeShadowVolume() {
}

void gbStaticMesh::RenderShadowVolume(gbVisNode* visNode, gbRenderInfoObj* renderInfo) {
    if (!m_shadowVolumeVB || !m_shadowVolumeIB) return;
}

gbVertexBubble* gbStaticMesh::GetVertBubble() {
    return m_pVertBubble;
}


/* ======== gbDynVertBuf ======== */

// Static member
gbGfxManager* gbDynVertBuf::pGfxMgr = nullptr;

gbDynVertBuf::gbDynVertBuf(unsigned int fvfFlags, int maxVertices) {
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

void gbDynVertBuf::RenderUIQuad(gbUIQuad* quadData, int numQuads, gbRenderEffect* effect, gbTextureArray* textures) {
}

void gbDynVertBuf::RenderGeomQuad(gbGeomQuad* quadData, int numQuads, gbRenderEffect* effect, gbTextureArray* textures) {
}

void gbDynVertBuf::RenderGeomQuadViaStrip(gbGeomQuad* quadData, int numQuads, gbRenderEffect* effect, gbTextureArray* textures) {
    RenderGeomQuadViaStrip(quadData, numQuads, effect, textures, 0);
}

void gbDynVertBuf::RenderGeomQuadViaStrip(gbGeomQuad* quadData, int numQuads, gbRenderEffect* effect, gbTextureArray* textures, unsigned long flags) {
}

void gbDynVertBuf::RenderLineStrip(gbColorQuad color, gbVec3D* points, int numPoints, gbRenderEffect* effect) {
}
