#include "gbengine/gbParticle.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbParticleEffect::gbParticleEffect(gbParticleEffect const & p1) {}

gbParticleEffect & gbParticleEffect::operator=(gbParticleEffect const & p1) { static gbParticleEffect _d; return _d; }

float gbParticleEffect::GetSpaceScale() { return 0.0f; }

void gbParticleEffect::Render(gbRenderInfoObj * p1) { }

void gbParticleEffect::SetSpaceScale(float p1) { }

