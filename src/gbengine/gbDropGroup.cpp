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
    desc.gravity = other.desc.gravity;
    desc.viewDistance = other.desc.viewDistance;
    desc.density = other.desc.density;
    desc.speedMinX = other.desc.speedMinX;
    desc.speedMaxX = other.desc.speedMaxX;
    desc.speedMinY = other.desc.speedMinY;
    desc.speedMaxY = other.desc.speedMaxY;
    desc.speedMinZ = other.desc.speedMinZ;
    desc.speedMaxZ = other.desc.speedMaxZ;
    elapsedTime = other.elapsedTime;
    spawnTimer = other.spawnTimer;
    units = other.units;
    pTexture = other.pTexture;
    pRenderEffect = other.pRenderEffect;
}
