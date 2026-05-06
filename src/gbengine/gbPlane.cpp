/**
 * gbengine.dll - gbPlane
 * Plane primitive for collision detection
 */

#include "gbengine/gbengine_types.h"
#include <math.h>

// Constructor
gbPlane::gbPlane() {
    normal.x = 0.0f;
    normal.y = 0.0f;
    normal.z = 0.0f;
}

// Assignment operator
gbPlane& gbPlane::operator=(const gbPlane& p) {
    normal = p.normal;
    d = p.d;
    return *this;
}

// Plane-AABB collision test
int gbPlane::IsColAABB(gbAABBox& box) {
    // Calculate AABB center and extents
    gbVec3D center;
    center.x = (box.vMin.x + box.vMax.x) * 0.5f;
    center.y = (box.vMin.y + box.vMax.y) * 0.5f;
    center.z = (box.vMin.z + box.vMax.z) * 0.5f;

    gbVec3D extent;
    extent.x = (box.vMax.x - box.vMin.x) * 0.5f;
    extent.y = (box.vMax.y - box.vMin.y) * 0.5f;
    extent.z = (box.vMax.z - box.vMin.z) * 0.5f;

    // Project box extent onto plane normal
    float r = extent.x * fabsf(normal.x) +
              extent.y * fabsf(normal.y) +
              extent.z * fabsf(normal.z);

    // Compute distance from plane to box center
    float s = normal.DotProduct(&center) + d;

    // Collision if distance <= projected extent
    return fabsf(s) <= r ? 1 : 0;
}

// Plane-OBB collision test
int gbPlane::IsColOBB(gbOBBox& box) {
    // Get OBB axes and extents
    gbVec3D axis[3];
    box.matrix.GetRow(&axis[0], 0);
    box.matrix.GetRow(&axis[1], 1);
    box.matrix.GetRow(&axis[2], 2);

    // Project OBB extent onto plane normal
    float r = box.extent.x * fabsf(normal.DotProduct(&axis[0])) +
              box.extent.y * fabsf(normal.DotProduct(&axis[1])) +
              box.extent.z * fabsf(normal.DotProduct(&axis[2]));

    // Get OBB center
    gbVec3D center;
    center.x = box.matrix.m[3][0];
    center.y = box.matrix.m[3][1];
    center.z = box.matrix.m[3][2];

    // Compute distance from plane to OBB center
    float s = normal.DotProduct(&center) + d;

    // Collision if distance <= projected extent
    return fabsf(s) <= r ? 1 : 0;
}
