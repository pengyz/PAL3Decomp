#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbPlane::gbPlane() {}

int gbPlane::IsColAABB(gbAABBox & p1) { return 0; }

int gbPlane::IsColOBB(gbOBBox & p1) { return 0; }

gbPlane & gbPlane::operator=(gbPlane const & p1) { static gbPlane _d; return _d; }

