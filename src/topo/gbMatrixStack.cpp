/**
 * gbMatrixStack - Matrix stack class implementation
 *
 * Matching decompilation of topo.dll gbMatrixStack methods.
 * Compiler: MSVC 6.0 SP5, /O2
 *
 * Verified against: topo.dll (ImageBase 0x10000000)
 *
 * Memory layout (16 bytes):
 *   +0x00: gbMatrix4 *pStack   (pointer to array of matrices)
 *   +0x04: int maxDepth         (max number of matrices allocated)
 *   +0x08: int curDepth          (current stack index)
 *   +0x0C: int dirty            (invalidation flag, cleared on modification)
 *
 * The stack is an array of gbMatrix4 (64 bytes each).
 * pStack[curDepth] is the current "top" matrix.
 */

#include "pal3.h"
#include <string.h>

// Memory allocation functions
extern void *operator new(unsigned int size);
extern void operator delete(void *p);

// ============================================================================
// 0x10002D50  gbMatrixStack(int)  (139 bytes)
// public: __thiscall gbMatrixStack::gbMatrixStack(int)
//
// Allocates a stack of 'depth' matrices, initializes top to identity.
// ============================================================================
gbMatrixStack::gbMatrixStack(int depth)
{
    maxDepth = depth;
    curDepth = 0;
    gbMatrix4 *buf = (gbMatrix4 *)operator new(depth << 6);
    if (buf != NULL) {
        gbMatrix4 *p = buf;
        int n = depth;
        if (n > 0) {
            do {
                p->LoadIdentity();  /* gbMatrix4 constructor calls LoadIdentity */
                n--;
                p = (gbMatrix4 *)((char *)p + 0x40);
            } while (n != 0);
        }
    } else {
        buf = NULL;
    }
    pStack = buf;
    pStack[curDepth].LoadIdentity();
    dirty = 0;
}

// ============================================================================
// 0x10002DE0  ~gbMatrixStack  (10 bytes)
// public: __thiscall gbMatrixStack::~gbMatrixStack(void)
// ============================================================================
gbMatrixStack::~gbMatrixStack(void)
{
    operator delete(pStack);
}

// ============================================================================
// 0x100019F0  operator=  (35 bytes)
// public: class gbMatrixStack & __thiscall gbMatrixStack::operator=(class gbMatrixStack const &)
// Note: Shared code with gbQuaternion::operator= (ICF)
// ============================================================================
gbMatrixStack &gbMatrixStack::operator=(const gbMatrixStack &other)
{
    *(int *)((char *)this + 0x00) = *(int *)((char *)&other + 0x00);
    *(int *)((char *)this + 0x04) = *(int *)((char *)&other + 0x04);
    *(int *)((char *)this + 0x08) = *(int *)((char *)&other + 0x08);
    *(int *)((char *)this + 0x0C) = *(int *)((char *)&other + 0x0C);
    return *this;
}

// ============================================================================
// 0x10002DF0  Push  (41 bytes)
// public: void __thiscall gbMatrixStack::Push(void)
//
// Copies current top matrix to next slot, increments depth.
// ============================================================================
void gbMatrixStack::Push(void)
{
    float *pSrc = (float *)&pStack[curDepth];
    float *pDst = (float *)&pStack[curDepth + 1];
    int i;
    for (i = 16; i != 0; i--) {
        *pDst = *pSrc;
        pSrc++;
        pDst++;
    }
    curDepth++;
}

// ============================================================================
// 0x10002E20  Pop  (15 bytes)
// public: void __thiscall gbMatrixStack::Pop(void)
//
// Decrements stack depth, clears dirty flag.
// ============================================================================
void gbMatrixStack::Pop(void)
{
    dirty = 0;
    curDepth--;
}

// ============================================================================
// 0x10002E30  LoadIdentity  (27 bytes)
// public: void __thiscall gbMatrixStack::LoadIdentity(void)
// ============================================================================
void gbMatrixStack::LoadIdentity(void)
{
    pStack[curDepth].LoadIdentity();
    dirty = 0;
}

// ============================================================================
// 0x10002E50  LoadMatrix  (37 bytes)
// public: void __thiscall gbMatrixStack::LoadMatrix(struct gbMatrix4 *)
//
// Copies 16 floats from the given matrix to the top of stack.
// ============================================================================
void gbMatrixStack::LoadMatrix(gbMatrix4 *mat)
{
    float *pSrc = (float *)mat;
    float *pDst = (float *)&pStack[curDepth];
    int i;
    for (i = 16; i != 0; i--) {
        *pDst = *pSrc;
        pSrc++;
        pDst++;
    }
    dirty = 0;
}

// ============================================================================
// 0x10002E80  MultMatrix  (34 bytes)
// public: void __thiscall gbMatrixStack::MultMatrix(struct gbMatrix4 *)
//
// Left-multiplies the top matrix by the given matrix.
// ============================================================================
void gbMatrixStack::MultMatrix(gbMatrix4 *mat)
{
    pStack[curDepth].LeftMultiply(*mat);
    dirty = 0;
}

// ============================================================================
// 0x10002EB0  Rotate(float, gbVec3D&)  (68 bytes)
// public: void __thiscall gbMatrixStack::Rotate(float,struct gbVec3D &)
//
// Creates a rotation matrix from axis/angle, left-multiplies top.
// ============================================================================
void gbMatrixStack::Rotate(float angle, gbVec3D &axis)
{
    gbMatrix4 rot;
    rot.SetAxisAngle(&axis, angle);
    pStack[curDepth].LeftMultiply(rot);
    dirty = 0;
}

// ============================================================================
// 0x10002F00  Rotate(gbQuaternion&)  (34 bytes)
// public: void __thiscall gbMatrixStack::Rotate(struct gbQuaternion &)
//
// Left-multiplies top by quaternion (converted to matrix internally).
// ============================================================================
void gbMatrixStack::Rotate(gbQuaternion &q)
{
    pStack[curDepth] *= q;
    dirty = 0;
}

// ============================================================================
// 0x10002F30  Translate(gbVec3D&)  (34 bytes)
// public: void __thiscall gbMatrixStack::Translate(struct gbVec3D &)
// ============================================================================
void gbMatrixStack::Translate(gbVec3D &v)
{
    pStack[curDepth].LeftTranslate(v);
    dirty = 0;
}

// ============================================================================
// 0x10002F90  Translate(float,float,float)  (44 bytes)
// public: void __thiscall gbMatrixStack::Translate(float,float,float)
// ============================================================================
void gbMatrixStack::Translate(float x, float y, float z)
{
    pStack[curDepth].LeftTranslate(x, y, z);
    dirty = 0;
}

// ============================================================================
// 0x10002F60  Scale(gbVec3D&)  (44 bytes)
// public: void __thiscall gbMatrixStack::Scale(struct gbVec3D &)
// ============================================================================
void gbMatrixStack::Scale(gbVec3D &v)
{
    pStack[curDepth].LeftScale(v.x, v.y, v.z);
    dirty = 0;
}

// ============================================================================
// 0x10002FC0  Scale(float,float,float)  (44 bytes)
// public: void __thiscall gbMatrixStack::Scale(float,float,float)
// ============================================================================
void gbMatrixStack::Scale(float sx, float sy, float sz)
{
    pStack[curDepth].LeftScale(sx, sy, sz);
    dirty = 0;
}

// ============================================================================
// 0x10002FF0  GetTop  (11 bytes)
// public: struct gbMatrix4 * __thiscall gbMatrixStack::GetTop(void)
// ============================================================================
gbMatrix4 *gbMatrixStack::GetTop(void)
{
    return &pStack[curDepth];
}
