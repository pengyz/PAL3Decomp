#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbAABBox::gbAABBox() {}

int gbAABBox::IsColAABB(gbAABBox & p1) { return 0; }

int gbAABBox::IsColPoint(gbVec3D & p1) { return 0; }

gbAABBox & gbAABBox::operator=(gbAABBox const & p1) { static gbAABBox _d; return _d; }

void gbAABBox::Transform(gbMatrix4 * p1) { }

