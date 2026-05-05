#ifndef PAL3A_GEOMFACTORY_H
#define PAL3A_GEOMFACTORY_H

#include "pal3a_types.h"

int Geom_NewCone(float topRadius, float bottomRadius, float height, int numSides, gbGeomQuad * quadbuf, int bufsize, float fTexLoop);

#endif // PAL3A_GEOMFACTORY_H
