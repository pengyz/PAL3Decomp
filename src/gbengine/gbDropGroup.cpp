/**
 * gbengine.dll - gbDropGroup
 * Drop/particle group for weather effects (rain/snow)
 */

#include "gbengine/gbParticle.h"
#include "gbengine/gbCamera.h"
#include <string.h>
#include <stdlib.h>

gbDropGroup::gbDropGroup(const gbDropGroup& other) {
    maxUnits = other.maxUnits;
    numActiveUnits = other.numActiveUnits;
    *(((int*)this) + 4) = *(((int*)&other) + 4);
    *(((int*)this) + 5) = *(((int*)&other) + 5);
    *(((int*)this) + 6) = *(((int*)&other) + 6);
    *(((int*)this) + 7) = *(((int*)&other) + 7);
    *(((int*)this) + 8) = *(((int*)&other) + 8);
    *(((int*)this) + 9) = *(((int*)&other) + 9);
    *(((int*)this) + 10) = *(((int*)&other) + 10);
    *(((int*)this) + 11) = *(((int*)&other) + 11);
    *(((int*)this) + 12) = *(((int*)&other) + 12);
    *(((int*)this) + 14) = *(((int*)&other) + 14);
    *(((int*)this) + 15) = *(((int*)&other) + 15);
    *(((int*)this) + 16) = *(((int*)&other) + 16);
    *(((int*)this) + 17) = *(((int*)&other) + 17);
    *(((int*)this) + 18) = *(((int*)&other) + 18);
    *(((int*)this) + 19) = *(((int*)&other) + 19);
}
