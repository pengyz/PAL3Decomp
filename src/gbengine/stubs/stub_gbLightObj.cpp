#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbLightObj::gbLightObj(gbLightObj const & p1) {}

gbLightObj::gbLightObj() {}

gbLightObj & gbLightObj::operator=(gbLightObj const & p1) { static gbLightObj _d; return _d; }

gbLight * gbLightObj::GetSysLight() { return 0; }

gbLightObj::~gbLightObj() {}

float gbLightObj::GetEffectOnPoint(gbVec3D const & p1, int p2) { return 0.0f; }

int gbLightObj::GetType() { return 0; }

gbSphere const * gbLightObj::GetBoundSphere() { return 0; }

void gbLightObj::Compute(gbVolModNode * p1) { }

void gbLightObj::ComputeBoundSphere() { }

void gbLightObj::Init(gbLightObj::LIGHT_TYPE p1) { }

