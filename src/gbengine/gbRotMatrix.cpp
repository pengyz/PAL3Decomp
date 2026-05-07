/**
 * gbRotMatrix - 3x3 Rotation Matrix class implementation
 *
 * Matching decompilation of gbengine.dll gbRotMatrix methods.
 * Compiler: MSVC 6.0 SP5, /O2
 *
 * Memory layout: float m[3][3] (36 bytes, row-major)
 *   m[0][0]=+0x00  m[0][1]=+0x04  m[0][2]=+0x08
 *   m[1][0]=+0x0C  m[1][1]=+0x10  m[1][2]=+0x14
 *   m[2][0]=+0x18  m[2][1]=+0x1C  m[2][2]=+0x20
 */

#include "gbengine/gbengine_types.h"
#include <math.h>
#include <string.h>

#define GB_FLOAT_EPSILON 0.005

gbRotMatrix::gbRotMatrix(void)
{
    memset(this, 0, 0x24);
    m[2][2] = 1.0f;
    m[1][1] = 1.0f;
    m[0][0] = 1.0f;
}

void gbRotMatrix::operator=(gbRotMatrix &other)
{
    int *pDst = (int *)this;
    int offset = (int)((char *)&other - (char *)this);
    int count = 9;
    do {
        *pDst = *(int *)((char *)pDst + offset);
        pDst++;
        count--;
    } while (count);
}

void gbRotMatrix::operator*=(gbRotMatrix &other)
{
    float temp[9];
    memcpy(temp, this, sizeof(temp));

    float *pRow = temp;
    int offset = (int)((char *)this - (char *)temp);
    int row = 3;
    for (;;) {
        float *pCol = (float *)&other;
        float *pResult = (float *)((char *)pRow + offset);
        int col = 3;
        do {
            *pResult = 0.0f;
            float *pA = pRow;
            float *pB = pCol;
            int k = 3;
            do {
                float v = *pA * *pB;
                pA++;
                pB += 3;
                k--;
                *pResult = v + *pResult;
            } while (k);
            pResult++;
            pCol++;
            col--;
        } while (col);
        pRow += 3;
        row--;
        if (!row)
            break;
    }
}

void gbRotMatrix::Rotate(gbVec3D *in, gbVec3D *out)
{
    out->x = in->y * m[1][0] + in->z * m[2][0] + in->x * m[0][0];
    out->y = in->x * m[0][1] + in->y * m[1][1] + in->z * m[2][1];
    out->z = in->x * m[0][2] + in->y * m[1][2] + in->z * m[2][2];
}

void gbRotMatrix::LoadIdentity(void)
{
    memset(this, 0, 0x24);
    m[2][2] = 1.0f;
    m[1][1] = 1.0f;
    m[0][0] = 1.0f;
}

bool const gbRotMatrix::IsValid(void)
{
    if (!this)
        return 0;
    int v2 = 0;
    float* p = (float*)this;
    while (*(float*)p * *(float*)p >= 0.0) {
        ++v2;
        p++;
        if (v2 >= 9)
            return 1;
    }
    return 0;
}

bool const gbRotMatrix::IsOrthonormal(void)
{
    float ax = m[0][0];
    float bx = m[1][0];
    float cx = m[2][0];
    float cy = m[2][1];
    float az = m[0][2];
    float ay = m[0][1];
    float by = m[1][1];
    float cz = m[2][2];
    float bz = m[1][2];

    // Normalize column Z (az, by_z, cz)
    double lenZ = sqrt(cz * cz + by * by + az * az);
    float nzx, nzy, nzz;
    if (fabs(lenZ) >= GB_FLOAT_EPSILON) {
        nzx = (float)(az / lenZ);
        nzy = (float)(by / lenZ);
        nzz = (float)(cz / lenZ);
    } else {
        nzz = 0.0f;
        nzx = 0.0f;
        nzy = 1.0f;
    }

    // Cross product of col_x and col_y
    float crossX = cy * bx - bz * cx;
    float crossY = ay * cx - cy * ax;
    float crossZ = bz * ax - ay * bx;

    // Normalize cross product
    double lenC = sqrt(crossZ * crossZ + crossX * crossX + crossY * crossY);
    float ncx, ncy, ncz;
    if (fabs(lenC) >= GB_FLOAT_EPSILON) {
        ncx = (float)(crossX / lenC);
        ncy = (float)(crossY / lenC);
        ncz = (float)(crossZ / lenC);
    } else {
        ncx = 0.0f;
        ncz = 0.0f;
        ncy = 1.0f;
    }

    if (fabs(ncx - nzx) < GB_FLOAT_EPSILON &&
        fabs(ncy - nzy) < GB_FLOAT_EPSILON &&
        fabs(ncz - nzz) < GB_FLOAT_EPSILON) {
        return true;
    }

    float neg_nzy = -nzy;
    float neg_nzz = -nzz;
    return fabs(ncx - (-nzx)) < GB_FLOAT_EPSILON &&
           fabs(ncy - neg_nzy) < GB_FLOAT_EPSILON &&
           fabs(ncz - neg_nzz) < GB_FLOAT_EPSILON;
}
