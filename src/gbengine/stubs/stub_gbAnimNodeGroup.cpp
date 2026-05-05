#include "gbengine/gbParticle.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbAnimNodeGroup::gbAnimNodeGroup(gbGfxManager * p1) {}

gbAnimNodeGroup::~gbAnimNodeGroup() {}

gbAnimNodeGroup & gbAnimNodeGroup::operator=(gbAnimNodeGroup const & p1) { static gbAnimNodeGroup _d; return _d; }

gbAnimNodeGroup * gbAnimNodeGroup::Clone() { return 0; }

int gbAnimNodeGroup::IsDead() { return 0; }

void gbAnimNodeGroup::SetSoundFileDir(char * p1) { }

void gbAnimNodeGroup::Attach() { }

void gbAnimNodeGroup::LoadFromFile(char * p1) { }

void gbAnimNodeGroup::Reset() { }

void gbAnimNodeGroup::SetPosition(gbMatrix4 const & p1) { }

void gbAnimNodeGroup::SetPosition(gbVec3D const & p1) { }

void gbAnimNodeGroup::SetPriority(int p1) { }

void gbAnimNodeGroup::SetToDead() { }

void gbAnimNodeGroup::ShowGroup(int p1) { }

void gbAnimNodeGroup::Update() { }

