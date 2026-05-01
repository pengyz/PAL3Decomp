/**
 * gbengine.dll - gbVertPool
 * Vertex and Index buffer pool management
 */

#include "gbengine/gbengine_types.h"
#include <d3d9.h>
#include <string.h>

// Forward declarations
class gbChain1D;
class gbChain1DNode;
class gbGfxManager;
class gbDynVertBuf;

// Enums
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

// gbChain1D - simple linked list manager
class gbChain1D {
public:
    gbChain1DNode* pHead;
    gbChain1DNode* pTail;
    int count;
    gbChain1DNode* pIterator;

    gbChain1D();
    ~gbChain1D();
    void AddNode(gbChain1DNode* node);
    void DelNodeFromChain(gbChain1DNode* node);
    void InsertAfter(gbChain1DNode* node, gbChain1DNode* after);
};

// gbChain1DNode - base class for linked list nodes
class gbChain1DNode {
public:
    void** vtable;
    gbChain1DNode* pNext;

    virtual ~gbChain1DNode() {}
};

// Global statics
static gbGfxManager* g_gbVertexPool_pGfxMgr = NULL;
static gbGfxManager* g_gbDynVertBuf_pGfxMgr = NULL;

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
    void Unlock();
    gbIndexBubble& operator=(const gbIndexBubble& other);
};

// Constructor: 0x10003b50
gbIndexBubble::gbIndexBubble(gbIndexPool* pool, gbPrimType prim, int start, int cnt, int used) {
    this->vtable = NULL;
    this->pPool = pool;
    this->primType = prim;
    this->startIndex = cnt;
    this->count = start;
    this->bUsed = used;
    this->field_1C = -1;
    this->field_20 = -1;
}

// Copy constructor: 0x10003bd0
gbIndexBubble::gbIndexBubble(const gbIndexBubble& other) {
    this->vtable = NULL;
    this->pPool = other.pPool;
    this->primType = other.primType;
    this->startIndex = other.startIndex;
    this->count = other.count;
    this->bUsed = other.bUsed;
    this->field_1C = other.field_1C;
    this->field_20 = other.field_20;
}

// Destructor: 0x10003f30
gbIndexBubble::~gbIndexBubble() {
    // Virtual destructor - cleanup handled by derived classes
}

// Set: 0x10003b90
void gbIndexBubble::Set(int start, int cnt, int used) {
    this->startIndex = start;
    this->count = cnt;
    this->bUsed = used;
}

// SetRange: 0x10003bb0
void gbIndexBubble::SetRange(int start, int cnt) {
    this->startIndex = start;
    this->count = cnt;
}

// Lock16: 0x10020900
unsigned short* gbIndexBubble::Lock16() {
    // Lock the index buffer for this bubble's range
    IDirect3DIndexBuffer9* pIB = nullptr;
    // Get IB from pool (implementation depends on pool structure)
    // For now, return null - needs proper D3D9 integration
    return nullptr;
}

// Unlock: 0x10020920
void gbIndexBubble::Unlock() {
    // Unlock the index buffer
    // Implementation depends on pool structure
}

// operator=: 0x10003c20
gbIndexBubble& gbIndexBubble::operator=(const gbIndexBubble& other) {
    if (this != &other) {
        this->pPool = other.pPool;
        this->primType = other.primType;
        this->startIndex = other.startIndex;
        this->count = other.count;
        this->bUsed = other.bUsed;
        this->field_1C = other.field_1C;
        this->field_20 = other.field_20;
    }
    return *this;
}


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

// Constructor: 0x10020930
gbIndexPool::gbIndexPool(gbPoolType type, int indexSz, int total) {
    this->vtable = NULL;

    // Initialize free list
    this->freeList.pHead = nullptr;
    this->freeList.pTail = nullptr;
    this->freeList.count = 0;
    this->freeList.pIterator = nullptr;

    // Initialize used list
    this->usedList.pHead = nullptr;
    this->usedList.pTail = nullptr;
    this->usedList.count = 0;
    this->usedList.pIterator = nullptr;

    this->vtable = NULL;
    this->poolType = type;
    this->indexSize = indexSz;
    this->totalSize = total;
    this->currentSize = 0;

    // Create initial free bubble covering entire pool
    gbIndexBubble* bubble = (gbIndexBubble*)operator new(0x24);
    if (bubble) {
        bubble->vtable = NULL;
        bubble->pPool = this;
        bubble->primType = (gbPrimType)0;
        bubble->startIndex = 0;
        bubble->count = total;
        bubble->bUsed = total;
        bubble->field_1C = -1;
        bubble->field_20 = -1;
    }

    this->freeList.AddNode((gbChain1DNode*)bubble);
}

// Copy constructor: 0x10003cf0
gbIndexPool::gbIndexPool(const gbIndexPool& other) {
    // Copy construction - shallow copy for now
    memcpy(this, &other, sizeof(gbIndexPool));
}

// Destructor: 0x100209f0
gbIndexPool::~gbIndexPool() {
    // Clean up bubbles and D3D resources
    // Implementation depends on proper cleanup
}

// NewBubble: 0x10020a50
gbIndexBubble* gbIndexPool::NewBubble(gbPrimType prim, int count) {
    gbIndexBubble* bestFit = nullptr;
    int bestSize = 0x7FFFFFFF;

    // Find best-fit free bubble
    gbChain1DNode* node = this->freeList.pHead;
    this->freeList.pIterator = node;

    while (node) {
        gbIndexBubble* bubble = (gbIndexBubble*)node;
        int freeSize = bubble->bUsed - count;

        if (freeSize >= 0 && freeSize < bestSize) {
            bestSize = freeSize;
            bestFit = bubble;
        }

        node = this->freeList.pIterator->pNext;
        this->freeList.pIterator = node;
    }

    if (!bestFit) {
        return nullptr;
    }

    // If remainder is too small, use entire bubble
    if (bestSize < 0x10) {
        this->freeList.DelNodeFromChain((gbChain1DNode*)bestFit);
        bestFit->startIndex = count;
        bestFit->primType = prim;
        this->usedList.AddNode((gbChain1DNode*)bestFit);
        return bestFit;
    }

    // Split the bubble - create new bubble for allocated region
    gbIndexBubble* newBubble = (gbIndexBubble*)operator new(0x24);
    if (newBubble) {
        newBubble->vtable = NULL;
        newBubble->pPool = this;
        newBubble->primType = prim;
        newBubble->startIndex = count;
        newBubble->count = count;
        newBubble->bUsed = bestFit->bUsed;
        newBubble->field_1C = -1;
        newBubble->field_20 = -1;
    }

    this->usedList.AddNode((gbChain1DNode*)newBubble);

    // Update remaining free bubble
    bestFit->bUsed += count;
    bestFit->count -= count;

    return newBubble;
}

// DelBubble: 0x10020b20
void gbIndexPool::DelBubble(gbIndexBubble* bubble) {
    // Remove from used list
    this->usedList.DelNodeFromChain((gbChain1DNode*)bubble);

    // Find position in free list (sorted by start index)
    gbChain1DNode* prev = nullptr;
    gbChain1DNode* curr = this->freeList.pHead;
    this->freeList.pIterator = curr;

    while (curr) {
        if (bubble->bUsed < ((gbIndexBubble*)curr)->bUsed) {
            // Insert before curr
            if (curr) {
                this->freeList.InsertAfter((gbChain1DNode*)bubble, prev);
            } else {
                this->freeList.AddNode((gbChain1DNode*)bubble);
            }
            goto merge_bubbles;
        }

        prev = curr;
        curr = this->freeList.pIterator->pNext;
        this->freeList.pIterator = curr;
    }

    // Add to end of free list
    this->freeList.AddNode((gbChain1DNode*)bubble);

merge_bubbles:
    // Try to merge with previous bubble
    if (prev) {
        gbIndexBubble* prevBubble = (gbIndexBubble*)prev;
        if (prevBubble->bUsed + prevBubble->count == bubble->bUsed) {
            // Merge
            prevBubble->startIndex = 0;
            prevBubble->count += bubble->count;
            this->freeList.DelNodeFromChain((gbChain1DNode*)bubble);
            if (bubble) {
                bubble->~gbIndexBubble();
                operator delete(bubble);
            }
            bubble = prevBubble;
        }
    }

    // Try to merge with next bubble
    if (curr) {
        gbIndexBubble* nextBubble = (gbIndexBubble*)curr;
        if (bubble->count + bubble->bUsed == nextBubble->bUsed) {
            // Merge
            nextBubble->bUsed = bubble->bUsed;
            nextBubble->startIndex = 0;
            nextBubble->count += bubble->count;
            this->freeList.DelNodeFromChain((gbChain1DNode*)bubble);
            if (bubble) {
                bubble->~gbIndexBubble();
                operator delete(bubble);
            }
        }
    }
}

// GetIndexSize: 0x10003cc0
int gbIndexPool::GetIndexSize() {
    return this->indexSize;
}

// GetInternalMemBuf: 0x10003ce0
void* gbIndexPool::GetInternalMemBuf() {
    return this->pIndexBuffer;
}

// IsEmpty: 0x10003cd0
int gbIndexPool::IsEmpty() {
    return this->usedList.count == 0;
}

// operator=: 0x10003d60
gbIndexPool& gbIndexPool::operator=(const gbIndexPool& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbIndexPool));
    }
    return *this;
}


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

// Constructor: 0x10003df0
gbVertexBubble::gbVertexBubble(gbVertexPool* pool, int start, int count, int used) {
    this->vtable = NULL;
    this->pPool = pool;
    this->startVertex = start;
    this->vertexCount = count;
    this->countUsed = used;
    this->bUsed = 0;
    this->pVertexData = nullptr;
    this->field_20 = nullptr;
    this->field_24 = nullptr;
    this->field_28 = nullptr;
    this->field_2C = nullptr;
    this->field_30 = nullptr;
    this->field_34 = nullptr;
}

// Copy constructor: 0x10003e60
gbVertexBubble::gbVertexBubble(const gbVertexBubble& other) {
    memcpy(this, &other, sizeof(gbVertexBubble));
}

// Destructor: 0x10003f30
gbVertexBubble::~gbVertexBubble() {
    // Virtual destructor
}

// Set: 0x10003e40
void gbVertexBubble::Set(int start, int count, int used) {
    this->startVertex = start;
    this->vertexCount = count;
    this->countUsed = used;
}

// Lock: 0x10020c00
void* gbVertexBubble::Lock() {
    // Lock vertex buffer
    return nullptr;
}

// Unlock: 0x10020ca0
void gbVertexBubble::Unlock() {
    // Unlock vertex buffer
}

// ClearPointer: 0x10003dd0
void gbVertexBubble::ClearPointer() {
    this->pVertexData = nullptr;
}

// StepVertexPtr: 0x10020cd0
void gbVertexBubble::StepVertexPtr() {
    // Advance vertex pointer
}

// operator=: 0x10003ed0
gbVertexBubble& gbVertexBubble::operator=(const gbVertexBubble& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbVertexBubble));
    }
    return *this;
}


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

    gbVertexBubble* NewBubble(int count);
    void DelBubble(gbVertexBubble* bubble);
    int GetStride();
    unsigned int GetVertType();
    int IsEmpty();
    gbVertexPool& operator=(const gbVertexPool& other);
};

gbGfxManager* gbVertexPool::pGfxMgr = nullptr;

// Constructor: 0x10020d90
gbVertexPool::gbVertexPool(gbPoolType type, unsigned int vertType, int total) {
    this->vtable = NULL;

    // Initialize free list
    this->freeList.pHead = nullptr;
    this->freeList.pTail = nullptr;
    this->freeList.count = 0;
    this->freeList.pIterator = nullptr;

    // Initialize used list
    this->usedList.pHead = nullptr;
    this->usedList.pTail = nullptr;
    this->usedList.count = 0;
    this->usedList.pIterator = nullptr;

    this->poolType = type;
    this->vtable = NULL;
    this->fvf = vertType;
    this->totalSize = total;

    // Calculate stride from FVF
    unsigned int stride = 0;
    if ((vertType & 0x80000000) == 0) {
        if (vertType & 0x001) stride += 12;   // Position
        if (vertType & 0x100) stride += 16;   // RHW
        if (vertType & 0x002) stride += 12;   // Normal
        if (vertType & 0x004) stride += 4;    // Diffuse
        if (vertType & 0x008) stride += 4;    // Specular
        if (vertType & 0x010) stride += 8;    // Tex1
        if (vertType & 0x020) stride += 8;    // Tex2
        if (vertType & 0x040) stride += 8;    // Tex3
        if (vertType & 0x080) stride += 8;    // Tex4
    } else {
        stride = vertType & 0x7FFFFFFF;
    }

    this->stride = stride;
    this->currentSize = 0;

    // Create initial free bubble
    gbVertexBubble* bubble = (gbVertexBubble*)operator new(0x38);
    if (bubble) {
        bubble->vtable = NULL;
        bubble->pPool = this;
        bubble->startVertex = 0;
        bubble->vertexCount = total;
        bubble->countUsed = total;
        bubble->bUsed = 0;
        bubble->pVertexData = nullptr;
        bubble->field_20 = nullptr;
        bubble->field_24 = nullptr;
        bubble->field_28 = nullptr;
        bubble->field_2C = nullptr;
        bubble->field_30 = nullptr;
        bubble->field_34 = nullptr;
    }

    this->freeList.AddNode((gbChain1DNode*)bubble);
}

// Copy constructor: 0x10003fc0
gbVertexPool::gbVertexPool(const gbVertexPool& other) {
    memcpy(this, &other, sizeof(gbVertexPool));
}

// Destructor: 0x10020eb0
gbVertexPool::~gbVertexPool() {
    // Cleanup
}

// NewBubble: 0x10020f10
gbVertexBubble* gbVertexPool::NewBubble(int count) {
    gbVertexBubble* bestFit = nullptr;
    int bestSize = 0x7FFFFFFF;

    // Find best-fit free bubble
    gbChain1DNode* node = this->freeList.pHead;
    this->freeList.pIterator = node;

    while (node) {
        gbVertexBubble* bubble = (gbVertexBubble*)node;
        int freeSize = bubble->countUsed - count;

        if (freeSize >= 0 && freeSize < bestSize) {
            bestSize = freeSize;
            bestFit = bubble;
        }

        node = this->freeList.pIterator->pNext;
        this->freeList.pIterator = node;
    }

    if (!bestFit) {
        return nullptr;
    }

    // If remainder is too small, use entire bubble
    if (bestSize < 0x10) {
        this->freeList.DelNodeFromChain((gbChain1DNode*)bestFit);
        bestFit->countUsed = count;
        this->usedList.AddNode((gbChain1DNode*)bestFit);
        return bestFit;
    }

    // Split the bubble
    gbVertexBubble* newBubble = (gbVertexBubble*)operator new(0x38);
    gbVertexBubble* result = nullptr;

    if (newBubble) {
        newBubble->vtable = NULL;
        newBubble->pPool = this;
        newBubble->startVertex = bestFit->startVertex;
        newBubble->vertexCount = count;
        newBubble->countUsed = count;
        newBubble->bUsed = 0;
        newBubble->pVertexData = nullptr;
        newBubble->field_20 = nullptr;
        newBubble->field_24 = nullptr;
        newBubble->field_28 = nullptr;
        newBubble->field_2C = nullptr;
        newBubble->field_30 = nullptr;
        newBubble->field_34 = nullptr;
        result = newBubble;
    }

    this->usedList.AddNode((gbChain1DNode*)result);

    // Update remaining free bubble
    bestFit->startVertex += count;
    bestFit->countUsed -= count;

    return result;
}

// DelBubble: 0x10020fe0
void gbVertexPool::DelBubble(gbVertexBubble* bubble) {
    // Similar to gbIndexPool::DelBubble but for vertices
    this->usedList.DelNodeFromChain((gbChain1DNode*)bubble);

    gbChain1DNode* prev = nullptr;
    gbChain1DNode* curr = this->freeList.pHead;
    this->freeList.pIterator = curr;

    while (curr) {
        if (bubble->startVertex < ((gbVertexBubble*)curr)->startVertex) {
            if (curr) {
                this->freeList.InsertAfter((gbChain1DNode*)bubble, prev);
            } else {
                this->freeList.AddNode((gbChain1DNode*)bubble);
            }
            goto merge_vert_bubbles;
        }

        prev = curr;
        curr = this->freeList.pIterator->pNext;
        this->freeList.pIterator = curr;
    }

    this->freeList.AddNode((gbChain1DNode*)bubble);

merge_vert_bubbles:
    // Merge with adjacent free bubbles
    if (prev) {
        gbVertexBubble* prevBubble = (gbVertexBubble*)prev;
        if (prevBubble->startVertex + prevBubble->countUsed == bubble->startVertex) {
            prevBubble->vertexCount = 0;
            prevBubble->countUsed += bubble->countUsed;
            this->freeList.DelNodeFromChain((gbChain1DNode*)bubble);
            if (bubble) {
                bubble->~gbVertexBubble();
                operator delete(bubble);
            }
            bubble = prevBubble;
        }
    }

    if (curr) {
        gbVertexBubble* nextBubble = (gbVertexBubble*)curr;
        if (bubble->countUsed + bubble->startVertex == nextBubble->startVertex) {
            nextBubble->startVertex = bubble->startVertex;
            nextBubble->vertexCount = 0;
            nextBubble->countUsed += bubble->countUsed;
            this->freeList.DelNodeFromChain((gbChain1DNode*)bubble);
            if (bubble) {
                bubble->~gbVertexBubble();
                operator delete(bubble);
            }
        }
    }
}

// GetStride: 0x10004d10
int gbVertexPool::GetStride() {
    return this->stride;
}

// GetVertType: 0x10003fa0
unsigned int gbVertexPool::GetVertType() {
    return this->fvf;
}

// IsEmpty: 0x10003fb0
int gbVertexPool::IsEmpty() {
    return this->usedList.count == 0;
}

// operator=: 0x10004040
gbVertexPool& gbVertexPool::operator=(const gbVertexPool& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbVertexPool));
    }
    return *this;
}


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
    int FindVertexPoolIndex(unsigned int* fvf, unsigned int type);
    gbVertexBubble* NewVertexBubble(unsigned int fvf, int count);
    void DelVertexBubble(gbVertexBubble* bubble);
    gbVertexBubble* NewSrcVertBub(unsigned int fvf, int count);
    void DelSrcVertBub(gbVertexBubble* bubble);
    gbIndexBubble* NewIndexBubble(gbPrimType prim, int count);
    void DelIndexBubble(gbIndexBubble* bubble);
    gbDynVertBuf* GetDynVertBuf(unsigned int fvf);
    gbVertPoolMgr& operator=(const gbVertPoolMgr& other);
};

// Constructor: 0x100210c0
gbVertPoolMgr::gbVertPoolMgr(gbGfxManager* mgr, int p2, int p3, int p4, int p5) {
    // Initialize vertex pool chain array (32 x gbChain1D, each 16 bytes)
    memset(this, 0, 0x10 * 0x20);

    // Initialize index pool list
    this->indexPoolList.pHead = nullptr;
    this->indexPoolList.pTail = nullptr;
    this->indexPoolList.count = 0;
    this->indexPoolList.pIterator = nullptr;

    // Initialize src vert pool chain array
    memset((char*)this + 0x390, 0, 0x10 * 0x20);

    this->maxVertexPoolSize = p2;
    this->maxIndexPoolSize = p3;
    this->pGfxManager = mgr;
    this->field_618 = p4;
    this->field_61C = p5;

    // Set global manager pointers
    gbVertexPool::pGfxMgr = mgr;
    g_gbDynVertBuf_pGfxMgr = mgr;

    // Zero out pool arrays
    for (int i = 0; i < 32; i++) {
        this->vertexPools[i] = nullptr;
        this->srcVertPools[i] = nullptr;
        this->dynVertBufs[i] = nullptr;
    }
}

// Destructor: 0x100211a0
gbVertPoolMgr::~gbVertPoolMgr() {
    // Clean up all pools
    for (int i = 0; i < 32; i++) {
        if (this->vertexPools[i]) {
            delete this->vertexPools[i];
        }
        if (this->srcVertPools[i]) {
            delete this->srcVertPools[i];
        }
        if (this->dynVertBufs[i]) {
            delete this->dynVertBufs[i];
        }
    }
}

// OnLostDevice: 0x10021240
int gbVertPoolMgr::OnLostDevice() {
    // Release D3D resources when device is lost
    return 0;
}

// OnResetDevice: 0x10021270
int gbVertPoolMgr::OnResetDevice() {
    // Recreate D3D resources when device is reset
    return 0;
}

// FindVertexPoolIndex: 0x100212a0
int gbVertPoolMgr::FindVertexPoolIndex(unsigned int* fvf, unsigned int type) {
    // Find pool index for given FVF type
    for (int i = 0; i < 32; i++) {
        if (this->vertexPools[i] && this->vertexPools[i]->fvf == type) {
            *fvf = type;
            return i;
        }
    }
    return -1;
}

// NewVertexBubble: 0x100212e0
gbVertexBubble* gbVertPoolMgr::NewVertexBubble(unsigned int fvf, int count) {
    // Update statistics
    int* pStatCount = (int*)((char*)this->pGfxManager + 0x214);
    *pStatCount += count;

    // Try existing pools
    gbVertexPool* pool = this->vertexPools[0];
    this->vertexPools[12] = pool;

    while (pool) {
        gbVertexBubble* bubble = pool->NewBubble(count);
        if (bubble) {
            return bubble;
        }

        pool = (gbVertexPool*)this->vertexPools[12]->pNext;
        this->vertexPools[12] = pool;
    }

    // Need to create new pool
    if (this->maxVertexPoolSize < count) {
        this->maxVertexPoolSize = count;
    }

    // Create pool through GfxManager virtual function
    void** vtable = *(void***)this->pGfxManager;
    typedef gbVertexPool* (*CreatePoolFunc)(gbGfxManager*, int, int, int);
    CreatePoolFunc createPool = (CreatePoolFunc)vtable[5];
    pool = createPool(this->pGfxManager, 0, fvf, this->maxVertexPoolSize);

    // Add to list
    // this->dynVertBufList.AddNode((gbChain1DNode*)pool);

    return pool->NewBubble(count);
}

// DelVertexBubble: 0x100213a0
void gbVertPoolMgr::DelVertexBubble(gbVertexBubble* bubble) {
    if (bubble && bubble->pPool) {
        bubble->pPool->DelBubble(bubble);
    }
}

// NewSrcVertBub: 0x10021430
gbVertexBubble* gbVertPoolMgr::NewSrcVertBub(unsigned int fvf, int count) {
    // Similar to NewVertexBubble but for system memory pools
    return NewVertexBubble(fvf, count);
}

// DelSrcVertBub: 0x100214f0
void gbVertPoolMgr::DelSrcVertBub(gbVertexBubble* bubble) {
    if (bubble && bubble->pPool) {
        bubble->pPool->DelBubble(bubble);
    }
}

// NewIndexBubble: 0x10021590
gbIndexBubble* gbVertPoolMgr::NewIndexBubble(gbPrimType prim, int count) {
    // Update statistics
    int* pStatCount = (int*)((char*)this->pGfxManager + 0x214);
    *pStatCount += count;

    // Try existing pools
    gbIndexPool* pool = (gbIndexPool*)this->indexPoolList.pHead;
    this->pIndexIterator = (gbChain1DNode*)pool;

    while (pool) {
        gbIndexBubble* bubble = pool->NewBubble(prim, count);
        if (bubble) {
            return bubble;
        }

        pool = (gbIndexPool*)this->pIndexIterator->pNext;
        this->pIndexIterator = (gbChain1DNode*)pool;
    }

    // Need to create new pool
    if (this->maxIndexPoolSize < count) {
        this->maxIndexPoolSize = count;
    }

    // Create pool through GfxManager virtual function
    void** vtable = *(void***)this->pGfxManager;
    typedef gbIndexPool* (*CreatePoolFunc)(gbGfxManager*, int, int, int);
    CreatePoolFunc createPool = (CreatePoolFunc)vtable[5];
    pool = createPool(this->pGfxManager, 0, 2, this->maxIndexPoolSize);

    this->indexPoolList.AddNode((gbChain1DNode*)pool);

    return pool->NewBubble(prim, count);
}

// DelIndexBubble: 0x10021620
void gbVertPoolMgr::DelIndexBubble(gbIndexBubble* bubble) {
    if (bubble && bubble->pPool) {
        bubble->pPool->DelBubble(bubble);
    }
}

// GetDynVertBuf: 0x10021680
gbDynVertBuf* gbVertPoolMgr::GetDynVertBuf(unsigned int fvf) {
    // Find or create dynamic vertex buffer for given FVF
    for (int i = 0; i < 32; i++) {
        if (this->dynVertBufs[i]) {
            // Check if FVF matches
            // return this->dynVertBufs[i];
        }
    }
    return nullptr;
}

// operator=: 0x100040b0
gbVertPoolMgr& gbVertPoolMgr::operator=(const gbVertPoolMgr& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbVertPoolMgr));
    }
    return *this;
}


// Stub implementations for gbChain1D methods
gbChain1D::gbChain1D() {
    pHead = nullptr;
    pTail = nullptr;
    count = 0;
    pIterator = nullptr;
}

gbChain1D::~gbChain1D() {
    // Cleanup nodes
}

void gbChain1D::AddNode(gbChain1DNode* node) {
    if (!node) return;

    node->pNext = nullptr;

    if (!pHead) {
        pHead = node;
        pTail = node;
    } else {
        pTail->pNext = node;
        pTail = node;
    }
    count++;
}

void gbChain1D::DelNodeFromChain(gbChain1DNode* node) {
    if (!node || !pHead) return;

    if (pHead == node) {
        pHead = node->pNext;
        if (!pHead) pTail = nullptr;
        count--;
        return;
    }

    gbChain1DNode* prev = pHead;
    while (prev && prev->pNext != node) {
        prev = prev->pNext;
    }

    if (prev) {
        prev->pNext = node->pNext;
        if (pTail == node) pTail = prev;
        count--;
    }
}

void gbChain1D::InsertAfter(gbChain1DNode* node, gbChain1DNode* after) {
    if (!node) return;

    if (!after) {
        // Insert at head
        node->pNext = pHead;
        pHead = node;
        if (!pTail) pTail = node;
    } else {
        node->pNext = after->pNext;
        after->pNext = node;
        if (pTail == after) pTail = node;
    }
    count++;
}
