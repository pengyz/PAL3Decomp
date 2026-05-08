/**
 * gbRotMatrix - 3x3 Rotation Matrix class implementation
 *
 * Matching decompilation of topo.dll gbRotMatrix methods.
 * Compiler: MSVC 6.0 SP5, /O2
 *
 * Verified against: topo.dll (ImageBase 0x10000000)
 *
 * Memory layout: float m[3][3] (36 bytes, row-major)
 *   m[0][0]=+0x00  m[0][1]=+0x04  m[0][2]=+0x08
 *   m[1][0]=+0x0C  m[1][1]=+0x10  m[1][2]=+0x14
 *   m[2][0]=+0x18  m[2][1]=+0x1C  m[2][2]=+0x20
 */

#include "pal3.h"
#include <math.h>
#include <string.h>

#define GB_FLOAT_EPSILON 0.005

// ============================================================================
// 0x100021F0  gbRotMatrix()  (12 bytes)
// public: __thiscall gbRotMatrix::gbRotMatrix(void)
// ============================================================================
#pragma inline_depth(0)
gbRotMatrix::gbRotMatrix(void)
{
    LoadIdentity();
}
#pragma inline_depth()

// ============================================================================
// 0x10002200  operator=  (27 bytes)
// public: void __thiscall gbRotMatrix::operator=(struct gbRotMatrix &)
//
// Copies 9 floats via a pointer loop. MSVC optimizes this into a
// single-pointer loop with a pre-computed src-dst offset.
// ============================================================================
void gbRotMatrix::operator=(gbRotMatrix &other)
{
    float *pSrc = (float *)&other;
    float *pDst = (float *)this;
    int i;
    for (i = 9; i != 0; i--) {
        *pDst = *pSrc;
        pDst++;
        pSrc++;
    }
}

// ============================================================================
// 0x10002220  operator*=  (126 bytes)
// public: void __thiscall gbRotMatrix::operator*=(struct gbRotMatrix &)
//
// Matrix multiply: this = this * other
// Copies this to temp first, then performs standard 3x3 product.
// ============================================================================
void gbRotMatrix::operator*=(gbRotMatrix &other)
{
    float temp[9];
    float *pSrc = (float *)this;
    float *pDst = temp;
    int i;

    for (i = 9; i != 0; i--) {
        *pDst = *pSrc;
        pSrc++;
        pDst++;
    }

    float *pRow = temp;
    int row = 3;
    do {
        float *pResult = (float *)this + (pRow - temp);
        float *pCol = (float *)&other;
        int col = 3;
        do {
            *pResult = 0.0f;
            float *pA = pRow;
            float *pB = pCol;
            int k = 3;
            do {
                float a = *pA;
                float b = *pB;
                pA++;
                pB += 3;
                k--;
                *pResult = a * b + *pResult;
            } while (k != 0);
            pResult++;
            pCol++;
            col--;
        } while (col != 0);
        pRow += 3;
        row--;
    } while (row != 0);
}

// ============================================================================
// 0x100022A0  Rotate  (81 bytes)
// public: void __thiscall gbRotMatrix::Rotate(struct gbVec3D *,struct gbVec3D *)
//
// Rotates input vector by this matrix: out = M^T * in
// (matrix stores basis vectors as rows, applies transpose)
// ============================================================================
void gbRotMatrix::Rotate(gbVec3D *in, gbVec3D *out)
{
    out->x = in->y * m[1][0] + in->z * m[2][0] + in->x * m[0][0];
    out->y = in->x * m[0][1] + in->y * m[1][1] + in->z * m[2][1];
    out->z = in->x * m[0][2] + in->y * m[1][2] + in->z * m[2][2];
}

// ============================================================================
// 0x10002300  LoadIdentity  (29 bytes)
// public: void __thiscall gbRotMatrix::LoadIdentity(void)
//
// Zeros all 9 floats via REP STOSD, then sets diagonal to 1.0f.
// Assignment order in binary: m[2][2], m[1][1], m[0][0] (compiler reorder).
// ============================================================================
void gbRotMatrix::LoadIdentity(void)
{
    memset(this, 0, sizeof(gbRotMatrix));
    m[2][2] = 1.0f;
    m[1][1] = 1.0f;
    m[0][0] = 1.0f;
}

// ============================================================================
// 0x10002320  IsValid  (42 bytes)
// public: bool const __thiscall gbRotMatrix::IsValid(void)
//
// Returns false if this==NULL or any element squared is negative (NaN check).
// Loops over all 9 floats.
// ============================================================================
bool gbRotMatrix::IsValid(void)
{
    if (this == NULL) return false;
    float *p = (float *)this;
    int i = 0;
    while (*p * *p >= 0.0f) {
        i++;
        p++;
        if (i > 8) {
            return true;
        }
    }
    return false;
}

// ============================================================================
// 0x10002350  IsOrthonormal  (308 bytes)
// public: bool const __thiscall gbRotMatrix::IsOrthonormal(void)
//
// Checks if the matrix is orthonormal by:
// 1. Extracting column vectors (col_x, col_y, col_z)
// 2. Normalizing col_z
// 3. Computing cross = col_x x col_y, normalizing it
// 4. Checking if cross ≈ ±col_z (within epsilon)
// ============================================================================
bool gbRotMatrix::IsOrthonormal(void)
{
    gbVec3D col_x, col_y, cross, col_z;

    col_x.x = m[0][0]; col_x.y = m[1][0]; col_x.z = m[2][0];
    col_y.x = m[0][1]; col_y.y = m[1][1]; col_y.z = m[2][1];
    col_z.x = m[0][2]; col_z.y = m[1][2]; col_z.z = m[2][2];
    cross.x = 0.0f;
    cross.y = 0.0f;
    cross.z = 0.0f;

    col_z.Normalize();
    col_x.CrossProduct(&col_y, &cross);
    cross.Normalize();

    if (fabs(cross.x - col_z.x) < GB_FLOAT_EPSILON &&
        fabs(cross.y - col_z.y) < GB_FLOAT_EPSILON &&
        fabs(cross.z - col_z.z) < GB_FLOAT_EPSILON) {
        return true;
    }

    col_z.x = -col_z.x;
    col_z.y = -col_z.y;
    col_z.z = -col_z.z;
    if (fabs(cross.x - col_z.x) < GB_FLOAT_EPSILON &&
        fabs(cross.y - col_z.y) < GB_FLOAT_EPSILON &&
        fabs(cross.z - col_z.z) < GB_FLOAT_EPSILON) {
        return true;
    }

    return false;
}
