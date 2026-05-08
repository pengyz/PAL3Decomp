/**
 * gbengine.dll - gbAABBox
 * Axis-Aligned Bounding Box primitive
 */

#include "gbengine/gbengine_types.h"
#include <math.h>

// Constructor
gbAABBox::gbAABBox() {
    vMin.x = vMin.y = vMin.z = 0.0f;
    vMax.x = vMax.y = vMax.z = 1.0f;
}

// Assignment operator
gbAABBox& gbAABBox::operator=(const gbAABBox& box) {
    vMin = box.vMin;
    vMax = box.vMax;
    return *this;
}

// AABB-AABB collision test
int gbAABBox::IsColAABB(gbAABBox& box) {
    return vMax.x >= box.vMin.x
        && vMin.x <= box.vMax.x
        && vMax.y >= box.vMin.y
        && vMin.y <= box.vMax.y
        && vMax.z >= box.vMin.z
        && vMin.z <= box.vMax.z;
}

// Point-in-AABB test
int gbAABBox::IsColPoint(gbVec3D& point) {
    return point.x >= vMin.x
        && point.y >= vMin.y
        && point.z >= vMin.z
        && point.x <= vMax.x
        && point.y <= vMax.y
        && point.z <= vMax.z;
}

// Transform AABB by matrix
void gbAABBox::Transform(gbMatrix4* mat) {
    float corners[24];
    float *p = corners;
    int i;
    for (i = 8; i != 0; i--) {
        p[0] = 0.0f;
        p[1] = 0.0f;
        p[2] = 0.0f;
        p += 3;
    }

    corners[0]  = vMax.x; corners[1]  = vMax.y; corners[2]  = vMax.z;
    corners[3]  = vMax.x; corners[4]  = vMax.y; corners[5]  = vMin.z;
    corners[6]  = vMax.x; corners[7]  = vMin.y; corners[8]  = vMax.z;
    corners[9]  = vMax.x; corners[10] = vMin.y; corners[11] = vMin.z;
    corners[12] = vMin.x; corners[13] = vMax.y; corners[14] = vMax.z;
    corners[15] = vMin.x; corners[16] = vMax.y; corners[17] = vMin.z;
    corners[18] = vMin.x; corners[19] = vMin.y; corners[20] = vMax.z;
    corners[21] = vMin.x; corners[22] = vMin.y; corners[23] = vMin.z;

    mat->Transform((gbVec3D *)corners, 8);

    *(int *)&vMin.z = 0x7F7FFFFF;
    *(int *)&vMin.y = 0x7F7FFFFF;
    *(int *)&vMin.x = 0x7F7FFFFF;
    *(int *)&vMax.z = 0xFF7FFFFF;
    *(int *)&vMax.y = 0xFF7FFFFF;
    *(int *)&vMax.x = 0xFF7FFFFF;

    float *pf = &corners[1];
    for (i = 8; i != 0; i--) {
        if (vMin.x > pf[-1]) vMin.x = pf[-1];
        if (vMax.x < pf[-1]) vMax.x = pf[-1];
        if (vMin.y > pf[0]) vMin.y = pf[0];
        if (vMax.y < pf[0]) vMax.y = pf[0];
        if (vMin.z > pf[1]) vMin.z = pf[1];
        if (vMax.z < pf[1]) vMax.z = pf[1];
        pf += 3;
    }
}
