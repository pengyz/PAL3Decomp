#include "gbengine/gbengine_types.h"
#include <string.h>

gbVec4D* gbMatrix4::GetColumn(gbVec4D* result, int col) const {
    result->x = m[0][col];
    result->y = m[1][col];
    result->z = m[2][col];
    result->w = m[3][col];
    return result;
}

gbVec4D* gbMatrix4::GetRow(gbVec4D* result, int row) const {
    result->x = m[row][0];
    result->y = m[row][1];
    result->z = m[row][2];
    result->w = m[row][3];
    return result;
}

void gbMatrix4::LeftMultiply(const gbQuaternion& q) {
    gbMatrix4 rot;
    const_cast<gbQuaternion&>(q).GetMatrix(&rot);
    LeftMultiply(rot);
}

void gbMatrix4::RotateIn(gbVec3D* v) {
    float x = m[0][0] * v->x + m[0][1] * v->y + m[0][2] * v->z;
    float y = m[1][0] * v->x + m[1][1] * v->y + m[1][2] * v->z;
    float z = m[2][0] * v->x + m[2][1] * v->y + m[2][2] * v->z;
    v->x = x;
    v->y = y;
    v->z = z;
}

void gbMatrix4::TransformPlane(float* const p) {
    float nx = p[0], ny = p[1], nz = p[2], d = p[3];
    p[0] = m[0][0] * nx + m[1][0] * ny + m[2][0] * nz;
    p[1] = m[0][1] * nx + m[1][1] * ny + m[2][1] * nz;
    p[2] = m[0][2] * nx + m[1][2] * ny + m[2][2] * nz;
    p[3] = d - (m[3][0] * p[0] + m[3][1] * p[1] + m[3][2] * p[2]);
}

void gbMatrix4::operator*=(const float* other) {
    gbMatrix4 tmp;
    memcpy(&tmp, other, sizeof(gbMatrix4));
    LeftMultiply(tmp);
}
