#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

bool gbVec3D::IsValid() const { return false; }

bool gbVec3D::operator==(gbVec3D const & p1) { return false; }

float gbVec3D::LengthSquare() const { return 0.0f; }

int gbVec3D::IsNormal() { return 0; }

gbVec3D gbVec3D::operator-() const { return 0; }

void gbVec3D::Inverse() { }

void gbVec3D::Zero() { }

void gbVec3D::`default constructor closure'() { }

void gbVec3D::operator*=(float p1) { }

void gbVec3D::operator+=(gbVec3D const & p1) { }

void gbVec3D::operator-=(gbVec3D const & p1) { }

void gbVec3D::operator/=(float p1) { }

void gbVec3D::operator=(gbVec3D const & p1) { }

