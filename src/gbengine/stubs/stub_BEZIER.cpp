#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

void BEZIER::computerCoefficient() { }

BEZIER::BEZIER(gbVec3D * p1) {}

BEZIER::BEZIER() {}

BEZIER::~BEZIER() {}

BEZIER & BEZIER::operator=(BEZIER const & p1) { static BEZIER _d; return _d; }

gbVec3D * BEZIER::GetControlPt() { return 0; }

gbVec3D BEZIER::getInterpolatePoint(float p1) { return 0; }

gbVec3D BEZIER::getTangentVector(float p1) { return 0; }

void BEZIER::SetControlPt(gbVec3D * p1) { }

