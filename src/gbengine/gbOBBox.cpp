/**
 * gbengine.dll - gbOBBox
 * Oriented Bounding Box primitive
 */

#include "gbengine/gbengine_types.h"
#include <math.h>

gbOBBox::gbOBBox() {
    trans.LoadIdentity();
}

gbOBBox& gbOBBox::operator=(const gbOBBox& box) {
    trans = box.trans;
    xlen = box.xlen;
    ylen = box.ylen;
    zlen = box.zlen;
    return *this;
}

gbVec3D gbOBBox::GetCenter() const {
    gbVec3D result;
    result.x = trans.m[3][0];
    result.y = trans.m[3][1];
    result.z = trans.m[3][2];
    return result;
}

// Get radius (distance from center to corner)
float gbOBBox::GetRadius() const {
    float r = (float)sqrt(xlen * xlen + ylen * ylen + zlen * zlen);
    return r * 0.5f;
}

// Get radius in a specific direction
float gbOBBox::GetRadiusInDirection(const gbVec3D& dir) const {
    float r = 0.0f;
    for (int i = 0; i < 3; i++) {
        gbVec3D axis;
        ((gbMatrix4*)&trans)->GetRow(&axis, i);
        float proj = fabsf(dir.DotProduct(&axis));
        r += proj * ((float*)&xlen)[i];
    }
    return r;
}

void gbOBBox::GetAABBox(gbAABBox& aabb) {
    aabb.vMin.x = xlen * -0.5f;
    aabb.vMin.y = ylen * -0.5f;
    aabb.vMin.z = zlen * -0.5f;
    aabb.vMax.x = xlen * 0.5f;
    aabb.vMax.y = ylen * 0.5f;
    aabb.vMax.z = zlen * 0.5f;
    aabb.Transform(&trans);
}

// 0x10027d10
void gbOBBox::GetSphere(gbSphere& sphere) {
    sphere.center.x = trans.m[3][0];
    sphere.center.y = trans.m[3][1];
    sphere.center.z = trans.m[3][2];
    sphere.radius = (float)sqrt(xlen * xlen + ylen * ylen + zlen * zlen) * 0.5f;
}

// OBB-OBB collision using Separating Axis Theorem
int gbOBBox::IsColOBB(gbOBBox* other) {
    gbVec3D T;
    T.x = other->trans.m[3][0] - trans.m[3][0];
    T.y = other->trans.m[3][1] - trans.m[3][1];
    T.z = other->trans.m[3][2] - trans.m[3][2];

    int i;
    for (i = 0; i < 3; i++) {
        gbVec3D axis;
        trans.GetRow(&axis, i);
        float dist = fabsf(T.DotProduct(&axis));
        float radiusA = ((float*)&xlen)[i];
        float radiusB = other->GetRadiusInDirection(axis);
        if (dist > radiusA + radiusB) return 0;

        other->trans.GetRow(&axis, i);
        dist = fabsf(T.DotProduct(&axis));
        radiusA = GetRadiusInDirection(axis);
        radiusB = ((float*)&other->xlen)[i];
        if (dist > radiusA + radiusB) return 0;
    }

    for (i = 0; i < 3; i++) {
        gbVec3D axisA;
        trans.GetRow(&axisA, i);
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
    center.x = trans.m[3][0];
    center.y = trans.m[3][1];
    center.z = trans.m[3][2];

    gbVec3D d;
    d.x = point.x - center.x;
    d.y = point.y - center.y;
    d.z = point.z - center.z;

    // Project point onto each axis and check bounds
    for (int i = 0; i < 3; i++) {
        gbVec3D axis;
        trans.GetRow(&axis, i);
        float proj = d.DotProduct(&axis);
        float halfExt = ((float*)&xlen)[i];
        if (fabsf(proj) > halfExt) return 0;
    }

    return 1;
}
