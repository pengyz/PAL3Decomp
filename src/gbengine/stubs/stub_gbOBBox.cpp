#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbOBBox::gbOBBox() {}

float gbOBBox::GetRadius() const { return 0.0f; }

float gbOBBox::GetRadiusInDirection(gbVec3D const & p1) const { return 0.0f; }

int gbOBBox::IsColOBB(gbOBBox * p1) { return 0; }

int gbOBBox::IsColPoint(gbVec3D & p1) { return 0; }

gbOBBox & gbOBBox::operator=(gbOBBox const & p1) { static gbOBBox _d; return _d; }

gbVec3D gbOBBox::GetCenter() const { return 0; }

void gbOBBox::GetAABBox(gbAABBox & p1) { }

void gbOBBox::GetSphere(gbSphere & p1) { }

