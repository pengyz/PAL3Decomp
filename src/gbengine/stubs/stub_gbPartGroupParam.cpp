#include "gbengine/gbParticle.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbPartGroupParam::~gbPartGroupParam() {}

gbRenderEffect * gbPartGroupParam::GetRenderEffect() { return 0; }

gbTexture * gbPartGroupParam::GetTexture() { return 0; }

gbPartGroupParam & gbPartGroupParam::operator=(gbPartGroupParam const & p1) { static gbPartGroupParam _d; return _d; }

void gbPartGroupParam::ComputeAirResist(gbParticleUnit * p1, float p2) { }

void gbPartGroupParam::ComputeParticleParam(gbParticleUnit * p1, float p2, float p3) { }

void gbPartGroupParam::InitParticleParam(gbParticleUnit * p1) { }

void gbPartGroupParam::LoadFromFile(gbVFile * p1) { }

