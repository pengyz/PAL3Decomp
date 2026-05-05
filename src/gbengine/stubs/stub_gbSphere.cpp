#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbSphere::gbSphere() {}

int gbSphere::IsColPoint(gbVec3D & p1) { return 0; }

int gbSphere::IsColSphere(gbVec3D & p1, float p2) { return 0; }

int gbSphere::IsColTriangle(gbVec3D & p1, gbVec3D & p2, gbVec3D & p3) { return 0; }

gbSphere & gbSphere::operator=(gbSphere const & p1) { static gbSphere _d; return _d; }

