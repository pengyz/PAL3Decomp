/**
 * gbengine.dll - gbDropGroup
 * Drop/particle group for weather effects (rain/snow)
 *
 * Compiler: MSVC 6.0 SP5
 */

#include "gbengine/gbParticle.h"
#include "gbengine/gbCamera.h"
#include <string.h>
#include <stdlib.h>

gbDropGroup::gbDropGroup(const gbDropGroup& other) {
    maxUnits = other.maxUnits;
    numActiveUnits = other.numActiveUnits;
    desc = other.desc;
    // NOTE: field_34 is intentionally NOT copied (offset 13 skipped in original)
    elapsedTime = other.elapsedTime;
    spawnTimer = other.spawnTimer;
    units = other.units;
    pTexture = other.pTexture;
    pRenderEffect = other.pRenderEffect;
}
