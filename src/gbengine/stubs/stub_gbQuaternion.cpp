#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbQuaternion::gbQuaternion() {}

bool const gbQuaternion::IsUnit() const { return false; }

bool const gbQuaternion::IsValid() const { return false; }

float gbQuaternion::Normalize() { return 0.0f; }

float const gbQuaternion::Magnitude() { return 0; }

int gbQuaternion::IsNormal() { return 0; }

gbQuaternion & gbQuaternion::operator=(gbQuaternion const & p1) { static gbQuaternion _d; return _d; }

void gbQuaternion::GetAxisAngle(gbVec3D * p1, float * p2) { }

void gbQuaternion::GetMatrix(gbMatrix4 * p1) const { }

void gbQuaternion::GetVec3D(float * p1, gbVec3D * p2) { }

void gbQuaternion::Inverse() { }

void gbQuaternion::MultiplyBy(gbQuaternion * p1, gbQuaternion * p2) { }

void gbQuaternion::RotateVector(gbVec3D * p1, gbVec3D * p2) { }

void gbQuaternion::SetAxisAngle(gbVec3D * p1, float p2) { }

void gbQuaternion::SetMatrix(gbMatrix4 * p1) { }

void gbQuaternion::SetTwoVector(gbVec3D * p1, gbVec3D * p2) { }

void gbQuaternion::SetUnit() { }

void gbQuaternion::SetVec3D(float p1, gbVec3D * p2) { }

void gbQuaternion::SetYawPitchRoll(float p1, float p2, float p3) { }

void gbQuaternion::Slerp(gbQuaternion * p1, gbQuaternion * p2, float p3) { }

