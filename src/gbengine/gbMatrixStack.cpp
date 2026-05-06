/**
 * gbMatrixStack - Matrix stack class implementation
 *
 * Matching decompilation of gbengine.dll gbMatrixStack methods.
 * Compiler: MSVC 6.0 SP5, /O2
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

#include "gbengine/gbengine_internal.h"
#include <string.h>

extern void *operator new(unsigned int size);
extern void operator delete(void *p);

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
                p->LoadIdentity();
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

gbMatrixStack::~gbMatrixStack(void)
{
    /* STUB */
    operator delete(pStack);
}

gbMatrixStack &gbMatrixStack::operator=(const gbMatrixStack &other)
{
    pStack = other.pStack;
    maxDepth = other.maxDepth;
    curDepth = other.curDepth;
    dirty = other.dirty;
    return *this;
}

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

void gbMatrixStack::Pop(void)
{
    /* STUB */
    dirty = 0;
    curDepth--;
}

void gbMatrixStack::LoadIdentity(void)
{
    /* STUB */
    pStack[curDepth].LoadIdentity();
    dirty = 0;
}

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

void gbMatrixStack::MultMatrix(gbMatrix4 *mat)
{
    /* STUB */
    pStack[curDepth].LeftMultiply(*mat);
    dirty = 0;
}

void gbMatrixStack::Rotate(float angle, gbVec3D &axis)
{
    gbMatrix4 rot;
    rot.SetAxisAngle(&axis, angle);
    pStack[curDepth].LeftMultiply(rot);
    dirty = 0;
}

void gbMatrixStack::Rotate(gbQuaternion &q)
{
    /* STUB */
    pStack[curDepth] *= q;
    dirty = 0;
}

void gbMatrixStack::Translate(gbVec3D &v)
{
    /* STUB */
    pStack[curDepth].LeftTranslate(v);
    dirty = 0;
}

void gbMatrixStack::Translate(float x, float y, float z)
{
    /* STUB */
    pStack[curDepth].LeftTranslate(x, y, z);
    dirty = 0;
}

void gbMatrixStack::Scale(gbVec3D &v)
{
    /* STUB */
    pStack[curDepth].LeftScale(v.x, v.y, v.z);
    dirty = 0;
}

void gbMatrixStack::Scale(float sx, float sy, float sz)
{
    /* STUB */
    pStack[curDepth].LeftScale(sx, sy, sz);
    dirty = 0;
}

gbMatrix4 *gbMatrixStack::GetTop(void)
{
    /* STUB */
    return &pStack[curDepth];
}

int gbMatrixStack::GetDepth(void)
{
    return curDepth;
}
