#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbRotMatrix::gbRotMatrix() {}

bool const gbRotMatrix::IsOrthonormal() { return false; }

bool const gbRotMatrix::IsValid() { return false; }

void gbRotMatrix::LoadIdentity() { }

void gbRotMatrix::Rotate(gbVec3D * p1, gbVec3D * p2) { }

void gbRotMatrix::operator*=(gbRotMatrix & p1) { }

void gbRotMatrix::operator=(gbRotMatrix & p1) { }

