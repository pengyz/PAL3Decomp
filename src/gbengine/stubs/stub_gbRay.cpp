#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbRay::gbRay() {}

float gbRay::IntersectPlane(gbVec3D & p1, gbVec3D & p2) { return 0.0f; }

int gbRay::IsColAABB(gbAABBox & p1) { return 0; }

int gbRay::IsColOBB(gbOBBox & p1) { return 0; }

int gbRay::IsColOBB_H(gbOBBox & p1) { return 0; }

int gbRay::IsColQuad(gbVec3D & p1, gbVec3D & p2, gbVec3D & p3) { return 0; }

int gbRay::IsColSphere(gbSphere & p1) { return 0; }

int gbRay::IsColTriangle(gbVec3D & p1, gbVec3D & p2, gbVec3D & p3) { return 0; }

int gbRay::IsColTriangle(gbVec3D & p1, gbVec3D & p2, gbVec3D & p3, gbVec3D & p4) { return 0; }

gbRay & gbRay::operator=(gbRay const & p1) { static gbRay _d; return _d; }

