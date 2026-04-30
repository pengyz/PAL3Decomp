/**
 * gbMatrix4 - 4x4 Matrix class implementation
 *
 * Matching decompilation of topo.dll gbMatrix4 methods.
 * Compiler: MSVC 6.0 SP5, /O2
 *
 * Verified against: topo.dll (ImageBase 0x10000000)
 *
 * Memory layout: float m[4][4] (64 bytes, row-major)
 *   Row 0: m[0][0]=+0x00  m[0][1]=+0x04  m[0][2]=+0x08  m[0][3]=+0x0C
 *   Row 1: m[1][0]=+0x10  m[1][1]=+0x14  m[1][2]=+0x18  m[1][3]=+0x1C
 *   Row 2: m[2][0]=+0x20  m[2][1]=+0x24  m[2][2]=+0x28  m[2][3]=+0x2C
 *   Row 3: m[3][0]=+0x30  m[3][1]=+0x34  m[3][2]=+0x38  m[3][3]=+0x3C
 *
 * Convention: vectors are transformed as out_j = sum_i(m[i][j] * in_i)
 * (equivalent to column-vector multiplication with the transpose)
 */

#include "pal3.h"
#include <math.h>
#include <string.h>

// ============================================================================
// 0x10001110  gbMatrix4()  (12 bytes)
// public: __thiscall gbMatrix4::gbMatrix4(void)
// ============================================================================
gbMatrix4::gbMatrix4(void)
{
    LoadIdentity();
}

// ============================================================================
// 0x10001120  operator=  (27 bytes)
// public: void __thiscall gbMatrix4::operator=(struct gbMatrix4 const &)
// ============================================================================
void gbMatrix4::operator=(const gbMatrix4 &other)
{
    float *pSrc = (float *)&other;
    float *pDst = (float *)this;
    int i;
    for (i = 16; i != 0; i--) {
        *pDst = *pSrc;
        pDst++;
        pSrc++;
    }
}

// ============================================================================
// 0x10001140  operator*= (gbMatrix4)  (122 bytes)
// public: void __thiscall gbMatrix4::operator*=(struct gbMatrix4 const &)
// Also: void __thiscall gbMatrix4::operator*=(float const *)
//
// Semantics: this = param * this (LEFT multiplication)
// Copies this to temp, then computes param * temp -> this
// ============================================================================
void gbMatrix4::operator*=(const gbMatrix4 &param)
{
    float temp[16];
    float *pSrc = (float *)this;
    float *pDst = temp;
    int i;

    for (i = 16; i != 0; i--) {
        *pDst = *pSrc;
        pSrc++;
        pDst++;
    }

    float *pOther = (float *)&param;
    int row = 4;
    do {
        float *pTemp = temp;
        float *pResult = (float *)this + (pOther - (float *)&param);
        int col = 4;
        do {
            *pResult = 0.0f;
            float *pB = pOther;
            float *pA = pTemp;
            int k = 4;
            do {
                float a = *pB;
                float b = *pA;
                pA += 4;
                pB++;
                k--;
                *pResult = a * b + *pResult;
            } while (k != 0);
            pResult++;
            pTemp++;
            col--;
        } while (col != 0);
        pOther += 4;
        row--;
    } while (row != 0);
}

// ============================================================================
// 0x100011C0  RightMultiply  (126 bytes)
// public: void __thiscall gbMatrix4::RightMultiply(struct gbMatrix4 const &)
//
// Semantics: this = this * param (RIGHT multiplication)
// Copies this to temp, then computes temp * param -> this
// ============================================================================
void gbMatrix4::RightMultiply(const gbMatrix4 &param)
{
    float temp[16];
    float *pSrc = (float *)this;
    float *pDst = temp;
    int i;

    for (i = 16; i != 0; i--) {
        *pDst = *pSrc;
        pSrc++;
        pDst++;
    }

    float *pRow = temp;
    int row = 4;
    do {
        float *pResult = (float *)this + (pRow - temp);
        float *pCol = (float *)&param;
        int col = 4;
        do {
            *pResult = 0.0f;
            float *pA = pRow;
            float *pB = pCol;
            int k = 4;
            do {
                float a = *pB;
                float b = *pA;
                pB += 4;
                pA++;
                k--;
                *pResult = a * b + *pResult;
            } while (k != 0);
            pResult++;
            pCol++;
            col--;
        } while (col != 0);
        pRow += 4;
        row--;
    } while (row != 0);
}

// ============================================================================
// 0x10001240  LeftMultiply  (13 bytes)
// public: void __thiscall gbMatrix4::LeftMultiply(struct gbMatrix4 const &)
//
// Wrapper: calls operator*= which does this = param * this
// ============================================================================
void gbMatrix4::LeftMultiply(const gbMatrix4 &param)
{
    *this *= param;
}

// ============================================================================
// 0x10001250  Transform(gbVec3D*, gbVec3D*)  (90 bytes)
// public: void __thiscall gbMatrix4::Transform(struct gbVec3D const *,struct gbVec3D *)const
//
// Transforms a point (applies rotation + translation):
// out_j = sum_i(m[i][j] * in_i) + m[3][j]
// ============================================================================
void gbMatrix4::Transform(const gbVec3D *in, gbVec3D *out) const
{
    out->x = in->y * m[1][0] + in->z * m[2][0] + in->x * m[0][0] + m[3][0];
    out->y = in->x * m[0][1] + in->y * m[1][1] + in->z * m[2][1] + m[3][1];
    out->z = in->x * m[0][2] + in->y * m[1][2] + in->z * m[2][2] + m[3][2];
}

// ============================================================================
// 0x100014F0  Rotate(gbVec3D*, gbVec3D*)  (81 bytes)
// public: void __thiscall gbMatrix4::Rotate(struct gbVec3D const *,struct gbVec3D *)const
//
// Rotates a vector (no translation, only upper-left 3x3):
// out_j = sum_i(m[i][j] * in_i)
// ============================================================================
void gbMatrix4::Rotate(const gbVec3D *in, gbVec3D *out) const
{
    out->x = in->y * m[1][0] + in->z * m[2][0] + in->x * m[0][0];
    out->y = in->x * m[0][1] + in->y * m[1][1] + in->z * m[2][1];
    out->z = in->x * m[0][2] + in->y * m[1][2] + in->z * m[2][2];
}

// ============================================================================
// 0x100015E0  LoadIdentity  (32 bytes)
// public: void __thiscall gbMatrix4::LoadIdentity(void)
// ============================================================================
void gbMatrix4::LoadIdentity(void)
{
    memset(this, 0, sizeof(gbMatrix4));
    m[0][0] = 1.0f;
    m[1][1] = 1.0f;
    m[2][2] = 1.0f;
    m[3][3] = 1.0f;
}

// ============================================================================
// 0x10001640  IsIdentity  (57 bytes)
// public: bool __thiscall gbMatrix4::IsIdentity(void)const
//
// Checks if the matrix is the identity matrix.
// Diagonal elements must == 1.0f, off-diagonal must == 0.0f.
// ============================================================================
bool gbMatrix4::IsIdentity(void) const
{
    float *p = (float *)this;
    int row = 0;
    do {
        int col = 0;
        do {
            if (row == col) {
                if (*p != 1.0f) {
                    return false;
                }
            } else {
                if (*p != 0.0f) {
                    return false;
                }
            }
            p++;
            col++;
        } while (col < 4);
        row++;
    } while (row < 4);
    return true;
}

// ============================================================================
// 0x10001700  IsValid  (42 bytes)
// public: bool __thiscall gbMatrix4::IsValid(void)const
//
// NaN check: ensures squaring each element doesn't produce a negative result.
// Also returns false if this==NULL.
// ============================================================================
bool gbMatrix4::IsValid(void) const
{
    if (this == NULL) return false;
    float *p = (float *)this;
    int i = 0;
    while (*p * *p >= 0.0f) {
        i++;
        p++;
        if (i > 15) {
            return true;
        }
    }
    return false;
}

// ============================================================================
// 0x100018D0  operator()  (17 bytes)
// public: float __thiscall gbMatrix4::operator()(int,int)
//
// Element access: returns m[row][col]
// ============================================================================
float gbMatrix4::operator()(int row, int col)
{
    return m[row][col];
}

// ============================================================================
// 0x10001DB0  Transpose (in-place)  (60 bytes)
// public: void __thiscall gbMatrix4::Transpose(void)
//
// Swaps upper-triangular with lower-triangular elements in place.
// ============================================================================
void gbMatrix4::Transpose(void)
{
    float *pCol = (float *)this + 1;
    float *pRow = (float *)this + 4;
    int n = 1;
    do {
        float *pA = pCol;
        float *pB = pRow;
        int k = n;
        if (k > 0) {
            do {
                float tmp = *pB;
                *pB = *pA;
                *pA = tmp;
                k--;
                pA += 4;
                pB++;
            } while (k != 0);
        }
        n++;
        pRow += 4;
        pCol++;
    } while (n < 4);
}

// ============================================================================
// 0x10001DF0  Transpose(gbMatrix4*)  (44 bytes)
// public: void __thiscall gbMatrix4::Transpose(struct gbMatrix4 *)const
//
// Writes the transpose of this matrix to the output parameter.
// Reads columns of this and writes them as rows of output.
// ============================================================================
void gbMatrix4::Transpose(gbMatrix4 *out) const
{
    float *pSrc = (float *)this;
    float *pDst = (float *)out;
    int col = 4;
    do {
        float *p = pSrc;
        int row = 4;
        do {
            float val = *p;
            p += 4;
            *pDst = val;
            pDst++;
            row--;
        } while (row != 0);
        pSrc++;
        col--;
    } while (col != 0);
}

// ============================================================================
// 0x100021B0  GetRow(gbVec3D*, int)  (32 bytes)
// public: struct gbVec3D * __thiscall gbMatrix4::GetRow(struct gbVec3D *,int)const
//
// Copies the first 3 elements of the specified row into a gbVec3D.
// ============================================================================
gbVec3D *gbMatrix4::GetRow(gbVec3D *out, int row) const
{
    float *pRow = (float *)this + row * 4;
    out->x = pRow[0];
    out->y = pRow[1];
    out->z = pRow[2];
    return out;
}

// ============================================================================
// 0x100021D0  GetColumn(gbVec3D*, int)  (32 bytes)
// public: struct gbVec3D * __thiscall gbMatrix4::GetColumn(struct gbVec3D *,int)const
//
// Copies the specified column (rows 0-2) into a gbVec3D.
// ============================================================================
gbVec3D *gbMatrix4::GetColumn(gbVec3D *out, int col) const
{
    out->x = m[0][col];
    out->y = m[1][col];
    out->z = m[2][col];
    return out;
}

// ============================================================================
// 0x10001F50  LeftTranslate(gbVec3D&)  (87 bytes)
// public: void __thiscall gbMatrix4::LeftTranslate(struct gbVec3D &)
//
// Adds translation by rotating the vector through the 3x3 part and
// accumulating into the translation row (row 3).
// m[3] += R * v  (where R is the upper-left 3x3)
// ============================================================================
void gbMatrix4::LeftTranslate(gbVec3D &v)
{
    m[3][0] = v.z * m[2][0] + v.y * m[1][0] + v.x * m[0][0] + m[3][0];
    m[3][1] = v.z * m[2][1] + v.y * m[1][1] + v.x * m[0][1] + m[3][1];
    m[3][2] = v.z * m[2][2] + v.y * m[1][2] + v.x * m[0][2] + m[3][2];
}

// ============================================================================
// 0x10001FB0  LeftTranslate(float,float,float)  (95 bytes)
// public: void __thiscall gbMatrix4::LeftTranslate(float,float,float)
// ============================================================================
void gbMatrix4::LeftTranslate(float x, float y, float z)
{
    m[3][0] = y * m[1][0] + z * m[2][0] + x * m[0][0] + m[3][0];
    m[3][1] = x * m[0][1] + y * m[1][1] + z * m[2][1] + m[3][1];
    m[3][2] = x * m[0][2] + y * m[1][2] + z * m[2][2] + m[3][2];
}

// ============================================================================
// 0x10002010  RightTranslate(gbVec3D&)  (33 bytes)
// public: void __thiscall gbMatrix4::RightTranslate(struct gbVec3D &)
//
// Simply adds the vector components to the translation row.
// ============================================================================
void gbMatrix4::RightTranslate(gbVec3D &v)
{
    m[3][0] = v.x + m[3][0];
    m[3][1] = v.y + m[3][1];
    m[3][2] = v.z + m[3][2];
}

// ============================================================================
// 0x10002040  RightTranslate(float,float,float)  (33 bytes)
// public: void __thiscall gbMatrix4::RightTranslate(float,float,float)
// ============================================================================
void gbMatrix4::RightTranslate(float x, float y, float z)
{
    m[3][0] = x + m[3][0];
    m[3][1] = y + m[3][1];
    m[3][2] = z + m[3][2];
}

// ============================================================================
// 0x10002070  RightScale  (121 bytes)
// public: void __thiscall gbMatrix4::RightScale(float,float,float)
//
// Scales columns: col0 *= sx, col1 *= sy, col2 *= sz
// (affects all 4 rows for each column)
// ============================================================================
void gbMatrix4::RightScale(float sx, float sy, float sz)
{
    m[0][0] = sx * m[0][0];
    m[1][0] = sx * m[1][0];
    m[2][0] = sx * m[2][0];
    m[3][0] = sx * m[3][0];
    m[0][1] = sy * m[0][1];
    m[1][1] = sy * m[1][1];
    m[2][1] = sy * m[2][1];
    m[3][1] = sy * m[3][1];
    m[0][2] = sz * m[0][2];
    m[1][2] = sz * m[1][2];
    m[2][2] = sz * m[2][2];
    m[3][2] = sz * m[3][2];
}

// ============================================================================
// 0x100020F0  LeftScale  (91 bytes)
// public: void __thiscall gbMatrix4::LeftScale(float,float,float)
//
// Scales rows: row0 *= sx, row1 *= sy, row2 *= sz
// (only affects first 3 elements of each row, not m[i][3])
// ============================================================================
void gbMatrix4::LeftScale(float sx, float sy, float sz)
{
    m[0][0] = sx * m[0][0];
    m[0][1] = sx * m[0][1];
    m[0][2] = sx * m[0][2];
    m[1][0] = sy * m[1][0];
    m[1][1] = sy * m[1][1];
    m[1][2] = sy * m[1][2];
    m[2][0] = sz * m[2][0];
    m[2][1] = sz * m[2][1];
    m[2][2] = sz * m[2][2];
}
