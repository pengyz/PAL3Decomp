#include "gbengine/gbMisc.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbTimeCounter & gbTimeCounter::operator=(gbTimeCounter const & p1) { static gbTimeCounter _d; return _d; }

double gbTimeCounter::Off() { return 0.0; }

void gbTimeCounter::On() { }

