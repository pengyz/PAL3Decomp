#include "gbengine/gbParticle.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

int gbParticleGroup::UpdateOneParticle(gbParticleUnit * p1, double p2) { return 0; }

gbParticleUnit * gbParticleGroup::CreateOneParticle(gbEmitterData * p1) { return 0; }

gbParticleUnit * gbParticleGroup::GetOldestParticle() { return 0; }

char * gbParticleGroup::GetName() { return 0; }

gbParticleGroup & gbParticleGroup::operator=(gbParticleGroup const & p1) { static gbParticleGroup _d; return _d; }

int gbParticleGroup::GetAlivePartNum() { return 0; }

gbPartGroupParam * gbParticleGroup::GetGroupParam() { return 0; }

