/**
 * gbengine.dll - gbVertPool
 * Vertex and Index buffer pool management
 */

#include "gbengine/gbMesh.h"
#include "gbengine/gbGfxManager.h"
#include <d3d9.h>
#include <string.h>

// Global statics
static gbGfxManager* g_gbDynVertBuf_pGfxMgr = NULL;
gbGfxManager* gbIndexPool::pGfxMgr = NULL;


/* ======== gbIndexBubble ======== */

// Constructor: 0x10003b50
gbIndexBubble::gbIndexBubble(gbIndexPool* pool, gbPrimType prim, int start, int cnt, int used) {
    this->pPool = pool;
    this->count = cnt;
    this->primType = prim;
    this->bUsed = used;
    this->startIndex = start;
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
    this->field_1C = start;
    this->field_20 = cnt;
}

// Lock16: 0x10020900
unsigned short* gbIndexBubble::Lock16() {
    // Lock the index buffer for this bubble's range
    IDirect3DIndexBuffer9* pIB = NULL;
    return NULL;
}

// gbIndexBubble::Lock32 - Lock 32-bit index buffer

unsigned int* gbIndexBubble::Lock32() {
    if (!pPool || !pPool->pBuffer) {
        return NULL;
    }

    // Lock the D3D index buffer
    void* pData = NULL;
    IDirect3DIndexBuffer9* pIB = (IDirect3DIndexBuffer9*)pPool->pBuffer;
    HRESULT hr = pIB->Lock(
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
    pPool->Unlock();
}

// operator=: 0x10003c20
gbIndexBubble& gbIndexBubble::operator=(const gbIndexBubble& other) {
    pNext = other.pNext;
    pPool = other.pPool;
    primType = other.primType;
    count = other.count;
    bUsed = other.bUsed;
    startIndex = other.startIndex;
    field_1C = other.field_1C;
    field_20 = other.field_20;
    return *this;
}


/* ======== gbIndexPool ======== */

// Constructor: 0x10020930
gbIndexPool::gbIndexPool(gbPoolType type, int indexSz, int total) {

    // Initialize free list
    this->freeList.pHead = NULL;
    this->freeList.pTail = NULL;
    this->freeList.m_numNode = 0;
    this->freeList.pIterator = NULL;

    // Initialize used list
    this->usedList.pHead = NULL;
    this->usedList.pTail = NULL;
    this->usedList.m_numNode = 0;
    this->usedList.pIterator = NULL;

    this->poolType = type;
    this->indexSize = indexSz;
    this->totalSize = total;
    this->pBuffer = NULL;

    // Create initial free bubble covering entire pool
    gbIndexBubble* bubble = (gbIndexBubble*)operator new(0x24);
    if (bubble) {
        bubble->pPool = this;
        bubble->primType = (gbPrimType)0;
        bubble->count = 0;
        bubble->bUsed = total;
        bubble->startIndex = 0;
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

// Lock: 0x100209a0 - Lock the entire index buffer
void gbIndexPool::Lock() {
    if (pBuffer) {
        IDirect3DIndexBuffer9* pIB = (IDirect3DIndexBuffer9*)pBuffer;
        void* pData = NULL;
        pIB->Lock(0, 0, &pData, 0);
    }
}

// Unlock: 0x100209c0 - Unlock the index buffer
void gbIndexPool::Unlock() {
    if (pBuffer) {
        IDirect3DIndexBuffer9* pIB = (IDirect3DIndexBuffer9*)pBuffer;
        pIB->Unlock();
    }
}

// NewBubble: 0x10020a50
gbIndexBubble* gbIndexPool::NewBubble(gbPrimType prim, int count) {
    gbIndexBubble* bestFit = NULL;
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
        return NULL;
    }

    // If remainder is too small, use entire bubble
    if (bestSize < 16) {
        this->freeList.DelNodeFromChain((gbChain1DNode*)bestFit);
        bestFit->count = count;
        bestFit->primType = prim;
        this->usedList.AddNodeOnTail((gbChain1DNode*)bestFit);
        return bestFit;
    }

    // Split the bubble - create new bubble for allocated region
    gbIndexBubble* newBubble = (gbIndexBubble*)operator new(0x24);
    if (newBubble) {
        newBubble->startIndex = bestFit->startIndex;
        newBubble->pPool = this;
        newBubble->primType = prim;
        newBubble->count = count;
        newBubble->bUsed = count;
        newBubble->field_1C = -1;
        newBubble->field_20 = -1;
    }

    this->usedList.AddNodeOnTail((gbChain1DNode*)newBubble);

    // Update remaining free bubble
    bestFit->startIndex += count;
    bestFit->bUsed -= count;

    return newBubble;
}

// DelBubble: 0x10020b20
void gbIndexPool::DelBubble(gbIndexBubble* bubble) {
    // Remove from used list
    this->usedList.DelNodeFromChain((gbChain1DNode*)bubble);

    // Find position in free list (sorted by startIndex)
    gbChain1DNode* prev = NULL;
    gbChain1DNode* curr = this->freeList.pHead;
    this->freeList.pIterator = curr;

    if (curr) {
        while (((gbIndexBubble*)curr)->startIndex <= bubble->startIndex) {
            prev = curr;
            curr = this->freeList.pIterator->pNext;
            this->freeList.pIterator = curr;
            if (!curr)
                goto insert_at_end;
        }
        this->freeList.InsertAfter((gbChain1DNode*)bubble, prev);
    } else {
insert_at_end:
        this->freeList.AddNodeOnTail((gbChain1DNode*)bubble);
    }

    // Try to merge with previous bubble
    if (prev) {
        gbIndexBubble* prevBubble = (gbIndexBubble*)prev;
        if (prevBubble->bUsed + prevBubble->startIndex == bubble->startIndex) {
            int merged = prevBubble->bUsed + bubble->bUsed;
            prevBubble->count = 0;
            prevBubble->bUsed = merged;
            this->freeList.DelNodeFromChain((gbChain1DNode*)bubble);
            if (bubble)
                delete bubble;
            bubble = prevBubble;
        }
    }

    // Try to merge with next bubble
    if (curr) {
        gbIndexBubble* nextBubble = (gbIndexBubble*)curr;
        if (bubble->bUsed + bubble->startIndex == nextBubble->startIndex) {
            int nextSize = nextBubble->bUsed;
            nextBubble->startIndex = bubble->startIndex;
            nextBubble->count = 0;
            nextBubble->bUsed = nextSize + bubble->bUsed;
            this->freeList.DelNodeFromChain((gbChain1DNode*)bubble);
            if (bubble)
                delete bubble;
        }
    }
}

// GetIndexSize: 0x10003cc0
int gbIndexPool::GetIndexSize() {
    return this->indexSize;
}

// GetInternalMemBuf: 0x10003ce0
void* gbIndexPool::GetInternalMemBuf() {
    return this->pBuffer;
}

// IsEmpty: 0x10003cd0
int gbIndexPool::IsEmpty() {
    return usedList[0] == 0;
}

// operator=: 0x10003d60
gbIndexPool& gbIndexPool::operator=(const gbIndexPool& other) {
    pNext = other.pNext;
    poolType = other.poolType;
    indexSize = other.indexSize;
    pBuffer = other.pBuffer;
    totalSize = other.totalSize;
    freeList.pHead = other.freeList.pHead;
    freeList.pTail = other.freeList.pTail;
    freeList.m_numNode = other.freeList.m_numNode;
    freeList.pIterator = other.freeList.pIterator;
    usedList.pHead = other.usedList.pHead;
    usedList.pTail = other.usedList.pTail;
    usedList.m_numNode = other.usedList.m_numNode;
    usedList.pIterator = other.usedList.pIterator;
    return *this;
}


/* ======== gbVertexBubble ======== */

// Constructor: 0x10003df0
gbVertexBubble::gbVertexBubble(gbVertexPool* pool, int start, int count, int used) {
    this->pPool = pool;
    this->startVertex = start;
    this->vertexCount = count;
    this->countUsed = used;
    this->pVertexData = NULL;
    this->field_1C = NULL;
    this->field_20 = NULL;
    this->field_24 = NULL;
    this->field_28 = NULL;
    this->field_2C = NULL;
    this->field_30 = NULL;
    this->field_34 = NULL;
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
        field_1C = (char*)pData + offset;
        offset += 12;
    }
    if (fvf & 0x4) {
        field_20 = (char*)pData + offset;
        offset += 4;
    }
    if (fvf & 0x8) {
        field_24 = (char*)pData + offset;
        offset += 4;
    }
    if (fvf & 0x10) {
        field_28 = (char*)pData + offset;
        offset += 8;
    }
    if (fvf & 0x20) {
        field_2C = (char*)pData + offset;
        offset += 8;
    }
    if (fvf & 0x40) {
        field_30 = (char*)pData + offset;
        offset += 8;
    }
    if (fvf & 0x80) {
        field_34 = (char*)pData + offset;
    }
    return pData;
}

// Unlock: 0x10020ca0
void gbVertexBubble::Unlock() {
    pVertexData = NULL;
    field_1C = NULL;
    field_20 = NULL;
    field_24 = NULL;
    field_28 = NULL;
    field_2C = NULL;
    field_30 = NULL;
    field_34 = NULL;
    pPool->OnResetDevice();
}

// ClearPointer: 0x10003dd0
void gbVertexBubble::ClearPointer() {
    pVertexData = NULL;
    field_1C = NULL;
    field_20 = NULL;
    field_24 = NULL;
    field_28 = NULL;
    field_2C = NULL;
    field_30 = NULL;
    field_34 = NULL;
}

// StepVertexPtr: 0x10020cd0
void gbVertexBubble::StepVertexPtr() {
    unsigned int flags = pPool->fvf;
    int s = pPool->stride;
    if ((flags & 1) || (flags & 0x100)) { pVertexData = (char*)pVertexData + s; }
    if (flags & 2)   { field_1C = (char*)field_1C + s; }
    if (flags & 4)   { field_20 = (char*)field_20 + s; }
    if (flags & 8)   { field_24 = (char*)field_24 + s; }
    if (flags & 0x10) { field_28 = (char*)field_28 + s; }
    if (flags & 0x20) { field_2C = (char*)field_2C + s; }
    if (flags & 0x40) { field_30 = (char*)field_30 + s; }
    if (flags & 0x80) { field_34 = (char*)field_34 + s; }
}

// operator=: 0x10003ed0
gbVertexBubble& gbVertexBubble::operator=(const gbVertexBubble& other) {
    pNext = other.pNext;
    pPool = other.pPool;
    startVertex = other.startVertex;
    countUsed = other.countUsed;
    vertexCount = other.vertexCount;
    pVertexData = other.pVertexData;
    field_1C = other.field_1C;
    field_20 = other.field_20;
    field_24 = other.field_24;
    field_28 = other.field_28;
    field_2C = other.field_2C;
    field_30 = other.field_30;
    field_34 = other.field_34;
    return *this;
}


/* ======== gbVertexPool ======== */

gbGfxManager* gbVertexPool::pGfxMgr = NULL;

// Constructor: 0x10020d90
gbVertexPool::gbVertexPool(gbPoolType type, unsigned int vertType, int total) {

    // Initialize free list
    this->freeList.pHead = NULL;
    this->freeList.pTail = NULL;
    this->freeList.m_numNode = 0;
    this->freeList.pIterator = NULL;

    // Initialize used list
    this->usedList.pHead = NULL;
    this->usedList.pTail = NULL;
    this->usedList.m_numNode = 0;
    this->usedList.pIterator = NULL;

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
    this->pBuffer = NULL;

    // Create initial free bubble
    gbVertexBubble* bubble = (gbVertexBubble*)operator new(0x38);
    if (bubble) {
        bubble->pPool = this;
        bubble->startVertex = 0;
        bubble->vertexCount = total;
        bubble->countUsed = total;
        bubble->pVertexData = NULL;
        bubble->field_1C = NULL;
        bubble->field_20 = NULL;
        bubble->field_24 = NULL;
        bubble->field_28 = NULL;
        bubble->field_2C = NULL;
        bubble->field_30 = NULL;
        bubble->field_34 = NULL;
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
    if (pBuffer) {
        IDirect3DVertexBuffer9* pVB = (IDirect3DVertexBuffer9*)pBuffer;
        pVB->Lock(start * stride, count * stride, &pData, 0);
    }
    return pData;
}

// OnLostDevice
int gbVertexPool::OnLostDevice() {
    if (pBuffer) {
        IDirect3DVertexBuffer9* pVB = (IDirect3DVertexBuffer9*)pBuffer;
        pVB->Release();
        pBuffer = NULL;
    }
    return 1;
}

// OnResetDevice
int gbVertexPool::OnResetDevice() {
    // Re-creation of the buffer is handled at a higher level
    // (by the D3D subclass or the pool manager)
    return 1;
}

// DrawIndexedPrimitive: base class stub (overridden by gbVertexPool_D3D)
void gbVertexPool::DrawIndexedPrimitive(gbVertexBubble* vb, void* ib, int param3, gbTexture** textures) {
    (void)vb;
    (void)ib;
    (void)param3;
    (void)textures;
}

// NewBubble: 0x10020f10
gbVertexBubble* gbVertexPool::NewBubble(int count) {
    gbVertexBubble* bestFit = NULL;
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
        return NULL;
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
    gbVertexBubble* result = NULL;

    if (newBubble) {
        newBubble->pPool = this;
        newBubble->startVertex = bestFit->startVertex;
        newBubble->vertexCount = count;
        newBubble->countUsed = count;
        newBubble->pVertexData = NULL;
        newBubble->field_1C = NULL;
        newBubble->field_20 = NULL;
        newBubble->field_24 = NULL;
        newBubble->field_28 = NULL;
        newBubble->field_2C = NULL;
        newBubble->field_30 = NULL;
        newBubble->field_34 = NULL;
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

    gbChain1DNode* prev = NULL;
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
    return usedList[0] == 0;
}

// operator=: 0x10004040
gbVertexPool& gbVertexPool::operator=(const gbVertexPool& other) {
    pNext = other.pNext;
    poolType = other.poolType;
    pBuffer = other.pBuffer;
    totalSize = other.totalSize;
    fvf = other.fvf;
    stride = other.stride;
    freeList.pHead = other.freeList.pHead;
    freeList.pTail = other.freeList.pTail;
    freeList.m_numNode = other.freeList.m_numNode;
    freeList.pIterator = other.freeList.pIterator;
    usedList.pHead = other.usedList.pHead;
    usedList.pTail = other.usedList.pTail;
    usedList.m_numNode = other.usedList.m_numNode;
    usedList.pIterator = other.usedList.pIterator;
    return *this;
}


/* ======== gbVertPoolMgr ======== */

// Constructor: 0x100210c0
gbVertPoolMgr::gbVertPoolMgr(gbGfxManager* mgr, int p2, int p3, int p4, int p5) {
    // Initialize vertex pool chain array (32 x gbChain1D, each 16 bytes)
    memset(this, 0, 0x10 * 0x20);

    // Initialize index pool list
    this->indexPoolList.pHead = NULL;
    this->indexPoolList.pTail = NULL;
    this->indexPoolList.m_numNode = 0;
    this->indexPoolList.pIterator = NULL;

    // Initialize src vertex pool chain area
    memset(&this->srcVertPoolChains, 0, 0x10 * 0x20);

    this->maxVertexPoolSize = p2;
    this->maxIndexPoolSize = p3;
    this->pGfxManager = mgr;
    this->field_618 = p4;
    this->field_61C = p5;

    // Set global manager pointers
    gbVertexPool::pGfxMgr = mgr;
    g_gbDynVertBuf_pGfxMgr = mgr;

    // Zero out FVF and pointer arrays
    for (int i = 0; i < 32; i++) {
        this->vertPoolFVFs[i] = 0;
        this->dynVertBufs[i] = NULL;
        this->dynVertBufFVFs[i] = 0;
        this->srcVertPoolFVFs[i] = 0;
    }
}

// Destructor: 0x100211a0
gbVertPoolMgr::~gbVertPoolMgr() {
    // Clean up all dynamic vert bufs
    for (int i = 0; i < 32; i++) {
        if (this->dynVertBufs[i]) {
            delete this->dynVertBufs[i];
        }
    }
}

// OnLostDevice: 0x10021240 (47B)
int gbVertPoolMgr::OnLostDevice() {
    int i = 0;
    do {
        if (dynVertBufs[i] != NULL) {
            // Call virtual method vtable[1] = OnLostDevice
            void** vtbl = *(void***)dynVertBufs[i];
            typedef int (*VFunc)(void*);
            if (((VFunc)vtbl[1])(dynVertBufs[i]) == 0) {
                return 0;
            }
        }
        i++;
    } while (i < 32);
    return 1;
}

// OnResetDevice: 0x10021270 (47B)
int gbVertPoolMgr::OnResetDevice() {
    int i = 0;
    do {
        if (dynVertBufs[i] != NULL) {
            // Call virtual method vtable[2] = OnResetDevice
            void** vtbl = *(void***)dynVertBufs[i];
            typedef int (*VFunc)(void*);
            if (((VFunc)vtbl[2])(dynVertBufs[i]) == 0) {
                return 0;
            }
        }
        i++;
    } while (i < 32);
    return 1;
}


// NewVertexBubble: 0x100212e0 (182B)
gbVertexBubble* gbVertPoolMgr::NewVertexBubble(unsigned int fvf, int count) {
    int i;
    gbVertexPool* pool;
    gbVertexBubble* result;
    gbChain1D* chain;

    // Update stat counter
    *(int*)((char*)pGfxManager + 0x210) += count;

    // Find pool index by matching FVF
    i = 0;
    do {
        if (vertPoolFVFs[i] == fvf) goto found;
        i++;
    } while (i < 32);

    // Not found - find empty slot and register
    i = 0;
    do {
        if (vertPoolFVFs[i] == 0) {
            vertPoolFVFs[i] = fvf;
            goto found;
        }
        i++;
    } while (i < 32);

    i = -1;

found:
    chain = &StaticPool[i];
    pool = (gbVertexPool*)chain->pHead;
    chain->pIterator = (gbChain1DNode*)pool;

    while (pool) {
        result = pool->NewBubble(count);
        if (result) return result;
        pool = (gbVertexPool*)chain->pIterator->pNext;
        chain->pIterator = (gbChain1DNode*)pool;
    }

    // No existing pool has space - create new one
    if (maxVertexPoolSize < count) {
        maxVertexPoolSize = count;
    }

    pool = (gbVertexPool*)pGfxManager->NewVertexPool(0, fvf, maxVertexPoolSize);

    chain->AddNode((gbChain1DNode*)pool);

    return pool->NewBubble(count);
}

// DelVertexBubble: 0x100213a0 (144B)
void gbVertPoolMgr::DelVertexBubble(gbVertexBubble* bubble) {
    int i;
    gbVertexPool* pool;

    // Update stat counter: pGfxManager->Stat.nStaticVertex -= bubble->vertexCount
    *(int*)((char*)pGfxManager + 0x210) -= bubble->vertexCount;

    pool = bubble->pPool;

    // Find pool index by matching FVF
    i = 0;
    do {
        if (vertPoolFVFs[i] == pool->fvf) goto found;
        i++;
    } while (i < 32);

    // Not found - find empty slot and register
    i = 0;
    do {
        if (vertPoolFVFs[i] == 0) {
            vertPoolFVFs[i] = pool->fvf;
            goto found;
        }
        i++;
    } while (i < 32);

    i = -1;

found:
    pool->DelBubble(bubble);

    // If pool is now empty, remove and delete it
    if (pool->usedList[0] == 0) {
        StaticPool[i].DelNodeFromChain((gbChain1DNode*)pool);
        if (pool) {
            delete pool;
        }
    }
}

// NewSrcVertBub: 0x10021430 (185B)
gbVertexBubble* gbVertPoolMgr::NewSrcVertBub(unsigned int fvf, int count) {
    int i;
    gbVertexPool* pool;
    gbVertexBubble* result;
    gbChain1D* chain;

    // Update stat counter
    *(int*)((char*)pGfxManager + 0x218) += count;

    // Find pool index by matching FVF
    i = 0;
    do {
        if (srcVertPoolFVFs[i] == fvf) goto found;
        i++;
    } while (i < 32);

    // Not found - find empty slot and register
    i = 0;
    do {
        if (srcVertPoolFVFs[i] == 0) {
            srcVertPoolFVFs[i] = fvf;
            goto found;
        }
        i++;
    } while (i < 32);

    i = -1;

found:
    chain = &srcVertPoolChains[i];
    pool = (gbVertexPool*)chain->pHead;
    chain->pIterator = (gbChain1DNode*)pool;

    while (pool) {
        result = pool->NewBubble(count);
        if (result) return result;
        pool = (gbVertexPool*)chain->pIterator->pNext;
        chain->pIterator = (gbChain1DNode*)pool;
    }

    // No existing pool has space - create new one
    if (field_61C < count) {
        field_61C = count;
    }

    pool = (gbVertexPool*)pGfxManager->NewVertexPool(2, fvf, field_61C);

    chain->AddNode((gbChain1DNode*)pool);

    return pool->NewBubble(count);
}

// DelSrcVertBub: 0x100214f0 (145B)
void gbVertPoolMgr::DelSrcVertBub(gbVertexBubble* bubble) {
    int i;
    gbVertexPool* pool;

    // Update stat counter: pGfxManager->Stat.nSrcVertex -= bubble->vertexCount
    *(int*)((char*)pGfxManager + 0x218) -= bubble->vertexCount;

    pool = bubble->pPool;

    // Find pool index by matching FVF
    i = 0;
    do {
        if (srcVertPoolFVFs[i] == pool->fvf) goto found;
        i++;
    } while (i < 32);

    // Not found - find empty slot and register
    i = 0;
    do {
        if (srcVertPoolFVFs[i] == 0) {
            srcVertPoolFVFs[i] = pool->fvf;
            goto found;
        }
        i++;
    } while (i < 32);

    i = -1;

found:
    pool->DelBubble(bubble);

    // If pool is now empty, remove and delete it
    if (pool->usedList[0] == 0) {
        srcVertPoolChains[i].DelNodeFromChain((gbChain1DNode*)pool);
        if (pool) {
            delete pool;
        }
    }
}

// NewIndexBubble: 0x10021590 (135B)
gbIndexBubble* gbVertPoolMgr::NewIndexBubble(gbPrimType prim, int count) {
    gbIndexPool* pool;
    gbIndexBubble* result;

    // Update stat counter
    *(int*)((char*)pGfxManager + 0x214) += count;

    pool = (gbIndexPool*)indexPoolList.pHead;
    indexPoolList.pIterator = (gbChain1DNode*)pool;

    while (pool) {
        result = pool->NewBubble(prim, count);
        if (result) return result;
        pool = (gbIndexPool*)indexPoolList.pIterator->pNext;
        indexPoolList.pIterator = (gbChain1DNode*)pool;
    }

    // No existing pool has space - create new one
    if (maxIndexPoolSize < count) {
        maxIndexPoolSize = count;
    }

    pool = (gbIndexPool*)pGfxManager->NewIndexPool(0, 2, maxIndexPoolSize);

    indexPoolList.AddNode((gbChain1DNode*)pool);

    return pool->NewBubble(prim, count);
}

// DelIndexBubble: 0x10021620 (85B)
void gbVertPoolMgr::DelIndexBubble(gbIndexBubble* bubble) {
    gbIndexPool* pool;

    // Update stat counter: pGfxManager->Stat.nStaticIndex -= bubble->count
    *(int*)((char*)pGfxManager + 0x214) -= bubble->count;

    pool = bubble->pPool;
    pool->DelBubble(bubble);

    // If pool is now empty, remove and delete it
    if (pool->usedList[0] == 0) {
        indexPoolList.DelNodeFromChain((gbChain1DNode*)pool);
        if (pool) {
            delete pool;
        }
    }
}

// GetDynVertBuf: 0x10021680 (121B)
gbDynVertBuf* gbVertPoolMgr::GetDynVertBuf(unsigned int fvf) {
    int i;

    // Search for existing entry with matching FVF
    i = 0;
    do {
        if (dynVertBufFVFs[i] == fvf) goto found;
        i++;
    } while (i < 32);

    // Not found - find empty slot
    i = 0;
    do {
        if (dynVertBufFVFs[i] == 0) {
            dynVertBufFVFs[i] = fvf;
            goto found;
        }
        i++;
    } while (i < 32);

    i = -1;

found:
    if (dynVertBufs[i] == NULL) {
        dynVertBufs[i] = (gbDynVertBuf*)pGfxManager->NewDynVertBuf(fvf, field_618);
        g_gbDynVertBuf_pGfxMgr = pGfxManager;
    }
    return dynVertBufs[i];
}

// operator=: 0x100040b0
gbVertPoolMgr& gbVertPoolMgr::operator=(const gbVertPoolMgr& other) {
    memcpy(this, &other, sizeof(gbVertPoolMgr));
    return *this;
}
