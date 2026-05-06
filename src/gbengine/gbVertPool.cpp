/**
 * gbengine.dll - gbVertPool
 * Vertex and Index buffer pool management
 */

#include "gbengine/gbMesh.h"
#include "gbengine/gbGfxManager.h"
#include <string.h>

// Global statics
static gbGfxManager* g_gbVertexPool_pGfxMgr = NULL;
static gbGfxManager* g_gbDynVertBuf_pGfxMgr = NULL;


/* ======== gbIndexBubble ======== */

// Constructor: 0x10003b50
gbIndexBubble::gbIndexBubble(gbIndexPool* pool, gbPrimType prim, int start, int cnt, int used) {
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
    return nullptr;
}

// gbIndexBubble::Lock32 - Lock 32-bit index buffer

unsigned int* gbIndexBubble::Lock32() {
    if (!pPool || !pPool->pIndexBuffer) {
        return NULL;
    }

    // Lock the D3D index buffer
    void* pData = NULL;
    HRESULT hr = pPool->pIndexBuffer->Lock(
        startIndex * sizeof(unsigned int),  // Offset in bytes
        count * sizeof(unsigned int),        // Size in bytes
        &pData,
        0                                    // Flags
    );

    if (FAILED(hr)) {
        return NULL;
    }

    return (unsigned int*)pData;
}

// Unlock: 0x10020920
void gbIndexBubble::Unlock() {
    pPool->pIndexBuffer->Unlock();
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

// Constructor: 0x10020930
gbIndexPool::gbIndexPool(gbPoolType type, int indexSz, int total) {

    // Initialize free list
    this->freeList.pHead = nullptr;
    this->freeList.pTail = nullptr;
    this->freeList.nCount = 0;
    this->freeList.pIterator = nullptr;

    // Initialize used list
    this->usedList.pHead = nullptr;
    this->usedList.pTail = nullptr;
    this->usedList.nCount = 0;
    this->usedList.pIterator = nullptr;

    this->poolType = type;
    this->indexSize = indexSz;
    this->totalSize = total;
    this->currentSize = 0;

    // Create initial free bubble covering entire pool
    gbIndexBubble* bubble = (gbIndexBubble*)operator new(0x24);
    if (bubble) {
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
    memcpy(this, &other, sizeof(gbIndexPool));
}

// Destructor: 0x100209f0
gbIndexPool::~gbIndexPool() {
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
    return this->usedList.nCount == 0;
}

// operator=: 0x10003d60
gbIndexPool& gbIndexPool::operator=(const gbIndexPool& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbIndexPool));
    }
    return *this;
}


/* ======== gbVertexBubble ======== */

// Constructor: 0x10003df0
gbVertexBubble::gbVertexBubble(gbVertexPool* pool, int start, int count, int used) {
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
}

// Set: 0x10003e40
void gbVertexBubble::Set(int start, int count, int used) {
    this->startVertex = start;
    this->vertexCount = count;
    this->countUsed = used;
}

// Lock: 0x10020c00 (160B)
void* gbVertexBubble::Lock() {
    void* pData = pPool->Lock(startVertex, vertexCount);
    int offset = 0;
    unsigned int fvf = pPool->fvf;

    if (fvf & 0x80000000)
        return pData;

    if (fvf & 0x1) {
        pVertexData = (char*)pData + offset;
        offset += 12;
    }
    if (fvf & 0x100) {
        pVertexData = (char*)pData + offset;
        offset += 16;
    }
    if (fvf & 0x2) {
        field_20 = (char*)pData + offset;
        offset += 12;
    }
    if (fvf & 0x4) {
        field_24 = (char*)pData + offset;
        offset += 4;
    }
    if (fvf & 0x8) {
        field_28 = (char*)pData + offset;
        offset += 4;
    }
    if (fvf & 0x10) {
        field_2C = (char*)pData + offset;
        offset += 8;
    }
    if (fvf & 0x20) {
        field_30 = (char*)pData + offset;
        offset += 8;
    }
    if (fvf & 0x40) {
        field_34 = (char*)pData + offset;
        offset += 8;
    }
    if (fvf & 0x80) {
        *(void**)((char*)this + 0x34) = (char*)pData + offset;
    }
    return pData;
}

// Unlock: 0x10020ca0
void gbVertexBubble::Unlock() {
    bUsed = 0;
    pVertexData = NULL;
    field_20 = NULL;
    field_24 = NULL;
    field_28 = NULL;
    field_2C = NULL;
    field_30 = NULL;
    field_34 = NULL;
    pPool->pVertexBuffer->Unlock();
}

// ClearPointer: 0x10003dd0
void gbVertexBubble::ClearPointer() {
    this->pVertexData = nullptr;
}

// StepVertexPtr: 0x10020cd0
void gbVertexBubble::StepVertexPtr() {
    unsigned int flags = pPool->fvf;
    int s = pPool->stride;
    if ((flags & 1) || (flags & 0x100)) { bUsed += s; }
    if (flags & 2)   { pVertexData = (char*)pVertexData + s; }
    if (flags & 4)   { field_20 = (char*)field_20 + s; }
    if (flags & 8)   { field_24 = (char*)field_24 + s; }
    if (flags & 0x10) { field_28 = (char*)field_28 + s; }
    if (flags & 0x20) { field_2C = (char*)field_2C + s; }
    if (flags & 0x40) { field_30 = (char*)field_30 + s; }
    if (flags & 0x80) { field_34 = (char*)field_34 + s; }
}

// operator=: 0x10003ed0
gbVertexBubble& gbVertexBubble::operator=(const gbVertexBubble& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbVertexBubble));
    }
    return *this;
}


/* ======== gbVertexPool ======== */

gbGfxManager* gbVertexPool::pGfxMgr = nullptr;

// Constructor: 0x10020d90
gbVertexPool::gbVertexPool(gbPoolType type, unsigned int vertType, int total) {

    // Initialize free list
    this->freeList.pHead = nullptr;
    this->freeList.pTail = nullptr;
    this->freeList.nCount = 0;
    this->freeList.pIterator = nullptr;

    // Initialize used list
    this->usedList.pHead = nullptr;
    this->usedList.pTail = nullptr;
    this->usedList.nCount = 0;
    this->usedList.pIterator = nullptr;

    this->poolType = type;
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
}

// Lock: virtual - locks portion of vertex buffer
void* gbVertexPool::Lock(int start, int count) {
    void* pData = NULL;
    if (pVertexBuffer) {
        pVertexBuffer->Lock(start * stride, count * stride, &pData, 0);
    }
    return pData;
}

// OnLostDevice
int gbVertexPool::OnLostDevice() {
    if (pVertexBuffer) {
        pVertexBuffer->Release();
        pVertexBuffer = NULL;
    }
    return 1;
}

// OnResetDevice
int gbVertexPool::OnResetDevice() {
    if (pDevice && !pVertexBuffer) {
        HRESULT hr = pDevice->CreateVertexBuffer(
            totalSize * stride,
            0,
            fvf,
            (D3DPOOL)poolType,
            &pVertexBuffer,
            NULL);
        if (FAILED(hr)) {
            return 0;
        }
    }
    return 1;
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
    return this->usedList.nCount == 0;
}

// operator=: 0x10004040
gbVertexPool& gbVertexPool::operator=(const gbVertexPool& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbVertexPool));
    }
    return *this;
}


/* ======== gbVertPoolMgr ======== */

// Constructor: 0x100210c0
gbVertPoolMgr::gbVertPoolMgr(gbGfxManager* mgr, int p2, int p3, int p4, int p5) {
    // Initialize vertex pool chain array (32 x gbChain1D, each 16 bytes)
    memset(this, 0, 0x10 * 0x20);

    // Initialize index pool list
    this->indexPoolList.pHead = nullptr;
    this->indexPoolList.pTail = nullptr;
    this->indexPoolList.nCount = 0;
    this->indexPoolList.pIterator = nullptr;

    // Initialize dynamic vert buf area
    memset(&this->dynVertBufList, 0, 0x10 * 0x20);

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
    for (int i = 0; i < 32; i++) {
        if (srcVertPools[i] != NULL) {
            if (srcVertPools[i]->OnLostDevice() == 0) {
                return 0;
            }
        }
    }
    return 1;
}

// OnResetDevice: 0x10021270
int gbVertPoolMgr::OnResetDevice() {
    for (int i = 0; i < 32; i++) {
        if (srcVertPools[i] != NULL) {
            if (srcVertPools[i]->OnResetDevice() == 0) {
                return 0;
            }
        }
    }
    return 1;
}

// Find which vertex pool index contains the given FVF
int gbVertPoolMgr::FindVertexPoolIndex(unsigned int* pFVF, unsigned int fvf) {
    for (int i = 0; i < 32; i++) {
        if (vertexPools[i] && vertexPools[i]->fvf == fvf) {
            if (pFVF) *pFVF = fvf;
            return i;
        }
    }

    // Not found - return first available slot
    for (int i = 0; i < 32; i++) {
        if (!vertexPools[i]) {
            if (pFVF) *pFVF = 0;
            return i;
        }
    }

    // No slots available
    if (pFVF) *pFVF = 0;
    return -1;
}

// NewVertexBubble: 0x100212e0
gbVertexBubble* gbVertPoolMgr::NewVertexBubble(unsigned int fvf, int count) {
    // Update statistics
    int* pStatCount = &this->pGfxManager->Stat.nStaticIndex;
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
    int* pStatCount = &this->pGfxManager->Stat.nStaticIndex;
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
