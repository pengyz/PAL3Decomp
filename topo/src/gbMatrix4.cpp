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
#pragma inline_depth(0)
gbMatrix4::gbMatrix4(void)
{
    LoadIdentity();
}
#pragma inline_depth()

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
    m[3][3] = 1.0f;
    m[2][2] = 1.0f;
    m[1][1] = 1.0f;
    m[0][0] = 1.0f;
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
                if (*(int *)p != 0x3F800000) {
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
// 0x10001910  SetAxisAngle(gbAxis, float, float)  (143 bytes)
// public: void __thiscall gbMatrix4::SetAxisAngle(enum gbAxis,float,float)
//
// Sets this to a rotation matrix for the given axis.
// param_2 = cos(angle), param_3 = sin(angle).
// ============================================================================
void gbMatrix4::SetAxisAngle(gbAxis axis, float cosA, float sinA)
{
    float *p = (float *)this;
    int i;
    for (i = 16; i != 0; i--) {
        *p = 0.0f;
        p++;
    }
    m[3][3] = 1.0f;
    if (axis == 0) {
        m[0][0] = 1.0f;
        m[1][1] = cosA;
        m[1][2] = sinA;
        m[2][1] = -sinA;
        m[2][2] = cosA;
    } else if (axis == 1) {
        m[1][1] = 1.0f;
        m[0][0] = cosA;
        m[2][0] = sinA;
        m[0][2] = -sinA;
        m[2][2] = cosA;
    } else if (axis == 2) {
        m[2][2] = 1.0f;
        m[0][0] = cosA;
        m[0][1] = sinA;
        m[1][0] = -sinA;
        m[1][1] = cosA;
    }
}

// ============================================================================
// 0x10001A30  SetAxisAngle(gbAxis, float)  (37 bytes)
// public: void __thiscall gbMatrix4::SetAxisAngle(enum gbAxis,float)
//
// Sets rotation matrix from axis and angle in degrees.
// Converts angle to radians, computes cos/sin, calls 3-arg overload.
// ============================================================================
void gbMatrix4::SetAxisAngle(gbAxis axis, float angle)
{
    float rad = angle * 0.017453292f;
    float s = (float)sin(rad);
    float c = (float)cos(rad);
    SetAxisAngle(axis, c, s);
}

// ============================================================================
// 0x10001A60  SetAxisAngle(gbVec3D*, float)  (74 bytes)
// public: void __thiscall gbMatrix4::SetAxisAngle(struct gbVec3D *,float)
//
// Arbitrary axis rotation: creates a quaternion, converts to matrix.
// ============================================================================
void gbMatrix4::SetAxisAngle(gbVec3D *axis, float angle)
{
    gbQuaternion q;
    q.x = 0.0f;
    q.y = 0.0f;
    q.z = 0.0f;
    q.w = 1.0f;
    q.SetAxisAngle(axis, angle);
    q.GetMatrix(this);
}

// ============================================================================
// 0x10001AB0  Invert (in-place)  (407 bytes)
// public: void __thiscall gbMatrix4::Invert(void)
//
// Computes the inverse of the matrix in-place. Uses the cofactor method
// for the 3x3 rotation part, then computes the translation from the
// rotation inverse. Assumes m[0][3]==m[1][3]==m[2][3]==0, m[3][3]==1.
// ============================================================================
void gbMatrix4::Invert(void)
{
    gbMatrix4 tmp;
    tmp.m[0][3] = 0.0f;
    tmp.m[1][3] = 0.0f;

    float cofA = m[1][1] * m[2][2] - m[2][1] * m[1][2];
    float cofB = m[1][0] * m[2][2] - m[2][0] * m[1][2];
    float cofC = m[2][1] * m[1][0] - m[2][0] * m[1][1];

    float det = 1.0f / (cofA * m[0][0] - cofB * m[0][1] + cofC * m[0][2]);

    tmp.m[0][0] = cofA * det;
    tmp.m[0][1] = -((m[0][1] * m[2][2] - m[2][1] * m[0][2]) * det);
    tmp.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * det;
    tmp.m[1][0] = -(cofB * det);
    tmp.m[1][1] = (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * det;
    tmp.m[1][2] = -((m[0][0] * m[1][2] - m[1][0] * m[0][2]) * det);
    tmp.m[2][0] = cofC * det;
    tmp.m[2][3] = 0.0f;
    tmp.m[3][3] = 1.0f;
    tmp.m[2][1] = -((m[2][1] * m[0][0] - m[2][0] * m[0][1]) * det);
    tmp.m[2][2] = (m[1][1] * m[0][0] - m[1][0] * m[0][1]) * det;
    tmp.m[3][0] = -(tmp.m[1][0] * m[3][1] + tmp.m[2][0] * m[3][2] + tmp.m[0][0] * m[3][0]);
    tmp.m[3][1] = -(tmp.m[1][1] * m[3][1] + tmp.m[2][1] * m[3][2] + tmp.m[0][1] * m[3][0]);
    tmp.m[3][2] = -(tmp.m[1][2] * m[3][1] + tmp.m[2][2] * m[3][2] + tmp.m[0][2] * m[3][0]);

    *this = tmp;
}

// ============================================================================
// 0x10001C50  Invert(gbMatrix4*)  (351 bytes)
// public: void __thiscall gbMatrix4::Invert(struct gbMatrix4 *)
//
// Computes the inverse and stores in output parameter.
// Same cofactor method as the in-place version.
// ============================================================================
void gbMatrix4::Invert(gbMatrix4 *out)
{
    float cofA = m[1][1] * m[2][2] - m[2][1] * m[1][2];
    float det = 1.0f / ((m[2][1] * m[1][0] - m[2][0] * m[1][1]) * m[0][2] +
                        (cofA * m[0][0] -
                        (m[1][0] * m[2][2] - m[2][0] * m[1][2]) * m[0][1]));

    out->m[0][0] = cofA * det;
    out->m[0][1] = -((m[0][1] * m[2][2] - m[2][1] * m[0][2]) * det);
    out->m[0][3] = 0;
    out->m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * det;
    out->m[1][0] = -((m[1][0] * m[2][2] - m[2][0] * m[1][2]) * det);
    out->m[1][1] = (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * det;
    out->m[1][3] = 0;
    out->m[1][2] = -((m[0][0] * m[1][2] - m[1][0] * m[0][2]) * det);
    out->m[2][0] = (m[2][1] * m[1][0] - m[2][0] * m[1][1]) * det;
    out->m[2][1] = -((m[2][1] * m[0][0] - m[2][0] * m[0][1]) * det);
    out->m[2][3] = 0;
    out->m[2][2] = (m[1][1] * m[0][0] - m[1][0] * m[0][1]) * det;
    out->m[3][0] = -(out->m[2][0] * m[3][2] + out->m[0][0] * m[3][0] + m[3][1] * out->m[1][0]);
    out->m[3][1] = -(out->m[0][1] * m[3][0] + out->m[2][1] * m[3][2] + m[3][1] * out->m[1][1]);
    out->m[3][3] = 1.0f;
    out->m[3][2] = -(m[3][0] * out->m[0][2] + m[3][1] * out->m[1][2] + m[3][2] * out->m[2][2]);
}

// ============================================================================
// 0x10001EF0  RightMultiply(gbQuaternion)  (48 bytes)
// public: void __thiscall gbMatrix4::RightMultiply(struct gbQuaternion const &)
//
// Converts quaternion to matrix, then right-multiplies this by it.
// ============================================================================
void gbMatrix4::RightMultiply(const gbQuaternion &q)
{
    gbMatrix4 tmp;
    ((gbQuaternion *)&q)->GetMatrix(&tmp);
    RightMultiply(tmp);
}

// ============================================================================
// 0x10001F20  operator*=(gbQuaternion)  (48 bytes)
// public: void __thiscall gbMatrix4::operator*=(struct gbQuaternion const &)
// Also: void __thiscall gbMatrix4::LeftMultiply(struct gbQuaternion const &)
//
// Converts quaternion to matrix, then left-multiplies this by it.
// ============================================================================
void gbMatrix4::operator*=(const gbQuaternion &q)
{
    gbMatrix4 tmp;
    ((gbQuaternion *)&q)->GetMatrix(&tmp);
    LeftMultiply(tmp);
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

// ============================================================================
// 0x10002150  GetRow(gbVec4D*, int)  (38 bytes)
// public: struct gbVec4D * __thiscall gbMatrix4::GetRow(struct gbVec4D *,int)const
//
// Copies all 4 elements of a row.
// ============================================================================
float *gbMatrix4::GetRow(float *out, int row) const
{
    float *pRow = (float *)this + row * 4;
    out[0] = pRow[0];
    out[1] = pRow[1];
    out[2] = pRow[2];
    out[3] = pRow[3];
    return out;
}

// ============================================================================
// 0x10002180  GetColumn(gbVec4D*, int)  (39 bytes)
// public: struct gbVec4D * __thiscall gbMatrix4::GetColumn(struct gbVec4D *,int)const
//
// Copies all 4 elements of a column.
// ============================================================================
float *gbMatrix4::GetColumn(float *out, int col) const
{
    out[0] = m[0][col];
    out[1] = m[1][col];
    out[2] = m[2][col];
    out[3] = m[3][col];
    return out;
}

// ============================================================================
// 0x100012B0  Transform(gbVec3D*, gbVec3D*, int)  (126 bytes)
// public: void __thiscall gbMatrix4::Transform(struct gbVec3D *,struct gbVec3D *,int)const
//
// Batch point transform: transforms an array of vectors.
// ============================================================================
void gbMatrix4::Transform(gbVec3D *in, gbVec3D *out, int count) const
{
    if (count > 0) {
        do {
            count--;
            out->x = in->y * m[1][0] + in->z * m[2][0] + in->x * m[0][0] + m[3][0];
            out->y = in->x * m[0][1] + in->y * m[1][1] + in->z * m[2][1] + m[3][1];
            out->z = in->x * m[0][2] + in->y * m[1][2] + in->z * m[2][2] + m[3][2];
            in++;
            out++;
        } while (count != 0);
    }
}

// ============================================================================
// 0x100013F0  Transform(gbVec3D*, int)  (116 bytes)
// public: void __thiscall gbMatrix4::Transform(struct gbVec3D *,int)const
//
// In-place batch point transform. Must preserve original values before
// overwriting since input and output are the same buffer.
// ============================================================================
void gbMatrix4::Transform(gbVec3D *verts, int count) const
{
    if (count > 0) {
        do {
            float ox = verts->x;
            float oy = verts->y;
            float oz = verts->z;
            count--;
            verts->z = ox * m[0][2] + oy * m[1][2] + oz * m[2][2] + m[3][2];
            verts->x = ox * m[0][0] + oy * m[1][0] + oz * m[2][0] + m[3][0];
            verts->y = ox * m[0][1] + oy * m[1][1] + oz * m[2][1] + m[3][1];
            verts++;
        } while (count != 0);
    }
}

// ============================================================================
// 0x10001330  Transform_W(gbVec3D*, gbVec3D*, int)  (185 bytes)
// public: void __thiscall gbMatrix4::Transform_W(struct gbVec3D *,struct gbVec3D *,int)const
//
// Batch perspective transform: full 4x4 multiply with W divide.
// out = (M * [in, 1]) / w
// ============================================================================
void gbMatrix4::Transform_W(gbVec3D *in, gbVec3D *out, int count) const
{
    if (count > 0) {
        do {
            count--;
            out->x = in->x * m[0][0] + in->y * m[1][0] + in->z * m[2][0] + m[3][0];
            out->y = in->x * m[0][1] + in->y * m[1][1] + in->z * m[2][1] + m[3][1];
            out->z = in->x * m[0][2] + in->y * m[1][2] + in->z * m[2][2] + m[3][2];
            float w = in->x * m[0][3] + in->y * m[1][3] + in->z * m[2][3] + m[3][3];
            out->x = out->x / w;
            out->y = out->y / w;
            out->z = out->z / w;
            out++;
            in++;
        } while (count != 0);
    }
}

// ============================================================================
// 0x10001760  IsOrthonormal  (337 bytes)
// public: bool __thiscall gbMatrix4::IsOrthonormal(void)const
//
// Same as gbRotMatrix::IsOrthonormal but also checks that the translation
// row (row 3) is valid (no NaN). Result = orthonormal_check & row3_valid.
// ============================================================================
bool gbMatrix4::IsOrthonormal(void) const
{
    gbVec3D col_x, col_y, cross, col_z;
    bool ortho;

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
        ortho = true;
    } else {
        col_z.x = -col_z.x;
        col_z.y = -col_z.y;
        col_z.z = -col_z.z;
        if (fabs(cross.x - col_z.x) < GB_FLOAT_EPSILON &&
            fabs(cross.y - col_z.y) < GB_FLOAT_EPSILON &&
            fabs(cross.z - col_z.z) < GB_FLOAT_EPSILON) {
            ortho = true;
        } else {
            ortho = false;
        }
    }

    bool valid = ((gbVec3D *)&m[3][0])->IsValid();
    return valid && ortho;
}

// ============================================================================
// 0x10001E20  MakeMatrix  (205 bytes)
// public: void __thiscall gbMatrix4::MakeMatrix(struct gbVec3D &,struct gbVec3D &,struct gbVec3D &)
//
// Builds a view/orientation matrix from forward, up, and position vectors.
// Row 0 = side (cross of up and forward, normalized)
// Row 1 = recomputed up (cross of forward and side)
// Row 2 = forward
// Row 3 = position
// ============================================================================
void gbMatrix4::MakeMatrix(gbVec3D &forward, gbVec3D &up, gbVec3D &pos)
{
    gbVec3D side, realUp;
    side.x = 0.0f; side.y = 0.0f; side.z = 0.0f;
    realUp.x = 0.0f; realUp.y = 0.0f; realUp.z = 0.0f;

    up.CrossProduct(&forward, &side);
    side.Normalize();
    forward.CrossProduct(&side, &realUp);

    m[0][0] = side.x;
    m[0][1] = side.y;
    m[0][2] = side.z;
    m[0][3] = 0.0f;
    m[1][0] = realUp.x;
    m[1][1] = realUp.y;
    m[1][2] = realUp.z;
    m[1][3] = 0.0f;
    m[2][0] = forward.x;
    m[2][1] = forward.y;
    m[2][2] = forward.z;
    m[2][3] = 0.0f;
    m[3][0] = pos.x;
    m[3][1] = pos.y;
    m[3][2] = pos.z;
    m[3][3] = 1.0f;
}

// ============================================================================
// 0x10001140  operator*= (float const *)  (ICF with operator*=(gbMatrix4 const &))
// public: void __thiscall gbMatrix4::operator*=(float const *)
// ============================================================================
void gbMatrix4::operator*=(const float *pFloats)
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

    float *pOther = (float *)pFloats;
    int row = 4;
    do {
        float *pTemp = temp;
        float *pResult = (float *)this + (pOther - (float *)pFloats);
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
// 0x10001F20  LeftMultiply(gbQuaternion)  (ICF with operator*=(gbQuaternion))
// public: void __thiscall gbMatrix4::LeftMultiply(struct gbQuaternion const &)
// ============================================================================
void gbMatrix4::LeftMultiply(const gbQuaternion &q)
{
    gbMatrix4 tmp;
    ((gbQuaternion *)&q)->GetMatrix(&tmp);
    LeftMultiply(tmp);
}

// ============================================================================
// 0x10002150  GetRow(gbVec4D)  (24 bytes)
// public: struct gbVec4D * __thiscall gbMatrix4::GetRow(struct gbVec4D *,int)const
// ============================================================================
gbVec4D *gbMatrix4::GetRow(gbVec4D *out, int row) const
{
    out->x = m[row][0];
    out->y = m[row][1];
    out->z = m[row][2];
    out->w = m[row][3];
    return out;
}

// ============================================================================
// 0x10002180  GetColumn(gbVec4D)  (30 bytes)
// public: struct gbVec4D * __thiscall gbMatrix4::GetColumn(struct gbVec4D *,int)const
// ============================================================================
gbVec4D *gbMatrix4::GetColumn(gbVec4D *out, int col) const
{
    out->x = m[0][col];
    out->y = m[1][col];
    out->z = m[2][col];
    out->w = m[3][col];
    return out;
}
