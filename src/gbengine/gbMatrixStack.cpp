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
    memcpy(&pStack[curDepth + 1], &pStack[curDepth], 0x40);
    curDepth++;
}

void gbMatrixStack::Pop(void)
{
    dirty = 0;
    curDepth--;
}

void gbMatrixStack::LoadIdentity(void)
{
    float* m = (float*)&pStack[curDepth];
    memset(m, 0, 0x40);
    m[15] = 1.0f;
    m[10] = 1.0f;
    m[5] = 1.0f;
    m[0] = 1.0f;
    dirty = 0;
}

void gbMatrixStack::LoadMatrix(gbMatrix4 *mat)
{
    memcpy(&pStack[curDepth], mat, 0x40);
    dirty = 0;
}

void gbMatrixStack::MultMatrix(gbMatrix4 *mat)
{
    float* dst = (float*)((char*)pStack + (curDepth << 6));
    float temp[16];
    int offset;
    int row;
    float* pRow;
    float* pOut;
    int col;
    float* pMat;
    float* pTmp;
    int k;
    float sum;

    offset = (int)dst - (int)mat;
    row = 4;
    memcpy(temp, dst, 0x40);
    for (;;) {
        pRow = temp;
        pOut = (float*)((char*)mat + offset);
        col = 4;
        do {
            *pOut = 0.0f;
            pMat = (float*)mat;
            pTmp = pRow;
            k = 4;
            do {
                sum = *pMat * *pTmp;
                pTmp += 4;
                ++pMat;
                --k;
                *pOut = sum + *pOut;
            } while (k);
            ++pOut;
            ++pRow;
            --col;
        } while (col);
        mat = (gbMatrix4*)((char*)mat + 16);
        if (!--row)
            break;
        offset = (int)dst - (int)mat;
    }
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
    pStack[curDepth] *= q;
    dirty = 0;
}

void gbMatrixStack::Translate(gbVec3D &v)
{
    float* m = (float*)&pStack[curDepth];
    m[12] = m[4] * v.y + m[8] * v.z + m[0] * v.x + m[12];
    m[13] = m[5] * v.y + m[1] * v.x + m[9] * v.z + m[13];
    m[14] = m[6] * v.y + m[2] * v.x + m[10] * v.z + m[14];
    dirty = 0;
}

void gbMatrixStack::Translate(float x, float y, float z)
{
    float* m = (float*)&pStack[curDepth];
    m[12] = y * m[4] + z * m[8] + x * m[0] + m[12];
    m[13] = x * m[1] + y * m[5] + z * m[9] + m[13];
    m[14] = x * m[2] + y * m[6] + z * m[10] + m[14];
    dirty = 0;
}

void gbMatrixStack::Scale(gbVec3D &v)
{
    float sz = v.z;
    float sy = v.y;
    float sx = v.x;
    float* m = (float*)&pStack[curDepth];
    m[0] = sx * m[0];
    m[1] = sx * m[1];
    m[2] = sx * m[2];
    m[4] = sy * m[4];
    m[5] = sy * m[5];
    m[6] = sy * m[6];
    m[8] = sz * m[8];
    m[9] = sz * m[9];
    m[10] = sz * m[10];
    dirty = 0;
}

void gbMatrixStack::Scale(float sx, float sy, float sz)
{
    float* m = (float*)&pStack[curDepth];
    m[0] = sx * m[0];
    m[1] = sx * m[1];
    m[2] = sx * m[2];
    m[4] = sy * m[4];
    m[5] = sy * m[5];
    m[6] = sy * m[6];
    m[8] = sz * m[8];
    m[9] = sz * m[9];
    m[10] = sz * m[10];
    dirty = 0;
}

gbMatrix4 *gbMatrixStack::GetTop(void)
{
    return &pStack[curDepth];
}

int gbMatrixStack::GetDepth(void)
{
    return curDepth;
}
