/**
 * gbengine.dll - gbRay
 * Ray primitive for collision detection
 */

#include "gbengine/gbengine_types.h"
#include <math.h>
#include <float.h>

// Constructor
gbRay::gbRay() {
    origin.x = origin.y = origin.z = 0.0f;
    direction.x = direction.y = 0.0f;
    direction.z = 1.0f;
}

// Assignment operator
gbRay& gbRay::operator=(const gbRay& r) {
    origin = r.Origin;
    direction = r.Direction;
    return *this;
}

float gbRay::IntersectPlane(gbVec3D& normal, gbVec3D& point) {
    float denom = direction.y * normal.y + direction.z * normal.z + direction.x * normal.x;
    if (denom >= 0.000001f || denom <= -0.000001f) {
        return ((point.z - origin.z) * normal.z
              + (point.x - origin.x) * normal.x
              + (point.y - origin.y) * normal.y) / denom;
    }
    return FLT_MAX;
}

int gbRay::IsColAABB(gbAABBox& box) {
    gbVec3D unitX, unitY, unitZ;
    unitX.x = 1.0f; unitX.y = 0.0f; unitX.z = 0.0f;
    unitY.x = 0.0f; unitY.y = 1.0f; unitY.z = 0.0f;
    unitZ.x = 0.0f; unitZ.y = 0.0f; unitZ.z = 1.0f;

    gbVec3D delta;
    float t1, t2, t3;

    delta.x = box.vMax.x; delta.y = box.vMax.y; delta.z = box.vMax.z;
    if (direction.x >= 0.000001f || direction.x <= -0.000001f) {
        delta.x -= origin.x; delta.y -= origin.y; delta.z -= origin.z;
        t1 = delta.DotProduct(&unitX) / direction.x;
    } else {
        t1 = FLT_MAX;
    }

    delta.x = box.vMax.x; delta.y = box.vMax.y; delta.z = box.vMax.z;
    if (direction.y >= 0.000001f || direction.y <= -0.000001f) {
        delta.x -= origin.x; delta.y -= origin.y; delta.z -= origin.z;
        t2 = delta.DotProduct(&unitY) / direction.y;
    } else {
        t2 = FLT_MAX;
    }

    delta.x = box.vMax.x; delta.y = box.vMax.y; delta.z = box.vMax.z;
    if (direction.z >= 0.000001f || direction.z <= -0.000001f) {
        delta.x -= origin.x; delta.y -= origin.y; delta.z -= origin.z;
        t3 = delta.DotProduct(&unitZ) / direction.z;
    } else {
        t3 = FLT_MAX;
    }

    if (t1 != FLT_MAX) {
        if (t2 != FLT_MAX && t3 != FLT_MAX) {
            float t4, t5, t6;

            delta.x = box.vMin.x; delta.y = box.vMin.y; delta.z = box.vMin.z;
            float dirX = direction.x;
            if (dirX >= 0.000001f || dirX <= -0.000001f) {
                delta.x -= origin.x; delta.y -= origin.y; delta.z -= origin.z;
                t4 = delta.DotProduct(&unitX) / dirX;
            } else {
                t4 = FLT_MAX;
            }

            float dirDotY = unitY.x * direction.x + unitY.y * direction.y + unitY.z * direction.z;
            delta.x = box.vMin.x; delta.y = box.vMin.y; delta.z = box.vMin.z;
            if (dirDotY >= 0.000001f || dirDotY <= -0.000001f) {
                delta.x -= origin.x; delta.y -= origin.y; delta.z -= origin.z;
                t5 = delta.DotProduct(&unitY) / dirDotY;
            } else {
                t5 = FLT_MAX;
            }

            float dirDotZ = direction.DotProduct(&unitZ);
            delta.x = box.vMin.x; delta.y = box.vMin.y; delta.z = box.vMin.z;
            if (dirDotZ >= 0.000001f || dirDotZ <= -0.000001f) {
                delta.x -= origin.x; delta.y -= origin.y; delta.z -= origin.z;
                t6 = delta.DotProduct(&unitZ) / dirDotZ;
            } else {
                t6 = FLT_MAX;
            }

            if (t1 > t4) t4 = t1;
            if (t2 > t5) t5 = t2;
            if (t3 > t6) t6 = t3;

            float tFar = (t5 >= t6) ? t6 : t5;
            float tEntry;
            if (t4 >= tFar) {
                tEntry = (t5 >= t6) ? t6 : t5;
            } else {
                tEntry = t4;
            }

            if (tEntry < 0.0f) return 0;
            return tEntry <= tFar;
        }

        if (origin.y < box.vMin.y) return 0;
        return origin.y <= box.vMax.y
            && origin.z >= box.vMin.z
            && origin.z <= box.vMax.z;
    }

    if (t2 != FLT_MAX) {
        if (origin.x < box.vMin.x) return 0;
        return origin.x <= box.vMax.x
            && origin.z >= box.vMin.z
            && origin.z <= box.vMax.z;
    }

    if (origin.y < box.vMin.y || origin.y > box.vMax.y || origin.x < box.vMin.x)
        return 0;
    return origin.x <= box.vMax.x;
}

int gbRay::IsColOBB(gbOBBox& obb) {
    gbVec3D axisX, axisY, axisZ;
    gbVec3D obbCenter, obbCenterNeg;
    gbVec3D temp, delta;

    axisX.x = 0.0f; axisX.y = 0.0f; axisX.z = 0.0f;
    axisY.x = 0.0f; axisY.y = 0.0f; axisY.z = 0.0f;
    axisZ.x = 0.0f; axisZ.y = 0.0f; axisZ.z = 0.0f;
    obbCenter.x = 0.0f; obbCenter.y = 0.0f; obbCenter.z = 0.0f;

    temp.x = 1.0f; temp.y = 0.0f; temp.z = 0.0f;
    obb.trans.Rotate(&temp, &axisX);

    temp.x = 0.0f; temp.y = 1.0f; temp.z = 0.0f;
    obb.trans.Rotate(&temp, &axisY);

    temp.x = 0.0f; temp.y = 0.0f; temp.z = 1.0f;
    obb.trans.Rotate(&temp, &axisZ);

    temp.x = obb.xlen * 0.5f;
    temp.y = obb.ylen * 0.5f;
    temp.z = obb.zlen * 0.5f;
    obb.trans.Transform(&temp, &obbCenter);

    float t1, t2, t3, t4, t5, t6;

    float dirDotX = axisX.z * direction.z + axisX.y * direction.y + axisX.x * direction.x;
    delta.x = obbCenter.x; delta.y = obbCenter.y; delta.z = obbCenter.z;
    if (dirDotX >= 0.000001f || dirDotX <= -0.000001f) {
        delta.x -= origin.x; delta.y -= origin.y; delta.z -= origin.z;
        t1 = delta.DotProduct(&axisX) / dirDotX;
    } else {
        t1 = FLT_MAX;
    }

    float dirDotY = axisY.z * direction.z + axisY.y * direction.y + axisY.x * direction.x;
    delta.x = obbCenter.x; delta.y = obbCenter.y; delta.z = obbCenter.z;
    if (dirDotY >= 0.000001f || dirDotY <= -0.000001f) {
        delta.x -= origin.x; delta.y -= origin.y; delta.z -= origin.z;
        t2 = delta.DotProduct(&axisY) / dirDotY;
    } else {
        t2 = FLT_MAX;
    }

    float dirDotZ = axisZ.z * direction.z + axisZ.y * direction.y + axisZ.x * direction.x;
    delta.x = obbCenter.x; delta.y = obbCenter.y; delta.z = obbCenter.z;
    if (dirDotZ >= 0.000001f || dirDotZ <= -0.000001f) {
        delta.x -= origin.x; delta.y -= origin.y; delta.z -= origin.z;
        t3 = delta.DotProduct(&axisZ) / dirDotZ;
    } else {
        t3 = FLT_MAX;
    }

    temp.x = -temp.x; temp.y = -temp.y; temp.z = -temp.z;
    obb.trans.Transform(&temp, &obbCenterNeg);

    dirDotX = axisX.z * direction.z + axisX.y * direction.y + axisX.x * direction.x;
    delta.x = obbCenterNeg.x; delta.y = obbCenterNeg.y; delta.z = obbCenterNeg.z;
    if (dirDotX >= 0.000001f || dirDotX <= -0.000001f) {
        delta.x -= origin.x; delta.y -= origin.y; delta.z -= origin.z;
        t4 = delta.DotProduct(&axisX) / dirDotX;
    } else {
        t4 = FLT_MAX;
    }

    float dirDotY2 = direction.DotProduct(&axisY);
    delta.x = obbCenterNeg.x; delta.y = obbCenterNeg.y; delta.z = obbCenterNeg.z;
    if (dirDotY2 >= 0.000001f || dirDotY2 <= -0.000001f) {
        delta.x -= origin.x; delta.y -= origin.y; delta.z -= origin.z;
        t5 = delta.DotProduct(&axisY) / dirDotY2;
    } else {
        t5 = FLT_MAX;
    }

    t6 = IntersectPlane(axisZ, obbCenterNeg);

    if (t1 > t4) { float s = t4; t4 = t1; t1 = s; }
    if (t2 > t5) { float s = t5; t5 = t2; t2 = s; }
    if (t3 > t6) { float s = t6; t6 = t3; t3 = s; }

    float tNear;
    if (t2 <= t3) tNear = t3; else tNear = t2;
    if (t1 <= tNear) { /* keep */ } else { tNear = t1; }

    float tFar;
    if (t5 >= t6) tFar = t6; else tFar = t5;
    if (t4 >= tFar) { /* keep */ } else { tFar = t4; }

    return tNear <= tFar;
}

// Ray-OBB intersection (via inverse transform to local AABB)
int gbRay::IsColOBB_H(gbOBBox& obb) {
    gbMatrix4 invMatrix = obb.trans;
    invMatrix.Invert();

    gbVec3D localOrigin, localDir;
    invMatrix.Transform(&origin, &localOrigin);
    invMatrix.Rotate(&direction, &localDir);

    float halfX = obb.xlen * 0.5f;
    float halfY = obb.ylen * 0.5f;
    float halfZ = obb.zlen * 0.5f;

    gbAABBox localBox;
    localBox.vMin.x = -halfX; localBox.vMin.y = -halfY; localBox.vMin.z = -halfZ;
    localBox.vMax.x = halfX;  localBox.vMax.y = halfY;  localBox.vMax.z = halfZ;

    gbRay localRay;
    localRay.Origin = localOrigin;
    localRay.Direction = localDir;
    return localRay.IsColAABB(localBox);
}

// Ray-Quad intersection (Moller-Trumbore, quad bounds)
int gbRay::IsColQuad(gbVec3D& v0, gbVec3D& v1, gbVec3D& v2) {
    gbVec3D pvec, qvec;
    gbVec3D edge1, edge2, tvec;

    pvec.x = 0.0f; pvec.y = 0.0f; pvec.z = 0.0f;
    qvec.x = 0.0f; qvec.y = 0.0f; qvec.z = 0.0f;

    edge1.x = v1.x - v0.x;
    edge1.y = v1.y - v0.y;
    edge1.z = v1.z - v0.z;

    edge2.x = v2.x - v0.x;
    edge2.y = v2.y - v0.y;
    edge2.z = v2.z - v0.z;

    tvec.x = origin.x - v0.x;
    tvec.y = origin.y - v0.y;
    tvec.z = origin.z - v0.z;

    direction.CrossProduct(&edge2, &pvec);
    tvec.CrossProduct(&edge1, &qvec);

    float det = pvec.z * edge1.z + pvec.y * edge1.y + pvec.x * edge1.x;
    if (det != 0.0f) {
        float inv_det = 1.0f / det;
        float u = (pvec.z * tvec.z + pvec.y * tvec.y + pvec.x * tvec.x) * inv_det;
        float v = (qvec.z * direction.z + qvec.y * direction.y + qvec.x * direction.x) * inv_det;
        if (u >= 0.0f && v >= 0.0f && u < 1.0f && v < 1.0f)
            return 1;
    }
    return 0;
}

// Ray-Sphere intersection
int gbRay::IsColSphere(gbSphere& sphere) {
    gbVec3D m;
    m.x = origin.x - sphere.center.x;
    m.y = origin.y - sphere.center.y;
    m.z = origin.z - sphere.center.z;

    float b = m.DotProduct(&direction);
    float c = m.DotProduct(&m) - sphere.radius * sphere.radius;

    if (c > 0.0f && b > 0.0f) return 0;

    float discr = b * b - c;
    if (discr < 0.0f) return 0;

    float t = -b - sqrtf(discr);
    return t >= 0.0f ? 1 : 0;
}

// Ray-Triangle intersection (Moller-Trumbore)
int gbRay::IsColTriangle(gbVec3D& v0, gbVec3D& v1, gbVec3D& v2) {
    gbVec3D pvec, qvec;
    gbVec3D edge1, edge2, tvec;

    pvec.x = 0.0f; pvec.y = 0.0f; pvec.z = 0.0f;
    qvec.x = 0.0f; qvec.y = 0.0f; qvec.z = 0.0f;

    edge1.x = v1.x - v0.x;
    edge1.y = v1.y - v0.y;
    edge1.z = v1.z - v0.z;

    edge2.x = v2.x - v0.x;
    edge2.y = v2.y - v0.y;
    edge2.z = v2.z - v0.z;

    tvec.x = origin.x - v0.x;
    tvec.y = origin.y - v0.y;
    tvec.z = origin.z - v0.z;

    direction.CrossProduct(&edge2, &pvec);
    tvec.CrossProduct(&edge1, &qvec);

    float det = pvec.z * edge1.z + pvec.y * edge1.y + pvec.x * edge1.x;
    if (det != 0.0f) {
        float inv_det = 1.0f / det;
        float u = (pvec.z * tvec.z + pvec.y * tvec.y + pvec.x * tvec.x) * inv_det;
        float v = (qvec.z * direction.z + qvec.y * direction.y + qvec.x * direction.x) * inv_det;
        if (u >= 0.0f && v >= 0.0f && v + u < 1.0f)
            return 1;
    }
    return 0;
}

// Ray-Triangle intersection with intersection point output
int gbRay::IsColTriangle(gbVec3D& v0, gbVec3D& v1, gbVec3D& v2, gbVec3D& hitPoint) {
    gbVec3D pvec, qvec;
    gbVec3D edge1, edge2, tvec;

    pvec.x = 0.0f; pvec.y = 0.0f; pvec.z = 0.0f;
    qvec.x = 0.0f; qvec.y = 0.0f; qvec.z = 0.0f;

    edge1.x = v1.x - v0.x;
    edge1.y = v1.y - v0.y;
    edge1.z = v1.z - v0.z;

    edge2.x = v2.x - v0.x;
    edge2.y = v2.y - v0.y;
    edge2.z = v2.z - v0.z;

    tvec.x = origin.x - v0.x;
    tvec.y = origin.y - v0.y;
    tvec.z = origin.z - v0.z;

    direction.CrossProduct(&edge2, &pvec);
    tvec.CrossProduct(&edge1, &qvec);

    float det = pvec.z * edge1.z + pvec.y * edge1.y + pvec.x * edge1.x;
    if (det == 0.0f)
        return 0;

    float inv_det = 1.0f / det;
    float u = (pvec.z * tvec.z + pvec.y * tvec.y + pvec.x * tvec.x) * inv_det;
    float v = (qvec.z * direction.z + qvec.y * direction.y + qvec.x * direction.x) * inv_det;
    if (u < 0.0f || v < 0.0f || v + u > 1.0f)
        return 0;

    float w = 1.0f - u - v;
    hitPoint.x = w * v0.x + u * v1.x + v * v2.x;
    hitPoint.y = w * v0.y + v * v2.y + u * v1.y;
    hitPoint.z = w * v0.z + u * v1.z + v * v2.z;
    return 1;
}
