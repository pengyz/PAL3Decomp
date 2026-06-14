/**
 * gbMatrix4 - 4x4 Matrix class implementation
 *
 * Matching decompilation of gbengine.dll gbMatrix4 methods.
 * Compiler: MSVC 6.0 SP5, /O2
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

#include "gbengine/gbengine_types.h"
#include <math.h>
#include <string.h>

#define GB_FLOAT_EPSILON 0.005

static float s_fHalfM = 0.5f;
static float s_fDeg2RadM = 0.017453292f;

gbMatrix4::gbMatrix4(void)
{
    memset(this, 0, sizeof(gbMatrix4));
    m[3][3] = 1.0f;
    m[2][2] = 1.0f;
    m[1][1] = 1.0f;
    m[0][0] = 1.0f;
}

void gbMatrix4::operator=(const gbMatrix4 &other)
{
    float *pDst = (float *)this;
    float *pSrc = (float *)&other;
    int i;
    for (i = 16; i != 0; i--) {
        *pDst++ = *pSrc++;
    }
}

void gbMatrix4::operator*=(const gbMatrix4 &param)
{
    float temp[16];
    memcpy(temp, this, sizeof(temp));

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
                *pResult = *pB * *pA + *pResult;
                pA += 4;
                pB++;
                k--;
            } while (k != 0);
            pResult++;
            pTemp++;
            col--;
        } while (col != 0);
        pOther += 4;
        row--;
    } while (row != 0);
}

void gbMatrix4::RightMultiply(const gbMatrix4 &param)
{
    float temp[16];
    memcpy(temp, this, sizeof(temp));

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
                *pResult = *pB * *pA + *pResult;
                pB += 4;
                pA++;
                k--;
            } while (k != 0);
            pResult++;
            pCol++;
            col--;
        } while (col != 0);
        pRow += 4;
        row--;
    } while (row != 0);
}

void gbMatrix4::LeftMultiply(const gbMatrix4 &param)
{
    float temp[16];
    memcpy(temp, this, sizeof(temp));

    float *pOther = (float *)&param;
    int row = 4;
    do {
        float *pResult = (float *)this + (pOther - (float *)&param);
        float *pTemp = temp;
        int col = 4;
        do {
            *pResult = 0.0f;
            float *pA = pOther;
            float *pB = pTemp;
            int k = 4;
            do {
                *pResult = *pA * *pB + *pResult;
                pA++;
                pB += 4;
                k--;
            } while (k != 0);
            pResult++;
            pTemp++;
            col--;
        } while (col != 0);
        pOther += 4;
        row--;
    } while (row != 0);
}

void gbMatrix4::Transform(const gbVec3D *in, gbVec3D *out) const
{
    out->x = in->y * m[1][0] + in->z * m[2][0] + in->x * m[0][0] + m[3][0];
    out->y = in->x * m[0][1] + in->y * m[1][1] + in->z * m[2][1] + m[3][1];
    out->z = in->x * m[0][2] + in->y * m[1][2] + in->z * m[2][2] + m[3][2];
}

void gbMatrix4::Rotate(const gbVec3D *in, gbVec3D *out) const
{
    out->x = in->y * m[1][0] + in->z * m[2][0] + in->x * m[0][0];
    out->y = in->x * m[0][1] + in->y * m[1][1] + in->z * m[2][1];
    out->z = in->x * m[0][2] + in->y * m[1][2] + in->z * m[2][2];
}

void gbMatrix4::LoadIdentity(void)
{
    memset(this, 0, sizeof(gbMatrix4));
    m[3][3] = 1.0f;
    m[2][2] = 1.0f;
    m[1][1] = 1.0f;
    m[0][0] = 1.0f;
}

bool gbMatrix4::IsIdentity(void) const
{
    float *p = (float *)this;
    int row, col;
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (row == col) {
                if (*p != 1.0f) return false;
            } else {
                if (*p != 0.0f) return false;
            }
            p++;
        }
    }
    return true;
}

bool gbMatrix4::IsValid(void) const
{
    if (this == NULL) return false;
    int i = 0;
    float* p = (float*)this;
    do {
        float v = *p;
        if (v * v < 0.0f) return false;
        i++;
        p++;
    } while (i < 16);
    return true;
}

float gbMatrix4::operator()(int row, int col)
{
    return m[row][col];
}

void gbMatrix4::Transpose(void)
{
    int n = 1;
    float *pCol = &m[0][1];
    float *pRow = &m[1][0];
    do {
        float *pA = pCol;
        float *pB = pRow;
        int k = n;
        if (k > 0) {
            do {
                float tmp = *pB;
                *pB = *pA;
                *pA = tmp;
                pA += 4;
                pB++;
            } while (--k);
        }
        n++;
        pRow += 4;
        pCol++;
    } while (n < 4);
}

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

gbVec3D *gbMatrix4::GetRow(gbVec3D *out, int row) const
{
    out->x = m[row][0];
    out->y = m[row][1];
    out->z = m[row][2];
    return out;
}

gbVec3D *gbMatrix4::GetColumn(gbVec3D *out, int col) const
{
    out->x = m[0][col];
    out->y = m[1][col];
    out->z = m[2][col];
    return out;
}

void gbMatrix4::SetAxisAngle(gbAxis axis, float cosA, float sinA)
{
    memset(this, 0, sizeof(gbMatrix4));
    int one = 0x3F800000;
    ((int *)this)[15] = one;
    switch (axis) {
    case 0:
        ((int *)this)[0] = one;
        ((int *)this)[5] = *(int *)&cosA;
        ((int *)this)[6] = *(int *)&sinA;
        m[2][1] = -sinA;
        ((int *)this)[10] = *(int *)&cosA;
        break;
    case 1:
        ((int *)this)[5] = one;
        ((int *)this)[0] = *(int *)&cosA;
        ((int *)this)[8] = *(int *)&sinA;
        m[0][2] = -sinA;
        ((int *)this)[10] = *(int *)&cosA;
        break;
    case 2:
        ((int *)this)[10] = one;
        ((int *)this)[0] = *(int *)&cosA;
        ((int *)this)[1] = *(int *)&sinA;
        m[1][0] = -sinA;
        ((int *)this)[5] = *(int *)&cosA;
        break;
    }
}

void gbMatrix4::SetAxisAngle(gbAxis axis, float angle)
{
    float rad = angle * 0.017453292f;
    float s = (float)sin(rad);
    float c = (float)cos(rad);
    SetAxisAngle(axis, c, s);
}

void gbMatrix4::SetAxisAngle(gbVec3D *axis, float angle)
{
    float a = angle;
    float halfRad = a * s_fHalfM;
    halfRad = halfRad * s_fDeg2RadM;
    float qdata[4];
    qdata[3] = (float)cos(halfRad);
    float s = (float)sin(halfRad);
    qdata[0] = s * axis->x;
    qdata[1] = s * axis->y;
    qdata[2] = s * axis->z;
    ((gbQuaternion *)qdata)->GetMatrix(this);
}

void gbMatrix4::Invert(gbMatrix4 *out) const
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

// NOTE: manually inlined Invert(gbMatrix4*) to match original compiler inlining
// revert to Invert(&tmp) + *this = tmp after binary matching is complete
void gbMatrix4::Invert()
{
    gbMatrix4 tmp;

    float cofA = m[2][2] * m[1][1] - m[2][1] * m[1][2];
    float det = 1.0f / ((m[2][1] * m[1][0] - m[2][0] * m[1][1]) * m[0][2] +
                        (cofA * m[0][0] -
                        (m[2][2] * m[1][0] - m[2][0] * m[1][2]) * m[0][1]));

    tmp.m[0][0] = cofA * det;
    tmp.m[0][1] = -((m[0][1] * m[2][2] - m[2][1] * m[0][2]) * det);
    tmp.m[0][3] = 0;
    tmp.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * det;
    tmp.m[1][0] = -((m[1][0] * m[2][2] - m[2][0] * m[1][2]) * det);
    tmp.m[1][1] = (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * det;
    tmp.m[1][3] = 0;
    tmp.m[1][2] = -((m[0][0] * m[1][2] - m[1][0] * m[0][2]) * det);
    tmp.m[2][0] = (m[2][1] * m[1][0] - m[2][0] * m[1][1]) * det;
    tmp.m[2][1] = -((m[2][1] * m[0][0] - m[2][0] * m[0][1]) * det);
    tmp.m[2][3] = 0;
    tmp.m[2][2] = (m[1][1] * m[0][0] - m[1][0] * m[0][1]) * det;
    tmp.m[3][0] = -(tmp.m[2][0] * m[3][2] + tmp.m[0][0] * m[3][0] + m[3][1] * tmp.m[1][0]);
    tmp.m[3][1] = -(tmp.m[0][1] * m[3][0] + tmp.m[2][1] * m[3][2] + m[3][1] * tmp.m[1][1]);
    tmp.m[3][3] = 1.0f;
    tmp.m[3][2] = -(m[3][0] * tmp.m[0][2] + m[3][1] * tmp.m[1][2] + m[3][2] * tmp.m[2][2]);

    *this = tmp;
}

void gbMatrix4::RightMultiply(const gbQuaternion &q)
{
    gbMatrix4 tmp;
    ((gbQuaternion *)&q)->GetMatrix(&tmp);
    RightMultiply(tmp);
}

void gbMatrix4::operator*=(const gbQuaternion &q)
{
    gbMatrix4 tmp;
    ((gbQuaternion *)&q)->GetMatrix(&tmp);
    LeftMultiply(tmp);
}

void gbMatrix4::LeftTranslate(gbVec3D &v)
{
    m[3][0] = v.z * m[2][0] + v.y * m[1][0] + v.x * m[0][0] + m[3][0];
    m[3][1] = v.z * m[2][1] + v.y * m[1][1] + v.x * m[0][1] + m[3][1];
    m[3][2] = v.z * m[2][2] + v.y * m[1][2] + v.x * m[0][2] + m[3][2];
}

void gbMatrix4::LeftTranslate(float x, float y, float z)
{
    m[3][0] = y * m[1][0] + z * m[2][0] + x * m[0][0] + m[3][0];
    m[3][1] = x * m[0][1] + y * m[1][1] + z * m[2][1] + m[3][1];
    m[3][2] = x * m[0][2] + y * m[1][2] + z * m[2][2] + m[3][2];
}

void gbMatrix4::RightTranslate(gbVec3D &v)
{
    m[3][0] = v.x + m[3][0];
    m[3][1] = v.y + m[3][1];
    m[3][2] = v.z + m[3][2];
}

void gbMatrix4::RightTranslate(float x, float y, float z)
{
    m[3][0] = x + m[3][0];
    m[3][1] = y + m[3][1];
    m[3][2] = z + m[3][2];
}

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
