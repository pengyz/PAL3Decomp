/**
 * gbengine.dll - gbMesh
 * Mesh classes for static and dynamic geometry
 */

#include "gbengine/gbMesh.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbGfxManager_impl.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbVisNode.h"
#include "gbengine/gbSceneGraph.h"
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

extern int gbComputeFVFStride(unsigned int fvf);
extern void gbColorQuadToFloat4(float* dest, unsigned char* src);
extern unsigned int gbCrc32Compute(const char* data, int len);
extern gbGfxManager* g_pActorGfxMgr;  // dword_1012B99C

// Internal helper: build canonical vertex from skin data (52 bytes output)
// 0x100063E0
static int BuildCanonicalVertex(int a1, int a2, int a3, int a4);
// Internal helper: build canonical vertex for index strip (56 bytes output)
// 0x100068F0
static int BuildCanonicalVertexStrip(int a1, int a2);

// These are defined elsewhere in this translation unit (or linked):
// 0x10006E70
extern void SortBoneWeights(int* pMeshData, int maxBones);
// 0x1000B4F0
extern void PartitionMesh(unsigned int* pMeshData, int maxBonesPerSection);
// 0x10016C70
extern void BuildShadowVolumeDataInternal(void* desc, int gfxMgr, unsigned int fvf, void* ppOutVB, void* ppOutIB);


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
    m_isLoaded = 0;
    m_pResMgr = NULL;
    m_meshType = MESH_STATIC;
    memset(m_objectName, 0, sizeof(m_objectName));
    m_vertFVF = 0;
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
    m_isLoaded = other.m_isLoaded;
    m_pResMgr = other.m_pResMgr;
    m_meshType = other.m_meshType;
    memcpy(m_objectName, other.m_objectName, sizeof(m_objectName));
    m_vertFVF = other.m_vertFVF;
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
    m_isLoaded = other.m_isLoaded;
    m_pResMgr = other.m_pResMgr;
    m_meshType = other.m_meshType;
    m_pGfxManager = other.m_pGfxManager;
    memcpy(m_objectName, other.m_objectName, 0x20u);
    m_vertFVF = other.m_vertFVF;
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
    return m_vertFVF;
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
    float ambR = gfxMgr->AmbientLight.Red;
    float ambG = gfxMgr->AmbientLight.Green;
    float ambB = gfxMgr->AmbientLight.Blue;
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
        lightDir.x = gfxMgr->AllLight[0].Direction.x;
        lightDir.y = gfxMgr->AllLight[0].Direction.y;
        lightDir.z = gfxMgr->AllLight[0].Direction.z;

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
        diffResult[0] = gfxMgr->AllLight[0].diffuse.Red * materialData[0];
        diffResult[1] = gfxMgr->AllLight[0].diffuse.Green * materialData[1];
        diffResult[2] = gfxMgr->AllLight[0].diffuse.Blue * materialData[2];
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
    m_meshType = (gbMeshType)0;
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
    m_isLoaded = other.m_isLoaded;
    m_pResMgr = other.m_pResMgr;
    m_meshType = other.m_meshType;
    m_pGfxManager = other.m_pGfxManager;
    memcpy(m_objectName, other.m_objectName, 0x20u);
    m_vertFVF = other.m_vertFVF;
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
    int   bufferRowSize;    // +0x20: bytes per vertex row (e.Green. 12 for XYZ)
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


/* ======== gbMesh ======== */

gbMesh::gbMesh(gbGfxManager* gfxMgr) : gbBaseMesh(gfxMgr) {
    m_field78 = 0;
    m_pVertBubbles = NULL;
    m_pFrameTimes = NULL;
    m_numVertFrames = 0;
    m_pLODKeys = NULL;
}

gbMesh::~gbMesh() {
    if (m_pVertBubbles) {
        for (int i = 0; i < m_numVertFrames; i++) {
            if (m_pVertBubbles[i])
                free(m_pVertBubbles[i]);
        }
        free(m_pVertBubbles);
        m_pVertBubbles = NULL;
    }
    if (m_pFrameTimes) { free(m_pFrameTimes); m_pFrameTimes = NULL; }
    if (m_pLODKeys) { free(m_pLODKeys); m_pLODKeys = NULL; }
}

void gbMesh::DrawSubSet(int index, gbRenderInfoObj* renderInfo) {
    gbMeshSection* section = &m_sections[index];

    if (section->m_pIndexBubble) {
        m_pGfxManager->SetMaterial((D3DMATERIAL9*)section->m_material);
        m_pGfxManager->DrawPrimitive();

        // Use first frame vertex bubble for rendering
        gbVertexBubble* vb = m_pVertBubbles ? m_pVertBubbles[0] : NULL;
        if (vb) {
            SetupMeshLighting(renderInfo, m_pGfxManager, (float*)section->m_material);
            gbVertexPool* pool = vb->pPool;
            pool->DrawIndexedPrimitive(
                vb,
                section->m_pIndexBubble,
                renderInfo->sectionIndex,
                section->m_textures
            );
        }
    }
}

void gbMesh::ComputeShadowVolume() {
}

void gbMesh::RenderShadowVolume(gbVisNode* visNode, gbRenderInfoObj* renderInfo) {
}

// 0x10011C60 - gbMesh::LoadFromFile (3222 bytes)
int gbMesh::LoadFromFile(gbVFile1* file, float quality) {
    gbVFile* vfile = (gbVFile*)file;
    int numVertsPerFrame;
    int numLODKeys;
    int stride;
    int i;

    if (m_isLoaded) {
        // Already loaded - seek past all data and return
        g_pVFileSys->Seek(vfile, 4, GBVFS_SEEK_CUR);
        g_pVFileSys->Read(&numVertsPerFrame, 4u, vfile);
        stride = gbComputeFVFStride(0x13);
        if (m_numVertFrames)
            g_pVFileSys->Seek(vfile, numVertsPerFrame * stride * m_numVertFrames, GBVFS_SEEK_CUR);
        g_pVFileSys->Seek(vfile, 4 * m_numVertFrames, GBVFS_SEEK_CUR);

        int numSec;
        g_pVFileSys->Read(&numSec, 4u, vfile);
        for (i = 0; i < numSec; i++) {
            char blendByte;
            g_pVFileSys->Read(&blendByte, 1u, vfile);
            g_pVFileSys->Seek(vfile, 20, GBVFS_SEEK_CUR);
            g_pVFileSys->Seek(vfile, 64, GBVFS_SEEK_CUR);
            int idxCount;
            g_pVFileSys->Read(&idxCount, 4u, vfile);
            if (idxCount)
                g_pVFileSys->Seek(vfile, 6 * idxCount, GBVFS_SEEK_CUR);
            if (quality >= 0.5f) {
                g_pVFileSys->Read(&numLODKeys, 4u, vfile);
                if (numLODKeys) {
                    g_pVFileSys->Seek(vfile, 4 * numLODKeys, GBVFS_SEEK_CUR);
                    g_pVFileSys->Seek(vfile, 20 * numLODKeys, GBVFS_SEEK_CUR);
                }
            }
        }
        return 1;
    }

    // First load path
    char texDir[256];
    if (TextureDir[0]) {
        strcpy(texDir, TextureDir);
    } else {
        file->GetDir(texDir, 0x100u);
    }

    // Read vertex frame count and vertices per frame
    g_pVFileSys->Read(&m_numVertFrames, 4u, vfile);
    g_pVFileSys->Read(&numVertsPerFrame, 4u, vfile);

    m_vertFVF = 0x13;
    stride = gbComputeFVFStride(0x13);

    // Allocate per-frame vertex bubble array
    m_pVertBubbles = (gbVertexBubble**)malloc(4 * m_numVertFrames);

    // Allocate temp buffer for raw vertex data
    void* tempBuf = malloc(numVertsPerFrame * stride);

    // Initialize AABB to extremes (raw int bit patterns)
    *(int*)&m_aabb.vMin.x = 2139095039;  // FLT_MAX bit pattern
    *(int*)&m_aabb.vMin.y = 2139095039;
    *(int*)&m_aabb.vMin.z = 2139095039;
    *(int*)&m_aabb.vMax.x = -8388609;    // -FLT_MAX bit pattern
    *(int*)&m_aabb.vMax.y = -8388609;
    *(int*)&m_aabb.vMax.z = -8388609;

    int frameIdx = 0;
    if (m_numVertFrames > 0) {
        while (1) {
            // Read raw vertex data for this frame
            g_pVFileSys->Read(tempBuf, numVertsPerFrame * stride, vfile);

            // Create vertex bubble for this frame
            gbVertPoolMgr* poolMgr = m_pGfxManager->pVertPoolMgr;
            m_pVertBubbles[frameIdx] = poolMgr->NewSrcVertBub(0x13u, numVertsPerFrame);

            gbVertexBubble* bubble = m_pVertBubbles[frameIdx];
            bubble->Lock();

            int vertIdx = 0;
            if (numVertsPerFrame > 0) {
                float* src = (float*)((char*)tempBuf + 20);
                do {
                    // Copy position (from raw offset 20..31) to pVertexData
                    *(float*)bubble->pVertexData = *src;
                    *((float*)bubble->pVertexData + 1) = src[1];
                    *((float*)bubble->pVertexData + 2) = src[2];

                    // Copy normal (from raw offset 8..19) to field_1C
                    *(float*)bubble->field_1C = *(src - 3);
                    *((float*)bubble->field_1C + 1) = *(src - 2);
                    *((float*)bubble->field_1C + 2) = *(src - 1);

                    // Copy UV (from raw offset 0..7) to field_28
                    *(float*)bubble->field_28 = *(src - 5);
                    *((float*)bubble->field_28 + 1) = *(src - 4);

                    // Update AABB
                    if (m_aabb.vMin.x > *src)
                        *(int*)&m_aabb.vMin.x = *(int*)src;
                    if (m_aabb.vMin.y > src[1])
                        *(int*)&m_aabb.vMin.y = *((int*)src + 1);
                    if (m_aabb.vMin.z > src[2])
                        *(int*)&m_aabb.vMin.z = *((int*)src + 2);
                    if (m_aabb.vMax.x < *src)
                        *(int*)&m_aabb.vMax.x = *(int*)src;
                    if (m_aabb.vMax.y < src[1])
                        *(int*)&m_aabb.vMax.y = *((int*)src + 1);
                    if (m_aabb.vMax.z < src[2])
                        *(int*)&m_aabb.vMax.z = *((int*)src + 2);

                    bubble->StepVertexPtr();
                    src += 8;
                    ++vertIdx;
                } while (vertIdx < numVertsPerFrame);
            }

            bubble->Unlock();
            vfile = (gbVFile*)file;
            if (++frameIdx >= m_numVertFrames)
                break;
        }
    }

    // Allocate and read frame times
    m_pFrameTimes = (float*)malloc(4 * m_numVertFrames);
    g_pVFileSys->Read(m_pFrameTimes, 4 * m_numVertFrames, vfile);

    // Normalize frame times (subtract first frame time from all)
    for (int j = 0; j < m_numVertFrames; j++) {
        m_pFrameTimes[j] = m_pFrameTimes[j] - m_pFrameTimes[0];
    }

    // Read number of sections
    g_pVFileSys->Read(&m_numSections, 4u, vfile);

    // Allocate section array using new[] (generates eh vector constructor iterator)
    int numSec = m_numSections;
    m_sections = new gbMeshSection[numSec];

    // Allocate LOD key array
    m_pLODKeys = (gbMeshLODKey*)malloc(8 * m_numSections);
    memset(m_pLODKeys, 0, 8 * m_numSections);

    int sectionIdx = 0;
    if (m_numSections > 0) {
        int sectionOffset = 0;
        do {
            gbVFile* curFile = (gbVFile*)file;
            int gfxMgrAddr = (int)m_pGfxManager;
            gbMeshSection* section = (gbMeshSection*)((char*)m_sections + sectionOffset);
            gbMeshLODKey* lodKey = &m_pLODKeys[sectionIdx];

            // Read blend mode (1 byte)
            unsigned char blendByte;
            g_pVFileSys->Read(&blendByte, 1u, curFile);
            section->m_blendMode = blendByte;

            // Read material data (20 bytes: 4 color quads + 1 float)
            unsigned char colorData[20];
            g_pVFileSys->Read(colorData, 0x14u, curFile);

            // Convert color quads to float material
            gbColorQuadToFloat4((float*)((char*)section + 92), &colorData[4]);    // emission
            gbColorQuadToFloat4((float*)((char*)section + 76), &colorData[0]);    // ambient
            gbColorQuadToFloat4((float*)((char*)section + 124), &colorData[12]);  // specular
            gbColorQuadToFloat4((float*)((char*)section + 108), &colorData[8]);   // diffuse

            // Shininess
            float shininess = *(float*)&colorData[16];
            *(float*)((char*)section + 140) = shininess;
            if (shininess < 0.0f) {
                *(int*)((char*)section + 140) = 0;
            } else if (shininess > 128.0f) {
                *(int*)((char*)section + 140) = 1124073472;  // 128.0f
            }

            // Read texture name (64 bytes)
            char texName[64];
            g_pVFileSys->Read(texName, 0x40u, curFile);

            gbTexture* tex;
            if (texName[0]) {
                char texPath[256];
                strcpy(texPath, texDir);
                strcat(texPath, texName);
                tex = m_pGfxManager->NewTexture(texPath);
                tex->LoadTexture(1);
                curFile = (gbVFile*)file;
            } else {
                gbEffectMgr* effMgr = *(gbEffectMgr**)((char*)m_pGfxManager + 200);
                tex = effMgr->GetWhiteTexture();
                tex->refCount++;
            }

            // Store texture
            section->m_textures[section->m_numTextures++] = tex;
            section->m_hasMultiTex = 0;

            // Read index count
            int idxCount;
            g_pVFileSys->Read(&idxCount, 4u, curFile);

            if (idxCount) {
                // Initialize vertex range
                section->m_faceStartCount = 0;
                section->m_vertStartCount = -1;

                // Read index data
                int idxDataSize = 6 * idxCount;
                unsigned short* idxBuf = (unsigned short*)malloc(idxDataSize);
                g_pVFileSys->Read(idxBuf, idxDataSize, curFile);

                // Find min/max vertex indices
                int totalIdx = 3 * idxCount;
                if (totalIdx > 0) {
                    unsigned short* ptr = idxBuf;
                    int count = totalIdx;
                    do {
                        if ((unsigned int)section->m_vertStartCount > (unsigned int)(unsigned short)*ptr) {
                            section->m_vertStartCount = (unsigned short)*ptr;
                        }
                        if ((unsigned int)section->m_faceStartCount < (unsigned int)(unsigned short)*ptr) {
                            section->m_faceStartCount = (unsigned short)*ptr;
                        }
                        ++ptr;
                        --count;
                    } while (count);
                }

                // Rebase indices by subtracting min
                int rebaseIdx = 0;
                if (totalIdx > 0) {
                    unsigned short* ptr2 = idxBuf;
                    do {
                        *ptr2 -= (unsigned short)section->m_vertStartCount;
                        idxCount = idxCount;  // reload from stack
                        ++rebaseIdx;
                        ++ptr2;
                    } while (rebaseIdx < 3 * idxCount);
                }

                // Create index bubble
                gbVertPoolMgr* poolMgr = *(gbVertPoolMgr**)((char*)m_pGfxManager + 196);
                gbIndexBubble* idxBubble = poolMgr->NewIndexBubble(GB_PRIM_POINTLIST, 3 * idxCount);
                section->m_pIndexBubble = idxBubble;

                // Lock, copy, unlock
                unsigned int* locked = idxBubble->Lock32();
                memcpy(locked, idxBuf, idxDataSize);
                ((gbIndexBubble*)section->m_pIndexBubble)->Unlock();

                // Set range on index bubble
                gbIndexBubble* ib = (gbIndexBubble*)section->m_pIndexBubble;
                ib->field_1C = section->m_vertStartCount;
                ib->field_20 = section->m_faceStartCount;

                free(idxBuf);
                curFile = (gbVFile*)file;
            } else {
                section->m_pIndexBubble = NULL;
                section->m_faceStartCount = 0;
                section->m_vertStartCount = 0;
            }

            // Read LOD data if quality is sufficient
            if (quality >= 0.5f) {
                int* pNumKeys = &lodKey->numKeys;
                g_pVFileSys->Read(pNumKeys, 4u, curFile);

                if (*pNumKeys) {
                    lodKey->pKeyData = malloc(72 * *pNumKeys);

                    // Read key times
                    int keyIdx = 0;
                    if (*pNumKeys > 0) {
                        int keyOffset = 0;
                        do {
                            g_pVFileSys->Read((void*)((char*)lodKey->pKeyData + keyOffset + 68), 4u, (gbVFile*)file);
                            ++keyIdx;
                            keyOffset += 72;
                            // Normalize key time
                            *(float*)((char*)lodKey->pKeyData + keyOffset - 4) =
                                *(float*)((char*)lodKey->pKeyData + keyOffset - 4) -
                                *(float*)((char*)lodKey->pKeyData + 68);
                        } while (keyIdx < lodKey->numKeys);
                    }

                    // Read key material data
                    int keyIdx2 = 0;
                    if (lodKey->numKeys > 0) {
                        int keyOfs2 = 0;
                        do {
                            unsigned char matColorData[20];
                            g_pVFileSys->Read(matColorData, 0x14u, (gbVFile*)file);

                            float* keyMat = (float*)((char*)lodKey->pKeyData + keyOfs2);

                            if (gbColorQuad::ColorQuadFmt) {
                                keyMat[4] = (double)matColorData[4] * 0.0039215689;
                                keyMat[5] = (double)matColorData[5] * 0.0039215689;
                                keyMat[6] = (double)matColorData[6] * 0.0039215689;
                            } else {
                                keyMat[4] = (double)matColorData[6] * 0.0039215689;
                                keyMat[5] = (double)matColorData[5] * 0.0039215689;
                                keyMat[6] = (double)matColorData[4] * 0.0039215689;
                            }
                            keyMat[7] = (double)matColorData[7] * 0.0039215689;

                            if (gbColorQuad::ColorQuadFmt) {
                                keyMat[0] = (double)matColorData[0] * 0.0039215689;
                                keyMat[1] = (double)matColorData[1] * 0.0039215689;
                                keyMat[2] = (double)matColorData[2] * 0.0039215689;
                            } else {
                                keyMat[0] = (double)matColorData[2] * 0.0039215689;
                                keyMat[1] = (double)matColorData[1] * 0.0039215689;
                                keyMat[2] = (double)matColorData[0] * 0.0039215689;
                            }
                            keyMat[3] = (double)matColorData[3] * 0.0039215689;

                            if (gbColorQuad::ColorQuadFmt) {
                                keyMat[12] = (double)matColorData[12] * 0.0039215689;
                                keyMat[13] = (double)matColorData[13] * 0.0039215689;
                                keyMat[14] = (double)matColorData[14] * 0.0039215689;
                            } else {
                                keyMat[12] = (double)matColorData[14] * 0.0039215689;
                                keyMat[13] = (double)matColorData[13] * 0.0039215689;
                                keyMat[14] = (double)matColorData[12] * 0.0039215689;
                            }
                            keyMat[15] = (double)matColorData[15] * 0.0039215689;

                            if (gbColorQuad::ColorQuadFmt) {
                                keyMat[8] = (double)matColorData[8] * 0.0039215689;
                                keyMat[9] = (double)matColorData[9] * 0.0039215689;
                                keyMat[10] = (double)matColorData[10] * 0.0039215689;
                            } else {
                                keyMat[8] = (double)matColorData[10] * 0.0039215689;
                                keyMat[9] = (double)matColorData[9] * 0.0039215689;
                                keyMat[10] = (double)matColorData[8] * 0.0039215689;
                            }
                            keyMat[11] = (double)matColorData[11] * 0.0039215689;

                            float shin = *(float*)&matColorData[16];
                            keyMat[16] = shin;
                            if (shin < 0.0f) {
                                keyMat[16] = 0.0f;
                            } else if (shin > 128.0f) {
                                keyMat[16] = 128.0f;
                            }

                            ++keyIdx2;
                            keyOfs2 += 72;
                        } while (keyIdx2 < lodKey->numKeys);
                    }
                } else {
                    lodKey->pKeyData = NULL;
                }
            }

            // Set bound center from vertex data at min-index vertex
            float* boundVert = (float*)((char*)tempBuf + 32 * section->m_vertStartCount);
            section->m_boundCenter.x = boundVert[5];
            section->m_boundCenter.y = boundVert[6];
            section->m_boundCenter.z = boundVert[7];

            ++sectionIdx;
            sectionOffset += 188;
        } while (sectionIdx < m_numSections);
    }

    free(tempBuf);
    m_isLoaded = 1;
    return 1;
}


/* ======== Skin Mesh Internal Functions ======== */

// 0x100063E0 - Build canonical vertex (52 bytes) from skin vertex + face data
static int BuildCanonicalVertex(int a1, int a2, int a3, int a4)
{
    double v6;
    double v7;
    double v8;
    float v9;

    *(int *)a1 = *(int *)a2;
    *(int *)(a1 + 4) = *(int *)(a2 + 4);
    *(int *)(a1 + 8) = *(int *)(a2 + 8);
    v6 = (double)(2 * (char)(*(unsigned short *)(a3 + 2 * a4 + 12) >> 8)) * 3.1415927 * 0.0039215689;
    v7 = (double)(unsigned char)*(unsigned short *)(a3 + 2 * a4 + 12) * 0.012319972;
    v9 = (float)v7;
    v8 = sin(v7);
    *(float *)(a1 + 12) = (float)(cos(v6) * v8);
    *(float *)(a1 + 16) = (float)(sin(v6) * v8);
    *(float *)(a1 + 20) = (float)cos((double)v9);
    *(float *)(a1 + 24) = (float)((double)*(unsigned char *)(a2 + 20) * 0.0039215689);
    *(float *)(a1 + 28) = (float)((double)*(unsigned char *)(a2 + 21) * 0.0039215689);
    *(float *)(a1 + 32) = (float)((double)*(unsigned char *)(a2 + 22) * 0.0039215689);
    *(float *)(a1 + 36) = (float)((double)*(unsigned char *)(a2 + 23) * 0.0039215689);
    *(char *)(a1 + 40) = *(char *)(a2 + 12);
    *(char *)(a1 + 41) = *(char *)(a2 + 13);
    *(char *)(a1 + 42) = *(char *)(a2 + 14);
    *(char *)(a1 + 43) = *(char *)(a2 + 15);
    *(int *)(a1 + 44) = *(int *)(a3 + 8 * a4 + 20);
    *(int *)(a1 + 48) = *(int *)(a3 + 8 * a4 + 44);
    return a1;
}

// 0x100068F0 - Build canonical vertex for index strip (56 bytes)
static int BuildCanonicalVertexStrip(int a1, int a2)
{
    *(int *)a1 = *(int *)a2;
    *(int *)(a1 + 4) = *(int *)(a2 + 4);
    *(int *)(a1 + 8) = *(int *)(a2 + 8);
    *(float *)(a1 + 24) = (float)((double)*(unsigned char *)(a2 + 20) * 0.0039215689);
    *(float *)(a1 + 28) = (float)((double)*(unsigned char *)(a2 + 21) * 0.0039215689);
    *(float *)(a1 + 32) = (float)((double)*(unsigned char *)(a2 + 22) * 0.0039215689);
    *(float *)(a1 + 36) = (float)((double)*(unsigned char *)(a2 + 23) * 0.0039215689);
    *(float *)(a1 + 40) = (float)*(unsigned char *)(a2 + 12);
    *(float *)(a1 + 44) = (float)*(unsigned char *)(a2 + 13);
    *(float *)(a1 + 48) = (float)*(unsigned char *)(a2 + 14);
    *(float *)(a1 + 52) = (float)*(unsigned char *)(a2 + 15);
    return a2;
}

// 0x100064E0 - BuildBuffers (1028B)
// Builds deduplicated vertex/index buffers for a skin mesh section
// pThis = skin mesh data struct (44 bytes), a2 = pointer to 1180-byte section
static void BuildBuffers(unsigned int* pThis, int a2)
{
    int v2;
    gbVertPoolMgr *v3;
    gbIndexBubble *v4;
    int v5;
    int v6;
    int v7;
    int v8;
    unsigned int *v9;
    int v10;
    int v11;
    int v12;
    int v13;
    int v14;
    unsigned int *v15;
    unsigned char *v16;
    int v17;
    int v18;
    int v19;
    unsigned int *v20;
    float *v21;
    int v22;
    gbVertexBubble *v23;
    int v24;
    char *v25;
    int v26;
    unsigned int *v27;
    unsigned int *Block;
    int v29;
    char *v30;
    unsigned int *v32;
    int *v33;
    int v34;
    char v35[52];
    int v36;
    int v37;
    unsigned int v38[7];

    v2 = a2;
    v3 = (gbVertPoolMgr *)*(unsigned int *)((char *)g_pActorGfxMgr + 196);
    v4 = v3->NewIndexBubble((gbPrimType)1, 3 * *(int *)(a2 + 1160));
    *(int *)(a2 + 1164) = (int)v4;
    v32 = v4->Lock32();
    v5 = 3 * *(int *)(a2 + 1160);
    v6 = (int)operator new(156 * *(int *)(a2 + 1160));
    v7 = 0;
    if (v6)
    {
        v8 = v5 - 1;
        if (v8 >= 0)
        {
            v9 = (unsigned int *)(v6 + 20);
            v10 = v8 + 1;
            do
            {
                *(v9 - 5) = 0;
                *(v9 - 4) = 0;
                *(v9 - 3) = 0;
                *(v9 - 2) = 0;
                *(v9 - 1) = 0;
                *v9 = 0;
                v9 += 13;
                --v10;
            }
            while (v10);
        }
        v25 = (char *)v6;
    }
    else
    {
        v25 = 0;
    }
    v11 = (int)operator new(12 * *(int *)(a2 + 1160));
    v12 = *(int *)(a2 + 1160);
    Block = (unsigned int *)v11;
    memset(v35, 0, 24);
    v36 = 0;
    v37 = 0;
    v38[0] = 0;
    v29 = 0;
    if (v12 > 0)
    {
        v26 = 0;
        while (1)
        {
            v13 = 17 * *(int *)(*(int *)(v2 + 1156) + 4 * v29);
            v14 = 0;
            v34 = (int)(pThis[7] + 4 * v13);
            v24 = 0;
            v33 = (int *)&Block[v7];
            v27 = (unsigned int *)v34;
            v30 = &v25[52 * v7];
            do
            {
                v15 = (unsigned int *)(pThis[6] + 36 * *v27);
                v36 = (int)*v15;
                v37 = (int)v15[1];
                v38[0] = v15[2];
                v38[5] = v15[7];
                if ((int)v15[7] > 0)
                {
                    v16 = (unsigned char *)(v15 + 3);
                    do
                    {
                        v16[(char *)v38 - (char *)v15] = v16[8];
                        v17 = *v16++;
                        v16[(char *)&v36 - (char *)v15 - 1] = *(unsigned char *)(a2 + 4 * v17 + 128);
                    }
                    while ((int)(v16 - (unsigned char *)v15 - 12) < (int)v15[7]);
                    v14 = v24;
                }
                BuildCanonicalVertex((int)v35, (int)&v36, v34, v14);
                v18 = (int)gbCrc32Compute(v35, 52);
                v19 = 0;
                if (v7 <= 0)
                    goto LABEL_35;
                v20 = Block;
                v21 = (float *)(v25 + 20);
                while ((unsigned int)v18 != *v20
                     || *(v21 - 5) != *(float *)v35
                     || *(v21 - 4) != *(float *)&v35[4]
                     || *(v21 - 3) != *(float *)&v35[8]
                     || *(v21 - 2) != *(float *)&v35[12]
                     || *(v21 - 1) != *(float *)&v35[16]
                     || *v21 != *(float *)&v35[20]
                     || v21[6] != *(float *)&v35[44]
                     || v21[7] != *(float *)&v35[48]
                     || v21[1] != *(float *)&v35[24]
                     || v21[2] != *(float *)&v35[28]
                     || v21[3] != *(float *)&v35[32]
                     || v21[4] != *(float *)&v35[36]
                     || *((unsigned int *)v21 + 5) != *(unsigned int *)&v35[40])
                {
                    ++v19;
                    ++v20;
                    v21 += 13;
                    if (v19 >= v7)
                        goto LABEL_35;
                }
                if (v19 >= v7)
                {
LABEL_35:
                    memcpy(v30, v35, 0x34u);
                    *v33 = v18;
                    *((unsigned short *)v32 + v14 + v26) = (unsigned short)v7++;
                    v30 += 52;
                    ++v33;
                }
                else
                {
                    *((unsigned short *)v32 + v14 + v26) = (unsigned short)v19;
                }
                v24 = ++v14;
                ++v27;
            }
            while (v14 < 3);
            v26 += 3;
            if (++v29 >= *(int *)(a2 + 1160))
                break;
            v2 = a2;
        }
        v2 = a2;
    }
    ((gbIndexBubble *)*(int *)(v2 + 1164))->Unlock();
    v22 = *(int *)(v2 + 1164);
    *(int *)(v22 + 32) = v7 - 1;
    *(int *)(v22 + 28) = 0;
    v23 = v3->NewVertexBubble(0x80000034, v7);
    *(int *)(v2 + 1168) = (int)v23;
    memcpy(v23->Lock(), v25, 4 * ((unsigned int)(52 * v7) >> 2));
    ((gbVertexBubble *)*(int *)(v2 + 1168))->Unlock();
    operator delete(Block);
    operator delete(v25);
}

// 0x100069B0 - BuildIndexStrip (970B)
// Builds vertex/index strip data for a skin mesh section
// pThis = skin mesh data struct (44 bytes), a2 = pointer to 1180-byte section
static void BuildIndexStrip(unsigned int* pThis, unsigned int* a2)
{
    unsigned short *v2;
    int v3;
    unsigned short *v4;
    int i;
    int v6;
    float *v7;
    int v8;
    float *v9;
    int v10;
    int v11;
    unsigned int *v12;
    unsigned int *v13;
    unsigned char *v14;
    int v15;
    int v16;
    float *v17;
    int v19;
    int v20;
    int v22;
    unsigned short *Block;
    float *v24;
    char *v25;
    unsigned int *v26;
    int v27;
    int v28;
    float v29[14];
    int v30;
    int v31;
    unsigned int v32[7];
    unsigned int v33[15];

    if (!a2[293])
    {
        v2 = (unsigned short *)malloc(6 * a2[290]);
        v3 = 0;
        Block = v2;
        if ((int)a2[290] > 0)
        {
            v4 = v2;
            do
            {
                for (i = 0; i < 3; ++i)
                {
                    ++v4;
                    v6 = 16 * *(int *)(a2[289] + 4 * v3) + i + *(int *)(a2[289] + 4 * v3);
                    *(v4 - 1) = *(unsigned short *)(pThis[7] + 4 * v6);
                }
                ++v3;
            }
            while (v3 < (int)a2[290]);
        }
        v7 = (float *)malloc(56 * (int)pThis[2]);
        v8 = (int)a2[290];
        v9 = v7;
        v10 = 0;
        v11 = 0;
        v24 = v9;
        memset(v29, 0, 24);
        v30 = 0;
        v31 = 0;
        v32[0] = 0;
        v28 = 0;
        v27 = 0;
        if (v8 > 0)
        {
            v22 = 0;
            do
            {
                v20 = 0;
                v12 = (unsigned int *)(pThis[7] + 68 * *(int *)(a2[289] + 4 * v10));
                v26 = v12;
                v25 = (char *)&v9[14 * v11];
                do
                {
                    v13 = (unsigned int *)(pThis[6] + 36 * *v12);
                    v30 = (int)*v13;
                    v31 = (int)v13[1];
                    v32[0] = v13[2];
                    v32[5] = v13[7];
                    if ((int)v13[7] > 0)
                    {
                        v14 = (unsigned char *)(v13 + 3);
                        do
                        {
                            v14[(char *)v32 - (char *)v13] = v14[8];
                            v15 = *v14++;
                            v14[(char *)&v30 - (char *)v13 - 1] = (unsigned char)a2[v15 + 32];
                        }
                        while ((int)(v14 - (unsigned char *)v13 - 12) < (int)v13[7]);
                        v11 = v28;
                    }
                    BuildCanonicalVertexStrip((int)v29, (int)&v30);
                    v16 = 0;
                    if (v11 <= 0)
                        goto LABEL_31;
                    v17 = v24 + 8;
                    while (*(v17 - 8) != v29[0]
                         || *(v17 - 7) != v29[1]
                         || *(v17 - 6) != v29[2]
                         || *(v17 - 2) != v29[6]
                         || *(v17 - 1) != v29[7]
                         || *v17 != v29[8]
                         || v17[1] != v29[9]
                         || v17[2] != v29[10]
                         || v17[3] != v29[11]
                         || v17[4] != v29[12]
                         || v17[5] != v29[13])
                    {
                        ++v16;
                        v17 += 14;
                        if (v16 >= v11)
                            goto LABEL_31;
                    }
                    if (v16 >= v11)
                    {
LABEL_31:
                        memcpy(v25, v29, 0x38u);
                        Block[v20 + v22] = (unsigned short)v11++;
                        v28 = v11;
                        v25 += 56;
                    }
                    else
                    {
                        Block[v20 + v22] = (unsigned short)v16;
                    }
                    v12 = v26 + 1;
                    ++v20;
                    ++v26;
                }
                while (v20 < 3);
                v9 = v24;
                v10 = v27 + 1;
                ++v27;
                v22 += 3;
            }
            while (v27 < (int)a2[290]);
        }
        v19 = (int)a2[290];
        memset(&v33[3], 255, 20);
        v33[1] = 0;
        v33[13] = 0;
        v33[11] = 0;
        v33[12] = (unsigned int)v19;
        v33[9] = (unsigned int)v11;
        v33[0] = (unsigned int)v9;
        v33[10] = (unsigned int)Block;
        v33[2] = 12;
        v33[8] = 56;
        v33[14] = 1008981770;
        BuildShadowVolumeDataInternal(v33, (int)g_pActorGfxMgr, 0x80000038, (void *)(a2 + 294), (void *)(a2 + 293));
        free(Block);
        free(v9);
    }
}

// 0x10006090 - LoadFromStream (754B)
// Loads skin mesh data from a gbVFile stream
// pThis = skin mesh data struct (44 bytes), a2 = gbVFile*
static int LoadSkinMeshFromStream(unsigned int* pThis, gbVFile* a2)
{
    int v4;
    int v5;
    int v6;
    int v7;
    unsigned int *v8;
    int v9;
    int v10;
    int v11;
    int v12;
    int i2;
    void *v14;
    int v15;
    int v16;
    float *v17;
    float *v18;
    int v21;
    void *v22;
    int result;
    int v25;
    int v26;
    int Buffera;
    int v28;
    int v29;
    int v30_counter;
    int v31_counter;

    g_pVFileSys->Read(pThis, 4u, a2);
    g_pVFileSys->Read((char*)pThis + 8, 4u, a2);
    g_pVFileSys->Read((char*)pThis + 12, 4u, a2);
    g_pVFileSys->Read((char*)pThis + 16, 4u, a2);
    g_pVFileSys->Read((char*)pThis + 20, 4u, a2);
    g_pVFileSys->Read((char*)pThis + 4, 4u, a2);
    v4 = (int)pThis[2];
    v5 = (int)operator new(36 * v4);
    v6 = 0;
    if (v5)
    {
        v7 = v4 - 1;
        if (v7 >= 0)
        {
            v8 = (unsigned int *)(v5 + 8);
            v9 = v7 + 1;
            do
            {
                *(v8 - 2) = 0;
                *(v8 - 1) = 0;
                *v8 = 0;
                v8 += 9;
                --v9;
            }
            while (v9);
        }
    }
    else
    {
        v5 = 0;
    }
    pThis[6] = (unsigned int)v5;
    if ((*((char*)pThis + 4) & 1) != 0)
    {
        v10 = 0;
        if ((int)pThis[2] > 0)
        {
            do
            {
                g_pVFileSys->Read((void *)(v6 + pThis[6]), 0xCu, a2);
                ++v10;
                v6 += 36;
            }
            while (v10 < (int)pThis[2]);
            v6 = 0;
        }
    }
    if ((pThis[1] & 0x800) != 0)
    {
        v30_counter = 0;
        if ((int)pThis[2] > 0)
        {
            v11 = 0;
            do
            {
                g_pVFileSys->Read(&Buffera, 1u, a2);
                v12 = 0;
                *(unsigned int *)(pThis[6] + v11 + 28) = (unsigned char)Buffera;
                if ((unsigned char)Buffera)
                {
                    do
                    {
                        g_pVFileSys->Read((void *)(v11 + pThis[6] + v12 + 12), 1u, a2);
                        g_pVFileSys->Read((void *)(v11 + pThis[6] + v12 + 20), 1u, a2);
                        ++v12;
                    }
                    while (v12 < (unsigned char)Buffera);
                }
                v11 += 36;
                ++v30_counter;
            }
            while (v30_counter < (int)pThis[2]);
            v6 = 0;
        }
    }
    if ((pThis[1] & 0x1000) != 0)
    {
        for (i2 = 0; i2 < (int)pThis[2]; v6 += 36)
        {
            g_pVFileSys->Read((void *)(pThis[6] + v6 + 32), 4u, a2);
            ++i2;
        }
    }
    v14 = (void *)operator new(68 * pThis[3]);
    v15 = (int)pThis[3];
    pThis[7] = (unsigned int)v14;
    g_pVFileSys->Read(v14, 68 * v15, a2);
    v31_counter = 0;
    if ((int)pThis[3] > 0)
    {
        Buffera = 0;
        do
        {
            v16 = Buffera;
            v28 = 3;
            do
            {
                v17 = (float *)(pThis[7] + v16 + 20);
                v29 = (int)(__int64)(*v17 * 255.0);
                *v17 = (float)((double)v29 * 0.0039215689);
                v18 = (float *)(pThis[7] + v16 + 44);
                v29 = (int)(__int64)(*v18 * 255.0);
                v16 += 8;
                --v28;
                *v18 = (float)((double)v29 * 0.0039215689);
            }
            while (v28);
            ++v31_counter;
            Buffera += 68;
        }
        while (v31_counter < (int)pThis[3]);
    }
    v21 = (int)pThis[4];
    if (v21)
    {
        v22 = (void *)operator new(16 * v21);
        pThis[8] = (unsigned int)v22;
        g_pVFileSys->Read(v22, 16 * pThis[4], a2);
    }
    SortBoneWeights((int*)pThis, 4);
    PartitionMesh(pThis, 26);
    result = (int)pThis[10];
    v25 = 0;
    if (result > 0)
    {
        v26 = 0;
        do
        {
            BuildBuffers(pThis, (int)(pThis[9] + v26));
            result = (int)pThis[10];
            ++v25;
            v26 += 1180;
        }
        while (v25 < result);
    }
    return result;
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
