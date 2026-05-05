#include "gbengine/gbGfxManager.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

int gbImage2DInfo::IsPreferAlpha() { return 0; }

gbImage2DInfo & gbImage2DInfo::operator=(gbImage2DInfo const & p1) { static gbImage2DInfo _d; return _d; }

