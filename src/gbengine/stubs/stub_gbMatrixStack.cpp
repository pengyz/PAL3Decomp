#include "gbengine/gbMisc.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbMatrixStack::gbMatrixStack(int p1) {}

gbMatrixStack::~gbMatrixStack() {}

gbMatrixStack & gbMatrixStack::operator=(gbMatrixStack const & p1) { static gbMatrixStack _d; return _d; }

int gbMatrixStack::GetDepth() { return 0; }

gbMatrix4 * gbMatrixStack::GetTop() { return 0; }

void gbMatrixStack::LoadIdentity() { }

void gbMatrixStack::LoadMatrix(gbMatrix4 * p1) { }

void gbMatrixStack::MultMatrix(gbMatrix4 * p1) { }

void gbMatrixStack::Pop() { }

void gbMatrixStack::Push() { }

void gbMatrixStack::Rotate(float p1, gbVec3D & p2) { }

void gbMatrixStack::Rotate(gbQuaternion & p1) { }

void gbMatrixStack::Scale(float p1, float p2, float p3) { }

void gbMatrixStack::Scale(gbVec3D & p1) { }

void gbMatrixStack::Translate(float p1, float p2, float p3) { }

void gbMatrixStack::Translate(gbVec3D & p1) { }

