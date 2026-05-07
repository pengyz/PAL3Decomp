/**
 * gbengine.dll - gbSphere
 * Sphere primitive for collision detection
 */

#include "gbengine/gbengine_types.h"
#include <math.h>

// Constructor
gbSphere::gbSphere() {
    radius = 1.0f;
    center.x = center.y = center.z = 0.0f;
}

// Assignment operator
gbSphere& gbSphere::operator=(const gbSphere& s) {
    radius = s.radius;
    center = s.center;
    return *this;
}

// Point-in-sphere test
int gbSphere::IsColPoint(gbVec3D& point) {
    gbVec3D d;
    d.x = point.x - center.x;
    d.y = point.y - center.y;
    d.z = point.z - center.z;
    float distSq = d.LengthSquare();
    return distSq <= (radius * radius) ? 1 : 0;
}

// Sphere-Sphere collision test
int gbSphere::IsColSphere(gbVec3D& otherCenter, float otherRadius) {
    gbVec3D d;
    d.x = otherCenter.x - center.x;
    d.y = otherCenter.y - center.y;
    d.z = otherCenter.z - center.z;
    float dist = d.Length();
    float radiusSum = radius + otherRadius;
    return dist <= radiusSum ? 1 : 0;
}

// Sphere-Triangle collision test
int gbSphere::IsColTriangle(gbVec3D& v0, gbVec3D& v1, gbVec3D& v2) {
    // Compute triangle edges
    gbVec3D e0, e1, e2;
    e0.x = v1.x - v0.x; e0.y = v1.y - v0.y; e0.z = v1.z - v0.z;
    e1.x = v2.x - v1.x; e1.y = v2.y - v1.y; e1.z = v2.z - v1.z;
    e2.x = v0.x - v2.x; e2.y = v0.y - v2.y; e2.z = v0.z - v2.z;

    // Compute triangle normal
    gbVec3D normal;
    e0.CrossProduct(&e1, &normal);
    normal.Normalize();

    // Check distance from sphere center to plane
    gbVec3D toCenter;
    toCenter.x = center.x - v0.x;
    toCenter.y = center.y - v0.y;
    toCenter.z = center.z - v0.z;
    float dist = fabsf(normal.DotProduct(&toCenter));

    if (dist > radius) return 0;

    // Project sphere center onto triangle plane
    gbVec3D projCenter;
    float offset = normal.DotProduct(&toCenter);
    projCenter.x = center.x - normal.x * offset;
    projCenter.y = center.y - normal.y * offset;
    projCenter.z = center.z - normal.z * offset;

    // Check if projected center is inside triangle
    // Using edge cross product method
    gbVec3D c0, c1, c2;
    gbVec3D p0, p1, p2;

    p0.x = projCenter.x - v0.x; p0.y = projCenter.y - v0.y; p0.z = projCenter.z - v0.z;
    p1.x = projCenter.x - v1.x; p1.y = projCenter.y - v1.y; p1.z = projCenter.z - v1.z;
    p2.x = projCenter.x - v2.x; p2.y = projCenter.y - v2.y; p2.z = projCenter.z - v2.z;

    e0.CrossProduct(&p0, &c0);
    e1.CrossProduct(&p1, &c1);
    e2.CrossProduct(&p2, &c2);

    float d0 = normal.DotProduct(&c0);
    float d1 = normal.DotProduct(&c1);
    float d2 = normal.DotProduct(&c2);

    if (d0 >= 0.0f && d1 >= 0.0f && d2 >= 0.0f) {
        return 1;  // Inside triangle
    }

    // Check distance to edges
    // Edge v0-v1
    gbVec3D v0v1;
    v0v1.x = v1.x - v0.x; v0v1.y = v1.y - v0.y; v0v1.z = v1.z - v0.z;
    gbVec3D v0c;
    v0c.x = center.x - v0.x; v0c.y = center.y - v0.y; v0c.z = center.z - v0.z;
    float t = v0c.DotProduct(&v0v1) / v0v1.DotProduct(&v0v1);
    if (t >= 0.0f && t <= 1.0f) {
        gbVec3D closest;
        closest.x = v0.x + v0v1.x * t;
        closest.y = v0.y + v0v1.y * t;
        closest.z = v0.z + v0v1.z * t;
        gbVec3D toClosest;
        toClosest.x = center.x - closest.x;
        toClosest.y = center.y - closest.y;
        toClosest.z = center.z - closest.z;
        if (toClosest.LengthSquare() <= radius * radius) return 1;
    }

    // Edge v1-v2
    gbVec3D v1v2;
    v1v2.x = v2.x - v1.x; v1v2.y = v2.y - v1.y; v1v2.z = v2.z - v1.z;
    gbVec3D v1c;
    v1c.x = center.x - v1.x; v1c.y = center.y - v1.y; v1c.z = center.z - v1.z;
    t = v1c.DotProduct(&v1v2) / v1v2.DotProduct(&v1v2);
    if (t >= 0.0f && t <= 1.0f) {
        gbVec3D closest;
        closest.x = v1.x + v1v2.x * t;
        closest.y = v1.y + v1v2.y * t;
        closest.z = v1.z + v1v2.z * t;
        gbVec3D toClosest;
        toClosest.x = center.x - closest.x;
        toClosest.y = center.y - closest.y;
        toClosest.z = center.z - closest.z;
        if (toClosest.LengthSquare() <= radius * radius) return 1;
    }

    // Edge v2-v0
    gbVec3D v2v0;
    v2v0.x = v0.x - v2.x; v2v0.y = v0.y - v2.y; v2v0.z = v0.z - v2.z;
    gbVec3D v2c;
    v2c.x = center.x - v2.x; v2c.y = center.y - v2.y; v2c.z = center.z - v2.z;
    t = v2c.DotProduct(&v2v0) / v2v0.DotProduct(&v2v0);
    if (t >= 0.0f && t <= 1.0f) {
        gbVec3D closest;
        closest.x = v2.x + v2v0.x * t;
        closest.y = v2.y + v2v0.y * t;
        closest.z = v2.z + v2v0.z * t;
        gbVec3D toClosest;
        toClosest.x = center.x - closest.x;
        toClosest.y = center.y - closest.y;
        toClosest.z = center.z - closest.z;
        if (toClosest.LengthSquare() <= radius * radius) return 1;
    }

    // Check distance to vertices
    gbVec3D cv0, cv1, cv2;
    cv0.x = center.x - v0.x; cv0.y = center.y - v0.y; cv0.z = center.z - v0.z;
    cv1.x = center.x - v1.x; cv1.y = center.y - v1.y; cv1.z = center.z - v1.z;
    cv2.x = center.x - v2.x; cv2.y = center.y - v2.y; cv2.z = center.z - v2.z;

    if (cv0.LengthSquare() <= radius * radius) return 1;
    if (cv1.LengthSquare() <= radius * radius) return 1;
    if (cv2.LengthSquare() <= radius * radius) return 1;

    return 0;
}
