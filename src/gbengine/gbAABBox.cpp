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
    return (vMin.x <= box.vMax.x && vMax.x >= box.vMin.x &&
            vMin.y <= box.vMax.y && vMax.y >= box.vMin.y &&
            vMin.z <= box.vMax.z && vMax.z >= box.vMin.z) ? 1 : 0;
}

// Point-in-AABB test
int gbAABBox::IsColPoint(gbVec3D& point) {
    return (point.x >= vMin.x && point.x <= vMax.x &&
            point.y >= vMin.y && point.y <= vMax.y &&
            point.z >= vMin.z && point.z <= vMax.z) ? 1 : 0;
}

// Transform AABB by matrix
void gbAABBox::Transform(gbMatrix4* mat) {
    // Transform all 8 corners and recompute AABB
    gbVec3D corners[8];
    corners[0] = gbVec3D(vMin.x, vMin.y, vMin.z);
    corners[1] = gbVec3D(vMax.x, vMin.y, vMin.z);
    corners[2] = gbVec3D(vMin.x, vMax.y, vMin.z);
    corners[3] = gbVec3D(vMax.x, vMax.y, vMin.z);
    corners[4] = gbVec3D(vMin.x, vMin.y, vMax.z);
    corners[5] = gbVec3D(vMax.x, vMin.y, vMax.z);
    corners[6] = gbVec3D(vMin.x, vMax.y, vMax.z);
    corners[7] = gbVec3D(vMax.x, vMax.y, vMax.z);

    // Transform first corner and initialize bounds
    mat->Transform(&corners[0], &corners[0]);
    vMin = vMax = corners[0];

    // Transform remaining corners and expand bounds
    for (int i = 1; i < 8; i++) {
        mat->Transform(&corners[i], &corners[i]);

        if (corners[i].x < vMin.x) vMin.x = corners[i].x;
        if (corners[i].y < vMin.y) vMin.y = corners[i].y;
        if (corners[i].z < vMin.z) vMin.z = corners[i].z;

        if (corners[i].x > vMax.x) vMax.x = corners[i].x;
        if (corners[i].y > vMax.y) vMax.y = corners[i].y;
        if (corners[i].z > vMax.z) vMax.z = corners[i].z;
    }
}
