/**
 * gbengine.dll - gbMesh
 * Mesh classes for static and dynamic geometry
 */

#include "gbengine/gbMesh.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbVisNode.h"
#include "gbengine/gbSceneGraph.h"
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
char gbBaseMesh::TextureDir[260] = "";

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

// 0x100048b0 - operator= (174B)
gbBaseMesh& gbBaseMesh::operator=(const gbBaseMesh& other) {
    m_resName = other.m_resName;
    m_resCrc = other.m_resCrc;
    m_resPrev = other.m_resPrev;
    m_resNext = other.m_resNext;
    m_fvf = other.m_fvf;
    m_pGfxManager = other.m_pGfxManager;
    memcpy(m_objectName, other.m_objectName, 0x20u);
    m_field2C = other.m_field2C;
    m_field30 = other.m_field30;
    m_field34 = other.m_field34;
    m_field38 = other.m_field38;
    m_flags = other.m_flags;
    m_numSections = other.m_numSections;
    m_sections = other.m_sections;
    m_currentTime = other.m_currentTime;
    m_aabb = other.m_aabb;
    m_memCache = other.m_memCache;
    return *this;
}

// Out-of-line accessors
gbMeshSection* gbBaseMesh::GetMeshSection(int index) {
    return &m_sections[index];
}

int gbBaseMesh::GetNumSection() {
    return m_numSections;
}

int gbBaseMesh::GetNumFaces() {
    int v1 = m_numSections;
    int v2 = 0;
    if (v1 > 0) {
        int* v3 = (int*)((int)m_sections + 144);
        do {
            int v4 = *v3;
            v3 += 47;
            v2 += *(int*)(v4 + 16) / 3;
        } while (--v1);
    }
    return v2;
}

unsigned int gbBaseMesh::GetFVF() {
    return m_fvf;
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
    gbTexture* tex = m_pGfxManager->NewTexture(textureName);
    tex->LoadTexture(1);
    ReplaceTexture(tex);
}

void gbBaseMesh::ReplaceTexture(gbTexture* texture) {
    m_sections[0].m_textures[0] = texture;
}

void gbBaseMesh::ComputeShadowVolume() {
    (void)0;
}

void gbBaseMesh::SetMeshTexDir(char* dir) {
    if (!dir)
        strcpy(TextureDir, "");
    else
        strcpy(TextureDir, dir);
}


/* ======== SetupMeshLighting (sub_100156F0) ======== */
// Helper function that sets up lighting/effect variants before drawing a mesh subset.
// Called from DrawSubSet. Sets world-view-projection matrix and ambient/emissive lighting.
// Original: 1443 bytes at 0x100156F0

static void SetupMeshLighting(gbRenderInfoObj* renderInfo, gbGfxManager* gfxMgr, float* materialData)
{
    // Get matrix stacks: [0]=view/projection, [1]=world
    gbMatrixStack* projStack = gfxMgr->pMatrixStack[0];
    gbMatrixStack* worldStack = gfxMgr->pMatrixStack[1];

    gbMatrix4* worldTop = worldStack->GetTop();
    gbMatrix4* projTop = projStack->GetTop();

    // Build combined matrix: world * scale * projection
    gbMatrix4 scaleMatrix;
    scaleMatrix.LoadIdentity();
    scaleMatrix.m[3][3] = -1.0f;

    gbMatrix4 combinedMatrix;
    combinedMatrix = *worldTop;
    combinedMatrix.RightMultiply(scaleMatrix);
    combinedMatrix.RightMultiply(*projTop);

    // Invert world matrix
    gbMatrix4 invWorld;
    worldTop->Invert(&invWorld);

    // Get render effect from renderInfo
    gbRenderEffect* effect = renderInfo->pEffect;
    unsigned int flags = renderInfo->renderFlags;

    // Get blend factor from the vis node
    float blendFactor = 1.0f;
    gbVisNode* node = renderInfo->pNode;
    if (node) {
        float bval;
        NodeBlend blendMode = node->GetBlend(bval);
        if (blendMode != BLEND_NONE) {
            blendFactor = bval;
        }
    }

    // Set world*view*projection matrix (variant 0) if flags indicate
    if (flags & 0x201) {
        effect->SetVariant(GBPARAM_WORLDMATRIX, &combinedMatrix);
    }

    // Compute ambient + emissive lighting (variant 4)
    // Material layout (D3DMATERIAL9-like, as float array):
    //   [0..3]  = diffuse  (r, g, b, a)
    //   [4..7]  = ambient  (r, g, b, a)
    //   [8..11] = specular (r, g, b, a)
    //   [12..15] = emissive (r, g, b, a)
    //   [16]    = power
    //
    // The original code uses offsets that map materialData:
    //   ambient at [4..7], emissive at [12..15], diffuse alpha at [3]
    float result[4];
    float ambR = gfxMgr->AmbientLight.r;
    float ambG = gfxMgr->AmbientLight.g;
    float ambB = gfxMgr->AmbientLight.b;
    float selfIllum = gfxMgr->fSelfIllum;

    // result = ambient_light * material_ambient + selfIllum * material_emissive
    result[0] = ambR * materialData[4] + selfIllum * materialData[12];
    result[1] = ambG * materialData[5] + selfIllum * materialData[13];
    result[2] = ambB * materialData[6] + selfIllum * materialData[14];
    result[3] = blendFactor * materialData[3];

    // SetVariant index 4 for the lighting result
    // Using the name-based variant setter for extended parameters
    effect->SetVariant((char*)"g_MaterialAmbient", result);

    // Set light direction variant if flags & 0x10
    if (flags & 0x10) {
        // Transform light direction to view space using inverse world matrix
        // Use first enabled directional light
        gbVec3D lightDir;
        lightDir.x = gfxMgr->AllLight[0].direction.x;
        lightDir.y = gfxMgr->AllLight[0].direction.y;
        lightDir.z = gfxMgr->AllLight[0].direction.z;

        gbVec3D transformedDir;
        invWorld.Rotate(&lightDir, &transformedDir);
        transformedDir.Normalize();

        float dirData[4];
        dirData[0] = transformedDir.x;
        dirData[1] = transformedDir.y;
        dirData[2] = transformedDir.z;
        dirData[3] = 0.0f;
        effect->SetVariant((char*)"g_LightDir", dirData);

        // Set diffuse light color * material diffuse
        float diffResult[4];
        diffResult[0] = gfxMgr->AllLight[0].diffuse.r * materialData[0];
        diffResult[1] = gfxMgr->AllLight[0].diffuse.g * materialData[1];
        diffResult[2] = gfxMgr->AllLight[0].diffuse.b * materialData[2];
        diffResult[3] = 1.0f;
        effect->SetVariant((char*)"g_MaterialDiffuse", diffResult);
    }
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

// 0x10011a10 - operator= (198B)
gbStaticMesh& gbStaticMesh::operator=(const gbStaticMesh& other) {
    m_resName = other.m_resName;
    m_resCrc = other.m_resCrc;
    m_resPrev = other.m_resPrev;
    m_resNext = other.m_resNext;
    m_fvf = other.m_fvf;
    m_pGfxManager = other.m_pGfxManager;
    memcpy(m_objectName, other.m_objectName, 0x20u);
    m_field2C = other.m_field2C;
    m_field30 = other.m_field30;
    m_field34 = other.m_field34;
    m_field38 = other.m_field38;
    m_flags = other.m_flags;
    m_numSections = other.m_numSections;
    m_sections = other.m_sections;
    m_currentTime = other.m_currentTime;
    m_aabb = other.m_aabb;
    m_memCache = other.m_memCache;
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
    gbMeshSection* section = &m_sections[index];

    if (section->m_pIndexBubble) {
        // Set material on gfx manager (vtable slot 11, offset +44)
        m_pGfxManager->SetMaterial((D3DMATERIAL9*)section->m_material);

        // Flush matrix stacks to D3D (vtable slot 15, offset +60)
        m_pGfxManager->DrawPrimitive();

        // Setup lighting/effect variants
        SetupMeshLighting(renderInfo, m_pGfxManager, (float*)section->m_material);

        // Draw indexed primitive via vertex pool
        // m_pVertBubble->pPool is the gbVertexPool, call its virtual DrawIndexedPrimitive
        gbVertexPool* pool = m_pVertBubble->pPool;
        pool->DrawIndexedPrimitive(
            m_pVertBubble,
            section->m_pIndexBubble,
            renderInfo->sectionIndex,
            section->m_textures
        );
    }
}

// Forward declarations for topo.dll imports (CreateTopoGeom/DestroyTopoGeom)
// These are resolved through the IAT at link time via topo.lib
struct TopoDataDesc;
enum TopoType { TOPO_SIMPLE = 0, TOPO_COMPLEX = 1 };

// ITopoGeom abstract interface (vtable layout from topo.dll):
//   vtable[0] = Generate(outputDesc*, float threshold)
//   vtable[1] = unknown
//   vtable[2] = Release(outputDesc*)
// We declare a matching class so the compiler generates correct thiscall vtable calls.
class ITopoGeom {
public:
    virtual void Generate(void* outputDesc, float threshold) = 0;
    virtual void Unknown() = 0;
    virtual void Release(void* outputDesc) = 0;
};

__declspec(dllimport) ITopoGeom* __cdecl CreateTopoGeom(TopoDataDesc* pDesc, TopoType type);
__declspec(dllimport) int __cdecl DestroyTopoGeom(ITopoGeom* pObj);

// TopoDataDesc: input descriptor for CreateTopoGeom (15 DWORDs = 60 bytes)
struct TopoDataDesc {
    void* pVertexData;      // +0x00: vertex position data
    int   vertexStride;     // +0x04: 0 = use bufferRowSize
    int   vertexFlags;      // +0x08
    int   desc_0C;          // +0x0C
    int   desc_10;          // +0x10
    int   desc_14;          // +0x14
    int   desc_18;          // +0x18
    int   desc_1C;          // +0x1C
    int   bufferRowSize;    // +0x20: bytes per vertex row (e.g. 12 for XYZ)
    int   vertexCount;      // +0x24: number of vertices
    void* pIndices16;       // +0x28: 16-bit index buffer
    void* pIndices32;       // +0x2C: 32-bit index buffer (NULL if using 16-bit)
    int   faceCount;        // +0x30: number of triangles
    int   field_34;         // +0x34
    int   field_38;         // +0x38: epsilon as float bits (0x3C23D70A = 0.01f)
};

// TopoGeom output descriptor (filled by ITopoGeom::Generate)
// Layout matches stack usage in FUN_10016c70
struct TopoOutputDesc {
    void* pVertexData;      // +0x00: output vertex positions
    int   field_04;         // +0x04
    int   field_08;         // +0x08
    int   field_0C;         // +0x0C
    int   field_10;         // +0x10
    int   field_14;         // +0x14
    int   field_18;         // +0x18
    int   field_1C;         // +0x1C
    void* pIndexData;       // +0x20: output index data
    int   stride;           // +0x24: output vertex stride
    int   numVertices;      // +0x28: output vertex count
    int   numFaces;         // +0x2C: output face count
    int   field_30;         // +0x30
    int   field_34;         // +0x34
    int   field_38;         // +0x38
};

// Internal shadow volume builder (0x10016c70, 308 bytes)
// Calls CreateTopoGeom to generate shadow volume geometry,
// then creates vertex/index bubbles with the result.
static void BuildShadowVolumeData(
    TopoDataDesc* desc,
    gbGfxManager* gfxMgr,
    unsigned int fvf,
    gbVertexBubble** ppOutVB,
    gbIndexBubble** ppOutIB)
{
    // Create topology geometry object (type 0 = simple)
    ITopoGeom* pTopoGeom = CreateTopoGeom(desc, TOPO_SIMPLE);

    // Initialize output descriptor
    TopoOutputDesc outputDesc;
    memset(&outputDesc, 0, sizeof(outputDesc));
    outputDesc.field_04 = -1;
    outputDesc.field_08 = -1;
    outputDesc.stride = -1;
    outputDesc.field_0C = -1;
    outputDesc.field_10 = -1;
    outputDesc.field_14 = -1;
    outputDesc.numVertices = -1;

    // Generate shadow volume geometry (threshold = 0.6f)
    pTopoGeom->Generate(&outputDesc, 0.6f);

    // Get vertex pool manager from gfx manager
    gbVertPoolMgr* poolMgr = gfxMgr->pVertPoolMgr;

    // Create index bubble for shadow volume (triangle list, numFaces*3 indices)
    gbIndexBubble* idxBubble = poolMgr->NewIndexBubble(GB_PRIM_POINTLIST, outputDesc.numFaces * 3);

    // Lock and copy index data
    unsigned short* pLockedIdx = idxBubble->Lock16();
    memcpy(pLockedIdx, outputDesc.pIndexData, outputDesc.numFaces * 6);
    idxBubble->Unlock();

    // Set index bubble range fields
    idxBubble->field_1C = 0;
    idxBubble->field_20 = outputDesc.numVertices - 1;

    // Create vertex bubble for shadow volume
    gbVertexBubble* vtxBubble = poolMgr->NewVertexBubble(fvf, outputDesc.numVertices);

    // Lock and copy vertex data
    void* pLockedVtx = vtxBubble->Lock();
    memcpy(pLockedVtx, outputDesc.pVertexData, outputDesc.stride * outputDesc.numVertices);
    vtxBubble->Unlock();

    // Release topology output data
    pTopoGeom->Release(&outputDesc);

    // Write output pointers
    *ppOutVB = vtxBubble;
    *ppOutIB = idxBubble;

    // Destroy topology geometry object
    DestroyTopoGeom(pTopoGeom);
}

void gbStaticMesh::ComputeShadowVolume() {
    if (m_shadowVolumeVB != NULL) return;

    // Get vertex count from vertex bubble
    int numVerts = m_pVertBubble->vertexCount;

    // Allocate position array (numVerts * 12 bytes for XYZ floats)
    unsigned int* Block = (unsigned int*)operator new(numVerts * 12);
    if (Block != NULL) {
        // Zero-initialize the position array
        if (numVerts - 1 >= 0) {
            unsigned int* ptr = Block + 2;
            int count = numVerts;
            do {
                ptr[-2] = 0;
                ptr[-1] = 0;
                ptr[0] = 0;
                ptr += 3;
                --count;
            } while (count);
        }
    } else {
        Block = NULL;
    }

    // Lock vertex bubble and copy XYZ positions
    m_pVertBubble->Lock();
    gbVertexBubble* vBubble = m_pVertBubble;
    int idx = 0;
    if (vBubble->vertexCount > 0) {
        unsigned int* dst = Block + 2;
        do {
            unsigned int* src = (unsigned int*)vBubble->pVertexData;
            dst[-2] = src[0];   // x
            dst[-1] = src[1];   // y
            dst[0] = src[2];    // z
            m_pVertBubble->StepVertexPtr();
            vBubble = m_pVertBubble;
            ++idx;
            dst += 3;
        } while (idx < vBubble->vertexCount);
    }
    m_pVertBubble->Unlock();

    // Count total indices from all sections
    int numSec = m_numSections;
    int totalIndices = 0;
    if (numSec > 0) {
        int* pIdxBubblePtr = (int*)((char*)m_sections + 0x90);
        do {
            int bubPtr = *pIdxBubblePtr;
            pIdxBubblePtr = (int*)((char*)pIdxBubblePtr + 0xBC);
            totalIndices += *(int*)(bubPtr + 0x10);
            --numSec;
        } while (numSec);
    }

    // Allocate index array (16-bit indices)
    unsigned short* indexBuf = (unsigned short*)operator new(totalIndices * 2);
    int sectionOffset = 0;
    int totalCopied = 0;
    unsigned short* savedIndexBuf = indexBuf;

    // Copy indices from all sections
    for (int i = 0; i < m_numSections; ++i) {
        gbIndexBubble* iBubble = *(gbIndexBubble**)((char*)m_sections + sectionOffset + 0x90);
        unsigned short* pSrc = iBubble->Lock16();
        int innerCount = 0;
        if (iBubble->count > 0) {
            unsigned short* pDst = &indexBuf[totalCopied];
            do {
                ++totalCopied;
                *pDst = *pSrc;
                pDst++;
                ++innerCount;
                pSrc++;
            } while (innerCount < iBubble->count);
            indexBuf = savedIndexBuf;
        }
        iBubble = *(gbIndexBubble**)((char*)m_sections + sectionOffset + 0x90);
        iBubble->Unlock();
        sectionOffset += 188;
    }

    // Build TopoDataDesc parameter struct
    TopoDataDesc topoDesc;
    topoDesc.vertexFlags = -1;
    topoDesc.desc_0C = -1;
    topoDesc.desc_10 = -1;
    topoDesc.desc_14 = -1;
    topoDesc.desc_18 = -1;
    topoDesc.desc_1C = -1;
    topoDesc.field_34 = 0;
    topoDesc.field_38 = 0;
    topoDesc.faceCount = totalCopied / 3;
    topoDesc.vertexCount = m_pVertBubble->vertexCount;
    topoDesc.pIndices16 = indexBuf;
    topoDesc.vertexStride = 0;
    topoDesc.pVertexData = Block;
    topoDesc.bufferRowSize = 12;
    topoDesc.pIndices32 = NULL;
    // Store epsilon as float bits: 0x3C23D70A = 0.01f
    *(int*)&topoDesc.field_38 = 0x3C23D70A;

    BuildShadowVolumeData(
        &topoDesc,
        m_pGfxManager,
        3,
        (gbVertexBubble**)&m_shadowVolumeVB,
        (gbIndexBubble**)&m_shadowVolumeIB
    );

    operator delete(Block);
    operator delete(indexBuf);
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

extern int gbComputeFVFStride(unsigned int fvf);

gbDynVertBuf::gbDynVertBuf(unsigned int fvfFlags, int maxVertices) {
    m_vertNum = maxVertices;
    m_field04 = 1;
    m_fvfFlags = fvfFlags;
    m_vertexStride = gbComputeFVFStride(fvfFlags);
    m_currentVertex = 0;
    m_vertexBuffer = NULL;
}

gbDynVertBuf::gbDynVertBuf(const gbDynVertBuf& other) {
    m_field04 = other.m_field04;
    m_vertNum = other.m_vertNum;
    m_fvfFlags = other.m_fvfFlags;
    m_vertexStride = other.m_vertexStride;
    m_currentVertex = other.m_currentVertex;
    m_vertexBuffer = other.m_vertexBuffer;
    m_pXYZ = other.m_pXYZ;
    m_pNormal = other.m_pNormal;
    m_pColor1 = other.m_pColor1;
    m_pColor2 = other.m_pColor2;
    memcpy(m_pUV, other.m_pUV, sizeof(m_pUV));
}

gbDynVertBuf::~gbDynVertBuf() {
}

gbDynVertBuf& gbDynVertBuf::operator=(const gbDynVertBuf& other) {
    if (this != &other) {
        m_field04 = other.m_field04;
        m_vertNum = other.m_vertNum;
        m_fvfFlags = other.m_fvfFlags;
        m_vertexStride = other.m_vertexStride;
        m_currentVertex = other.m_currentVertex;
        m_vertexBuffer = other.m_vertexBuffer;
        m_pXYZ = other.m_pXYZ;
        m_pNormal = other.m_pNormal;
        m_pColor1 = other.m_pColor1;
        m_pColor2 = other.m_pColor2;
        memcpy(m_pUV, other.m_pUV, sizeof(m_pUV));
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
    unsigned int flags = m_fvfFlags;
    if (flags & 0x01)
        m_pXYZ = (float*)((char*)m_pXYZ + m_vertexStride);
    if (flags & 0x02)
        m_pNormal = (float*)((char*)m_pNormal + m_vertexStride);
    if (flags & 0x04)
        m_pColor1 = (gbColorQuad*)((char*)m_pColor1 + m_vertexStride);
    if (flags & 0x08)
        m_pColor2 = (gbColorQuad*)((char*)m_pColor2 + m_vertexStride);
    if (flags & 0x10)
        m_pUV[0] = (float*)((char*)m_pUV[0] + m_vertexStride);
    if (flags & 0x20)
        m_pUV[1] = (float*)((char*)m_pUV[1] + m_vertexStride);
    if (flags & 0x40)
        m_pUV[2] = (float*)((char*)m_pUV[2] + m_vertexStride);
    if (flags & 0x80)
        m_pUV[3] = (float*)((char*)m_pUV[3] + m_vertexStride);
}

// gbDynVertBuf methods moved to gbDynVertBuf.cpp
