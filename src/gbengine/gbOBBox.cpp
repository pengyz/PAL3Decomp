/**
 * gbengine.dll - gbOBBox
 * Oriented Bounding Box primitive
 */

#include "gbengine/gbengine_types.h"
#include <math.h>

// Constructor
gbOBBox::gbOBBox() {
    /* STUB */
    matrix.LoadIdentity();
    extent.x = extent.y = extent.z = 1.0f;
}

// Assignment operator
gbOBBox& gbOBBox::operator=(const gbOBBox& box) {
    /* STUB */
    matrix = box.matrix;
    extent = box.extent;
    return *this;
}

// Get center of OBB
gbVec3D gbOBBox::GetCenter() const {
    /* STUB */
    gbVec3D center;
    center.x = matrix.m[3][0];
    center.y = matrix.m[3][1];
    center.z = matrix.m[3][2];
    return center;
}

// Get radius (distance from center to corner)
float gbOBBox::GetRadius() const {
    /* STUB */
    return extent.Length();
}

// Get radius in a specific direction
float gbOBBox::GetRadiusInDirection(const gbVec3D& dir) const {
    /* STUB */
    float r = 0.0f;
    for (int i = 0; i < 3; i++) {
        gbVec3D axis;
        ((gbMatrix4*)&matrix)->GetRow(&axis, i);
        float proj = fabsf(dir.DotProduct(&axis));
        r += proj * ((float*)&extent)[i];
    }
    return r;
}

// Convert OBB to AABB
void gbOBBox::GetAABBox(gbAABBox& aabb) {
    /* STUB */
    gbVec3D axis[3];
    matrix.GetRow(&axis[0], 0);
    matrix.GetRow(&axis[1], 1);
    matrix.GetRow(&axis[2], 2);

    gbVec3D center;
    center.x = matrix.m[3][0];
    center.y = matrix.m[3][1];
    center.z = matrix.m[3][2];

    gbVec3D e;
    e.x = extent.x * fabsf(axis[0].x) + extent.y * fabsf(axis[1].x) + extent.z * fabsf(axis[2].x);
    e.y = extent.x * fabsf(axis[0].y) + extent.y * fabsf(axis[1].y) + extent.z * fabsf(axis[2].y);
    e.z = extent.x * fabsf(axis[0].z) + extent.y * fabsf(axis[1].z) + extent.z * fabsf(axis[2].z);

    aabb.vMin.x = center.x - e.x;
    aabb.vMin.y = center.y - e.y;
    aabb.vMin.z = center.z - e.z;
    aabb.vMax.x = center.x + e.x;
    aabb.vMax.y = center.y + e.y;
    aabb.vMax.z = center.z + e.z;
}

// Convert OBB to bounding sphere
void gbOBBox::GetSphere(gbSphere& sphere) {
    /* STUB */
    sphere.center.x = matrix.m[3][0];
    sphere.center.y = matrix.m[3][1];
    sphere.center.z = matrix.m[3][2];
    sphere.radius = extent.Length();
}

// Point-in-OBB test
int gbOBBox::IsColPoint(gbVec3D& point) {
    /* STUB */
    gbVec3D center;
    center.x = matrix.m[3][0];
    center.y = matrix.m[3][1];
    center.z = matrix.m[3][2];

    gbVec3D d;
    d.x = point.x - center.x;
    d.y = point.y - center.y;
    d.z = point.z - center.z;

    // Project point onto each axis and check bounds
    for (int i = 0; i < 3; i++) {
        gbVec3D axis;
        matrix.GetRow(&axis, i);
        float proj = d.DotProduct(&axis);
        float halfExt = ((float*)&extent)[i];
        if (fabsf(proj) > halfExt) return 0;
    }

    return 1;
}
