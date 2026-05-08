/**
 * gbengine.dll - gbPlane
 * Plane primitive for collision detection
 */

#include "gbengine/gbengine_types.h"
#include <math.h>

gbPlane::gbPlane() {
    *(int*)&normal.x = 0;
    *(int*)&normal.y = 0;
    *(int*)&normal.z = 0;
}

gbPlane& gbPlane::operator=(const gbPlane& p) {
    normal.x = p.normal.x;
    normal.y = p.normal.y;
    normal.z = p.normal.z;
    d = p.d;
    return *this;
}

int gbPlane::IsColAABB(gbAABBox& box) {
    float farX, farY, farZ;
    float nearX, nearY;
    float nearZ;

    if (normal.x >= 0.0f) {
        farX = box.vMin.x;
        nearX = box.vMax.x;
    } else {
        farX = box.vMax.x;
        nearX = box.vMin.x;
    }
    if (normal.y >= 0.0f) {
        farY = box.vMin.y;
        nearY = box.vMax.y;
    } else {
        farY = box.vMax.y;
        nearY = box.vMin.y;
    }
    if (normal.z >= 0.0f) {
        farZ = box.vMin.z;
        nearZ = box.vMax.z;
    } else {
        farZ = box.vMax.z;
        nearZ = box.vMin.z;
    }
    if (farX * normal.x + farY * normal.y + farZ * normal.z > d) {
        return 0;
    }
    if (nearX * normal.x + nearY * normal.y + nearZ * normal.z < d) {
        return 0;
    }
    return 1;
}

int gbPlane::IsColOBB(gbOBBox& box) {
    float* m = (float*)&box.matrix;
    float local[10];

    local[3] = d;
    local[0] = m[1] * normal.y + m[2] * normal.z + m[0] * normal.x;
    local[1] = m[5] * normal.y + m[6] * normal.z + normal.x * m[4];
    local[2] = m[9] * normal.y + m[10] * normal.z + m[8] * normal.x;
    local[4] = m[12] - box.extent.x * 0.5f;
    local[5] = m[13] - box.extent.y * 0.5f;
    local[6] = m[14] - box.extent.z * 0.5f;
    local[7] = box.extent.x * 0.5f + m[12];
    local[8] = box.extent.y * 0.5f + m[13];
    local[9] = box.extent.z * 0.5f + m[14];

    return ((gbPlane*)&local[0])->IsColAABB(*(gbAABBox*)&local[4]);
}
