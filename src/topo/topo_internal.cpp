/**
 * topo.dll - Internal TopoGeom implementation
 *
 * Matching decompilation of topo.dll internal functions.
 * Compiler: MSVC 6.0 SP5, /O2
 *
 * These are the private implementation details used by CreateTopoGeom:
 *   - TopoGeom_Init (FUN_100066f0): main object initializer
 *   - TopoMeshData_Init (FUN_10006590): vertex data initializer
 *   - TopoFaceVector_Size (FUN_10008820): element count query
 *   - TopoFaceVector_Insert (FUN_10008940): insert elements (with realloc)
 *   - TopoFaceVector_Erase (FUN_10008c10): erase range of elements
 *
 * Memory layouts:
 *
 * TopoGeom (object at 'this'):
 *   +0x00: vtable pointer
 *   +0x04: type
 *   +0x08: TopoFaceVector.pBegin  (face data start)
 *   +0x0C: TopoFaceVector.pEnd    (face data end = begin + count * 0x30)
 *   +0x10: TopoFaceVector.pAlloc  (allocated end)
 *   +0x14: TopoMeshData* (0x34-byte mesh data object)
 *
 * TopoFaceVector (embedded at this+0x04):
 *   +0x00 (this+0x04): pBegin  -- pointer to first element
 *   +0x04 (this+0x08): pEnd    -- pointer past last element
 *   +0x08 (this+0x0C): pAlloc  -- end of allocated buffer
 *   Element size: 0x30 bytes (48 bytes) per face
 *
 * TopoFace (0x30 bytes per face):
 *   +0x00: int idx[3]     (vertex indices, 3 ints = 12 bytes)
 *   +0x0C: int adj[3][2]  (adjacency data, 3 pairs = 24 bytes, init to -1)
 *   +0x24: int extra[3]   (additional data, 12 bytes)
 *
 * TopoMeshData (0x34 bytes, allocated with operator new):
 *   +0x00: void *pVertexBuffer
 *   +0x04: int vertexStride
 *   +0x08: int vertexFlags
 *   +0x0C: int field_0C (copied from desc+0x0C..0x1B, 4 dwords)
 *   +0x10: int field_10
 *   +0x14: int field_14
 *   +0x18: int field_18
 *   +0x1C: int field_1C
 *   +0x20: int bufferRowSize
 *   +0x24: int vertexCount
 *   +0x28: int allocRowCount (min 16)
 *   +0x2C: int field_2C
 *   +0x30: int field_30
 *
 * TopoDataDesc (input descriptor, int*-based offsets):
 *   [0]  +0x00: void *pVertexData
 *   [1]  +0x04: int vertexStride
 *   [2]  +0x08: int vertexFlags
 *   [3]  +0x0C: int desc_0C
 *   [4]  +0x10: int desc_10
 *   [5]  +0x14: int desc_14
 *   [6]  +0x18: int desc_18
 *   [7]  +0x1C: int desc_1C
 *   [8]  +0x20: int bufferRowSize
 *   [9]  +0x24: int vertexCount
 *   [10] +0x28: unsigned short *pIndices16 (16-bit index buffer)
 *   [11] +0x2C: unsigned int *pIndices32 (32-bit index buffer)
 *   [12] +0x30: int faceCount
 *   [13] +0x34: int field_34
 *   [14] +0x38: int field_38
 */

#include "pal3.h"
#include <string.h>

// CRT
extern "C" void *operator new(unsigned int size);
extern "C" void operator delete(void *p);
extern "C" void *malloc(unsigned int size);
extern "C" void free(void *p);

// FUN_10009960: copy 0x30 bytes (one face entry) from src to dst
// Used as element assignment in the vector operations
extern void __fastcall TopoFace_Assign(void *dst, int src);

// FUN_10009c7b: operator delete wrapper
extern void __cdecl operator_delete_wrapper(void *p);

// ============================================================================
// 0x10008820  TopoFaceVector_Size  (33 bytes)
// int __fastcall TopoFaceVector_Size(int this)
//
// Returns the number of face elements (each 0x30 bytes) in the vector.
// Vector layout: this+0x04=pBegin, this+0x08=pEnd
// ============================================================================
int __fastcall TopoFaceVector_Size(void *pThis)
{
    int pBegin = *(int *)((int)pThis + 0x04);
    if (pBegin == 0) {
        return 0;
    }
    return (*(int *)((int)pThis + 0x08) - pBegin) / 0x30;
}

// ============================================================================
// 0x10008c10  TopoFaceVector_Erase  (162 bytes)
// undefined4 * __thiscall TopoFaceVector_Erase(void *this, undefined4 *param_1, undefined4 *param_2)
//
// Erases elements in range [param_1, param_2) by moving elements after param_2
// forward into the gap. Each element is 0x30 bytes (12 dwords).
// The move is done element-by-element, with the source at a fixed offset
// from destination (the gap size = param_2 - param_1).
// ============================================================================
int *__fastcall TopoFaceVector_Erase(void *pThis, int edx, int *pFirst, int *pLast)
{
    int *pEnd = *(int **)((int)pThis + 0x08);
    int *pDst = pFirst;

    if (pLast != pEnd) {
        int *pNextSrc = (int *)((char *)pLast + 0x2C);  /* pLast + 11 dwords */
        do {
            int iVar4 = 3;
            int offset = (int)pNextSrc + (-0x2C - (int)pDst);
            int *pCopy = pDst;
            do {
                *pCopy = *(int *)(offset + (int)pCopy);
                pCopy++;
                iVar4--;
            } while (iVar4 != 0);
            int *pCopy2 = pDst + 3;
            iVar4 = 3;
            do {
                *pCopy2 = *(int *)((int)pCopy2 + offset);
                pCopy2[1] = *(int *)((int)pCopy2 + offset + 4);
                pCopy2 += 2;
                iVar4--;
            } while (iVar4 != 0);
            pDst[9] = pNextSrc[-2];
            pDst[10] = pNextSrc[-1];
            int *pNext = pNextSrc + 1;
            *(int *)((int)pFirst + (-0x30 - (int)pLast) + (int)(pNextSrc + 0xC)) = *pNextSrc;
            pDst = pDst + 0xC;
            pNextSrc = pNextSrc + 0xC;
        } while (pNext != pEnd);
    }
    *(int **)((int)pThis + 0x08) = pDst;
    return pFirst;
}

// ============================================================================
// 0x10008940  TopoFaceVector_Insert  (714 bytes)
// void __thiscall TopoFaceVector_Insert(void *this, undefined4 *param_1, uint param_2, undefined4 *param_3)
//
// Inserts param_2 copies of param_3 (0x30 bytes each) at position param_1.
// May reallocate if needed. This is a complex STL-like vector::insert.
// Due to complexity (714 bytes, multiple branches), declared as extern.
// ============================================================================
extern void __fastcall TopoFaceVector_Insert(void *pThis, int edx,
    int *pPos, unsigned int count, int *pValue);

// ============================================================================
// 0x10006590  TopoMeshData_Init  (316 bytes)
// void __thiscall TopoMeshData_Init(void *this, int *param_1)
//
// Initializes a TopoMeshData object from a TopoDataDesc descriptor.
// Allocates vertex buffer and copies vertex data.
// ============================================================================
void __fastcall TopoMeshData_Init(void *pThis, int edx, int *pDesc)
{
    int vertexCount = pDesc[9];                     /* desc+0x24 */
    *(int *)((int)pThis + 0x24) = vertexCount;
    int bufRowSize = pDesc[8];                      /* desc+0x20 */
    *(int *)((int)pThis + 0x20) = bufRowSize;

    int allocRows = vertexCount;
    if (vertexCount < 0x10) {
        allocRows = 0x10;
    }
    *(int *)((int)pThis + 0x28) = allocRows;

    *(int *)((int)pThis + 0x04) = pDesc[1];         /* vertexStride */
    int vertexFlags = pDesc[2];                     /* vertexFlags */
    *(int *)((int)pThis + 0x08) = vertexFlags;

    /* Copy 4 dwords from desc+0x0C to this+0x0C */
    int *pDst = (int *)((int)pThis + 0x0C);
    int offset = (int)pDesc - (int)pThis;
    int n = 4;
    do {
        *pDst = *(int *)(offset + (int)pDst);
        pDst++;
        n--;
    } while (n != 0);

    *(int *)((int)pThis + 0x1C) = pDesc[7];         /* desc+0x1C */

    if (vertexFlags >= 0) {
        /* Normal path: allocate rowSize * allocRows, copy rowSize * vertexCount bytes */
        void *buf = malloc(*(int *)((int)pThis + 0x20) * *(int *)((int)pThis + 0x28));
        *(void **)pThis = buf;

        unsigned int copySize = (unsigned int)(*(int *)((int)pThis + 0x20) * *(int *)((int)pThis + 0x24));
        int *pSrc = (int *)pDesc[0];
        int *pCopyDst = (int *)buf;

        /* REP MOVSD + REP MOVSB */
        unsigned int dwords = copySize >> 2;
        unsigned int bytes = copySize & 3;
        while (dwords != 0) { *pCopyDst = *pSrc; pSrc++; pCopyDst++; dwords--; }
        char *pByteSrc = (char *)pSrc;
        char *pByteDst = (char *)pCopyDst;
        while (bytes != 0) { *pByteDst = *pByteSrc; pByteSrc++; pByteDst++; bytes--; }

        *(int *)((int)pThis + 0x2C) = pDesc[0xD];   /* desc+0x34 */
        *(int *)((int)pThis + 0x30) = pDesc[0xE];   /* desc+0x38 */
        return;
    }

    /* Negative flags path: expand vertex rows by inserting 12 extra bytes per row */
    int newRowSize = *(int *)((int)pThis + 0x20) + 0x0C;
    *(int *)((int)pThis + 0x20) = newRowSize;

    void *buf = malloc(newRowSize * *(int *)((int)pThis + 0x28));
    *(void **)pThis = buf;

    int idx = 0;
    if (vertexCount > 0) {
        do {
            char *pDstRow = (char *)*(int *)pThis + *(int *)((int)pThis + 0x20) * idx;
            int stride = *(int *)((int)pThis + 0x04);
            unsigned int copyLen = stride + 0x0C;
            char *pSrcRow = (char *)pDesc[0] + pDesc[8] * idx;

            /* Copy first (stride + 12) bytes: REP MOVSD + REP MOVSB */
            int *pd = (int *)pDstRow;
            int *ps = (int *)pSrcRow;
            unsigned int dw = copyLen >> 2;
            unsigned int byt = copyLen & 3;
            while (dw != 0) { *pd = *ps; ps++; pd++; dw--; }
            char *pbd = (char *)pd;
            char *pbs = (char *)ps;
            while (byt != 0) { *pbd = *pbs; pbs++; pbd++; byt--; }

            /* Copy remaining bytes (original row - stride - 12) if any */
            unsigned int remaining = (unsigned int)(pDesc[8] - stride - 0x0C);
            if (remaining != 0) {
                char *pSrc2 = (char *)pSrcRow + stride + 0x0C;
                char *pDst2 = (char *)pDstRow + stride + 0x18;

                int *pd2 = (int *)pDst2;
                int *ps2 = (int *)pSrc2;
                unsigned int dw2 = remaining >> 2;
                unsigned int byt2 = remaining & 3;
                while (dw2 != 0) { *pd2 = *ps2; ps2++; pd2++; dw2--; }
                char *pbd2 = (char *)pd2;
                char *pbs2 = (char *)ps2;
                while (byt2 != 0) { *pbd2 = *pbs2; pbs2++; pbd2++; byt2--; }
            }

            idx++;
        } while (idx < *(int *)((int)pThis + 0x24));
    }

    *(int *)((int)pThis + 0x08) = *(int *)((int)pThis + 0x04) + 0x0C;
    *(int *)((int)pThis + 0x2C) = pDesc[0xD];       /* desc+0x34 */
    *(int *)((int)pThis + 0x30) = pDesc[0xE];       /* desc+0x38 */
}

// ============================================================================
// 0x100066f0  TopoGeom_Init  (394 bytes)
// undefined4 __thiscall TopoGeom_Init(void *this, int *param_1)
//
// Main TopoGeom initializer called by CreateTopoGeom factory.
// 1. Allocates a 0x34-byte TopoMeshData object and stores at this+0x14
// 2. Calls TopoMeshData_Init to parse vertex data from descriptor
// 3. Resizes the face vector to match descriptor's faceCount
// 4. Fills face indices from either 16-bit or 32-bit index buffers
// 5. Initializes adjacency data to 0xFFFFFFFF (-1)
// Returns 1 on completion.
// ============================================================================
int __fastcall TopoGeom_Init(void *pThis, int edx, int *pDesc)
{
    int *pMesh;
    unsigned int faceCount;
    unsigned int curSize;
    int local_30[9];
    int local_c;
    int local_8;
    int local_4;

    /* Allocate and init TopoMeshData */
    pMesh = (int *)operator new(0x34);
    if (pMesh != NULL) {
        pMesh[0] = 0;
        pMesh[10] = 0;  /* +0x28 */
        pMesh[9] = 0;   /* +0x24 */
    } else {
        pMesh = NULL;
    }
    *(int **)((int)pThis + 0x14) = pMesh;

    /* Initialize mesh data from descriptor */
    TopoMeshData_Init(pMesh, 0, pDesc);

    /* Get face vector info */
    int pBegin = *(int *)((int)pThis + 0x08);
    faceCount = (unsigned int)pDesc[0x0C];           /* desc+0x30 = faceCount */
    void *pVec = (void *)((int)pThis + 0x04);        /* face vector at this+0x04 */

    local_c = 0;
    local_8 = 0;
    local_4 = 0;

    /* Compute current size */
    if (pBegin == 0) {
        curSize = 0;
    } else {
        curSize = (unsigned int)((*(int *)((int)pThis + 0x0C) - pBegin) / 0x30);
    }

    if (curSize < faceCount) {
        /* Need to grow: insert (faceCount - curSize) elements at end */
        int sizeNow;
        if (pBegin == 0) {
            sizeNow = 0;
        } else {
            sizeNow = (*(int *)((int)pThis + 0x0C) - pBegin) / 0x30;
        }
        TopoFaceVector_Insert(pVec, 0,
            *(int **)((int)pThis + 0x0C),            /* insert at pEnd */
            faceCount - sizeNow, local_30);
    } else {
        /* May need to shrink */
        unsigned int existingSize = (unsigned int)TopoFaceVector_Size(pVec);
        if (faceCount < existingSize) {
            TopoFaceVector_Erase(pVec, 0,
                (int *)(faceCount * 0x30 + *(int *)((int)pThis + 0x08)),
                *(int **)((int)pThis + 0x0C));
        }
    }

    /* Fill face data from index buffer */
    int nFaces = pDesc[0x0C];               /* faceCount at desc+0x30 */
    int iCounter = 0;
    int idx16Ofs = 0;                       /* EBX: advances by 6 per face */
    int faceOfs = 0;                        /* EAX: advances by 0x30 per face */
    int idx32Ofs = 0;                       /* ECX on stack: advances by 0x0C */

    if (nFaces > 0) {
        do {
            if (pDesc[10] != 0) {
                /* 16-bit indices (desc+0x28 = pIndices16) */
                unsigned short *pIdx16 = (unsigned short *)pDesc[10];
                unsigned int i0 = (unsigned int)*(unsigned short *)((char *)pIdx16 + idx16Ofs);
                unsigned int i1 = (unsigned int)*(unsigned short *)((char *)pIdx16 + idx16Ofs + 2);
                unsigned int i2 = (unsigned int)*(unsigned short *)((char *)pIdx16 + idx16Ofs + 4);
                int base = *(int *)((int)pThis + 0x08);
                *(unsigned int *)(base + faceOfs) = i0;
                *(unsigned int *)(base + faceOfs + 4) = i1;
                *(unsigned int *)(base + faceOfs + 8) = i2;
            } else {
                /* 32-bit indices (desc+0x2C = pIndices32) */
                int *pIdx32 = (int *)pDesc[11];
                int base = *(int *)((int)pThis + 0x08);
                *(int *)(base + faceOfs) = *(int *)((char *)pIdx32 + idx32Ofs);
                *(int *)(base + faceOfs + 4) = *(int *)((char *)pIdx32 + idx32Ofs + 4);
                *(int *)(base + faceOfs + 8) = *(int *)((char *)pIdx32 + idx32Ofs + 8);
            }

            /* Initialize adjacency to -1: offsets +0x0C, +0x14, +0x1C within face */
            int adjOfs = faceOfs;
            int n = 3;
            do {
                int pBase2 = *(int *)((int)pThis + 0x08);
                adjOfs += 8;
                n--;
                *(int *)(adjOfs + pBase2 + 4) = (int)0xFFFFFFFF;
            } while (n != 0);

            iCounter++;
            idx16Ofs += 6;
            idx32Ofs += 0x0C;
            faceOfs += 0x30;
        } while (iCounter < pDesc[0x0C]);
    }

    return 1;
}
