/**
 * gbengine.dll - gbOBBox
 * Oriented Bounding Box primitive
 */

#include "gbengine/gbengine_types.h"
#include <math.h>

gbOBBox::gbOBBox() {
    matrix.LoadIdentity();
}

gbOBBox& gbOBBox::operator=(const gbOBBox& box) {
    matrix = box.trans;
    extent.x = box.xlen;
    extent.y = box.ylen;
    extent.z = box.zlen;
    return *this;
}

gbVec3D gbOBBox::GetCenter() const {
    gbVec3D result;
    result.x = matrix.m[3][0];
    result.y = matrix.m[3][1];
    result.z = matrix.m[3][2];
    return result;
}

// Get radius (distance from center to corner)
float gbOBBox::GetRadius() const {
    float r = (float)sqrt(extent.x * extent.x + extent.y * extent.y + extent.z * extent.z);
    return r * 0.5f;
}

// Get radius in a specific direction
float gbOBBox::GetRadiusInDirection(const gbVec3D& dir) const {
    float r = 0.0f;
    for (int i = 0; i < 3; i++) {
        gbVec3D axis;
        ((gbMatrix4*)&matrix)->GetRow(&axis, i);
        float proj = fabsf(dir.DotProduct(&axis));
        r += proj * ((float*)&xlen)[i];
    }
    return r;
}

void gbOBBox::GetAABBox(gbAABBox& aabb) {
    aabb.vMin.x = extent.x * -0.5f;
    aabb.vMin.y = extent.y * -0.5f;
    aabb.vMin.z = extent.z * -0.5f;
    aabb.vMax.x = extent.x * 0.5f;
    aabb.vMax.y = extent.y * 0.5f;
    aabb.vMax.z = extent.z * 0.5f;
    aabb.Transform(&matrix);
}

// 0x10027d10
void gbOBBox::GetSphere(gbSphere& sphere) {
    sphere.center.x = matrix.m[3][0];
    sphere.center.y = matrix.m[3][1];
    sphere.center.z = matrix.m[3][2];
    sphere.radius = (float)sqrt(extent.x * extent.x + extent.y * extent.y + extent.z * extent.z) * 0.5f;
}

// OBB-OBB collision using Separating Axis Theorem
int gbOBBox::IsColOBB(gbOBBox* other) {
    gbVec3D T;
    T.x = other->trans.m[3][0] - matrix.m[3][0];
    T.y = other->trans.m[3][1] - matrix.m[3][1];
    T.z = other->trans.m[3][2] - matrix.m[3][2];

    int i;
    for (i = 0; i < 3; i++) {
        gbVec3D axis;
        matrix.GetRow(&axis, i);
        float dist = fabsf(T.DotProduct(&axis));
        float radiusA = ((float*)&xlen)[i];
        float radiusB = other->GetRadiusInDirection(axis);
        if (dist > radiusA + radiusB) return 0;

        other->trans.GetRow(&axis, i);
        dist = fabsf(T.DotProduct(&axis));
        radiusA = GetRadiusInDirection(axis);
        radiusB = ((float*)&other->extent)[i];
        if (dist > radiusA + radiusB) return 0;
    }

    for (i = 0; i < 3; i++) {
        gbVec3D axisA;
        matrix.GetRow(&axisA, i);
        for (int j = 0; j < 3; j++) {
            gbVec3D axisB;
            other->trans.GetRow(&axisB, j);

            gbVec3D cross;
            axisA.CrossProduct(&axisB, &cross);

            float len = cross.Length();
            if (len < 0.0001f) continue;

            float dist = fabsf(T.DotProduct(&cross)) / len;
            float radiusA = GetRadiusInDirection(cross) / len;
            float radiusB = other->GetRadiusInDirection(cross) / len;

            if (dist > radiusA + radiusB) return 0;
        }
    }

    return 1;
}

// Point-in-OBB test
int gbOBBox::IsColPoint(gbVec3D& point) {
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
        float halfExt = ((float*)&xlen)[i];
        if (fabsf(proj) > halfExt) return 0;
    }

    return 1;
}
