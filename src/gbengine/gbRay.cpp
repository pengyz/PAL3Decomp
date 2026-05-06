/**
 * gbengine.dll - gbRay
 * Ray primitive for collision detection
 */

#include "gbengine/gbengine_types.h"
#include <math.h>
#include <float.h>

// Moller-Trumbore ray-triangle intersection algorithm
extern "C" int __cdecl gbIntersectTriangle(
    gbVec3D* rayOrigin, gbVec3D* rayDir,
    gbVec3D* v0, gbVec3D* v1, gbVec3D* v2,
    gbVec3D* intersection);

// Constructor
gbRay::gbRay() {
    origin.x = origin.y = origin.z = 0.0f;
    direction.x = direction.y = 0.0f;
    direction.z = 1.0f;
}

// Assignment operator
gbRay& gbRay::operator=(const gbRay& r) {
    origin = r.origin;
    direction = r.direction;
    return *this;
}

// Intersect with plane defined by two vectors (plane normal and point on plane)
float gbRay::IntersectPlane(gbVec3D& normal, gbVec3D& pointOnPlane) {
    float denom = direction.DotProduct(&normal);
    if (fabsf(denom) < 0.0001f) {
        return -1.0f;  // Ray parallel to plane
    }

    gbVec3D toOrigin;
    toOrigin.x = origin.x - pointOnPlane.x;
    toOrigin.y = origin.y - pointOnPlane.y;
    toOrigin.z = origin.z - pointOnPlane.z;

    float t = -toOrigin.DotProduct(&normal) / denom;
    return t >= 0.0f ? t : -1.0f;
}

// Ray-AABB intersection (slab method)
int gbRay::IsColAABB(gbAABBox& box) {
    float tmin = -FLT_MAX, tmax = FLT_MAX;

    for (int i = 0; i < 3; i++) {
        float o = ((float*)&origin)[i];
        float d = ((float*)&direction)[i];
        float bmin = ((float*)&box.vMin)[i];
        float bmax = ((float*)&box.vMax)[i];

        if (fabsf(d) < 0.0001f) {
            if (o < bmin || o > bmax) return 0;
        } else {
            float t1 = (bmin - o) / d;
            float t2 = (bmax - o) / d;
            if (t1 > t2) { float temp = t1; t1 = t2; t2 = temp; }
            tmin = (t1 > tmin) ? t1 : tmin;
            tmax = (t2 < tmax) ? t2 : tmax;
            if (tmin > tmax) return 0;
        }
    }

    return tmin >= 0.0f ? 1 : 0;
}

// Ray-Quad intersection (test as two triangles)
int gbRay::IsColQuad(gbVec3D& v0, gbVec3D& v1, gbVec3D& v2) {
    // Quad is v0-v1-v2 forming first triangle, v0-v2-? forming second
    // Parameters only provide 3 vertices, so this might be degenerate
    // Try testing as triangle (3-parameter version)
    return IsColTriangle(v0, v1, v2);
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
    gbVec3D intersection;
    return gbIntersectTriangle(&origin, &direction, &v0, &v1, &v2, &intersection);
}

// Ray-Triangle intersection with barycentric coordinates
int gbRay::IsColTriangle(gbVec3D& v0, gbVec3D& v1, gbVec3D& v2, gbVec3D& bary) {
    gbVec3D intersection;
    if (!gbIntersectTriangle(&origin, &direction, &v0, &v1, &v2, &intersection)) {
        return 0;
    }

    // Compute barycentric coordinates
    gbVec3D e1, e2, p;
    e1.x = v1.x - v0.x; e1.y = v1.y - v0.y; e1.z = v1.z - v0.z;
    e2.x = v2.x - v0.x; e2.y = v2.y - v0.y; e2.z = v2.z - v0.z;
    p.x = intersection.x - v0.x; p.y = intersection.y - v0.y; p.z = intersection.z - v0.z;

    float d00 = e1.DotProduct(&e1);
    float d01 = e1.DotProduct(&e2);
    float d11 = e2.DotProduct(&e2);
    float d20 = p.DotProduct(&e1);
    float d21 = p.DotProduct(&e2);

    float denom = d00 * d11 - d01 * d01;
    if (fabsf(denom) < 0.0001f) {
        bary.x = bary.y = bary.z = 0.0f;
        return 1;
    }

    bary.y = (d11 * d20 - d01 * d21) / denom;
    bary.z = (d00 * d21 - d01 * d20) / denom;
    bary.x = 1.0f - bary.y - bary.z;

    return 1;
}
