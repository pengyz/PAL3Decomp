/**
 * gbengine.dll - BEZIER
 * Bezier curve implementation (cubic Bezier with 4 control points)
 */

#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_internal.h"
#include <math.h>
#include <string.h>

// Constructor with control points
BEZIER::BEZIER(gbVec3D* points) {
    if (points) {
        for (int i = 0; i < 4; i++) {
            ctrlPt[i] = points[i];
        }
    } else {
        memset(ctrlPt, 0, sizeof(ctrlPt));
    }
    dirty = 1;
    memset(coeff, 0, sizeof(coeff));
}

// Default constructor
BEZIER::BEZIER() {
    memset(ctrlPt, 0, sizeof(ctrlPt));
    dirty = 1;
    memset(coeff, 0, sizeof(coeff));
}

// Destructor
BEZIER::~BEZIER() {
    /* STUB */
    // Nothing to clean up
}

// Assignment operator
BEZIER& BEZIER::operator=(const BEZIER& b) {
    for (int i = 0; i < 4; i++) {
        ctrlPt[i] = b.ctrlPt[i];
        coeff[i] = b.coeff[i];
    }
    dirty = b.dirty;
    return *this;
}

// Get control points (returns pointer to array)
gbVec3D* BEZIER::GetControlPt() {
    return ctrlPt;
}

// Set control points (expects array of 4 points)
void BEZIER::SetControlPt(gbVec3D* points) {
    if (points) {
        for (int i = 0; i < 4; i++) {
            ctrlPt[i] = points[i];
        }
        dirty = 1;
    }
}

// Compute binomial coefficients for cubic Bezier
void BEZIER::computerCoefficient() {
    // Cubic Bezier coefficients: (1-t)^3, 3(1-t)^2*t, 3(1-t)*t^2, t^3
    // Binomial coefficients for n=3: 1, 3, 3, 1
    coeff[0] = 1;
    coeff[1] = 3;
    coeff[2] = 3;
    coeff[3] = 1;
    dirty = 0;
}

// Get interpolated point on curve at parameter t [0,1]
gbVec3D BEZIER::getInterpolatePoint(float t) {
    if (dirty) {
        computerCoefficient();
    }

    // Clamp t to [0,1]
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    float u = 1.0f - t;
    gbVec3D result;
    result.x = result.y = result.z = 0.0f;

    // Cubic Bezier formula: P(t) = sum(i=0..3) [ coeff[i] * (1-t)^(3-i) * t^i * ctrlPt[i] ]
    for (int i = 0; i < 4; i++) {
        float tPow = powf(t, (float)i);
        float uPow = powf(u, (float)(3 - i));
        float blend = (float)coeff[i] * tPow * uPow;

        result.x += ctrlPt[i].x * blend;
        result.y += ctrlPt[i].y * blend;
        result.z += ctrlPt[i].z * blend;
    }

    return result;
}

// Get tangent vector (derivative) at parameter t [0,1]
gbVec3D BEZIER::getTangentVector(float t) {
    if (dirty) {
        computerCoefficient();
    }

    // Clamp t to [0,1]
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    float u = 1.0f - t;
    gbVec3D result;
    result.x = result.y = result.z = 0.0f;

    // Derivative of cubic Bezier: P'(t) = 3 * sum(i=0..2) [ (1-t)^(2-i) * t^i * (ctrlPt[i+1] - ctrlPt[i]) ]
    for (int i = 0; i < 3; i++) {
        gbVec3D diff;
        diff.x = ctrlPt[i + 1].x - ctrlPt[i].x;
        diff.y = ctrlPt[i + 1].y - ctrlPt[i].y;
        diff.z = ctrlPt[i + 1].z - ctrlPt[i].z;

        float tPow = powf(t, (float)i);
        float uPow = powf(u, (float)(2 - i));
        float blend = 3.0f * tPow * uPow;

        result.x += diff.x * blend;
        result.y += diff.y * blend;
        result.z += diff.z * blend;
    }

    // Normalize tangent vector
    result.Normalize();
    return result;
}
