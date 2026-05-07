#pragma once

#include "gbengine/gbengine_types.h"
#include "gbengine/gbChain.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"

// Forward declarations (circular dep or defined later in this file)
class gbGfxManager;
class gbRenderEffect;
class gbVisNode;
class gbDynVertBuf;
class gbIndexPool;
class gbVertexPool;


/* ======== Enums ======== */

enum gbPrimType {
    GB_PRIM_POINTLIST = 1,
    GB_PRIM_LINELIST = 2,
    GB_PRIM_LINESTRIP = 3,
    GB_PRIM_TRIANGLELIST = 4,
    GB_PRIM_TRIANGLESTRIP = 5,
    GB_PRIM_TRIANGLEFAN = 6
};

enum gbPoolType {
    GB_POOL_DEFAULT = 0,
    GB_POOL_MANAGED = 1,
    GB_POOL_SYSTEMMEM = 2,
    GB_POOL_SCRATCH = 3
};

enum gbMeshType {
    MESH_STATIC = 0,
    MESH_SKINNED = 1,
    MESH_PROGRESSIVE = 2
};


/* ======== gbIndexBubble ======== */

class gbIndexBubble : public gbChain1DNode {
public:
    class gbIndexPool* pPool;      // +0x08
    gbPrimType primType;            // +0x0C
    int count;                      // +0x10
    int bUsed;                      // +0x14
    int startIndex;                 // +0x18
    int field_1C;                   // +0x1C
    int field_20;                   // +0x20

    gbIndexBubble(gbIndexPool* pool, gbPrimType prim, int start, int cnt, int used);
    gbIndexBubble(const gbIndexBubble& other);
    virtual ~gbIndexBubble();

    void Set(int start, int cnt, int used);
    void SetRange(int start, int cnt);
    unsigned short* Lock16();
    unsigned int* Lock32();
    void Unlock();
    gbIndexBubble& operator=(const gbIndexBubble& other);
};


/* ======== gbVertexBubble ======== */

class gbVertexBubble : public gbChain1DNode {
public:
    class gbVertexPool* pPool;      // +0x08
    int startVertex;                // +0x0C
    int countUsed;                  // +0x10
    int vertexCount;                // +0x14
    void* pVertexData;              // +0x18
    void* field_1C;                 // +0x1C
    void* field_20;                 // +0x20
    void* field_24;                 // +0x24
    void* field_28;                 // +0x28
    void* field_2C;                 // +0x2C
    void* field_30;                 // +0x30
    void* field_34;                 // +0x34

    gbVertexBubble(gbVertexPool* pool, int start, int count, int used);
    gbVertexBubble(const gbVertexBubble& other);
    virtual ~gbVertexBubble();

    void Set(int start, int count, int used);
    void* Lock();
    void Unlock();
    void ClearPointer();
    void StepVertexPtr();
    gbVertexBubble& operator=(const gbVertexBubble& other);
};


/* ======== gbIndexPool ======== */
// sizeof(base) = 0x38 (verified from new(0x38) in slot 5 factory)
// D3D subclass adds no extra fields (buffer stored at +0x10)

class gbIndexPool : public gbChain1DNode {
public:
    gbPoolType poolType;            // +0x08
    int indexSize;                  // +0x0C: bytes per index (2 or 4)
    void* pBuffer;                  // +0x10: index buffer (IDirect3DIndexBuffer9* or malloc'd)
    int totalSize;                  // +0x14: total index count
    gbChain1D freeList;             // +0x18 (16 bytes)
    gbChain1D usedList;             // +0x28 (16 bytes)
    // total = 0x38

    static gbGfxManager* pGfxMgr;

    gbIndexPool(gbPoolType type, int indexSz, int total);
    gbIndexPool(const gbIndexPool& other);
    virtual ~gbIndexPool();
    virtual void Lock();
    virtual void Unlock();

    gbIndexBubble* NewBubble(gbPrimType prim, int count);
    void DelBubble(gbIndexBubble* bubble);
    int GetIndexSize();
    void* GetInternalMemBuf();
    int IsEmpty();
    gbIndexPool& operator=(const gbIndexPool& other);
};


/* ======== gbVertexPool ======== */
// sizeof(base) = 0x3C (verified from new(0x3C) in slot 4 factory)
// D3D subclass adds no extra fields (buffer stored at +0x0C)

class gbVertexPool : public gbChain1DNode {
public:
    gbPoolType poolType;            // +0x08
    void* pBuffer;                  // +0x0C: vertex buffer (IDirect3DVertexBuffer9* or malloc'd)
    int totalSize;                  // +0x10: total vertex count
    unsigned int fvf;               // +0x14: custom FVF flags
    int stride;                     // +0x18: bytes per vertex (computed from fvf)
    gbChain1D freeList;             // +0x1C (16 bytes)
    gbChain1D usedList;             // +0x2C (16 bytes)
    // total = 0x3C

    static gbGfxManager* pGfxMgr;

    gbVertexPool(gbPoolType type, unsigned int vertType, int total);
    gbVertexPool(const gbVertexPool& other);
    virtual ~gbVertexPool();

    virtual int OnLostDevice();
    virtual int OnResetDevice();
    virtual void DrawIndexedPrimitive(gbVertexBubble* vb, void* ib, int param3, gbTexture** textures);

    void* Lock(int start, int count);

    gbVertexBubble* NewBubble(int count);
    void DelBubble(gbVertexBubble* bubble);
    int GetStride();
    unsigned int GetVertType();
    int IsEmpty();
    gbVertexPool& operator=(const gbVertexPool& other);
};


/* ======== gbVertPoolMgr ======== */

class gbVertPoolMgr {
public:
    gbChain1D vertPoolChains[32];        // +0x000 (32*16=512 bytes, ends at +0x200)
    gbVertexPool* vertexPools[32];       // +0x200 (32*4=128 bytes, ends at +0x280)
    gbChain1D indexPoolList;             // +0x280 (16 bytes, ends at +0x290)
    gbVertexPool* srcVertPools[32];      // +0x290 (32*4=128 bytes, ends at +0x310)
    void* field_310[32];                 // +0x310 (32*4=128 bytes, ends at +0x390)
    gbChain1D dynVertBufChains[32];      // +0x390 (32*16=512 bytes, ends at +0x590)
    gbDynVertBuf* dynVertBufs[32];       // +0x590 (32*4=128 bytes, ends at +0x610)
    int maxVertexPoolSize;               // +0x610
    int maxIndexPoolSize;                // +0x614
    int field_618;                       // +0x618
    int field_61C;                       // +0x61C
    gbGfxManager* pGfxManager;           // +0x620

    gbVertPoolMgr(gbGfxManager* mgr, int p2, int p3, int p4, int p5);
    ~gbVertPoolMgr();

    int OnLostDevice();
    int OnResetDevice();
    gbVertexBubble* NewVertexBubble(unsigned int fvf, int count);
    void DelVertexBubble(gbVertexBubble* bubble);
    gbVertexBubble* NewSrcVertBub(unsigned int fvf, int count);
    void DelSrcVertBub(gbVertexBubble* bubble);
    gbIndexBubble* NewIndexBubble(gbPrimType prim, int count);
    void DelIndexBubble(gbIndexBubble* bubble);
    gbDynVertBuf* GetDynVertBuf(unsigned int fvf);
    gbVertPoolMgr& operator=(const gbVertPoolMgr& other);

private:
    int FindVertexPoolIndex(unsigned int* fvf, unsigned int type);
};


/* ======== Mesh types ======== */

struct gbRenderInfoObj;

// Geometry node description (sizeof = 52, verified from LoadFromFile: "52 * numMeshes" read)
struct GeomNodeDesc {
    char name[48];
    int flags;
};

// Mesh section (submesh) - sizeof = 0xBC = 188 bytes (47 DWORDs)
// Layout verified via IDA: LoadFromStream, AttachSelf, DrawSubSet, ~gbBaseMesh
class gbMeshSection {
public:
    gbMeshSection();

    int m_blendMode;                // +0x00 [0]: 0=opaque, 1=alpha, 2=additive, 3=other
    int m_hasMultiTex;              // +0x04 [1]: 1 if numTextures==2
    gbTexture* m_textures[16];      // +0x08 [2..17]: inline texture pointer array
    int m_numTextures;              // +0x48 [18]: active texture count
    char m_material[0x44];          // +0x4C [19..35]: material data (68 bytes, read from file)
    void* m_pIndexBubble;           // +0x90 [36]: gbIndexBubble*
    int m_vertStartCount;           // +0x94 [37]: vertex start/count for indexBubble
    int m_faceStartCount;           // +0x98 [38]: face start/count for indexBubble
    gbVec3D m_boundCenter;          // +0x9C [39..41]: bounding center for sorting
    void* m_overrideEffect;         // +0xA8 [42]: gbRenderEffect* override (NULL = auto)
    void* m_animTexArray;           // +0xAC [43]: animated texture pointer array
    int m_animTexSlot;              // +0xB0 [44]: which texture slot to animate
    int m_numAnimFrames;            // +0xB4 [45]: number of animation frames
    int m_animFrameInterval;        // +0xB8 [46]: frame duration in milliseconds
    // total sizeof = 0xBC
};

// Mesh memory cache
struct gbMeshMemCache {
    void* vertexData;
    void* indexData;
    int vertexSize;
    int indexSize;
};


/* ======== gbBaseMesh ======== */

class gbBaseMesh {
    friend class gbGeomNode;
    friend class gbStaticMesh;
public:
    gbBaseMesh(gbGfxManager* gfxMgr);
    gbBaseMesh(const gbBaseMesh& other);
    virtual ~gbBaseMesh();

    gbBaseMesh& operator=(const gbBaseMesh& other);

    // Reference counting
    void Release(void);

    // Virtual methods
    virtual void DrawSubSetBase(int index, void* renderInfo);
    virtual void ComputeShadowVolume();
    virtual void RenderShadowVolume(gbVisNode* visNode, gbRenderInfoObj* renderInfo);

    // Accessors (declared out-of-line for proper symbol emission)
    gbMeshSection* GetMeshSection(int index);
    int GetNumSection();
    int GetNumFaces();
    unsigned int GetFVF();
    gbMeshType GetMeshType();
    gbAABBox* GetAABBox();
    const char* GetObjectName();
    gbMeshMemCache* GetMemoryCache();

    // Animation time
    void SetCurTime(float time);

    // Texture management
    void SetTexture(int index, gbTexture* texture);
    void ReplaceTexture(const char* textureName);
    void ReplaceTexture(gbTexture* texture);

    // Static methods
    static void SetMeshTexDir(char* dir);

protected:
    // Layout verified via IDA Hex-Rays (2026-05-06)
    // gbBaseMesh inherits gbResource (vtable + refCount + name + crc + links)
    int m_refCount;                 // +0x04: reference count (init 1)
    char* m_resName;                // +0x08: resource name (malloc'd, from gbResource)
    unsigned int m_resCrc;          // +0x0C: CRC32 of name (from gbResource)
    void* m_resPrev;                // +0x10: resource list link (from gbResource)
    void* m_resNext;                // +0x14: resource list link (from gbResource)
    unsigned int m_fvf;             // +0x18: FVF flags (gbStaticMesh zeros this)
    char m_objectName[16];          // +0x1C: fixed object name (GetObjectName)
    void* m_field2C;                // +0x2C
    void* m_field30;                // +0x30
    void* m_field34;                // +0x34
    void* m_field38;                // +0x38
    int m_flags;                    // +0x3C: mesh flags (bit 2 = alpha test)
    gbMeshSection* m_sections;      // +0x40: section array (stride 0xBC)
    int m_numSections;              // +0x44: number of sections
    gbMeshMemCache m_memCache;      // +0x48: vertex/index data cache (16 bytes)
    gbAABBox m_aabb;                // +0x58: axis-aligned bounding box (24 bytes)
    float m_currentTime;            // +0x70: current animation time
    gbGfxManager* m_pGfxManager;    // +0x74: graphics manager pointer

    // Static members
    static int Effect_RefCount;
    static gbRenderEffect** pShadowEffect;
    static char TextureDir[260];
};


/* ======== gbStaticMesh ======== */

class gbStaticMesh : public gbBaseMesh {
public:
    gbStaticMesh(gbGfxManager* gfxMgr);
    gbStaticMesh(const gbStaticMesh& other);
    virtual ~gbStaticMesh();

    gbStaticMesh& operator=(const gbStaticMesh& other);

    // Virtual methods
    virtual void DrawSubSet(int index, gbRenderInfoObj* renderInfo);
    virtual void ComputeShadowVolume();
    virtual void RenderShadowVolume(gbVisNode* visNode, gbRenderInfoObj* renderInfo);

    // Loading
    int LoadFromStream(gbVFile* file, int flags, GeomNodeDesc* desc);

    // Accessors
    gbVertexBubble* GetVertBubble();

    // Static members
    static char* LightMapDir;

private:
    gbVertexBubble* m_pVertBubble;
    void* m_shadowVolumeVB;
    void* m_shadowVolumeIB;
};


/* ======== gbDynVertBuf ======== */

// UI quad structure (40 bytes / 10 floats per quad)
// [0] x1 (left), [1] y1 (top), [2] x2 (right), [3] y2 (bottom)
// [4] u1, [5] v1, [6] u2, [7] v2, [8] z (depth), [9] color (as uint)
struct gbUIQuad {
    float x1, y1, x2, y2;
    float u1, v1, u2, v2;
    float z;
    unsigned int color;
};

// Geometry quad structure (68 bytes / 17 dwords per quad)
// [0-2] v0 xyz, [3-5] v1 xyz, [6-8] v2 xyz, [9-11] v3 xyz
// [12] u1, [13] v1, [14] u2, [15] v2, [16] color
struct gbGeomQuad {
    gbVec3D verts[4];       // 4 corner positions (48 bytes)
    float u1, v1, u2, v2;   // texture coordinates (16 bytes)
    unsigned int color;      // vertex color (4 bytes)
};

class gbDynVertBuf {
public:
    gbDynVertBuf(unsigned int fvfFlags, int maxVertices);
    gbDynVertBuf(const gbDynVertBuf& other);
    virtual ~gbDynVertBuf();

    gbDynVertBuf& operator=(const gbDynVertBuf& other);

    // Virtual methods for buffer management
    virtual float* Lock(int numVerts);
    virtual void Unlock();
    virtual void Draw(int primType, gbRenderEffect* effect, gbTextureArray* textures);

    float* GetXYZ();
    float* GetNormal();
    gbColorQuad* GetColor1();
    gbColorQuad* GetColor2();
    int GetVertNum();
    int GetVertexStride();
    float* GetUV(int index);
    void StepVertexPtr();

    void RenderUIQuad(gbUIQuad* quadData, int numQuads, gbRenderEffect* effect, gbTextureArray* textures);
    void RenderGeomQuad(gbGeomQuad* quadData, int numQuads, gbRenderEffect* effect, gbTextureArray* textures);
    void RenderGeomQuadViaStrip(gbGeomQuad* quadData, int numQuads, gbRenderEffect* effect, gbTextureArray* textures);
    void RenderGeomQuadViaStrip(gbGeomQuad* quadData, int numQuads, gbRenderEffect* effect, gbTextureArray* textures, unsigned long flags);
    void RenderLineStrip(gbColorQuad color, gbVec3D* points, int numPoints, gbRenderEffect* effect);

    static gbGfxManager* pGfxMgr;
    static gbRenderEffect* pLineEffect;

    int m_field04;              // +0x04: =1 in constructor
    int m_vertNum;              // +0x08: vertex count (init to maxVertices)
    unsigned int m_fvfFlags;    // +0x0C: FVF flags
    int m_vertexStride;         // +0x10: stride computed from fvfFlags
    int m_currentVertex;        // +0x14: current write position
    void* m_vertexBuffer;       // +0x18: vertex buffer pointer
    float* m_pXYZ;              // +0x1C
    float* m_pNormal;           // +0x20
    gbColorQuad* m_pColor1;     // +0x24
    gbColorQuad* m_pColor2;     // +0x28
    float* m_pUV[4];            // +0x2C..+0x38 (UV sets 0-3)
};
