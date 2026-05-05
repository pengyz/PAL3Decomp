#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbMatrix4::gbMatrix4() {}

bool gbMatrix4::IsIdentity() const { return false; }

bool gbMatrix4::IsOrthonormal() const { return false; }

bool gbMatrix4::IsValid() const { return false; }

float gbMatrix4::operator()(int p1, int p2) { return 0.0f; }

gbVec3D * gbMatrix4::GetColumn(gbVec3D * p1, int p2) const { return 0; }

gbVec3D * gbMatrix4::GetRow(gbVec3D * p1, int p2) const { return 0; }

gbVec4D * gbMatrix4::GetColumn(gbVec4D * p1, int p2) const { return 0; }

gbVec4D * gbMatrix4::GetRow(gbVec4D * p1, int p2) const { return 0; }

void gbMatrix4::Invert(gbMatrix4 * p1) const { }

void gbMatrix4::LeftMultiply(gbMatrix4 const & p1) { }

void gbMatrix4::LeftMultiply(gbQuaternion const & p1) { }

void gbMatrix4::LeftScale(float p1, float p2, float p3) { }

void gbMatrix4::LeftTranslate(float p1, float p2, float p3) { }

void gbMatrix4::LeftTranslate(gbVec3D & p1) { }

void gbMatrix4::LoadIdentity() { }

void gbMatrix4::MakeMatrix(gbVec3D & p1, gbVec3D & p2, gbVec3D & p3) { }

void gbMatrix4::RightMultiply(gbMatrix4 const & p1) { }

void gbMatrix4::RightMultiply(gbQuaternion const & p1) { }

void gbMatrix4::RightScale(float p1, float p2, float p3) { }

void gbMatrix4::RightTranslate(float p1, float p2, float p3) { }

void gbMatrix4::RightTranslate(gbVec3D & p1) { }

void gbMatrix4::Rotate(gbVec3D const * p1, gbVec3D * p2) const { }

void gbMatrix4::RotateIn(gbVec3D * p1) { }

void gbMatrix4::SetAxisAngle(gbAxis p1, float p2) { }

void gbMatrix4::SetAxisAngle(gbAxis p1, float p2, float p3) { }

void gbMatrix4::SetAxisAngle(gbVec3D * p1, float p2) { }

void gbMatrix4::Transform(gbVec3D * p1, int p2) const { }

void gbMatrix4::Transform(gbVec3D * p1, gbVec3D * p2, int p3) const { }

void gbMatrix4::Transform(gbVec3D const * p1, gbVec3D * p2) const { }

void gbMatrix4::TransformPlane(float * const p1) { }

void gbMatrix4::Transform_W(gbVec3D * p1, gbVec3D * p2, int p3) const { }

void gbMatrix4::Transpose(gbMatrix4 * p1) const { }

void gbMatrix4::operator*=(float const * p1) { }

void gbMatrix4::operator*=(gbMatrix4 const & p1) { }

void gbMatrix4::operator*=(gbQuaternion const & p1) { }

void gbMatrix4::operator=(gbMatrix4 const & p1) { }

