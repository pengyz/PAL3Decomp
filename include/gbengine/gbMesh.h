#pragma once

#include "gbengine/gbengine_types.h"
#include "gbengine/gbChain.h"
#include <d3d9.h>

// Forward declarations
class gbEffectMgr;
class gbGfxManager;
class gbRenderEffect;
class gbTexture;
struct gbTextureArray;
class gbVFile;
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
    int startIndex;                 // +0x10
    int count;                      // +0x14
    int bUsed;                      // +0x18
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
    int vertexCount;                // +0x10
    int countUsed;                  // +0x14
    int bUsed;                      // +0x18
    void* pVertexData;              // +0x1C
    void* field_20;
    void* field_24;
    void* field_28;
    void* field_2C;
    void* field_30;
    void* field_34;

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

class gbIndexPool : public gbChain1DNode {
public:
    gbPoolType poolType;            // +0x08
    int indexSize;                  // +0x0C
    int currentSize;                // +0x10
    int totalSize;                  // +0x14
    gbChain1D freeList;             // +0x18
    gbChain1D usedList;             // +0x28
    gbChain1DNode* pIterator;       // +0x38
    IDirect3DDevice9* pDevice;
    IDirect3DIndexBuffer9* pIndexBuffer;

    gbIndexPool(gbPoolType type, int indexSz, int total);
    gbIndexPool(const gbIndexPool& other);
    virtual ~gbIndexPool();

    gbIndexBubble* NewBubble(gbPrimType prim, int count);
    void DelBubble(gbIndexBubble* bubble);
    int GetIndexSize();
    void* GetInternalMemBuf();
    int IsEmpty();
    gbIndexPool& operator=(const gbIndexPool& other);
};


/* ======== gbVertexPool ======== */

class gbVertexPool : public gbChain1DNode {
public:
    gbPoolType poolType;            // +0x08
    int currentSize;                // +0x0C
    int totalSize;                  // +0x10
    unsigned int fvf;               // +0x14
    int stride;                     // +0x18
    gbChain1D freeList;             // +0x1C
    gbChain1D usedList;             // +0x2C
    gbChain1DNode* pIterator;
    IDirect3DDevice9* pDevice;
    IDirect3DVertexBuffer9* pVertexBuffer;

    static gbGfxManager* pGfxMgr;

    gbVertexPool(gbPoolType type, unsigned int vertType, int total);
    gbVertexPool(const gbVertexPool& other);
    virtual ~gbVertexPool();

    virtual void* Lock(int start, int count);
    virtual int OnLostDevice();
    virtual int OnResetDevice();

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
    gbVertexPool* vertexPools[32];      // +0x000 to +0x280
    gbChain1D indexPoolList;             // +0x280
    gbChain1DNode* pIndexIterator;       // +0x28C
    gbVertexPool* srcVertPools[32];      // +0x290 to +0x390
    gbChain1D dynVertBufList;            // +0x390
    gbDynVertBuf* dynVertBufs[32];       // +0x3A0 to +0x590
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

// Forward declaration (full definition in gbSceneGraph.h)
struct gbRenderInfoObj;

// Geometry node description
struct GeomNodeDesc {
    char name[64];
    int flags;
};

// Mesh section (submesh) - sizeof = 0xBC (deduced from iteration stride)
// Known field offsets: +0x08=textureArray, +0x48=numTextures, +0x90=indexBubble
// m_faceCount position unknown (used via direct member access in GetNumFaces)
class gbMeshSection {
public:
    gbMeshSection();

    void* _field00;                 // +0x00
    void* _field04;                 // +0x04
    gbTexture** m_pTextureArray;    // +0x08: array of texture pointers
    int m_vertexStart;              // +0x0C
    int m_vertexCount;              // +0x10
    int m_faceStart;                // +0x14
    int m_faceCount;                // +0x18
    int m_materialIndex;            // +0x1C
    char _pad20[0x28];              // +0x20..+0x47
    int m_numTextures;              // +0x48: number of active textures
    char _pad4C[0x44];              // +0x4C..+0x8F
    void* m_pIndexBubble;           // +0x90: gbIndexBubble*
    char _pad94[0x28];              // +0x94..+0xBB
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
public:
    gbBaseMesh(gbGfxManager* gfxMgr);
    gbBaseMesh(const gbBaseMesh& other);
    virtual ~gbBaseMesh();

    gbBaseMesh& operator=(const gbBaseMesh& other);

    // Virtual methods
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
    int m_refCount;                 // +0x04
    void* m_reserved1;              // +0x08
    void* m_reserved2;              // +0x0C
    void* m_reserved3;              // +0x10
    void* m_reserved4;              // +0x14
    void* m_vertexBuffer;           // +0x18
    void* m_reserved5[15];          // +0x1C-0x57
    void* m_indexBuffer;            // +0x58
    void* m_reserved6[3];           // +0x5C-0x67
    gbAABBox m_aabb;                // +0x68 (24 bytes)
    gbGfxManager* m_pGfxManager;    // +0x74
    char m_objectName[16];          // +0x80
    gbMeshSection* m_sections;      // +0x90
    int m_numSections;              // +0x94
    gbMeshType m_meshType;          // +0x98
    float m_currentTime;            // +0x9C
    gbMeshMemCache m_memCache;      // +0xA0

    // Static members
    static int Effect_RefCount;
    static gbRenderEffect** pShadowEffect;
    static char* TextureDir;
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

class gbDynVertBuf : public gbChain1DNode {
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

    void* m_vertexBuffer;       // +0x08
    unsigned int m_fvfFlags;    // +0x0C
    int m_maxVertices;          // +0x10
    int m_currentVertex;        // +0x14
    int m_vertexStride;         // +0x18
    float* m_pXYZ;              // +0x1C
    float* m_pNormal;           // +0x20
    gbColorQuad* m_pColor1;     // +0x24
    gbColorQuad* m_pColor2;     // +0x28
    float* m_pUV[4];            // +0x2C..+0x38 (UV sets 0-3)
    int m_vertNum;              // +0x3C
};
